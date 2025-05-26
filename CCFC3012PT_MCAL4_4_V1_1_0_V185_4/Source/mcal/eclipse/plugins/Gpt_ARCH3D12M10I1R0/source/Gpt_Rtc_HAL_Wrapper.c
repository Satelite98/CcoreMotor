 /****************************************************************************
*
* Copyright (c) 2023  C*Core -   All Rights Reserved
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* PROJECT     : CCFC3007BC
* DESCRIPTION : CCFC3007BC rtcapi low level drivers code
* HISTORY     : Initial version
* @file     Gpt_Rtc_LLDriver.c
* @version  1.0
* @date     2023 - 08 - 30
* @brief    Initial version.
*
*****************************************************************************/

#include "Gpt_Rtc_HAL_Wrapper.h"
#include "Gpt_Rtc_LLDriver.h"
#include "Gpt.h"
#include "SchM_Gpt.h"
/*=====================================SOURCE FILE VERSION INFORMATION==============================*/

#define GPT_VENDOR_ID_C                 176
#define GPT_AR_MAJOR_VER_C              4
#define GPT_AR_MINOR_VER_C              4
#define GPT_AR_PATCH_VER_C              0
#define GPT_SW_MAJOR_VER_C              1
#define GPT_SW_MINOR_VER_C              0
#define GPT_SW_PATCH_VER_C              1

/*============================================FILE VERSION CHECKS===================================*/

/* Check if current file and GPT header file are of the same vendor */
#if (GPT_VENDOR_ID_C != GPT_VENDOR_ID)
#error "NON-MATCHED DATA : GPT_VENDOR_ID"
#endif

/* Check if current file and GPT header file are of the same Autosar version */
#if (GPT_AR_MAJOR_VER_C != GPT_CFG_AR_MAJOR_VER)
#error "NON-MATCHED DATA : GPT_CFG_AR_MAJOR_VER"
#endif
#if (GPT_AR_MINOR_VER_C != GPT_CFG_AR_MINOR_VER)
#error "NON-MATCHED DATA : GPT_CFG_AR_MINOR_VER"
#endif
#if (GPT_AR_PATCH_VER_C != GPT_CFG_AR_PATCH_VER)
#error "NON-MATCHED DATA : GPT_CFG_AR_PATCH_VER"
#endif

/* Check if current file and GPT header file are of the same Software version */
#if (GPT_SW_MAJOR_VER_C != GPT_CFG_SW_MAJOR_VER)
#error "NON-MATCHED DATA : GPT_CFG_SW_MAJOR_VER"
#endif
#if (GPT_SW_MINOR_VER_C != GPT_CFG_SW_MINOR_VER)
#error "NON-MATCHED DATA : GPT_CFG_SW_MINOR_VER"
#endif
#if (GPT_SW_PATCH_VER_C != GPT_CFG_SW_PATCH_VER)
#error "NON-MATCHED DATA : GPT_CFG_SW_PATCH_VER"
#endif

VAR(uint16, AUTOMATIC) API_TimerValue;
VAR(uint16, AUTOMATIC) API_TimerValue = 0;

FUNC(void, GPT_CODE) Gpt_RtcApi_Wrapper_Init
(
    P2CONST(Gpt_HwChannelConfig, AUTOMATIC, GPT_APPL_CONST) psGpt_HwConfig
)
{

    static VAR(rtcapi_module_t, AUTOMATIC) RTCAPI_Module_Conifg;
    RTCAPI_Module_Conifg.clockType = psGpt_HwConfig->eRtcClk;
    RTCAPI_Module_Conifg.freezeMode = psGpt_HwConfig->bFreezeEnable;
    switch(psGpt_HwConfig->eRtcDiv)
    {
        case RTC_DIV512:
            RTCAPI_Module_Conifg.prescaler512 = (boolean)TRUE;
            break;
        case RTC_DIV32:
            RTCAPI_Module_Conifg.prescaler32 = (boolean)TRUE;
            break;
        case RTC_DIV32_512:
            RTCAPI_Module_Conifg.prescaler32 = (boolean)TRUE;
            RTCAPI_Module_Conifg.prescaler512 = (boolean)TRUE;
            break;
        case RTC_DIV0:
        default:
            RTCAPI_Module_Conifg.prescaler512 = (boolean)FALSE;
            RTCAPI_Module_Conifg.prescaler32 = (boolean)FALSE;
            break;
    }

    SchM_Enter_GPT_EXCLUSIVE_AREA_23();
    (void)RTCAPI_LLD_ModuleInit(&RTCAPI_Module_Conifg);
    
    if(psGpt_HwConfig->eHwModule == GPT_MODULE_RTC)
    {
        RTCAPI_LLD_RTCInit();
    }
    else if(psGpt_HwConfig->eHwModule == GPT_MODULE_API)
    {
        RTCAPI_LLD_APIInit();
    }
    else
    {
        //nothing
    }
    SchM_Exit_GPT_EXCLUSIVE_AREA_23();
}

