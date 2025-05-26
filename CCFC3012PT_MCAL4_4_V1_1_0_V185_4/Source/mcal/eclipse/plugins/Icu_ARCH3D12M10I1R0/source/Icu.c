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
*   @file    Icu.c
*   @version 
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Icu MCAL driver.
*
*   @addtogroup Icu
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*====================================================================================================
                                        INCLUDE FILES
====================================================================================================*/
#include "Icu.h"
#include "Det.h"
#include "Icu_Cfg.h"
#include "Icu_Autosar_Wrapper.h"
#include "Icu_Irq.h"
/*====================================================================================================
                                SOURCE FILE VERSION INFORMATION
====================================================================================================*/
#define ICU_VENDOR_ID_C                 176
#define ICU_AR_REL_MAJOR_VER_C          4
#define ICU_AR_REL_MINOR_VER_C          4
#define ICU_AR_REL_REVISION_VER_C       0
#define ICU_SW_MAJOR_VER_C              1
#define ICU_SW_MINOR_VER_C              0
#define ICU_SW_PATCH_VER_C              1

/*====================================================================================================
                                        FILE VERSION CHECKS
====================================================================================================*/
#if (ICU_VENDOR_ID_C != ICU_VENDOR_ID_H)
    #error " NON-MATCHED DATA : ICU_VENDOR_ID_C "
#endif
#if (ICU_AR_REL_MAJOR_VER_C != ICU_MAJOR_VER_H)
    #error " NON-MATCHED DATA : ICU_AR_REL_MAJOR_VER_C "
#endif
#if (ICU_AR_REL_MINOR_VER_C != ICU_MINOR_VER_H)
    #error " NON-MATCHED DATA : ICU_AR_REL_MINOR_VER_C "
#endif
#if (ICU_AR_REL_REVISION_VER_C != ICU_REVISION_VER_H)
    #error " NON-MATCHED DATA : ICU_AR_REL_REVISION_VER_C "
#endif
#if (ICU_SW_MAJOR_VER_C != ICU_SW_MAJOR_VER_H)
    #error " NON-MATCHED DATA : ICU_SW_MAJOR_VER_C "
#endif
#if (ICU_SW_MINOR_VER_C != ICU_SW_MINOR_VER_H)
    #error " NON-MATCHED DATA : ICU_SW_MINOR_VER_C "
#endif
#if (ICU_SW_PATCH_VER_C != ICU_SW_PATCH_VER_H)
    #error " NON-MATCHED DATA : ICU_SW_PATCH_VER_C "
#endif

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                      EXTERN VARIABLES
==================================================================================================*/
/**
* include the Icu configuration structure of precompile mode
*/
#if(ICU_CONFIG_VARIANT == ICU_VARIANT_PRECOMPILE)
extern CONST(Icu_ConfigType, ICU_CONST) Icu_Cfg;
#endif

#define ICU_CORE_Z70_ID_MASK                        (0x01U)
#define ICU_CORE_Z71_ID_MASK                        (0x02U)
#define ICU_CORE_Z42_ID_MASK                        (0x04U)
/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/
/**
* Saves the state of Icu module
*/
static VAR(Icu_ModuleState_Type, ICU_VAR) eIcu_ModuleState[ICU_CORE_NUM] = {ICU_STATE_UNINIT};

/**
* Pointer initialized during init with the address of the received configuration structure.
*/
P2CONST(Icu_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_CfgPtr[ICU_CORE_NUM] = {NULL_PTR};

/**
* Stores configuration of ICU Channels
*/
VAR(Icu_ChannelInfoType, AUTOMATIC) sIcu_ChannelInfo[ICU_CORE_NUM][ICU_MAX_CHANNEL];

/**
* Saves the current Icu mode
*/
VAR(Icu_ModeType, ICU_VAR) eIcu_CurrentMode[ICU_CORE_NUM];

#if (ICU_MULTI_CORE_SUPPORT == STD_ON)
#define ICU_START_SEC_VAR_SHARED_INIT
/**
* Flag to Channel init
*/
#include "Icu_MemMap.h"
volatile VAR(uint8, ICU_VAR) sIcu_u8Hw2LogicChannelMap[ICU_CORE_NUM][ICU_MAX_CHANNEL] = {{0U}};
#define ICU_STOP_SEC_VAR_SHARED_INIT
#include "Icu_MemMap.h"
#endif

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
#define ICU_START_SEC_CODE
#include "Icu_MemMap.h"

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_Init_Verify \
( \
    P2CONST(Icu_ConfigType, AUTOMATIC, ICU_APPL_CONST) sIcu_ConfigPtr \
);

LOCAL_INLINE FUNC(void, ICU_CODE) Icu_InitChannelState \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelIndex \
);

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_Deinit_Verify(void);

LOCAL_INLINE FUNC(void, ICU_CODE) Icu_DenitChannelState \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelIndex \
);

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_Setmode_Verify \
( \
    VAR(Icu_ModeType,AUTOMATIC) eIcu_Mode \
);

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_DisableWakeup_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
);

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_EnableWakeup_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
);

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_SetActivationCondition_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel, \
    VAR(Icu_ActivationType, AUTOMATIC) eIcu_Activation \
);

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_DisableNotification_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
);

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_EnableNotification_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
);

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_GetInputState_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
);

#if (ICU_GETINPUTSTATE_API == STD_ON)
LOCAL_INLINE FUNC(Icu_InputStateType, ICU_CODE) Icu_GetIcuInputState \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
);
#endif

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_StartTimestamp_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel, \
    P2CONST(Icu_ValueType, AUTOMATIC,ICU_APPL_CONST) u32Icu_BufferPtr, \
    VAR(uint16, AUTOMATIC) u16_IcuBufferSize, \
    VAR(uint16, AUTOMATIC) u16Icu_NotifyInterval \
);

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_StopTimestamp_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
);

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_GetTimestampIndex_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
);

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_ResetEdgeCount_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
);

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_EnableEdgeCount_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
);

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_DisableEdgeCount_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
);

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_GetEdgeNumbers_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
);

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_EnableEdgeDetection_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
);

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_DisableEdgeDetection_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
);

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_StartSignalMeasurement_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
);

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_StopSignalMeasurement_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
);

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_GetTimeElapsed_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
);

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_GetDutyCycleValues_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel, \
	P2CONST(Icu_DutyCycleType, AUTOMATIC, ICU_APPL_CONST) DutyCycleValues
);

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_CheckWakeup_Verify( void );

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_GetInputLevel_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
);

#if (ICU_CAPTURERGISTER_API == STD_ON)
LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_GetCaptureRegisterValue_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
);
#endif

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_CheckParamVersionInfo \
( \
    P2CONST(Std_VersionInfoType, AUTOMATIC, ICU_APPL_CONST) sIcu_Versioninfo \
);
#if (ICU_OVERFLOW_NOTIFICATION_API == STD_ON)
LOCAL_INLINE FUNC(boolean, ICU_CODE) Icu_GetOverflow \
( \
    VAR(Icu_ChannelType, AUTOMATIC) Channel, \
    VAR(uint8, AUTOMATIC) u8ServiceId, \
    VAR(uint8, AUTOMATIC) u8Error \
);
#endif
/*==================================================================================================
*                                    FUNCTION NOT AUTOSAR
==================================================================================================*/
FUNC(void, ICU_CODE) Icu_SetChannelState \
( \
    VAR(Icu_ChannelType,AUTOMATIC) u16Icu_Channel, \
    VAR(Icu_ChannelState_Type,AUTOMATIC) u32Icu_StateMask \
)
{
    SchM_Enter_ICU_CRITICAL_AREA_03();
    sIcu_ChannelInfo[GetCoreID()][u16Icu_Channel].u32Icu_ChannelState |= u32Icu_StateMask;/* GetCoreID */
    SchM_Exit_ICU_CRITICAL_AREA_03();
}

FUNC(void,ICU_CODE) Icu_ClearChannelState \
( \
    VAR(Icu_ChannelType,AUTOMATIC) u16Icu_Channel, \
    VAR(Icu_ChannelState_Type,AUTOMATIC) u32Icu_StateMask \
)
{
    SchM_Enter_ICU_CRITICAL_AREA_04();
    sIcu_ChannelInfo[GetCoreID()][u16Icu_Channel].u32Icu_ChannelState &= ((Icu_ChannelState_Type)(~u32Icu_StateMask));/* GetCoreID */
    SchM_Exit_ICU_CRITICAL_AREA_04();
}

FUNC(Icu_ChannelState_Type,ICU_CODE) Icu_GetChannelState \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel, \
    VAR(Icu_ChannelState_Type,AUTOMATIC) u32Icu_StateMask \
)
{
    VAR(uint32,AUTOMATIC) u8Icu_CheckFlag = 0U;

    u8Icu_CheckFlag = sIcu_ChannelInfo[GetCoreID()][u16Icu_Channel].u32Icu_ChannelState & u32Icu_StateMask;/* GetCoreID */

    return u8Icu_CheckFlag;
}

FUNC(Icu_LevelType,ICU_CODE) Icu_GetInputLevel \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel
)
{
    VAR(Icu_LevelType, ICU_CODE) returnVal = ICU_LEVEL_LOW;

    VAR(Std_ReturnType,AUTOMATIC) validchannel = Icu_GetInputLevel_Verify(u16Icu_Channel);

    if ((Std_ReturnType)E_OK == validchannel)
    {
        returnVal = Icu_Autosar_Wrapper_GetInputLevel(u16Icu_Channel, sIcu_CfgPtr[GetCoreID()]);/* GetCoreID */
    }

    return returnVal;
}

#if (ICU_CAPTURERGISTER_API == STD_ON)
FUNC(Icu_ValueType, ICU_CODE) Icu_GetCaptureRegisterValue \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
)
{
    VAR(Icu_ValueType, AUTOMATIC) tempValue = (Icu_ValueType)0U;

    VAR(Std_ReturnType,AUTOMATIC) validchannel = Icu_GetCaptureRegisterValue_Verify(u16Icu_Channel);

    if ((Std_ReturnType)E_OK == validchannel)
    {
        tempValue = (Icu_ValueType)Icu_Autosar_Wrapper_GetCaptureRegisterValue(u16Icu_Channel, \
            sIcu_CfgPtr[GetCoreID()]);
    }

    return tempValue;
}
#endif

#if (ICU_DEV_ERROR_DETECT == STD_ON)
LOCAL_INLINE FUNC(void, ICU_CODE) Icu_ReportError \
( \
    VAR(uint8, AUTOMATIC) Icu_ApiId, \
    VAR(uint8, AUTOMATIC) Icu_ErrorId \
)
{
    (void)Det_ReportError((uint16)ICU_MODULE_ID, 0U, (uint8)Icu_ApiId, (uint8)Icu_ErrorId);
}
#endif

