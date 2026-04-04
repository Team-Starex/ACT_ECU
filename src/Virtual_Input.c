#include "Virtual_Input.h"
#include "Driver_Can.h"
#include "App_Scheduler.h"
#include "ActEcu_Types.h"

#define VIRTUAL_INPUT_FRAME_TIMEOUT_CYCLES   (3u)
#define VIRTUAL_INPUT_INVALID_FRAME_LIMIT    (3u)
#define VIRTUAL_INPUT_ALIVE_STALE_LIMIT      (3u)

volatile VirtualInput_Shared g_virtualInputShared = {0u, 0u, {0u, 0u, 0u}, 0u};

volatile uint8  g_oneShotActive = 0u;
volatile uint16 g_oneShotCnt    = 0u;

static uint32 g_lastSeqCpu0          = 0u;
static uint8  g_prevAckSeqCpu0       = 0u;
static uint8  g_ackSeqInitialized    = 0u;

static uint8  g_prevAliveCntCpu0     = 0u;
static uint8  g_aliveInitialized     = 0u;

static uint8  g_noNewFrameCntCpu0    = 0u;
static uint8  g_invalidFrameCntCpu0  = 0u;
static uint8  g_aliveStaleCntCpu0    = 0u;

static App_InputSignals g_rxSignals;

static uint8 Virtual_Input_IsValidSafeState(uint8 rawSafeState)
{
    return (rawSafeState <= (uint8)ACTECU_SAFE_FATAL_NO_RESPONSE) ? 1u : 0u;
}

static uint8 Virtual_Input_IsValidSpeedState(uint8 rawSpeedState)
{
    return (rawSpeedState <= (uint8)ACTECU_SPEED_HIGH) ? 1u : 0u;
}

