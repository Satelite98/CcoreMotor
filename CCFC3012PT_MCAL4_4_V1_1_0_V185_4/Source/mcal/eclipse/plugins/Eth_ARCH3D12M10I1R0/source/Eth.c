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
*   @file    Eth.c
*   @version 1.0.1
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Eth MCAL driver.
*
*   @addtogroup Eth
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/**
****************************************************************************************
 * @brief: Include Files
****************************************************************************************
*/
#include "Eth.h"
#include "Dem.h"
#if (ETH_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
#include "Eth_AutoSar_Wrapper.h"
#if STD_ON == ETH_CTRLENABLE_MII
#include "EthTrcv.h"
#endif /* ETH_CTRLENABLE_MII */
#include "SchM_Eth.h"

/**
****************************************************************************************
 * @brief: Eth.c Version
****************************************************************************************
*/
#define ETH_C_VENDOR_ID                    176
#define ETH_C_AR_REL_MAJOR_VER             4
#define ETH_C_AR_REL_MINOR_VER             4
#define ETH_C_AR_REL_REV_VER               0
#define ETH_C_SW_MAJOR_VER                 1
#define ETH_C_SW_MINOR_VER                 0
#define ETH_C_SW_PATCH_VER                 1
/**
****************************************************************************************
 * @brief: Version Verify
****************************************************************************************
*/
#if (ETH_CFG_H_VENDOR_ID != ETH_C_VENDOR_ID)
    #error " NON-MATCHED DATA : ETH_C_VENDOR_ID "
#endif
#if (ETH_CFG_H_AR_REL_MAJOR_VER != ETH_C_AR_REL_MAJOR_VER)
    #error " NON-MATCHED DATA : ETH_C_AR_REL_MAJOR_VER "
#endif
#if (ETH_CFG_H_AR_REL_MINOR_VER != ETH_C_AR_REL_MINOR_VER)
    #error " NON-MATCHED DATA : ETH_C_AR_REL_MINOR_VER "
#endif
#if (ETH_CFG_H_AR_REL_REV_VER != ETH_C_AR_REL_REV_VER)
    #error " NON-MATCHED DATA : ETH_C_AR_REL_REV_VER "
#endif
#if (ETH_CFG_H_SW_MAJOR_VER != ETH_C_SW_MAJOR_VER)
    #error " NON-MATCHED DATA : ETH_C_SW_MAJOR_VER "
#endif
#if (ETH_CFG_H_SW_MINOR_VER != ETH_C_SW_MINOR_VER)
    #error " NON-MATCHED DATA : ETH_C_SW_MINOR_VER "
#endif
#if (ETH_CFG_H_SW_PATCH_VER != ETH_C_SW_PATCH_VER)
    #error " NON-MATCHED DATA : ETH_C_SW_PATCH_VER "
#endif

/**
****************************************************************************************
 * @brief: Global Variables
****************************************************************************************
*/
VAR(volatile Eth_ModeType, ETH_VAR) Eth_Ctrlmode[ETH_MAXCTRLS_SUPPORTED] = {ETH_MODE_DOWN};
VAR(volatile Eth_StateType, ETH_VAR) Eth_CtrlState[ETH_MAXCTRLS_SUPPORTED] = {ETH_STATE_UNINIT};
P2CONST(Eth_ConfigType, ETH_VAR, ETH_APPL_CONST) Eth_InternalCfgPtr = NULL_PTR;

/**
****************************************************************************************
 * @brief: Local Functions
****************************************************************************************
*/

#define ETH_START_SEC_CODE
#include "Eth_MemMap.h"

LOCAL_INLINE FUNC(Std_ReturnType, ETH_CODE) Eth_InitVerify \
( \
    P2CONST(Eth_ConfigType, AUTOMATIC, ETH_APPL_CONST) CfgPtr \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Eth_ret = E_NOT_OK;

#if (ETH_PRECOMPILE_SUPPORT == STD_OFF)
    if (NULL_PTR == CfgPtr)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_INIT, \
            ETH_E_PARAM_POINTER \
                                );
#endif
    }
#else
    if (NULL_PTR != CfgPtr)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_INIT, \
            ETH_E_PARAM_POINTER \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#endif
    else
    {
        u8Eth_ret = E_OK;
    }

    return u8Eth_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, ETH_CODE) Eth_SetControllerModeVerify \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Eth_ret = E_NOT_OK;
#if STD_ON == ETH_MULTICORE_ENABLED
    VAR(uint32, AUTOMATIC) u32Eth_CoreId = 0U;

    u32Eth_CoreId = Eth_GetCoreID();    /*get coreid*/
#endif
    if (CtrlIdx >= (uint8)ETH_MAXCTRLS_SUPPORTED)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_SETCONTROLLERMODE, ETH_E_INV_CTRL_IDX \
                              );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (ETH_STATE_INIT != Eth_CtrlState[CtrlIdx])
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_SETCONTROLLERMODE, ETH_E_UNINIT \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#if STD_ON == ETH_MULTICORE_ENABLED
    else if (u32Eth_CoreId != Eth_InternalCfgPtr->pEth_CoreMap[CtrlIdx].CoreId)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT 
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_SETCONTROLLERMODE, \
            ETH_E_PARAM_CONFIG \
                            );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#endif
    else
    {
        u8Eth_ret = E_OK;
    }

    return u8Eth_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, ETH_CODE) Eth_GetControllerModeVerify \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    P2VAR(Eth_ModeType, AUTOMATIC, ETH_APPL_DATA) CtrlModePtr \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Eth_ret = E_NOT_OK;
#if STD_ON == ETH_MULTICORE_ENABLED
    VAR(uint32, AUTOMATIC) u32Eth_CoreId = 0U;

    u32Eth_CoreId = Eth_GetCoreID();    /*get coreid*/