#if(ICU_MULTI_CORE_SUPPORT == STD_ON)
LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_CoreVerify \
(
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel, \
    VAR(uint8, AUTOMATIC) Icu_ApiId \
)
{
    VAR(uint32, AUTOMATIC) u32Icu_CurrentCoreId = Icu_GetCoreID();
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_RetValue = (Std_ReturnType)E_NOT_OK;
    VAR(uint32, AUTOMATCI) Temp = u32Icu_CurrentCoreId & sIcu_CfgPtr[GetCoreID()]->Icu_CoreMap[u16Icu_Channel].nCoreId;
    if(Temp == 0U)
    {
        #if (ICU_DEV_ERROR_DETECT == STD_ON)
        (void)Icu_ReportError(Icu_ApiId, ICU_E_PARAM_CHANNEL);
		#else
        (void)Icu_ApiId;
        #endif
    }
    else
    {
        u8Icu_RetValue = (Std_ReturnType)E_OK;
    }

    return u8Icu_RetValue;
}
#endif
/*==================================================================================================
*                                    FUNCTION AUTOSAR
==================================================================================================*/
/**************************************************************************************************
**  Service Name     : Icu_Init
**                                                                                                  
**  Description      : This function initializes the driver.
**                                                                                                  
**  Service ID       : 0x00
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Non Reentrant
**                                                                                                  
**  Parameters (in)  : ConfigPtr: Pointer to a selected configuration structure
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : None
**                                                                                                  
****************************************************************************************************/
FUNC(void, ICU_CODE) Icu_Init(P2CONST(Icu_ConfigType, AUTOMATIC, ICU_APPL_CONST) ConfigPtr)
{
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel = 0U; 
    VAR(Std_ReturnType,  AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Gtm_ChNum = 0U;
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_eMios_ChNum = 0U;
#ifdef RESOURCE_SUPPORT_ETPU
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_eTpu_ChNum = 0U;
#endif /*#RESOURCE_SUPPORT_ETPU*/
#if defined(CCFC3012PT)
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Wkpu_ChNum = 0U;
#endif
    VAR(Icu_IndexType,  AUTOMATIC) u16Icu_Instance;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    u8Icu_VerifyRetVal = Icu_Init_Verify(ConfigPtr);
#if(ICU_CONFIG_VARIANT == ICU_VARIANT_POSTBUILD)
    sIcu_CfgPtr[u8Icu_CoreId] = ConfigPtr;
#else
    sIcu_CfgPtr[u8Icu_CoreId] = &Icu_Cfg;
#endif

    if((Std_ReturnType)E_OK == u8Icu_VerifyRetVal)
    {
        Icu_Autosar_Wrapper_Init(sIcu_CfgPtr[u8Icu_CoreId]);

        if (sIcu_CfgPtr[u8Icu_CoreId]->Icu_GtmConfig != NULL_PTR)
        {
            u16Icu_Gtm_ChNum    = sIcu_CfgPtr[u8Icu_CoreId]->Icu_GtmConfig->uChannelCount;
        }
        if (sIcu_CfgPtr[u8Icu_CoreId]->Icu_eMoisConfig != NULL_PTR)
        {
            u16Icu_eMios_ChNum  = sIcu_CfgPtr[u8Icu_CoreId]->Icu_eMoisConfig->uChannelCount;
        }
#ifdef RESOURCE_SUPPORT_ETPU
        if (sIcu_CfgPtr[u8Icu_CoreId]->Icu_eTpuConfig != NULL_PTR)
        {
            u16Icu_eTpu_ChNum   = sIcu_CfgPtr[u8Icu_CoreId]->Icu_eTpuConfig->uChannelCount;
        }
#endif /*#RESOURCE_SUPPORT_ETPU*/
#if defined(CCFC3012PT)
        if (sIcu_CfgPtr[u8Icu_CoreId]->Icu_WkpuConfig != NULL_PTR)
        {
            u16Icu_Wkpu_ChNum   = sIcu_CfgPtr[u8Icu_CoreId]->Icu_WkpuConfig->uChannelCount;
        }
#endif

        /* GTM infomation initilazition */
        for (u16Icu_Channel = 0U; u16Icu_Channel < u16Icu_Gtm_ChNum; u16Icu_Channel++)
        {
            u16Icu_Instance = sIcu_CfgPtr[u8Icu_CoreId]->Icu_GtmConfig->pGtmChannelConfig[u16Icu_Channel].IcuConfig_Instance;

            Icu_ClearChannelState(u16Icu_Instance, ICU_CHANNEL_STATE_NOTIFICATION);
            Icu_ClearChannelState(u16Icu_Instance, ICU_CHANNEL_STATE_WKUP);
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].u16Icu_Instance = u16Icu_Instance;
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuConfig_ChannelMode = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_GtmConfig->pGtmChannelConfig[u16Icu_Channel].IcuConfig_ChannelMode;
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_Notification = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_GtmConfig->pGtmChannelConfig[u16Icu_Channel].IcuChannel_Notification;
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_TimestampNotification = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_GtmConfig->pGtmChannelConfig[u16Icu_Channel].IcuChannel_TimestampNotification;
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_WakeupCapability = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_GtmConfig->pGtmChannelConfig[u16Icu_Channel].IcuChannel_WakeupCapability;
#if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_WakeupValue = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_GtmConfig->pGtmChannelConfig[u16Icu_Channel].IcuChannel_WakeupValue;
#endif
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_SignalMeasurementProperty = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_GtmConfig->pGtmChannelConfig[u16Icu_Channel].IcuChannel_SignalMeasurementProperty;
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_bDmaSupport = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_GtmConfig->pGtmChannelConfig[u16Icu_Channel].IcuChannel_bDmaSupport;
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_DmaChannel = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_GtmConfig->pGtmChannelConfig[u16Icu_Channel].IcuChannel_DmaChannel;
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_TimestampBufferProperty = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_GtmConfig->pGtmChannelConfig[u16Icu_Channel].IcuChannel_TimestampBufferProperty;

            Icu_InitChannelState(u16Icu_Instance);
        }

        /* eMIOS infomation initilazition */
        for (u16Icu_Channel = 0U; u16Icu_Channel < u16Icu_eMios_ChNum; u16Icu_Channel++)
        {
            u16Icu_Instance = sIcu_CfgPtr[u8Icu_CoreId]->Icu_eMoisConfig->peMiosChannelConfig[u16Icu_Channel].IcuConfig_Instance;

            Icu_ClearChannelState(u16Icu_Instance, ICU_CHANNEL_STATE_NOTIFICATION);
            Icu_ClearChannelState(u16Icu_Instance, ICU_CHANNEL_STATE_WKUP);
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].u16Icu_Instance = u16Icu_Instance;
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuConfig_ChannelMode = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_eMoisConfig->peMiosChannelConfig[u16Icu_Channel].IcuConfig_ChannelMode;
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_Notification = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_eMoisConfig->peMiosChannelConfig[u16Icu_Channel].IcuChannel_Notification;
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_TimestampNotification = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_eMoisConfig->peMiosChannelConfig[u16Icu_Channel].IcuChannel_TimestampNotification;
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_WakeupCapability = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_eMoisConfig->peMiosChannelConfig[u16Icu_Channel].IcuChannel_WakeupCapability;
#if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_WakeupValue = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_eMoisConfig->peMiosChannelConfig[u16Icu_Channel].IcuChannel_WakeupValue;
#endif
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_SignalMeasurementProperty = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_eMoisConfig->peMiosChannelConfig[u16Icu_Channel].IcuChannel_SignalMeasurementProperty;
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_bDmaSupport = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_eMoisConfig->peMiosChannelConfig[u16Icu_Channel].IcuChannel_bDmaSupport;
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_DmaChannel = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_eMoisConfig->peMiosChannelConfig[u16Icu_Channel].IcuChannel_DmaChannel;
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_TimestampBufferProperty = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_eMoisConfig->peMiosChannelConfig[u16Icu_Channel].IcuChannel_TimestampBufferProperty;

            Icu_InitChannelState(u16Icu_Instance);
        }
#ifdef RESOURCE_SUPPORT_ETPU
        /* eTPU infomation initilazition */
        for (u16Icu_Channel = 0U; u16Icu_Channel < u16Icu_eTpu_ChNum; u16Icu_Channel++)
        {
            u16Icu_Instance = sIcu_CfgPtr[u8Icu_CoreId]->Icu_eTpuConfig->peTpuChannelConfig[u16Icu_Channel].IcuConfig_Instance;

            Icu_ClearChannelState(u16Icu_Instance, ICU_CHANNEL_STATE_NOTIFICATION);
            Icu_ClearChannelState(u16Icu_Instance, ICU_CHANNEL_STATE_WKUP);
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].u16Icu_Instance = u16Icu_Instance;
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuConfig_ChannelMode = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_eTpuConfig->peTpuChannelConfig[u16Icu_Channel].IcuConfig_ChannelMode;
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_Notification = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_eTpuConfig->peTpuChannelConfig[u16Icu_Channel].IcuChannel_Notification;
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_TimestampNotification = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_eTpuConfig->peTpuChannelConfig[u16Icu_Channel].IcuChannel_TimestampNotification;
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_WakeupCapability = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_eTpuConfig->peTpuChannelConfig[u16Icu_Channel].IcuChannel_WakeupCapability;
#if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_WakeupValue = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_eTpuConfig->peTpuChannelConfig[u16Icu_Channel].IcuChannel_WakeupValue;
#endif
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_SignalMeasurementProperty = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_eTpuConfig->peTpuChannelConfig[u16Icu_Channel].IcuChannel_SignalMeasurementProperty;
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_bDmaSupport = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_eTpuConfig->peTpuChannelConfig[u16Icu_Channel].IcuChannel_bDmaSupport;
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_DmaChannel = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_eTpuConfig->peTpuChannelConfig[u16Icu_Channel].IcuChannel_DmaChannel;
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_TimestampBufferProperty = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_eTpuConfig->peTpuChannelConfig[u16Icu_Channel].IcuChannel_TimestampBufferProperty;

            Icu_InitChannelState(u16Icu_Instance);
        }
#endif /*#RESOURCE_SUPPORT_ETPU*/

#if defined(CCFC3012PT)
        /* Wkpu infomation initilazition */
        for (u16Icu_Channel = 0U; u16Icu_Channel < u16Icu_Wkpu_ChNum; u16Icu_Channel++)
        {
            u16Icu_Instance = sIcu_CfgPtr[u8Icu_CoreId]->Icu_WkpuConfig->pWkpuChannelConfig[u16Icu_Channel].IcuConfig_Instance;

            Icu_ClearChannelState(u16Icu_Instance, ICU_CHANNEL_STATE_NOTIFICATION);
            Icu_ClearChannelState(u16Icu_Instance, ICU_CHANNEL_STATE_WKUP);
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].u16Icu_Instance = u16Icu_Instance;
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuConfig_ChannelMode = ICU_MODE_SIGNAL_EDGE_DETECT;
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_Notification = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_WkpuConfig->pWkpuChannelConfig[u16Icu_Channel].IcuChannel_Notification;

            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_WakeupCapability = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_WkpuConfig->pWkpuChannelConfig[u16Icu_Channel].IcuChannel_WakeupCapability;
#if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Instance].sIcu_ChannelConfig.IcuChannel_WakeupValue = \
                sIcu_CfgPtr[u8Icu_CoreId]->Icu_WkpuConfig->pWkpuChannelConfig[u16Icu_Channel].IcuChannel_WakeupValue;
#endif
            Icu_InitChannelState(u16Icu_Instance);
        }
#endif
        eIcu_CurrentMode[u8Icu_CoreId] = ICU_MODE_NORMAL;
        eIcu_ModuleState[u8Icu_CoreId] = ICU_STATE_IDLE;
    }
}

#if(ICU_DEINIT_API == STD_ON)
/**************************************************************************************************
**  Service Name     : Icu_DeInit
**                                                                                                  
**  Description      : This function de-initializes the ICU module.
**                                                                                                  
**  Service ID       : 0x01
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Non Reentrant
**                                                                                                  
**  Parameters (in)  : None
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : None
**                                                                                                  
****************************************************************************************************/
FUNC(void, ICU_CODE) Icu_DeInit(void)
{
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelIndex = 0U;
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    u8Icu_VerifyRetVal = Icu_Deinit_Verify();
    if((Std_ReturnType)E_OK == u8Icu_VerifyRetVal)
    {
        Icu_Autosar_Wrapper_DeInit(sIcu_CfgPtr[u8Icu_CoreId]);
        for(u16Icu_ChannelIndex = 0;u16Icu_ChannelIndex < sIcu_CfgPtr[u8Icu_CoreId]->Icu_NumChannels;u16Icu_ChannelIndex++)
        {

            Icu_DenitChannelState(u16Icu_ChannelIndex);
        }

        sIcu_CfgPtr[u8Icu_CoreId] = NULL_PTR;
        eIcu_CurrentMode[u8Icu_CoreId] = ICU_MODE_NORMAL;
        eIcu_ModuleState[u8Icu_CoreId] = ICU_STATE_UNINIT;

    }
}
#endif

#if (ICU_SETMODE_API == STD_ON)
/**************************************************************************************************
**  Service Name     : Icu_SetMode
**                                                                                                  
**  Description      : This function sets the ICU mode.
**                                                                                                  
**  Service ID       : 0x02
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Non Reentrant
**                                                                                                  
**  Parameters (in)  : Mode: ICU_MODE_NORMAL: Normal operation, all used interrupts are enabled
**                              according to the notification requests.
**                           ICU_MODE_SLEEP: Reduced power mode. In sleep mode only those
**                              notifications are available which are configured as wakeup capable.
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : None
**                                                                                                  
****************************************************************************************************/
FUNC(void,ICU_CODE) Icu_SetMode(VAR(Icu_ModeType,AUTOMATIC) Mode)
{
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelIndex = 0U;
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    u8Icu_VerifyRetVal = Icu_Setmode_Verify(Mode);
    if ((Std_ReturnType)E_OK == u8Icu_VerifyRetVal)
    {

        SchM_Enter_ICU_EXCLUSIVE_AREA_00();
		if(Mode == ICU_MODE_SLEEP)
		{
			for(u16Icu_ChannelIndex = 0;u16Icu_ChannelIndex < sIcu_CfgPtr[u8Icu_CoreId]->Icu_NumChannels;u16Icu_ChannelIndex++)
			{
				if(Icu_GetChannelState(u16Icu_ChannelIndex,ICU_CHANNEL_STATE_WKUP) != ICU_CHANNEL_STATE_WKUP)
				{
                    /* Disable */
					Icu_Autosar_Wrapper_IrqConfig(u16Icu_ChannelIndex, sIcu_CfgPtr[u8Icu_CoreId], FALSE);
				}
                else
                {
                    /* Enable */
                    Icu_Autosar_Wrapper_IrqConfig(u16Icu_ChannelIndex, sIcu_CfgPtr[u8Icu_CoreId], TRUE);
                    Icu_SetChannelState(u16Icu_ChannelIndex,ICU_CHANNEL_STATE_RUNNING);
                }
			}
		}
		else /* normal mode */
		{
			for(u16Icu_ChannelIndex = 0;u16Icu_ChannelIndex < sIcu_CfgPtr[u8Icu_CoreId]->Icu_NumChannels;u16Icu_ChannelIndex++)
			{
				if(Icu_GetChannelState(u16Icu_ChannelIndex,ICU_CHANNEL_STATE_WKUP) == ICU_CHANNEL_STATE_WKUP)
				{
					Icu_Autosar_Wrapper_IrqConfig(u16Icu_ChannelIndex, sIcu_CfgPtr[u8Icu_CoreId], FALSE);
					Icu_ClearChannelState(u16Icu_ChannelIndex,ICU_CHANNEL_STATE_RUNNING);
				}
				else if (Icu_GetChannelState(u16Icu_ChannelIndex,ICU_CHANNEL_STATE_RUNNING) == ICU_CHANNEL_STATE_RUNNING)
				{
					Icu_Autosar_Wrapper_IrqConfig(u16Icu_ChannelIndex, sIcu_CfgPtr[u8Icu_CoreId], TRUE);
				}
				else
				{
					// Do nothing
				}
			}
		}
		eIcu_CurrentMode[u8Icu_CoreId] = Mode;

        SchM_Exit_ICU_EXCLUSIVE_AREA_00();
    }
    eIcu_ModuleState[u8Icu_CoreId] = ICU_STATE_IDLE;
}
#endif /* (ICU_SETMODE_API == STD_ON) */

#if (ICU_DISABLEWAKEUP_API == STD_ON)
/**************************************************************************************************
**  Service Name     : Icu_DisableWakeup
**                                                                                                  
**  Description      : This function disables the wakeup capability of a single ICU channel.
**                                                                                                  
**  Service ID       : 0x03
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : Channel: Numeric identifier of the ICU channel.
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : None
**                                                                                                  
****************************************************************************************************/
FUNC(void, ICU_CODE) Icu_DisableWakeup(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;

    u8Icu_VerifyRetVal = Icu_DisableWakeup_Verify(Channel);
    if((Std_ReturnType)E_OK == u8Icu_VerifyRetVal)
    {
        Icu_ClearChannelState(Channel, ICU_CHANNEL_STATE_WKUP);
    }
}
#endif

