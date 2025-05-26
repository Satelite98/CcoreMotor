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
*   @file    eTPU_HAL_Irq.h
*   @version 
*
*      AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Icu MCAL driver.
*
*   @addtogroup Icu
*   @{
*/
#ifndef ETPU_HAL_IRQ_H
#define ETPU_HAL_IRQ_H

#ifdef __cplusplus
extern "C"
{
#endif

/*====================================================================================================
                                        INCLUDE FILES
====================================================================================================*/
#include "StandardTypes.h"
#include "intc_lld.h"
#ifdef RESOURCE_SUPPORT_ETPU
/*====================================================================================================
                                SOURCE FILE VERSION INFORMATION
====================================================================================================*/

#define ETPU_HAL_IRQ_VENDOR_ID_H                   176

#define ETPU_HAL_IRQ_MAJOR_VER_H                   4
#define ETPU_HAL_IRQ_MINOR_VER_H                   4
#define ETPU_HAL_IRQ_REVISION_VER_H                0

#define ETPU_HAL_IRQ_SW_MAJOR_VER_H                1
#define ETPU_HAL_IRQ_SW_MINOR_VER_H                0
#define ETPU_HAL_IRQ_SW_PATCH_VER_H                1

#if (ETPU_HAL_IRQ_VENDOR_ID_H != STANDARD_VENDOR_ID)
#error "NON-MATCHED DATA : ICU_VENDOR_ID_CFG"
#endif

/* Check if current file and ICU header file are of the same Autosar version */
#if (ETPU_HAL_IRQ_MAJOR_VER_H != STANDARD_AR_RELEASE_MAJOR_VERSION)
#error "NON-MATCHED DATA : ICU_MAJOR_VER_H"
#endif
#if (ETPU_HAL_IRQ_MINOR_VER_H != STANDARD_AR_RELEASE_MINOR_VERSION)
#error "NON-MATCHED DATA : ICU_MINOR_VER_H"
#endif
#if (ETPU_HAL_IRQ_REVISION_VER_H != STANDARD_AR_RELEASE_REVISION_VERSION)
#error "NON-MATCHED DATA : ICU_REVISION_VER_H"
#endif

/* Check if current file and ICU header file are of the same Software version */
#if (ETPU_HAL_IRQ_SW_MAJOR_VER_H != STANDARD_SW_MAJOR_VERSION)
#error "NON-MATCHED DATA : ICU_SW_MAJOR_VER_H"
#endif
#if (ETPU_HAL_IRQ_SW_MINOR_VER_H != STANDARD_SW_MINOR_VERSION)
#error "NON-MATCHED DATA : ICU_SW_MINOR_VER_H"
#endif
#if (ETPU_HAL_IRQ_SW_PATCH_VER_H != STANDARD_SW_PATCH_VERSION)
#error "NON-MATCHED DATA : ICU_SW_PATCH_VER_H"
#endif

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
#define ETPU_IRQ_INSTANCE_MAX			3
/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/
typedef void(*irq_notification)
( \
    VAR(uint8_t, AUTOMATIC) etpuIndex, \
    VAR(uint8_t, AUTOMATIC) ChanNum \
);
/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/


FUNC(void, ICU_CODE) eTPUA_CH0_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH1_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH2_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH3_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH4_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH5_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH6_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH7_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH8_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH9_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH10_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH11_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH12_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH13_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH14_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH15_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH16_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH17_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH18_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH19_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH20_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH21_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH22_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH23_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH24_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH25_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH26_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH27_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH28_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH29_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH30_Handler(void);
FUNC(void, ICU_CODE) eTPUA_CH31_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH0_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH1_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH2_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH3_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH4_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH5_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH6_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH7_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH8_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH9_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH10_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH11_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH12_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH13_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH14_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH15_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH16_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH17_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH18_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH19_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH20_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH21_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH22_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH23_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH24_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH25_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH26_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH27_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH28_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH29_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH30_Handler(void);
FUNC(void, ICU_CODE) eTPUB_CH31_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH0_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH1_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH2_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH3_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH4_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH5_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH6_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH7_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH8_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH9_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH10_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH11_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH12_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH13_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH14_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH15_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH16_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH17_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH18_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH19_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH20_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH21_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH22_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH23_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH24_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH25_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH26_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH27_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH28_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH29_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH30_Handler(void);
FUNC(void, ICU_CODE) eTPUC_CH31_Handler(void);

#ifdef __cplusplus
}
#endif
#endif /* ETPU_HAL_IRQ_H */

#endif /*#RESOURCE_SUPPORT_ETPU*/

