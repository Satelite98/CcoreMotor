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
*   @file    Gtm_HAL_Irq.c
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
#include "Icu_Irq.h"
#include "Icu.h"
#include "Gtm_HAL_Irq.h"
#ifdef RESORUCE_SUPPORT_GTM104
#include "Icu_Gtm_LLDrivers.h"
#include "Icu_Gtm_Tim_LLDrivers.h"
#endif
#include "Icu_Gtm_Wrapper.h"
#ifdef RESORUCE_SUPPORT_GTM410
#include "Icu_Gtm4_Tim_LLDrivers.h"
#endif
/*====================================================================================================
                                SOURCE FILE VERSION INFORMATION
====================================================================================================*/

/*====================================================================================================
                                        FILE VERSION CHECKS
====================================================================================================*/
#define GTM_HAL_IRQ_VENDOR_ID_C                  176

#define GTM_HAL_IRQ_MAJOR_VER_C                  4
#define GTM_HAL_IRQ_MINOR_VER_C                  4
#define GTM_HAL_IRQ_REVISION_VER_C               0

#define GTM_HAL_IRQ_SW_MAJOR_VER_C               1
#define GTM_HAL_IRQ_SW_MINOR_VER_C               0
#define GTM_HAL_IRQ_SW_PATCH_VER_C               1

#if (GTM_HAL_IRQ_VENDOR_ID_C != GTM_HAL_IRQ_VENDOR_ID_H)
#error "NON-MATCHED DATA : ICU_VENDOR_ID_CFG"
#endif

/* Check if current file and ICU header file are of the same Autosar version */
#if (GTM_HAL_IRQ_MAJOR_VER_C != GTM_HAL_IRQ_MAJOR_VER_H)
#error "NON-MATCHED DATA : ICU_MAJOR_VER_H"
#endif
#if (GTM_HAL_IRQ_MINOR_VER_C != GTM_HAL_IRQ_MINOR_VER_H)
#error "NON-MATCHED DATA : ICU_MINOR_VER_H"
#endif
#if (GTM_HAL_IRQ_REVISION_VER_C != GTM_HAL_IRQ_REVISION_VER_H)
#error "NON-MATCHED DATA : ICU_REVISION_VER_H"
#endif

/* Check if current file and ICU header file are of the same Software version */
#if (GTM_HAL_IRQ_SW_MAJOR_VER_C != GTM_HAL_IRQ_SW_MAJOR_VER_H)
#error "NON-MATCHED DATA : ICU_SW_MAJOR_VER_H"
#endif
#if (GTM_HAL_IRQ_SW_MINOR_VER_C != GTM_HAL_IRQ_SW_MINOR_VER_H)
#error "NON-MATCHED DATA : ICU_SW_MINOR_VER_H"
#endif
#if (GTM_HAL_IRQ_SW_PATCH_VER_C != GTM_HAL_IRQ_SW_PATCH_VER_H)
#error "NON-MATCHED DATA : ICU_SW_PATCH_VER_H"
#endif
/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/
extern FUNC(void, ICU_CODE) Icu_Gtm_ProcessInterrupt \
( \
    VAR(GTM_TIM_Type,AUTOMATIC)ModuleId, \
    VAR(Icu_ChannelType, AUTOMATIC) ChannelId \
);

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

ISR(GTM_TIM_0_CH_0_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM0,GTM_CH_0);
}

ISR(GTM_TIM_0_CH_1_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM0,GTM_CH_1);
}

ISR(GTM_TIM_0_CH_2_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM0,GTM_CH_2);
}

ISR(GTM_TIM_0_CH_3_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM0,GTM_CH_3);
}

ISR(GTM_TIM_0_CH_4_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM0,GTM_CH_4);
}

ISR(GTM_TIM_0_CH_5_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM0,GTM_CH_5);
}

ISR(GTM_TIM_0_CH_6_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM0,GTM_CH_6);
}

ISR(GTM_TIM_0_CH_7_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM0,GTM_CH_7);
}

ISR(GTM_TIM_1_CH_0_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM1,GTM_CH_0);
}

ISR(GTM_TIM_1_CH_1_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM1,GTM_CH_1);
}

ISR(GTM_TIM_1_CH_2_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM1,GTM_CH_2);
}

ISR(GTM_TIM_1_CH_3_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM1,GTM_CH_3);
}

ISR(GTM_TIM_1_CH_4_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM1,GTM_CH_4);
}

ISR(GTM_TIM_1_CH_5_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM1,GTM_CH_5);
}

