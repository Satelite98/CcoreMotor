#ifndef GPT_RTC_HAL_WRAPPER_H
#define GPT_RTC_HAL_WRAPPER_H
#include "StandardTypes.h"
#include "Gpt.h"

/*=====================================SOURCE FILE VERSION INFORMATION==============================*/
#define GPT_VENDOR_ID_H                     176
#define GPT_MODULE_ID_H                     100
#define GPT_AR_MAJOR_VER_H                  4
#define GPT_AR_MINOR_VER_H                  4
#define GPT_AR_PATCH_VER_H                  0
#define GPT_SW_MAJOR_VER_H                  1
#define GPT_SW_MINOR_VER_H                  0
#define GPT_SW_PATCH_VER_H                  1

/*============================================FILE VERSION CHECKS===================================*/

#if (GPT_VENDOR_ID_H != GPT_VENDOR_ID)
#error "NON-MATCHED DATA : GPT_CFG_VENDOR_ID"
#endif

#if (GPT_AR_MAJOR_VER_H != GPT_CFG_AR_MAJOR_VER)
#error "NON-MATCHED DATA : GPT_CFG_AR_MAJOR_VER"
#endif
#if (GPT_AR_MINOR_VER_H != GPT_CFG_AR_MINOR_VER)
#error "NON-MATCHED DATA : GPT_CFG_AR_MINOR_VER"
#endif
#if (GPT_AR_PATCH_VER_H != GPT_CFG_AR_PATCH_VER)
#error "NON-MATCHED DATA : GPT_CFG_AR_PATCH_VER"
#endif

#if (GPT_SW_MAJOR_VER_H != GPT_CFG_SW_MAJOR_VER)
#error "NON-MATCHED DATA : GPT_CFG_SW_MAJOR_VER"
#endif
#if (GPT_SW_MINOR_VER_H != GPT_CFG_SW_MINOR_VER)
#error "NON-MATCHED DATA : GPT_CFG_SW_MINOR_VER"
#endif
#if (GPT_SW_PATCH_VER_H != GPT_CFG_SW_PATCH_VER)
#error "NON-MATCHED DATA : GPT_CFG_SW_PATCH_VER"
#endif

FUNC(void, GPT_CODE) Gpt_RtcApi_Wrapper_Init
(
    P2CONST(Gpt_HwChannelConfig, AUTOMATIC, GPT_APPL_CONST) psGpt_HwConfig
);

FUNC(void, GPT_CODE) Gpt_Rtc_Wrapper_DeInit(void);

FUNC(uint32, GPT_CODE) Gpt_Rtc_Wrapper_GetTimeElapsed       \
(                                                           \
    P2VAR(boolean, AUTOMATIC, GPT_APPL_DATA) pbIsRollover,  \
    P2VAR(uint32, AUTOMATIC, GPT_APPL_DATA) pu32TargetValue \
);
FUNC(uint32, GPT_CODE) Gpt_Rtc_Wrapper_GetTimeRemaining(void);

FUNC(void, GPT_CODE) Gpt_Rtc_Wrapper_StartTimer(VAR(uint32, AUTOMATIC) u32Value);

FUNC(void, GPT_CODE) Gpt_Api_Wrapper_StartTimer(VAR(uint32, AUTOMATIC) u32Value);

FUNC(void, GPT_CODE) Gpt_Rtc_Wrapper_StopTimer(void);

FUNC(void, GPT_CODE) Gpt_Api_Wrapper_StopTimer(void);

FUNC(void, GPT_CODE) Gpt_Rtc_Wrapper_EnableNotification(void);

FUNC(void, GPT_CODE) Gpt_Rtc_Wrapper_DisableNotification(void);

FUNC(void, GPT_CODE) Gpt_Api_Wrapper_EnableNotification(void);

FUNC(void, GPT_CODE) Gpt_Api_Wrapper_DisableNotification(void);

FUNC(Std_ReturnType, GPT_CODE) Gpt_Rtc_Wrapper_SetTimeDate              \
(                                                                       \
    P2CONST(RTCAPI_RTCTimedateType, AUTOMATIC, GPT_APPL_CONST) timeDate \
);

FUNC(void, GPT_CODE) Gpt_Rtc_Wrapper_GetTimeDate                           \
(                                                                          \
    CONSTP2VAR(RTCAPI_RTCTimedateType, AUTOMATIC, GPT_APPL_CONST) timeDate \
);

FUNC(void, GPT_CODE) Gpt_Rtc_Wrapper_ConvertSecondsToTimeDate              \
(                                                                          \
    P2CONST(uint32, AUTOMATIC, GPT_APPL_CONST) seconds,                    \
    CONSTP2VAR(RTCAPI_RTCTimedateType, AUTOMATIC, GPT_APPL_CONST) timeDate \
);

FUNC(void, GPT_CODE) Gpt_Rtc_Wrapper_ConvertTimeDateToSeconds            \
(                                                                        \
    P2CONST(RTCAPI_RTCTimedateType, AUTOMATIC, GPT_APPL_CONST) timeDate, \
    CONSTP2VAR(uint32, AUTOMATIC, GPT_APPL_CONST) seconds                \
);
#endif
