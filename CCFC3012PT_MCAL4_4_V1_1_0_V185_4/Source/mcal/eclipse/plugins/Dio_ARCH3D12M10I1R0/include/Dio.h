/**************************************************************************** 
* 
* Copyright (c) 2023  C*Core -   All Rights Reserved  
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*   Project              : AUTOSAR 4.4.0 MCAL
*   Platform             : PowerPC e200
*   Peripheral           : 
*   Dependencies         : 
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : 
*   Autosar Conf.Variant :
*   SW Version           : 
*   Build Version        : 
*****************************************************************************/
/**
*   @file    Dio.c
*   @version 1.0.0
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Dio MCAL driver.
*   @addtogroup Dio
*   @{
*/

#ifndef DIO_H
#define DIO_H

#ifdef __cplusplus
extern "C"{
#endif
/* ==============================================INCLUDE FILES======================================= */
#include "Dio_AutoSar_Wrapper.h"
#include "Dio_Cfg.h"
/* =====================================SOURCE FILE VERSION INFORMATION============================== */
#define DIO_H_VENDOR_ID                     176
#define DIO_H_MODULE_ID                     120
#define DIO_H_MAJOR_VERSION                 4
#define DIO_H_MINOR_VERSION                 4
#define DIO_H_patch_VERSION                 0
#define DIO_H_SW_MAJOR_VERSION              1
#define DIO_H_SW_MINOR_VERSION              0
#define DIO_H_SW_PATCH_VERSION              1

/* ============================================FILE VERSION CHECKS=================================== */
#if (DIO_H_VENDOR_ID != DIO_ATS_WRA_H_VENDOR_ID)
    #error " NON-MATCHED DATA : DIO_H_VENDOR_ID "
#endif
#if (DIO_H_MAJOR_VERSION != DIO_ATS_WRA_H_MAJOR_VERSION)
    #error " NON-MATCHED DATA : DIO_H_MAJOR_VERSION "
#endif
#if (DIO_H_MINOR_VERSION != DIO_ATS_WRA_H_MINOR_VERSION)
    #error " NON-MATCHED DATA : DIO_H_MINOR_VERSION "
#endif
#if (DIO_H_patch_VERSION != DIO_ATS_WRA_H_patch_VERSION)
    #error " NON-MATCHED DATA : DIO_H_patch_VERSION "
#endif
#if (DIO_H_SW_MAJOR_VERSION != DIO_ATS_WRAH_SW_MAJOR_VERSION)
    #error " NON-MATCHED DATA : DIO_H_SW_MAJOR_VERSION "
#endif
#if (DIO_H_SW_MINOR_VERSION != DIO_ATS_WRA_H_SW_MINOR_VERSION)
    #error " NON-MATCHED DATA : DIO_H_SW_MINOR_VERSION "
#endif
#if (DIO_H_SW_PATCH_VERSION != DIO_ATS_WRA_H_SW_PATCH_VERSION)
    #error " NON-MATCHED DATA : DIO_H_SW_PATCH_VERSION "
#endif

/*============================================DEFINES AND MACROS====================================*/
#define DIO_START_SEC_CODE
#include "Dio_MemMap.h"

#define DIO_BIT1_LEFTMOST_MASK_U16                  ((uint16)0x8000U)
#define DIO_PIN_MASK_U16                            ((uint16)0x000FU)
#define DIO_PORTID_SHIFT_U8							((uint16)0x4U)

/*============================================FUNCTION PROTOTYPES===================================*/
FUNC(Dio_LevelType, DIO_CODE) Dio_ReadChannel \
( \
    CONST(Dio_ChannelType, AUTOMATIC) ChannelId \
);
FUNC(void, DIO_CODE) Dio_WriteChannel \
( \
    CONST(Dio_ChannelType, AUTOMATIC) ChannelId, \
	CONST(Dio_LevelType, AUTOMATIC) Level \
);
FUNC(Dio_PortLevelType, DIO_CODE) Dio_ReadPort \
( \
    CONST(Dio_PortType, AUTOMATIC) PortlId \
);
FUNC(void, DIO_CODE) Dio_WritePort \
( \
    CONST(Dio_PortType, AUTOMATIC) PortId, \
    CONST(Dio_PortLevelType, AUTOMATIC) Level \
);
FUNC(Dio_PortLevelType, DIO_CODE) Dio_ReadChannelGroup \
( \
    P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_APPL_CONST) ChannelGroupIdPtr \
);
FUNC(void, DIO_CODE) Dio_WriteChannelGroup \
( \
    P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_APPL_CONST) ChannelGroupIdPtr, \
    CONST(Dio_PortLevelType,AUTOMATIC) Level \
);
FUNC(void, DIO_CODE) Dio_GetVersionInfo \
( \
    P2VAR(Std_VersionInfoType, AUTOMATIC, DIO_APPL_DATA) VersionInfo \
);
FUNC(Dio_LevelType, DIO_CODE) Dio_FlipChannel \
( \
    CONST(Dio_ChannelType, AUTOMATIC) ChannelId \
);
FUNC(void, DIO_CODE) Dio_MaskedWritePort \
( \
    CONST(Dio_PortType, AUTOMATIC) PortId, \
    CONST(Dio_PortLevelType, AUTOMATIC) Level, \
    CONST(Dio_PortLevelType, AUTOMATIC) Mask \
);
#define DIO_STOP_SEC_CODE
#include "Dio_MemMap.h"
#ifdef __cplusplus
}
#endif

#endif