#endif
    if (CtrlIdx >= (uint8)ETH_MAXCTRLS_SUPPORTED)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_GETCONTROLLERMODE, ETH_E_INV_CTRL_IDX \
                              );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (NULL_PTR == CtrlModePtr)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_GETCONTROLLERMODE, ETH_E_PARAM_POINTER \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (ETH_STATE_INIT != Eth_CtrlState[CtrlIdx])
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_GETCONTROLLERMODE, ETH_E_UNINIT \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#if STD_ON == ETH_MULTICORE_ENABLED
    else if (u32Eth_CoreId != Eth_InternalCfgPtr->pEth_CoreMap[CtrlIdx].CoreId)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT 
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_GETCONTROLLERMODE, \
            ETH_E_PARAM_CONFIG \
                            );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#endif
    else
    {
        u8Eth_ret = E_OK;
    }

    return u8Eth_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, ETH_CODE) Eth_GetPhysAddrVerify \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Eth_ret = E_NOT_OK;
#if STD_ON == ETH_MULTICORE_ENABLED
    VAR(uint32, AUTOMATIC) u32Eth_CoreId = 0U;

    u32Eth_CoreId = Eth_GetCoreID();    /*get coreid*/
#endif
    if (CtrlIdx >= (uint8)ETH_MAXCTRLS_SUPPORTED)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_GETPHYSADDR, \
            ETH_E_INV_CTRL_IDX \
                              );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (NULL_PTR == PhysAddrPtr)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_GETPHYSADDR, ETH_E_PARAM_POINTER \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (ETH_STATE_INIT != Eth_CtrlState[CtrlIdx])
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_GETPHYSADDR, ETH_E_UNINIT \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#if STD_ON == ETH_MULTICORE_ENABLED
    else if (u32Eth_CoreId != Eth_InternalCfgPtr->pEth_CoreMap[CtrlIdx].CoreId)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT 
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_GETPHYSADDR, \
            ETH_E_PARAM_CONFIG \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#endif
    else
    {
        u8Eth_ret = E_OK;
    }

    return u8Eth_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, ETH_CODE) Eth_SetPhysAddrVerify \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    P2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) PhysAddrPtr \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Eth_ret = E_NOT_OK;
#if STD_ON == ETH_MULTICORE_ENABLED
    VAR(uint32, AUTOMATIC) u32Eth_CoreId = 0U;

    u32Eth_CoreId = Eth_GetCoreID();    /*get coreid*/
#endif
    if (CtrlIdx >= (uint8)ETH_MAXCTRLS_SUPPORTED)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_SETPHYSADDR, \
            ETH_E_INV_CTRL_IDX \
                              );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (NULL_PTR == PhysAddrPtr)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_SETPHYSADDR, ETH_E_PARAM_POINTER \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (ETH_STATE_INIT != Eth_CtrlState[CtrlIdx])
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_SETPHYSADDR, ETH_E_UNINIT \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#if STD_ON == ETH_MULTICORE_ENABLED
    else if (u32Eth_CoreId != Eth_InternalCfgPtr->pEth_CoreMap[CtrlIdx].CoreId)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT 
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_SETPHYSADDR, \
            ETH_E_PARAM_CONFIG \
                            );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#endif
    else
    {
        u8Eth_ret = E_OK;
    }

    return u8Eth_ret;
}

#if STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER
LOCAL_INLINE FUNC(Std_ReturnType, ETH_CODE) Eth_UpdatePhysAddrFilterVerify \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    P2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) PhysAddrPtr \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Eth_ret = E_NOT_OK;
#if STD_ON == ETH_MULTICORE_ENABLED
    VAR(uint32, AUTOMATIC) u32Eth_CoreId = 0U;

    u32Eth_CoreId = Eth_GetCoreID();    /*get coreid*/
#endif
    if (CtrlIdx >= (uint8)ETH_MAXCTRLS_SUPPORTED)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
          (uint8) ETH_MODULE_ID, ETH_DRIVER_INSTANCE, \
          (uint8) ETH_SID_UPDATEADDRFILTER, \
          ETH_E_INV_CTRL_IDX \
                              );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (NULL_PTR == PhysAddrPtr)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_UPDATEADDRFILTER, ETH_E_PARAM_POINTER \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (ETH_STATE_INIT != Eth_CtrlState[CtrlIdx])
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_UPDATEADDRFILTER, ETH_E_UNINIT \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#if STD_ON == ETH_MULTICORE_ENABLED
    else if (u32Eth_CoreId != Eth_InternalCfgPtr->pEth_CoreMap[CtrlIdx].CoreId)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT 
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_UPDATEADDRFILTER, \
            ETH_E_PARAM_CONFIG \
                            );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#endif
    else
    {
        u8Eth_ret = E_OK;
    }

    return u8Eth_ret;
}
#endif /* STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER */

#if STD_ON == ETH_CTRLENABLE_MII
LOCAL_INLINE FUNC(Std_ReturnType, ETH_CODE) Eth_WriteMiiVerify \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Eth_ret = E_NOT_OK;
#if STD_ON == ETH_MULTICORE_ENABLED
    VAR(uint32, AUTOMATIC) u32Eth_CoreId = 0U;

    u32Eth_CoreId = Eth_GetCoreID();    /*get coreid*/
#endif
    if (CtrlIdx >= (uint8)ETH_MAXCTRLS_SUPPORTED)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_WRITEMII, \
            ETH_E_INV_CTRL_IDX \
                              );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (ETH_STATE_INIT != Eth_CtrlState[CtrlIdx])
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_WRITEMII, \
            ETH_E_UNINIT \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#if STD_ON == ETH_MULTICORE_ENABLED
    else if (u32Eth_CoreId != Eth_InternalCfgPtr->pEth_CoreMap[CtrlIdx].CoreId)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT 
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_WRITEMII, \
            ETH_E_PARAM_CONFIG \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#endif
    else
    {
        u8Eth_ret = E_OK;
    }

    return u8Eth_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, ETH_CODE) Eth_ReadMiiVerify \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    P2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) RegValPtr \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Eth_ret = E_NOT_OK;
#if STD_ON == ETH_MULTICORE_ENABLED
    VAR(uint32, AUTOMATIC) u32Eth_CoreId = 0U;

    u32Eth_CoreId = Eth_GetCoreID();    /*get coreid*/