static ActEcu_SafeState Virtual_Input_DecodeSafeState(uint8 rawSafeState)
{
    switch (rawSafeState)
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

static void Virtual_Input_ClearRxSignals(void)
{
    g_rxSignals.safeStateRaw = 0u;
    g_rxSignals.speedStateRaw = 0u;
    g_rxSignals.brakeActive = 0u;
    g_rxSignals.evState = 0u;
    g_rxSignals.ackButton = 0u;
    g_rxSignals.msgValid = 0u;
    g_rxSignals.aliveCnt = 0u;
    g_rxSignals.ackSeq = 0u;
    g_rxSignals.ackSeqPrev = 0u;
}

static void Virtual_Input_ResetCommMonitor(void)
{
    g_prevAckSeqCpu0      = 0u;
    g_ackSeqInitialized   = 0u;

    g_prevAliveCntCpu0    = 0u;
    g_aliveInitialized    = 0u;

    g_noNewFrameCntCpu0   = 0u;
    g_invalidFrameCntCpu0 = 0u;
    g_aliveStaleCntCpu0   = 0u;
}

static void Virtual_Input_ApplyParsedSignals(uint8 rawSafeState,
                                             uint8 rawSpeedState,
                                             uint8 brakeActive,
                                             uint8 evState,
                                             uint8 ackButton)
{
    App_Scheduler_SetSafeState(Virtual_Input_DecodeSafeState(rawSafeState));
    App_Scheduler_SetSpeedState(rawSpeedState);
    App_Scheduler_SetBrakeActive(brakeActive);
    App_Scheduler_SetEventState(evState);
    App_Scheduler_SetAckButton(ackButton);
}

static void Virtual_Input_ApplyCommFailSafe(void)
{
//    App_Scheduler_SetSafeState(ACTECU_SAFE_FATAL_NO_RESPONSE);
//    App_Scheduler_SetSpeedState((uint8)ACTECU_SPEED_STOP);
//    App_Scheduler_SetBrakeActive(0u);
//    App_Scheduler_SetEventState((uint8)ACTECU_EVENT_NONE);
//    App_Scheduler_SetAckButton(0u);
//
//    Virtual_Input_ResetCommMonitor();
}

void Virtual_Input_Init(void)
{
    g_virtualInputShared.valid = 0u;
    g_virtualInputShared.seq = 0u;
    g_virtualInputShared.data[0] = 0u;
    g_virtualInputShared.data[1] = 0u;
    g_virtualInputShared.data[2] = 0u;
    g_virtualInputShared.reserved = 0u;

    g_lastSeqCpu0 = 0u;

    Virtual_Input_ResetCommMonitor();
    Virtual_Input_ClearRxSignals();

    g_oneShotActive = 0u;
    g_oneShotCnt = 0u;
}

void Virtual_Input_Task(void)
{
    uint32 currSeq;
    uint8  byte0;
    uint8  byte1;
    uint8  byte2;

    uint8  rawSafeState;
    uint8  rawSpeedState;
    uint8  brakeActive;
    uint8  evState;
    uint8  ackButton;
    uint8  msgValid;
    uint8  reservedBit;
    uint8  aliveCnt;
    uint8  ackSeq;

    if (g_virtualInputShared.valid == 0u)
    {
        return;
    }

    currSeq = g_virtualInputShared.seq;

    if (currSeq == g_lastSeqCpu0)
    {
        if (g_noNewFrameCntCpu0 < 0xFFu)
        {
            g_noNewFrameCntCpu0++;
        }

        if (g_noNewFrameCntCpu0 >= VIRTUAL_INPUT_FRAME_TIMEOUT_CYCLES)
        {
            Virtual_Input_ApplyCommFailSafe();
        }

        return;
    }

    g_lastSeqCpu0 = currSeq;
    g_noNewFrameCntCpu0 = 0u;

    byte0 = g_virtualInputShared.data[0];
    byte1 = g_virtualInputShared.data[1];
    byte2 = g_virtualInputShared.data[2];

    rawSafeState = (uint8)(byte0 & 0x0Fu);
    rawSpeedState = (uint8)((byte0 >> 4) & 0x0Fu);

    brakeActive = (uint8)(byte1 & 0x01u);
    evState     = (uint8)((byte1 >> 1) & 0x0Fu);
    ackButton   = (uint8)((byte1 >> 5) & 0x01u);
    msgValid    = (uint8)((byte1 >> 6) & 0x01u);
    reservedBit = (uint8)((byte1 >> 7) & 0x01u);

    aliveCnt = (uint8)(byte2 & 0x0Fu);
    ackSeq   = (uint8)((byte2 >> 4) & 0x0Fu);

    g_rxSignals.safeStateRaw = rawSafeState;
    g_rxSignals.speedStateRaw = rawSpeedState;
    g_rxSignals.brakeActive = brakeActive;
    g_rxSignals.evState = evState;
    g_rxSignals.ackButton = ackButton;
    g_rxSignals.msgValid = msgValid;
    g_rxSignals.aliveCnt = aliveCnt;
    g_rxSignals.ackSeqPrev = g_rxSignals.ackSeq;
    g_rxSignals.ackSeq = ackSeq;

    if ((msgValid == 0u) ||
        (reservedBit != 0u) ||
        (Virtual_Input_IsValidSafeState(rawSafeState) == 0u) ||
        (Virtual_Input_IsValidSpeedState(rawSpeedState) == 0u))
    {
        if (g_invalidFrameCntCpu0 < 0xFFu)
        {
            g_invalidFrameCntCpu0++;
        }

        if (g_invalidFrameCntCpu0 >= VIRTUAL_INPUT_INVALID_FRAME_LIMIT)
        {
            Virtual_Input_ApplyCommFailSafe();
        }

        return;
    }

    g_invalidFrameCntCpu0 = 0u;

    if (g_aliveInitialized == 0u)
    {
        g_prevAliveCntCpu0 = aliveCnt;
        g_aliveInitialized = 1u;
        g_aliveStaleCntCpu0 = 0u;
    }
    else
    {
        if (aliveCnt == g_prevAliveCntCpu0)
        {
            if (g_aliveStaleCntCpu0 < 0xFFu)
            {
                g_aliveStaleCntCpu0++;
            }
        }
        else
        {
            g_aliveStaleCntCpu0 = 0u;
        }

        g_prevAliveCntCpu0 = aliveCnt;
    }

    if (g_aliveStaleCntCpu0 >= VIRTUAL_INPUT_ALIVE_STALE_LIMIT)
    {
        Virtual_Input_ApplyCommFailSafe();
        return;
    }

    Virtual_Input_ApplyParsedSignals(rawSafeState,
                                     rawSpeedState,
                                     brakeActive,
                                     evState,
                                     ackButton);

    if (g_ackSeqInitialized == 0u)
    {
        g_prevAckSeqCpu0 = ackSeq;
        g_ackSeqInitialized = 1u;
    }
    else
    {
        if (ackSeq != g_prevAckSeqCpu0)
        {
            g_oneShotActive = 1u;
            g_oneShotCnt = 0u;
        }

        g_prevAckSeqCpu0 = ackSeq;
    }
}

void Virtual_Input_InjectorInit(void)
{
    g_virtualInputShared.valid = 0u;
    g_virtualInputShared.seq = 0u;
    g_virtualInputShared.data[0] = 0u;
    g_virtualInputShared.data[1] = 0u;
    g_virtualInputShared.data[2] = 0u;
    g_virtualInputShared.reserved = 0u;

    /* 초기값은 "아직 유효한 프레임 없음" 상태로 둠 */
    Virtual_Input_InjectorWriteFrame(0x00u, 0x00u, 0x00u);
}

void Virtual_Input_InjectorWriteFrame(uint8 byte0, uint8 byte1, uint8 byte2)
{
    g_virtualInputShared.valid = 0u;

    g_virtualInputShared.data[0] = byte0;
    g_virtualInputShared.data[1] = byte1;
    g_virtualInputShared.data[2] = byte2;
    g_virtualInputShared.reserved = 0u;

    g_virtualInputShared.seq++;
    g_virtualInputShared.valid = 1u;
}
