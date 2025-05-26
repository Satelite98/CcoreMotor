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
*   @file    Can_Irq.h
*   @version 1.0.1
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Can MCAL driver.
*
*   @addtogroup Can
*   @{
*/

#ifndef CAN_IRQ_H
#define CAN_IRQ_H

#ifdef __cplusplus
extern "C"{
#endif

#define CAN_IRQ_H_VENDOR_ID                     176
#define CAN_IRQ_H_AR_REL_MAJOR_VER              4
#define CAN_IRQ_H_AR_REL_MINOR_VER              4
#define CAN_IRQ_H_AR_REL_REV_VER                0
#define CAN_IRQ_H_SW_MAJOR_VER                  1
#define CAN_IRQ_H_SW_MINOR_VER                  0
#define CAN_IRQ_H_SW_PATCH_VER                  1

#if (CAN_CFG_H_VENDOR_ID != CAN_IRQ_H_VENDOR_ID)
    #error " NON-MATCHED DATA : CAN_IRQ_H_VENDOR_ID "
#endif
#if (CAN_CFG_H_AR_REL_MAJOR_VER != CAN_IRQ_H_AR_REL_MAJOR_VER)
    #error " NON-MATCHED DATA : CAN_IRQ_H_AR_REL_MAJOR_VER "
#endif
#if (CAN_CFG_H_AR_REL_MINOR_VER != CAN_IRQ_H_AR_REL_MINOR_VER)
    #error " NON-MATCHED DATA : CAN_IRQ_H_AR_REL_MINOR_VER "
#endif
#if (CAN_CFG_H_AR_REL_REV_VER != CAN_IRQ_H_AR_REL_REV_VER)
    #error " NON-MATCHED DATA : CAN_IRQ_H_AR_REL_REV_VER "
#endif
#if (CAN_CFG_H_SW_MAJOR_VER != CAN_IRQ_H_SW_MAJOR_VER)
    #error " NON-MATCHED DATA : CAN_IRQ_H_SW_MAJOR_VER "
#endif
#if (CAN_CFG_H_SW_MINOR_VER != CAN_IRQ_H_SW_MINOR_VER)
    #error " NON-MATCHED DATA : CAN_IRQ_H_SW_MINOR_VER "
#endif
#if (CAN_CFG_H_SW_PATCH_VER != CAN_IRQ_H_SW_PATCH_VER)
    #error " NON-MATCHED DATA : CAN_IRQ_H_SW_PATCH_VER "
#endif

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"

FUNC(void, CAN_CODE) ISR_M_CAN1_0(void);
FUNC(void, CAN_CODE) ISR_M_CAN1_1(void);
FUNC(void, CAN_CODE) ISR_M_CAN2_0(void);
FUNC(void, CAN_CODE) ISR_M_CAN2_1(void);
FUNC(void, CAN_CODE) ISR_M_CAN3_0(void);
FUNC(void, CAN_CODE) ISR_M_CAN3_1(void);
FUNC(void, CAN_CODE) ISR_M_CAN4_0(void);
FUNC(void, CAN_CODE) ISR_M_CAN4_1(void);
FUNC(void, CAN_CODE) ISR_M_CAN5_0(void);
FUNC(void, CAN_CODE) ISR_M_CAN5_1(void);
FUNC(void, CAN_CODE) ISR_M_CAN6_0(void);
FUNC(void, CAN_CODE) ISR_M_CAN6_1(void);
FUNC(void, CAN_CODE) ISR_M_CAN7_0(void);
FUNC(void, CAN_CODE) ISR_M_CAN7_1(void);
FUNC(void, CAN_CODE) ISR_M_CAN8_0(void);
FUNC(void, CAN_CODE) ISR_M_CAN8_1(void);
FUNC(void, CAN_CODE) ISR_M_CAN9_0(void);
FUNC(void, CAN_CODE) ISR_M_CAN9_1(void);
FUNC(void, CAN_CODE) ISR_M_CAN10_0(void);
FUNC(void, CAN_CODE) ISR_M_CAN10_1(void);
FUNC(void, CAN_CODE) ISR_M_CAN11_0(void);
FUNC(void, CAN_CODE) ISR_M_CAN11_1(void);
FUNC(void, CAN_CODE) ISR_M_CAN12_0(void);
FUNC(void, CAN_CODE) ISR_M_CAN12_1(void);

#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* CAN_IRQ_H */
