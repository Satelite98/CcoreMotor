/**
 *   @file    Det.h
 *   @version 1.0.2
 *
 *   @brief   AUTOSAR Det - module interface.
 *   @details This file contains the functions prototypes and data types of the AUTOSAR Det.
 *            This file contains sample code only. It is not part of the production code deliverables
 *
 *   @addtogroup DET_MODULE
 *   @{
 */
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           :
*   Dependencies         : none
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_0_REV_0003
*   Autosar Conf.Variant :
*   SW Version           : 1.0.1
*   Build Version        : MPC577XM_MCAL_1_0_1_RTM_ASR_REL_4_0_REV_0003_20170922
*
*   (c) Copyright (c) 2006-2016 Freescale Semiconductor, Inc.
*       Copyright 2017 CCFC.
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/
#ifndef DET_H
#define DET_H

#ifdef __cplusplus
extern "C"
{
#endif

    /*==================================================================================================
    *                                         INCLUDE FILES
    * 1) system and project includes
    * 2) needed interfaces from external units
    * 3) internal and external interfaces from this unit
    ==================================================================================================*/

    /*==================================================================================================
    *                               SOURCE FILE VERSION INFORMATION
    ==================================================================================================*/
    /**
     * @file           Det.h
     * @requirements   DET001_PI
     */
#include "console.h"
#define DET_VENDOR_ID                176
#define DET_MODULE_ID                15

#define DET_AR_RELEASE_MAJOR_VERSION 4
#define DET_AR_RELEASE_MINOR_VERSION 4
#define DET_AR_RELEASE_REVISION_VERSION 0
#define DET_SW_MAJOR_VERSION 1
#define DET_SW_MINOR_VERSION 0
#define DET_SW_PATCH_VERSION 1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
extern VAR(uint8, DET_VAR) Det_InstanceId; /**< @brief DET instance ID*/
extern VAR(uint8, DET_VAR) Det_ApiId;      /**< @brief DET API ID*/
extern VAR(uint8, DET_VAR) Det_ErrorId;        /**< @brief DET Error ID*/

extern VAR(uint16, DET_VAR) Det_ModuleId; /**< @brief DET module ID*/

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/
FUNC(void, DET_CODE)Det_Init(void);
FUNC(Std_ReturnType, DET_CODE)Det_ReportError(VAR(uint16, AUTOMATIC) ModuleId, VAR(uint8, AUTOMATIC) InstanceId, VAR(uint8, AUTOMATIC) ApiId, VAR(uint8, AUTOMATIC) ErrorId);
FUNC(Std_ReturnType, DET_CODE) Det_ReportRuntimeError(VAR(uint16, AUTOMATIC) ModuleId, VAR(uint8, AUTOMATIC) InstanceId, VAR(uint8, AUTOMATIC) ApiId, VAR(uint8, AUTOMATIC) ErrorId);
FUNC(Std_ReturnType, DET_CODE) Det_ReportTransientFault(VAR(uint16, AUTOMATIC) ModuleId, VAR(uint8, AUTOMATIC) InstanceId, VAR(uint8, AUTOMATIC) ApiId, VAR(uint8, AUTOMATIC) FaultId);
FUNC(void, DET_CODE)Det_Start(void);

#ifdef __cplusplus
}
#endif

#endif

/** @} */
