/**************************************************************************** 
* 
* Copyright (c) 2023  C*Core -   All Rights Reserved  
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* 
*   Project              : AUTOSAR 4.4.0 MCAL
*   Platform             : PowerPC 
*   Peripheral           : 
*   Dependencies         : 
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : 
*   Autosar Conf.Variant :
*   SW Version           : 
*   Build Version        : 
*  
*****************************************************************************/

/**
*   @file    Icu_eTPU_Wrapper.h
*   @version 
*
*      AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Icu MCAL driver.
*
*   @addtogroup Icu
*   @{
*/
#ifndef ICU_ETPU_WRAPPER_H
#define ICU_ETPU_WRAPPER_H

#ifdef __cplusplus
extern "C"
{
#endif

/*====================================================================================================
                                        INCLUDE FILES
====================================================================================================*/
#include "Icu_eTPU_HAL_Wrapper.h"
struct ICU_eTPU_ConfigType;
#include "Icu.h"
#include "Icu_eMIOS_Types.h"
#ifdef RESOURCE_SUPPORT_ETPU
/*====================================================================================================
                                SOURCE FILE VERSION INFORMATION
====================================================================================================*/

/*====================================================================================================
                                        FILE VERSION CHECKS
====================================================================================================*/
#define ICU_ETPU_WRAPPER_VENDOR_ID_H                   176

#define ICU_ETPU_WRAPPER_MAJOR_VER_H                   4
#define ICU_ETPU_WRAPPER_MINOR_VER_H                   4
#define ICU_ETPU_WRAPPER_REVISION_VER_H                0

#define ICU_ETPU_WRAPPER_SW_MAJOR_VER_H                1
#define ICU_ETPU_WRAPPER_SW_MINOR_VER_H                0
#define ICU_ETPU_WRAPPER_SW_PATCH_VER_H                1

#if (ICU_ETPU_WRAPPER_VENDOR_ID_H != ICU_VENDOR_ID_H)
#error "NON-MATCHED DATA : ICU_VENDOR_ID_CFG"
#endif

/* Check if current file and ICU header file are of the same Autosar version */
#if (ICU_ETPU_WRAPPER_MAJOR_VER_H != ICU_MAJOR_VER_H)
#error "NON-MATCHED DATA : ICU_MAJOR_VER_H"
#endif
#if (ICU_ETPU_WRAPPER_MINOR_VER_H != ICU_MINOR_VER_H)
#error "NON-MATCHED DATA : ICU_MINOR_VER_H"
#endif
#if (ICU_ETPU_WRAPPER_REVISION_VER_H != ICU_REVISION_VER_H)
#error "NON-MATCHED DATA : ICU_REVISION_VER_H"
#endif

/* Check if current file and ICU header file are of the same Software version */
#if (ICU_ETPU_WRAPPER_SW_MAJOR_VER_H != ICU_SW_MAJOR_VER_H)
#error "NON-MATCHED DATA : ICU_SW_MAJOR_VER_H"
#endif
#if (ICU_ETPU_WRAPPER_SW_MINOR_VER_H != ICU_SW_MINOR_VER_H)
#error "NON-MATCHED DATA : ICU_SW_MINOR_VER_H"
#endif
#if (ICU_ETPU_WRAPPER_SW_PATCH_VER_H != ICU_SW_PATCH_VER_H)
#error "NON-MATCHED DATA : ICU_SW_PATCH_VER_H"
#endif
/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
#define ICU_ETPU_CHANNEL_MAP            STD_ON
/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/
typedef enum
{
    ETPU_IC_PRIORITY_DISABLE = 0x0,
    ETPU_IC_PRIORITY_LOW     = 0x1,
    ETPU_IC_PRIORITY_MIDDLE  = 0x2,
    ETPU_IC_PRIORITY_HIGH    = 0x3,
} eTPU_Priority_Types;

typedef enum
{
    ETPU_IC_MODE_CONT       = 0x0,
    ETPU_IC_MODE_SINGLE     = 0x1,
    ETPU_IC_MODE_LINK       = 0x2,
} eTPU_Mode_Types;

typedef enum
{
    ETPU_IC_TCR1            = 0x0,
    ETPU_IC_TCR2            = 0x1,
} eTPU_TimeBase_Types;

typedef struct
{
    VAR(eTPU_Priority_Types,  ICU_CONST) priority;
    VAR(eTPU_Mode_Types,      ICU_CONST) mode;
    VAR(eTPU_TimeBase_Types,  ICU_CONST) timebase;
} ICU_eTPU_HwConfig;

typedef struct
{
    /* ICU channel instance */
    CONST(Icu_IndexType,           ICU_CONST) IcuConfig_Instance;
    /* eTPU module. ref@eTPU_Module_Types eTPU_A,eTPU_B,eTPU_C */
    CONST(Icu_Module_Type,          ICU_CONST) IcuConfig_ModuleId;
    /* eTPU channel. 0~31. ref@ETPU_CHANNEL_x(x=0...31) */
    CONST(Icu_ChannelType,          ICU_CONST) IcuConfig_ChannelId;
    CONST(Icu_MeasurementModeType,  ICU_CONST) IcuConfig_ChannelMode;
    /* detect mode */
    CONST(Icu_ActivationType,       ICU_CONST) IcuChannel_DefaultStartEdge;
    CONST(Icu_NotifyType,           ICU_CONST) IcuChannel_Notification;
    CONST(Icu_NotifyType,           ICU_CONST) IcuChannel_TimestampNotification;
    CONST(Icu_SignalMeasurementPropertyType, ICU_CONST) IcuChannel_SignalMeasurementProperty;
    CONST(Icu_TimestampBufferType,  ICU_CONST) IcuChannel_TimestampBufferProperty;
    CONST(boolean,                  ICU_CONST) IcuChannel_WakeupCapability;
#if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)
    CONST(EcuM_WakeupSourceType,    ICU_CONST) IcuChannel_WakeupValue;
#endif
    /* TRUE: dma enable, FALSE: dma disable */
    CONST(boolean,                  ICU_CONST) IcuChannel_bDmaSupport;
    CONST(uint8,                    ICU_CONST) IcuChannel_DmaChannel;
    CONST(boolean,                  ICU_CONST) IcuChannel_bSignalMeasureWithoutInterrupt;
    CONST(ICU_eTPU_HwConfig,        ICU_CONST) *pIcuConfig_HwConfig;
} ICU_eTPU_ChannelConfig;

typedef struct ICU_eTPU_ConfigType
{
    /* Number of ICU etpu channels */
    CONST(Icu_ChannelType,          ICU_CONST) uChannelCount;
    /* Hardware dependent Channel configuration */
    CONST(ICU_eTPU_ChannelConfig,   ICU_CONST) *peTpuChannelConfig;
} ICU_eTPU_Config;

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
FUNC(Icu_ChannelType, ICU_CODE) Icu_eTpu_Wrapper_GetInstance \
( \
    VAR(uint8,  AUTOMATIC) u8Module, \
    VAR(uint8,  AUTOMATIC) u8Channel \
);

FUNC(void, ICU_CODE) Icu_eTpu_Wrapper_Init \
( \
    P2CONST(struct ICU_eTPU_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);

FUNC(void, ICU_CODE) Icu_eTpu_Wrapper_DeInit \
( \
    P2CONST(struct ICU_eTPU_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);

FUNC(void, ICU_CODE) eTpu_Channel_EnIrq \
(
    VAR(uint8, AUTOMATIC) u8Module, \
    VAR(uint8, AUTOMATIC) u8Channel \
);

FUNC(void, ICU_CODE) eTpu_Channel_DisIrq \
(
    VAR(uint8, AUTOMATIC) u8Module, \
    VAR(uint8, AUTOMATIC) u8Channel \
);

FUNC (void, ICU_CODE) Icu_eTpu_Wrapper_SetActivationCondition \
( \
    VAR(Icu_ChannelType,                 AUTOMATIC) nChannel, \
    VAR(Icu_ActivationType,              AUTOMATIC) eActivation, \
    VAR(Icu_MeasurementModeType,         AUTOMATIC) eMode, \
    P2CONST(struct ICU_eTPU_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);

FUNC (Icu_InputStateType, ICU_CODE) Icu_eTpu_Wrapper_GetInputState \
( \
    VAR(Icu_ChannelType,                 AUTOMATIC) nChannel, \
    P2CONST(struct ICU_eTPU_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);

FUNC (void, ICU_CODE) Icu_eTpu_Wrapper_EnableEdgeDetection \
( \
    VAR(Icu_ChannelType,                 AUTOMATIC) nChannel, \
    P2CONST(struct ICU_eTPU_ConfigType,  ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);

FUNC (void, ICU_CODE) Icu_eTpu_Wrapper_DisableEdgeDetection \
( \
    VAR(Icu_ChannelType,                 AUTOMATIC) nChannel, \
    P2CONST(struct ICU_eTPU_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
FUNC (void, ICU_CODE) Icu_eTpu_Wrapper_StartSignalMeasurement \
( \
    VAR(Icu_ChannelType,                 AUTOMATIC) nChannel, \
    VAR(uint32,                          AUTOMATIC) u32StartEdge, \
    VAR(uint16,                          AUTOMATIC) u16MeasProperty, \
    VAR(boolean,                         AUTOMATIC) bDmaSupport, \
    P2CONST(struct ICU_eTPU_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);

FUNC (void, ICU_CODE) Icu_eTpu_Wrapper_StopSignalMeasurement \
( \
    VAR(Icu_ChannelType,                 AUTOMATIC) nChannel, \
    P2CONST(struct ICU_eTPU_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);
#endif /* ICU_SIGNAL_MEASUREMENT_API */

FUNC (uint32, ICU_CODE) Icu_eTpu_Wrapper_GetStartAddress \
( \
    VAR(Icu_ChannelType,                 AUTOMATIC) nChannel, \
    P2CONST(struct ICU_eTPU_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);

#if (ICU_TIMESTAMP_API == STD_ON)
FUNC (void, ICU_CODE) Icu_eTpu_Wrapper_StartTimestamp \
( \
    VAR(Icu_ChannelType,                 AUTOMATIC) nChannel, \
    VAR(boolean,                         AUTOMATIC) bDmaSupport, \
    P2CONST(struct ICU_eTPU_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);

FUNC (void, ICU_CODE) Icu_eTpu_Wrapper_StopTimestamp \
( \
    VAR(Icu_ChannelType,                 AUTOMATIC) nChannel, \
    P2CONST(struct ICU_eTPU_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);
#endif /* ICU_TIMESTAMP_API */

#if (ICU_EDGE_COUNT_API == STD_ON)
FUNC (void, ICU_CODE) Icu_eTpu_Wrapper_ResetEdgeCount \
( \
    VAR(Icu_ChannelType,                 AUTOMATIC) nChannel, \
    P2CONST(struct ICU_eTPU_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);

FUNC (void, ICU_CODE) Icu_eTpu_Wrapper_EnableEdgeCount \
( \
    VAR(Icu_ChannelType,                 AUTOMATIC) nChannel, \
    P2CONST(struct ICU_eTPU_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);

FUNC (void, ICU_CODE) Icu_eTpu_Wrapper_DisableEdgeCount \
( \
    VAR(Icu_ChannelType,                 AUTOMATIC) nChannel, \
    P2CONST(struct ICU_eTPU_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);

FUNC (uint32, ICU_CODE) Icu_eTpu_Wrapper_GetEdgeNumbers \
( \
    VAR(Icu_ChannelType,                 AUTOMATIC) nChannel, \
    P2CONST(struct ICU_eTPU_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);
#endif /* ICU_EDGE_COUNT_API */

FUNC (boolean, ICU_CODE) Icu_eTpu_Wrapper_GetOverflow \
( \
    VAR(Icu_ChannelType,                 AUTOMATIC) nChannel, \
    P2CONST(struct ICU_eTPU_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);

FUNC (Icu_LevelType, ICU_CODE) Icu_eTpu_Wrapper_GetInputLevel \
( \
    VAR(Icu_ChannelType,                 AUTOMATIC) nChannel, \
    P2CONST(struct ICU_eTPU_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);

FUNC(Icu_ValueType, ICU_CODE) Icu_eTpu_Wrapper_GetTimeElapsed \
( \
    VAR(Icu_ChannelType,                 AUTOMATIC) nChannel, \
    P2CONST(struct ICU_eTPU_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);

#if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)
FUNC(EcuM_WakeupSourceType, ICU_CODE) Icu_eTpu_Wrapper_GetWakeupSource \
( \
    VAR(Icu_ChannelType,                 AUTOMATIC) nChannel, \
    P2CONST(struct ICU_eTPU_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);
#endif /* ICU_REPORT_WAKEUP_SOURCE */

FUNC(Icu_TimestampBufferType, ICU_CODE) Icu_eTpu_Wrapper_GetTimestampBufferType \
( \
    VAR(Icu_ChannelType,                 AUTOMATIC) nChannel, \
    P2CONST(struct ICU_eTPU_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);

FUNC (Icu_ValueType, ICU_CODE) Icu_eTpu_Wrapper_GetCaptureRegisterValue \
( \
    VAR(Icu_ChannelType,                AUTOMATIC) nChannel, \
    P2CONST(struct ICU_eTPU_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);

FUNC (void, ICU_CODE) Icu_eTpu_Wrapper_IrqConfig
(
    VAR(Icu_ChannelType,                 AUTOMATIC) nChannel, \
    P2CONST(struct ICU_eTPU_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr, \
    VAR(boolean,                 AUTOMATIC) IsEnable
);
#ifdef __cplusplus
}
#endif

#endif /* ICU_ETPU_WRAPPER_H */

#endif /*#RESOURCE_SUPPORT_ETPU*/