#endif
    if (CtrlIdx >= (uint8)ETH_MAXCTRLS_SUPPORTED)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_READMII, \
            ETH_E_INV_CTRL_IDX \
                              );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (NULL_PTR == RegValPtr)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_READMII, ETH_E_PARAM_POINTER \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (ETH_STATE_INIT != Eth_CtrlState[CtrlIdx])
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_READMII, ETH_E_UNINIT \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#if STD_ON == ETH_MULTICORE_ENABLED
    else if (u32Eth_CoreId != Eth_InternalCfgPtr->pEth_CoreMap[CtrlIdx].CoreId)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT 
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_READMII, \
            ETH_E_PARAM_CONFIG \
                            );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#endif
    else
    {
        u8Eth_ret = E_OK;
    }

    return u8Eth_ret;
}
#endif /* ETH_CTRLENABLE_MII */

#if STD_ON == ETH_GET_COUNTVAL_API
LOCAL_INLINE FUNC(Std_ReturnType, ETH_CODE) Eth_GetCounterValuesVerify \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    P2VAR(Eth_CounterType, AUTOMATIC, ETH_APPL_DATA) CounterPtr \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Eth_ret = E_NOT_OK;
#if STD_ON == ETH_MULTICORE_ENABLED
    VAR(uint32, AUTOMATIC) u32Eth_CoreId = 0U;

    u32Eth_CoreId = Eth_GetCoreID();    /*get coreid*/
#endif
    if (CtrlIdx >= ETH_MAXCTRLS_SUPPORTED)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_GETCOUNTERVALUES, \
            ETH_E_INV_CTRL_IDX \
                              );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (ETH_STATE_INIT != Eth_CtrlState[CtrlIdx])
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_GETCOUNTERVALUES, ETH_E_UNINIT \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (NULL_PTR == CounterPtr)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_GETCOUNTERVALUES, \
            ETH_E_PARAM_POINTER \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#if STD_ON == ETH_MULTICORE_ENABLED
    else if (u32Eth_CoreId != Eth_InternalCfgPtr->pEth_CoreMap[CtrlIdx].CoreId)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT 
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_GETCOUNTERVALUES, \
            ETH_E_PARAM_CONFIG \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#endif
    else
    {
        u8Eth_ret = E_OK;
    }

    return u8Eth_ret;
}
#endif /* ETH_GET_COUNTVAL_API */

#if STD_ON == ETH_GET_RXSTATS_API
LOCAL_INLINE FUNC(Std_ReturnType, ETH_CODE) Eth_GetRxStatsVerify \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    P2VAR(Eth_RxStatsType, AUTOMATIC, ETH_APPL_DATA) RxStats \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Eth_ret = E_NOT_OK;
#if STD_ON == ETH_MULTICORE_ENABLED
    VAR(uint32, AUTOMATIC) u32Eth_CoreId = 0U;

    u32Eth_CoreId = Eth_GetCoreID();    /*get coreid*/
#endif
    if (CtrlIdx >= ETH_MAXCTRLS_SUPPORTED)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_GETRXSTATS, \
            ETH_E_INV_CTRL_IDX \
                              );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (ETH_STATE_INIT != Eth_CtrlState[CtrlIdx])
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_GETRXSTATS, ETH_E_UNINIT \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (NULL_PTR == RxStats)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_GETRXSTATS, \
            ETH_E_PARAM_POINTER \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#if STD_ON == ETH_MULTICORE_ENABLED
    else if (u32Eth_CoreId != Eth_InternalCfgPtr->pEth_CoreMap[CtrlIdx].CoreId)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT 
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_GETRXSTATS, \
            ETH_E_PARAM_CONFIG \
                            );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#endif
    else
    {
        u8Eth_ret = E_OK;
    }

    return u8Eth_ret;
}
#endif /* ETH_GET_RXSTATS_API */

#if STD_ON == ETH_GET_TXSTATS_API
LOCAL_INLINE FUNC(Std_ReturnType, ETH_CODE) Eth_GetTxStatsVerify \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    P2VAR(Eth_TxStatsType, AUTOMATIC, ETH_APPL_DATA) TxStats \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Eth_ret = E_NOT_OK;
#if STD_ON == ETH_MULTICORE_ENABLED
    VAR(uint32, AUTOMATIC) u32Eth_CoreId = 0U;

    u32Eth_CoreId = Eth_GetCoreID();    /*get coreid*/
#endif
    if (CtrlIdx >= ETH_MAXCTRLS_SUPPORTED)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_GETTXSTATS, ETH_E_INV_CTRL_IDX \
                              );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (ETH_STATE_INIT != Eth_CtrlState[CtrlIdx])
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_GETTXSTATS, ETH_E_UNINIT \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (NULL_PTR == TxStats)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_GETTXSTATS, ETH_E_PARAM_POINTER \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#if STD_ON == ETH_MULTICORE_ENABLED
    else if (u32Eth_CoreId != Eth_InternalCfgPtr->pEth_CoreMap[CtrlIdx].CoreId)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT 
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_GETTXSTATS, \
            ETH_E_PARAM_CONFIG \
                            );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#endif
    else
    {
        u8Eth_ret = E_OK;
    }

    return u8Eth_ret;
}
#endif /* ETH_GET_TXSTATS_API */

#if STD_ON == ETH_GET_TXERRORCOUNT_API
LOCAL_INLINE FUNC(Std_ReturnType, ETH_CODE) Eth_GetTxErrorCounterValuesVerify \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    P2VAR(Eth_TxErrorCounterValuesType, AUTOMATIC, ETH_APPL_DATA) TxErrorCounterValues \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Eth_ret = E_NOT_OK;
#if STD_ON == ETH_MULTICORE_ENABLED
    VAR(uint32, AUTOMATIC) u32Eth_CoreId = 0U;

    u32Eth_CoreId = Eth_GetCoreID();    /*get coreid*/
