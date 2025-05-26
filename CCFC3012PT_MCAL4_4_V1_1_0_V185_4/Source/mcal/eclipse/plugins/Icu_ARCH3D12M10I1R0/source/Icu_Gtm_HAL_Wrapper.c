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
*   @file    Icu_Gtm_HAL_Wrapper.c
*   @version 
*
*      AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Icu MCAL driver.
*
*   @addtogroup Icu
*   @{
*/

/*====================================================================================================
                                        INCLUDE FILES
====================================================================================================*/
#include "Icu.h"
#include "Icu_Cfg.h"
#include "Icu_Gtm_HAL_Wrapper.h"
#include "Icu_Irq.h"
#include "Icu_Gtm_Wrapper.h"
#include "Icu_Gtm4_Tim_LLDrivers.h"
#include "Gpt_Gtm410_LLDriver.h"
/*====================================================================================================
                                SOURCE FILE VERSION INFORMATION
====================================================================================================*/

/*====================================================================================================
                                        FILE VERSION CHECKS
====================================================================================================*/
#define ICU_GTM_HAL_WRAPPER_VENDOR_ID_C                   176

#define ICU_GTM_HAL_WRAPPER_MAJOR_VER_C                   4
#define ICU_GTM_HAL_WRAPPER_MINOR_VER_C                   4
#define ICU_GTM_HAL_WRAPPER_REVISION_VER_C                0

#define ICU_GTM_HAL_WRAPPER_SW_MAJOR_VER_C                1
#define ICU_GTM_HAL_WRAPPER_SW_MINOR_VER_C                0
#define ICU_GTM_HAL_WRAPPER_SW_PATCH_VER_C                1

#if (ICU_GTM_HAL_WRAPPER_VENDOR_ID_C != ICU_GTM_HAL_WRAPPER_VENDOR_ID_H)
#error "NON-MATCHED DATA : ICU_VENDOR_ID_CFG"
#endif

/* Check if current file and ICU header file are of the same Autosar version */
#if (ICU_GTM_HAL_WRAPPER_MAJOR_VER_C != ICU_GTM_HAL_WRAPPER_MAJOR_VER_H)
#error "NON-MATCHED DATA : ICU_MAJOR_VER_H"
#endif
#if (ICU_GTM_HAL_WRAPPER_MINOR_VER_C != ICU_GTM_HAL_WRAPPER_MINOR_VER_H)
#error "NON-MATCHED DATA : ICU_MINOR_VER_H"
#endif
#if (ICU_GTM_HAL_WRAPPER_REVISION_VER_C != ICU_GTM_HAL_WRAPPER_REVISION_VER_H)
#error "NON-MATCHED DATA : ICU_REVISION_VER_H"
#endif

/* Check if current file and ICU header file are of the same Software version */
#if (ICU_GTM_HAL_WRAPPER_SW_MAJOR_VER_C != ICU_GTM_HAL_WRAPPER_SW_MAJOR_VER_H)
#error "NON-MATCHED DATA : ICU_SW_MAJOR_VER_H"
#endif
#if (ICU_GTM_HAL_WRAPPER_SW_MINOR_VER_C != ICU_GTM_HAL_WRAPPER_SW_MINOR_VER_H)
#error "NON-MATCHED DATA : ICU_SW_MINOR_VER_H"
#endif
#if (ICU_GTM_HAL_WRAPPER_SW_PATCH_VER_C != ICU_GTM_HAL_WRAPPER_SW_PATCH_VER_H)
#error "NON-MATCHED DATA : ICU_SW_PATCH_VER_H"
#endif
/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/
extern VAR(Icu_ChannelInfoType, AUTOMATIC) sIcu_ChannelInfo[ICU_CORE_NUM][ICU_MAX_CHANNEL];

static VAR(GTM_TIM_Channel_ConfigData, ICU_VAR) sIcu_Gtm_ChConfig[ICU_GTM_MODULE_MAX*ICU_GTM_CHANNEL_MAX];

extern P2CONST(Icu_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_CfgPtr[ICU_CORE_NUM];
#ifdef RESORUCE_SUPPORT_GTM104
typedef volatile struct GTM_TIM_tag st_GTM_TIM_tag;
static st_GTM_TIM_tag* g_GTM_TIM_Base[6U] = \
{ \
    GTM_TIM_0_BASE_ADDR, \
    GTM_TIM_1_BASE_ADDR, \
    GTM_TIM_2_BASE_ADDR, \
    GTM_TIM_3_BASE_ADDR, \
    GTM_TIM_4_BASE_ADDR, \
    GTM_TIM_5_BASE_ADDR \
};
#endif /* RESORUCE_SUPPORT_GTM104 */


/*==================================================================================================
*                              NOT AUTOSAR FUNCTION PROTOTYPES
==================================================================================================*/
#define ICU_START_SEC_CODE
#include "Icu_MemMap.h"

LOCAL_INLINE FUNC(void, ICU_CODE) Gtm_SetChConfig
(
    VAR(uint8,      AUTOMATIC) u8Module, \
    VAR(uint8,      AUTOMATIC) u8Channel, \
    VAR(uint32,     AUTOMATIC) u32Mask, \
    VAR(uint32,     AUTOMATIC) u32Value \
)
{
    VAR(uint8, AUTOMATIC) u8ChannelIdx = (uint8)0U;

    u8ChannelIdx = ICU_GTM_MODU_CHAN_COMBIN(u8Module, u8Channel);

    switch (u32Mask)
    {
    case GTM_CONFIG_DATA_INITED:
    {
        sIcu_Gtm_ChConfig[u8ChannelIdx].bits.inited = (uint8)u32Value;
        break;
    }
    case GTM_CONFIG_DATA_MEASMODE:
    {
        sIcu_Gtm_ChConfig[u8ChannelIdx].bits.mode = (uint8)u32Value;
        break;
    }
    case GTM_CONFIG_DATA_OPMODE:
    {
        sIcu_Gtm_ChConfig[u8ChannelIdx].bits.opmode = (uint8)u32Value;
        break;
    }
    case GTM_CONFIG_DATA_DMA:
    {
        sIcu_Gtm_ChConfig[u8ChannelIdx].bits.dma = (uint8)u32Value;
        break;
    }
    case GTM_CONFIG_DATA_PROPERTY:
    {
        sIcu_Gtm_ChConfig[u8ChannelIdx].bits.property = (uint8)u32Value;
        break;
    }
    case GTM_CONFIG_DATA_CLEAR:
    {
        sIcu_Gtm_ChConfig[u8ChannelIdx].data = u32Value;
        break;
    }
    default:
        /*nothing*/
        break;
    }
}

LOCAL_INLINE FUNC(uint32, ICU_CODE) Gtm_GetChConfig
(
    VAR(uint8,      AUTOMATIC) u8Module, \
    VAR(uint8,      AUTOMATIC) u8Channel, \
    VAR(uint32,     AUTOMATIC) u32Mask \
)
{
    VAR(uint32,     AUTOMATIC) u32RetrunValue = (0xFFFFFFFFU);
    VAR(uint8,      AUTOMATIC) u8ChannelIdx = (uint8)0U;

    u8ChannelIdx = ICU_GTM_MODU_CHAN_COMBIN(u8Module, u8Channel);

    switch (u32Mask)
    {
    case GTM_CONFIG_DATA_INITED:
    {
        u32RetrunValue = sIcu_Gtm_ChConfig[u8ChannelIdx].bits.inited;
        break;
    }
    case GTM_CONFIG_DATA_MEASMODE:
    {
        u32RetrunValue = sIcu_Gtm_ChConfig[u8ChannelIdx].bits.mode;
        break;
    }
    case GTM_CONFIG_DATA_OPMODE:
    {
        u32RetrunValue = sIcu_Gtm_ChConfig[u8ChannelIdx].bits.opmode;
        break;
    }
    case GTM_CONFIG_DATA_DMA:
    {
        u32RetrunValue = sIcu_Gtm_ChConfig[u8ChannelIdx].bits.dma;
        break;
    }
    case GTM_CONFIG_DATA_PROPERTY:
    {
        u32RetrunValue = sIcu_Gtm_ChConfig[u8ChannelIdx].bits.property;
        break;
    }
    default:
        /*nothing*/
        break;
    }

    return u32RetrunValue;
}

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
FUNC(void, ICU_CODE) Icu_Wrapper_Init \
( \
    VAR(Icu_Module_Type, AUTOMATIC) u8Icu_ModuleId, \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelId, \
    P2CONST(Gtm_Channel_Config, AUTOMATIC, ICU_APPL_CONST) pGtmChannelConfig \
)
{
    /* Reset channel */
    (void)GTM_TIM_LLD_Ch_RstChannel((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId);
    /* Set channel mode */
    (void)GTM_TIM_LLD_Ch_SetChannelMode((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, pGtmChannelConfig->timMode);
    /* Set source clock */
    (void)GTM_TIM_LLD_Ch_SelectClkSource((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, pGtmChannelConfig->clockSource);

    /* Set GPR input */
    (void)GTM_TIM_LLD_Ch_SelectGPRInput((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, \
        pGtmChannelConfig->GPRInput, pGtmChannelConfig->GPRInput);
    /* Set TBU0 input */
    GTM_TIM_LLD_Channel_SetTBUSel((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, (GTM_TIME_TBU_TS0_Type)pGtmChannelConfig->TBU0Input);
    /* Set Start Edge */
    Icu_Wrapper_SetActivationCondition(u8Icu_ModuleId, u16Icu_ChannelId, pGtmChannelConfig->startEdge);
    /* Set Filter */
    if (pGtmChannelConfig->filterEnable == (boolean)TRUE)
    {
    	(void)GTM_TIM_LLD_Ch_SelFLCountFall((GTM_TIM_Type)u8Icu_ModuleId,(GTM_TIM_Channel_Type) u16Icu_ChannelId, pGtmChannelConfig->fallCounterFilterMode);
    	(void)GTM_TIM_LLD_Ch_SelFLCountRise((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, pGtmChannelConfig->riseCounterFilterMode);
    	(void)GTM_TIM_LLD_ChSelFLModeFallEdge((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, pGtmChannelConfig->fallEdgeFilterMode);
    	(void)GTM_TIM_LLD_ChSelFLModeRiseEdge((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, pGtmChannelConfig->riseEdgeFilterMode);
    	(void)GTM_TIM_LLD_Ch_SetFLCounFreq((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, pGtmChannelConfig->filterCounterFrequency);
    	(void)GTM_TIM_LLD_Channel_SetFPFE((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, pGtmChannelConfig->filterParamFallEdge);
    	(void)GTM_TIM_LLD_Channel_SetFPRE((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, pGtmChannelConfig->filterParamRiseEdge);
    	(void)GTM_TIM_LLD_Ch_IsEnableFL((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, GPT_GTM_Enable);
    }
    else
    {
        /* default Disable */
    }
    /* Disable interrupt */
    (void)GTM_TIM_LLD_Ch_IsEnableIntcEN((GTM_TIM_Type)u8Icu_ModuleId,  (GTM_TIM_Channel_Type)u16Icu_ChannelId, GPT_GTM_Disable);
}

FUNC(void, ICU_CODE) Icu_Wrapper_ConfigInit \
( \
    VAR(Icu_Module_Type, AUTOMATIC) u8Icu_ModuleId, \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelId, \
    P2CONST(Gtm_Channel_Config, AUTOMATIC, ICU_APPL_CONST) pGtmChannelConfig \
)
{
    (void)pGtmChannelConfig;
    /* Channel inited */
    Gtm_SetChConfig(u8Icu_ModuleId, (uint8)u16Icu_ChannelId, GTM_CONFIG_DATA_INITED, 1U);
}

FUNC(void, ICU_CODE) Icu_Wrapper_DeInit \
( \
    VAR(Icu_Module_Type, AUTOMATIC) u8Icu_ModuleId, \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelId \
)
{
    (void)GTM_TIM_LLD_Ch_IsEnableChannel((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, GPT_GTM_Disable);
    /* Reset channel */
    (void)GTM_TIM_LLD_Ch_RstChannel((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId);
    /* Clear config data */
    Gtm_SetChConfig(u8Icu_ModuleId, (uint8)u16Icu_ChannelId, (uint32)GTM_CONFIG_DATA_CLEAR, 0U);
}

FUNC(void, ICU_CODE) Icu_Wrapper_EnIrq \
( \
    VAR(Icu_Module_Type, AUTOMATIC) u8Icu_ModuleId, \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelId \
)
{
	(void)GTM_TIM_LLD_Ch_IsEnableChannel((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, GPT_GTM_Enable);
    (void)GTM_TIM_LLD_Ch_IsEnableIntcEN((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, GPT_GTM_Enable);
}

FUNC(void, ICU_CODE) Icu_Wrapper_DisIrq \
( \
    VAR(Icu_Module_Type, AUTOMATIC) u8Icu_ModuleId, \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelId \
)
{
	(void)GTM_TIM_LLD_Channel_ClearInterruptNOTIFY((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId);
	(void)GTM_TIM_LLD_Ch_IsEnableChannel((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, GPT_GTM_Disable);
	(void)GTM_TIM_LLD_Ch_IsEnableIntcEN((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, GPT_GTM_Disable);
}

FUNC(void, ICU_CODE) Icu_Wrapper_SetActivationCondition \
( \
    VAR(Icu_Module_Type, AUTOMATIC) u8Icu_ModuleId, \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelId, \
    VAR(GTM_TIM_Edge_Type, AUTOMATIC) eIcu_Activation \
)
{
    SchM_Enter_ICU_EXCLUSIVE_AREA_20();

    switch(eIcu_Activation)
    {
    case ICU_GTM_TIM_EDGE_FALLING:
    case ICU_GTM_TIM_EDGE_RISING:
    {
        (void)GTM_TIM_LLD_Channel_CTRL_ISL((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, (Icu_ValueType)0);
        (void)GTM_TIM_LLD_Channel_ActivationEdge((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, (uint32)eIcu_Activation);
        break;
    }
    case ICU_GTM_TIM_EDGE_BOTH:
    {
        (void)GTM_TIM_LLD_Channel_CTRL_ISL((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, (Icu_ValueType)1);
        (void)GTM_TIM_LLD_Channel_ActivationEdge((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, (uint32)0);
        break;
    }
    default:
        /* nothing to do */
        break;
    }

    SchM_Exit_ICU_EXCLUSIVE_AREA_20();
}

FUNC(void, ICU_CODE) Icu_Wrapper_StartTimestamp
( \
    VAR(Icu_Module_Type, AUTOMATIC) u8Icu_ModuleId, \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelId, \
    VAR(boolean, AUTOMATIC) bDmaSupport \
)
{
    SchM_Enter_ICU_EXCLUSIVE_AREA_21();

    (void)GTM_TIM_LLD_Channel_ClearInterruptNOTIFY((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId);
    (void)GTM_TIM_LLD_Ch_IsEnableIntc((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, TIM_IRQ_NEWVAL, GPT_GTM_Enable);
    (void)GTM_TIM_LLD_Ch_IsEnableChannel((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, GPT_GTM_Enable);
    if (bDmaSupport == (boolean)TRUE)
    {
        Gtm_SetChConfig(u8Icu_ModuleId, (uint8)u16Icu_ChannelId,\
            GTM_CONFIG_DATA_MEASMODE, GTM_TIM_MODE_TIMESTAMP_WITH_DMA);
    }
    else
    {
        Gtm_SetChConfig(u8Icu_ModuleId, (uint8)u16Icu_ChannelId,\
            GTM_CONFIG_DATA_MEASMODE, GTM_TIM_MODETIMESTAMP_NO_DMA);
    }

    SchM_Exit_ICU_EXCLUSIVE_AREA_21();
}

FUNC(void, ICU_CODE) Icu_Wrapper_StopTimestamp \
( \
    VAR(Icu_Module_Type, AUTOMATIC) u8Icu_ModuleId, \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelId, \
    VAR(GPT_GTM_Status_Type, AUTOMATIC) eIcu_GTMIsEnable \
)
{
    (void)eIcu_GTMIsEnable;
    VAR(uint32,     AUTOMATIC) u32ConfigData = (uint32)0U;

    SchM_Enter_ICU_EXCLUSIVE_AREA_22();

    (void)GTM_TIM_LLD_Ch_IsEnableIntc((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, TIM_IRQ_NEWVAL, GPT_GTM_Disable);
    (void)GTM_TIM_LLD_Ch_IsEnableChannel((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, GPT_GTM_Disable);

    /* Clear Channel meas mode */
    u32ConfigData = Gtm_GetChConfig(u8Icu_ModuleId, (uint8)u16Icu_ChannelId, (uint32)GTM_CONFIG_DATA_MEASMODE);
    u32ConfigData &= ~(GTM_TIM_MODETIMESTAMP_NO_DMA | GTM_TIM_MODE_TIMESTAMP_WITH_DMA);
    Gtm_SetChConfig(u8Icu_ModuleId, (uint8)u16Icu_ChannelId, \
            (uint32)GTM_CONFIG_DATA_MEASMODE, \
            (uint32)u32ConfigData);

    SchM_Exit_ICU_EXCLUSIVE_AREA_22();
}

FUNC(void, ICU_CODE) Icu_Wrapper_ResetEdgeCount \
( \
    VAR(Icu_Module_Type, AUTOMATIC) u8Icu_ModuleId, \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelId, \
    VAR(GPT_GTM_Status_Type, AUTOMATIC) eIcu_GTMIsEnable \
)
{
    (void)eIcu_GTMIsEnable;
    SchM_Enter_ICU_EXCLUSIVE_AREA_23();
    (void)GTM_TIM_LLD_Ch_IsEnableChannel((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, GPT_GTM_Disable);
    (void)GTM_TIM_LLD_Ch_IsEnableChannel((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, GPT_GTM_Enable);
    SchM_Exit_ICU_EXCLUSIVE_AREA_23();
}

FUNC(void, ICU_CODE) Icu_Wrapper_EnableEdgeCount \
( \
    VAR(Icu_Module_Type, AUTOMATIC) u8Icu_ModuleId, \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelId
)
{
    VAR(uint32,                 AUTOMATIC) u32ConfigData = 0U;
    SchM_Enter_ICU_EXCLUSIVE_AREA_24();
    (void)GTM_TIM_LLD_Channel_ClearInterruptNOTIFY((GTM_TIM_Type)u8Icu_ModuleId,(GTM_TIM_Channel_Type) u16Icu_ChannelId);
    (void)GTM_TIM_LLD_Ch_IsEnableIntc((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, TIM_IRQ_CNTOFL, GPT_GTM_Enable);
    u32ConfigData = Gtm_GetChConfig(u8Icu_ModuleId, (uint8)u16Icu_ChannelId, (uint32)GTM_CONFIG_DATA_MEASMODE);
    u32ConfigData |= (GTM_TIM_MODE_EDGE_COUNTER);
    Gtm_SetChConfig(u8Icu_ModuleId, (uint8)u16Icu_ChannelId, \
            (uint32)GTM_CONFIG_DATA_MEASMODE, \
            (uint32)u32ConfigData);
    (void)GTM_TIM_LLD_Ch_IsEnableChannel((GTM_TIM_Type)u8Icu_ModuleId,(GTM_TIM_Channel_Type)u16Icu_ChannelId, GPT_GTM_Enable);
    SchM_Exit_ICU_EXCLUSIVE_AREA_24();
}

FUNC(void, ICU_CODE) Icu_Wrapper_DisableEdgeCount \
( \
    VAR(Icu_Module_Type, AUTOMATIC) u8Icu_ModuleId, \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelId
)
{
    SchM_Enter_ICU_EXCLUSIVE_AREA_25();
    (void)GTM_TIM_LLD_Ch_IsEnableChannel((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, GPT_GTM_Disable);
    (void)GTM_TIM_LLD_Ch_ClearIntcFlag((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, TIM_IRQ_NEWVAL);
    (void)GTM_TIM_LLD_Ch_IsEnableIntc((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, TIM_IRQ_CNTOFL, GPT_GTM_Disable);
    SchM_Exit_ICU_EXCLUSIVE_AREA_25();
}

FUNC(Icu_EdgeNumberType, ICU_CODE) Icu_Wrapper_GetEdgeNumbers \
( \
    VAR(Icu_Module_Type, AUTOMATIC) u8Icu_ModuleId, \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelId \
)
{
    VAR(Icu_EdgeNumberType, AUTOMATIC) u16Icu_EdgeNumbers = 0U;

    u16Icu_EdgeNumbers = (Icu_EdgeNumberType)GTM_TIM_LLD_Ch_GetGPR1Parameter( \
    		(GTM_TIM_Type)u8Icu_ModuleId, \
			(GTM_TIM_Channel_Type)u16Icu_ChannelId);

    return u16Icu_EdgeNumbers;
}

FUNC(void, ICU_CODE) Icu_Wrapper_EnableEdgeDetection \
( \
    VAR(Icu_Module_Type, AUTOMATIC) u8Icu_ModuleId, \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelId, \
    VAR(GPT_GTM_Status_Type, AUTOMATIC) eIcu_GTMIsEnable \
)
{
    (void)eIcu_GTMIsEnable;
    VAR(GTM_TIM_Interrupt_Type, AUTOMATIC) eIcu_GTMTimIntc = TIM_IRQ_NEWVAL;
    VAR(uint32,                 AUTOMATIC) u32ConfigData = 0U;

    SchM_Enter_ICU_EXCLUSIVE_AREA_26();

    (void)GTM_TIM_LLD_Ch_ClearIntcFlag((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, eIcu_GTMTimIntc);
    (void)GTM_TIM_LLD_Ch_IsEnableIntc((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId,eIcu_GTMTimIntc, GPT_GTM_Enable);
    (void)GTM_TIM_LLD_Ch_IsEnableChannel((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, GPT_GTM_Enable);

    u32ConfigData = Gtm_GetChConfig(u8Icu_ModuleId, (uint8)u16Icu_ChannelId, (uint32)GTM_CONFIG_DATA_MEASMODE);
    u32ConfigData |= (GTM_TIM_MODE_SIGNAL_EDGE_DETECT);
    Gtm_SetChConfig(u8Icu_ModuleId, (uint8)u16Icu_ChannelId, \
            (uint32)GTM_CONFIG_DATA_MEASMODE, \
            (uint32)u32ConfigData);

    SchM_Exit_ICU_EXCLUSIVE_AREA_26();
}

FUNC(void, ICU_CODE) Icu_Wrapper_DisableEdgeDetection \
( \
    VAR(Icu_Module_Type, AUTOMATIC) u8Icu_ModuleId, \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelId, \
    VAR(GPT_GTM_Status_Type, AUTOMATIC) eIcu_GTMIsEnable \
)
{
    (void)eIcu_GTMIsEnable;
    VAR(GTM_TIM_Interrupt_Type, AUTOMATIC) eIcu_GTMTimIntc = TIM_IRQ_NEWVAL;
    VAR(uint32,                 AUTOMATIC) u32ConfigData = 0U;

    SchM_Enter_ICU_EXCLUSIVE_AREA_27();

    (void)GTM_TIM_LLD_Ch_IsEnableIntc((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId,eIcu_GTMTimIntc, GPT_GTM_Disable);
    (void)GTM_TIM_LLD_Ch_IsEnableChannel((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, GPT_GTM_Disable);

    /* Clear Channel meas mode */
    u32ConfigData = Gtm_GetChConfig(u8Icu_ModuleId, (uint8)u16Icu_ChannelId, (uint32)GTM_CONFIG_DATA_MEASMODE);
    u32ConfigData &= ~(GTM_TIM_MODE_SIGNAL_EDGE_DETECT);
    Gtm_SetChConfig(u8Icu_ModuleId, (uint8)u16Icu_ChannelId, \
            (uint32)GTM_CONFIG_DATA_MEASMODE, \
            (uint32)u32ConfigData);

    SchM_Exit_ICU_EXCLUSIVE_AREA_27();
}

FUNC(void, ICU_CODE) Icu_Wrapper_StartSignalMeasurement \
( \
    VAR(Icu_Module_Type, AUTOMATIC) u8Icu_ModuleId, \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelId, \
    VAR(uint16,          AUTOMATIC) nMeasProperty, \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelNumber \
)
{
	(void)u16Icu_ChannelNumber;
    VAR(uint32, AUTOMATIC) u32ConfigData = 0U;

    SchM_Enter_ICU_EXCLUSIVE_AREA_28();

    (void)GTM_TIM_LLD_Channel_ClearInterruptNOTIFY((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId);
    (void)GTM_TIM_LLD_Ch_IsEnableIntcEN((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, GPT_GTM_Enable);
    (void)GTM_TIM_LLD_Ch_IsEnableIntc((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, TIM_IRQ_CNTOFL, GPT_GTM_Enable);
    (void)GTM_TIM_LLD_Ch_IsEnableIntc((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, TIM_IRQ_NEWVAL, GPT_GTM_Enable);
    (void)GTM_TIM_LLD_Ch_IsEnableChannel((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, GPT_GTM_Enable);

    u32ConfigData = Gtm_GetChConfig(u8Icu_ModuleId, (uint8)u16Icu_ChannelId, (uint32)GTM_CONFIG_DATA_MEASMODE);
    u32ConfigData |= (GTM_TIM_MODE_SIGNAL_MEASUREMENT);
    Gtm_SetChConfig(u8Icu_ModuleId, (uint8)u16Icu_ChannelId, \
            (uint32)GTM_CONFIG_DATA_MEASMODE, \
            (uint32)u32ConfigData);
    Gtm_SetChConfig(u8Icu_ModuleId, (uint8)u16Icu_ChannelId,
            (uint32)GTM_CONFIG_DATA_PROPERTY,
            (uint32)nMeasProperty);

    SchM_Exit_ICU_EXCLUSIVE_AREA_28();
}

FUNC(void, ICU_CODE) Icu_Wrapper_StopSignalMeasurement \
( \
    VAR(Icu_Module_Type, AUTOMATIC) u8Icu_ModuleId, \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelId, \
    VAR(GPT_GTM_Status_Type, AUTOMATIC) eIcu_GTMIsEnable \
)
{
    (void)eIcu_GTMIsEnable;
    VAR(uint32, AUTOMATIC) u32ConfigData = 0U;
    SchM_Enter_ICU_EXCLUSIVE_AREA_29();

    (void)GTM_TIM_LLD_Ch_IsEnableIntcEN((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, GPT_GTM_Disable);
    (void)GTM_TIM_LLD_Ch_IsEnableIntcNOTIFY((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, GPT_GTM_Disable);

    /* Clear Measure type */
    u32ConfigData = Gtm_GetChConfig(u8Icu_ModuleId,(uint8) u16Icu_ChannelId, (uint32)GTM_CONFIG_DATA_MEASMODE);
    u32ConfigData &= ~(GTM_TIM_MODE_SIGNAL_MEASUREMENT);
    Gtm_SetChConfig(u8Icu_ModuleId, (uint8)u16Icu_ChannelId, \
            (uint32)GTM_CONFIG_DATA_MEASMODE, \
            (uint32)u32ConfigData);

    SchM_Exit_ICU_EXCLUSIVE_AREA_29();
}

FUNC(Icu_InputStateType, ICU_CODE) Icu_Wrapper_GetInputState \
( \
    VAR(Icu_Module_Type, AUTOMATIC) u8Icu_ModuleId, \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelId \
)
{
    VAR(boolean, AUTOMATIC) bResult = (boolean)FALSE;
    /* GetCoreID */
    if ((sIcu_ChannelInfo[GetCoreID()][ICU_GTM_MODU_CHAN_COMBIN(u8Icu_ModuleId, (uint8)u16Icu_ChannelId)].u32Icu_ChannelEdgeDetection == ICU_ACTIVE) || \
        (GTM_TIM_LLD_Ch_GetInterruptFlag((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, TIM_IRQ_NEWVAL) != 0U) || \
        (GTM_TIM_LLD_Ch_GetInterruptFlag((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, TIM_IRQ_ECNTOFL) != 0U))
    {
        SchM_Enter_ICU_EXCLUSIVE_AREA_30();

        bResult = (boolean)TRUE;
        (void)GTM_TIM_LLD_Ch_ClearIntcFlag((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, TIM_IRQ_NEWVAL);
        (void)GTM_TIM_LLD_Ch_ClearIntcFlag((GTM_TIM_Type)u8Icu_ModuleId, (GTM_TIM_Channel_Type)u16Icu_ChannelId, TIM_IRQ_ECNTOFL);

        SchM_Exit_ICU_EXCLUSIVE_AREA_30();
    }

    return (bResult != FALSE) ? (Icu_InputStateType)TRUE : (Icu_InputStateType)FALSE;
}

FUNC(uint32, ICU_CODE) Icu_Wrapper_GetStartAddress \
( \
    VAR(Icu_Module_Type, AUTOMATIC) u8Icu_ModuleId, \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelId \
)
{
    return GTM_TIM_LLD_Channel_GetAddress((GTM_TIM_Type)u8Icu_ModuleId,  (GTM_TIM_Channel_Type)u16Icu_ChannelId);
}

FUNC(boolean, ICU_CODE) Icu_Wrapper_GetOverFlow \
( \
    VAR(Icu_Module_Type, AUTOMATIC) u8Icu_ModuleId, \
    VAR(Icu_ChannelType, AUTOMATIC) u16Icu_ChannelId \
)
{
    VAR(boolean, AUTOMATIC) bRetrunValue = (boolean)FALSE;

    if (GTM_TIM_LLD_Ch_GetInterruptFlag((GTM_TIM_Type)u8Icu_ModuleId,  (GTM_TIM_Channel_Type)u16Icu_ChannelId, TIM_IRQ_CNTOFL) != 0U)
    {
        bRetrunValue = (boolean)TRUE;
    }

    return bRetrunValue;
}


#define ICU_STOP_SEC_CODE
#include "Icu_MemMap.h"

LOCAL_INLINE FUNC(void, ICU_CODE) Gtm_Channel_SignalMeasurement
(
    VAR(uint8, AUTOMATIC) ModuleId, \
    VAR(uint8, AUTOMATIC) Channel \
)
{
    VAR(uint32,  AUTOMATIC) eMeasProperty;
    VAR(Icu_ChannelType,                    AUTOMATIC) u16Channel = \
        (Icu_ChannelType)Icu_Gtm_Wrapper_GetInstance(ModuleId, Channel);
    VAR(uint8,ICU_VAR) u8Icu_CoreId = (uint8)GetCoreID();

    eMeasProperty = Gtm_GetChConfig(ModuleId, Channel, (uint32)GTM_CONFIG_DATA_PROPERTY);
    SchM_Enter_ICU_EXCLUSIVE_AREA_04();
    switch (eMeasProperty)
    {
    case GTM_TIM_MEAS_TYPE_DUTY_CYCLE:
    {
        sIcu_ChannelInfo[u8Icu_CoreId][u16Channel].u32Icu_ChannelPeriod \
            = GTM_TIM_LLD_Ch_GetGPR1Parameter((GTM_TIM_Type)ModuleId,(GTM_TIM_Channel_Type)Channel);
        sIcu_ChannelInfo[u8Icu_CoreId][u16Channel].u32Icu_ChannelActiveTime \
            = GTM_TIM_LLD_Ch_GetGPR0Param((GTM_TIM_Type)ModuleId,(GTM_TIM_Channel_Type)Channel);
        break;
    }
    case GTM_TIM_MEAS_TYPE_LOW_TIME:
    {
    	if(sIcu_CfgPtr[u8Icu_CoreId]->Icu_GtmConfig->pGtmChannelConfig[u16Channel].IcuChannel_DefaultStartEdge == ICU_FALLING_EDGE)
    	{
    		sIcu_ChannelInfo[u8Icu_CoreId][u16Channel].u32Icu_ChannelActiveTime \
    		            = GTM_TIM_LLD_Ch_GetGPR0Param((GTM_TIM_Type)ModuleId,(GTM_TIM_Channel_Type)Channel);
    	}
    	else
    	{
    		sIcu_ChannelInfo[u8Icu_CoreId][u16Channel].u32Icu_ChannelActiveTime \
			    =(GTM_TIM_LLD_Ch_GetGPR1Parameter((GTM_TIM_Type)ModuleId,(GTM_TIM_Channel_Type)Channel)) \
                - (GTM_TIM_LLD_Ch_GetGPR0Param((GTM_TIM_Type)ModuleId,(GTM_TIM_Channel_Type)Channel));
    	}
    	break;
    }
    case GTM_TIM_MEAS_TYPE_HIGH_TIME:
    {
    	if(sIcu_CfgPtr[u8Icu_CoreId]->Icu_GtmConfig->pGtmChannelConfig[u16Channel].IcuChannel_DefaultStartEdge == ICU_RISING_EDGE)
    	{
    		sIcu_ChannelInfo[u8Icu_CoreId][u16Channel].u32Icu_ChannelActiveTime \
    		            = GTM_TIM_LLD_Ch_GetGPR0Param((GTM_TIM_Type)ModuleId,(GTM_TIM_Channel_Type)Channel);
    	}
    	else
    	{
    		sIcu_ChannelInfo[u8Icu_CoreId][u16Channel].u32Icu_ChannelActiveTime \
			    =(GTM_TIM_LLD_Ch_GetGPR1Parameter((GTM_TIM_Type)ModuleId,(GTM_TIM_Channel_Type)Channel)) \
                - (GTM_TIM_LLD_Ch_GetGPR0Param((GTM_TIM_Type)ModuleId,(GTM_TIM_Channel_Type)Channel));
    	}
        break;
    }
    default:
    {
        sIcu_ChannelInfo[u8Icu_CoreId][u16Channel].u32Icu_ChannelPeriod \
            = GTM_TIM_LLD_Ch_GetGPR1Parameter((GTM_TIM_Type)ModuleId,(GTM_TIM_Channel_Type)Channel);
        break;
    }

    }
    sIcu_ChannelInfo[u8Icu_CoreId][u16Channel].u32Icu_ChannelEdgeDetection = ICU_ACTIVE;
    SchM_Exit_ICU_EXCLUSIVE_AREA_04();
}

LOCAL_INLINE FUNC(void, ICU_CODE) Gtm_Channel_TimeStamp
(
    VAR(uint8, AUTOMATIC) ModuleId, \
    VAR(uint8, AUTOMATIC) Channel \
)
{
    VAR(uint32,                     AUTOMATIC) u32GPR0Temp = \
        GTM_TIM_LLD_Ch_GetGPR0Param((GTM_TIM_Type)ModuleId, (GTM_TIM_Channel_Type)Channel);
    VAR(Icu_ChannelType,            AUTOMATIC) u16Channel = \
        (Icu_ChannelType)Icu_Gtm_Wrapper_GetInstance(ModuleId, Channel);

    ICU_AutoSAR_Wapper_Timestamp(u16Channel, 1, &u32GPR0Temp, FALSE);
}

LOCAL_INLINE FUNC (void, ICU_CODE) Gtm_Wrapper_Channel_ReportWakeupAndOverflow
(
    VAR(uint8,          AUTOMATIC) u8Module, \
    VAR(uint8,          AUTOMATIC) u8Channel, \
    VAR(boolean,        AUTOMATIC) bOverflow \
)
{
    VAR(Icu_ChannelType, ICU_VAR) Instance = ICU_ATS_Gtm_Wapper_GetInstance(u8Module, u8Channel);

    ICU_ReportWakeupAndOverflow(Instance, bOverflow);
}

LOCAL_INLINE FUNC (void, ICU_CODE) Gtm_Wrapper_Channel_ReportEvents
(
    VAR(uint8,          AUTOMATIC) u8Module, \
    VAR(uint8,          AUTOMATIC) u8Channel, \
    VAR(boolean,        AUTOMATIC) bOverflow \
)
{
    VAR(Icu_ChannelType, ICU_VAR) Instance = ICU_ATS_Gtm_Wapper_GetInstance(u8Module, u8Channel);

    ICU_AutoSAR_Wapper_ReportEvents(Instance, bOverflow);
}

FUNC(void, ICU_CODE) Icu_Gtm_ProcessInterrupt \
( \
    VAR(GTM_TIM_Type,       AUTOMATIC)ModuleId, \
    VAR(Icu_ChannelType,    AUTOMATIC) Channel \
)
{
    VAR(uint32,             AUTOMATIC) eMeasMode;
    VAR(boolean,            AUTOMATIC) bOverflow = (boolean)FALSE;
    VAR(boolean,            AUTOMATIC) bNewValue = (boolean)FALSE;
    uint32_t* pIrqNotify;

#ifdef RESORUCE_SUPPORT_GTM410

    pIrqNotify = (uint32_t*)&(GTM4.GLS[ModuleId].TIM.CH[Channel].IRQ_NOTIFY.R);
	
#elif  RESORUCE_SUPPORT_GTM104

    P2CONST(st_GTM_TIM_tag, ICU_VAR, ICU_APPL_CONST) GTM_TIM_Reg_n = g_GTM_TIM_Base[ModuleId];
    pIrqNotify = (uint32*)((uint32)(&GTM_TIM_Reg_n->CH0_IRQ_NOTIFY.R) + (0x80u * (uint8)Channel));

#endif /* RESORUCE_SUPPORT_GTM410 */

    bOverflow = (boolean)((*pIrqNotify >> 2) & 0x1);
    bNewValue = (boolean)(*pIrqNotify & 0x1);
    *pIrqNotify = 0xFF;

    eMeasMode = Gtm_GetChConfig((uint8)ModuleId, (uint8)Channel, (uint32)GTM_CONFIG_DATA_MEASMODE);

    switch (eMeasMode)
    {
        case GTM_TIM_MODE_SIGNAL_MEASUREMENT:
        {
            if(bNewValue == TRUE)
            {
                Gtm_Channel_SignalMeasurement((uint8)ModuleId, (uint8)Channel);
            }
            break;
        }
        case GTM_TIM_MODETIMESTAMP_NO_DMA:
        {
            Gtm_Channel_TimeStamp((uint8)ModuleId, (uint8)Channel);
            break;
        }
        case GTM_TIM_MODE_SIGNAL_EDGE_DETECT:
        {
            Gtm_Wrapper_Channel_ReportEvents((uint8)ModuleId, (uint8)Channel, (boolean)FALSE);
            break;
        }
        case GTM_TIM_MODE_TIMESTAMP_WITH_DMA:
        {
            Gtm_Wrapper_Channel_ReportWakeupAndOverflow((uint8)ModuleId, (uint8)Channel, bOverflow);
            break;
        }
        case GTM_TIM_MODE_EDGE_COUNTER:
        {
            Gtm_Wrapper_Channel_ReportWakeupAndOverflow((uint8)ModuleId, (uint8)Channel, bOverflow);
            break;
        }
        default:
        {
            /* nothing to do */
            break;
        }
    }
}

FUNC(boolean, ICU_CODE) Gtm_Channel_GetInputLevel \
( \
    VAR(uint8,  AUTOMATIC) u8Module, \
    VAR(uint8,  AUTOMATIC) u8Channel \
)
{
    VAR(boolean, AUTOMATIC) bRetrunValue = (boolean)FALSE;

    bRetrunValue = (boolean)((GTM_TIM_LLD_Channel_GetGPR0EdgeCounter((GTM_TIM_Type)u8Module, 
        (GTM_TIM_Channel_Type)u8Channel) & 0x1U) != 0U) ? (boolean)TRUE : (boolean)FALSE;

    return bRetrunValue;
}

FUNC(uint32, ICU_CODE) Gtm_Channel_GetGPR0Value \
( \
    VAR(uint8,  AUTOMATIC) u8Module, \
    VAR(uint8,  AUTOMATIC) u8Channel \
)
{
    VAR(uint32, AUTOMATIC) u32RetrunValue = (uint32)0U;

    u32RetrunValue = (uint32)(GTM_TIM_LLD_Ch_GetGPR0Param((GTM_TIM_Type)u8Module, \
        (GTM_TIM_Channel_Type)u8Channel));

    return u32RetrunValue;
}