#if (ICU_ENABLEWAKEUP_API == STD_ON)
/**************************************************************************************************
**  Service Name     : Icu_EnableWakeup
**                                                                                                  
**  Description      : This function (re-)enables the wakeup capability of the given ICU channel.
**                                                                                                  
**  Service ID       : 0x04
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : Channel: Numeric identifier of the ICU channel.
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : None
**                                                                                                  
****************************************************************************************************/
FUNC(void,ICU_CODE) Icu_EnableWakeup(VAR(Icu_ChannelType,AUTOMATIC) Channel)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;

    u8Icu_VerifyRetVal = Icu_EnableWakeup_Verify(Channel); 
    if ((Std_ReturnType)E_OK == u8Icu_VerifyRetVal)
    {
        Icu_SetChannelState(Channel, ICU_CHANNEL_STATE_WKUP);
    }
}
#endif

/**************************************************************************************************
**  Service Name     : Icu_SetActivationCondition
**                                                                                                  
**  Description      : This function sets the activation-edge for the given channel.
**                                                                                                  
**  Service ID       : 0x05
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : Channel: Numeric identifier of the ICU channel.
**                     Activation: Type of activation (if supported by hardware)
**                                 ICU_RISING_EDGE
**                                 ICU_FALLING_EDGE
**                                 ICU_BOTH_EDGES
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : None
**                                                                                                  
****************************************************************************************************/
FUNC(void, ICU_CODE) Icu_SetActivationCondition \
( \
    VAR(Icu_ChannelType, AUTOMATIC) Channel, \
    VAR(Icu_ActivationType, AUTOMATIC) Activation \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    u8Icu_VerifyRetVal = Icu_SetActivationCondition_Verify(Channel,Activation);
    if((Std_ReturnType)E_OK == u8Icu_VerifyRetVal)
    {
        Icu_ClearChannelState(Channel, ICU_CHANNEL_STATE_IDLE);
        Icu_Autosar_Wrapper_SetActivationCondition
        ( \
            Channel, \
            Activation,\
            sIcu_ChannelInfo[u8Icu_CoreId][Channel].sIcu_ChannelConfig.IcuConfig_ChannelMode, \
            sIcu_CfgPtr[u8Icu_CoreId] \
        );
    }
}

/**************************************************************************************************
**  Service Name     : Icu_DisableNotification
**                                                                                                  
**  Description      : This function disables the notification of a channel.
**                                                                                                  
**  Service ID       : 0x06
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : Channel: Numeric identifier of the ICU channel.
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : None
**                                                                                                  
****************************************************************************************************/
FUNC(void, ICU_CODE) Icu_DisableNotification(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;

    u8Icu_VerifyRetVal = Icu_DisableNotification_Verify(Channel);
    if((Std_ReturnType)E_OK == u8Icu_VerifyRetVal)
    {
        Icu_ClearChannelState(Channel, ICU_CHANNEL_STATE_NOTIFICATION);
    }
}

/**************************************************************************************************
**  Service Name     : Icu_EnableNotification
**                                                                                                  
**  Description      : This function enables the notification on the given channel.
**                                                                                                  
**  Service ID       : 0x07
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : Channel: Numeric identifier of the ICU channel.
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : None
**                                                                                                  
****************************************************************************************************/
FUNC(void, ICU_CODE) Icu_EnableNotification(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;

    u8Icu_VerifyRetVal = Icu_EnableNotification_Verify(Channel);
    if((Std_ReturnType)E_OK == u8Icu_VerifyRetVal)
    {
        Icu_SetChannelState(Channel, ICU_CHANNEL_STATE_NOTIFICATION);
    }
}

#if (ICU_GETINPUTSTATE_API == STD_ON)
/**************************************************************************************************
**  Service Name     : Icu_GetInputState
**                                                                                                  
**  Description      : This function returns the status of the ICU input.
**                                                                                                  
**  Service ID       : 0x08
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : Channel: Numeric identifier of the ICU channel.
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : Icu_InputStateType:  ICU_ACTIVE, ICU_IDLE
**                                                                                                  
****************************************************************************************************/
FUNC(Icu_InputStateType, ICU_CODE) Icu_GetInputState(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    VAR(Icu_InputStateType,AUTOMATIC) eIcu_RetState = ICU_IDLE;
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;

    u8Icu_VerifyRetVal = Icu_GetInputState_Verify(Channel);
    if((Std_ReturnType)E_OK == u8Icu_VerifyRetVal)
    {
        eIcu_RetState = Icu_GetIcuInputState(Channel);
    }

    return eIcu_RetState;
}
#endif

#if (ICU_STARTTIMESTAMP_API == STD_ON)
/**************************************************************************************************
**  Service Name     : Icu_StartTimestamp
**                                                                                                  
**  Description      : This function starts the capturing of timer values on the edges.
**                                                                                                  
**  Service ID       : 0x09
**                                                                                                  
**  Sync/Async       : Asynchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : Channel: Numeric identifier of the ICU channel.
**                     BufferSize: Size of the external buffer (number of entries)
**                     NotifyInterval: Notification interval (number of events)
**                                                                                                  
**  Parameters (out) : BufferPtr: Pointer to the buffer-array where the timestamp values shall be
**                     placed
**                                                                                                  
**  Return value     : None
**                                                                                                  
****************************************************************************************************/
FUNC(void, ICU_CODE) Icu_StartTimestamp \
( \
    VAR(Icu_ChannelType, AUTOMATIC) Channel, \
    P2VAR(Icu_ValueType, AUTOMATIC, ICU_APPL_DATA) BufferPtr, \
    VAR(uint16, AUTOMATIC) BufferSize, \
    VAR(uint16, AUTOMATIC) NotifyInterval \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(boolean,        AUTOMATIC) bDmaSupport = (boolean)FALSE;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();
#ifdef ICU_TIMESTAMP_USES_DMA
#if (ICU_TIMESTAMP_USES_DMA == STD_ON)
    VAR(Std_ReturnType, AUTOMATIC) returnResult = (Std_ReturnType)E_NOT_OK;
#endif
#endif
    u8Icu_VerifyRetVal = Icu_StartTimestamp_Verify(Channel, BufferPtr, BufferSize, NotifyInterval);
    if ((Std_ReturnType)E_OK == u8Icu_VerifyRetVal)
    {
        Icu_SetChannelState(Channel, ICU_CHANNEL_STATE_RUNNING);
        SchM_Enter_ICU_EXCLUSIVE_AREA_01();
        {
            sIcu_ChannelInfo[u8Icu_CoreId][Channel].u32Icu_ChannelBuffer = BufferPtr;
            sIcu_ChannelInfo[u8Icu_CoreId][Channel].u32Icu_ChannelBufferSize = BufferSize;
            sIcu_ChannelInfo[u8Icu_CoreId][Channel].u32Icu_ChannelBufferNotify = NotifyInterval;
            sIcu_ChannelInfo[u8Icu_CoreId][Channel].u32Icu_ChannelBufferNotifyCount = 0U;
            sIcu_ChannelInfo[u8Icu_CoreId][Channel].u32Icu_ChannelBufferIndex = 0U;
        }
        SchM_Exit_ICU_EXCLUSIVE_AREA_01();
        Icu_ClearChannelState(Channel, ICU_CHANNEL_STATE_OVERFLOW);

#ifdef ICU_TIMESTAMP_USES_DMA
#if (ICU_TIMESTAMP_USES_DMA == STD_ON)
        /* initialize dma information */
        if ((sIcu_ChannelInfo[u8Icu_CoreId][Channel].sIcu_ChannelConfig.IcuChannel_bDmaSupport == (boolean)TRUE) && \
            (sIcu_ChannelInfo[u8Icu_CoreId][Channel].sIcu_ChannelConfig.IcuChannel_DmaChannel != ICU_INVALID_DMA_CHANNEL))
        {
            returnResult = Icu_Autosar_Wrapper_StartTimestampDMA(Channel, sIcu_CfgPtr[u8Icu_CoreId]);
            if (returnResult == (Std_ReturnType)E_OK)
            {
                /* Enable notification */
                EDMA_SetChnDisRequestsOnTransferComplete \
                ( \
                    sIcu_ChannelInfo[u8Icu_CoreId][Channel].sIcu_ChannelConfig.IcuChannel_DmaChannel, \
                    (boolean)TRUE \
                );
                /* Enable complete interrupt */
                EDMA_SetInterruptConfig \
                ( \
                    sIcu_ChannelInfo[u8Icu_CoreId][Channel].sIcu_ChannelConfig.IcuChannel_DmaChannel, \
                    EDMA_CHN_ENABLE_MAJOR_LOOP_DONE_INT, \
                    (boolean)TRUE \
                );
                /* Setup callback */
                (void)EDMA_SetUpCallback \
                ( \
                    sIcu_ChannelInfo[u8Icu_CoreId][Channel].sIcu_ChannelConfig.IcuChannel_DmaChannel, \
                    *(&ICU_TimeStamp_Callback_From_DMA), \
                    &sIcu_ChannelInfo[u8Icu_CoreId][Channel].u16Icu_Instance \
                );
                /* enable dma mode */
                bDmaSupport = (boolean)TRUE;
                /* Start DMA */
                (void)EDMA_SetChannelRequest \
                ( \
                    sIcu_ChannelInfo[u8Icu_CoreId][Channel].sIcu_ChannelConfig.IcuChannel_DmaChannel \
                );
            }
        }
#endif
#endif
        Icu_Autosar_Wrapper_StartTimestamp(Channel, bDmaSupport, sIcu_CfgPtr[u8Icu_CoreId]);
#if (ICU_MULTI_CORE == STD_ON)
        Icu_Autosar_Wrapper_SetMultiCoreIrqEnableState(Channel, 1);
#endif
    }
}
#endif

#if (ICU_STOPTIMESTAMP_API == STD_ON)
/**************************************************************************************************
**  Service Name     : Icu_StopTimestamp
**                                                                                                  
**  Description      : This function stops the timestamp measurement of the given channel.
**                                                                                                  
**  Service ID       : 0x0a
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : Channel: Numeric identifier of the ICU channel.
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : None
**                                                                                                  
****************************************************************************************************/
FUNC(void, ICU_CODE) Icu_StopTimestamp(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    u8Icu_VerifyRetVal = Icu_StopTimestamp_Verify(Channel);
    if ((Std_ReturnType)E_OK == u8Icu_VerifyRetVal)
    {
#ifdef ICU_TIMESTAMP_USES_DMA
#if (ICU_TIMESTAMP_USES_DMA == STD_ON)
        /* disable dma request */
        if ((sIcu_ChannelInfo[u8Icu_CoreId][Channel].sIcu_ChannelConfig.IcuChannel_bDmaSupport == (boolean)TRUE) && \
            (sIcu_ChannelInfo[u8Icu_CoreId][Channel].sIcu_ChannelConfig.IcuChannel_DmaChannel != ICU_INVALID_DMA_CHANNEL))
        {
        	(void)EDMA_ClearChannelRequest(sIcu_ChannelInfo[u8Icu_CoreId][Channel].sIcu_ChannelConfig.IcuChannel_DmaChannel);
        }
#endif
#endif /* ICU_TIMESTAMP_USES_DMA */

        Icu_Autosar_Wrapper_StopTimestamp(Channel, sIcu_CfgPtr[u8Icu_CoreId]);
        Icu_ClearChannelState(Channel, ICU_CHANNEL_STATE_RUNNING);
#if (ICU_MULTI_CORE == STD_ON)
        Icu_Autosar_Wrapper_SetMultiCoreIrqEnableState(Channel, 0);
#endif
    }
}
#endif

#if (ICU_GETTIMESTAMPINDEX_API == STD_ON)
/**************************************************************************************************
**  Service Name     : Icu_GetTimestampIndex
**                                                                                                  
**  Description      : This function reads the timestamp index of the given channel.
**                                                                                                  
**  Service ID       : 0x0b
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : Channel: Numeric identifier of the ICU channel.
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : Icu_IndexType: Abstract return type to cover different microcontrollers.
**                                                                                                  
****************************************************************************************************/
FUNC(Icu_IndexType, ICU_CODE) Icu_GetTimestampIndex(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(Icu_IndexType, AUTOMATIC) u16Icu_TimeStampIndex = 0U;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();
#ifdef ICU_TIMESTAMP_USES_DMA
#if (ICU_TIMESTAMP_USES_DMA == STD_ON)
    VAR(Icu_ValueType,  AUTOMATIC) nBuffIndex;
#endif
#endif

    u8Icu_VerifyRetVal = Icu_GetTimestampIndex_Verify(Channel);
    if ((Std_ReturnType)E_OK == u8Icu_VerifyRetVal)
    {

#ifdef ICU_TIMESTAMP_USES_DMA
#if (ICU_TIMESTAMP_USES_DMA == STD_ON)
            if ((sIcu_ChannelInfo[u8Icu_CoreId][Channel].sIcu_ChannelConfig.IcuChannel_bDmaSupport == (boolean)TRUE) && \
                 (sIcu_ChannelInfo[u8Icu_CoreId][Channel].sIcu_ChannelConfig.IcuChannel_DmaChannel != ICU_INVALID_DMA_CHANNEL))
            {
                VAR(uint32, AUTOMATIC) u16crtIter;

                SchM_Enter_ICU_EXCLUSIVE_AREA_08();

                u16crtIter =(uint32) sIcu_ChannelInfo[u8Icu_CoreId][Channel].u32Icu_ChannelBufferSize - \
                		EDMA_GetChnRemainingIterationsCount(sIcu_ChannelInfo[u8Icu_CoreId][Channel].sIcu_ChannelConfig.IcuChannel_DmaChannel);
                u16Icu_TimeStampIndex = (uint16)(sIcu_ChannelInfo[u8Icu_CoreId][Channel].u32Icu_ChannelBufferIndex + \
                    (Icu_IndexType)u16crtIter);

                SchM_Exit_ICU_EXCLUSIVE_AREA_08();

                for (nBuffIndex = 0; nBuffIndex < sIcu_ChannelInfo[u8Icu_CoreId][Channel].u32Icu_ChannelBufferSize; nBuffIndex++)
                {
                    sIcu_ChannelInfo[u8Icu_CoreId][Channel].u32Icu_ChannelBuffer[nBuffIndex] &= 0xFFFFFFU;
                }
            }
            else
            {
#endif
#endif /* ICU_TIMESTAMP_USES_DMA */
                u16Icu_TimeStampIndex = Icu_Autosar_Wrapper_GetTimestampIndex(Channel, sIcu_CfgPtr[u8Icu_CoreId]);
#ifdef ICU_TIMESTAMP_USES_DMA
#if (ICU_TIMESTAMP_USES_DMA == STD_ON)
            }
#endif
#endif

    }

    return u16Icu_TimeStampIndex;
}
#endif

