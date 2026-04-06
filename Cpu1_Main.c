//#include "IfxCpu.h"
//#include "IfxScuWdt.h"
//#include "IfxStm.h"
//#include "Bsp.h"
//
//#include "Virtual_Input.h"
//#include "ActEcu_Enum.h"
//
//extern IfxCpu_syncEvent cpuSyncEvent;
//
//#define CPU1_PERIOD_MS                  (10u)
//
//static uint8 packByte0(uint8 safeState, uint8 speedState)
//{
//    return (uint8)((safeState & 0x0Fu) | ((speedState & 0x0Fu) << 4));
//}
//
//static uint8 packByte1(uint8 brakeActive, uint8 evState, uint8 ackButton, uint8 msgValid)
//{
//    return (uint8)((brakeActive & 0x01u)
//          | ((evState & 0x0Fu) << 1)
//          | ((ackButton & 0x01u) << 5)
//          | ((msgValid & 0x01u) << 6));
//}
//
//static uint8 packByte2(uint8 aliveCnt, uint8 ackSeq)
//{
//    return (uint8)((aliveCnt & 0x0Fu) | ((ackSeq & 0x0Fu) << 4));
//}
//
//int core1_main(void)
//{
//    uint32 step = 0u;
//    uint8 aliveCnt = 0u;
//    uint8 ackSeq = 0u;
//
//    IfxCpu_enableInterrupts();
//    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
//
//    IfxCpu_emitEvent(&cpuSyncEvent);
//    IfxCpu_waitEvent(&cpuSyncEvent, 1);
//
//    Virtual_Input_InjectorInit();
//
//    while (1)
//    {
//        uint8 safeState = (uint8)ACTECU_SAFE_NORMAL;
//        uint8 speedState = (uint8)ACTECU_SPEED_STOP;
//        uint8 brakeActive = 0u;
//        uint8 evState = (uint8)ACTECU_EVENT_NONE;
//        uint8 ackButton = 0u;
//        uint8 msgValid = 1u;
//        uint8 byte0;
//        uint8 byte1;
//        uint8 byte2;
//
//        if (step < 500u)
//        {
//            speedState = (uint8)ACTECU_SPEED_STOP;
//        }
//        else if (step < 1000u)
//        {
//            speedState = (uint8)ACTECU_SPEED_LOW;
//        }
//        else if (step < 1500u)
//        {
//            speedState = (uint8)ACTECU_SPEED_MID;
//        }
//        else if (step < 2000u)
//        {
//            speedState = (uint8)ACTECU_SPEED_HIGH;
//        }
//        else if (step < 2200u)
//        {
//            speedState = (uint8)ACTECU_SPEED_HIGH;
//            evState = (uint8)ACTECU_EVENT_RAPID_BRAKE;
//            brakeActive = 1u;
//        }
//        else if (step < 2700u)
//        {
//            speedState = (uint8)ACTECU_SPEED_LOW;
//        }
//        else if (step < 2900u)
//        {
//            speedState = (uint8)ACTECU_SPEED_LOW;
//            evState = (uint8)ACTECU_EVENT_RAPID_ACCEL;
//        }
//        else if (step < 3400u)
//        {
//            speedState = (uint8)ACTECU_SPEED_MID;
//        }
//        else if (step < 3600u)
//        {
//            speedState = (uint8)ACTECU_SPEED_MID;
//            evState = (uint8)ACTECU_EVENT_STEER_LEVEL1;
//        }
//        else if (step < 3800u)
//        {
//            speedState = (uint8)ACTECU_SPEED_MID;
//            evState = (uint8)ACTECU_EVENT_STEER_LEVEL2;
//        }
//        else if (step < 4300u)
//        {
//            safeState = (uint8)ACTECU_SAFE_CRITICAL;
//            speedState = (uint8)ACTECU_SPEED_MID;
//        }
//        else if (step < 4800u)
//        {
//            safeState = (uint8)ACTECU_SAFE_FATAL_NO_RESPONSE;
//            speedState = (uint8)ACTECU_SPEED_STOP;
//        }
//        else
//        {
//            step = 0u;
//            continue;
//        }
//
//        byte0 = packByte0(safeState, speedState);
//        byte1 = packByte1(brakeActive, evState, ackButton, msgValid);
//        byte2 = packByte2(aliveCnt, ackSeq);
//
//        Virtual_Input_InjectorWriteFrame(byte0, byte1, byte2);
//
//        aliveCnt = (uint8)((aliveCnt + 1u) & 0x0Fu);
//
//        step++;
//        waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, CPU1_PERIOD_MS));
//    }
//}
//
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "IfxStm.h"
#include "Bsp.h"

extern IfxCpu_syncEvent cpuSyncEvent;

int core1_main(void)
{
    IfxCpu_enableInterrupts();
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());

    IfxCpu_emitEvent(&cpuSyncEvent);
    IfxCpu_waitEvent(&cpuSyncEvent, 1);

    /* 실제 CAN 수신 사용 시 CPU1 가상 주입은 비활성화 */
    while (1)
    {
        waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 1000));
    }

    return 0;
}
