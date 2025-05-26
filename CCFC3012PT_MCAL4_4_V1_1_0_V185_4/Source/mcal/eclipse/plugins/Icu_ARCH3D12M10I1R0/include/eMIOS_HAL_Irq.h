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
*   @file    Icu_eMIOS_HAL_Irq.h
*   @version 
*
*      AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Icu MCAL driver.
*
*   @addtogroup Icu
*   @{
*/
#ifndef EMIOS_HAL_IRQ_H
#define EMIOS_HAL_IRQ_H

#ifdef __cplusplus
extern "C"
{
#endif

/*====================================================================================================
                                        INCLUDE FILES
====================================================================================================*/
#include "StandardTypes.h"
#include "intc_lld.h"

/*====================================================================================================
                                SOURCE FILE VERSION INFORMATION
====================================================================================================*/

/*====================================================================================================
                                        FILE VERSION CHECKS
====================================================================================================*/
#define EMIOS_HAL_IRQ_VENDOR_ID_H                   176

#define EMIOS_HAL_IRQ_MAJOR_VER_H                   4
#define EMIOS_HAL_IRQ_MINOR_VER_H                   4
#define EMIOS_HAL_IRQ_REVISION_VER_H                0

#define EMIOS_HAL_IRQ_SW_MAJOR_VER_H                1
#define EMIOS_HAL_IRQ_SW_MINOR_VER_H                0
#define EMIOS_HAL_IRQ_SW_PATCH_VER_H                1

#if (EMIOS_HAL_IRQ_VENDOR_ID_H != STANDARD_VENDOR_ID)
#error "NON-MATCHED DATA : ICU_VENDOR_ID_CFG"
#endif

/* Check if current file and ICU header file are of the same Autosar version */
#if (EMIOS_HAL_IRQ_MAJOR_VER_H != STANDARD_AR_RELEASE_MAJOR_VERSION)
#error "NON-MATCHED DATA : ICU_MAJOR_VER_H"
#endif
#if (EMIOS_HAL_IRQ_MINOR_VER_H != STANDARD_AR_RELEASE_MINOR_VERSION)
#error "NON-MATCHED DATA : ICU_MINOR_VER_H"
#endif
#if (EMIOS_HAL_IRQ_REVISION_VER_H != STANDARD_AR_RELEASE_REVISION_VERSION)
#error "NON-MATCHED DATA : ICU_REVISION_VER_H"
#endif

/* Check if current file and ICU header file are of the same Software version */
#if (EMIOS_HAL_IRQ_SW_MAJOR_VER_H != STANDARD_SW_MAJOR_VERSION)
#error "NON-MATCHED DATA : ICU_SW_MAJOR_VER_H"
#endif
#if (EMIOS_HAL_IRQ_SW_MINOR_VER_H != STANDARD_SW_MINOR_VERSION)
#error "NON-MATCHED DATA : ICU_SW_MINOR_VER_H"
#endif
#if (EMIOS_HAL_IRQ_SW_PATCH_VER_H != STANDARD_SW_PATCH_VERSION)
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
typedef void(*irq_emios_notification)
( \
    VAR(uint8_t, AUTOMATIC) emiosIndex, \
    VAR(uint8_t, AUTOMATIC) ChanNum \
);
/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
#if defined(RESOURCE_SUPPORT_EMIOS0) 
FUNC(void, ICU_CODE) eMIOS0_CH0_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH1_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH2_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH3_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH4_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH5_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH6_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH7_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH8_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH9_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH10_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH11_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH12_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH13_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH14_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH15_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH16_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH17_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH18_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH19_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH20_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH21_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH22_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH23_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH24_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH25_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH26_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH27_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH28_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH29_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH30_Handler(void);
FUNC(void, ICU_CODE) eMIOS0_CH31_Handler(void);
#endif



#if defined(RESOURCE_SUPPORT_EMIOS1)
FUNC(void, ICU_CODE) eMIOS1_CH0_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH1_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH2_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH3_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH4_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH5_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH6_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH7_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH8_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH9_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH10_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH11_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH12_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH13_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH14_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH15_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH16_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH17_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH18_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH19_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH20_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH21_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH22_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH23_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH24_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH25_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH26_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH27_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH28_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH29_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH30_Handler(void);
FUNC(void, ICU_CODE) eMIOS1_CH31_Handler(void);
#endif

#ifdef __cplusplus
}
#endif
#endif /* ICU_EMIOS_HAL_IRQ_H */