#endif
    if (CtrlIdx >= ETH_MAXCTRLS_SUPPORTED)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_GETTXERRORCOUNTERVALUES, ETH_E_INV_CTRL_IDX \
                              );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (ETH_STATE_INIT != Eth_CtrlState[CtrlIdx])
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_GETTXERRORCOUNTERVALUES, ETH_E_UNINIT \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (NULL_PTR == TxErrorCounterValues)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_GETTXERRORCOUNTERVALUES, ETH_E_PARAM_POINTER \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#if STD_ON == ETH_MULTICORE_ENABLED
    else if (u32Eth_CoreId != Eth_InternalCfgPtr->pEth_CoreMap[CtrlIdx].CoreId)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT 
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_GETTXERRORCOUNTERVALUES, \
            ETH_E_PARAM_CONFIG \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#endif
    else
    {
        u8Eth_ret = E_OK;
    }

    return u8Eth_ret;
}
#endif /* ETH_GET_TXERRORCOUNT_API */

LOCAL_INLINE FUNC(Std_ReturnType, ETH_CODE) Eth_ProvideTxBufferVerify \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    P2VAR(Eth_BufIdxType, AUTOMATIC, ETH_APPL_DATA) BufIdxPtr, \
    P2P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) BufPtr, \
    P2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LenBytePtr \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Eth_ret = E_NOT_OK;
#if STD_ON == ETH_MULTICORE_ENABLED
    VAR(uint32, AUTOMATIC) u32Eth_CoreId = 0U;

    u32Eth_CoreId = Eth_GetCoreID();    /*get coreid*/
#endif
    if (CtrlIdx >= (uint8)ETH_MAXCTRLS_SUPPORTED)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_PROVIDETXBUFFER, ETH_E_INV_CTRL_IDX \
                              );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (NULL_PTR == BufIdxPtr)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_PROVIDETXBUFFER, ETH_E_PARAM_POINTER \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (NULL_PTR == BufPtr)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_PROVIDETXBUFFER, ETH_E_PARAM_POINTER \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (NULL_PTR == LenBytePtr)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_PROVIDETXBUFFER, ETH_E_PARAM_POINTER \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (ETH_STATE_INIT != Eth_CtrlState[CtrlIdx])
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_PROVIDETXBUFFER, ETH_E_UNINIT \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#if STD_ON == ETH_MULTICORE_ENABLED
    else if (u32Eth_CoreId != Eth_InternalCfgPtr->pEth_CoreMap[CtrlIdx].CoreId)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT 
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_PROVIDETXBUFFER, \
            ETH_E_PARAM_CONFIG \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#endif
    else
    {
        u8Eth_ret = E_OK;
    }

    return u8Eth_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, ETH_CODE) Eth_TransmitVerify \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    VAR(Eth_BufIdxType, AUTOMATIC) BufIdx, \
    P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Eth_ret = E_NOT_OK;
#if STD_ON == ETH_MULTICORE_ENABLED
    VAR(uint32, AUTOMATIC) u32Eth_CoreId = 0U;

    u32Eth_CoreId = Eth_GetCoreID();    /*get coreid*/
#endif
    if (CtrlIdx >= (uint8)ETH_MAXCTRLS_SUPPORTED)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_TRANSMIT, \
            ETH_E_INV_CTRL_IDX \
                              );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (NULL_PTR == PhysAddrPtr)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_TRANSMIT, ETH_E_PARAM_POINTER \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (ETH_STATE_INIT != Eth_CtrlState[CtrlIdx])
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_TRANSMIT, ETH_E_UNINIT \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (ETH_MODE_ACTIVE != Eth_AutoSar_Wrapper_Check_Ctrl_Is_Active(CtrlIdx))
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_TRANSMIT, ETH_E_INV_MODE \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (BufIdx >= (Eth_BufIdxType)TX_BUFFER_COUNT)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
        (uint8) ETH_MODULE_ID, \
        ETH_DRIVER_INSTANCE, (uint8) \
        ETH_SID_TRANSMIT, ETH_E_INV_PARAM \
                        );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#if STD_ON == ETH_MULTICORE_ENABLED
    else if (u32Eth_CoreId != Eth_InternalCfgPtr->pEth_CoreMap[CtrlIdx].CoreId)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT 
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_TRANSMIT, \
            ETH_E_PARAM_CONFIG \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#endif
    else
    {
        u8Eth_ret = E_OK;
    }

    return u8Eth_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, ETH_CODE) Eth_ReceiveVerify \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Eth_ret = E_NOT_OK;
#if STD_ON == ETH_MULTICORE_ENABLED
    VAR(uint32, AUTOMATIC) u32Eth_CoreId = 0U;

    u32Eth_CoreId = Eth_GetCoreID();    /*get coreid*/
#endif
    if (CtrlIdx >= (uint8)ETH_MAXCTRLS_SUPPORTED)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_RECEIVE, \
            ETH_E_INV_CTRL_IDX \
                              );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (ETH_STATE_INIT != Eth_CtrlState[CtrlIdx])
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_RECEIVE, \
            ETH_E_UNINIT \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (ETH_MODE_ACTIVE != Eth_AutoSar_Wrapper_Check_Ctrl_Is_Active(CtrlIdx))
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_RECEIVE, ETH_E_INV_MODE \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#if STD_ON == ETH_MULTICORE_ENABLED
    else if (u32Eth_CoreId != Eth_InternalCfgPtr->pEth_CoreMap[CtrlIdx].CoreId)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT 
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_RECEIVE, \
            ETH_E_PARAM_CONFIG \
                            );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#endif
    else
    {
        u8Eth_ret = E_OK;
    }

    return u8Eth_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, ETH_CODE) Eth_TxConfirmationVerify(VAR(uint8, AUTOMATIC) CtrlIdx)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Eth_ret = E_NOT_OK;
#if STD_ON == ETH_MULTICORE_ENABLED
    VAR(uint32, AUTOMATIC) u32Eth_CoreId = 0U;

    u32Eth_CoreId = Eth_GetCoreID();    /*get coreid*/
