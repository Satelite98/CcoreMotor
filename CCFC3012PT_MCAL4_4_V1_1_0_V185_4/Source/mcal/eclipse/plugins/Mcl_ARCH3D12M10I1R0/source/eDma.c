/**************************************************************************** 
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
*   @file    eDma.c
*   @version 1.0.1
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of eDma MCAL driver.
*
*   @addtogroup eDma
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

#include "eDma.h"
#include "Det.h"

#define EDMA_C_VENDOR_ID                     176
#define EDMA_C_AR_REL_MAJOR_VER              4
#define EDMA_C_AR_REL_MINOR_VER              4
#define EDMA_C_AR_REL_REV_VER                0
#define EDMA_C_SW_MAJOR_VER                  1
#define EDMA_C_SW_MINOR_VER                  0
#define EDMA_C_SW_PATCH_VER                  1

#if (EDMA_CFG_H_VENDOR_ID != EDMA_C_VENDOR_ID)
    #error " NON-MATCHED DATA : EDMA_C_VENDOR_ID "
#endif
#if (EDMA_CFG_H_AR_REL_MAJOR_VER != EDMA_C_AR_REL_MAJOR_VER)
    #error " NON-MATCHED DATA : EDMA_C_AR_REL_MAJOR_VER "
#endif
#if (EDMA_CFG_H_AR_REL_MINOR_VER != EDMA_C_AR_REL_MINOR_VER)
    #error " NON-MATCHED DATA : EDMA_C_AR_REL_MINOR_VER "
#endif
#if (EDMA_CFG_H_AR_REL_REV_VER != EDMA_C_AR_REL_REV_VER)
    #error " NON-MATCHED DATA : EDMA_C_AR_REL_REV_VER "
#endif
#if (EDMA_CFG_H_SW_MAJOR_VER != EDMA_C_SW_MAJOR_VER)
    #error " NON-MATCHED DATA : EDMA_C_SW_MAJOR_VER "
#endif
#if (EDMA_CFG_H_SW_MINOR_VER != EDMA_C_SW_MINOR_VER)
    #error " NON-MATCHED DATA : EDMA_C_SW_MINOR_VER "
#endif
#if (EDMA_CFG_H_SW_PATCH_VER != EDMA_C_SW_PATCH_VER)
    #error " NON-MATCHED DATA : EDMA_C_SW_PATCH_VER "
#endif

#define EDMA_START_SEC_VAR_SHARED_INIT
#include "Edma_MemMap.h"
static P2CONST(EDma_ConfigType, EDMA_CONST, EDMA_APPL_CONST) g_pEdma_Config = NULL_PTR;
#define EDMA_STOP_SEC_VAR_SHARED_INIT
#include "Edma_MemMap.h"

#define EDMA_START_SEC_VAR_SHARED_INIT
#include "Edma_MemMap.h"
static VAR(edma_state_t, EDMA_VAR) g_sEdma_ControllerState = {{0U}};
#define EDMA_STOP_SEC_VAR_SHARED_INIT
#include "Edma_MemMap.h"

#if (EDMA_DEV_ERROR_DETECT == STD_ON)
LOCAL_INLINE FUNC(void, EDMA_CODE) EDMA_ReportError \
( \
    VAR(uint8, AUTOMATIC) u8Edma_ApiId, \
    VAR(uint8, AUTOMATIC) u8Edma_ErrorId \
);
#endif

#if (EDMA_DEV_ERROR_DETECT == STD_ON)
LOCAL_INLINE FUNC(void, EDMA_CODE) EDMA_ReportError \
( \
    VAR(uint8, AUTOMATIC) u8Edma_ApiId, \
    VAR(uint8, AUTOMATIC) u8Edma_ErrorId \
)
{
    (void)Det_ReportError((uint16)EDMA_MODULE_ID, (uint8)0U, u8Edma_ApiId, u8Edma_ErrorId);
}
#endif

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_InitVerify \
( \
    P2CONST(EDma_ConfigType, EDMA_CONST, EDMA_APPL_CONST) pEdma_Config \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
#if (EDMA_PRECOMPILE_SUPPORT == STD_OFF)
    if (NULL_PTR == pEdma_Config)
#else
    if (NULL_PTR != pEdma_Config)
#endif
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_INIT, EDMA_E_PARAM_POINTER);
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetUpCallbackVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(eDMACallbackType, AUTOMATIC) callback \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SETUP_CALLBACK, EDMA_E_PARAM_DATA_LENGTH);
#endif
    }
    else if(NULL_PTR == callback)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SETUP_CALLBACK, EDMA_E_PARAM_POINTER);
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_ClearIntStatusVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_CLEAR_INT_STATUS, EDMA_E_PARAM_DATA_LENGTH);
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_SwRequestTriggerEnVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SW_REQUEST_TRIGGEREN, EDMA_E_PARAM_DATA_LENGTH);
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetChannelSourceConfigVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel,
    VAR(uint32, AUTOMATIC) request,
    VAR(boolean, AUTOMATIC) triggerEn \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    (void)request;
    (void)triggerEn;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_CHN_SOURCE_CONFIG, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_ChannelInitVerify \
( \
    P2CONST(eDMAChnStateType, EDMA_CONST, EDMA_APPL_DATA) eedma_channelState, \
    P2CONST(eDMAChanConfigType, EDMA_CONST, EDMA_APPL_DATA) eedma_channelConfig \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    if (NULL_PTR == eedma_channelState)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_CHANNEL_INIT, EDMA_E_PARAM_POINTER);  
#endif
    }
    else if(NULL_PTR == eedma_channelConfig)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_CHANNEL_INIT, EDMA_E_PARAM_POINTER);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_ClearSwTCDStructVerify \
( \
    P2CONST(eDMASwTcdType, EDMA_CONST, EDMA_APPL_DATA) swtcd \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    if (NULL_PTR == swtcd)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_CLEAR_SWTCD_STRUCT, EDMA_E_PARAM_POINTER);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetSingleTransferConfigVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(eDMATransferType, AUTOMATIC) type, \
    VAR(uint32, AUTOMATIC) srcAddr, \
    VAR(uint32, AUTOMATIC) destAddr, \
    VAR(eDMATransferSizeType, AUTOMATIC) transferSize, \
    VAR(uint32, AUTOMATIC) dataBufferSize \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    (void)srcAddr;
    (void)destAddr;
    (void)dataBufferSize;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_SINGLE_TRF_CONFIG, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else if(EDMA_TRANSFER_TYPE_PERIPHTOPERIPH < type)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_SINGLE_TRF_CONFIG, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else if(EDMA_TRANSFER_SIZE_16B < transferSize)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_SINGLE_TRF_CONFIG, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetMultiTransferConfigVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(eDMATransferType, AUTOMATIC) type, \
    VAR(uint32, AUTOMATIC) srcAddr, \
    VAR(uint32, AUTOMATIC) destAddr, \
    VAR(eDMATransferSizeType, AUTOMATIC) transferSize, \
    VAR(uint32, AUTOMATIC) blockSize, \
    VAR(uint32, AUTOMATIC) blockCount, \
    VAR(boolean, AUTOMATIC) disableReqOnCompletion \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    (void)srcAddr;
    (void)destAddr;
    (void)blockSize;
    (void)blockCount;
    (void)disableReqOnCompletion;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_MULTI_TRF_CONFIG, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else if(EDMA_TRANSFER_TYPE_PERIPHTOPERIPH < type)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_MULTI_TRF_CONFIG, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else if(EDMA_TRANSFER_SIZE_16B < transferSize)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_MULTI_TRF_CONFIG, EDMA_E_PARAM_DATA_LENGTH);  
#endif  
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetLoopTransferConfigVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    P2CONST(eDMATransferConfigType, EDMA_CONST, EDMA_APPL_DATA)transferConfig \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_LOOP_TRF_CONFIG, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else if(NULL_PTR == transferConfig)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_LOOP_TRF_CONFIG, EDMA_E_PARAM_POINTER);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_CopyConfigToSwTCDVerify \
( \
    P2CONST(eDMATransferConfigType, EDMA_CONST,EDMA_APPL_DATA)config, \
    P2CONST(eDMASwTcdType, EDMA_CONST, EDMA_APPL_DATA) stcd \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    if (NULL_PTR == config)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_COPY_CONFIG_TO_SWTCD, EDMA_E_PARAM_POINTER);  
#endif
    }
    else if(NULL_PTR == stcd)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_LOOP_TRF_CONFIG, EDMA_E_PARAM_POINTER);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetScatterGatherTransferConfigVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    P2CONST(eDMASwTcdType, EDMA_CONST,EDMA_APPL_DATA)stcd, \
    VAR(eDMATransferSizeType, AUTOMATIC) transferSize, \
    VAR(uint32, AUTOMATIC) bytesOnEachRequest, \
    P2CONST(eDMAScatterGatherListType, EDMA_CONST,EDMA_APPL_DATA) srcList, \
    P2CONST(eDMAScatterGatherListType, EDMA_CONST,EDMA_APPL_DATA) destList, \
    VAR(uint8, AUTOMATIC) tcdCount \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    (void)transferSize;
    (void)bytesOnEachRequest;
    (void)tcdCount;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_SCT_GTH_TRF_CONFIG, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else if(NULL_PTR == stcd)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_SCT_GTH_TRF_CONFIG, EDMA_E_PARAM_POINTER);  
#endif
    }
    else if(NULL_PTR == srcList)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_SCT_GTH_TRF_CONFIG, EDMA_E_PARAM_POINTER);  
#endif
    }
    else if(NULL_PTR == destList)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_SCT_GTH_TRF_CONFIG, EDMA_E_PARAM_POINTER);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetChannelRequestVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_CHANNEL_REQUEST, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_ClearChannelRequestVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_CLEAR_CHANNEL_REQUEST, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_ClearHwTCDVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_CLEAR_HW_TCD, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetChnSrcAddrVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(uint32, AUTOMATIC) address \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    (void)address;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_CHN_SRC_ADDR, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetChnSrcAddrOffsetVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(sint16, AUTOMATIC) offset \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    (void)offset;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_CHN_SRC_ADDR_OFF, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetChnSrcAddrReadTransferSizeVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(eDMATransferSizeType, AUTOMATIC) size \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    (void)size;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_CHN_SRC_ADD_RD_TRF, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetChnSrcAddrLastAdjustmentVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(sint32, AUTOMATIC) adjust \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    (void)adjust;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_CHN_SRC_AD_LST_ADJ, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetChnDestAddrLastAdjustmentVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(sint32, AUTOMATIC) adjust \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    (void)adjust;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_CHN_DST_AD_LST_ADJ, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetChnDestAddrVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(uint32, AUTOMATIC) address \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    (void)address;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_CHN_DEST_ADDR, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetChnDestAddrOffsetVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(sint16, AUTOMATIC) offset \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    (void)offset;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_CHN_DEST_ADDR_OFF, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetChnDestdrWriteTransferSizeVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(eDMATransferSizeType, AUTOMATIC) size \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_CHN_DST_ADD_WR_TRF, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else if(EDMA_TRANSFER_SIZE_16B < size)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_CHN_DST_ADD_WR_TRF, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetChnMinorLpTransferByteVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(uint32, AUTOMATIC) nbytes \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    (void)nbytes;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_CHN_MINOR_LP_TRFBT, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetChnMajorLpIterationCountVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(uint32, AUTOMATIC) majorLoopCount \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    (void)majorLoopCount;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_CHN_MAJOR_LP_ITER, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_GetChnRemainingIterationsCountVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_GET_CHN_REMAINING_ITER, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetChnScatterGatherLinkModeVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(uint32, AUTOMATIC) nextTCDAddr \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    (void)nextTCDAddr;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_CHN_SCT_GTH_LK_MOD, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetChnDisRequestsOnTransferCompleteVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(boolean, AUTOMATIC) disable \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    (void)disable;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_CHN_DIS_REQ_ON_TRF, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetInterruptConfigVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(eDMAChannelInterruptType, AUTOMATIC) intSrc, \
    VAR(boolean, AUTOMATIC) enable \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    (void)enable;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_INTERRUPT_CONFIG, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else if(EDMA_CHN_ENABLE_MAJOR_LOOP_DONE_INT < intSrc)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_SET_INTERRUPT_CONFIG, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_WaitChnTransferDoneVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_WAIT_CHN_TRANSFER_DONE, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_GetChnConfigStatusVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_GET_CHN_CONFIG_STATUS, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

LOCAL_INLINE FUNC(Std_ReturnType, EDMA_CODE) EDMA_ErrorIRQHandlerVerify \
( \
    VAR(uint8, AUTOMATIC) mappedChannel \
)
{
    VAR(Std_ReturnType,AUTOMATIC) u8Edma_ret = E_NOT_OK;
    if (EDMA_CHN127_NUMBER < mappedChannel)
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_ERROR_IRQ_HANDLER, EDMA_E_PARAM_DATA_LENGTH);  
#endif
    }
    else
    {
        u8Edma_ret = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)u8Edma_ret;
}

#if (EDMA_VERSION_INFO_API == STD_ON)
FUNC(void, EDMA_CODE) EDMA_GetVersionInfo \
( \
    P2VAR(Std_VersionInfoType, AUTOMATIC, EDMA_APPL_DATA) versioninfo \
)
{
    if (versioninfo == NULL_PTR) 
    {
#if (EDMA_DEV_ERROR_DETECT == STD_ON)
        EDMA_ReportError(EDMA_SID_GET_VERSION_INFO, EDMA_E_PARAM_POINTER);
#endif
    }
    else
    {
        versioninfo->vendorID = EDMA_H_VENDOR_ID;
        versioninfo->moduleID = EDMA_MODULE_ID;
        versioninfo->sw_major_version = EDMA_H_SW_MAJOR_VER;
        versioninfo->sw_minor_version = EDMA_H_SW_MINOR_VER;
        versioninfo->sw_patch_version = EDMA_H_SW_PATCH_VER;
    }
}
#endif

/*****************************************************************************
**  Service Name     : EDMA_Init        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x00                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(void, EDMA_CODE) EDMA_Init(P2CONST(EDma_ConfigType, EDMA_CONST, EDMA_APPL_CONST) peDmaConfig)
{
    if ((Std_ReturnType)E_OK == EDMA_InitVerify(peDmaConfig))
    {
#if (EDMA_PRECOMPILE_SUPPORT == STD_OFF)
        g_pEdma_Config = peDmaConfig;
#else
        g_pEdma_Config = &EDma_Config;
        (void)peDmaConfig;
#endif
        (void)EDMA_LLD_ModuleInit(&g_sEdma_ControllerState, \
                                  g_pEdma_Config->pEdma_DeviceConfig, \
                                  g_pEdma_Config->pEdma_ChStateArray, \
                                  g_pEdma_Config->pEdma_ChanelConfig, \
                                  g_pEdma_Config->u32Edma_ChanelCnt);
        EDMA_LLD_NoUsedChInit(g_pEdma_Config->pEdma_ChPriorityCfgs);
    }
}
/*****************************************************************************
**  Service Name     : EDMA_SetUpCallback        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x02                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetUpCallback \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(eDMACallbackType, AUTOMATIC) callback, \
    P2VAR(void, AUTOMATIC, EDMA_APPL_DATA) parameter \
)
{
    VAR(Std_ReturnType, EDMA_VAR) RetResult = (Std_ReturnType)E_NOT_OK;
    if ((Std_ReturnType)E_OK == EDMA_SetUpCallbackVerify(mappedChannel,callback))
    {
        (void)EDMA_LLD_SetUpCallback(mappedChannel,callback,parameter);
        RetResult = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)RetResult;
}
/*****************************************************************************
**  Service Name     : EDMA_ClearIntStatus        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x03                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(void, EDMA_CODE) EDMA_ClearIntStatus(VAR(uint8, AUTOMATIC) mappedChannel)
{
    if ((Std_ReturnType)E_OK == EDMA_ClearIntStatusVerify(mappedChannel))
    {
        EDMA_HW_ClearIntStatus(mappedChannel);
    }
}
/*****************************************************************************
**  Service Name     : EDMA_ModuleInit        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x04                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(void, EDMA_CODE) EDMA_SwRequestTriggerEn(VAR(uint8, AUTOMATIC) mappedChannel)
{
    if ((Std_ReturnType)E_OK == EDMA_SwRequestTriggerEnVerify(mappedChannel))
    {
        EDMA_LLD_SwRequestTriggerEn(mappedChannel);
    }
}
/*****************************************************************************
**  Service Name     : EDMA_SetChannelSourceConfig        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x05                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetChannelSourceConfig \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(uint32, AUTOMATIC) request, \
    VAR(boolean, AUTOMATIC) triggerEn \
)
{
    VAR(Std_ReturnType, EDMA_VAR) RetResult = (Std_ReturnType)E_NOT_OK;
    if ((Std_ReturnType)E_OK == EDMA_SetChannelSourceConfigVerify(mappedChannel,request,triggerEn))
    {
        (void)EDMA_LLD_SetChannelSourceConfig(mappedChannel,request,triggerEn);
        RetResult = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)RetResult;
}
/*****************************************************************************
**  Service Name     : EDMA_ChannelInit        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x06                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(Std_ReturnType, EDMA_CODE) EDMA_ChannelInit \
( \
    P2VAR(eDMAChnStateType, AUTOMATIC, EDMA_APPL_DATA) eedma_channelState, \
    P2CONST(eDMAChanConfigType, EDMA_CONST,EDMA_APPL_DATA) eedma_channelConfig \
)
{
    VAR(Std_ReturnType, EDMA_VAR) RetResult = (Std_ReturnType)E_NOT_OK;
    if ((Std_ReturnType)E_OK == EDMA_ChannelInitVerify(eedma_channelState,eedma_channelConfig))
    {
        (void)EDMA_LLD_ChannelInit(eedma_channelState,eedma_channelConfig);
        RetResult = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)RetResult;
}

/*****************************************************************************
**  Service Name     : EDMA_ClearSwTCDStruct        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x07                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(void, EDMA_CODE) EDMA_ClearSwTCDStruct(P2VAR(eDMASwTcdType, AUTOMATIC, EDMA_APPL_DATA) swtcd)
{
    if((Std_ReturnType)E_OK == EDMA_ClearSwTCDStructVerify(swtcd))
    {
        EDMA_LLD_ClearSwTCDStruct(swtcd);
    }
}
/*****************************************************************************
**  Service Name     : EDMA_SetSingleTransferConfig        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x08                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetSingleTransferConfig \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(eDMATransferType, AUTOMATIC) type, \
    VAR(uint32, AUTOMATIC) srcAddr, \
    VAR(uint32, AUTOMATIC) destAddr, \
    VAR(eDMATransferSizeType, AUTOMATIC) transferSize, \
    VAR(uint32, AUTOMATIC) dataBufferSize \
)
{
    VAR(Std_ReturnType, EDMA_VAR) RetResult = (Std_ReturnType)E_NOT_OK;
    if ((Std_ReturnType)E_OK \
            == EDMA_SetSingleTransferConfigVerify(mappedChannel,type,srcAddr,destAddr, \
                                                  transferSize,dataBufferSize))
    {
        (void)EDMA_LLD_SetSglTransferConfig(mappedChannel,type,srcAddr,destAddr, \
                                               transferSize,dataBufferSize);
        RetResult = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)RetResult;
}
/*****************************************************************************
**  Service Name     : EDMA_SetMultiTransferConfig        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x09                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetMultiTransferConfig \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(eDMATransferType, AUTOMATIC) type, \
    VAR(uint32, AUTOMATIC) srcAddr, \
    VAR(uint32, AUTOMATIC) destAddr, \
    VAR(eDMATransferSizeType, AUTOMATIC) transferSize, \
    VAR(uint32, AUTOMATIC) blockSize, \
    VAR(uint32, AUTOMATIC) blockCount, \
    VAR(boolean, AUTOMATIC) disableReqOnCompletion \
)
{
    VAR(Std_ReturnType, EDMA_VAR) RetResult = (Std_ReturnType)E_NOT_OK;
    if ((Std_ReturnType)E_OK  \
            == EDMA_SetMultiTransferConfigVerify(mappedChannel,type,srcAddr,destAddr,transferSize, \
                                                 blockSize,blockCount,disableReqOnCompletion))
    {
        (void)EDMA_LLD_SetMultiTransferConfig(mappedChannel,type,srcAddr,destAddr,transferSize, \
                                              blockSize,blockCount,disableReqOnCompletion);
        RetResult = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)RetResult;
}
/*****************************************************************************
**  Service Name     : EDMA_SetLoopTransferConfig        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x0A                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetLoopTransferConfig \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    P2CONST(eDMATransferConfigType, EDMA_CONST,EDMA_APPL_DATA)transferConfig \
)
{
    VAR(Std_ReturnType, EDMA_VAR) RetResult = (Std_ReturnType)E_NOT_OK;
    if ((Std_ReturnType)E_OK == EDMA_SetLoopTransferConfigVerify(mappedChannel,transferConfig))
    {
        (void)EDMA_LLD_SetLoopTransferConfig(mappedChannel,transferConfig);
        RetResult = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)RetResult;
}
/*****************************************************************************
**  Service Name     : EDMA_CopyConfigToSwTCD        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x0B                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(void, EDMA_CODE) EDMA_CopyConfigToSwTCD \
( \
    P2CONST(eDMATransferConfigType, EDMA_CONST,EDMA_APPL_DATA)config, \
    P2VAR(eDMASwTcdType, AUTOMATIC, EDMA_APPL_DATA) stcd \
)
{
    if((Std_ReturnType)E_OK == EDMA_CopyConfigToSwTCDVerify(config,stcd))
    {
        EDMA_LLD_CopyConfigToSwTCD(config,stcd);
    }
}
/*****************************************************************************
**  Service Name     : EDMA_SetScatterGatherTransferConfig        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x0C                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetScatterGatherTransferConfig \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    P2CONST(eDMASwTcdType, EDMA_CONST,EDMA_APPL_DATA)stcd, \
    VAR(eDMATransferSizeType, AUTOMATIC) transferSize, \
    VAR(uint32, AUTOMATIC) bytesOnEachRequest, \
    P2CONST(eDMAScatterGatherListType, EDMA_CONST,EDMA_APPL_DATA) srcList, \
    P2CONST(eDMAScatterGatherListType, EDMA_CONST,EDMA_APPL_DATA) destList, \
    VAR(uint8, AUTOMATIC) tcdCount \
)
{
    VAR(Std_ReturnType, EDMA_VAR) RetResult = (Std_ReturnType)E_NOT_OK;
    if ((Std_ReturnType)E_OK  \
            == EDMA_SetScatterGatherTransferConfigVerify(mappedChannel,stcd,transferSize, \
                                                         bytesOnEachRequest,srcList,destList, \
                                                         tcdCount))
    {
        (void)EDMA_LLD_SetScatterGatherTrfCfg(mappedChannel,stcd,transferSize, \
                bytesOnEachRequest,srcList,destList,tcdCount);
        RetResult = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)RetResult;
}
/*****************************************************************************
**  Service Name     : EDMA_SetChannelRequest        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x0D                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(Std_ReturnType, EDMA_CODE) EDMA_SetChannelRequest(VAR(uint8, AUTOMATIC) mappedChannel)
{
    VAR(Std_ReturnType, EDMA_VAR) RetResult = (Std_ReturnType)E_NOT_OK;
    if ((Std_ReturnType)E_OK == EDMA_SetChannelRequestVerify(mappedChannel))
    {
        (void)EDMA_LLD_SetChannelRequest(mappedChannel);
        RetResult = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)RetResult;
}
/*****************************************************************************
**  Service Name     : EDMA_ClearChannelRequest        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x0E                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(Std_ReturnType, EDMA_CODE) EDMA_ClearChannelRequest(VAR(uint8, AUTOMATIC) mappedChannel)
{
    VAR(Std_ReturnType, EDMA_VAR) RetResult = (Std_ReturnType)E_NOT_OK;
    if ((Std_ReturnType)E_OK == EDMA_ClearChannelRequestVerify(mappedChannel))
    {
        (void)EDMA_LLD_ClearChannelRequest(mappedChannel);
        RetResult = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)RetResult;
}
/*****************************************************************************
**  Service Name     : EDMA_ClearHwTCD        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x0F                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(void, EDMA_CODE) EDMA_ClearHwTCD(VAR(uint8, AUTOMATIC) mappedChannel)
{
    if ((Std_ReturnType)E_OK == EDMA_ClearHwTCDVerify(mappedChannel))
    {
        EDMA_LLD_ClearHwTCD(mappedChannel);
    }
}
/*****************************************************************************
**  Service Name     : EDMA_SetChnSrcAddr        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x10                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(void, EDMA_CODE) EDMA_SetChnSrcAddr \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(uint32, AUTOMATIC) address \
)
{
    if ((Std_ReturnType)E_OK == EDMA_SetChnSrcAddrVerify(mappedChannel,address))
    {
        EDMA_LLD_SetChnSrcAddr(mappedChannel,address);
    }
}
/*****************************************************************************
**  Service Name     : EDMA_SetChnSrcAddrOffset        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x11                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(void, EDMA_CODE) EDMA_SetChnSrcAddrOffset \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(sint16, AUTOMATIC) offset \
)
{
    if ((Std_ReturnType)E_OK == EDMA_SetChnSrcAddrOffsetVerify(mappedChannel,offset))
    {
        EDMA_LLD_SetChnSrcAddrOffset(mappedChannel,offset);
    }
}
/*****************************************************************************
**  Service Name     : EDMA_SetChnSrcAddrReadTransferSize        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x12                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(void, EDMA_CODE) EDMA_SetChnSrcAddrReadTransferSize \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(eDMATransferSizeType, AUTOMATIC) size \
)
{
    if ((Std_ReturnType)E_OK == EDMA_SetChnSrcAddrReadTransferSizeVerify(mappedChannel,size))
    {
        EDMA_LLD_SetChnSrcAddrRdTrfSize(mappedChannel,size);
    }
}
/*****************************************************************************
**  Service Name     : EDMA_SetChnSrcAddrLastAdjustment        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x13                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(void, EDMA_CODE) EDMA_SetChnSrcAddrLastAdjustment \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(sint32, AUTOMATIC) adjust \
)
{
    if ((Std_ReturnType)E_OK == EDMA_SetChnSrcAddrLastAdjustmentVerify(mappedChannel,adjust))
    {
        EDMA_LLD_SetChnSrcAddrLastAdj(mappedChannel,adjust);
    }
}
/*****************************************************************************
**  Service Name     : EDMA_SetChnSrcAddrLastAdjustment        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x14                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(void, EDMA_CODE) EDMA_SetChnDestAddrLastAdjustment \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(sint32, AUTOMATIC) adjust \
)
{
    if ((Std_ReturnType)E_OK == EDMA_SetChnDestAddrLastAdjustmentVerify(mappedChannel,adjust))
    {
        EDMA_LLD_SetChnDestAddrLastAdj(mappedChannel,adjust);
    }
}
/*****************************************************************************
**  Service Name     : EDMA_SetChnDestAddr        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x15                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(void, EDMA_CODE) EDMA_SetChnDestAddr \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(uint32, AUTOMATIC) address \
)
{
    if ((Std_ReturnType)E_OK == EDMA_SetChnDestAddrVerify(mappedChannel,address))
    {
        EDMA_LLD_SetChnDestAddr(mappedChannel,address);
    }
}
/*****************************************************************************
**  Service Name     : EDMA_SetChnDestAddrOffset        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x16                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(void, EDMA_CODE) EDMA_SetChnDestAddrOffset \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(sint16, AUTOMATIC) offset \
)
{
    if ((Std_ReturnType)E_OK == EDMA_SetChnDestAddrOffsetVerify(mappedChannel,offset))
    {
        EDMA_LLD_SetChnDestAddrOffset(mappedChannel,offset);
    }
}
/*****************************************************************************
**  Service Name     : EDMA_SetChnDestdrWriteTransferSize        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x17                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(void, EDMA_CODE) EDMA_SetChnDestdrWriteTransferSize \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(eDMATransferSizeType, AUTOMATIC) size \
)
{
    if ((Std_ReturnType)E_OK == EDMA_SetChnDestdrWriteTransferSizeVerify(mappedChannel,size))
    {
        EDMA_LLD_SetChnDestdrWrTrfSize(mappedChannel,size);
    }
}
/*****************************************************************************
**  Service Name     : EDMA_SetChnMinorLpTransferByte        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x18                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(void, EDMA_CODE) EDMA_SetChnMinorLpTransferByte \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(uint32, AUTOMATIC) nbytes \
)
{
    if ((Std_ReturnType)E_OK == EDMA_SetChnMinorLpTransferByteVerify(mappedChannel,nbytes))
    {
        EDMA_LLD_SetChnMinorLpTrfByte(mappedChannel,nbytes);
    }
}
/*****************************************************************************
**  Service Name     : EDMA_SetChnMajorLpIterationCount        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x19                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(void, EDMA_CODE) EDMA_SetChnMajorLpIterationCount \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(uint32, AUTOMATIC) majorLoopCount \
)
{
    if ((Std_ReturnType)E_OK \
            == EDMA_SetChnMajorLpIterationCountVerify(mappedChannel,majorLoopCount))
    {
        EDMA_LLD_SetChnMajorLpIterCount(mappedChannel,majorLoopCount);
    }
}
/*****************************************************************************
**  Service Name     : EDMA_GetChnRemainingIterationsCount        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x1A                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(uint32, EDMA_CODE) EDMA_GetChnRemainingIterationsCount(VAR(uint8, AUTOMATIC) mappedChannel)
{
    VAR(uint32, EDMA_VAR) RetResult = 0U;
    if ((Std_ReturnType)E_OK == EDMA_GetChnRemainingIterationsCountVerify(mappedChannel))
    {
        RetResult = EDMA_LLD_GetChnRemainingIterCnt(mappedChannel);
    }
    return RetResult;
}
/*****************************************************************************
**  Service Name     : EDMA_SetChnScatterGatherLinkMode        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x1B                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(void, EDMA_CODE) EDMA_SetChnScatterGatherLinkMode \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(uint32, AUTOMATIC) nextTCDAddr \
)
{
    if ((Std_ReturnType)E_OK == EDMA_SetChnScatterGatherLinkModeVerify(mappedChannel,nextTCDAddr))
    {
        EDMA_LLD_SetChnSctGthLinkMode(mappedChannel,nextTCDAddr);
    }
}
/*****************************************************************************
**  Service Name     : EDMA_SetChnDisRequestsOnTransferComplete        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x1C                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(void, EDMA_CODE) EDMA_SetChnDisRequestsOnTransferComplete \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(boolean, AUTOMATIC) disable \
)
{
    if ((Std_ReturnType)E_OK \
            == EDMA_SetChnDisRequestsOnTransferCompleteVerify(mappedChannel,disable))
    {
        EDMA_LLD_SetChnDisReqOnTrfComp(mappedChannel,disable);
    }
}
/*****************************************************************************
**  Service Name     : EDMA_SetInterruptConfig        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x1D                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(void, EDMA_CODE) EDMA_SetInterruptConfig \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(eDMAChannelInterruptType, AUTOMATIC) intSrc, \
    VAR(boolean, AUTOMATIC) enable \
)
{
    if ((Std_ReturnType)E_OK == EDMA_SetInterruptConfigVerify(mappedChannel,intSrc,enable))
    {
        EDMA_LLD_SetInterruptConfig(mappedChannel,intSrc,enable);
    }
}
/*****************************************************************************
**  Service Name     : EDMA_CancelExcutingChnTransfer        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x1E                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(void, EDMA_CODE) EDMA_CancelExcutingChnTransfer(VAR(boolean, AUTOMATIC) error)
{
    EDMA_LLD_CancelExcutingChnTrf(error);
}
/*****************************************************************************
**  Service Name     : EDMA_WaitChnTransferDone        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x1F                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(void, EDMA_CODE) EDMA_WaitChnTransferDone(VAR(uint8, AUTOMATIC) mappedChannel)
{
    if ((Std_ReturnType)E_OK == EDMA_WaitChnTransferDoneVerify(mappedChannel))
    {
        EDMA_LLD_WaitChnTransferDone(mappedChannel);
    }
}
/*****************************************************************************
**  Service Name     : EDMA_GetChnConfigStatus        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x20                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(Std_ReturnType, EDMA_CODE) EDMA_GetChnConfigStatus(VAR(uint8, AUTOMATIC) mappedChannel)
{
    VAR(Std_ReturnType, EDMA_VAR) RetResult = (Std_ReturnType)E_NOT_OK;
    if ((Std_ReturnType)E_OK == EDMA_GetChnConfigStatusVerify(mappedChannel))
    {
        (void)EDMA_LLD_GetChnConfigStatus(mappedChannel);
        RetResult = (Std_ReturnType)E_OK;
    }
    return (Std_ReturnType)RetResult;
}
/*****************************************************************************
**  Service Name     : EDMA_ErrorIRQHandler        
**                                             
**  Description      : This function initializes the module.   
**                                                                            
**  Service ID       : 0x21                                                   
**                                                                            
**  Sync/Async       : Synchronous                                            
**                                                                            
**  Reentrancy       : Non-Reentrant                                          
**                                                                            
**  Parameters (in)  : Config: Pointer to driver configuration.  
**                                                                            
**  Parameters (out) : None                                                 
**                                                                            
**  Return value     : None                                                   
**                                                                            
******************************************************************************/
FUNC(void, EDMA_CODE) EDMA_ErrorIRQHandler(VAR(uint8, AUTOMATIC) mappedChannel)
{
    if ((Std_ReturnType)E_OK == EDMA_ErrorIRQHandlerVerify(mappedChannel))
    {
        EDMA_LLD_ErrorIRQHandler(mappedChannel);
    }
}

#ifdef __cplusplus
}
#endif