ISR(GTM_TIM_1_CH_6_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM1,GTM_CH_6);
}

ISR(GTM_TIM_1_CH_7_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM1,GTM_CH_7);
}


ISR(GTM_TIM_2_CH_0_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM2,GTM_CH_0);
}

ISR(GTM_TIM_2_CH_1_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM2,GTM_CH_1);
}

ISR(GTM_TIM_2_CH_2_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM2,GTM_CH_2);
}

ISR(GTM_TIM_2_CH_3_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM2,GTM_CH_3);
}

ISR(GTM_TIM_2_CH_4_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM2,GTM_CH_4);
}

ISR(GTM_TIM_2_CH_5_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM2,GTM_CH_5);
}

ISR(GTM_TIM_2_CH_6_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM2,GTM_CH_6);
}

ISR(GTM_TIM_2_CH_7_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM2,GTM_CH_7);
}

ISR(GTM_TIM_3_CH_0_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM3,GTM_CH_0);
}

ISR(GTM_TIM_3_CH_1_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM3,GTM_CH_1);
}

ISR(GTM_TIM_3_CH_2_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM3,GTM_CH_2);
}

ISR(GTM_TIM_3_CH_3_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM3,GTM_CH_3);
}

ISR(GTM_TIM_3_CH_4_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM3,GTM_CH_4);
}

ISR(GTM_TIM_3_CH_5_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM3,GTM_CH_5);
}

ISR(GTM_TIM_3_CH_6_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM3,GTM_CH_6);
}

ISR(GTM_TIM_3_CH_7_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM3,GTM_CH_7);
}

ISR(GTM_TIM_4_CH_0_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM4,GTM_CH_0);
}

ISR(GTM_TIM_4_CH_1_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM4,GTM_CH_1);
}

ISR(GTM_TIM_4_CH_2_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM4,GTM_CH_2);
}

ISR(GTM_TIM_4_CH_3_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM4,GTM_CH_3);
}

ISR(GTM_TIM_4_CH_4_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM4,GTM_CH_4);
}

ISR(GTM_TIM_4_CH_5_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM4,GTM_CH_5);
}

ISR(GTM_TIM_4_CH_6_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM4,GTM_CH_6);
}

ISR(GTM_TIM_4_CH_7_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM4,GTM_CH_7);
}

ISR(GTM_TIM_5_CH_0_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM5,GTM_CH_0);
}

ISR(GTM_TIM_5_CH_1_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM5,GTM_CH_1);
}

ISR(GTM_TIM_5_CH_2_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM5,GTM_CH_2);
}

ISR(GTM_TIM_5_CH_3_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM5,GTM_CH_3);
}

ISR(GTM_TIM_5_CH_4_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM5,GTM_CH_4);
}

ISR(GTM_TIM_5_CH_5_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM5,GTM_CH_5);
}

ISR(GTM_TIM_5_CH_6_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM5,GTM_CH_6);
}

ISR(GTM_TIM_5_CH_7_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM5,GTM_CH_7);
}

ISR(GTM_TIM_6_CH_0_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM6,GTM_CH_0);
}

ISR(GTM_TIM_6_CH_1_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM6,GTM_CH_1);
}

ISR(GTM_TIM_6_CH_2_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM6,GTM_CH_2);
}

ISR(GTM_TIM_6_CH_3_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM6,GTM_CH_3);
}

ISR(GTM_TIM_6_CH_4_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM6,GTM_CH_4);
}

ISR(GTM_TIM_6_CH_5_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM6,GTM_CH_5);
}

ISR(GTM_TIM_6_CH_6_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM6,GTM_CH_6);
}

ISR(GTM_TIM_6_CH_7_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM6,GTM_CH_7);
}

ISR(GTM_TIM_7_CH_0_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM7,GTM_CH_0);
}

ISR(GTM_TIM_7_CH_1_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM7,GTM_CH_1);
}

ISR(GTM_TIM_7_CH_2_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM7,GTM_CH_2);
}

ISR(GTM_TIM_7_CH_3_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM7,GTM_CH_3);
}

ISR(GTM_TIM_7_CH_4_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM7,GTM_CH_4);
}

ISR(GTM_TIM_7_CH_5_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM7,GTM_CH_5);
}

ISR(GTM_TIM_7_CH_6_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM7,GTM_CH_6);
}

ISR(GTM_TIM_7_CH_7_ISR)
{
    Icu_Gtm_ProcessInterrupt(GTM_TIM7,GTM_CH_7);
}

