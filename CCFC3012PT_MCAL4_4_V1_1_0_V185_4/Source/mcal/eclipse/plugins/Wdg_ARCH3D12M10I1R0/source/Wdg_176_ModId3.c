/****************************************************************************
*
* Copyright (c) 2023  C*Core -   All Rights Reserved
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
*/
/*==================================================================================================
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
*   *****************************************************************************/
/**
*   @file    Wdg_Channel.c
*   @version 1.0.1
*
*   @addtogroup Wdg
*   @{
*/
#ifdef __cplusplus
extern "C"{
#endif

#include "Wdg_Module.h"
#include "wdg_176_ModId3.h"

#define WDG_176_MOD3_CVENDOR_ID                   176
#define WDG_176_MOD3_C_VER_MAJOR                  4
#define WDG_176_MOD3_C_VER_MINOR                  4
#define WDG_176_MOD3_C_VER_REVISION               0
#define WDG_176_MOD3_C_SW_VER_MAJOR               1
#define WDG_176_MOD3_C_SW_VER_MINOR               0
#define WDG_176_MOD3_C_SW_VER_PATCH               1

#if (WDG_176_MOD3_CVENDOR_ID != WDG_176_MOD3_H_VENDOR_ID)
    #error " NON-MATCHED DATA : WDG_176_MOD3_CVENDOR_ID "
#endif
#if (WDG_176_MOD3_C_VER_MAJOR != WDG_176_MOD3_H_VER_MAJOR)
    #error " NON-MATCHED DATA : WDG_176_MOD3_C_VER_MAJOR "
#endif
#if (WDG_176_MOD3_C_VER_MINOR != WDG_176_MOD3_H_VER_MINOR)
    #error " NON-MATCHED DATA : WDG_176_MOD3_C_VER_MINOR "
#endif
#if (WDG_176_MOD3_C_VER_REVISION != WDG_176_MOD3_H_VER_REVISION)
    #error " NON-MATCHED DATA : WDG_176_MOD3_C_VER_REVISION "
#endif
#if (WDG_176_MOD3_C_SW_VER_MAJOR != WDG_176_MOD3_H_SW_VER_MAJOR)
    #error " NON-MATCHED DATA : WDG_176_MOD3_C_SW_VER_MAJOR "
#endif
#if (WDG_176_MOD3_C_SW_VER_MINOR != WDG_176_MOD3_H_SW_VER_MINOR)
    #error " NON-MATCHED DATA : WDG_176_MOD3_C_SW_VER_MINOR "
#endif
#if (WDG_176_MOD3_C_SW_VER_PATCH != WDG_176_MOD3_H_SW_VER_PATCH)
    #error " NON-MATCHED DATA : WDG_176_MOD3_C_SW_VER_PATCH "
#endif

#ifdef WDG_ROM
#define WDG_START_SEC_CODE
#else
#define WDG_START_SEC_RAMCODE
#endif

#include "Wdg_MemMap.h"
FUNC(void, WDG_CODE) Wdg_176_ModId3_Init \
( \
    P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr \
)
{
    Wdg_RunInstance_Init(ConfigPtr,SWT3);
}
#ifdef WDG_ROM
#define WDG_STOP_SEC_CODE
#else
#define WDG_STOP_SEC_RAMCODE
#endif
#include "Wdg_MemMap.h"

#ifdef WDG_ROM
#define WDG_START_SEC_CODE
#else
#define WDG_START_SEC_RAMCODE
#endif

#include "Wdg_MemMap.h"
FUNC(Std_ReturnType, WDG_CODE) Wdg_176_ModId3_SetMode(VAR(WdgIf_ModeType,AUTOMATIC) Mode)
{
    return Wdg_RunInstance_SetMode(Mode,SWT3);
}
#ifdef WDG_ROM
#define WDG_STOP_SEC_CODE
#else
#define WDG_STOP_SEC_RAMCODE
#endif
#include "Wdg_MemMap.h"

#ifdef WDG_ROM
#define WDG_START_SEC_CODE
#else
#define WDG_START_SEC_RAMCODE
#endif

#include "Wdg_MemMap.h"
FUNC(void, WDG_CODE) Wdg_176_ModId3_SetTriggerCondition(VAR(uint16,AUTOMATIC) timeout)
{
    Wdg_RunSetTriggerCondition(timeout,SWT3);
}
#ifdef WDG_ROM
#define WDG_STOP_SEC_CODE
#else
#define WDG_STOP_SEC_RAMCODE
#endif
#include "Wdg_MemMap.h"

#ifdef WDG_ROM
#define WDG_START_SEC_CODE
#else
#define WDG_START_SEC_RAMCODE
#endif

#include "Wdg_MemMap.h"
#if(WDG_VERSION_INFO_API==STD_ON)
FUNC(void, WDG_CODE) Wdg_176_ModId3_GetVersionInfo \
( \
    P2VAR(Std_VersionInfoType, AUTOMATIC, WDG_APPL_DATA) Versioninfo \
)
{
    Wdg_RunGetVersionInfo(Versioninfo,SWT3);
}
#endif
#ifdef WDG_ROM
#define WDG_STOP_SEC_CODE
#else
#define WDG_STOP_SEC_RAMCODE
#endif
#include "Wdg_MemMap.h"
#ifdef __cplusplus
}
#endif
/** @} */