#endif
    if (CtrlIdx >= (uint8)ETH_MAXCTRLS_SUPPORTED)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_TXCONFIRMATION, ETH_E_INV_CTRL_IDX \
                              );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (ETH_STATE_INIT != Eth_CtrlState[CtrlIdx])
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_TXCONFIRMATION, ETH_E_UNINIT \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
    else if (ETH_MODE_ACTIVE != Eth_AutoSar_Wrapper_Check_Ctrl_Is_Active(CtrlIdx))
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) \
            ETH_SID_TXCONFIRMATION, ETH_E_INV_MODE \
                                );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#if STD_ON == ETH_MULTICORE_ENABLED
    else if (u32Eth_CoreId != Eth_InternalCfgPtr->pEth_CoreMap[CtrlIdx].CoreId)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT 
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_TXCONFIRMATION, \
            ETH_E_PARAM_CONFIG \
                            );
#endif /* ETH_DEV_ERROR_DETECT  */
    }
#endif
    else
    {
        u8Eth_ret = E_OK;
    }

    return u8Eth_ret;
}

#if STD_ON == ETH_GET_VERSION_INFO_API
LOCAL_INLINE FUNC(Std_ReturnType, ETH_CODE) Eth_GetVersionInfoVerify \
( \
    P2VAR(Std_VersionInfoType, AUTOMATIC, ETH_APPL_DATA) VersionInfoPtr \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Eth_ret = E_NOT_OK;

    if (NULL_PTR == VersionInfoPtr)
    {
#if STD_ON == ETH_DEV_ERROR_DETECT
        (void)Det_ReportError ( \
            (uint8) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (uint8) ETH_SID_GETVERSIONINFO, ETH_E_PARAM_POINTER \
                              );
#endif
    }
    else
    {
        u8Eth_ret = E_OK;
    }

    return u8Eth_ret;
}
#endif /* ETH_GET_VERSION_INFO_API */

/**
****************************************************************************************
 * @brief: Global Functions
****************************************************************************************
*/
/**
****************************************************************************************
* @brief         Initializes the Ethernet Driver
* @param[in]     CfgPtr Points to the implementation specific structure containing
*                the Eth driver configuration
* @return void
****************************************************************************************
*/

FUNC(void, ETH_CODE) Eth_Init(P2CONST(Eth_ConfigType, AUTOMATIC, ETH_APPL_CONST) CfgPtr)
{
    VAR(uint8, AUTOMATIC) u8CtrlCount = 0U;
#if STD_ON == ETH_MULTICORE_ENABLED
    VAR(uint32, AUTOMATIC) u32Eth_CoreId = 0U;

    u32Eth_CoreId = Eth_GetCoreID();    /*get coreid*/
#endif
    if ((Std_ReturnType)E_OK == Eth_InitVerify(CfgPtr))
    {
        if (Eth_InternalCfgPtr == NULL_PTR)
        {
#if (ETH_PRECOMPILE_SUPPORT == STD_ON)
            Eth_InternalCfgPtr = &Eth_Config;
            (void)CfgPtr;
#else
            /* config param */
            Eth_InternalCfgPtr = CfgPtr;
#endif
        }

        for (u8CtrlCount = ETH_MIN_CTRLIDX; u8CtrlCount <= ETH_MAX_CTRLIDX; u8CtrlCount++)
        {
#if STD_ON == ETH_MULTICORE_ENABLED
            if (u32Eth_CoreId == Eth_InternalCfgPtr->pEth_CoreMap[u8CtrlCount].CoreId)
            {
#endif
                Eth_AutoSar_Wrapper_InitController(u8CtrlCount);
#if STD_ON == ETH_MULTICORE_ENABLED
            }
#endif
        }
    }
}

/**
****************************************************************************************
* @brief         Enables or disables the given controller
* @param[in]     CtrlIdx Index of the controller to be enabled or disabled.
*                The index is valid within the context of the Ethernet Driver
*                only.
* @param[in]     CtrlMode Mode which shall be entered
*                - ETH_MODE_DOWN: disable the controller
*                - ETH_MODE_ACTIVE: enable the controller
* @return        Error status
****************************************************************************************
*/

FUNC(Std_ReturnType, ETH_CODE) Eth_SetControllerMode \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    VAR(Eth_ModeType, AUTOMATIC) CtrlMode \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8FunctionSuccess = (Std_ReturnType)E_NOT_OK;
    if ((Std_ReturnType)E_OK == Eth_SetControllerModeVerify(CtrlIdx))
    {
        u8FunctionSuccess = Eth_AutoSar_Wrapper_SetControllerMode(CtrlIdx, CtrlMode);

    }

    return u8FunctionSuccess;
}

/**
****************************************************************************************
* @brief         Obtains the mode of the given controller
* @param[in]     CtrlIdx Index of the controller which state shall be read.
*                The index is valid within the context of the Ethernet Driver
*                only.
* @param[out]    CtrlModePtr Pointer where to store the current controller mode.
* @return        Error status
****************************************************************************************
*/

FUNC(Std_ReturnType, ETH_CODE) Eth_GetControllerMode \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    P2VAR(Eth_ModeType, AUTOMATIC, ETH_APPL_DATA) CtrlModePtr \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8FunctionSuccess = (Std_ReturnType)E_NOT_OK;
    /* Variable used to track the function execution success status */

    if ((Std_ReturnType)E_OK == Eth_GetControllerModeVerify(CtrlIdx, CtrlModePtr))
    {
        Eth_AutoSar_Wrapper_GetControllerMode(CtrlIdx, CtrlModePtr);
        u8FunctionSuccess = (Std_ReturnType)E_OK;
    }

    return u8FunctionSuccess;
}
  

/**
****************************************************************************************
* @brief         Obtains the physical source address used by the indexed
*                controller (the node MAC address).
* @param[in]     CtrlIdx Index of the controller which MAC address should be
*                read. The index is valid within the context of the Ethernet
*                Driver only.
* @param[out]    PhysAddrPtr Pointer where to store physical source address
*                (MAC address). The address in network byte order is stored into
*                6 bytes at the given memory address.
* @return void
****************************************************************************************
*/

FUNC(void, ETH_CODE) Eth_GetPhysAddr \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr \
)
{
    if ((Std_ReturnType)E_OK == Eth_GetPhysAddrVerify(CtrlIdx, PhysAddrPtr))
    {
        Eth_AutoSar_Wrapper_GetPhysAddr(CtrlIdx, PhysAddrPtr);
    }
}  