FUNC(void, GPT_CODE) Gpt_Rtc_Wrapper_DeInit(void)
{
    SchM_Enter_GPT_EXCLUSIVE_AREA_24();
    RTCAPI_LLD_DeInit();
    SchM_Exit_GPT_EXCLUSIVE_AREA_24();
}

FUNC(uint32, GPT_CODE) Gpt_Rtc_Wrapper_GetTimeElapsed       \
(                                                           \
    P2VAR(boolean, AUTOMATIC, GPT_APPL_DATA) pbIsRollover,  \
    P2VAR(uint32, AUTOMATIC, GPT_APPL_DATA) pu32TargetValue \
)
{
    
    VAR(uint8, AUTOMATIC)  u8Flag;
    VAR(uint32, AUTOMATIC)  u32Value;
    *pu32TargetValue = RTCAPI_LLD_GetRunTime();
     u32Value = RTCAPI_LLD_GetRunTime();

    u8Flag = RTC_API_LLD_GetRTCF();
    if(u8Flag == (uint8)1u)
    {
        *pbIsRollover = true;
    }
    else
    {
        *pbIsRollover = false;
    }
    return u32Value;
}

FUNC(uint32, GPT_CODE) Gpt_Rtc_Wrapper_GetTimeRemaining(void)
{
    
    VAR(uint32, AUTOMATIC)  u32TimeElapsed = 0;
    u32TimeElapsed = RTCAPI_LLD_GetRunTime();
    
    return RTC_API_LLD_GetRTCVAL() - u32TimeElapsed;
}

FUNC(void, GPT_CODE) Gpt_Rtc_Wrapper_StartTimer \
(                                               \
    VAR(uint32, AUTOMATIC) u32Value             \
)
{
    SchM_Enter_GPT_EXCLUSIVE_AREA_25();
    (void)RTCAPI_LLD_StopCounter();

    RTC_API_LLD_SetRTCVAL(u32Value);

    RTCAPI_LLD_StartCounter();

    RTC_API_LLD_ClearRTCF();
    SchM_Exit_GPT_EXCLUSIVE_AREA_25();
}

FUNC(void, GPT_CODE) Gpt_Api_Wrapper_StartTimer \
(                                               \
    VAR(uint32, AUTOMATIC) u32Value             \
)
{
    SchM_Enter_GPT_EXCLUSIVE_AREA_26();
    RTC_API_LLD_ClearAPIF();

    RTC_API_LLD_SetAPIVAL(u32Value);

    RTC_API_LLD_SetAPIEN(true);

    RTC_API_LLD_SetAPIIE(true);

    RTCAPI_LLD_StartCounter();
    SchM_Exit_GPT_EXCLUSIVE_AREA_26();

}

FUNC(void, GPT_CODE) Gpt_Rtc_Wrapper_StopTimer(void)
{
    SchM_Enter_GPT_EXCLUSIVE_AREA_27();
    (void)RTCAPI_LLD_StopCounter();
    SchM_Exit_GPT_EXCLUSIVE_AREA_27();
}

FUNC(void, GPT_CODE) Gpt_Api_Wrapper_StopTimer(void)
{
    SchM_Enter_GPT_EXCLUSIVE_AREA_28();
    RTC_API_LLD_SetAPIEN(false);
    RTC_API_LLD_SetAPIIE(false);
    SchM_Exit_GPT_EXCLUSIVE_AREA_28();
}

FUNC(void, GPT_CODE) Gpt_Rtc_Wrapper_EnableNotification(void)
{
    SchM_Enter_GPT_EXCLUSIVE_AREA_29();
    RTC_API_LLD_SetRTCIE(true);
    RTC_API_LLD_ClearRTCF();
    SchM_Exit_GPT_EXCLUSIVE_AREA_29();
}

