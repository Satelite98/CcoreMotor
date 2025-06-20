/**
*   @file    WdgIf_Types.h
*   @version 1.0.1
*
*   @brief   AUTOSAR WdgIf - Interface Types header file.
*   @details Contains information about Interface Types header file.
*            This file contains sample code only. It is not part of the production code deliverables.
*
*   @addtogroup Wdg
*   @{
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
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/

#ifndef WDGIF_TYPES_H
#define WDGIF_TYPES_H

#define WDGIF_TYPES_H_VENDOR_ID                      176
#define WDGIF_TYPES_H_VERSION_MAJOR                  4
#define WDGIF_TYPES_H_VERSION_MINOR                  4
#define WDGIF_TYPES_H_VERSION_REVISION               0
#define WDGIF_TYPES_H_SW_VERSION_MAJOR               1
#define WDGIF_TYPES_H_SW_VERSION_MINOR               0
#define WDGIF_TYPES_H_SW_VERSION_PATCH               1
#ifdef __cplusplus
extern "C"{
#endif

typedef enum
{
    WDGIF_UNINIT         = 0x00,  /**< @brief The watchdog driver is not uninitialized.  This shall be the default value after reset */
    WDGIF_IDLE,                   /**< @brief = 0x01 The watchdog driver is currently idle, i.e not beeing triggered or mode changed */
    WDGIF_BUSY                    /**< @brief = 0x02 The watchdog driver is currently busy, i.e triggered or switchd between modes */
}WdgIf_StatusType;

/** 
*   @brief  This enumerated type will contain the watchdog driver's possible modes 
*/
typedef enum {
    WDGIF_OFF_MODE      = 0,/**< @brief  In this mode, the watchdog driver is disabled (switched off). */
    WDGIF_SLOW_MODE,        /**< @brief  =0x01 In this mode, the watchdog driver is set up for a long timeout period (slow triggering).*/
    WDGIF_FAST_MODE         /**< @brief  =0x02 In this mode, the watchdog driver is set up for a short timeout period (fast triggering).*/
} WdgIf_ModeType;
/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
typedef P2FUNC(Std_ReturnType, WDGIF_WDG_CODE, WdgIf_SetModeFctPtrType)(WdgIf_ModeType Wdg_176_ModId_SetMode);
typedef P2FUNC(void, WDGIF_WDG_CODE, WdgIf_SetTriggerFctPtrType)(uint16 Wdg_176_ModId_SetTriggerCondition);
/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /*WDGIF_TYPES_H*/