/**
****************************************************************************************
* @brief         Set or change physical address to the defined controller.
* @param[in]     CtrlIdx Index of the controller which PHY address should be
*                changed. The index is valid within the context of the Ethernet
*                Driver only.
* @param[in]     PhysAddrPtr Pointer to PHY address which should be set to
*                the controller. The address is stored in 6 bytes of memory
*                in network byte order.
* @return void
****************************************************************************************
*/

FUNC(void, ETH_CODE) Eth_SetPhysAddr \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    P2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) PhysAddrPtr \
)
{
    if ((Std_ReturnType)E_OK == Eth_SetPhysAddrVerify(CtrlIdx, PhysAddrPtr))
    {
        Eth_AutoSar_Wrapper_SetPhysAddr(CtrlIdx, PhysAddrPtr);
    }
}

#if STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER
/**
****************************************************************************************
* @brief         Adds or removes the specific @c PhysAddrPtr address to or from
*                a multicast address pool at controller specified by @c CtrlIdx
*                index.
* @param[in]     CtrlIdx Index of the controller. The index is valid within
*                the context of the Ethernet Driver only.
* @param[in]     PhysAddrPtr Pointer to PHY address which shall be added
*                or removed to or from multicast pool.
*                The address in network byte order stored into 6 bytes of
*                memory.
* @param[in]     Action Determine whenever the defined address will be added
*                to the pool ETH_ADD_TO_FILTER or removed from it
*                ETH_REMOVE_FROM_FILTER.
* @return Std_ReturnType
****************************************************************************************
*/

FUNC(Std_ReturnType, ETH_CODE) Eth_UpdatePhysAddrFilter \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    P2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) PhysAddrPtr, \
    VAR(Eth_FilterActionType, AUTOMATIC) Action \
)
{
    VAR(Std_ReturnType, AUTOMATIC) eReturnStatus = (Std_ReturnType)E_NOT_OK;

    if ((Std_ReturnType)E_OK == Eth_UpdatePhysAddrFilterVerify(CtrlIdx, PhysAddrPtr))
    {
        if ((Eth_FilterActionType)Action <= ETH_REMOVE_FROM_FILTER)
        {
            Eth_AutoSar_Wrapper_UpdatePhysAddrFilter(CtrlIdx, PhysAddrPtr, Action);
            eReturnStatus = (Std_ReturnType)E_OK;
        }
        else
        {
            eReturnStatus = (Std_ReturnType)E_NOT_OK;
        }
    }
    return eReturnStatus;
}
#endif /* STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER */

#if STD_ON == ETH_CTRLENABLE_MII
/**
****************************************************************************************
* @brief         Writes to a transceiver (physical layer driver) register.
* @param[in]     CtrlIdx Index of the controller which transceiver register
*                shall be written. The index is valid within the context of
*                the Ethernet Driver only.
* @param[in]     TrcvIdx Index of the transceiver connected the MII. The value
*                shall be within the range 0..31.
* @param[in]     RegIdx Index of the transceiver register to be written. The
*                value shall be within the range 0..31.
* @param[in]     RegVal Value to be written into the indexed register.
* @return Std_ReturnType
****************************************************************************************
*/

FUNC(Std_ReturnType, ETH_CODE) Eth_WriteMii \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    VAR(uint8, AUTOMATIC) TrcvIdx, \
    VAR(uint8, AUTOMATIC) RegIdx, \
    VAR(uint16, AUTOMATIC) RegVal \
)
{
    VAR(Std_ReturnType, AUTOMATIC) eReturnStatus = (Std_ReturnType)E_NOT_OK;

    if ((Std_ReturnType)E_OK == Eth_WriteMiiVerify(CtrlIdx))
    {
        if ((boolean)TRUE == Eth_AutoSar_Wrapper_WriteMii(CtrlIdx, TrcvIdx, RegIdx, RegVal))
        {
            Eth_InternalCfgPtr->pController[CtrlIdx].Eth_EthTrcvDriverFunctionList.writeMiiIndicationFunction(CtrlIdx, TrcvIdx, RegIdx);
            eReturnStatus = (Std_ReturnType)E_OK;
        }
    }

    return eReturnStatus;
}

/**
****************************************************************************************
* @brief          Reads a transceiver (physical layer driver) register.
* @param[in]      CtrlIdx Index of the controller which transceiver register
*                 shall be read. The index is valid within the context of
*                 the Ethernet Driver only.
* @param[in]      TrcvIdx Index of the transceiver connected on the MII. The
*                 value shall be within the range 0..31.
* @param[in]      RegIdx Index of the transceiver register to be read. The
*                 Value shall be within the range 0..31.
* @param[out]     RegValPtr Filled with the register content of the indexed register
* @return Std_ReturnType
****************************************************************************************
*/

FUNC(Std_ReturnType, ETH_CODE) Eth_ReadMii \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    VAR(uint8, AUTOMATIC) TrcvIdx, \
    VAR(uint8, AUTOMATIC) RegIdx, \
    P2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) RegValPtr \
)
{
    VAR(Std_ReturnType, AUTOMATIC) eReturnStatus = (Std_ReturnType)E_NOT_OK;
    
    if ((Std_ReturnType)E_OK == Eth_ReadMiiVerify(CtrlIdx, RegValPtr))
    {
        if ((boolean)TRUE == Eth_AutoSar_Wrapper_ReadMii(CtrlIdx, TrcvIdx, RegIdx, RegValPtr))
        {
            Eth_InternalCfgPtr->pController[CtrlIdx].Eth_EthTrcvDriverFunctionList.readMiiIndicationFunction(CtrlIdx, TrcvIdx, RegIdx, *RegValPtr);
            eReturnStatus = (Std_ReturnType)E_OK;
        }
    }

    return eReturnStatus;
}
#endif /* ETH_CTRLENABLE_MII */

#if STD_ON == ETH_GET_COUNTVAL_API
/**
****************************************************************************************
* @brief            Reads a list with drop counter values of the corresponding controller.
* @param[in]        CtrlIdx Index of the controller which shall be be read the drop
*                   package counts.
* @param[in,out]    CountValues The number of values which return.
*                   -In: Maximal number of values which can be written from DropCount.
*                   -Out: Number of values which are returned in the DropCount list.
* @param[out]       DropCount The interpretation of this list of values is hardware 
*                   dependent
* @return           Error status
****************************************************************************************
*/

