/**************************************************************************** 
* 
* Copyright (c) 2023  C*Core -   All Rights Reserved  
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* 
*   Project              : AUTOSAR 4.4.0 MCAL
*   Platform             : PowerPC e200
*   Peripheral           : 
*   Dependencies         : 
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 
*   Build Version        : 
*
*****************************************************************************/

/**
*   @file    Can.h
*   @version 1.0.1
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Can MCAL driver.
*
*   @addtogroup Can
*   @{
*/

#ifndef Can_H
#define Can_H

#ifdef __cplusplus
extern "C"{
#endif

#include "ComStack_Types.h"
#include "Can_Cfg.h"
#include "Can_GeneralTypes.h"
#include "Mcal.h"
#include "Can_LLDriver.h"
#include "Can_Irq.h"

#define CAN_H_VENDOR_ID                     176
#define CAN_H_AR_REL_MAJOR_VER              4
#define CAN_H_AR_REL_MINOR_VER              4
#define CAN_H_AR_REL_REV_VER                0
#define CAN_H_SW_MAJOR_VER                  1
#define CAN_H_SW_MINOR_VER                  0
#define CAN_H_SW_PATCH_VER                  1
#define CAN_MODULE_ID                       80

#if (CAN_CFG_H_VENDOR_ID != CAN_H_VENDOR_ID)
    #error " NON-MATCHED DATA : CAN_H_VENDOR_ID "
#endif
#if (CAN_CFG_H_AR_REL_MAJOR_VER != CAN_H_AR_REL_MAJOR_VER)
    #error " NON-MATCHED DATA : CAN_H_AR_REL_MAJOR_VER "
#endif
#if (CAN_CFG_H_AR_REL_MINOR_VER != CAN_H_AR_REL_MINOR_VER)
    #error " NON-MATCHED DATA : CAN_H_AR_REL_MINOR_VER "
#endif
#if (CAN_CFG_H_AR_REL_REV_VER != CAN_H_AR_REL_REV_VER)
    #error " NON-MATCHED DATA : CAN_H_AR_REL_REV_VER "
#endif
#if (CAN_CFG_H_SW_MAJOR_VER != CAN_H_SW_MAJOR_VER)
    #error " NON-MATCHED DATA : CAN_H_SW_MAJOR_VER "
#endif
#if (CAN_CFG_H_SW_MINOR_VER != CAN_H_SW_MINOR_VER)
    #error " NON-MATCHED DATA : CAN_H_SW_MINOR_VER "
#endif
#if (CAN_CFG_H_SW_PATCH_VER != CAN_H_SW_PATCH_VER)
    #error " NON-MATCHED DATA : CAN_H_SW_PATCH_VER "
#endif

#define CAN_E_PARAM_POINTER         ((uint8)0x01U)
#define CAN_E_PARAM_HANDLE          ((uint8)0x02U)
#define CAN_E_PARAM_DATA_LENGTH     ((uint8)0x03U)
#define CAN_E_PARAM_CONTROLLER      ((uint8)0x04U)
#define CAN_E_UNINIT                ((uint8)0x05U)
#define CAN_E_TRANSITION            ((uint8)0x06U)
#define CAN_E_PARAM_BAUDRATE        ((uint8)0x07U)
#define CAN_E_ICOM_CONFIG_INVALID   ((uint8)0x08U)
#define CAN_E_INIT_FAILED           ((uint8)0x09U)
#define CAN_E_DATALOST              ((uint8)0x01U)
#define CAN_E_INVALID_CONTROLLER    ((uint8)0x0AU)
#define CAN_E_PARAM_CONFIG          ((uint8)0x0BU)

#define CAN_SID_INIT                          ((uint8)0x00U)
#define CAN_SID_MAIN_FUNCTION_WRITE           ((uint8)0x01U)
#define CAN_SID_SET_CONTROLLER_MODE           ((uint8)0x03U)
#define CAN_SID_DISABLE_CONT_INTERRUPTS       ((uint8)0x04U)
#define CAN_SID_ENABLE_CONT_INTERRUPTS        ((uint8)0x05U)
#define CAN_SID_WRITE                         ((uint8)0x06U)
#define CAN_SID_GET_VERSION_INFO              ((uint8)0x07U)
#define CAN_SID_MAIN_FUNCTION_READ            ((uint8)0x08U)
#define CAN_SID_MAIN_FUNCTION_BUS_OFF         ((uint8)0x09U)
#define CAN_SID_MAIN_FUNCTION_WAKEUP          ((uint8)0x0AU)
#define CAN_SID_CBK_CHECK_WAKEUP              ((uint8)0x0BU)
#define CAN_SID_MAIN_FUNCTION_MODE            ((uint8)0x0CU)
#define CAN_SID_CHANGE_BAUDRATE               ((uint8)0x0DU)
#define CAN_SID_CHECK_BAUDRATE                ((uint8)0x0EU)
#define CAN_SID_SET_BAUDRATE                  ((uint8)0x0FU)
#define CAN_SID_DEINIT                        ((uint8)0x10U)
#define CAN_SID_GETCONTROLLERERRORSTATE       ((uint8)0x11U)
#define CAN_SID_GETCONTROLLERMODE             ((uint8)0x12U)
#define CAN_SID_GET_RX_ERROR_COUNTER          ((uint8)0x30U)
#define CAN_SID_GET_TX_ERROR_COUNTER          ((uint8)0x31U)

#if (CAN_MULTICORE_ENABLED == STD_ON)
    #define Can_GetCoreID()       GetCoreID()
#else
    #define Can_GetCoreID()       ((uint32)CAN_DEFAULT_COREID)
#endif

typedef enum {
    CAN_UNINIT = 0U,
    CAN_READY
} Can_DriverStateType;

typedef struct {
    P2CONST(mcan_hwObject, CAN_CONST, CAN_APPL_CONST)   hwObjectConfig;
    P2CONST(CANConfig, CAN_CONST, CAN_APPL_CONST)       controllerConfig;
    CONST(uint32, CAN_CONST)                             HwObjCount;
#if (CAN_MULTICORE_ENABLED == STD_ON)
    P2CONST(mcan_core_map_t, CAN_CONST, CAN_APPL_CONST) coreMap;
#endif
} Can_ConfigType;

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"

#if (CAN_VERSION_INFO_API == STD_ON)
FUNC(void, CAN_CODE) Can_GetVersionInfo \
( \
    P2VAR(Std_VersionInfoType, AUTOMATIC, CAN_APPL_DATA) versioninfo \
);
#endif
FUNC(void, CAN_CODE) Can_Init(P2CONST(Can_ConfigType, AUTOMATIC, CAN_APPL_CONST) Config);
FUNC(void, CAN_CODE) Can_DeInit(void);
#if (CAN_SET_BAUDRATE_API == STD_ON)
FUNC(Std_ReturnType, CAN_CODE) Can_SetBaudrate \
( \
    VAR(uint8, AUTOMATIC) Controller, \
    VAR(uint16, AUTOMATIC) BaudRateConfigID \
);
#endif
FUNC(Std_ReturnType, CAN_CODE) Can_SetControllerMode \
( \
    VAR(uint8, AUTOMATIC) Controller, \
    VAR(Can_ControllerStateType, AUTOMATIC) Transition \
);
FUNC(void, CAN_CODE) Can_DisableControllerInterrupts(VAR(uint8, AUTOMATIC) Controller);
FUNC(void, CAN_CODE) Can_EnableControllerInterrupts(VAR(uint8, AUTOMATIC) Controller);
/*
    [SWS_Can_00485] The function Can_CheckWakeup shall be pre compile time 
    configurable On/Off by the configuration parameter: CanWakeupFunctionalityAPI
*/
#if (CAN_CHECK_WAKEUP_API == STD_ON)
FUNC(Std_ReturnType, CAN_CODE) Can_CheckWakeup(VAR(uint8, AUTOMATIC) Controller);
#endif
FUNC(Std_ReturnType, CAN_CODE) Can_GetControllerErrorState \
( \
    VAR(uint8, AUTOMATIC) ControllerId, \
    P2VAR(Can_ErrorStateType, AUTOMATIC, CAN_APPL_DATA) ErrorStatePtr \
);
FUNC(Std_ReturnType, CAN_CODE) Can_GetControllerMode \
( \
    VAR(uint8, AUTOMATIC) Controller, \
    P2VAR(Can_ControllerStateType, AUTOMATIC, CAN_APPL_DATA) ControllerModePtr \
);
FUNC(Std_ReturnType, CAN_CODE) Can_GetControllerRxErrorCounter \
( \
    VAR(uint8, AUTOMATIC) ControllerId, \
    P2VAR(uint8, AUTOMATIC, CAN_APPL_DATA) pRxErrorCounterPtr \
);
FUNC(Std_ReturnType, CAN_CODE) Can_GetControllerTxErrorCounter \
( \
    VAR(uint8, AUTOMATIC) ControllerId, \
    P2VAR(uint8, AUTOMATIC, CAN_APPL_DATA) pTxErrorCounterPtr \
);
FUNC(Std_ReturnType, CAN_CODE) Can_Write \
( \
    VAR(Can_HwHandleType, AUTOMATIC) Hth, \
    P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) PduInfo \
);
/*
    [SWS_Can_00031] The function Can_MainFunction_Write shall perform the polling 
    of TX confirmation when CanTxProcessing
*/
#if (CAN_MAINFUNCTION_WRITE_API == STD_ON)
FUNC(void, CAN_CODE) Can_MainFunction_Write(void);
#endif
/*
    [SWS_Can_00108] The function Can_MainFunction_Read shall perform the polling 
    of RX indications when CanRxProcessing is set to POLLING or MIXED. In case of 
    MIXED processing only the hardware objects for which 
    CanHardwareObjectUsesPolling is set to TRUE shall be polled.
*/
#if (CAN_MAINFUNCTION_READ_API == STD_ON)
FUNC(void, CAN_CODE) Can_MainFunction_Read(void);
#endif
/*
    [SWS_Can_00109] The function Can_MainFunction_BusOff shall perform the 
    polling of bus-off events that are configured statically as 'to be polled'.
*/
#if (CAN_MAINFUNCTION_BUSOFF_API == STD_ON)
FUNC(void, CAN_CODE) Can_MainFunction_BusOff(void);
#endif
/*
    [SWS_Can_00112] The function Can_MainFunction_Wakeup shall perform the 
    polling of wake-up events that are configured statically as 'to be polled'.
*/
#if (CAN_MAINFUNCTION_WAKEUP_API == STD_ON)
FUNC(void, CAN_CODE) Can_MainFunction_Wakeup(void);
#endif
FUNC(void, CAN_CODE) Can_MainFunction_Mode(void);

