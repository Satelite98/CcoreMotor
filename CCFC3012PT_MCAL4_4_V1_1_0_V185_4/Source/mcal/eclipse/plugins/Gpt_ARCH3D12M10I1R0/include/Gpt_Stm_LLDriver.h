/****************************************************************************
*
* Copyright (c) 2023  C*Core -   All Rights Reserved
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* @file     Gpt_Stm_LLDriver.h
* @version  1.0
* @date     2023 - 01 - 01
* @brief    Initial version.
*
*****************************************************************************/
#ifndef GPT_STM_LLDRIVER_H
#define GPT_STM_LLDRIVER_H

#ifdef __cplusplus
extern "C"{
#endif

/*==============================================INCLUDE FILES=======================================*/
/*PRQA S 1534,3472,1535,3630 EOF*/
#include "derivative.h"
#include "StandardTypes.h"
#include "Gpt_Cfg.h"
/*=====================================SOURCE FILE VERSION INFORMATION==============================*/
#define GPT_VENDOR_ID_H                     176
#define GPT_MODULE_ID_H                     100
#define GPT_AR_MAJOR_VER_H                  4
#define GPT_AR_MINOR_VER_H                  4
#define GPT_AR_PATCH_VER_H                  0
#define GPT_SW_MAJOR_VER_H                  1
#define GPT_SW_MINOR_VER_H                  0
#define GPT_SW_PATCH_VER_H                  1

/*============================================FILE VERSION CHECKS===================================*/

#if (GPT_VENDOR_ID_H != GPT_VENDOR_ID)
#error "NON-MATCHED DATA : GPT_CFG_VENDOR_ID"
#endif

#if (GPT_AR_MAJOR_VER_H != GPT_CFG_AR_MAJOR_VER)
#error "NON-MATCHED DATA : GPT_CFG_AR_MAJOR_VER"
#endif
#if (GPT_AR_MINOR_VER_H != GPT_CFG_AR_MINOR_VER)
#error "NON-MATCHED DATA : GPT_CFG_AR_MINOR_VER"
#endif
#if (GPT_AR_PATCH_VER_H != GPT_CFG_AR_PATCH_VER)
#error "NON-MATCHED DATA : GPT_CFG_AR_PATCH_VER"
#endif

#if (GPT_SW_MAJOR_VER_H != GPT_CFG_SW_MAJOR_VER)
#error "NON-MATCHED DATA : GPT_CFG_SW_MAJOR_VER"
#endif
#if (GPT_SW_MINOR_VER_H != GPT_CFG_SW_MINOR_VER)
#error "NON-MATCHED DATA : GPT_CFG_SW_MINOR_VER"
#endif
#if (GPT_SW_PATCH_VER_H != GPT_CFG_SW_PATCH_VER)
#error "NON-MATCHED DATA : GPT_CFG_SW_PATCH_VER"
#endif
/*=================================================Constants========================================*/

/*============================================DEFINES AND MACROS====================================*/

#define STM_0_BASE_ADDR                          ((uint32)&STM_0)
#define STM_1_BASE_ADDR                          ((uint32)&STM_1)
#define STM_2_BASE_ADDR                          ((uint32)&STM_2)
#define STM_3_BASE_ADDR                          ((uint32)&STM_3)
#define STM_4_BASE_ADDR                          ((uint32)&STM_4)
#define STM_5_BASE_ADDR                          ((uint32)&STM_5)
#define STM_0_BASE                               ((STM_tag_Type *)STM_0_BASE_ADDR)
#define STM_1_BASE                               ((STM_tag_Type *)STM_1_BASE_ADDR)
#define STM_2_BASE                               ((STM_tag_Type *)STM_2_BASE_ADDR)
#define STM_3_BASE                               ((STM_tag_Type *)STM_3_BASE_ADDR)
#define STM_4_BASE                               ((STM_tag_Type *)STM_4_BASE_ADDR)
#define STM_5_BASE                               ((STM_tag_Type *)STM_5_BASE_ADDR)
#define STM_BASE_ARRAY                           {STM_0_BASE, STM_1_BASE, STM_2_BASE,STM_3_BASE, STM_4_BASE, STM_5_BASE}

#define STM_INSTANCE_NUM                         6U

#define STM0_CH_NUM                              4U
#define STM1_CH_NUM                              4U
#define STM2_CH_NUM                              4U
#define STM3_CH_NUM                              4U
#define STM4_CH_NUM                              4U
#define STM5_CH_NUM                              4U

#define GPT_STM_MODULE_MAX               		(6U)
#define GPT_STM_CHANNEL_MAX              		(4U)

#define STM_CR_CPS_MASK                          0xff00u
#define STM_CR_CPS_SHIFT                         8u

#define STM_MOD_SHIFT               ((uint8)4U)
#define STM_CH_MASK_U8              ((uint8)0x0FU)

#define STM_MODULE_INDEX_U32(ch)    (((ch) >> STM_MOD_SHIFT) & 0xFU)
#define STM_CHANNEL_INDEX_U32(ch)   ((ch) & STM_CH_MASK_U8)
/*===================================================ENUMS==========================================*/
typedef enum{
    STM0 = 0,
    STM1,
    STM2,
    STM3,
    STM4,
    STM5
}STM_ModuleID_Type;

typedef enum{
    STM_Channel0 = 0,
    STM_Channel1,
    STM_Channel2,
    STM_Channel3
}STM_ChannelID_Type;

typedef enum{
    STM_FREEZEOFF = 0,
    STM_FREEZEON
}STM_DebugMode_Type;

typedef enum{
    STM_Disable = 0,
    STM_Enable
}STM_Std_ReturnTypeype;

/*=======================================STRUCTURES AND OTHER TYPEDEFS==============================*/

typedef  struct STM_tag                          STM_tag_Type;

/*==============================================GLOBAL FUNCTIONS====================================*/
FUNC(STM_ModuleID_Type, GPT_CODE) Gpt_Stm_LLD_ConvertModuleId    
(                                                
   VAR(uint8, AUTOMATIC) u8ModuleId
);

FUNC(STM_ChannelID_Type, GPT_CODE) Gpt_Stm_LLD_ConvertChanId    
(                                                
   VAR(uint8, AUTOMATIC) u8ChannelId
);

FUNC(void, GPT_CODE) Gpt_Stm_IRQHandler \
( \
    VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID, \
    VAR(STM_ChannelID_Type, AUTOMATIC) STM_ChannelID \
);


FUNC(void, GPT_CODE) Gpt_Stm_LLD_Deinit \
(                                       \
    VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID \
);

FUNC(void, GPT_CODE) Gpt_Stm_LLD_ClearIntFlag \
( \
    VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID, \
    VAR(STM_ChannelID_Type, AUTOMATIC) STM_ChannelID
);

FUNC(void, GPT_CODE) Gpt_Stm_LLD_ModuleDisable \
( \
    VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID \
);

FUNC(Std_ReturnType, GPT_CODE) Gpt_Stm_LLD_ModuleEnable \
( \
    VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID \
);

FUNC(void, GPT_CODE) Gpt_Stm_LLD_ChannelEnable \
( \
    VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID, \
    VAR(STM_ChannelID_Type, AUTOMATIC) STM_ChannelID \
);

FUNC(void, GPT_CODE) Gpt_Stm_LLD_ChannelDisable \
( \
    VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID, \
    VAR(STM_ChannelID_Type, AUTOMATIC) STM_ChannelID \
);

FUNC(void, GPT_CODE) Gpt_Stm_LLD_SetCounter \
( \
    VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID, \
    VAR(uint32, AUTOMATIC) value \
);

FUNC(uint32, GPT_CODE) Gpt_Stm_LLD_GetCounter \
( \
    VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID \
);

FUNC(void, GPT_CODE) Gpt_Stm_LLD_SetDebugFreeze      \
(                                                    \
    VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID,  \
    VAR(STM_DebugMode_Type, AUTOMATIC) STM_DebugMode \
);

FUNC(uint8, GPT_CODE) Gpt_Stm_LLD_GetDebugFreeze \
( \
    VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID \
);

FUNC(uint32, GPT_CODE) Gpt_Stm_LLD_GetIntFlag \
( \
    VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID, \
    VAR(STM_ChannelID_Type, AUTOMATIC) STM_ChannelID \
);

FUNC(void, GPT_CODE) Gpt_Stm_LLD_SetCompareValue \
( \
    VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID, \
    VAR(STM_ChannelID_Type, AUTOMATIC) STM_ChannelID, \
    VAR(uint32, AUTOMATIC) CompareValue \
);

FUNC(uint32, GPT_CODE) Gpt_Stm_LLD_GetCompareValue \
( \
    VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID, \
    VAR(STM_ChannelID_Type, AUTOMATIC) STM_ChannelID \
);

FUNC(void, GPT_CODE) Gpt_Stm_LLD_SetPrescaler       \
(                                                   \
    VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID, \
    VAR(uint32, AUTOMATIC) ClockDivision            \
);

FUNC(Std_ReturnType, GPT_CODE) Gpt_STM_LLD_DelayInit \
(                                                    \
    VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID   \
);

FUNC(void, GPT_CODE) Gpt_Stm_LLD_DelayMs \
( \
   VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID, \
   VAR(uint32, AUTOMATIC) ms \
);
FUNC(void, GPT_CODE) Gpt_Stm_LLD_DelayUs \
( \
    VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID, \
    VAR(uint32, AUTOMATIC) us \
);

FUNC(STM_Std_ReturnTypeype, GPT_CODE) Gpt_Stm_LLD_IsModuleEnable \
(                                                                \
    VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID \
);


#ifdef __cplusplus
}
#endif

#endif