FUNC(Std_ReturnType, ETH_CODE) Eth_GetCounterValues \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    P2VAR(Eth_CounterType, AUTOMATIC, ETH_APPL_DATA) CounterPtr \
)
{
    VAR(Std_ReturnType, AUTOMATIC) eReturnStatus = (Std_ReturnType)E_NOT_OK;

    if ((Std_ReturnType)E_OK == Eth_GetCounterValuesVerify(CtrlIdx, CounterPtr))
    {
        Eth_AutoSar_Wrapper_GetCounterValues(CtrlIdx, CounterPtr);
        eReturnStatus = (Std_ReturnType)E_OK;
    }
    return eReturnStatus;
}
#endif /* ETH_GET_COUNTVAL_API */

#if STD_ON == ETH_GET_RXSTATS_API
/**
****************************************************************************************
* @brief        Read the status of a controller
* @param[in]    CtrlIdx Index of the controller which shall be read the status register.
* @param[out]   etherStats Pointer to 32 bit long memory space to be filled with
*               the list values according to IETF RFC 2819 (Remote Network 
*               Monitoring Management Information Base). 
* @return       Error status
****************************************************************************************
*/

FUNC(Std_ReturnType, ETH_CODE) Eth_GetRxStats \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    P2VAR(Eth_RxStatsType, AUTOMATIC, ETH_APPL_DATA) RxStats \
)
{
    VAR(Std_ReturnType, AUTOMATIC) eReturnStatus = (Std_ReturnType)E_NOT_OK;

    if ((Std_ReturnType)E_OK == Eth_GetRxStatsVerify(CtrlIdx, RxStats))
    {
        Eth_AutoSar_Wrapper_GetRxStats(CtrlIdx, RxStats);
        eReturnStatus = (Std_ReturnType)E_OK;
    }
    return eReturnStatus;
}
#endif /* ETH_GET_RXSTATS_API */

#if STD_ON == ETH_GET_TXSTATS_API
/**
****************************************************************************************
* @brief        Read the status of a controller
* @param[in]    CtrlIdx Index of the controller which shall be read the status register.
* @param[out]   TxStats Pointer to 32 bit long memory space to be filled with
*               the list values according to IETF RFC1213. 
* @return       Error status
****************************************************************************************
*/

FUNC(Std_ReturnType, ETH_CODE) Eth_GetTxStats \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    P2VAR(Eth_TxStatsType, AUTOMATIC, ETH_APPL_DATA) TxStats \
)
{
    VAR(Std_ReturnType, AUTOMATIC) eReturnStatus = (Std_ReturnType)E_NOT_OK;

    if ((Std_ReturnType)E_OK == Eth_GetTxStatsVerify(CtrlIdx, TxStats))
    {
        Eth_AutoSar_Wrapper_GetTxStats(CtrlIdx, TxStats);
        eReturnStatus = (Std_ReturnType)E_OK;
    }

    return eReturnStatus;
}
#endif /* ETH_GET_TXSTATS_API */

#if STD_ON == ETH_GET_TXERRORCOUNT_API
/**
****************************************************************************************
* @brief        Read the status of a controller
* @param[in]    CtrlIdx Index of the controller which shall be read the status register.
* @param[out]   TxErrorCounterValues Pointer to 32 bit long memory space to be filled with
*               the list values according to IETF RFC1213. 
* @return       Error status
****************************************************************************************
*/

FUNC(Std_ReturnType, ETH_CODE) Eth_GetTxErrorCounterValues \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    P2VAR(Eth_TxErrorCounterValuesType, AUTOMATIC, ETH_APPL_DATA) TxErrorCounterValues \
)
{
    VAR(Std_ReturnType, AUTOMATIC) eReturnStatus = (Std_ReturnType)E_NOT_OK;

    if ((Std_ReturnType)E_OK == Eth_GetTxErrorCounterValuesVerify(CtrlIdx, TxErrorCounterValues))
    {
        Eth_AutoSar_Wrapper_GetTxErrorCounterValues(CtrlIdx, TxErrorCounterValues);
        eReturnStatus = (Std_ReturnType)E_OK;
    }

    return eReturnStatus;
}
#endif /* ETH_GET_TXERRORCOUNT_API */

/**
****************************************************************************************
* @brief         Provides access to a transmit buffer of the specified
*                controller.
* @param[in]     CtrlIdx Index of the controller which buffer shall be provided.
*                The index is valid within the context of the Ethernet Driver
*                only.
* @param[out]    BufIdxPtr Index to the granted transmit buffer resource.
*                It uniquely identifies the buffer in all subsequent calls of
*                functions Eth_Transmit() and Eth_TxConfirmation().
* @param[out]    BufPtr Pointer to the granted buffer. This is the space where
*                the data to be transmitted shall be stored.
* @param[in,out] LenBytePtr Buffer payload length
*                - In: desired length in bytes
*                - Out: granted length in bytes
* @return        Error and buffer status
****************************************************************************************
*/

FUNC(BufReq_ReturnType, ETH_CODE) Eth_ProvideTxBuffer \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    VAR(uint8, AUTOMATIC) Priority, \
    P2VAR(Eth_BufIdxType, AUTOMATIC, ETH_APPL_DATA) BufIdxPtr, \
    P2P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) BufPtr, \
    P2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LenBytePtr \
)
{
    /* Variable used to track function success status */
    VAR(BufReq_ReturnType, AUTOMATIC) eFunctionSuccess = BUFREQ_E_NOT_OK;

    if ((Std_ReturnType)E_OK == Eth_ProvideTxBufferVerify(CtrlIdx, BufIdxPtr, BufPtr, LenBytePtr))
    {
        eFunctionSuccess = Eth_AutoSar_Wrapper_ProvideTxBuffer(CtrlIdx, Priority, BufIdxPtr, BufPtr, LenBytePtr);
    }

    return eFunctionSuccess;
}

