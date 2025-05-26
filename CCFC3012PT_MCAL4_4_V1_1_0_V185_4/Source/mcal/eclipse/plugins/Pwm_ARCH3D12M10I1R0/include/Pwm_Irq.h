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
*   @file    Pwm_Irq.h
*   @version 1.0.1
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Pwm MCAL driver.
*
*   @addtogroup Pwm
*   @{
*/

#ifndef PWM_IRQ_H
#define PWM_IRQ_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mcal.h"
#include "Pwm_Cfg.h"

#define PWM_IRQ_H_VENDOR_ID                      176
#define PWM_IRQ_H_AR_REL_MAJOR_VER               4
#define PWM_IRQ_H_AR_REL_MINOR_VER               4
#define PWM_IRQ_H_AR_REL_REV_VER                 0
#define PWM_IRQ_H_SW_MAJOR_VER                   1
#define PWM_IRQ_H_SW_MINOR_VER                   0
#define PWM_IRQ_H_SW_PATCH_VER                   1

#if (PWM_IRQ_H_VENDOR_ID != PWM_CFG_H_VENDOR_ID)
    #error " NON-MATCHED DATA : PWM_IRQ_H_VENDOR_ID "
#endif
#if (PWM_IRQ_H_AR_REL_MAJOR_VER != PWM_CFG_H_AR_REL_MAJOR_VER)
    #error " NON-MATCHED DATA : PWM_IRQ_H_AR_REL_MAJOR_VER "
#endif
#if (PWM_IRQ_H_AR_REL_MINOR_VER != PWM_CFG_H_AR_REL_MINOR_VER)
    #error " NON-MATCHED DATA : PWM_IRQ_H_AR_REL_MINOR_VER "
#endif
#if (PWM_IRQ_H_AR_REL_REV_VER != PWM_CFG_H_AR_REL_REV_VER)
    #error " NON-MATCHED DATA : PWM_IRQ_H_AR_REL_REV_VER "
#endif
#if (PWM_IRQ_H_SW_MAJOR_VER != PWM_CFG_H_SW_MAJOR_VER)
    #error " NON-MATCHED DATA : PWM_IRQ_H_SW_MAJOR_VER "
#endif
#if (PWM_IRQ_H_SW_MINOR_VER != PWM_CFG_H_SW_MINOR_VER)
    #error " NON-MATCHED DATA : PWM_IRQ_H_SW_MINOR_VER "
#endif
#if (PWM_IRQ_H_SW_PATCH_VER != PWM_CFG_H_SW_PATCH_VER)
    #error " NON-MATCHED DATA : PWM_IRQ_H_SW_PATCH_VER "
#endif

#if (defined(CCFC3007PT) || defined (CCFC3008PT) || defined (CCFC3012PT))

FUNC(void, PWM_CODE)Pwm_clr_isr_flag(VAR(Pwm_ChannelType, AUTOMATIC) Pwm_ChannelId);
FUNC(void, PWM_CODE)Pwm_Tom_isr_handle \
( \
    VAR(uint8, AUTOMATIC) u8hw_index, \
    VAR(uint8, AUTOMATIC) u8ch0_index, \
    VAR(uint8, AUTOMATIC) u8ch1_index \
);
FUNC(void, PWM_CODE)Pwm_Atom_isr_handle \
( \
    VAR(uint8, AUTOMATIC) u8hw_index, \
    VAR(uint8, AUTOMATIC) u8ch0_index, \
    VAR(uint8, AUTOMATIC) u8ch1_index \
);
#endif
FUNC(void, PWM_CODE)Pwm_Emios_isr_handle \
( \
    VAR(uint8, AUTOMATIC) u8hw_index, \
    VAR(uint8, AUTOMATIC) u8ch_index \
);
#if (defined(CCFC3007PT) || defined(CCFC3008PT) || defined(CCFC3007BC))
FUNC(void, PWM_CODE)Pwm_Etpu_isr_handle \
( \
    VAR(uint8, AUTOMATIC) u8hw_index, \
    VAR(uint8, AUTOMATIC) u8ch_index \
);
#endif

FUNC(void, PWM_CODE) Pwm_Set_Emios_DAOC_B \
( \
    VAR(uint8, AUTOMATIC) u8hw_index, \
    VAR(uint8, AUTOMATIC) u8ch_index, \
    VAR(uint32, AUTOMATIC) value \
);
FUNC(void, PWM_CODE) Pwm_Set_Emios_DAOC_Active \
( \
    VAR(uint8, AUTOMATIC) u8hw_index, \
    VAR(uint8, AUTOMATIC) u8ch_index, \
    VAR(uint32, AUTOMATIC) value \
);
FUNC(void, PWM_CODE) Pwm_Emios_DAOC_Isr_handle \
( \
    VAR(uint8, AUTOMATIC) u8hw_index, \
    VAR(uint8, AUTOMATIC) u8ch_index \
);

#ifdef __cplusplus
}
#endif

#endif