FUNC(void, GPT_CODE) Gpt_Rtc_Wrapper_DisableNotification(void)
{
    SchM_Enter_GPT_EXCLUSIVE_AREA_30();
    RTC_API_LLD_SetRTCIE(false);
    SchM_Exit_GPT_EXCLUSIVE_AREA_30();
}

FUNC(void, GPT_CODE) Gpt_Api_Wrapper_EnableNotification(void)
{
    SchM_Enter_GPT_EXCLUSIVE_AREA_31();
    RTC_API_LLD_ClearAPIF();
    RTC_API_LLD_SetAPIIE(true);
    SchM_Exit_GPT_EXCLUSIVE_AREA_31();
}

FUNC(void, GPT_CODE) Gpt_Api_Wrapper_DisableNotification(void)
{
    SchM_Enter_GPT_EXCLUSIVE_AREA_32();
    RTC_API_LLD_SetAPIIE(false);
    SchM_Exit_GPT_EXCLUSIVE_AREA_32();
}


/*================================================================================================*/
/**
*
* @brief         Rtc Driver function
* @details       This function:
*                        - will set the date passed by the user.
*
* @param[in]     *timeDate          pointer to configuration
* @return        Std_ReturnType  status error
* @pre           The driver needs to be initialized.
* @implements    Gpt_Rtc_Wrapper_SetTimeDate_Activity
*/
FUNC(Std_ReturnType, GPT_CODE) Gpt_Rtc_Wrapper_SetTimeDate              \
(                                                                       \
    P2CONST(RTCAPI_RTCTimedateType, AUTOMATIC, GPT_APPL_CONST) timeDate \
)
{
    return RTCAPI_LLD_RTCSetTimeDate(timeDate);
}

/*================================================================================================*/
/**
*
* @brief         Rtc Driver function
* @details       This function:
*                        - will get the current time and date and it will
*                               store in the state structure.
*
* @param[in]     *timeDate          pointer to configuration
* @return        void
* @pre           The driver needs to be initialized.
* @implements    Gpt_Rtc_Wrapper_GetTimeDate_Activity
*/
FUNC(void, GPT_CODE) Gpt_Rtc_Wrapper_GetTimeDate                           \
(                                                                          \
    CONSTP2VAR(RTCAPI_RTCTimedateType, AUTOMATIC, GPT_APPL_CONST) timeDate \
)
{
    RTCAPI_LLD_RTCGetTimeDate(timeDate);
}

/*================================================================================================*/
/**
*
* @brief         Rtc Driver function
* @details       This function:
*                        - will convert seconds into time-date format.
*
* @param[in]     seconds         number of seconds
* @param[in]     *timeDate       pointer to configuration
* @return        void
* @pre           The driver needs to be initialized.
* @implements    Gpt_Rtc_Wrapper_ConvertSecondsToTimeDate_Activity
*/
FUNC(void, GPT_CODE) Gpt_Rtc_Wrapper_ConvertSecondsToTimeDate              \
(                                                                          \
    P2CONST(uint32, AUTOMATIC, GPT_APPL_CONST) seconds,                    \
    CONSTP2VAR(RTCAPI_RTCTimedateType, AUTOMATIC, GPT_APPL_CONST) timeDate \
)
{
    RTCAPI_LLD_RTCConvertSecondsToTimeDate(seconds, timeDate);
}

/*================================================================================================*/
/**
*
* @brief         Rtc Driver function
* @details       This function:
*                        - will convert time-date into seconds.
*
* @param[in]     seconds         number of seconds
* @param[in]     *timeDate       pointer to configuration
* @return        void
* @pre           The driver needs to be initialized.
* @implements    Gpt_Rtc_Wrapper_ConvertTimeDateToSeconds_Activity
*/
FUNC(void, GPT_CODE) Gpt_Rtc_Wrapper_ConvertTimeDateToSeconds            \
(                                                                        \
    P2CONST(RTCAPI_RTCTimedateType, AUTOMATIC, GPT_APPL_CONST) timeDate, \
    CONSTP2VAR(uint32, AUTOMATIC, GPT_APPL_CONST) seconds                \
)
{
    RTCAPI_LLD_RTCConvertTimeDateToSeconds(timeDate, seconds);
}