#if (ICU_RESETEDGECOUNT_API == STD_ON)
/**************************************************************************************************
**  Service Name     : Icu_ResetEdgeCount
**                                                                                                  
**  Description      : This function resets the value of the counted edges to zero.
**                                                                                                  
**  Service ID       : 0x0c
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : Channel: Numeric identifier of the ICU channel.
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : None
**                                                                                                  
****************************************************************************************************/
FUNC(void, ICU_CODE) Icu_ResetEdgeCount(VAR(Icu_ChannelType,AUTOMATIC) Channel)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    u8Icu_VerifyRetVal = Icu_ResetEdgeCount_Verify(Channel);
    if ((Std_ReturnType)E_OK == u8Icu_VerifyRetVal)
    {
        Icu_ClearChannelState(Channel, ICU_CHANNEL_STATE_OVERFLOW);
        Icu_Autosar_Wrapper_ResetEdgeCount(Channel,sIcu_CfgPtr[u8Icu_CoreId]);
    }
}
#endif

#if (ICU_ENABLEEDGECOUNT_API == STD_ON)
/**************************************************************************************************
**  Service Name     : Icu_EnableEdgeCount
**                                                                                                  
**  Description      : This function enables the counting of edges of the given channel.
**                                                                                                  
**  Service ID       : 0x0d
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : Channel: Numeric identifier of the ICU channel.
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : None
**                                                                                                  
****************************************************************************************************/
FUNC(void, ICU_CODE) Icu_EnableEdgeCount(VAR(Icu_ChannelType,AUTOMATIC) Channel)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    u8Icu_VerifyRetVal = Icu_EnableEdgeCount_Verify(Channel);
    if ((Std_ReturnType)E_OK == u8Icu_VerifyRetVal)
    {
        Icu_ClearChannelState(Channel, ICU_CHANNEL_STATE_OVERFLOW);
        Icu_SetChannelState(Channel, ICU_CHANNEL_STATE_RUNNING);
        Icu_Autosar_Wrapper_EnableEdgeCount(Channel, sIcu_CfgPtr[u8Icu_CoreId]);
    }
}
#endif

#if (ICU_DISABLEEDGECOUNT_API == STD_ON)
/**************************************************************************************************
**  Service Name     : Icu_DisableEdgeCount
**                                                                                                  
**  Description      : This function disables the counting of edges of the given channel.
**                                                                                                  
**  Service ID       : 0x0e
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : Channel: Numeric identifier of the ICU channel.
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : None
**                                                                                                  
****************************************************************************************************/
FUNC(void, ICU_CODE) Icu_DisableEdgeCount(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    u8Icu_VerifyRetVal = Icu_DisableEdgeCount_Verify(Channel);
    if ((Std_ReturnType)E_OK == u8Icu_VerifyRetVal)
    {
        Icu_Autosar_Wrapper_DisableEdgeCount(Channel, sIcu_CfgPtr[u8Icu_CoreId]);
        Icu_ClearChannelState(Channel,ICU_CHANNEL_STATE_RUNNING);
    }
}
#endif

#if (ICU_GETEDGENUMBERS_API == STD_ON)
/**************************************************************************************************
**  Service Name     : Icu_GetEdgeNumbers
**                                                                                                  
**  Description      : This function reads the number of counted edges.
**                                                                                                  
**  Service ID       : 0x0f
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : Channel: Numeric identifier of the ICU channel.
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : Icu_EdgeNumberType: Abstract return type to cover different microcontrollers.
**                                                                                                  
****************************************************************************************************/
FUNC(Icu_EdgeNumberType, ICU_CODE) Icu_GetEdgeNumbers(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    VAR(Icu_EdgeNumberType, AUTOMATIC) u16Icu_EdgeNumbers = 0U;
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    u8Icu_VerifyRetVal = Icu_GetEdgeNumbers_Verify(Channel);
    if ((Std_ReturnType)E_OK == u8Icu_VerifyRetVal)
    {
#if (ICU_OVERFLOW_NOTIFICATION_API == STD_ON)
        if ((boolean)FALSE == Icu_GetOverflow(Channel, ICU_GETEDGENUMBERS_ID, ICU_E_EDGECOUNTING_OVERFLOW))
        {
#endif
            u16Icu_EdgeNumbers = Icu_Autosar_Wrapper_GetEdgeNumbers(Channel, sIcu_CfgPtr[u8Icu_CoreId]);
#if (ICU_OVERFLOW_NOTIFICATION_API == STD_ON)
        }
#endif
    }

    return u16Icu_EdgeNumbers;
}
#endif

#if (ICU_ENABLEEDGEDETECTION_API == STD_ON)
/**************************************************************************************************
**  Service Name     : Icu_EnableEdgeDetection
**                                                                                                  
**  Description      : This function enables / re-enables the detection of edges of the given channel.
**                                                                                                  
**  Service ID       : 0x16
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : Channel: Numeric identifier of the ICU channel.
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : None
**                                                                                                  
****************************************************************************************************/
FUNC(void,ICU_CODE) Icu_EnableEdgeDetection(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    u8Icu_VerifyRetVal = Icu_EnableEdgeDetection_Verify(Channel);
    if ((Std_ReturnType)E_OK == u8Icu_VerifyRetVal)
    {
        Icu_SetChannelState(Channel, ICU_CHANNEL_STATE_RUNNING);
        Icu_Autosar_Wrapper_EnableEdgeDetection(Channel, sIcu_CfgPtr[u8Icu_CoreId]);
    }
}
#endif

#if (ICU_DISABLEEDGEDETECTION_API == STD_ON)
/**************************************************************************************************
**  Service Name     : Icu_DisableEdgeDetection
**                                                                                                  
**  Description      : This function disables the detection of edges of the given channel.
**                                                                                                  
**  Service ID       : 0x17
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : Channel: Numeric identifier of the ICU channel.
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : None
**                                                                                                  
****************************************************************************************************/
FUNC(void,ICU_CODE) Icu_DisableEdgeDetection(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    u8Icu_VerifyRetVal = Icu_DisableEdgeDetection_Verify(Channel);
    if ((Std_ReturnType)E_OK == u8Icu_VerifyRetVal)
    {
        Icu_Autosar_Wrapper_DisableEdgeDetection(Channel, sIcu_CfgPtr[u8Icu_CoreId]);
        Icu_ClearChannelState(Channel, ICU_CHANNEL_STATE_RUNNING);
    }
}
#endif

#if (ICU_STARTSIGNALMEASUREMENT_API == STD_ON)
/**************************************************************************************************
**  Service Name     : Icu_StartSignalMeasurement
**                                                                                                  
**  Description      : This function starts the measurement of signals.
**                                                                                                  
**  Service ID       : 0x13
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : Channel: Numeric identifier of the ICU channel.
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : None
**                                                                                                  
****************************************************************************************************/
FUNC(void, ICU_CODE) Icu_StartSignalMeasurement(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(boolean,        AUTOMATIC) bDmaSupport = (boolean)FALSE;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();
#if (ICU_SIGNALMEASUREMENT_USES_DMA == STD_ON)
    VAR(Std_ReturnType , AUTOMATIC) returnResult = (Std_ReturnType)E_NOT_OK;
#endif

    u8Icu_VerifyRetVal = Icu_StartSignalMeasurement_Verify(Channel);
    if ((Std_ReturnType)E_OK == u8Icu_VerifyRetVal)
    {
        Icu_SetChannelState(Channel, ICU_CHANNEL_STATE_RUNNING);
        /*Clear the previous overflow status flag (if was the case) */
        Icu_ClearChannelState(Channel, ICU_CHANNEL_STATE_OVERFLOW);
#if (ICU_SIGNALMEASUREMENT_USES_DMA == STD_ON)
        /* DMA Config */
        if ((sIcu_ChannelInfo[u8Icu_CoreId][Channel].sIcu_ChannelConfig.IcuChannel_bDmaSupport == (boolean)TRUE) && \
             (sIcu_ChannelInfo[u8Icu_CoreId][Channel].sIcu_ChannelConfig.IcuChannel_DmaChannel != ICU_INVALID_DMA_CHANNEL))
        {
            SchM_Enter_ICU_EXCLUSIVE_AREA_11();
            returnResult = Icu_Autosar_Wrapper_StartSignalMeasurementDMA(Channel, sIcu_CfgPtr[u8Icu_CoreId]);
            SchM_Exit_ICU_EXCLUSIVE_AREA_11();
            if (returnResult == (Std_ReturnType)E_OK)
            {

                /* Enable notification */
#if 0
                EDMA_SetChnDisRequestsOnTransferComplete \
                ( \
                    sIcu_ChannelInfo[u8Icu_CoreId][Channel].sIcu_ChannelConfig.IcuChannel_DmaChannel, \
                    (boolean)TRUE \
                );
#endif

                /* Enable complete interrupt */
                EDMA_SetInterruptConfig \
                ( \
                    sIcu_ChannelInfo[u8Icu_CoreId][Channel].sIcu_ChannelConfig.IcuChannel_DmaChannel, \
                    EDMA_CHN_ENABLE_MAJOR_LOOP_DONE_INT, \
                    (boolean)TRUE \
                );

                /* Setup callback */
                (void)EDMA_SetUpCallback \
                ( \
                    sIcu_ChannelInfo[u8Icu_CoreId][Channel].sIcu_ChannelConfig.IcuChannel_DmaChannel, \
                    *(&ICU_SingalMeasurement_Callback_From_DMA), \
                    &sIcu_ChannelInfo[u8Icu_CoreId][Channel].u16Icu_Instance \
                );

                /* enable dma mode */
                bDmaSupport = (boolean)TRUE;
                /* Start DMA */
                (void)EDMA_SetChannelRequest \
                ( \
                    sIcu_ChannelInfo[u8Icu_CoreId][Channel].sIcu_ChannelConfig.IcuChannel_DmaChannel \
                );
            }
        }

#endif /* ICU_SIGNALMEASUREMENT_USES_DMA */

#if ((ICU_GETTIMEELAPSED_API == STD_ON) || (ICU_GETDUTYCYCLEVALUES_API == STD_ON))
        /* Reset Data */
        sIcu_ChannelInfo[u8Icu_CoreId][Channel].u32Icu_ChannelActiveTime = 0U;
        sIcu_ChannelInfo[u8Icu_CoreId][Channel].u32Icu_ChannelPeriod = 0U;
#endif
        Icu_Autosar_Wrapper_StartSignalMeasurement(Channel, bDmaSupport, sIcu_CfgPtr[u8Icu_CoreId]);
        Icu_ClearChannelState(Channel, ICU_CHANNEL_STATE_IDLE);
#if (ICU_MULTI_CORE == STD_ON)
        Icu_Autosar_Wrapper_SetMultiCoreIrqEnableState(Channel, 1);
#endif
    }
}
#endif

#if (ICU_STOPSIGNALMEASUREMENT_API == STD_ON)
/**************************************************************************************************
**  Service Name     : Icu_StopSignalMeasurement
**                                                                                                  
**  Description      : This function stops the measurement of signals of the given channel.
**                                                                                                  
**  Service ID       : 0x14
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : Channel: Numeric identifier of the ICU channel.
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : None
**                                                                                                  
****************************************************************************************************/
FUNC(void, ICU_CODE) Icu_StopSignalMeasurement(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    u8Icu_VerifyRetVal = Icu_StopSignalMeasurement_Verify(Channel);
    if ((Std_ReturnType)E_OK == u8Icu_VerifyRetVal)
    {
        Icu_Autosar_Wrapper_StopSignalMeasurement(Channel, sIcu_CfgPtr[u8Icu_CoreId]);
        Icu_ClearChannelState(Channel, ICU_CHANNEL_STATE_RUNNING);
#if (ICU_MULTI_CORE == STD_ON)
        Icu_Autosar_Wrapper_SetMultiCoreIrqEnableState(Channel, 0);
#endif
    }
}
#endif

#if (ICU_GETTIMEELAPSED_API == STD_ON)
/**************************************************************************************************
**  Service Name     : Icu_GetTimeElapsed
**                                                                                                  
**  Description      : This function reads the elapsed Signal Low Time for the given channel.
**                                                                                                  
**  Service ID       : 0x10
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : Channel: Numeric identifier of the ICU channel.
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : Icu_ValueType: see Description
**                                                                                                  
****************************************************************************************************/
FUNC(Icu_ValueType, ICU_CODE) Icu_GetTimeElapsed(VAR(Icu_ChannelType, AUTOMATIC) Channel)
{
    VAR(Icu_ValueType, AUTOMATIC) u32Icu_TimeElapsed = (Icu_ValueType)0U;
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    u8Icu_VerifyRetVal = Icu_GetTimeElapsed_Verify(Channel);

    if ((Std_ReturnType)E_OK == u8Icu_VerifyRetVal)
    {
        u32Icu_TimeElapsed =  Icu_Autosar_Wrapper_GetTimeElapsed(Channel, sIcu_CfgPtr[u8Icu_CoreId]);
        Icu_ClearChannelState(Channel, ICU_CHANNEL_STATE_IDLE);
    }

    return u32Icu_TimeElapsed;
}
#endif

