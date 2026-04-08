#include "Virtual_Input.h"
#include "Driver_Can.h"
#include "App_Scheduler.h"
#include "ActEcu_Types.h"

#define VIRTUAL_INPUT_FRAME_TIMEOUT_CYCLES   (3u)
#define VIRTUAL_INPUT_INVALID_FRAME_LIMIT    (3u)
#define VIRTUAL_INPUT_ALIVE_STALE_LIMIT      (3u)

volatile VirtualInput_Shared g_virtual_input_shared = {0u, 0u, {0u, 0u, 0u}, 0u};

volatile uint8  g_one_shot_active = 0u;
volatile uint16 g_one_shot_cnt    = 0u;

static uint32 g_last_seq_cpu0         = 0u;
static uint8  g_prev_ack_seq_cpu0     = 0u;
static uint8  g_ack_seq_initialized   = 0u;

static uint8  g_prev_alive_cnt_cpu0   = 0u;
static uint8  g_alive_initialized     = 0u;

static uint8  g_no_new_frame_cnt_cpu0  = 0u;
static uint8  g_invalid_frame_cnt_cpu0 = 0u;
static uint8  g_alive_stale_cnt_cpu0   = 0u;

static App_InputSignals g_rx_signals;

static uint8 virtual_input_is_valid_safe_state(uint8 raw_safe_state)
{
    return (raw_safe_state <= (uint8)ACTECU_SAFE_FATAL_NO_RESPONSE) ? 1u : 0u;
}

static uint8 virtual_input_is_valid_speed_state(uint8 raw_speed_state)
{
    return (raw_speed_state <= (uint8)ACTECU_SPEED_HIGH) ? 1u : 0u;
}

static ActEcu_SafeState virtual_input_decode_safe_state(uint8 raw_safe_state)
{
    switch (raw_safe_state)
    {
    case ACTECU_SAFE_NORMAL:
        return ACTECU_SAFE_NORMAL;
    case ACTECU_SAFE_WARNING:
        return ACTECU_SAFE_WARNING;
    case ACTECU_SAFE_CRITICAL:
        return ACTECU_SAFE_CRITICAL;
    case ACTECU_SAFE_FATAL_NO_RESPONSE:
        return ACTECU_SAFE_FATAL_NO_RESPONSE;
    default:
        return ACTECU_SAFE_NORMAL;
    }
}

static void virtual_input_clear_rx_signals(void)
{
    g_rx_signals.safe_state_raw = 0u;
    g_rx_signals.speed_state_raw = 0u;
    g_rx_signals.brake_active = 0u;
    g_rx_signals.ev_state = 0u;
    g_rx_signals.ack_button = 0u;
    g_rx_signals.msg_valid = 0u;
    g_rx_signals.alive_cnt = 0u;
    g_rx_signals.ack_seq = 0u;
    g_rx_signals.ack_seq_prev = 0u;
}

static void virtual_input_reset_comm_monitor(void)
{
    g_prev_ack_seq_cpu0      = 0u;
    g_ack_seq_initialized    = 0u;

    g_prev_alive_cnt_cpu0    = 0u;
    g_alive_initialized      = 0u;

    g_no_new_frame_cnt_cpu0   = 0u;
    g_invalid_frame_cnt_cpu0  = 0u;
    g_alive_stale_cnt_cpu0    = 0u;
}

static void virtual_input_apply_parsed_signals(uint8 raw_safe_state,
                                               uint8 raw_speed_state,
                                               uint8 brake_active,
                                               uint8 ev_state,
                                               uint8 ack_button)
{
    App_Scheduler_SetSafeState(virtual_input_decode_safe_state(raw_safe_state));
    App_Scheduler_SetSpeedState(raw_speed_state);
    App_Scheduler_SetBrakeActive(brake_active);
    App_Scheduler_SetEventState(ev_state);
    App_Scheduler_SetAckButton(ack_button);
}

static void virtual_input_apply_comm_fail_safe(void)
{
//    App_Scheduler_SetSafeState(ACTECU_SAFE_FATAL_NO_RESPONSE);
//    App_Scheduler_SetSpeedState((uint8)ACTECU_SPEED_STOP);
//    App_Scheduler_SetBrakeActive(0u);
//    App_Scheduler_SetEventState((uint8)ACTECU_EVENT_NONE);
//    App_Scheduler_SetAckButton(0u);
//
//    virtual_input_reset_comm_monitor();
}

void Virtual_Input_Init(void)
{
    g_virtual_input_shared.valid = 0u;
    g_virtual_input_shared.seq = 0u;
    g_virtual_input_shared.data[0] = 0u;
    g_virtual_input_shared.data[1] = 0u;
    g_virtual_input_shared.data[2] = 0u;
    g_virtual_input_shared.reserved = 0u;

    g_last_seq_cpu0 = 0u;

    virtual_input_reset_comm_monitor();
    virtual_input_clear_rx_signals();

    g_one_shot_active = 0u;
    g_one_shot_cnt = 0u;
}