/**
****************************************************************************************
* @brief         Triggers transmission of a previously granted and then filled
*                transmit buffer.
* @param[in]     CtrlIdx Index of the controller which buffer shall be
*                transmitted. The index is valid within the context of
*                the Ethernet Driver only.
* @param[in]     BufIdx Index of the buffer resource to be transmitted.
* @param[in]     FrameType Desired value of the Ethernet frame type in the
*                frame header.
* @param[in]     TxConfirmation Activates transmission confirmation.
* @param[in]     LenByte Buffer data length in bytes (payload length).
* @param[in]     PhysAddrPtr Physical target address (MAC address) in network
*                byte order.
* @return        Error status
****************************************************************************************
*/

FUNC(Std_ReturnType, ETH_CODE) Eth_Transmit \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    VAR(Eth_BufIdxType, AUTOMATIC) BufIdx, \
    VAR(Eth_FrameType, AUTOMATIC) FrameType, \
    VAR(boolean, AUTOMATIC) TxConfirmation, \
    VAR(uint16, AUTOMATIC) LenByte, \
    P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr
#if STD_ON == ETH_BRIDGE_SUPPORT
    , P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) PhysSourceAddrPtr
#endif /* ETH_BRIDGE_SUPPORT  */
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8FunctionSuccess = (Std_ReturnType)E_NOT_OK; /* Used to track function success */

    if ((Std_ReturnType)E_OK == Eth_TransmitVerify(CtrlIdx, BufIdx, PhysAddrPtr))
    {
        u8FunctionSuccess = Eth_AutoSar_Wrapper_Transmit(CtrlIdx, BufIdx, FrameType, TxConfirmation, LenByte, PhysAddrPtr
#if STD_ON == ETH_BRIDGE_SUPPORT
                                                        , PhysSourceAddrPtr
#endif
                                                        );
    }

    return u8FunctionSuccess; 
}
/**
****************************************************************************************
* @brief         Triggers frames reception notifications.
* @param[in]     CtrlIdx Index of the controller which shall be checked whether
*                any new frames were received. The index is valid within
*                the context of the Ethernet Driver only.
* @param[in]     FifoIdx Specifies the related FIFO
* @param[out]    RxStatusPtr Informs the caller whether a frame was received 
*                (@c ETH_RECEIVED or @c ETH_NOT_RECEIVED) and whether more frames
*                are available in the queue (@c ETH_RECEIVED or 
*                @c ETH_RECEIVED_MORE_DATA_AVAILABLE).
* @return void
****************************************************************************************
*/

FUNC(void, ETH_CODE) Eth_Receive \
( \
    VAR(uint8, AUTOMATIC) CtrlIdx, \
    VAR(uint8, AUTOMATIC) FifoIdx, \
    P2VAR(Eth_RxStatusType, AUTOMATIC, ETH_APPL_DATA) RxStatusPtr \
)
{
    if ((Std_ReturnType)E_OK == Eth_ReceiveVerify(CtrlIdx))
    {
        Eth_AutoSar_Wrapper_Receive(CtrlIdx, FifoIdx, RxStatusPtr);
    }
}

/**
****************************************************************************************
* @brief         Triggers frame transmission confirmations.
* @param[in]     CtrlIdx Index of the controller which shall be checked whether
*                any frame transmission has finished. The index is valid within
*                the context of the Ethernet Driver only.
* @return void
****************************************************************************************
*/

FUNC(void, ETH_CODE) Eth_TxConfirmation(VAR(uint8, AUTOMATIC) CtrlIdx)
{
    VAR(uint8, AUTOMATIC) u8Eth_FifoIdx = 0U;
    VAR(boolean, AUTOMATIC) bEth_IsInterrupt = FALSE;

    bEth_IsInterrupt = Eth_InternalCfgPtr->pController[CtrlIdx].EnableTxInterrupt;

    if ((Std_ReturnType)E_OK == Eth_TxConfirmationVerify(CtrlIdx))
    {
        if ((boolean)FALSE == bEth_IsInterrupt)
        {
            for (u8Eth_FifoIdx = 0U; u8Eth_FifoIdx < ETH_MAX_TXFIFO_CONFIG; u8Eth_FifoIdx++)
            {
                /* Check all buffers and report them - returned error 
                status is ignored because there is no mean to report errors
                in the AUTOSAR specification */
                Eth_AutoSar_Wrapper_TxConfirmation(CtrlIdx, u8Eth_FifoIdx);
            }
        }
    }
}

#if STD_ON == ETH_GET_VERSION_INFO_API
/**
****************************************************************************************
* @brief         Returns the version information of this module.
* @param[out]    VersionInfoPtr Pointer where to store the version information
*                of this particular module instance.
* @return void
****************************************************************************************
*/

FUNC(void, ETH_CODE) Eth_GetVersionInfo \
( \
    P2VAR(Std_VersionInfoType, AUTOMATIC, ETH_APPL_DATA) VersionInfoPtr \
)
{
    if ((Std_ReturnType)E_OK == Eth_GetVersionInfoVerify(VersionInfoPtr))
    {
        VersionInfoPtr->moduleID = (uint16)ETH_MODULE_ID;
        VersionInfoPtr->vendorID = (uint16)ETH_H_VENDOR_ID;
        VersionInfoPtr->sw_major_version = (uint8)ETH_H_SW_MAJOR_VER;
        VersionInfoPtr->sw_minor_version = (uint8)ETH_H_SW_MINOR_VER;
        VersionInfoPtr->sw_patch_version = (uint8)ETH_H_SW_PATCH_VER;
    }
}
#endif /* ETH_GET_VERSION_INFO_API */

/**
****************************************************************************************
* @brief  The function checks for controller errors and lost frames. Used for polling state 
*         changes. Calls EthIf_CtrlModeIndication when the controller mode changed.
* @return void
****************************************************************************************
*/

FUNC(void, ETH_CODE) Eth_MainFunction(void)
{
    Eth_AutoSar_Wrapper_MainFunction();
}

#define ETH_STOP_SEC_CODE
#include "Eth_MemMap.h"

#ifdef __cplusplus
}
#endif
