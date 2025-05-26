#ifndef SENT_HAL_WRAPPER_H
#define SENT_HAL_WRAPPER_H

#include "Sent.h"

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

#define SENT_MODULE_SHIFT                        (5U)

FUNC(void, SENT_CODE) Sent_Hal_Wrapper_Init
(
    VAR(Sent_ChannelType, AUTOMATIC) ChannelId
);

FUNC(void, SENT_CODE) Sent_Hal_Wrapper_SetChannel
(
    VAR(Sent_ChannelType, AUTOMATIC) ChannelId,
    VAR(Sent_StatType, AUTOMATIC) Operation
);

FUNC(uint32, SENT_CODE) Sent_Hal_Wrapper_ReadData
(
    VAR(Sent_ChannelType, AUTOMATIC) ChannelId
);

FUNC(void, SENT_CODE) Sent_Hal_Wrapper_ReadSerialData
(
    VAR(Sent_ChannelType, AUTOMATIC) ChannelId,
    P2VAR(Sent_RxSerialDataType, AUTOMATIC, SENT_APPL_DATA) pDataPtr
);

FUNC(void, SENT_CODE) Sent_Hal_Wrapper_ReadChannelStatus
(
    VAR(Sent_ChannelType, AUTOMATIC) ChannelId,
    P2VAR(Sent_ChanStatusType, AUTOMATIC, SENT_APPL_DATA) pStatPtr
);

FUNC(void, SENT_CODE) Sent_Hal_Wrapper_DeInit
(
    VAR(Sent_ChannelType, AUTOMATIC) ChannelId
);

#endif
