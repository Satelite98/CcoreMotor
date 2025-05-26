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
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           :
*   Build Version        :
*
*****************************************************************************/

/**
*   @file    Gpt_Pit_HAL_Wrapper.h
*   @version 1.0.1
*
*      AUTOSAR 4.4.0 - Common Level Driver source file.
*    Autosar layer of Gpt MCAL driver.
*
*   @addtogroup Gpt
*   @{
*/

#ifndef GPT_PIT_HAL_WRAPPER_H
#define GPT_PIT_HAL_WRAPPER_H

#ifdef __cplusplus
extern "C"{
#endif

/*==============================================INCLUDE FILES=======================================*/
#include "Gpt_Pit_LLDriver.h"

/*=================================== ==SOURCE FILE VERSION INFORMATION==============================*/
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
extern VAR(PIT_ClkFreq, AUTOMATIC) PitClkFreq;
/*============================================DEFINES AND MACROS====================================*/

/*===================================================ENUMS==========================================*/

/*=======================================STRUCTURES AND OTHER TYPEDEFS==============================*/
typedef struct {
    VAR(uint8, GPT_VAR) status;
    VAR(uint32, GPT_VAR) loadValue;
} PIT_ChannelInfo;

typedef struct {
    VAR(uint8, GPT_VAR) status;
    VAR(uint8, GPT_VAR) rtiSatus;
    VAR(PIT_ChannelInfo, GPT_VAR) channel[GPT_PIT_MODULE_CHANNEL_MAX];
} GPT_PIT_ModuleInfo;


typedef struct {
    VAR(GPT_PIT_ModuleInfo, GPT_VAR) module[GPT_PIT_MODULE_MAX];
} GPT_PIT_ModuleMgr;


/*==============================================GLOBAL FUNCTIONS====================================*/
FUNC(void, GPT_CODE) Gpt_Pit_Wrapper_Init   \
(                                           \
    VAR(uint8, AUTOMATIC) u8Pit_HwChannel,  \
    VAR(boolean, AUTOMATIC) bPit_FreezeEnable
#if (GPT_PIT_CHAIN_MODE == STD_ON)
    ,
    VAR(boolean, AUTOMATIC) bGpt_Pit_ChainMode
#endif
);

FUNC(void, GPT_CODE) Gpt_Pit_Wrapper_DeInit \
( 											\
    VAR(uint8, AUTOMATIC) u8Pit_HwChannel 	\
);

FUNC(uint32, GPT_CODE) Gpt_Pit_Wrapper_GetTimeElapsed \
( 																\
    VAR(uint8, AUTOMATIC) u8Pit_HwChannel, 						\
    P2VAR(boolean, AUTOMATIC, GPT_APPL_DATA) pbPit_IsRollover, 	\
    P2VAR(uint32, AUTOMATIC, GPT_APPL_DATA) pu32Pit_TargetValue \
);

FUNC(uint32, GPT_CODE) Gpt_Pit_Wrapper_GetTimeRemaining 	\
( 															\
    VAR(uint8, AUTOMATIC) u8Pit_HwChannel 				    \
);

FUNC(void, GPT_CODE) Gpt_Pit_Wrapper_StartTimer \
( 												\
    VAR(uint8, AUTOMATIC) u8Pit_HwChannel, 	    \
    VAR(uint32, AUTOMATIC) u32Pit_Value 	    \
);

FUNC(void, GPT_CODE) Gpt_Pit_Wrapper_StopTimer  \
( 												\
    VAR(uint8, AUTOMATIC) u8Pit_HwChannel 	    \
);

FUNC(void, GPT_CODE) Gpt_Pit_Wrapper_EnableNotification \
( 														\
    VAR(uint8, AUTOMATIC) u8Pit_HwChannel 						\
);

FUNC(void, GPT_CODE) Gpt_Pit_Wrapper_DisableNotification 	\
( 															\
    VAR(uint8, AUTOMATIC) u8Pit_HwChannel 							\
);


#ifdef __cplusplus
}
#endif

#endif