#if (ICU_GETDUTYCYCLEVALUES_API == STD_ON)
/**************************************************************************************************
**  Service Name     : Icu_GetDutyCycleValues
**                                                                                                  
**  Description      : This function reads the coherent active time and period time for the given ICU
**                     Channel.
**                                                                                                  
**  Service ID       : 0x11
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : Channel: Numeric identifier of the ICU channel.
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : DutyCycleValues: Pointer to a buffer where the results (high time and period time)
**                                      shall be placed
**                                                                                                  
****************************************************************************************************/
FUNC(void, ICU_CODE) Icu_GetDutyCycleValues \
( \
    VAR(Icu_ChannelType, AUTOMATIC) Channel, \
    P2VAR(Icu_DutyCycleType, AUTOMATIC, ICU_APPL_DATA) DutyCycleValues \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    u8Icu_VerifyRetVal = Icu_GetDutyCycleValues_Verify(Channel,DutyCycleValues);
    if ((Std_ReturnType)E_OK == u8Icu_VerifyRetVal)
    {
        Icu_Autosar_Wrapper_GetDutyCycleValues(Channel, DutyCycleValues, sIcu_CfgPtr[u8Icu_CoreId]);
    }
}
#endif

#if (ICU_CHECKWAKEUP_API == STD_ON && ICU_REPORT_WAKEUP_SOURCE == STD_ON)
/**************************************************************************************************
**  Service Name     : Icu_CheckWakeup
**                                                                                                  
**  Description      : Checks if a wakeup capable ICU channel is the source for a wakeup event and
**                     calls the ECU state manager service EcuM_SetWakeupEvent in case of a valid
**                     ICU channel wakeup event.
**                                                                                                  
**  Service ID       : 0x15
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : WakeupSource: Informatin on wakeup source to be checked.
**                     The associated ICU channel can be determined from configuration data
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : None
**                                                                                                  
****************************************************************************************************/
FUNC(void, ICU_CODE) Icu_CheckWakeup(VAR(EcuM_WakeupSourceType, AUTOMATIC) WakeupSource)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelIndex = 0U;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    u8Icu_VerifyRetVal = Icu_CheckWakeup_Verify();
    if ((Std_ReturnType)E_OK == u8Icu_VerifyRetVal)
    {
        for (u16Icu_ChannelIndex = 0U;u16Icu_ChannelIndex < sIcu_CfgPtr[u8Icu_CoreId]->Icu_NumChannels;u16Icu_ChannelIndex++)
        {
            if ((Icu_ChannelState_Type)(ICU_CHANNEL_IS_WAKEUP_SOURCE | ICU_CHANNEL_STATE_WKUP) ==  \
                 Icu_GetChannelState(u16Icu_ChannelIndex, ICU_CHANNEL_IS_WAKEUP_SOURCE | ICU_CHANNEL_STATE_WKUP))
            {
#if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)
                if (WakeupSource == \
                    sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_ChannelIndex].sIcu_ChannelConfig.IcuChannel_WakeupValue)
                {
                    EcuM_SetWakeupEvent(WakeupSource);
                    Icu_ClearChannelState(u16Icu_ChannelIndex, ICU_CHANNEL_IS_WAKEUP_SOURCE);
                    break;
                }
#else
                Icu_ClearChannelState(u16Icu_ChannelIndex, ICU_CHANNEL_IS_WAKEUP_SOURCE);
#endif
            }
        }
    }
}
#endif

#if (ICU_GETVERSIONINFO_API == STD_ON)
/**************************************************************************************************
**  Service Name     : Icu_GetVersionInfo
**                                                                                                  
**  Description      : This function returns the version information of this module.
**                                                                                                  
**  Service ID       : 0x12
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : None
**                                                                                                  
**  Parameters (out) : versioninfo: Pointer to where to store the version information of this module.
**                                                                                                  
**  Return value     : None
**                                                                                                  
****************************************************************************************************/
FUNC(void, ICU_CODE) Icu_GetVersionInfo \
( \
    P2VAR(Std_VersionInfoType, AUTOMATIC, ICU_APPL_DATA) versioninfo \
)
{
    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (NULL_PTR == versioninfo)
    {
        #if (ICU_DEV_ERROR_DETECT == STD_ON)
        Icu_ReportError(ICU_GETVERSIONINFO_ID, ICU_E_PARAM_POINTER);
        #endif
    }
    #endif
    if ((Std_ReturnType)E_OK == Icu_CheckParamVersionInfo(versioninfo))
    {
        Icu_Autosar_Wrapper_GetVersionInfo(versioninfo);
    }
}
#endif

/*==================================================================================================
*                                    FUNCTION NOT AUTOSAR
==================================================================================================*/
/**************************************************************************************************
**  Service Name     : Icu_Init_Verify
**                                                                                                  
**  Description      : This function returns the Icu_Init check parameter.
**                                                                                                  
**  Service ID       : None
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : None
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : Std_ReturnType
**                                                                                                  
****************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_Init_Verify \
( \
    P2CONST(Icu_ConfigType, AUTOMATIC, ICU_APPL_CONST) sIcu_ConfigPtr \
)
{

	VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;

    if(eIcu_ModuleState[GetCoreID()] == ICU_STATE_IDLE )/* GetCoreID */
    {
        #if (ICU_DEV_ERROR_DETECT == STD_ON)
        Icu_ReportError(ICU_INIT_ID,ICU_E_ALREADY_INITIALIZED);
        #endif
        u8Icu_VerifyRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else if(NULL_PTR == sIcu_ConfigPtr)
    {
        #if (ICU_DEV_ERROR_DETECT == STD_ON)
        Icu_ReportError(ICU_INIT_ID,ICU_E_INIT_FAILED);
        #endif
        u8Icu_VerifyRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        u8Icu_VerifyRetVal = (Std_ReturnType)E_OK;
    }

    return u8Icu_VerifyRetVal;
}

/**************************************************************************************************
**  Service Name     : Icu_InitChannelState
**                                                                                                  
**  Description      : This function init channel information.
**                                                                                                  
**  Service ID       : None
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : None
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : Std_ReturnType
**                                                                                                  
****************************************************************************************************/
LOCAL_INLINE FUNC(void, ICU_CODE) Icu_InitChannelState \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelIndex \
)
{
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_ChannelIndex].u32Icu_ChannelState = 0U;
    sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_ChannelIndex].u32Icu_ChannelEdgeNumbers = 0;
    sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_ChannelIndex].u32Icu_ChannelEdgeDetection = ICU_IDLE;

    if(ICU_MODE_TIMESTAMP == sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_ChannelIndex].sIcu_ChannelConfig.IcuConfig_ChannelMode)
    {
        sIcu_ChannelInfo[GetCoreID()][u16Icu_ChannelIndex].u32Icu_ChannelBuffer = NULL_PTR;/* GetCoreID */
    }
}

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_Deinit_Verify(void)
{
    /******SWS_Icu_00299*********/
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_OK;

    if(ICU_STATE_UNINIT == eIcu_ModuleState[GetCoreID()])/* GetCoreID */
    {
        #if (ICU_DEV_ERROR_DETECT == STD_ON)
        Icu_ReportError(ICU_DEINIT_ID,ICU_E_UNINIT);
        #endif
        u8Icu_VerifyRetVal = (Std_ReturnType)E_NOT_OK;
    }

    return u8Icu_VerifyRetVal;
}

LOCAL_INLINE FUNC(void, ICU_CODE) Icu_DenitChannelState \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelIndex \
)
{
    sIcu_ChannelInfo[GetCoreID()][u16Icu_ChannelIndex].u32Icu_ChannelState = 0U;/* GetCoreID */
}

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_Setmode_Verify \
( \
    VAR(Icu_ModeType,AUTOMATIC) eIcu_Mode \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_OK;
    VAR(Icu_ChannelType,AUTOMATIC) u16Icu_ChannelIndex = 0U;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    if(ICU_STATE_UNINIT == eIcu_ModuleState[u8Icu_CoreId])
    {
        u8Icu_VerifyRetVal = (Std_ReturnType)E_NOT_OK;
        #if (ICU_DEV_ERROR_DETECT == STD_ON)
        Icu_ReportError(ICU_SETMODE_ID,ICU_E_UNINIT);
        #endif
    }
    else if(eIcu_Mode == eIcu_CurrentMode[u8Icu_CoreId])
    {
    	u8Icu_VerifyRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else if((ICU_MODE_SLEEP != eIcu_Mode) && (ICU_MODE_NORMAL != eIcu_Mode))
    {
    	u8Icu_VerifyRetVal = (Std_ReturnType)E_NOT_OK;
        #if (ICU_DEV_ERROR_DETECT == STD_ON)
        Icu_ReportError(ICU_SETMODE_ID,ICU_E_PARAM_MODE);
        #endif
    }
    else
    {
    	if(eIcu_Mode == ICU_MODE_SLEEP)
    	{
    		for(u16Icu_ChannelIndex = 0;u16Icu_ChannelIndex < sIcu_CfgPtr[u8Icu_CoreId]->Icu_NumChannels;u16Icu_ChannelIndex++)
    		{
    			if(ICU_CHANNEL_STATE_RUNNING == Icu_GetChannelState(u16Icu_ChannelIndex,ICU_CHANNEL_STATE_RUNNING))
    			{
    				#if (ICU_DEV_ERROR_DETECT == STD_ON)
    				Icu_ReportError(ICU_SETMODE_ID, ICU_E_BUSY_OPERATION);
    				#endif
    				break;
    			}
    		}
    		if(u16Icu_ChannelIndex != sIcu_CfgPtr[u8Icu_CoreId]->Icu_NumChannels)
    		{
    			u8Icu_VerifyRetVal = (Std_ReturnType)E_NOT_OK;
    		}
    		else
    		{
    			u8Icu_VerifyRetVal = (Std_ReturnType)E_OK;
    		}
    	}
    	else
    	{
    		u8Icu_VerifyRetVal = (Std_ReturnType)E_OK;
    	}
    }
    return u8Icu_VerifyRetVal;
}

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_DisableWakeup_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    if(ICU_STATE_UNINIT == eIcu_ModuleState[u8Icu_CoreId])
    {
        #if (ICU_DEV_ERROR_DETECT == STD_ON)
        Icu_ReportError(ICU_DISABLEWAKEUP_ID,ICU_E_UNINIT);
        #endif
    }
    else
    {
        if(u16Icu_Channel >= (Icu_ChannelType)ICU_MAX_CHANNEL)
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_DISABLEWAKEUP_ID,ICU_E_PARAM_CHANNEL);
            #endif
        }
        else if(sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Channel].sIcu_ChannelConfig.IcuChannel_WakeupCapability != (boolean)TRUE)
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_DISABLEWAKEUP_ID,ICU_E_PARAM_CHANNEL);
            #endif
        }
        else
        {
            u8Icu_VerifyRetVal = (Std_ReturnType)E_OK;
            #if(ICU_MULTI_CORE_SUPPORT == STD_ON)
            if(u8Icu_VerifyRetVal == (Std_ReturnType)E_OK)
            {
                u8Icu_VerifyRetVal = Icu_CoreVerify(u16Icu_Channel,ICU_DISABLEWAKEUP_ID);
            }
            #endif
        }
    }

    return u8Icu_VerifyRetVal;
}

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_EnableWakeup_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    if (ICU_MODE_NORMAL == eIcu_CurrentMode[u8Icu_CoreId])
    {
        if (ICU_STATE_UNINIT == eIcu_ModuleState[u8Icu_CoreId])
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_ENABLEWAKEUP_ID,ICU_E_UNINIT);
            #endif
        }
        else
        {
            if((u16Icu_Channel >= (Icu_ChannelType)ICU_MAX_CHANNEL))
            {
                #if (ICU_DEV_ERROR_DETECT == STD_ON)
                Icu_ReportError(ICU_ENABLEWAKEUP_ID,ICU_E_PARAM_CHANNEL);
                #endif
            }
            else if(sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Channel].sIcu_ChannelConfig.IcuChannel_WakeupCapability != (boolean)TRUE)
            {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_ENABLEWAKEUP_ID,ICU_E_PARAM_CHANNEL);
            #endif
            }
            else
            {
                u8Icu_VerifyRetVal = (Std_ReturnType)E_OK;
                #if(ICU_MULTI_CORE_SUPPORT == STD_ON)
                if(u8Icu_VerifyRetVal == (Std_ReturnType)E_OK)
                {  
                    u8Icu_VerifyRetVal = Icu_CoreVerify(u16Icu_Channel,ICU_ENABLEWAKEUP_ID);
                }
                #endif
            }
        }
    }

    return u8Icu_VerifyRetVal;
}

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_SetActivationCondition_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel, \
    VAR(Icu_ActivationType, AUTOMATIC) eIcu_Activation \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    if(ICU_MODE_NORMAL == eIcu_CurrentMode[u8Icu_CoreId])
    {
        if (ICU_STATE_UNINIT == eIcu_ModuleState[u8Icu_CoreId])
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_SETACTIVATIONCONDITION_ID,ICU_E_UNINIT);
            #endif
        }
        else
        {
            if((u16Icu_Channel >= (Icu_ChannelType)ICU_MAX_CHANNEL))
            {
                #if (ICU_DEV_ERROR_DETECT == STD_ON)
                Icu_ReportError(ICU_SETACTIVATIONCONDITION_ID,ICU_E_PARAM_CHANNEL);
                #endif
            }
            /**[SWS_Icu_00090]**/
            else if(ICU_MODE_SIGNAL_MEASUREMENT == \
                sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Channel].sIcu_ChannelConfig.IcuConfig_ChannelMode)
            {
                #if (ICU_DEV_ERROR_DETECT == STD_ON)
                Icu_ReportError(ICU_SETACTIVATIONCONDITION_ID,ICU_E_PARAM_CHANNEL);
                #endif
            }
            else
            {
                if ((ICU_RISING_EDGE != eIcu_Activation) && \
                    (ICU_FALLING_EDGE != eIcu_Activation) && \
                    (ICU_BOTH_EDGES != eIcu_Activation))
                {
                    #if (ICU_DEV_ERROR_DETECT == STD_ON)
                    Icu_ReportError(ICU_SETACTIVATIONCONDITION_ID,ICU_E_PARAM_ACTIVATION);
                    #endif
                    u8Icu_VerifyRetVal = E_NOT_OK;
                } 
                else
                {
                    u8Icu_VerifyRetVal = E_OK;
                    #if(ICU_MULTI_CORE_SUPPORT == STD_ON)
                    if(u8Icu_VerifyRetVal == (Std_ReturnType)E_OK)
                    {
                        u8Icu_VerifyRetVal = Icu_CoreVerify(u16Icu_Channel,ICU_SETACTIVATIONCONDITION_ID);
                    }
                    #endif
                }
            }
        }
    }

    return u8Icu_VerifyRetVal;
}

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_DisableNotification_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    if(ICU_MODE_NORMAL == eIcu_CurrentMode[u8Icu_CoreId])
    {
        if(ICU_STATE_UNINIT == eIcu_ModuleState[u8Icu_CoreId])
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_DISABLENOTIFICATION_ID,ICU_E_UNINIT);
            #endif
        }
        else
        {
            if((u16Icu_Channel >= (Icu_ChannelType)ICU_MAX_CHANNEL))
            {
                #if (ICU_DEV_ERROR_DETECT == STD_ON)
                Icu_ReportError(ICU_DISABLENOTIFICATION_ID,ICU_E_PARAM_CHANNEL);
                #endif
            }
            else
            {
                u8Icu_VerifyRetVal = (Std_ReturnType)E_OK;
                #if(ICU_MULTI_CORE_SUPPORT == STD_ON)
                if(u8Icu_VerifyRetVal == (Std_ReturnType)E_OK)
                {
                    u8Icu_VerifyRetVal = Icu_CoreVerify(u16Icu_Channel,ICU_DISABLENOTIFICATION_ID);
                }
                #endif
            }
        }
    }

    return u8Icu_VerifyRetVal;
}

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_EnableNotification_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    if(ICU_MODE_NORMAL == eIcu_CurrentMode[u8Icu_CoreId])
    {
        if(ICU_STATE_UNINIT == eIcu_ModuleState[u8Icu_CoreId])
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_ENABLENOTIFICATION_ID,ICU_E_UNINIT);
            #endif
        }
        else
        {
            if((u16Icu_Channel >= (Icu_ChannelType)ICU_MAX_CHANNEL))
            {
                #if (ICU_DEV_ERROR_DETECT == STD_ON)
                Icu_ReportError(ICU_ENABLENOTIFICATION_ID,ICU_E_PARAM_CHANNEL);
                #endif
            }
            else
            {
                u8Icu_VerifyRetVal = (Std_ReturnType)E_OK;
                #if(ICU_MULTI_CORE_SUPPORT == STD_ON)
                if(u8Icu_VerifyRetVal == (Std_ReturnType)E_OK)
                {
                    u8Icu_VerifyRetVal = Icu_CoreVerify(u16Icu_Channel,ICU_ENABLENOTIFICATION_ID);
                }
                #endif
            }
        }
    }

    return u8Icu_VerifyRetVal;
}

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_GetInputState_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    if(ICU_STATE_UNINIT == eIcu_ModuleState[u8Icu_CoreId])
    {
        #if (ICU_DEV_ERROR_DETECT == STD_ON)
        Icu_ReportError(ICU_GETINPUTSTATE_ID,ICU_E_UNINIT);
        #endif
    }
    else
    {
        if((u16Icu_Channel >= (Icu_ChannelType)ICU_MAX_CHANNEL) )
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_GETINPUTSTATE_ID,ICU_E_PARAM_CHANNEL);
            #endif
        }
        else if((ICU_MODE_SIGNAL_EDGE_DETECT != \
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Channel].sIcu_ChannelConfig.IcuConfig_ChannelMode) && \
            (ICU_MODE_SIGNAL_MEASUREMENT != \
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Channel].sIcu_ChannelConfig.IcuConfig_ChannelMode))
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_GETINPUTSTATE_ID,ICU_E_PARAM_CHANNEL);
            #endif
        }
        else
        {
            u8Icu_VerifyRetVal = (Std_ReturnType)E_OK;
            #if(ICU_MULTI_CORE_SUPPORT == STD_ON)
            if(u8Icu_VerifyRetVal == (Std_ReturnType)E_OK)
            {
                u8Icu_VerifyRetVal = Icu_CoreVerify(u16Icu_Channel,ICU_GETINPUTSTATE_ID);
            }
            #endif
        }
    }
    return u8Icu_VerifyRetVal;
}

