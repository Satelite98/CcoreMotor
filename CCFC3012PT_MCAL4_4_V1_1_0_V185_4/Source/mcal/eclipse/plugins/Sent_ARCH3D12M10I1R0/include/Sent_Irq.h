#ifndef SENT_IRQ_H
#define SENT_IRQ_H

#include "Sent_Cfg.h"

/*=====================================SOURCE FILE VERSION INFORMATION==============================*/
#define SENT_VENDOR_ID_H                     176
#define SENT_MODULE_ID_H                     100
#define SENT_AR_MAJOR_VER_H                  4
#define SENT_AR_MINOR_VER_H                  4
#define SENT_AR_PATCH_VER_H                  0
#define SENT_SW_MAJOR_VER_H                  1
#define SENT_SW_MINOR_VER_H                  0
#define SENT_SW_PATCH_VER_H                  1

/*============================================FILE VERSION CHECKS===================================*/

#if (SENT_VENDOR_ID_H != SENT_VENDOR_ID)
#error "NON-MATCHED DATA : SENT_CFG_VENDOR_ID"
#endif

#if (SENT_AR_MAJOR_VER_H != SENT_CFG_AR_MAJOR_VER)
#error "NON-MATCHED DATA : SENT_CFG_AR_MAJOR_VER"
#endif
#if (SENT_AR_MINOR_VER_H != SENT_CFG_AR_MINOR_VER)
#error "NON-MATCHED DATA : SENT_CFG_AR_MINOR_VER"
#endif
#if (SENT_AR_PATCH_VER_H != SENT_CFG_AR_PATCH_VER)
#error "NON-MATCHED DATA : SENT_CFG_AR_PATCH_VER"
#endif

#if (SENT_SW_MAJOR_VER_H != SENT_CFG_SW_MAJOR_VER)
#error "NON-MATCHED DATA : SENT_CFG_SW_MAJOR_VER"
#endif
#if (SENT_SW_MINOR_VER_H != SENT_CFG_SW_MINOR_VER)
#error "NON-MATCHED DATA : SENT_CFG_SW_MINOR_VER"
#endif
#if (SENT_SW_PATCH_VER_H != SENT_CFG_SW_PATCH_VER)
#error "NON-MATCHED DATA : SENT_CFG_SW_PATCH_VER"
#endif

#ifdef FEATURE_SRX_HAS_COMBINED_IRQ
FUNC(void, SENT_CODE) SRX0_COMBINED_IRQHandler(void);
FUNC(void, SENT_CODE) SRX1_COMBINED_IRQHandler(void);
#endif

FUNC(void, SENT_CODE) SRX0_CH0_IRQHandler(void);
FUNC(void, SENT_CODE) SRX1_CH0_IRQHandler(void);
FUNC(void, SENT_CODE) SRX0_CH2_IRQHandler(void);
FUNC(void, SENT_CODE) SRX0_CH3_IRQHandler(void);
FUNC(void, SENT_CODE) SRX0_CH4_IRQHandler(void);
FUNC(void, SENT_CODE) SRX0_CH5_IRQHandler(void);
FUNC(void, SENT_CODE) SRX0_CH6_IRQHandler(void);
FUNC(void, SENT_CODE) SRX0_CH7_IRQHandler(void);

FUNC(void, SENT_CODE) SRX0_CH1_IRQHandler(void);
FUNC(void, SENT_CODE) SRX1_CH1_IRQHandler(void);
FUNC(void, SENT_CODE) SRX1_CH2_IRQHandler(void);
FUNC(void, SENT_CODE) SRX1_CH3_IRQHandler(void);
FUNC(void, SENT_CODE) SRX1_CH4_IRQHandler(void);
FUNC(void, SENT_CODE) SRX1_CH5_IRQHandler(void);
FUNC(void, SENT_CODE) SRX1_CH6_IRQHandler(void);

#endif
