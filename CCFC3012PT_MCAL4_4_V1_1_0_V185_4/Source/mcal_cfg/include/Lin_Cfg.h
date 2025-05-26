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
*   Autosar Revision     :
*   Autosar Conf.Variant :
*   SW Version           :
*   Build Version        :
*
*****************************************************************************/

/**
 *   @file    Lin_Cfg.h
 *   @version 1.0.1
 *
 *   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
 *   @details Autosar layer of Lin MCAL driver.
 *
 *   @addtogroup Lin
 */

#ifndef LIN_CFG_H
#define LIN_CFG_H

#ifdef __cplusplus
extern "C"
{
#endif
/*=======================================INCLUDE FILES=============================================*/
#include "EcuM_Cbk.h"
#include "Mcal.h"

/*=============================SOURCE FILE VERSION INFORMATION======================================*/
#define LIN_VENDOR_ID_OUTPUT                    176
#define LIN_AR_REL_MJR_VERSION_PLUGIN           4
#define LIN_AR_REL_MNR_VERSION_PLUGIN           4
#define LIN_AR_REL_REV_VERSION_OUTPUT           0
#define LIN_SW_MAJOR_VERSION_OUTPUT             1
#define LIN_SW_MINOR_VERSION_OUTPUT             0
#define LIN_SW_PATCH_VERSION_OUTPUT             1
/* =====================================SOURCE FILE VERSION INFORMATION============================== */
#define LIN_WRAPPER_C_VENDOR_ID                            LIN_VENDOR_ID_PLUGIN
#define LIN_WRAPPER_C_AR_REL_MAJOR_VER                     LIN_AR_REL_MJR_VERSION_PLUGIN
#define LIN_WRAPPER_C_AR_REL_MINOR_VER                     LIN_AR_REL_MNR_VERSION_PLUGIN
#define LIN_WRAPPER_C_AR_REL_REV_VER                       LIN_AR_REL_REV_VERSION_PLUGIN
#define LIN_WRAPPER_C_SW_MAJOR_VER                         LIN_SW_MAJOR_VERSION_PLUGIN
#define LIN_WRAPPER_C_SW_MINOR_VER                         LIN_SW_MINOR_VERSION_PLUGIN
#define LIN_WRAPPER_C_SW_PATCH_VER                         LIN_SW_PATCH_VERSION_PLUGIN
/* ============================================FILE VERSION CHECKS=================================== */
#if (LIN_VENDOR_ID_PLUGIN != LIN_WRAPPER_C_VENDOR_ID)
    #error " NON-MATCHED DATA : LIN_WRAPPER_C_VENDOR_ID "
#endif
#if (LIN_AR_REL_MJR_VERSION_PLUGIN != LIN_WRAPPER_C_AR_REL_MAJOR_VER)
    #error " NON-MATCHED DATA : LIN_WRAPPER_C_AR_REL_MAJOR_VER "
#endif
#if (LIN_AR_REL_MNR_VERSION_PLUGIN != LIN_WRAPPER_C_AR_REL_MINOR_VER)
    #error " NON-MATCHED DATA : LIN_WRAPPER_C_AR_REL_MINOR_VER "
#endif
#if (LIN_AR_REL_REV_VERSION_PLUGIN != LIN_WRAPPER_C_AR_REL_REV_VER)
    #error " NON-MATCHED DATA : LIN_WRAPPER_C_AR_REL_REV_VER "
#endif
#if (LIN_SW_MAJOR_VERSION_PLUGIN != LIN_WRAPPER_C_SW_MAJOR_VER)
    #error " NON-MATCHED DATA : LIN_WRAPPER_C_SW_MAJOR_VER "
#endif
#if (LIN_SW_MINOR_VERSION_PLUGIN != LIN_WRAPPER_C_SW_MINOR_VER)
    #error " NON-MATCHED DATA : LIN_WRAPPER_C_SW_MINOR_VER "
#endif
#if (LIN_SW_PATCH_VERSION_PLUGIN != LIN_WRAPPER_C_SW_PATCH_VER)
    #error " NON-MATCHED DATA : LIN_WRAPPER_C_SW_PATCH_VER "
#endif
/*=========================================CONSTANTS================================================*/

/*=====================================DEFINES AND MACROS===========================================*/

#define LIN_PRECOMPILE_SUPPORT  (STD_OFF) 

#define LIN_HW_MAX_MODULES 15U

#define LIN_MAX_DATA_LENGTH 8U

#define LIN_HW_MAX_AVAILABLE_MODULES 17U

#define LIN_MASTER_NODE_USED  (STD_ON) 

#define LIN_TIMEOUT_LOOPS ((uint32)1000U)

#define LIN_DEV_ERROR_DETECT (STD_ON)

#define LIN_VERSION_INFO_API (STD_ON) 

#define LIN_DISABLE_FRAME_TIMEOUT (STD_OFF)

#define LinHWCh_0    0U
                    
#define LinHWCh_1    1U
                    
#define LinHWCh_2    2U
                    
#define LinHWCh_14    14U
                    
#define LinHWCh_15    15U
                    
#define LinHWCh_16    16U
                    
#define LinHWCh_3    3U
                    
#define LinHWCh_4    4U
                    
#define LinHWCh_6    6U
                    
#define LinHWCh_7    7U
                    
#define LinHWCh_8    8U
                    
#define LinHWCh_9    9U
                    
#define LinHWCh_10    10U
                    
#define LinHWCh_11    11U
                    
#define LinHWCh_12    12U
                    
#define LIN_DISABLE_DEM_REPORT_ERROR_STATUS (STD_ON) 

#define LIN_MULTICORE_SUPPORT (STD_ON)

#define LIN_UNALLOCATEDPAR_CORE_ID 0U

#define LIN_NONE_ECUM_WAKEUP_SOURCE_REF (uint32)0U


#define LIN_MAX_PARTITIONS     ((uint32)6U)

/*============================================ENUMS=================================================*/

/*===============================STRUCTURES AND OTHER TYPEDEFS======================================*/

/*===============================GLOBAL VARIABLE DECLARATIONS=======================================*/

/*===================================FUNCTION PROTOTYPES============================================*/

/*=================================EXTERNAL CONSTANTS===============================================*/

#define LIN_START_SEC_CONFIG_DATA
#include "Lin_MemMap.h"

#define LIN_STOP_SEC_CONFIG_DATA
#include "Lin_MemMap.h"

#ifdef __cplusplus
}
#endif
#endif

/** @} */