#if (CAN_MULTIPLE_READ_PERIOD == STD_ON)

#ifdef CAN_MAINFUNCTION_PERIOD_READ_0
extern FUNC(void, CAN_CODE) Can_MainFunction_Read_0(void);
#endif

#ifdef CAN_MAINFUNCTION_PERIOD_READ_1
extern FUNC(void, CAN_CODE) Can_MainFunction_Read_1(void);
#endif

#ifdef CAN_MAINFUNCTION_PERIOD_READ_2
extern FUNC(void, CAN_CODE) Can_MainFunction_Read_2(void);
#endif

#ifdef CAN_MAINFUNCTION_PERIOD_READ_3
extern FUNC(void, CAN_CODE) Can_MainFunction_Read_3(void);
#endif

#ifdef CAN_MAINFUNCTION_PERIOD_READ_4
extern FUNC(void, CAN_CODE) Can_MainFunction_Read_4(void);
#endif

#endif // CAN_MULTIPLE_READ_PERIOD

#if (CAN_MULTIPLE_WRITE_PERIOD == STD_ON)

#ifdef CAN_MAINFUNCTION_PERIOD_WRITE_0
extern FUNC(void, CAN_CODE) Can_MainFunction_Write_0(void);
#endif

#ifdef CAN_MAINFUNCTION_PERIOD_WRITE_1
extern FUNC(void, CAN_CODE) Can_MainFunction_Write_1(void);
#endif

#ifdef CAN_MAINFUNCTION_PERIOD_WRITE_2
extern FUNC(void, CAN_CODE) Can_MainFunction_Write_2(void);
#endif

#ifdef CAN_MAINFUNCTION_PERIOD_WRITE_3
extern FUNC(void, CAN_CODE) Can_MainFunction_Write_3(void);
#endif

#ifdef CAN_MAINFUNCTION_PERIOD_WRITE_4
extern FUNC(void, CAN_CODE) Can_MainFunction_Write_4(void);
#endif

#endif

#if (CAN_PRECOMPILE_SUPPORT == STD_OFF)
CAN_PB_CONFIG_DECLARATION
#else
extern CONST(Can_ConfigType, CAN_CONST) Can_Config;
#endif

extern P2CONST(Can_ConfigType, CAN_VAR, CAN_APPL_CONST) g_pCan_CurConfig;

#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#ifdef __cplusplus
}
#endif

#endif