void Virtual_Input_Task(void)
{
    uint32 curr_seq;
    uint8  byte0;
    uint8  byte1;
    uint8  byte2;

    uint8  raw_safe_state;
    uint8  raw_speed_state;
    uint8  brake_active;
    uint8  ev_state;
    uint8  ack_button;
    uint8  msg_valid;
    uint8  reserved_bit;
    uint8  alive_cnt;
    uint8  ack_seq;

    if (g_virtual_input_shared.valid == 0u)
    {
        return;
    }

    curr_seq = g_virtual_input_shared.seq;

    if (curr_seq == g_last_seq_cpu0)
    {
        if (g_no_new_frame_cnt_cpu0 < 0xFFu)
        {
            g_no_new_frame_cnt_cpu0++;
        }

        if (g_no_new_frame_cnt_cpu0 >= VIRTUAL_INPUT_FRAME_TIMEOUT_CYCLES)
        {
            virtual_input_apply_comm_fail_safe();
        }

        return;
    }

    g_last_seq_cpu0 = curr_seq;
    g_no_new_frame_cnt_cpu0 = 0u;

    byte0 = g_virtual_input_shared.data[0];
    byte1 = g_virtual_input_shared.data[1];
    byte2 = g_virtual_input_shared.data[2];

    raw_safe_state  = (uint8)(byte0 & 0x0Fu);
    raw_speed_state = (uint8)((byte0 >> 4) & 0x0Fu);

    brake_active = (uint8)(byte1 & 0x01u);
    ev_state     = (uint8)((byte1 >> 1) & 0x0Fu);
    ack_button   = (uint8)((byte1 >> 5) & 0x01u);
    msg_valid    = (uint8)((byte1 >> 6) & 0x01u);
    reserved_bit = (uint8)((byte1 >> 7) & 0x01u);

    alive_cnt = (uint8)(byte2 & 0x0Fu);
    ack_seq   = (uint8)((byte2 >> 4) & 0x0Fu);

    g_rx_signals.safe_state_raw = raw_safe_state;
    g_rx_signals.speed_state_raw = raw_speed_state;
    g_rx_signals.brake_active = brake_active;
    g_rx_signals.ev_state = ev_state;
    g_rx_signals.ack_button = ack_button;
    g_rx_signals.msg_valid = msg_valid;
    g_rx_signals.alive_cnt = alive_cnt;
    g_rx_signals.ack_seq_prev = g_rx_signals.ack_seq;
    g_rx_signals.ack_seq = ack_seq;

    if ((reserved_bit != 0u) ||
        (virtual_input_is_valid_safe_state(raw_safe_state) == 0u) ||
        (virtual_input_is_valid_speed_state(raw_speed_state) == 0u))
    {
        if (g_invalid_frame_cnt_cpu0 < 0xFFu)
        {
            g_invalid_frame_cnt_cpu0++;
        }

        if (g_invalid_frame_cnt_cpu0 >= VIRTUAL_INPUT_INVALID_FRAME_LIMIT)
        {
            virtual_input_apply_comm_fail_safe();
        }

        return;
    }

    g_invalid_frame_cnt_cpu0 = 0u;

    if (g_alive_initialized == 0u)
    {
        g_prev_alive_cnt_cpu0 = alive_cnt;
        g_alive_initialized = 1u;
        g_alive_stale_cnt_cpu0 = 0u;
    }
    else
    {
        if (alive_cnt == g_prev_alive_cnt_cpu0)
        {
            if (g_alive_stale_cnt_cpu0 < 0xFFu)
            {
                g_alive_stale_cnt_cpu0++;
            }
        }
        else
        {
            g_alive_stale_cnt_cpu0 = 0u;
        }

        g_prev_alive_cnt_cpu0 = alive_cnt;
    }

    if (g_alive_stale_cnt_cpu0 >= VIRTUAL_INPUT_ALIVE_STALE_LIMIT)
    {
        virtual_input_apply_comm_fail_safe();
        return;
    }

    virtual_input_apply_parsed_signals(raw_safe_state,
                                       raw_speed_state,
                                       brake_active,
                                       ev_state,
                                       ack_button);

    if (g_ack_seq_initialized == 0u)
    {
        g_prev_ack_seq_cpu0 = ack_seq;
        g_ack_seq_initialized = 1u;
    }
    else
    {
        if (ack_seq != g_prev_ack_seq_cpu0)
        {
            g_one_shot_active = 1u;
            g_one_shot_cnt = 0u;
        }

        g_prev_ack_seq_cpu0 = ack_seq;
    }
}

void Virtual_Input_InjectorInit(void)
{
    g_virtual_input_shared.valid = 0u;
    g_virtual_input_shared.seq = 0u;
    g_virtual_input_shared.data[0] = 0u;
    g_virtual_input_shared.data[1] = 0u;
    g_virtual_input_shared.data[2] = 0u;
    g_virtual_input_shared.reserved = 0u;

    Virtual_Input_InjectorWriteFrame(0x00u, 0x00u, 0x00u);
}

void Virtual_Input_InjectorWriteFrame(uint8 byte0, uint8 byte1, uint8 byte2)
{
    g_virtual_input_shared.valid = 0u;

    g_virtual_input_shared.data[0] = byte0;
    g_virtual_input_shared.data[1] = byte1;
    g_virtual_input_shared.data[2] = byte2;
    g_virtual_input_shared.reserved = 0u;

    g_virtual_input_shared.seq++;
    g_virtual_input_shared.valid = 1u;
}
