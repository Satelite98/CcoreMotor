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
*   @file    Gpt_Irq.h
*   @version 1.0.1
*
*      AUTOSAR 4.4.0 - Common Level Driver source file.
*    Autosar layer of Gpt MCAL driver.
*
*   @addtogroup Gpt
*   @{
*/

#ifndef GPT_IRQ_H
#define GPT_IRQ_H

#ifdef __cplusplus
extern "C"{
#endif

/*==============================================INCLUDE FILES=======================================*/
#include "StandardTypes.h"
#include "intc_lld.h"

#include "Gpt_Stm_HAL_Wrapper.h"
#include "Gpt_Pit_HAL_Wrapper.h"
#include "Gpt_Gtm_HAL_Wrapper.h"

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

/*===================================================ENUMS==========================================*/

/*=======================================STRUCTURES AND OTHER TYPEDEFS==============================*/

/*==============================================GLOBAL FUNCTIONS====================================*/

FUNC(void, GPT_CODE) STM0_CH0_Handler(void);
FUNC(void, GPT_CODE) STM0_CH1_Handler(void);
FUNC(void, GPT_CODE) STM0_CH2_Handler(void);
FUNC(void, GPT_CODE) STM0_CH3_Handler(void);
FUNC(void, GPT_CODE) STM1_CH0_Handler(void);
FUNC(void, GPT_CODE) STM1_CH1_Handler(void);
FUNC(void, GPT_CODE) STM1_CH2_Handler(void);
FUNC(void, GPT_CODE) STM1_CH3_Handler(void);
FUNC(void, GPT_CODE) STM2_CH0_Handler(void);
FUNC(void, GPT_CODE) STM2_CH1_Handler(void);
FUNC(void, GPT_CODE) STM2_CH2_Handler(void);
FUNC(void, GPT_CODE) STM2_CH3_Handler(void);
FUNC(void, GPT_CODE) STM3_CH0_Handler(void);
FUNC(void, GPT_CODE) STM3_CH1_Handler(void);
FUNC(void, GPT_CODE) STM3_CH2_Handler(void);
FUNC(void, GPT_CODE) STM3_CH3_Handler(void);
FUNC(void, GPT_CODE) STM4_CH0_Handler(void);
FUNC(void, GPT_CODE) STM4_CH1_Handler(void);
FUNC(void, GPT_CODE) STM4_CH2_Handler(void);
FUNC(void, GPT_CODE) STM4_CH3_Handler(void);
FUNC(void, GPT_CODE) STM5_CH0_Handler(void);
FUNC(void, GPT_CODE) STM5_CH1_Handler(void);
FUNC(void, GPT_CODE) STM5_CH2_Handler(void);
FUNC(void, GPT_CODE) STM5_CH3_Handler(void);

FUNC(void, GPT_CODE) PIT0_CH0_ISR(void);
FUNC(void, GPT_CODE) PIT0_CH1_ISR(void);
FUNC(void, GPT_CODE) PIT0_CH2_ISR(void);
FUNC(void, GPT_CODE) PIT0_CH3_ISR(void);
FUNC(void, GPT_CODE) PIT0_CH4_ISR(void);
FUNC(void, GPT_CODE) PIT0_CH5_ISR(void);
FUNC(void, GPT_CODE) PIT0_CH6_ISR(void);
FUNC(void, GPT_CODE) PIT0_CH7_ISR(void);
FUNC(void, GPT_CODE) PIT1_CH0_ISR(void);
FUNC(void, GPT_CODE) PIT1_CH1_ISR(void);
FUNC(void, GPT_CODE) RTI_ISR(void);


FUNC(void, GPT_CODE) TOM0_CH0_CH1_ISR(void);
FUNC(void, GPT_CODE) TOM0_CH2_CH3_ISR(void);
FUNC(void, GPT_CODE) TOM0_CH4_CH5_ISR(void);
FUNC(void, GPT_CODE) TOM0_CH6_CH7_ISR(void);
FUNC(void, GPT_CODE) TOM0_CH8_CH9_ISR(void);
FUNC(void, GPT_CODE) TOM0_CH10_CH11_ISR(void);
FUNC(void, GPT_CODE) TOM0_CH12_CH13_ISR(void);
FUNC(void, GPT_CODE) TOM0_CH14_CH15_ISR(void);

FUNC(void, GPT_CODE) TOM1_CH0_CH1_ISR(void);
FUNC(void, GPT_CODE) TOM1_CH2_CH3_ISR(void);
FUNC(void, GPT_CODE) TOM1_CH4_CH5_ISR(void);
FUNC(void, GPT_CODE) TOM1_CH6_CH7_ISR(void);
FUNC(void, GPT_CODE) TOM1_CH8_CH9_ISR(void);
FUNC(void, GPT_CODE) TOM1_CH10_CH11_ISR(void);
FUNC(void, GPT_CODE) TOM1_CH12_CH13_ISR(void);
FUNC(void, GPT_CODE) TOM1_CH14_CH15_ISR(void);

FUNC(void, GPT_CODE) TOM2_CH0_CH1_ISR(void);
FUNC(void, GPT_CODE) TOM2_CH2_CH3_ISR(void);
FUNC(void, GPT_CODE) TOM2_CH4_CH5_ISR(void);
FUNC(void, GPT_CODE) TOM2_CH6_CH7_ISR(void);
FUNC(void, GPT_CODE) TOM2_CH8_CH9_ISR(void);
FUNC(void, GPT_CODE) TOM2_CH10_CH11_ISR(void);
FUNC(void, GPT_CODE) TOM2_CH12_CH13_ISR(void);
FUNC(void, GPT_CODE) TOM2_CH14_CH15_ISR(void);

FUNC(void, GPT_CODE) TOM3_CH0_CH1_ISR(void);
FUNC(void, GPT_CODE) TOM3_CH2_CH3_ISR(void);
FUNC(void, GPT_CODE) TOM3_CH4_CH5_ISR(void);
FUNC(void, GPT_CODE) TOM3_CH6_CH7_ISR(void);
FUNC(void, GPT_CODE) TOM3_CH8_CH9_ISR(void);
FUNC(void, GPT_CODE) TOM3_CH10_CH11_ISR(void);
FUNC(void, GPT_CODE) TOM3_CH12_CH13_ISR(void);
FUNC(void, GPT_CODE) TOM3_CH14_CH15_ISR(void);

FUNC(void, GPT_CODE) TOM4_CH0_CH1_ISR(void);
FUNC(void, GPT_CODE) TOM4_CH2_CH3_ISR(void);
FUNC(void, GPT_CODE) TOM4_CH4_CH5_ISR(void);
FUNC(void, GPT_CODE) TOM4_CH6_CH7_ISR(void);
FUNC(void, GPT_CODE) TOM4_CH8_CH9_ISR(void);
FUNC(void, GPT_CODE) TOM4_CH10_CH11_ISR(void);
FUNC(void, GPT_CODE) TOM4_CH12_CH13_ISR(void);
FUNC(void, GPT_CODE) TOM4_CH14_CH15_ISR(void);

FUNC(void, GPT_CODE) TOM5_CH0_CH1_ISR(void);
FUNC(void, GPT_CODE) TOM5_CH2_CH3_ISR(void);
FUNC(void, GPT_CODE) TOM5_CH4_CH5_ISR(void);
FUNC(void, GPT_CODE) TOM5_CH6_CH7_ISR(void);
FUNC(void, GPT_CODE) TOM5_CH8_CH9_ISR(void);
FUNC(void, GPT_CODE) TOM5_CH10_CH11_ISR(void);
FUNC(void, GPT_CODE) TOM5_CH12_CH13_ISR(void);
FUNC(void, GPT_CODE) TOM5_CH14_CH15_ISR(void);

FUNC(void, GPT_CODE) TOM6_CH0_CH1_ISR(void);
FUNC(void, GPT_CODE) TOM6_CH2_CH3_ISR(void);
FUNC(void, GPT_CODE) TOM6_CH4_CH5_ISR(void);
FUNC(void, GPT_CODE) TOM6_CH6_CH7_ISR(void);
FUNC(void, GPT_CODE) TOM6_CH8_CH9_ISR(void);
FUNC(void, GPT_CODE) TOM6_CH10_CH11_ISR(void);
FUNC(void, GPT_CODE) TOM6_CH12_CH13_ISR(void);
FUNC(void, GPT_CODE) TOM6_CH14_CH15_ISR(void);

FUNC(void, GPT_CODE) TOM7_CH0_CH1_ISR(void);
FUNC(void, GPT_CODE) TOM7_CH2_CH3_ISR(void);
FUNC(void, GPT_CODE) TOM7_CH4_CH5_ISR(void);
FUNC(void, GPT_CODE) TOM7_CH6_CH7_ISR(void);
FUNC(void, GPT_CODE) TOM7_CH8_CH9_ISR(void);
FUNC(void, GPT_CODE) TOM7_CH10_CH11_ISR(void);
FUNC(void, GPT_CODE) TOM7_CH12_CH13_ISR(void);
FUNC(void, GPT_CODE) TOM7_CH14_CH15_ISR(void);

FUNC(void,GPT_CODE) Gpt_Stm_Callback_From_IRQ(VAR(Gpt_ChannelType, AUTOMATIC) Gpt_Channel);

FUNC(void, GPT_CODE) Gpt_Pit_Callback_From_IRQ(VAR(Gpt_ChannelType, AUTOMATIC) Gpt_Channel);

FUNC(void,GPT_CODE) Gpt_Gtm_Callback_From_IRQ(VAR(Gpt_ChannelType, AUTOMATIC) Gpt_Channel);

FUNC(void,GPT_CODE) Gpt_Rtc_Callback_From_IRQ(VAR(Gpt_ChannelType, AUTOMATIC) Gpt_Channel);

#ifdef __cplusplus
}
#endif

#endif // _GPT_IRQ_H_