#if (ICU_GETINPUTSTATE_API == STD_ON)
LOCAL_INLINE FUNC(Icu_InputStateType, ICU_CODE) Icu_GetIcuInputState \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
)
{
    VAR(Icu_InputStateType,     AUTOMATIC) eIcu_RetState = ICU_IDLE;
    VAR(Icu_MeasurementModeType,AUTOMATIC) eIcu_ChannelMode;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    /*SWS_Icu_00032*/
    if(Icu_GetChannelState(u16Icu_Channel, ICU_CHANNEL_STATE_IDLE) ==  (Icu_ChannelState_Type)ICU_IDLE)
    {
        eIcu_RetState = ICU_ACTIVE;
        Icu_ClearChannelState(u16Icu_Channel, ICU_CHANNEL_STATE_IDLE);
    }

    eIcu_ChannelMode = sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Channel].sIcu_ChannelConfig.IcuConfig_ChannelMode;

    if ((eIcu_ChannelMode == ICU_MODE_SIGNAL_EDGE_DETECT) || \
        (eIcu_ChannelMode == ICU_MODE_SIGNAL_MEASUREMENT))
    {
        eIcu_RetState = Icu_Autosar_Wrapper_GetInputState(u16Icu_Channel, sIcu_CfgPtr[u8Icu_CoreId]);
    }

    return eIcu_RetState;
}
#endif /* (ICU_GETINPUTSTATE_API == STD_ON) */

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_StartTimestamp_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel, \
    P2CONST(Icu_ValueType, AUTOMATIC,ICU_APPL_CONST) u32Icu_BufferPtr, \
    VAR(uint16, AUTOMATIC) u16_IcuBufferSize, \
    VAR(uint16, AUTOMATIC) u16Icu_NotifyInterval \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    if(ICU_MODE_SLEEP == eIcu_CurrentMode[u8Icu_CoreId])
    {
        u8Icu_VerifyRetVal = E_NOT_OK;
    }
    else
    {
        if(ICU_MODE_NORMAL == eIcu_CurrentMode[u8Icu_CoreId])
        {
            if(eIcu_ModuleState[u8Icu_CoreId] == ICU_STATE_UNINIT )
            {
                #if (ICU_DEV_ERROR_DETECT == STD_ON)
                Icu_ReportError(ICU_STARTTIMESTAMP_ID,ICU_E_UNINIT);
                #endif
            }
            else
            {
                if (NULL_PTR == u32Icu_BufferPtr)
                {
                    #if (ICU_DEV_ERROR_DETECT == STD_ON)
                    Icu_ReportError(ICU_STARTTIMESTAMP_ID,ICU_E_PARAM_POINTER);
                    #endif
                }
            	else if((u16Icu_Channel >= (Icu_ChannelType)ICU_MAX_CHANNEL))
                {
                    #if (ICU_DEV_ERROR_DETECT == STD_ON)
                    Icu_ReportError(ICU_STARTTIMESTAMP_ID,ICU_E_PARAM_CHANNEL);
                    #endif
                }
                else if(ICU_MODE_TIMESTAMP != \
                    sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Channel].sIcu_ChannelConfig.IcuConfig_ChannelMode)
                {
                    #if (ICU_DEV_ERROR_DETECT == STD_ON)
                    Icu_ReportError(ICU_STARTTIMESTAMP_ID,ICU_E_PARAM_CHANNEL);
                    #endif
                }
                else
                {
                    if ((uint16)0U == u16_IcuBufferSize)
                    {
                        #if (ICU_DEV_ERROR_DETECT == STD_ON)
                        Icu_ReportError(ICU_STARTTIMESTAMP_ID,ICU_E_PARAM_BUFFER_SIZE);
                        #endif
                    }
                    else if ((ICU_CHANNEL_STATE_NOTIFICATION  \
                             == Icu_GetChannelState(u16Icu_Channel,ICU_CHANNEL_STATE_NOTIFICATION)) \
                             && (NULL_PTR != sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Channel].sIcu_ChannelConfig.IcuChannel_Notification) \
                             && ((uint16)0U == u16Icu_NotifyInterval))
                    {
                        #if (ICU_DEV_ERROR_DETECT == STD_ON)
                        Icu_ReportError(ICU_STARTTIMESTAMP_ID,ICU_E_PARAM_NOTIFY_INTERVAL);
                        #endif
                    }
                    else
                    {
                        u8Icu_VerifyRetVal = E_OK;
                        #if(ICU_MULTI_CORE_SUPPORT == STD_ON)
                        if(u8Icu_VerifyRetVal == (Std_ReturnType)E_OK)
                        {
                            u8Icu_VerifyRetVal = Icu_CoreVerify(u16Icu_Channel,ICU_STARTTIMESTAMP_ID);
                        }
                        #endif
                    }
                }
            }
        }
    }

    return u8Icu_VerifyRetVal;
}

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_StopTimestamp_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    if(ICU_MODE_NORMAL == eIcu_CurrentMode[u8Icu_CoreId])
    {
        if(eIcu_ModuleState[u8Icu_CoreId] == ICU_STATE_UNINIT)
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_STOPTIMESTAMP_ID,ICU_E_UNINIT);
            #endif
        }
        else if(ICU_MODE_TIMESTAMP != \
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Channel].sIcu_ChannelConfig.IcuConfig_ChannelMode)
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_STOPTIMESTAMP_ID,ICU_E_PARAM_CHANNEL);
            #endif
        }
        /*SWS_Icu_00166*/
        else if(ICU_CHANNEL_STATE_RUNNING != \
                    Icu_GetChannelState(u16Icu_Channel, ICU_CHANNEL_STATE_RUNNING))
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_STOPTIMESTAMP_ID,ICU_E_NOT_STARTED);
            #endif
        }
        else
        {
            if((u16Icu_Channel >= (Icu_ChannelType)ICU_MAX_CHANNEL))
            {
                #if (ICU_DEV_ERROR_DETECT == STD_ON)
                Icu_ReportError(ICU_STOPTIMESTAMP_ID,ICU_E_PARAM_CHANNEL);
                #endif 
            }
            else
            {
                u8Icu_VerifyRetVal = (Std_ReturnType)E_OK;
                #if(ICU_MULTI_CORE_SUPPORT == STD_ON)

                if(u8Icu_VerifyRetVal == (Std_ReturnType)E_OK)
                {
                    u8Icu_VerifyRetVal = Icu_CoreVerify(u16Icu_Channel,ICU_STOPTIMESTAMP_ID);
                }
                #endif
            }
        }
    }

    return u8Icu_VerifyRetVal;
}

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_GetTimestampIndex_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    if(ICU_MODE_NORMAL == eIcu_CurrentMode[u8Icu_CoreId])
    {
        if(eIcu_ModuleState[u8Icu_CoreId] == ICU_STATE_UNINIT)
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_GETTIMESTAMPINDEX_ID,ICU_E_UNINIT);
            #endif
        }
        else
        {
            if((u16Icu_Channel >= (Icu_ChannelType)ICU_MAX_CHANNEL))
            {
                #if (ICU_DEV_ERROR_DETECT == STD_ON)
                Icu_ReportError(ICU_GETTIMESTAMPINDEX_ID,ICU_E_PARAM_CHANNEL);
                #endif
            }
            else if(ICU_MODE_TIMESTAMP != \
                sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Channel].sIcu_ChannelConfig.IcuConfig_ChannelMode)
            {
                #if (ICU_DEV_ERROR_DETECT == STD_ON)
                Icu_ReportError(ICU_GETTIMESTAMPINDEX_ID,ICU_E_PARAM_CHANNEL);
                #endif
            }
            else
            {
                u8Icu_VerifyRetVal = (Std_ReturnType)E_OK;
                #if(ICU_MULTI_CORE_SUPPORT == STD_ON)
                if(u8Icu_VerifyRetVal == (Std_ReturnType)E_OK)
                {
                    u8Icu_VerifyRetVal = Icu_CoreVerify(u16Icu_Channel,ICU_GETTIMESTAMPINDEX_ID);
                }
                #endif
            }
        }
    }

    return u8Icu_VerifyRetVal;
}

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_ResetEdgeCount_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    if(ICU_MODE_NORMAL == eIcu_CurrentMode[u8Icu_CoreId])
    {
        if(eIcu_ModuleState[u8Icu_CoreId] == ICU_STATE_UNINIT)
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_RESETEDGECOUNT_ID,ICU_E_UNINIT);
            #endif
        }
        else if(ICU_MODE_EDGE_COUNTER != \
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Channel].sIcu_ChannelConfig.IcuConfig_ChannelMode)
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_RESETEDGECOUNT_ID,ICU_E_PARAM_CHANNEL);
            #endif
        }
        else
        {
            if((u16Icu_Channel >= (Icu_ChannelType)ICU_MAX_CHANNEL))
            {
                #if (ICU_DEV_ERROR_DETECT == STD_ON)
                Icu_ReportError(ICU_RESETEDGECOUNT_ID,ICU_E_PARAM_CHANNEL);
                #endif
            }
            else
            {
                u8Icu_VerifyRetVal = (Std_ReturnType)E_OK;
                #if(ICU_MULTI_CORE_SUPPORT == STD_ON)
    
                if(u8Icu_VerifyRetVal == (Std_ReturnType)E_OK)
                {
                    u8Icu_VerifyRetVal = Icu_CoreVerify(u16Icu_Channel,ICU_RESETEDGECOUNT_ID);
                }
                #endif
            }
        }
    }

    return u8Icu_VerifyRetVal;
}

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_EnableEdgeCount_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    if(ICU_MODE_NORMAL == eIcu_CurrentMode[u8Icu_CoreId])
    {
        if(eIcu_ModuleState[u8Icu_CoreId] == ICU_STATE_UNINIT)
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_ENABLEEDGECOUNT_ID,ICU_E_UNINIT);
            #endif
        }
        else if(ICU_MODE_EDGE_COUNTER != \
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Channel].sIcu_ChannelConfig.IcuConfig_ChannelMode)
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_ENABLEEDGECOUNT_ID,ICU_E_PARAM_CHANNEL);
            #endif
        }
        else
        {
            if((u16Icu_Channel >= (Icu_ChannelType)ICU_MAX_CHANNEL))
            {
                #if (ICU_DEV_ERROR_DETECT == STD_ON)
                Icu_ReportError(ICU_ENABLEEDGECOUNT_ID,ICU_E_PARAM_CHANNEL);
                #endif
            }
            else
            {
                u8Icu_VerifyRetVal = (Std_ReturnType)E_OK;
                #if(ICU_MULTI_CORE_SUPPORT == STD_ON)
    
                if(u8Icu_VerifyRetVal == (Std_ReturnType)E_OK)
                {
                    u8Icu_VerifyRetVal = Icu_CoreVerify(u16Icu_Channel,ICU_ENABLEEDGECOUNT_ID);
                }
                #endif
            }
        }
    }

    return u8Icu_VerifyRetVal;
}

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_DisableEdgeCount_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    if(ICU_MODE_NORMAL == eIcu_CurrentMode[u8Icu_CoreId])
    {
        if(eIcu_ModuleState[u8Icu_CoreId] == ICU_STATE_UNINIT)
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_DISABLEEDGECOUNT_ID,ICU_E_UNINIT);
            #endif
        }
        else if(ICU_MODE_EDGE_COUNTER != \
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Channel].sIcu_ChannelConfig.IcuConfig_ChannelMode)
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_DISABLEEDGECOUNT_ID,ICU_E_PARAM_CHANNEL);
            #endif
        }
        else
        {
            if((u16Icu_Channel >= (Icu_ChannelType)ICU_MAX_CHANNEL))
            {
                #if (ICU_DEV_ERROR_DETECT == STD_ON)
                Icu_ReportError(ICU_DISABLEEDGECOUNT_ID,ICU_E_PARAM_CHANNEL);
                #endif
            }
            else
            {
                u8Icu_VerifyRetVal = (Std_ReturnType)E_OK;
                #if(ICU_MULTI_CORE_SUPPORT == STD_ON)
    
                if(u8Icu_VerifyRetVal == (Std_ReturnType)E_OK)
                {
                    u8Icu_VerifyRetVal = Icu_CoreVerify(u16Icu_Channel,ICU_DISABLEEDGECOUNT_ID);
                }
                #endif
            }
        }
    }

    return u8Icu_VerifyRetVal;
}

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_GetEdgeNumbers_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    if(ICU_MODE_NORMAL == eIcu_CurrentMode[u8Icu_CoreId])
    {
        if(eIcu_ModuleState[u8Icu_CoreId] == ICU_STATE_UNINIT)
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_GETEDGENUMBERS_ID,ICU_E_UNINIT);
            #endif
        }
        else if(ICU_MODE_EDGE_COUNTER != \
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Channel].sIcu_ChannelConfig.IcuConfig_ChannelMode)
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_GETEDGENUMBERS_ID,ICU_E_PARAM_CHANNEL);
            #endif
        }
        else
        {
            if((u16Icu_Channel >= (Icu_ChannelType)ICU_MAX_CHANNEL))
            {
                #if (ICU_DEV_ERROR_DETECT == STD_ON)
                Icu_ReportError(ICU_GETEDGENUMBERS_ID,ICU_E_PARAM_CHANNEL);
                #endif
            }
            else
            {
                u8Icu_VerifyRetVal = (Std_ReturnType)E_OK;
                #if(ICU_MULTI_CORE_SUPPORT == STD_ON)
    
                if(u8Icu_VerifyRetVal == (Std_ReturnType)E_OK)
                {
                    u8Icu_VerifyRetVal = Icu_CoreVerify(u16Icu_Channel,ICU_GETEDGENUMBERS_ID);
                }
                #endif
            }
        }
    }

    return u8Icu_VerifyRetVal;
}

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_EnableEdgeDetection_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    if(ICU_MODE_NORMAL == eIcu_CurrentMode[u8Icu_CoreId])
    {
        if(eIcu_ModuleState[u8Icu_CoreId] == ICU_STATE_UNINIT)
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_ENABLEEDGEDETECTION_ID,ICU_E_UNINIT);
            #endif
        }
        else if(ICU_MODE_SIGNAL_EDGE_DETECT != \
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Channel].sIcu_ChannelConfig.IcuConfig_ChannelMode)
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_ENABLEEDGEDETECTION_ID,ICU_E_PARAM_CHANNEL);
            #endif
        }
        else
        {
            if((u16Icu_Channel >= (Icu_ChannelType)ICU_MAX_CHANNEL))
            {
                #if (ICU_DEV_ERROR_DETECT == STD_ON)
                Icu_ReportError(ICU_ENABLEEDGEDETECTION_ID,ICU_E_PARAM_CHANNEL);
                #endif
            }
            else
            {
                u8Icu_VerifyRetVal = (Std_ReturnType)E_OK;
                #if(ICU_MULTI_CORE_SUPPORT == STD_ON)
    
                if(u8Icu_VerifyRetVal == (Std_ReturnType)E_OK)
                {
                    u8Icu_VerifyRetVal = Icu_CoreVerify(u16Icu_Channel,ICU_ENABLEEDGEDETECTION_ID);
                }
                #endif
            }
        }
    }

    return u8Icu_VerifyRetVal;
}

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_DisableEdgeDetection_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    if(ICU_MODE_NORMAL == eIcu_CurrentMode[u8Icu_CoreId])
    {
        if(eIcu_ModuleState[u8Icu_CoreId] == ICU_STATE_UNINIT)
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_DISABLEEDGEDETECTION_ID,ICU_E_UNINIT);
            #endif
        }
        else if(ICU_MODE_SIGNAL_EDGE_DETECT != \
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Channel].sIcu_ChannelConfig.IcuConfig_ChannelMode)
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_DISABLEEDGEDETECTION_ID,ICU_E_PARAM_CHANNEL);
            #endif
        }
        else
        {
            if((u16Icu_Channel >= (Icu_ChannelType)ICU_MAX_CHANNEL))
            {
                #if (ICU_DEV_ERROR_DETECT == STD_ON)
                Icu_ReportError(ICU_DISABLEEDGEDETECTION_ID,ICU_E_PARAM_CHANNEL);
                #endif
            }
            else
            {
                u8Icu_VerifyRetVal = (Std_ReturnType)E_OK;
                #if(ICU_MULTI_CORE_SUPPORT == STD_ON)
    
                if(u8Icu_VerifyRetVal == (Std_ReturnType)E_OK)
                {
                    u8Icu_VerifyRetVal = Icu_CoreVerify(u16Icu_Channel,ICU_DISABLEEDGEDETECTION_ID);
                }
                #endif
            }
        }
    }

    return u8Icu_VerifyRetVal;
}

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_StartSignalMeasurement_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    if(ICU_MODE_NORMAL == eIcu_CurrentMode[u8Icu_CoreId])
    {
        if(eIcu_ModuleState[u8Icu_CoreId] == ICU_STATE_UNINIT)
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_STARTSIGNALMEASUREMENT_ID,ICU_E_UNINIT);
            #endif
        }
        else
        {
            if((u16Icu_Channel >= (Icu_ChannelType)ICU_MAX_CHANNEL))
            {
                #if (ICU_DEV_ERROR_DETECT == STD_ON)
                Icu_ReportError(ICU_STARTSIGNALMEASUREMENT_ID,ICU_E_PARAM_CHANNEL);
                #endif
            }
            else if(ICU_MODE_SIGNAL_MEASUREMENT != \
                sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Channel].sIcu_ChannelConfig.IcuConfig_ChannelMode)
            {
                #if (ICU_DEV_ERROR_DETECT == STD_ON)
                Icu_ReportError(ICU_STARTSIGNALMEASUREMENT_ID,ICU_E_PARAM_CHANNEL);
                #endif
            }
            else
            {
                u8Icu_VerifyRetVal = (Std_ReturnType)E_OK;
                #if(ICU_MULTI_CORE_SUPPORT == STD_ON)
    
                if(u8Icu_VerifyRetVal == (Std_ReturnType)E_OK)
                {
                    u8Icu_VerifyRetVal = Icu_CoreVerify(u16Icu_Channel,ICU_STARTSIGNALMEASUREMENT_ID);
                }
                #endif
            }
        }
    }

    return u8Icu_VerifyRetVal;
}

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_StopSignalMeasurement_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    if(ICU_MODE_NORMAL == eIcu_CurrentMode[u8Icu_CoreId])
    {
        if(eIcu_ModuleState[u8Icu_CoreId] == ICU_STATE_UNINIT)
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_STOPSIGNALMEASUREMENT_ID,ICU_E_UNINIT);
            #endif
        }
        else if(ICU_MODE_SIGNAL_MEASUREMENT != \
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Channel].sIcu_ChannelConfig.IcuConfig_ChannelMode)
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_STOPSIGNALMEASUREMENT_ID,ICU_E_PARAM_CHANNEL);
            #endif
        }
        else
        {
            if((u16Icu_Channel >= (Icu_ChannelType)ICU_MAX_CHANNEL))
            {
                #if (ICU_DEV_ERROR_DETECT == STD_ON)
                Icu_ReportError(ICU_STOPSIGNALMEASUREMENT_ID,ICU_E_PARAM_CHANNEL);
                #endif
            }
            else
            {
                u8Icu_VerifyRetVal = (Std_ReturnType)E_OK;
                #if(ICU_MULTI_CORE_SUPPORT == STD_ON)
    
                if(u8Icu_VerifyRetVal == (Std_ReturnType)E_OK)
                {
                    u8Icu_VerifyRetVal = Icu_CoreVerify(u16Icu_Channel,ICU_STOPSIGNALMEASUREMENT_ID);
                }
                #endif
            }
        }
    }

    return u8Icu_VerifyRetVal;
}

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_GetTimeElapsed_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    if(ICU_MODE_NORMAL == eIcu_CurrentMode[u8Icu_CoreId])
    {
        if(eIcu_ModuleState[u8Icu_CoreId] == ICU_STATE_UNINIT)
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_GETTIMEELAPSED_ID,ICU_E_UNINIT);
            #endif
        }
        else if(ICU_MODE_SIGNAL_MEASUREMENT != \
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Channel].sIcu_ChannelConfig.IcuConfig_ChannelMode)
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_GETTIMEELAPSED_ID,ICU_E_PARAM_CHANNEL);
            #endif
        }
        else
        {
            if((u16Icu_Channel >= (Icu_ChannelType)ICU_MAX_CHANNEL))
            {
                #if (ICU_DEV_ERROR_DETECT == STD_ON)
                Icu_ReportError(ICU_GETTIMEELAPSED_ID,ICU_E_PARAM_CHANNEL);
                #endif
            }
            else
            {
                u8Icu_VerifyRetVal = (Std_ReturnType)E_OK;
                #if(ICU_MULTI_CORE_SUPPORT == STD_ON)
    
                if(u8Icu_VerifyRetVal == (Std_ReturnType)E_OK)
                {
                    u8Icu_VerifyRetVal = Icu_CoreVerify(u16Icu_Channel,ICU_GETTIMEELAPSED_ID);
                }
                #endif
            }
        }
    }

    return u8Icu_VerifyRetVal;
}

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_GetDutyCycleValues_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel, \
	P2CONST(Icu_DutyCycleType, AUTOMATIC, ICU_APPL_CONST) DutyCycleValues
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    if(ICU_MODE_NORMAL == eIcu_CurrentMode[u8Icu_CoreId])
    {
        if(eIcu_ModuleState[u8Icu_CoreId] == ICU_STATE_UNINIT)
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_GETDUTYCYCLEVALUES_ID,ICU_E_UNINIT);
            #endif
        }
        else if(NULL_PTR == DutyCycleValues)
        {
			#if (ICU_DEV_ERROR_DETECT == STD_ON)
			Icu_ReportError(ICU_GETDUTYCYCLEVALUES_ID,ICU_E_PARAM_POINTER);
			#endif
        }
        else if(ICU_MODE_SIGNAL_MEASUREMENT != \
            sIcu_ChannelInfo[u8Icu_CoreId][u16Icu_Channel].sIcu_ChannelConfig.IcuConfig_ChannelMode)
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
            Icu_ReportError(ICU_GETDUTYCYCLEVALUES_ID,ICU_E_PARAM_CHANNEL);
            #endif
        }
        else
        {
            if((u16Icu_Channel >= (Icu_ChannelType)ICU_MAX_CHANNEL))
            {
                #if (ICU_DEV_ERROR_DETECT == STD_ON)
                Icu_ReportError(ICU_GETDUTYCYCLEVALUES_ID,ICU_E_PARAM_CHANNEL);
                #endif
            }
            else
            {
                u8Icu_VerifyRetVal = (Std_ReturnType)E_OK;
                #if(ICU_MULTI_CORE_SUPPORT == STD_ON)
    
                if(u8Icu_VerifyRetVal == (Std_ReturnType)E_OK)
                {
                    u8Icu_VerifyRetVal = Icu_CoreVerify(u16Icu_Channel,ICU_GETDUTYCYCLEVALUES_ID);
                }
                #endif
            }
        }
    }

    return u8Icu_VerifyRetVal;
}

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_CheckWakeup_Verify(void)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    if(eIcu_ModuleState[u8Icu_CoreId] == ICU_STATE_UNINIT)
    {
        #if (ICU_DEV_ERROR_DETECT == STD_ON)
        Icu_ReportError(ICU_CHECKWAKEUP_ID,ICU_E_UNINIT);
        #endif
    }
    else
    {
        u8Icu_VerifyRetVal = (Std_ReturnType)E_OK;
    }

    return u8Icu_VerifyRetVal;
}

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_CheckParamVersionInfo \
( \
    P2CONST(Std_VersionInfoType, AUTOMATIC, ICU_APPL_CONST) sIcu_Versioninfo \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Icu_CheckFlag = (Std_ReturnType)E_OK;

    if (NULL_PTR == sIcu_Versioninfo)
    {
        #if (ICU_DEV_ERROR_DETECT == STD_ON)
        Icu_ReportError(ICU_GETVERSIONINFO_ID, ICU_E_PARAM_VINFO);
        #endif
        u8Icu_CheckFlag = (Std_ReturnType)E_NOT_OK;
    }

    return u8Icu_CheckFlag;
}

LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_GetInputLevel_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    if(eIcu_ModuleState[u8Icu_CoreId] == ICU_STATE_UNINIT)
    {
        #if (ICU_DEV_ERROR_DETECT == STD_ON)
        Icu_ReportError(ICU_GETINPUTLEVEL_ID,ICU_E_UNINIT);
        #endif
    }
    else
    {
        if((u16Icu_Channel >= (Icu_ChannelType)ICU_MAX_CHANNEL))
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
                Icu_ReportError(ICU_GETINPUTLEVEL_ID,ICU_E_PARAM_CHANNEL);
            #endif
        }
        else
        {
            u8Icu_VerifyRetVal = (Std_ReturnType)E_OK;
        }
    }

    return u8Icu_VerifyRetVal;
}

#if (ICU_CAPTURERGISTER_API == STD_ON)
LOCAL_INLINE FUNC(Std_ReturnType, ICU_CODE) Icu_GetCaptureRegisterValue_Verify \
( \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_Channel \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Icu_VerifyRetVal = E_NOT_OK;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = GetCoreID();

    if(eIcu_ModuleState[u8Icu_CoreId] == ICU_STATE_UNINIT)
    {
        #if (ICU_DEV_ERROR_DETECT == STD_ON)
        Icu_ReportError(ICU_GETREGISTERVALUE_ID,ICU_E_UNINIT);
        #endif
    }
    else
    {
        if((u16Icu_Channel >= (Icu_ChannelType)ICU_MAX_CHANNEL))
        {
            #if (ICU_DEV_ERROR_DETECT == STD_ON)
                Icu_ReportError(ICU_GETREGISTERVALUE_ID,ICU_E_PARAM_CHANNEL);
            #endif
        }
        else
        {
            u8Icu_VerifyRetVal = (Std_ReturnType)E_OK;
        }
    }

    return u8Icu_VerifyRetVal;
}
#endif

/*==================================================================================================
*                                    NONAUTOSAR FUNCTION
==================================================================================================*/
/**************************************************************************************************
**  Service Name     : Icu_CallNotification
**                                                                                                  
**  Description      : According to the last call of Icu_EnableNotification, this notification 
**                     function to be called if the requested signal edge (rising / falling / both edges)
**                     occurs (once per edge).
**                                                                                                  
**  Service ID       : None
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : None
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : None
**                                                                                                  
****************************************************************************************************/
LOCAL_INLINE FUNC(void, ICU_CODE) Icu_CallNotification \
( \
    VAR(Icu_ChannelType, AUTOMATIC) Channel \
)
{
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();
    /* Call Icu_Channel_Notification */
    if (sIcu_ChannelInfo[u8Icu_CoreId][Channel].sIcu_ChannelConfig.IcuChannel_Notification != NULL_PTR)
    {
        sIcu_ChannelInfo[u8Icu_CoreId][Channel].sIcu_ChannelConfig.IcuChannel_Notification();
    }
}

/**************************************************************************************************
**  Service Name     : Icu_CallOverflowNotification
**                                                                                                  
**  Description      : According to the last call of Icu_EnableNotification, this notification 
**                     function to be called if the requested channel is over flow.
**                                                                                                  
**  Service ID       : None
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : None
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : None
**                                                                                                  
****************************************************************************************************/
LOCAL_INLINE FUNC(void, ICU_CODE) Icu_CallOverflowNotification \
( \
    VAR(Icu_ChannelType, AUTOMATIC) Channel \
)
{
	(void)Channel;
    /* Over FLow callout */
}

/**************************************************************************************************
**  Service Name     : Icu_CallTimestampNotification
**                                                                                                  
**  Description      : According to the last call of Icu_StartTimestamp, this notification 
**                     function to be called if the timestamp receive complete.
**                                                                                                  
**  Service ID       : None
**                                                                                                  
**  Sync/Async       : Synchronous
**                                                                                                  
**  Reentrancy       : Reentrant
**                                                                                                  
**  Parameters (in)  : None
**                                                                                                  
**  Parameters (out) : None
**                                                                                                  
**  Return value     : None
**                                                                                                  
****************************************************************************************************/
LOCAL_INLINE FUNC(void, ICU_CODE) Icu_CallTimestampNotification \
( \
    VAR(Icu_ChannelType, AUTOMATIC) Channel \
)
{
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();
    /* Call IcuChannel_TimestampNotification */
    if (sIcu_ChannelInfo[u8Icu_CoreId][Channel].sIcu_ChannelConfig.IcuChannel_TimestampNotification != NULL_PTR)
    {
        sIcu_ChannelInfo[u8Icu_CoreId][Channel].sIcu_ChannelConfig.IcuChannel_TimestampNotification();
    }
}
#if (ICU_OVERFLOW_NOTIFICATION_API == STD_ON)
LOCAL_INLINE FUNC(boolean, ICU_CODE) Icu_GetOverflow \
( \
    VAR(Icu_ChannelType,    AUTOMATIC) Channel, \
    VAR(uint8,              AUTOMATIC) u8ServiceId, \
    VAR(uint8,              AUTOMATIC) u8Error \
)
{
    VAR(boolean, AUTOMATIC) bOverflow = (boolean)FALSE;
    VAR(boolean, AUTOMATIC) bChOverflowState = (boolean)FALSE;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    if (ICU_CHANNEL_STATE_OVERFLOW == Icu_GetChannelState(Channel,ICU_CHANNEL_STATE_OVERFLOW))
    {
        bChOverflowState = (boolean)TRUE;
    }

    if (((boolean)TRUE == Icu_Autosar_Wrapper_GetOverFlow(Channel, sIcu_CfgPtr[u8Icu_CoreId])) || \
        ((boolean)TRUE == bChOverflowState) \
       )
    {
        #if (ICU_DEV_ERROR_DETECT == STD_ON)
        (void)Icu_ReportError(u8ServiceId, u8Error);
		#else
        (void)u8ServiceId;
        (void)u8Error;
        #endif
        bOverflow = (boolean)TRUE;
    }

    return bOverflow;
}
#endif
FUNC(void, ICU_CODE) Icu_ReportWakeupAndOverflow \
( \
    VAR(Icu_ChannelType,    AUTOMATIC) Channel, \
    VAR(boolean,            AUTOMATIC) bOverflow \
)
{
    VAR(boolean, AUTOMATIC) bChWakeupCapable;
    VAR(EcuM_WakeupSourceType, AUTOMATIC) wakeupSource;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    if (ICU_CHANNEL_STATE_WKUP == Icu_GetChannelState (Channel, ICU_CHANNEL_STATE_WKUP))
    {
        bChWakeupCapable = (boolean)TRUE;
    }
    else
    {
        bChWakeupCapable = (boolean)FALSE;
    }

    if ((ICU_MODE_SLEEP == eIcu_CurrentMode[u8Icu_CoreId]) && (bChWakeupCapable == (boolean)TRUE))
    {
        Icu_SetChannelState(Channel, ICU_CHANNEL_IS_WAKEUP_SOURCE);
#if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)
        wakeupSource = (EcuM_WakeupSourceType)Icu_Autosar_Wrapper_GetWakeupSource(Channel, sIcu_CfgPtr[u8Icu_CoreId]);
        EcuM_CheckWakeup(wakeupSource);
#else
        (void)wakeupSource;
#endif /* ICU_REPORT_WAKEUP_SOURCE == STD_ON */
    }

    if ((boolean)TRUE == bOverflow)
    {
        Icu_SetChannelState(Channel, ICU_CHANNEL_STATE_OVERFLOW);
#if (ICU_OVERFLOW_NOTIFICATION_API == STD_ON)
        /* Over flow callback */
        Icu_CallOverflowNotification(Channel);
#endif  /* ICU_OVERFLOW_NOTIFICATION_API */
    }
}

FUNC(void, ICU_CODE) Icu_ReportEvents \
( \
    VAR(Icu_ChannelType,    AUTOMATIC) Channel, \
    VAR(boolean,            AUTOMATIC) bOverflow \
)
{
    Icu_SetChannelState(Channel, ICU_CHANNEL_STATE_IDLE);
    Icu_ReportWakeupAndOverflow(Channel, bOverflow);

    SchM_Enter_ICU_CRITICAL_AREA_02();

    sIcu_ChannelInfo[GetCoreID()][Channel].u32Icu_ChannelEdgeDetection = ICU_ACTIVE;/* GetCoreID */

    SchM_Exit_ICU_CRITICAL_AREA_02();

    Icu_CallNotification(Channel);
}

FUNC(void,ICU_CODE) Icu_Timestamp \
( \
    VAR(Icu_ChannelType,    AUTOMATIC) Channel, \
    VAR(uint8,              AUTOMATIC) u8CapturedWords, \
    P2CONST(Icu_ValueType,  AUTOMATIC,  ICU_APPL_CONST) pBufferPtr, \
    VAR(boolean,            AUTOMATIC) bOverflow \
)
{
    VAR(uint8, AUTOMATIC) u8Word;
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();
    VAR(Icu_ValueType,  AUTOMATIC) chBufferSize   = sIcu_ChannelInfo[u8Icu_CoreId][Channel].u32Icu_ChannelBufferSize;
    VAR(Icu_ValueType,  AUTOMATIC) chBufferNotify = sIcu_ChannelInfo[u8Icu_CoreId][Channel].u32Icu_ChannelBufferNotify;
    VAR(boolean,        AUTOMATIC) bReturnValue = (boolean)TRUE;
    VAR(Icu_TimestampBufferType, ICU_CODE) timestampBufferProperty;

    Icu_ReportWakeupAndOverflow(Channel, bOverflow);

    SchM_Enter_ICU_CRITICAL_AREA_01();

    for (u8Word = 0U; u8Word < u8CapturedWords; u8Word++)
    {
        sIcu_ChannelInfo[u8Icu_CoreId][Channel].u32Icu_ChannelBuffer[sIcu_ChannelInfo[u8Icu_CoreId][Channel].u32Icu_ChannelBufferIndex] = \
            pBufferPtr[u8Word];
        sIcu_ChannelInfo[u8Icu_CoreId][Channel].u32Icu_ChannelBufferIndex++;

        if (sIcu_ChannelInfo[u8Icu_CoreId][Channel].u32Icu_ChannelBufferIndex >= chBufferSize)
        {
            timestampBufferProperty = sIcu_ChannelInfo[u8Icu_CoreId][Channel].sIcu_ChannelConfig.IcuChannel_TimestampBufferProperty;
            if (ICU_CIRCULAR_BUFFER == timestampBufferProperty)
            {
                sIcu_ChannelInfo[u8Icu_CoreId][Channel].u32Icu_ChannelBufferIndex = 0;
            }
            else if (ICU_LINEAR_BUFFER == timestampBufferProperty)
            {
                /* Linear buffer is full, stop the channel */
#if (ICU_STOPTIMESTAMP_API == STD_ON)
                Icu_Autosar_Wrapper_StopTimestamp(Channel, sIcu_CfgPtr[u8Icu_CoreId]);
#endif
                Icu_SetChannelState(Channel, ICU_CHANNEL_STATE_IDLE);

                /* Stop captured time stamps */
                bReturnValue = (boolean)FALSE;
            }
            else
            {
                /*nothing*/
            }
        }

        if (0U != chBufferNotify)
        {
            sIcu_ChannelInfo[u8Icu_CoreId][Channel].u32Icu_ChannelBufferNotifyCount ++;
            if (sIcu_ChannelInfo[u8Icu_CoreId][Channel].u32Icu_ChannelBufferNotifyCount >= chBufferNotify)
            {
                sIcu_ChannelInfo[u8Icu_CoreId][Channel].u32Icu_ChannelBufferNotifyCount = 0U;
                /* Call User Notification Function and/or Wakeup Function */
                Icu_CallTimestampNotification(Channel);
            }
        }

        if ((boolean)FALSE == bReturnValue)
        {
            break;
        }
    }

    SchM_Exit_ICU_CRITICAL_AREA_01();
#if (ICU_MULTI_CORE == STD_ON)
    Icu_Autosar_Wrapper_SetMultiCoreIrqCompleteState(Channel, 1);
#endif
}

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
FUNC(void,ICU_CODE) Icu_SignalMeasurement \
( \
    VAR(Icu_ChannelType,    AUTOMATIC) Channel, \
    VAR(Icu_ValueType,      AUTOMATIC) activePulseWidth, \
    VAR(Icu_ValueType,      AUTOMATIC) period, \
    VAR(boolean,            AUTOMATIC) bOverflow \
)
{
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();
    SchM_Enter_ICU_CRITICAL_AREA_00();
    {
        sIcu_ChannelInfo[u8Icu_CoreId][Channel].u32Icu_ChannelActiveTime = activePulseWidth;
        sIcu_ChannelInfo[u8Icu_CoreId][Channel].u32Icu_ChannelPeriod = period;
        sIcu_ChannelInfo[u8Icu_CoreId][Channel].u32Icu_ChannelEdgeDetection = ICU_ACTIVE;
    }
    SchM_Exit_ICU_CRITICAL_AREA_00();

    Icu_ReportWakeupAndOverflow(Channel, bOverflow);
    Icu_SetChannelState(Channel, ICU_CHANNEL_STATE_IDLE);
#if (ICU_MULTI_CORE == STD_ON)
    Icu_Autosar_Wrapper_SetMultiCoreIrqCompleteState(Channel, 1);
#endif
}
#endif /* ICU_SIGNAL_MEASUREMENT_API */

#define ICU_STOP_SEC_CODE
#include "Icu_MemMap.h"


#ifdef __cplusplus
}
#endif
