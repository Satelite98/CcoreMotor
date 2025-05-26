/****************************************************************************
*
* Copyright (c) 2023  C*Core -   All Rights Reserved
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
*   Project              : AUTOSAR 4.4.0 MCAL
*   Platform             : PowerPC
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
*   @file    Gpt.c
*   @version 1.0.1
*
*      AUTOSAR 4.4.0 - Common Level Driver source file.
*    Autosar layer of Gpt MCAL driver.
*
*   @addtogroup Gpt
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==============================================INCLUDE FILES=======================================*/
#include "Gpt.h"
#include "Gpt_AutoSAR_Wrapper.h"
#include "Gpt_Stm_HAL_Wrapper.h"
#include "Gpt_Gtm_LLDriver.h"
#include "Gpt_Pit_HAL_Wrapper.h"
#include "Gpt_Rtc_HAL_Wrapper.h"
#include "Gpt_Gtm_HAL_Wrapper.h"


#if (GPT_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* (GPT_DEV_ERROR_DETECT == STD_ON) */

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

/*=================================================Constants========================================*/

#define GPT_IS_VALID_CHANNEL(ch)        ((ch) < GPT_HW_CHANNEL_NUM)

/* used to debug wakeup function, just print log */
#define GPT_WAKEUP_DEBUG                        STD_OFF
#if (GPT_WAKEUP_DEBUG == STD_ON)
#include "console.h"
#endif


/*===========================================VARIABLE DECLARATIONS==================================*/


static VAR(Gpt_StatusType, GPT_VAR) sGpt_Status[GPT_MAX_PARTITION] = {GPT_UNINIT};
static volatile VAR(Gpt_ModeType, GPT_VAR) sGpt_eMode[GPT_MAX_PARTITION] = {GPT_MODE_NORMAL};

#if(GPT_ENABLE_GTMCMU == STD_ON)
static VAR(Gpt_StatusType, GPT_VAR) sGpt_GtmStatus[GPT_MAX_PARTITION] = {GPT_UNINIT};
#endif

P2CONST(Gpt_ConfigType, GPT_VAR,  GPT_APPL_CONST)  sGpt_pConfig[GPT_MAX_PARTITION];
/*============================================DEFINES AND MACROS====================================*/

/*===================================================ENUMS==========================================*/

/*=======================================STRUCTURES AND OTHER TYPEDEFS==============================*/

/*==================================LOCAL FUNCTION PROTOTYPES=======================================*/
LOCAL_INLINE FUNC(void, GPT_CODE) Gpt_DetReportError(	\
		VAR(uint8, AUTOMATIC) InstanceId, 		\
		VAR(uint8, AUTOMATIC) ApiId, 			\
		VAR(uint8, AUTOMATIC) ErrorId			\
);

/*===============================================LOCAL FUNCTIONS====================================*/

LOCAL_INLINE FUNC(void, GPT_CODE) Gpt_DetReportError(	\
		VAR(uint8, AUTOMATIC) InstanceId, 	\
		VAR(uint8, AUTOMATIC) ApiId, 		\
		VAR(uint8, AUTOMATIC) ErrorId		\
)
{
#if (GPT_DEV_ERROR_DETECT == STD_ON)
	(void)Det_ReportError( 								\
			(uint16)GPT_MODULE_ID, InstanceId, ApiId, 	\
			ErrorId 									\
		);
#else
	(void)InstanceId;
	(void)ApiId;
	(void)ErrorId;
#endif
}

#if (GPT_ENABLE_MULTICORE == STD_ON)
LOCAL_INLINE FUNC(Std_ReturnType, GPT_CODE) Gpt_CoreVerify(VAR(Gpt_ChannelType, AUTOMATIC) Channel, VAR(uint8, AUTOMATIC) ApiId)
{
    VAR(Std_ReturnType,AUTOMATIC) returnValue = (Std_ReturnType)E_NOT_OK;
    VAR(uint32, AUTOMATIC) CurrentCoreId = 1 << Gpt_GetCoreID();

    VAR(uint8, AUTOMATCI) Temp = CurrentCoreId & sGpt_pConfig[Gpt_GetCoreID()]->pGpt_CoreMap[Channel].u8CoreId;
	if(Temp == (uint8)0u)
	{
		(void)Gpt_DetReportError 		\
		( 								\
			GPT_INSTANCE_ID, 			\
			ApiId, 						\
			GPT_E_PARAM_CONFIG   		\
		);
	}
	else
	{
		returnValue = (Std_ReturnType)E_OK;
	}
	return returnValue;
}
#endif

LOCAL_INLINE FUNC(Std_ReturnType,GPT_CODE) Gpt_InitVerify 		\
( 																\
    P2CONST(Gpt_ConfigType, AUTOMATIC, GPT_APPL_CONST) pConfig  \
)
{
    VAR(Std_ReturnType,AUTOMATIC) returnValue = (Std_ReturnType)E_NOT_OK;

    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
    /* If caller is the initialization function, OK */
    if (GPT_READY == sGpt_Status[CoreIndex])
    {

/*
    [SWS_Gpt_00307] [ If development error detection is enabled for the GPT module:
    If the GPT driver is not in operation mode "uninitialized", the function Gpt_Init shall
    raise the error GPT_E_ALREADY_INITIALIZED. ]
*/
/*
    [SWS_Gpt_00309] [ A re-initialization of the GPT driver by executing the
    Gpt_Init function requires a de-initialization before by executing a Gpt_DeInit. ]
*/
        (void)Gpt_DetReportError 		\
        ( 								\
            GPT_INSTANCE_ID, 			\
            GPT_SID_INIT, 				\
            GPT_E_ALREADY_INITIALIZED 	\
        );
    }
    else
    {
#if (GPT_PRECOMPILE_SUPPORT == STD_OFF)
        /* check input paramter is valid */
        if (NULL_PTR == pConfig)
        {
            (void)Gpt_DetReportError 		\
            ( 								\
                GPT_INSTANCE_ID, 			\
                GPT_SID_INIT, 				\
				GPT_E_PARAM_POINTER 		\
            );
        }
        else
#else
        	(void)pConfig;
#endif
        {
            returnValue = (Std_ReturnType)E_OK;
        }
    }

    return returnValue;
}

#if (GPT_TIME_ELAPSED_API == STD_ON)
LOCAL_INLINE FUNC(Std_ReturnType,GPT_CODE) Gpt_GetTimeElapsedVerify 	\
( 																		\
    VAR(Gpt_ChannelType, AUTOMATIC) Channel 							\
)
{
    VAR(Std_ReturnType,AUTOMATIC) returnValue = (Std_ReturnType)E_NOT_OK;

    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
    if (sGpt_Status[CoreIndex] == GPT_UNINIT)
    {
        /*
            [SWS_Gpt_00222] [ If development error detection is enabled for GPT module:
            If the driver is not initialized, the function Gpt_GetTimeElapsed shall raise the error
            GPT_E_UNINIT. ]
        */
        (void)Gpt_DetReportError 			\
        ( 									\
            GPT_INSTANCE_ID, 				\
            GPT_SID_TIMEELAPSED, 			\
            GPT_E_UNINIT 					\
        );
    }
    else
    {
        /*
            [SWS_Gpt_00210] [ If development error detection is enabled for GPT module:
            If the parameter Channel is invalid (not within the range specified by configuration),
            the function Gpt_GetTimeElapsed shall raise the error GPT_E_PARAM_CHANNEL. ]
        */
        if (!GPT_IS_VALID_CHANNEL(Channel))
        {
            (void)Gpt_DetReportError 		\
            ( 								\
                GPT_INSTANCE_ID, 			\
                GPT_SID_TIMEELAPSED, 		\
                GPT_E_PARAM_CHANNEL 		\
            );
        }
        else
        {
#if (GPT_ENABLE_MULTICORE == STD_ON)
            returnValue = Gpt_CoreVerify(Channel, GPT_SID_TIMEELAPSED);
#else
            returnValue = (Std_ReturnType)E_OK;
#endif
        }
    }

    return returnValue;
}
#endif

#if (GPT_TIME_REMAINING_API == STD_ON)
LOCAL_INLINE FUNC(Std_ReturnType,GPT_CODE) Gpt_GetTimeRemainingVerify   \
( 																		\
    VAR(Gpt_ChannelType, AUTOMATIC) Channel 							\
)
{
    VAR(Std_ReturnType,AUTOMATIC) returnValue = (Std_ReturnType)E_NOT_OK;

    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
    if (sGpt_Status[CoreIndex] == GPT_UNINIT)
    {
        /*
            [SWS_Gpt_00223] [ If development error detection is enabled for GPT module:
            If the driver is not initialized, the function Gpt_GetTimeRemaining shall raise the
            error GPT_E_UNINIT. ]
        */
        (void)Gpt_DetReportError 	\
        ( 							\
            GPT_INSTANCE_ID, 		\
            GPT_SID_TIMEREMAINING,	\
            GPT_E_UNINIT \
        );
    }
    else
    {
        if (!GPT_IS_VALID_CHANNEL(Channel))
        {
            /*
                [SWS_Gpt_00211] [ If development error detection is enabled for GPT module:
                If the parameter Channel is invalid (not within the range specified by configuration),
                the function Gpt_GetTimeRemaining shall raise the error
                GPT_E_PARAM_CHANNEL. ]
            */
            (void)Gpt_DetReportError 	\
            ( 							\
                GPT_INSTANCE_ID, 		\
                GPT_SID_TIMEREMAINING,  \
                GPT_E_PARAM_CHANNEL 	\
            );
        }
        else
        {
#if (GPT_ENABLE_MULTICORE == STD_ON)
            returnValue = Gpt_CoreVerify(Channel, GPT_SID_TIMEREMAINING);
#else
            returnValue = (Std_ReturnType)E_OK;
#endif
        }
    }

    return returnValue;
}
#endif

LOCAL_INLINE FUNC(Std_ReturnType,GPT_CODE) Gpt_StartTimerVerify \
( 																\
    VAR(Gpt_ChannelType, AUTOMATIC) Channel, 					\
    VAR(Gpt_ValueType, AUTOMATIC) u32Value 						\
)
{
    VAR(Std_ReturnType,AUTOMATIC) returnValue = (Std_ReturnType)E_NOT_OK;

    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
    if (sGpt_Status[CoreIndex] == GPT_UNINIT)
    {
        /*
            [SWS_Gpt_00224] [ If development error detection is enabled for GPT module:
            If the driver is not initialized, the function Gpt_StartTimer shall raise the error
            GPT_E_UNINIT. ]
        */
        (void)Gpt_DetReportError 	\
        ( 							\
            GPT_INSTANCE_ID, 		\
            GPT_SID_STARTTIMER, 	\
            GPT_E_UNINIT 			\
        );
    }
    else
    {
        if (!GPT_IS_VALID_CHANNEL(Channel))
        {
            /*
                [SWS_Gpt_00212] [ If development error detection is enabled for GPT module:
                If the parameter Channel is invalid (not within the range specified by configuration),
                the function Gpt_StartTimer shall raise the error GPT_E_PARAM_CHANNEL. ]
            */
            (void)Gpt_DetReportError 	\
            ( 							\
                GPT_INSTANCE_ID, 		\
                GPT_SID_STARTTIMER, 	\
                GPT_E_PARAM_CHANNEL 	\
            );
        }
        else if (((uint32)u32Value == (uint32)0u) || \
                ((*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].uChannelTickValueMax < (uint32)u32Value))
        {
            /*
                [SWS_Gpt_00218] [ If development error detection is enabled for GPT module:
                The function Gpt_StartTimer shall raise the error GPT_E_PARAM_VALUE if the
                parameter Value is "0" or not within the allowed range (exceeding the maximum
                timer resolution). ]
            */
            (void)Gpt_DetReportError 	\
            ( 							\
                GPT_INSTANCE_ID, 		\
                GPT_SID_STARTTIMER, 	\
                GPT_E_PARAM_VALUE 		\
            );
        }
        else
        {
#if (GPT_ENABLE_MULTICORE == STD_ON)
            returnValue = Gpt_CoreVerify(Channel, GPT_SID_STARTTIMER);
#else
            returnValue = (Std_ReturnType)E_OK;
#endif
        }
    }

    return returnValue;
}

LOCAL_INLINE FUNC(Std_ReturnType,GPT_CODE) Gpt_StopTimerVerify 	\
( 																\
    VAR(Gpt_ChannelType, AUTOMATIC) Channel 					\
)
{
    VAR(Std_ReturnType,AUTOMATIC) returnValue = (Std_ReturnType)E_NOT_OK;

    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
    if (sGpt_Status[CoreIndex] == GPT_UNINIT)
    {
        /*
            [SWS_Gpt_00225] [ If development error detection is enabled for GPT module:
            If the driver is not initialized, the function Gpt_StopTimer shall raise the error
            GPT_E_UNINIT. ]
        */
        (void)Gpt_DetReportError 		\
        ( 								\
            GPT_INSTANCE_ID, 			\
            GPT_SID_STOPTIMER, 			\
            GPT_E_UNINIT 				\
        );
    }
    else
    {
        if (!GPT_IS_VALID_CHANNEL(Channel))
        {

            /*
                [SWS_Gpt_00213] [ If development error detection is enabled for GPT module:
                If the parameter Channel is invalid (not within the range specified by configuration),
                the function Gpt_StopTimer shall raise the error GPT_E_PARAM_CHANNEL. ]
            */
            (void)Gpt_DetReportError 			\
            ( 								\
                GPT_INSTANCE_ID, 			\
                GPT_SID_STOPTIMER, 			\
                GPT_E_PARAM_CHANNEL 		\
            );
        }
        else
        {
#if (GPT_ENABLE_MULTICORE == STD_ON)
            returnValue = Gpt_CoreVerify(Channel, GPT_SID_STOPTIMER);
#else
            returnValue = (Std_ReturnType)E_OK;
#endif
        }
    }

    return returnValue;
}

#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
LOCAL_INLINE FUNC(Std_ReturnType,GPT_CODE) Gpt_EnableNotificationVerify 		\
( 																				\
    VAR(Gpt_ChannelType, AUTOMATIC) Channel 									\
)
{
    VAR(Std_ReturnType,AUTOMATIC) returnValue = (Std_ReturnType)E_NOT_OK;

    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
    if (sGpt_Status[CoreIndex] == GPT_UNINIT)
    {
        /*
            [SWS_Gpt_00226] [ If development error detection is enabled for GPT module:
            If the driver is not initialized, the function Gpt_EnableNotification shall raise the
            error GPT_E_UNINIT. ]
        */
        (void)Gpt_DetReportError 		\
        ( 								\
            GPT_INSTANCE_ID, 			\
            GPT_SID_ENABLENOTIFICATION, \
            GPT_E_UNINIT 				\
        );
    }
    else
    {
        if (!GPT_IS_VALID_CHANNEL(Channel))
        {
            /*
                [SWS_Gpt_00214] [ If development error detection is enabled for GPT module:
                If the parameter Channel is invalid (not within the range specified by
                configuration), the function Gpt_EnableNotification shall raise the error
                GPT_E_PARAM_CHANNEL. ]
            */
            (void)Gpt_DetReportError 		\
            ( 								\
                GPT_INSTANCE_ID, 			\
                GPT_SID_ENABLENOTIFICATION, \
                GPT_E_PARAM_CHANNEL 		\
            );
        }
        else
        {
#if (GPT_ENABLE_MULTICORE == STD_ON)
            returnValue = Gpt_CoreVerify(Channel, GPT_SID_ENABLENOTIFICATION);
#else
            returnValue = (Std_ReturnType)E_OK;
#endif
        }
    }

    return returnValue;
}

LOCAL_INLINE FUNC(Std_ReturnType,GPT_CODE) Gpt_ChannelNotificationVerify 	\
( 																			\
    VAR(uint8, AUTOMATIC) u8ServiceId, 										\
    VAR(Gpt_ChannelType, AUTOMATIC) Channel 								\
)
{
    VAR(Std_ReturnType,AUTOMATIC) returnValue = (Std_ReturnType)E_NOT_OK;

    if (NULL_PTR == (*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].pfNotification)
    {
        /*
            [SWS_Gpt_00377] [ If development error detection is enabled for GPT module:
            If no valid notification function is configured (GptNotification), the function
            Gpt_EnableNotification shall raise the error GPT_E_PARAM_CHANNEL. ]
        */
        (void)Gpt_DetReportError 			\
        ( 									\
            GPT_INSTANCE_ID, 				\
            u8ServiceId, 					\
            GPT_E_PARAM_CHANNEL 			\
        );
    }
    else
    {
#if (GPT_ENABLE_MULTICORE == STD_ON)
        returnValue = Gpt_CoreVerify(Channel, u8ServiceId);
#else
        returnValue = (Std_ReturnType)E_OK;
#endif
    }

    return returnValue;
}

LOCAL_INLINE FUNC(Std_ReturnType,GPT_CODE) Gpt_DisableNotificationVerify 	\
( 																			\
    VAR(Gpt_ChannelType, AUTOMATIC) Channel 								\
)
{
    VAR(Std_ReturnType,AUTOMATIC) returnValue = (Std_ReturnType)E_NOT_OK;

    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
    if (sGpt_Status[CoreIndex] == GPT_UNINIT)
    {

        /*
            [SWS_Gpt_00227] [ If development error detection is enabled for GPT module:
            If the driver is not initialized, the function Gpt_DisableNotification shall raise
            the error GPT_E_UNINIT. ]
        */
        (void)Gpt_DetReportError 			\
        ( 									\
            GPT_INSTANCE_ID, 				\
            GPT_SID_DISABLENOTIFICATION, 	\
            GPT_E_UNINIT 					\
        );
    }
    else
    {
        if (!GPT_IS_VALID_CHANNEL(Channel))
        {
            /*
                [SWS_Gpt_00217] [ If development error detection is enabled for GPT module:
                If the parameter Channel is invalid (not within the range specified by configuration),
                the function Gpt_DisableNotification shall raise the error
                GPT_E_PARAM_CHANNEL. ]
            */
            (void)Gpt_DetReportError 			\
            ( 									\
                GPT_INSTANCE_ID, 				\
                GPT_SID_DISABLENOTIFICATION, 	\
                GPT_E_PARAM_CHANNEL 			\
            );
        }
        else if (NULL_PTR == (*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].pfNotification)
        {
            /*
                [SWS_Gpt_00379] [If development error detection is enabled for GPT module:
                If no valid notification function is configured (GptNotification), the function
                Gpt_DisableNotification shall raise the error GPT_E_PARAM_CHANNEL. ]
            */
            (void)Gpt_DetReportError 			\
            ( 									\
                GPT_INSTANCE_ID, 				\
                GPT_SID_DISABLENOTIFICATION, 	\
                GPT_E_PARAM_CHANNEL 			\
            );
        }
        else
        {
#if (GPT_ENABLE_MULTICORE == STD_ON)
            returnValue = Gpt_CoreVerify(Channel, GPT_SID_DISABLENOTIFICATION);
#else
            returnValue = (Std_ReturnType)E_OK;
#endif
        }
    }

    return returnValue;
}

#endif

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)

LOCAL_INLINE FUNC(Std_ReturnType,GPT_CODE) Gpt_SetModeVerify(VAR(Gpt_ModeType, AUTOMATIC) mode)
{
    VAR(Std_ReturnType,AUTOMATIC) returnValue = (Std_ReturnType)E_NOT_OK;

    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
    if (sGpt_Status[CoreIndex] == GPT_UNINIT)
    {
        /*
            [SWS_Gpt_00228] [ If development error detection is enabled for GPT module:
            If the driver is not initialized, the function Gpt_SetMode shall raise the error
            GPT_E_UNINIT. ]
        */
        (void)Gpt_DetReportError 		\
        ( 								\
            GPT_INSTANCE_ID, 			\
            GPT_SID_SETMODE, 			\
            GPT_E_UNINIT 				\
        );
    }
    else
    {
        if (((mode) != GPT_MODE_NORMAL) && ((mode) != GPT_MODE_SLEEP))
        {
            /*
                [SWS_Gpt_00231] [ If development error detection is enabled for GPT module:
                The function Gpt_SetMode shall raise the error GPT_E_PARAM_MODE if the
                parameter Mode is invalid. ]
            */
            (void)Gpt_DetReportError 		\
            ( 								\
                GPT_INSTANCE_ID, 			\
                GPT_SID_SETMODE, 			\
                GPT_E_PARAM_MODE 			\
            );
        }
        else
        {
            returnValue = (Std_ReturnType)E_OK;
        }
    }

    return returnValue;
}

LOCAL_INLINE FUNC(Std_ReturnType,GPT_CODE) Gpt_GetModeVerify(void)
{
    VAR(Std_ReturnType,AUTOMATIC) returnValue = (Std_ReturnType)E_NOT_OK;

    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
    if (sGpt_Status[CoreIndex] == GPT_UNINIT)
    {
        (void)Gpt_DetReportError 		\
        ( 								\
            GPT_INSTANCE_ID, 			\
            GPT_SID_SETMODE, 			\
            GPT_E_UNINIT 				\
        );
    }
    else
    {
        returnValue = (Std_ReturnType)E_OK;
    }

    return returnValue;
}

#endif

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
LOCAL_INLINE FUNC(Std_ReturnType,GPT_CODE) Gpt_ChannelWakeupVerify 	\
( 																	\
    VAR(uint8, AUTOMATIC) u8ServiceId, 								\
    VAR(Gpt_ChannelType, AUTOMATIC) Channel 						\
)
{
    VAR(Std_ReturnType,AUTOMATIC) returnValue = (Std_ReturnType)E_NOT_OK;

    if ((boolean)FALSE == (*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].bEnableWakeup)
    {
        (void)Gpt_DetReportError(
            GPT_INSTANCE_ID,
            u8ServiceId,
            GPT_E_PARAM_CHANNEL
            );
    }
    else
    {
#if (GPT_ENABLE_MULTICORE == STD_ON)
        returnValue = Gpt_CoreVerify(Channel, u8ServiceId);
#else
        returnValue = (Std_ReturnType)E_OK;
#endif
    }

    return returnValue;

}

LOCAL_INLINE FUNC(Std_ReturnType,GPT_CODE) Gpt_DisableWakeupVerify \
( 													\
    VAR(Gpt_ChannelType, AUTOMATIC) Channel 		\
)
{
    VAR(Std_ReturnType,AUTOMATIC) returnValue = (Std_ReturnType)E_NOT_OK;

    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
    if (sGpt_Status[CoreIndex] == GPT_UNINIT)
    {
        /*
            [SWS_Gpt_00229] [ If development error detection is enabled for GPT module:
            If the driver is not initialized, the function Gpt_DisableWakeup shall raise the error
            GPT_E_UNINIT. ]
        */
        (void)Gpt_DetReportError 		\
        ( 								\
            GPT_INSTANCE_ID, 			\
            GPT_SID_DISABLEWAKEUP, 		\
            GPT_E_UNINIT 				\
        );
    }
    else
    {
        if (!GPT_IS_VALID_CHANNEL(Channel))
        {
            /*
                [SWS_Gpt_00215] [ If development error detection is enabled for GPT module:
                If the parameter Channel is invalid (not within the range specified by configuration)
                or channel wakeup is not enabled by configuration (GptEnableWakeup), the function
                Gpt_DisableWakeup shall raise the error GPT_E_PARAM_CHANNEL. ]
            */
            (void)Gpt_DetReportError 	\
            ( 							\
                GPT_INSTANCE_ID, 		\
                GPT_SID_DISABLEWAKEUP, 	\
                GPT_E_PARAM_CHANNEL 	\
            );
        }
        else
        {
#if (GPT_ENABLE_MULTICORE == STD_ON)
            returnValue = Gpt_CoreVerify(Channel, GPT_SID_DISABLEWAKEUP);
#else
            returnValue = (Std_ReturnType)E_OK;
#endif
        }
    }

    return returnValue;
}

LOCAL_INLINE FUNC(Std_ReturnType,GPT_CODE) Gpt_CheckWakeupVerify 	\
( 																	\
    VAR(Gpt_ChannelType, AUTOMATIC) Channel 						\
)
{
    VAR(Std_ReturnType,AUTOMATIC) returnValue = (Std_ReturnType)E_NOT_OK;
    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();

    if (sGpt_Status[CoreIndex] == GPT_UNINIT)
    {
        /*
            [SWS_Gpt_00325] [ If development error detection is enabled for GPT module:
            If the driver is not initialized, the function Gpt_CheckWakeup shall raise the error
            GPT_E_UNINIT. ]
        */
        (void)Gpt_DetReportError 			\
        ( 									\
            GPT_INSTANCE_ID, 				\
            GPT_SID_CHECKWAKEUP, 			\
            GPT_E_UNINIT 					\
        );
    }
    else
    {
        if (!GPT_IS_VALID_CHANNEL(Channel))
        {
            (void)Gpt_DetReportError 		\
            ( 								\
                GPT_INSTANCE_ID, 			\
                GPT_SID_CHECKWAKEUP, 		\
                GPT_E_PARAM_CHANNEL 		\
            );
        }
        else
        {
#if (GPT_ENABLE_MULTICORE == STD_ON)
            returnValue = Gpt_CoreVerify(Channel, GPT_SID_CHECKWAKEUP);
#else
            returnValue = (Std_ReturnType)E_OK;
#endif
        }
    }

    return returnValue;
}

#endif


#if(GPT_PREDEFTIMER_FUNCTIONALITY_API == STD_ON)
LOCAL_INLINE FUNC(Std_ReturnType,GPT_CODE) Gpt_GetPredefTimerVerify \
( 																	\
	P2CONST(uint32, AUTOMATIC, GPT_APPL_CONST) pu32TimeValue 		\
)
{
    VAR(Std_ReturnType,AUTOMATIC) returnValue = (Std_ReturnType)E_NOT_OK;

    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
    if (sGpt_Status[CoreIndex] == GPT_UNINIT)
    {
        /*
            [SWS_Gpt_00398] [ If development error detection is enabled for GPT module: If
            the driver is not initialized, the function Gpt_GetPredefTimerValue shall raise
            the error GPT_E_UNINIT. ]
        */
        (void)Gpt_DetReportError 			\
        ( 									\
            GPT_INSTANCE_ID, 				\
            GPT_SID_GET_PREDEF_TIMERVALUE,  \
            GPT_E_UNINIT 					\
        );
    }
    else
    {
        if (pu32TimeValue == NULL_PTR)
        {
            /*
                [SWS_Gpt_00403] [ If development error detection is enabled for GPT module: If
                the parameter TimeValuePtr is a null pointer, the function
                Gpt_GetPredefTimerValue shall raise the error GPT_E_PARAM_POINTER.]
            */
            (void)Gpt_DetReportError 			\
            ( 									\
                GPT_INSTANCE_ID, 				\
                GPT_SID_GET_PREDEF_TIMERVALUE,  \
                GPT_E_PARAM_POINTER 			\
            );
        }
        else
        {
            returnValue = (Std_ReturnType)E_OK;
        }
    }

    return returnValue;
}

LOCAL_INLINE FUNC(Std_ReturnType, GPT_CODE) Gpt_GetPredefTimerTimerVerify(
	    VAR(Gpt_PredefTimerType, AUTOMATIC) ePredefTimer
)
{
    VAR(Std_ReturnType, AUTOMATIC) returnValue = (Std_ReturnType)E_OK;
	if ((ePredefTimer != GPT_PREDEF_TIMER_1US_16BIT) 		\
			&& (ePredefTimer != GPT_PREDEF_TIMER_1US_24BIT) 	\
			&& (ePredefTimer != GPT_PREDEF_TIMER_1US_32BIT) 	\
			&& (ePredefTimer != GPT_PREDEF_TIMER_100US_32BIT))
	{
		/*

			[SWS_Gpt_00399] [ If development error detection is enabled for GPT module: If
			the parameter PredefTimer is invalid, the function
			Gpt_GetPredefTimerValue shall raise the development error
			GPT_E_PARAM_PREDEF_TIMER. ]
		*/
		(void)Gpt_DetReportError 			\
		( 									\
			GPT_INSTANCE_ID, 				\
			GPT_SID_GET_PREDEF_TIMERVALUE, 	\
			GPT_E_PARAM_PREDEF_TIMER 		\
		);
		returnValue = (Std_ReturnType)E_NOT_OK;
	}
	if( *((sGpt_pConfig[Gpt_GetCoreID()]->pChannelPredefConfigType) + (uint8)ePredefTimer) == NULL_PTR )
	{
		/*
			[SWS_Gpt_00400] [ If development error detection is enabled for GPT module: If
			the GPT Predef Timer passed by the parameter PredefTimer is not enabled, the
			function Gpt_GetPredefTimerValue shall raise the development error
			GPT_E_PARAM_PREDEF_TIMER. ]
		*/
		(void)Gpt_DetReportError 			\
		( 									\
			GPT_INSTANCE_ID, 				\
			GPT_SID_GET_PREDEF_TIMERVALUE, 	\
			GPT_E_PARAM_PREDEF_TIMER 		\
		);
		returnValue = (Std_ReturnType)E_NOT_OK;
	}

    return returnValue;
}

LOCAL_INLINE FUNC(Std_ReturnType, GPT_CODE) Gpt_GetPredefTimereModeVerify	\
( 											\
    VAR(uint8, AUTOMATIC) u8ServiceId 		\
)
{
    VAR(Std_ReturnType, AUTOMATIC) returnValue = (Std_ReturnType)E_NOT_OK;

    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
    if (GPT_MODE_SLEEP == sGpt_eMode[CoreIndex])
    {
        /*
            [SWS_Gpt_00401] [ If the driver is in "sleep mode", the function
            Gpt_GetPredefTimerValue shall raise the runtime error GPT_E_MODE.]
        */
#if(GPT_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportRuntimeError 	\
        ( 								\
            (uint16)GPT_MODULE_ID, 		\
            GPT_INSTANCE_ID, 			\
            u8ServiceId, 				\
            GPT_E_MODE 					\
        );
#else
        (void)u8ServiceId;
#endif
    }
    else
    {
        returnValue = (Std_ReturnType)E_OK;
    }
    return returnValue;
}
#endif

LOCAL_INLINE FUNC(Std_ReturnType,GPT_CODE) Gpt_GetChannelStatusVerify 	\
( 																		\
    VAR(Gpt_ChannelType, AUTOMATIC) Channel 							\
)
{
    VAR(Std_ReturnType,AUTOMATIC) returnValue = (Std_ReturnType)E_NOT_OK;

    if (!GPT_IS_VALID_CHANNEL(Channel))
    {
        (void)Gpt_DetReportError    \
        (                           \
            GPT_INSTANCE_ID,        \
            GPT_SID_GETSTATUS,    \
            GPT_E_PARAM_CHANNEL     \
        );
    }
    else
    {
#if (GPT_ENABLE_MULTICORE == STD_ON)
        returnValue = Gpt_CoreVerify(Channel, GPT_SID_GETSTATUS);
#else
        returnValue = (Std_ReturnType)E_OK;
#endif
    }

    return returnValue;
}

/*==============================================GLOBAL FUNCTIONS====================================*/


#if (GPT_VERSION_INFO_API == STD_ON)
/*
    [SWS_Gpt_00279]
*/
/*****************************************************************************
**  Service Name     : Gpt_GetVersionInfo
**
**  Description      : This function returns the version information of
**                     this module.
**
**  Service ID       : 0x00
**
**  Sync/Async       : Synchronous
**
**  Reentrancy       : Reentrant
**
**  Parameters (in)  : None
**
**  Parameters (out) : versioninfo: Pointer to where to store the version
**                     information of this module.
**
**  Return value     : None
**
******************************************************************************/
FUNC(void, GPT_CODE) Gpt_GetVersionInfo 			\
( 													\
    P2VAR(Std_VersionInfoType, AUTOMATIC, GPT_APPL_DATA) VersionInfoPtr \
)
{
    /*
        [SWS_Gpt_00338] [ If development error detection is enabled for the GPT module:
        If the parameter VersionInfoPtr is a null pointer, the function
        Gpt_GetVersionInfo shall raise the error GPT_E_PARAM_POINTER. ]
    */
    if (NULL_PTR == VersionInfoPtr)
    {
    	(void)Gpt_DetReportError 					    \
        ( 											    \
            GPT_INSTANCE_ID, GPT_SID_GETVERSIONINFO,    \
            GPT_E_PARAM_POINTER 					    \
        );
    }
    else
    {
        VersionInfoPtr->vendorID         = (uint16)GPT_VENDOR_ID;
        VersionInfoPtr->moduleID         = (uint16)GPT_MODULE_ID;
        VersionInfoPtr->sw_major_version = (uint8)GPT_SW_MAJOR_VER_C;
        VersionInfoPtr->sw_minor_version = (uint8)GPT_SW_MINOR_VER_C;
        VersionInfoPtr->sw_patch_version = (uint8)GPT_SW_PATCH_VER_C;
    }
}
#endif /* GPT_VERSION_INFO_API */


/*
    [SWS_Gpt_00280]
*/
/*****************************************************************************
**  Service Name     : Gpt_Init
**
**  Description      : Initializes the GPT driver
**
**  Service ID       : 0x01
**
**  Sync/Async       : Synchronous
**
**  Reentrancy       : Reentrant
**
**  Parameters (in)  : ConfigPtr:Pointer to a selected configuration structure
**
**  Parameters (out) : None
**
**  Return value     : None
**
******************************************************************************/
FUNC(void, GPT_CODE) Gpt_Init(P2CONST(Gpt_ConfigType, AUTOMATIC, GPT_APPL_CONST) ConfigPtr)
{
    VAR(Gpt_ChannelType, AUTOMATIC) Channel;
    P2VAR(Gpt_Wrapper_ChannelInfo, AUTOMATIC, GPT_APPL_DATA) pChannelInfo = NULL_PTR;

    /* Get the current core ID */
#if (GPT_ENABLE_MULTICORE == STD_ON)
    VAR(uint8, AUTOMATIC) CoreIndex = (uint8)(1u <<Gpt_GetCoreID());
#endif
    VAR(uint8, AUTOMATIC) CoreId = (uint8)(Gpt_GetCoreID());

    if (Gpt_InitVerify(ConfigPtr) == (Std_ReturnType)E_OK)
    {
/*
    [SWS_Gpt_00006] [ The function Gpt_Init shall initialize the hardware timer
    module according to a configuration set referenced by ConfigPtr. ]
*/
#if (GPT_PRECOMPILE_SUPPORT == STD_ON)
    	GPT_CONFIG_DECLARATION;
        sGpt_pConfig[Gpt_GetCoreID()] = &GptChannelConfigSet;
        (void)ConfigPtr;
#else
        sGpt_pConfig[Gpt_GetCoreID()] = ConfigPtr;
#endif

/*
    [SWS_Gpt_00390] The function Gpt_Init shall start all enabled GPT Predef Timers at value 0.
*/
#if (GPT_PREDEFTIMER_FUNCTIONALITY_API == STD_ON)
        /*Initialize Predef Timers.*/
        Gpt_Wrapper_StartPredefTimer(sGpt_pConfig[Gpt_GetCoreID()]);
#endif /* GPT_PREDEFTIMER_FUNCTIONALITY_API */

        /*Initialize for each Channel the runtime status informations.*/
        for (Channel = 0U; Channel < (Gpt_ChannelType)sGpt_pConfig[Gpt_GetCoreID()]->uChannelCount; Channel++)
        {
#if (GPT_ENABLE_MULTICORE == STD_ON)
            if((sGpt_pConfig[Gpt_GetCoreID()]->pGpt_CoreMap[Channel].u8CoreId & CoreIndex) != (uint8)0u)
#endif
            {
                pChannelInfo = Gpt_AutoSar_Wrapper_GetChannelInfo(Channel);

                if((pChannelInfo != NULL_PTR) && (pChannelInfo->eChannelStatus == GPT_STATUS_UNINITIALIZED))
                {
/*
	[SWS_Gpt_00107] [ The function Gpt_Init shall disable all interrupt notifications,
	controlled by the GPT driver. ]
*/
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
                	/*Disable notification*/
                	pChannelInfo->bNotificationEnabled = (boolean)FALSE;
#endif

#if (GPT_ENABLE_MULTICORE == STD_ON)
                	pChannelInfo->pGpt_CoreId[Channel] = sGpt_pConfig[Gpt_GetCoreID()]->pGpt_CoreMap[Channel].u8CoreId;
#endif

/*
	[SWS_Gpt_00258] [ The function Gpt_Init shall disable all wakeup interrupts,
	controlled by the GPT driver.
*/
#if ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) && (GPT_REPORT_WAKEUP_SOURCE == STD_ON))
    				/*Disable wakeup*/
    				pChannelInfo->bWakeupEnabled = (boolean)FALSE;
    				/*Clear wakeup generation status*/
    				pChannelInfo->bWakeupGenerated = (boolean)FALSE;
#endif

    				/* Initialize the running information of the Channel*/
    				pChannelInfo->eChannelStatus = GPT_STATUS_INITIALIZED;
    				pChannelInfo->aStopTimeVal = 0U;

    				/*
    					[SWS_Gpt_00068] [ The function Gpt_Init shall only initialize the configured
    					resources. Resources that are not configured in the configuration file shall
    					not be touched. ]
    				*/
    				/*Initialize hardware timer Channel.*/
    				Gpt_AutoSar_Wrapper_Init((*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].pHwChannelConfig);

    				/*
    					[SWS_Gpt_00339] [ The function Gpt_Init shall set the operation mode of the
    					GPT driver to "normal mode". This leads to a behavior like Gpt_SetMode is called
    					with parameter GPT_MODE_NORMAL. ]
    				*/
    				sGpt_eMode[CoreId] = GPT_MODE_NORMAL;
    				sGpt_Status[CoreId] = GPT_READY;
                }
            }
        }
    }
}

/*
    [SWS_Gpt_00194] [ The function Gpt_DeInit shall be pre compile time
    configurable On/Off by the configuration parameter: GptDeInitApi. ]
*/
#if (GPT_DEINIT_API == STD_ON)
LOCAL_INLINE FUNC(Std_ReturnType,GPT_CODE) Gpt_DeInitVerify(void)
{
    VAR(Std_ReturnType,AUTOMATIC) returnValue = (Std_ReturnType)E_NOT_OK;

    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
    if (sGpt_Status[CoreIndex] == GPT_UNINIT)
    {
        /*
            [SWS_Gpt_00220] [ If development error detection is enabled for the GPT module:
            If the driver is not initialized, the function Gpt_DeInit shall raise the error
            GPT_E_UNINIT. ]
        */
        (void)Gpt_DetReportError 		\
        ( 								\
            GPT_INSTANCE_ID, 			\
            GPT_SID_DEINIT, 			\
            GPT_E_UNINIT 				\
        );
    }
    else
    {
        returnValue = (Std_ReturnType)E_OK;
    }

    return returnValue;
}

/*
    [SWS_Gpt_00281]
*/
/*****************************************************************************
**  Service Name     : Gpt_DeInit
**
**  Description      : Deinitializes the GPT driver
**
**  Service ID       : 0x02
**
**  Sync/Async       : Synchronous
**
**  Reentrancy       : Reentrant
**
**  Parameters (in)  : None
**
**  Parameters (out) : None
**
**  Return value     : None
**
******************************************************************************/
FUNC(void, GPT_CODE) Gpt_DeInit(void)
{
    VAR(Gpt_ChannelType, AUTOMATIC) Channel;
    VAR(Std_ReturnType, AUTOMATIC) allChannelStatus = (Std_ReturnType)E_OK;
    P2VAR(Gpt_Wrapper_ChannelInfo, AUTOMATIC, GPT_APPL_DATA) pChannelInfo = NULL_PTR;

#if (GPT_ENABLE_MULTICORE == STD_ON)
    VAR(uint8, AUTOMATIC) CoreIndex = (uint8)(1u << Gpt_GetCoreID());
#endif
    VAR(uint8, AUTOMATIC) CoreId = (uint8)(Gpt_GetCoreID());

    if (Gpt_DeInitVerify() == (Std_ReturnType)E_OK)
    {
        for (Channel = 0U; Channel < (Gpt_ChannelType)sGpt_pConfig[Gpt_GetCoreID()]->uChannelCount; Channel++)
        {
#if (GPT_ENABLE_MULTICORE == STD_ON)
            if((CoreIndex & sGpt_pConfig[Gpt_GetCoreID()]->pGpt_CoreMap[Channel].u8CoreId) != (uint8)0u)
#endif
            {
            	pChannelInfo = Gpt_AutoSar_Wrapper_GetChannelInfo(Channel);
            	if(pChannelInfo != NULL_PTR)
            	{
    				/*
    					[SWS_Gpt_00234] [ If any timer Channel is in state "running", the function
    					Gpt_DeInit shall raise the runtime error GPT_E_BUSY. ]
    				*/
                	if (GPT_STATUS_RUNNING == (pChannelInfo->eChannelStatus))
                	{
#if(GPT_DEV_ERROR_DETECT == STD_ON)
    					(void)Det_ReportRuntimeError 		\
    					(  									\
    						(uint16)GPT_MODULE_ID, 			\
    						GPT_INSTANCE_ID, 				\
    						GPT_SID_DEINIT, 				\
    						GPT_E_BUSY 						\
    					);
#endif
    					allChannelStatus = (Std_ReturnType)E_NOT_OK;
    					break;
                	}
            	}
            	else
            	{
            		allChannelStatus = (Std_ReturnType)E_NOT_OK;
            	}
            }
        }
		if((Std_ReturnType)E_OK == allChannelStatus)
		{
			for (Channel = 0U; Channel < (Gpt_ChannelType)sGpt_pConfig[Gpt_GetCoreID()]->uChannelCount; Channel++)
			{

#if (GPT_ENABLE_MULTICORE == STD_ON)
				if((CoreIndex & sGpt_pConfig[Gpt_GetCoreID()]->pGpt_CoreMap[Channel].u8CoreId) != (uint8)0u)
#endif
				{
					pChannelInfo = Gpt_AutoSar_Wrapper_GetChannelInfo(Channel);

					if(pChannelInfo != NULL_PTR)
					{

						/*
							[SWS_Gpt_00105] [ The function Gpt_DeInit shall disable all interrupt
							notifications and wakeup interrupts, controlled by the GPT driver. ]
						*/
						#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
						/* Disable notification*/
						pChannelInfo->bNotificationEnabled = (boolean)FALSE;
						#endif
						#if ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) && (GPT_REPORT_WAKEUP_SOURCE == STD_ON))
						/* Disable wakeup */
						pChannelInfo->bWakeupEnabled = (boolean)FALSE;
						/* Clear wakeup generation status*/
						pChannelInfo->bWakeupGenerated = (boolean)FALSE;
						#endif

						/* De initialize the running information of the Channel */
						pChannelInfo->eChannelStatus = GPT_STATUS_UNINITIALIZED;
						pChannelInfo->aStopTimeVal = 0;

						/*
							[SWS_Gpt_00008] The function Gpt_DeInit shall deinitialize the hardware used
							by the GPT driver (depending on configuration) to the power on reset state. Values of
							registers which are not writeable are excluded. It's the responsibility of the hardware
							design that the state does not lead to undefined activities in the uC.
						 */
						/*
							[SWS_Gpt_00162] [ The function Gpt_DeInit shall influence only the peripherals,
							which are allocated by the static configuration. ]
						 */
						/*
							[SWS_Gpt_00308] [ If a postbuild multiple selectable configuration variant was
							used, the function Gpt_DeInit shall further influence only the peripherals, which
							are allocated by the runtime configuration set passed by the previous call of the
							function Gpt_Init. ]
						 */
						/* De Initialize hardware timer Channel.*/
						Gpt_AutoSar_Wrapper_DeInit(((*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].pHwChannelConfig));
					}
				}
			}

/*
    [SWS_Gpt_00391]  The function Gpt_DeInit shall stop all enabled GPT PredefTimers.
*/
#if (GPT_PREDEFTIMER_FUNCTIONALITY_API == STD_ON)
			/* stop Predef timers.*/
			Gpt_Wrapper_StopPredefTimer(sGpt_pConfig[Gpt_GetCoreID()]);
#endif /* GPT_PREDEFTIMER_FUNCTIONALITY_API */

			/*
				[SWS_Gpt_00363] [ The function Gpt_DeInit shall set the operation mode of the
				GPT driver to "uninitialized". ]
			*/
			/* Reset GPT global config */
			sGpt_Status[CoreId] = GPT_UNINIT;
			sGpt_pConfig[Gpt_GetCoreID()] = NULL_PTR;
		}
    }
}
#endif /* GPT_DEINIT_API */

/*
    [SWS_Gpt_00195] [ The function Gpt_GetTimeElapsed shall be pre compile time
    configurable On/Off by the configuration parameter: GptTimeElapsedApi. ]
*/
#if (GPT_TIME_ELAPSED_API == STD_ON)
/*
    [SWS_Gpt_00282]
*/
/*****************************************************************************
**  Service Name     : Gpt_GetTimeElapsed
**
**  Description      : Returns the time already elapsed.
**
**  Service ID       : 0x03
**
**  Sync/Async       : Synchronous
**
**  Reentrancy       : Reentrant
**
**  Parameters (in)  : Numeric identifier of the GPT Channel
**
**  Parameters (out) : None
**
**  Return value     : Elapsed timer value (in number of ticks)
**
******************************************************************************/
FUNC(Gpt_ValueType, GPT_CODE) Gpt_GetTimeElapsed(VAR(Gpt_ChannelType, AUTOMATIC) Channel)
{
    VAR(Gpt_ValueType, AUTOMATIC) returnValue = (Gpt_ValueType)0;
    VAR(Gpt_Wrapper_HwChannelInfo, AUTOMATIC) hwChannelInfo = {FALSE, 0};
    P2VAR(Gpt_Wrapper_ChannelInfo, AUTOMATIC, GPT_APPL_DATA) pChannelInfo = NULL_PTR;

    /*
        [SWS_Gpt_00113] [ The function Gpt_GetTimeElapsed shall be fully reentrant,
        this means even for the same timer Channel. ]
    */
    if (Gpt_GetTimeElapsedVerify(Channel) == (Std_ReturnType)E_OK)
    {
        returnValue = Gpt_AutoSar_Wrapper_GetTimeElapsed 								 					\
						( 																	 				\
							(((*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].pHwChannelConfig)), \
							&hwChannelInfo 													 				\
						);

        pChannelInfo = Gpt_AutoSar_Wrapper_GetChannelInfo(Channel);

        if(pChannelInfo != NULL_PTR)
        {
        	switch (pChannelInfo->eChannelStatus)
			{
				case GPT_STATUS_RUNNING:
				{
					/*
						[SWS_Gpt_00010] The function Gpt_GetTimeElapsed shall return the time
						already elapsed. When the channel is in mode one-shot mode, this is the value
						relative to the point in time, the channel has been started.
					*/
					/* Check if Channel counter has already rollover */
					if (((boolean)TRUE == hwChannelInfo.bChannelRollover) && \
						(GPT_CH_MODE_ONESHOT == (*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].eChannelMode))
					{
						/* The timer has already expired. get the target time return */
						returnValue = hwChannelInfo.uTargetTime;
					}
					break;
				}
				/*
					[SWS_Gpt_00295] [ If the function Gpt_GetTimeElapsed is called on a timer
					Channel in state "initialized" (Channel started never before), the function shall return
					the value "0". ]
				*/
				case GPT_STATUS_INITIALIZED:
				{
					returnValue = (Gpt_ValueType)0;
					break;
				}
				/*
					[SWS_Gpt_00297] [ If the function Gpt_GetTimeElapsed is called on a timer
					Channel in state "stopped", the function shall return the time value at the moment of
					stopping. ]
				*/
				case GPT_STATUS_STOPPED:
				{
					/* Return elapsed time at the when the Channel was stopped */
					returnValue = pChannelInfo->aStopTimeVal;
					break;
				}
				/*
					[SWS_Gpt_00299] [ If the function Gpt_GetTimeElapsed is called on a Channel
					configured for "one-shot mode" in state "expired" (timer has reached the target time),
					the function shall return the target time. ]
				*/
				case GPT_STATUS_EXPIRED:
				{
					returnValue = hwChannelInfo.uTargetTime;
					break;
				}
				default:
					/* Error GPT Status, nothing todo */
					break;
			}
		}
    }

    /*
        [SWS_Gpt_00361] [ When the Channel is in mode "continuous mode", the return
        value of Gpt_GetTimeElapsed is the value relative to the last recurrence (target
        time reached) or to the start of the Channel before the first recurrence occurs. ]
    */
    return returnValue;
}
#endif /* GPT_TIME_ELAPSED_API */

/*
    [SWS_Gpt_00196] [ The function Gpt_GetTimeRemaining shall be pre compile time
    configurable On/Off by the configuration parameter: GptTimeRemainingApi. ]
*/
#if (GPT_TIME_REMAINING_API == STD_ON)
/*
    [SWS_Gpt_00283]
*/
/*****************************************************************************
**  Service Name     : Gpt_GetTimeRemaining
**
**  Description      : Returns the time remaining until the target time is reached
**
**  Service ID       : 0x04
**
**  Sync/Async       : Synchronous
**
**  Reentrancy       : Reentrant
**
**  Parameters (in)  : Numeric identifier of the GPT Channel
**
**  Parameters (out) : None
**
**  Return value     : Remaining timer value (in number of ticks)
**
******************************************************************************/
FUNC(Gpt_ValueType, GPT_CODE) Gpt_GetTimeRemaining(VAR(Gpt_ChannelType, AUTOMATIC) Channel)
{
    VAR(Gpt_ValueType, AUTOMATIC) returnValue = (Gpt_ValueType)0;
    VAR(Gpt_Wrapper_HwChannelInfo, AUTOMATIC) hwChannelInfo = {FALSE, 0};
    P2VAR(Gpt_Wrapper_ChannelInfo, AUTOMATIC, GPT_APPL_DATA) pChannelInfo = NULL_PTR;

    /*
        [SWS_Gpt_00114] [ The function Gpt_GetTimeRemaining shall be fully reentrant,
        this means even for the same timer Channel. ]
    */
    if (Gpt_GetTimeRemainingVerify(Channel) == (Std_ReturnType)E_OK)
    {
        returnValue = Gpt_AutoSar_Wrapper_GetTimeElapsed 						\
        ( 																		\
            (((*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].pHwChannelConfig)), 	\
            &hwChannelInfo 														\
        );

        pChannelInfo = Gpt_AutoSar_Wrapper_GetChannelInfo(Channel);
        if(pChannelInfo != NULL_PTR)
        {
            switch (pChannelInfo->eChannelStatus)
            {
                case GPT_STATUS_RUNNING:
                {
                    /*Check if Channel counter has already roll-over*/
                    if(((boolean)TRUE == hwChannelInfo.bChannelRollover) && \
                       (GPT_CH_MODE_ONESHOT == (*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].eChannelMode))
                    {
                        /* The timer has already expired. get the target time return */
                        returnValue = (Gpt_ValueType)0;
                    }
                    else
                    {
                        /*
                            [SWS_Gpt_00083] [ The function Gpt_GetTimeRemaining shall return the timer
                            value remaining until the target time will be reached next time. The remaining time is
                            the "target time" minus the time already elapsed. ]
                        */
                        /* Calculate remaining time from elapsed time */
                        returnValue = hwChannelInfo.uTargetTime - returnValue;
                    }
                    break;
                }
                /*
                    [SWS_Gpt_00301] [ If the function Gpt_GetTimeRemaining is called on a timer
                    Channel in state "initialized" (Channel started never before), the function shall return
                    the value "0". ]
                */
                case GPT_STATUS_INITIALIZED:
                {
                    returnValue = (Gpt_ValueType)0;
                    break;
                }
                /*
                    [SWS_Gpt_00303] [ If the function Gpt_GetTimeRemaining is called on a timer
                    Channel in state "stopped", the function shall return the remaining time value at the
                    moment of stopping. ]
                */
                case GPT_STATUS_STOPPED:
                {
                    returnValue = hwChannelInfo.uTargetTime - pChannelInfo->aStopTimeVal;
                    break;
                }
                /*
                    [SWS_Gpt_00305] [ If the function Gpt_GetTimeRemaining is called on a Channel
                    configured for "one-shot mode" in state "expired" (timer has reached the target time),
                    the function shall return the value 0. ]
                */
                case GPT_STATUS_EXPIRED:
                {
                    returnValue = (Gpt_ValueType)0;
                    break;
                }
                default:
                    /* Error GPT Status, nothing todo */
                    break;
            }
        }
    }

    return returnValue;
}
#endif /* GPT_TIME_REMAINING_API */



/*
    [SWS_Gpt_00284]
*/
/*****************************************************************************
**  Service Name     : Gpt_StartTimer
**
**  Description      : Starts a timer Channel.
**
**  Service ID       : 0x05
**
**  Sync/Async       : Synchronous
**
**  Reentrancy       : Reentrant
**
**  Parameters (in)  : Channel:Numeric identifier of the GPT Channel
**  Parameters (in)  : Value: Target time in number of ticks.
**
**  Parameters (out) : None
**
**  Return value     : None
**
******************************************************************************/
FUNC(void, GPT_CODE) Gpt_StartTimer 			\
( 												\
    VAR(Gpt_ChannelType,    AUTOMATIC) Channel, \
    VAR(Gpt_ValueType,      AUTOMATIC) Value 	\
)
{
    P2VAR(Gpt_Wrapper_ChannelInfo, AUTOMATIC, GPT_APPL_DATA) pChannelInfo = NULL_PTR;

    /*
        [SWS_Gpt_00115] [ The function Gpt_StartTimer shall be reentrant, if the timer
        channels used in concurrent calls are different. ]
    */
    if (Gpt_StartTimerVerify(Channel, Value) == (Std_ReturnType)E_OK)
    {
        /* Enable hardware interrupts for the one-shot mode */
        if (GPT_CH_MODE_ONESHOT == (*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].eChannelMode)
        {
            /*
                [SWS_Gpt_00275] [ If configured and enabled, an interrupt notification or a wakeup
                interrupt occurs, when the target time is reached. ]
            */
            Gpt_AutoSar_Wrapper_EnableInterrupt 									 			\
            (																					\
                ((*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].pHwChannelConfig) 	\
            );

        }

        /* Set timer Channel status is running or expired */
        {
            pChannelInfo = Gpt_AutoSar_Wrapper_GetChannelInfo(Channel);
            if (pChannelInfo->eChannelStatus == GPT_STATUS_RUNNING)
            {
                /*
                    [SWS_Gpt_00084] [ If the function Gpt_StartTimer is called on a Channel in state
                    "running", the function shall raise the runtime error GPT_E_BUSY. ]
                */
#if(GPT_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportRuntimeError 		\
            ( 									\
                (uint16)GPT_MODULE_ID, 			\
                GPT_INSTANCE_ID, 				\
                GPT_SID_STARTTIMER, 			\
                GPT_E_BUSY 						\
            );
#endif
            }
            else
            {
                /*
                    [SWS_Gpt_00364] [ The state of the selected timer Channel shall be changed to
                    "running" if Gpt_StartTimer is called. ]
                */
                pChannelInfo->eChannelStatus = GPT_STATUS_RUNNING;

                /*
                    [SWS_Gpt_00274] [ The function Gpt_StartTimer shall start the selected timer
                    Channel with a defined target time. ]
                */
                /* Call Wrapper layer start timer */
                Gpt_AutoSar_Wrapper_StartTimer			 							\
                ( 																	\
                    ((*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].pHwChannelConfig), 	\
                    Value 															\
                );
            }
        }
    }
}



/*
    [SWS_Gpt_00285]
*/
/*****************************************************************************
**  Service Name     : Gpt_StopTimer
**
**  Description      : Stops a timer Channel
**
**  Service ID       : 0x06
**
**  Sync/Async       : Synchronous
**
**  Reentrancy       : Reentrant
**
**  Parameters (in)  : Channel:Numeric identifier of the GPT Channel
**
**  Parameters (out) : None
**
**  Return value     : None
**
******************************************************************************/
FUNC(void, GPT_CODE) Gpt_StopTimer(VAR(Gpt_ChannelType, AUTOMATIC) Channel)
{
    VAR(Gpt_Wrapper_HwChannelInfo, AUTOMATIC) hwChannelInfo = {FALSE, 0};
    P2VAR(Gpt_Wrapper_ChannelInfo, AUTOMATIC, GPT_APPL_DATA) pChannelInfo = NULL_PTR;
    VAR(Gpt_ValueType, AUTOMATIC) uElapsedTime = 0;

    /*
        [SWS_Gpt_00116] [ The function Gpt_StopTimer shall be reentrant, if the timer
        channels used in concurrent calls are different. ]
    */
    if (Gpt_StopTimerVerify(Channel) == (Std_ReturnType)E_OK)
    {
        pChannelInfo = Gpt_AutoSar_Wrapper_GetChannelInfo(Channel);
        /* Get the elapsed  time, used set stoptimerval */
        uElapsedTime = Gpt_AutoSar_Wrapper_GetTimeElapsed 					\
        ( 																	\
            ((*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].pHwChannelConfig),  \
            &hwChannelInfo 													\
        );

        /*
            [SWS_Gpt_00099] [ If development error detection is enabled for GPT module:
            If the function Gpt_StopTimer is called on a channel in state "initialized", "stopped"
            or "expired", the function shall not raise a development error. ]
        */
        /* Check the logical cchannel status is running */
        if (GPT_STATUS_RUNNING == pChannelInfo->eChannelStatus)
        {

            /*
                [SWS_Gpt_00013] [ The function Gpt_StopTimer shall stop the selected timer
                channel. ]
            */
            /* Call Wrapper layer stop timer */
            Gpt_AutoSar_Wrapper_StopTimer(((*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].pHwChannelConfig));

            {
                if (((boolean)TRUE == hwChannelInfo.bChannelRollover) 					\
                        && (GPT_CH_MODE_ONESHOT 										\
                        == (*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].eChannelMode))	\
                {
                    /* Set Channel status to EXPIRED */
                    pChannelInfo->eChannelStatus = GPT_STATUS_EXPIRED;
                }
                else
                {
                    /* Store the stopping time for later use by other API calls*/
                    pChannelInfo->aStopTimeVal = uElapsedTime;

                    /*
                        [SWS_Gpt_00343] [ The state of the selected timer channel shall be changed to
                        "stopped" if Gpt_StopTimer is called. ]
                    */
                    /* Set GPT Channel status to stopped */
                    pChannelInfo->eChannelStatus = GPT_STATUS_STOPPED;
                }
            }
        }
        else
        {
            /*
                [SWS_Gpt_00344] [ If the function Gpt_StopTimer is called on a channel in state
                "initialized", "stopped" or "expired", the function shall leave without any action (no
                change of the channel state). ]
            */
        }
    }
}

/*
    [SWS_Gpt_00199] [ The function Gpt_EnableNotification shall be pre compile
    time configurable On/Off by the configuration parameter:
    GptEnableDisableNotificationApi. ]
*/
/*
    [SWS_Gpt_00200] [ The function Gpt_DisableNotification shall be pre
    compile time configurable On/Off by the configuration parameter:
    GptEnableDisableNotificationApi. ]
*/
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
/*
    [SWS_Gpt_00286]
*/
/*****************************************************************************
**  Service Name     : Gpt_EnableNotification
**
**  Description      : Enables the interrupt notification for a Channel
**
**  Service ID       : 0x07
**
**  Sync/Async       : Synchronous
**
**  Reentrancy       : Reentrant
**
**  Parameters (in)  : Channel:Numeric identifier of the GPT Channel
**
**  Parameters (out) : None
**
**  Return value     : None
**
******************************************************************************/
FUNC(void, GPT_CODE) Gpt_EnableNotification(VAR(Gpt_ChannelType, AUTOMATIC) Channel)
{
    P2VAR(Gpt_Wrapper_ChannelInfo, AUTOMATIC, GPT_APPL_DATA) pChannelInfo = NULL_PTR;

    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
    /*
        [SWS_Gpt_00117] [ The function Gpt_EnableNotification shall be reentrant, if
        the timer channels used in concurrent calls are different. ]
    */
    if (Gpt_EnableNotificationVerify(Channel) == (Std_ReturnType)E_OK)
    {
        if (Gpt_ChannelNotificationVerify(GPT_SID_ENABLENOTIFICATION, Channel) == (Std_ReturnType)E_OK)
        {
            pChannelInfo = Gpt_AutoSar_Wrapper_GetChannelInfo(Channel);
            if(pChannelInfo != NULL_PTR)
            {
                /*
                    [SWS_Gpt_00014] [ The function Gpt_EnableNotification shall enable the
                    interrupt notification of the referenced channel configured for notification (see also
                    SWS_Gpt_00233). The function shall save an attribute like "notification enabled" of
                    the channel. ]
                */
                /* Set the enable notification attribute */
                pChannelInfo->bNotificationEnabled = (boolean)TRUE;

                if (GPT_MODE_NORMAL == sGpt_eMode[CoreIndex])
                {
                    /* Enable hardware interrupts */
                    Gpt_AutoSar_Wrapper_EnableInterrupt 								\
                    ( 																	\
                        ((*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].pHwChannelConfig) 	\
                    );
                }
            }
        }
    }
}

FUNC(boolean, GPT_CODE) Gpt_GetNotificationStatus(VAR(Gpt_ChannelType, AUTOMATIC) Channel)
{
    P2VAR(Gpt_Wrapper_ChannelInfo, AUTOMATIC, GPT_APPL_DATA) pChannelInfo = NULL_PTR;
    VAR(boolean, AUTOMATIC) returnValue = FALSE;

    if (Gpt_EnableNotificationVerify(Channel) == (Std_ReturnType)E_OK)
    {
        pChannelInfo = Gpt_AutoSar_Wrapper_GetChannelInfo(Channel);

        if(pChannelInfo != NULL_PTR)
        {
            /* Get the enable notification attribute */
            returnValue = pChannelInfo->bNotificationEnabled;
        }
    }

    return returnValue;
}

/*
    [SWS_Gpt_00287]
*/
/*****************************************************************************
**  Service Name     : Gpt_DisableNotification
**
**  Description      : Disables the interrupt notification for a Channel
**
**  Service ID       : 0x08
**
**  Sync/Async       : Synchronous
**
**  Reentrancy       : Reentrant
**
**  Parameters (in)  : Channel:Numeric identifier of the GPT Channel
**
**  Parameters (out) : None
**
**  Return value     : None
**
******************************************************************************/
FUNC(void, GPT_CODE) Gpt_DisableNotification(VAR(Gpt_ChannelType, AUTOMATIC) Channel)
{
    P2VAR(Gpt_Wrapper_ChannelInfo, AUTOMATIC, GPT_APPL_DATA) pChannelInfo = NULL_PTR;

    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
    /*
        [SWS_Gpt_00118] [ The function Gpt_DisableNotification shall be reentrant,
        if the timer channels used in concurrent calls are different. ]
    */
    if (Gpt_DisableNotificationVerify(Channel) == (Std_ReturnType)E_OK)
    {
        pChannelInfo = Gpt_AutoSar_Wrapper_GetChannelInfo(Channel);

        /*
            [SWS_Gpt_00015] [ The function Gpt_DisableNotification shall disable the
            interrupt notification of the referenced channel configured for notification (see also
            SWS_Gpt_00233). The function shall save an attribute like "notification disabled" of
            the channel. ]
        */
        /* Set the enable notification attribute */
        pChannelInfo->bNotificationEnabled = (boolean)FALSE;

        /* If the Channel not running in ONE-SHOT mode, Then disable interrupt */
        if ((GPT_MODE_NORMAL == sGpt_eMode[CoreIndex]) 								\
                && ((GPT_CH_MODE_CONTINUOUS 								\
                == (*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].eChannelMode) \
                || (GPT_STATUS_RUNNING != pChannelInfo->eChannelStatus)))
        {
            /*Disable hardware interrupts*/
            Gpt_AutoSar_Wrapper_DisableInterrupt(
                ((*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].pHwChannelConfig));
        }
    }
}
#endif /* GPT_ENABLE_DISABLE_NOTIFICATION_API */


/*
    [SWS_Gpt_00201] [ The function Gpt_SetMode shall be pre compile time
    configurable On/Off by the configuration parameter:
    GptWakeupFunctionalityApi. ]
*/
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)

#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
LOCAL_INLINE FUNC(void, GPT_CODE) Gpt_SetNormalMode(void)
{
    VAR(Gpt_ChannelType, AUTOMATIC) Channel = 0U;
    P2VAR(Gpt_Wrapper_ChannelInfo, AUTOMATIC, GPT_APPL_DATA) pChannelInfo = NULL_PTR;

    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
/*
    [SWS_Gpt_00392] If the parameter Mode has the value GPT_MODE_NORMAL:
    If the driver is in sleep mode, the function Gpt_SetMode shall restart all enabled
    GPT Predef Timers at value 0.
*/
#if (GPT_PREDEFTIMER_FUNCTIONALITY_API == STD_ON)
        if (GPT_MODE_SLEEP == sGpt_eMode[CoreIndex])
        {
            /* Start predef timer */
            Gpt_Wrapper_StartPredefTimer(sGpt_pConfig[Gpt_GetCoreID()]);
        }
#endif /* GPT_PREDEFTIMER_FUNCTIONALITY_API */
    /*
        [SWS_Gpt_00165] [ If the parameter Mode has the value GPT_MODE_NORMAL, the
        function Gpt_SetMode shall not restart automatically the timer channels which have
        been stopped by entering the sleep mode. ]
    */

    for (Channel = 0U; Channel < (Gpt_ChannelType)sGpt_pConfig[Gpt_GetCoreID()]->uChannelCount; Channel++)
    {
        pChannelInfo = Gpt_AutoSar_Wrapper_GetChannelInfo(Channel);

        if(pChannelInfo != NULL_PTR)
        {
			if((*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].pfNotification != NULL_PTR)
			{
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
				if ((boolean)TRUE == pChannelInfo->bNotificationEnabled)
				{
					/*Enable GPT timer interrupts*/
					Gpt_AutoSar_Wrapper_EnableInterrupt(
							((*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].pHwChannelConfig));
				}
				else
#endif
				{
					/* If the Channel not running in ONE-SHOT mode, Then disable interrupt */
					if((GPT_STATUS_RUNNING != pChannelInfo->eChannelStatus) || \
						(GPT_CH_MODE_CONTINUOUS == (*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].eChannelMode))
					{
						/*Disable GPT timer interrupts*/
						Gpt_AutoSar_Wrapper_DisableInterrupt(
								((*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].pHwChannelConfig));
					}
				}
			}
        }
    }
}

LOCAL_INLINE FUNC(void, GPT_CODE) Gpt_SetSleepMode(void)
{
    VAR(Gpt_ChannelType, AUTOMATIC) Channel = 0U;
    P2VAR(Gpt_Wrapper_ChannelInfo, AUTOMATIC, GPT_APPL_DATA) pChannelInfo = NULL_PTR;
    VAR(Gpt_Wrapper_HwChannelInfo, AUTOMATIC) hwChannelInfo = {FALSE, 0};
    VAR(Gpt_ValueType, AUTOMATIC) uElapsedTime = 0U;

    /*
        [SWS_Gpt_00341] [ If the parameter has the value GPT_MODE_SLEEP the function
        Gpt_SetMode shall not start a wakeup timer automatically. First, the user shall call
        Gpt_StartTimer to start a wakeup timer, after this the user shall call
        Gpt_SetMode with parameter GPT_MODE_SLEEP. ]
    */
    for (Channel = 0U; Channel < (Gpt_ChannelType)sGpt_pConfig[Gpt_GetCoreID()]->uChannelCount; Channel++)
    {
        pChannelInfo = Gpt_AutoSar_Wrapper_GetChannelInfo(Channel);

        if(pChannelInfo != NULL_PTR)
        {
            /* Check the Channel is wakeup enabled */
            if ((boolean)TRUE == pChannelInfo->bWakeupEnabled)
            {
                /* Enable GPT timer interrupts for wakeup */
                Gpt_EnableWakeup(Channel);
            }
            /* Disable interrupts and stop the Channel*/
            else
            {
                /* Disable GPT timer interrupts */
                Gpt_AutoSar_Wrapper_DisableInterrupt 										\
                ( 																	\
                    (((*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].pHwChannelConfig)) \
                );

                /* Get the elapsed time used for STOPPED mode of gpt elapse func. */
                uElapsedTime = Gpt_AutoSar_Wrapper_GetTimeElapsed 							\
                ( 																	\
                    ((*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].pHwChannelConfig),  \
                    &hwChannelInfo 													\
                );

                /* Stop the running timer */
                if (GPT_STATUS_RUNNING == pChannelInfo->eChannelStatus)
                {
                    {
                        if (((boolean)TRUE == hwChannelInfo.bChannelRollover) 	\
                                && (GPT_CH_MODE_ONESHOT 						\
                                == (*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].eChannelMode))
                        {
                            /* IF the Channel is ONE-SHOT mode, Set the Channel status to EXPIRED*/
                            pChannelInfo->eChannelStatus = GPT_STATUS_EXPIRED;
                        }
                        else
                        {
                            /* Save the elapse time before Stopped of Channel status */
                            pChannelInfo->aStopTimeVal = uElapsedTime;


                            /* Set the Channel status to STOPPED*/
                            pChannelInfo->eChannelStatus = GPT_STATUS_STOPPED;
                        }
                    }

                    /*
                        [SWS_Gpt_00164] [ If the function Gpt_SetMode is called with parameter Mode
                        has the value GPT_MODE_SLEEP: All timer channels in state "running" which are not
                        configured for wakeup or not enabled for wakeup interruption (stored attribute) via
                        Gpt_EnableWakeup shall be stopped and their state shall be changed to "stopped". ]
                    */
                    /* Stop the Channel timer */
                    Gpt_AutoSar_Wrapper_StopTimer(((*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].pHwChannelConfig));
                }
            }
        }
    }

/*
    [SWS_Gpt_00393]  If the parameter Mode has the value GPT_MODE_SLEEP:
    The function Gpt_SetMode shall stop all enabled GPT Predef Timers. 
*/
#if (GPT_PREDEFTIMER_FUNCTIONALITY_API == STD_ON)
    /* Stop Predef Timers. */
    Gpt_Wrapper_StopPredefTimer(sGpt_pConfig[Gpt_GetCoreID()]);
#endif /* GPT_PREDEFTIMER_FUNCTIONALITY_API */
}
#endif /* GPT_REPORT_WAKEUP_SOURCE */

/*
    [SWS_Gpt_00288]
*/
/*****************************************************************************
**  Service Name     : Gpt_SetMode
**
**  Description      : Sets the operation mode of the GPT.
**
**  Service ID       : 0x09
**
**  Sync/Async       : Synchronous
**
**  Reentrancy       : Reentrant
**
**  Parameters (in)  : mode:GPT_MODE_NORMAL: Normal operation mode of the GPT driver.
**                          GPT_MODE_SLEEP: Sleep mode of the GPT driver (wakeup capable).
**
**  Parameters (out) : None
**
**  Return value     : None
**
******************************************************************************/
FUNC(void, GPT_CODE) Gpt_SetMode(VAR(Gpt_ModeType, AUTOMATIC) Mode)
{
    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
    /*
        [SWS_Gpt_00255] [ The function Gpt_SetMode is only available if the configuration
        parameter GptReportWakeupSource is enabled. ]
    */
#if (GPT_REPORT_WAKEUP_SOURCE == STD_OFF)
    (void)Mode;
#else

    if (Gpt_SetModeVerify(Mode) == (Std_ReturnType)E_OK)
    {
        /*
            [SWS_Gpt_00151] [ The function Gpt_SetMode shall set the operation mode of the
            GPT driver to the given mode parameter. ]
        */
        switch (Mode)
        {
            case GPT_MODE_NORMAL:
                /*
                    [SWS_Gpt_00152] [ If the parameter Mode has the value GPT_MODE_NORMAL:
                    The function Gpt_SetMode shall enable the interrupt notification for all channels
                    which are configured for notification and the notification is enabled (stored attribute)
                    via the function Gpt_EnableNotification prior. All other interrupt notifications
                    shall be disabled. ]
                */
                Gpt_SetNormalMode();

                /* Save GPT mode */
                sGpt_eMode[CoreIndex] = GPT_MODE_NORMAL;
                break;

            case GPT_MODE_SLEEP:

                /*
                    [SWS_Gpt_00153] [ If the parameter Mode has the value GPT_MODE_SLEEP:
                    The function Gpt_SetMode shall enable the wakeup interrupts for all channels which
                    are configured for wakeup and the wakeup is enabled (stored attribute) via the
                    function Gpt_EnableWakeup prior. All other wakeup interrupts shall be disabled. ]
                */
                Gpt_SetSleepMode();

                /* Save GPT mode */
                sGpt_eMode[CoreIndex] = GPT_MODE_SLEEP;
                break;

            default:
                /* Nothing todo */
                break;
        }
    }
#endif // GPT_REPORT_WAKEUP_SOURCE
}


/*****************************************************************************
**  Service Name     : Gpt_GetMode
**
**  Description      : Get the operation mode of the GPT.
**
**  Service ID       : None
**
**  Sync/Async       : Synchronous
**
**  Reentrancy       : Reentrant
**
**  Parameters (in)  : None
**
**  Parameters (out) : None
**
**  Return value     : GPT_MODE_NORMAL: Normal operation mode of the GPT driver.
**                     GPT_MODE_SLEEP: Sleep mode of the GPT driver (wakeup capable).
**
******************************************************************************/
FUNC(Gpt_ModeType, GPT_CODE) Gpt_GetMode(void)
{
    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
    if (Gpt_GetModeVerify() == (Std_ReturnType)E_OK)
    {
        /* Check GPT init */
    }

    return sGpt_eMode[CoreIndex];
}
#endif /* GPT_WAKEUP_FUNCTIONALITY_API */

/*
    [SWS_Gpt_00202] [ The function Gpt_DisableWakeup shall be pre compile time
    configurable On/Off by the configuration parameter:
    GptWakeupFunctionalityApi. ]
*/
/*
    [SWS_Gpt_00203] [ The function Gpt_EnableWakeup shall be pre compile time
    configurable On/Off by the configuration parameter:
    GptWakeupFunctionalityApi. ]
*/
/*
    [SWS_Gpt_00324] [ The function Gpt_CheckWakeup shall be pre compile time
    configurable On/Off by the configuration parameter:
    GptWakeupFunctionalityApi. ]
*/
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/*
    [SWS_Gpt_00289]
*/
/*****************************************************************************
**  Service Name     : Gpt_DisableWakeup
**
**  Description      : Disables the wakeup interrupt of a Channel (relevant in sleep mode).
**
**  Service ID       : 0x0a
**
**  Sync/Async       : Synchronous
**
**  Reentrancy       : Reentrant
**
**  Parameters (in)  : Channel:Numeric identifier of the GPT Channel.
**
**  Parameters (out) : None
**
**  Return value     : None
**
******************************************************************************/
FUNC(void, GPT_CODE) Gpt_DisableWakeup(VAR(Gpt_ChannelType, AUTOMATIC) Channel)
{
    /*
        [SWS_Gpt_00157] [ The function Gpt_DisableWakeup is only feasible, if
        GptReportWakeupSource is statically configured available. ]
    */
#if (GPT_REPORT_WAKEUP_SOURCE == STD_OFF)
    (void)Channel;
#else
    P2VAR(Gpt_Wrapper_ChannelInfo, AUTOMATIC, GPT_APPL_DATA) pChannelInfo = NULL_PTR;

    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
    /*
        [SWS_Gpt_00155] [ The function Gpt_DisableWakeup shall be reentrant, if the
        timer channels used in concurrent calls are different. ]
    */
    if (Gpt_DisableWakeupVerify(Channel) == (Std_ReturnType)E_OK)
    {
        if (Gpt_ChannelWakeupVerify(GPT_SID_DISABLEWAKEUP, Channel) == (Std_ReturnType)E_OK)
        {
            pChannelInfo = Gpt_AutoSar_Wrapper_GetChannelInfo(Channel);
            /* Set the enable wakeup attribute */
            pChannelInfo->bWakeupEnabled = (boolean)FALSE;

            /*
                [SWS_Gpt_00159] [ The function Gpt_DisableWakeup shall disable the wakeup
                interrupt of the referenced channel configured for wakeup. The function shall save an
                attribute like "wakeup disabled" of the channel.
                Comment: This attribute affects the wakeup interrupt always when the driver is in
                "sleep mode". In "normal mode" the attribute has no influence. ]
            */
            /* if Channel is one-shot or running mode, it is need disable IRQ */
            if ((GPT_MODE_SLEEP == sGpt_eMode[CoreIndex]) 									\
                    &&((GPT_CH_MODE_CONTINUOUS 									\
                    == (*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].eChannelMode) \
                    || (GPT_STATUS_RUNNING != pChannelInfo->eChannelStatus)))
            {
                /* Disable timer Channel interrupt */
                Gpt_AutoSar_Wrapper_DisableInterrupt(
                    ((*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].pHwChannelConfig));
            }
        }
    }
#endif // GPT_REPORT_WAKEUP_SOURCE

}

LOCAL_INLINE FUNC(Std_ReturnType,GPT_CODE) Gpt_EnableWakeupVerify 	\
( 																	\
    VAR(Gpt_ChannelType, AUTOMATIC) Channel 						\
)
{
    VAR(Std_ReturnType,AUTOMATIC) returnValue = (Std_ReturnType)E_NOT_OK;

    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
    if (sGpt_Status[CoreIndex] == GPT_UNINIT)
    {
        /*
            [SWS_Gpt_00230] [ If development error detection is enabled for GPT module:
            If the driver is not initialized, the function Gpt_EnableWakeup shall raise the error
            GPT_E_UNINIT. ]
        */
        (void)Gpt_DetReportError 		\
        ( 								\
            GPT_INSTANCE_ID, 			\
            GPT_SID_ENABLEWAKEUP, 		\
            GPT_E_UNINIT 				\
        );
    }
    else
    {
        if (!GPT_IS_VALID_CHANNEL(Channel))
        {
            /*
                [SWS_Gpt_00216] [ If development error detection is enabled for GPT module:
                If the parameter Channel is invalid (not within the range specified by configuration)
                or channel wakeup is not enabled by configuration (GptEnableWakeup), the function
                Gpt_EnableWakeup shall raise the error GPT_E_PARAM_CHANNEL. ]
            */
            (void)Gpt_DetReportError 			\
            ( 								\
                GPT_INSTANCE_ID, 			\
                GPT_SID_ENABLEWAKEUP, 		\
                GPT_E_PARAM_CHANNEL 		\
            );
        }
        else
        {
            returnValue = (Std_ReturnType)E_OK;
        }
    }

    return returnValue;
}

/*
    [SWS_Gpt_00290]
*/
/*****************************************************************************
**  Service Name     : Gpt_EnableWakeup
**
**  Description      : Enables the wakeup interrupt of a Channel (relevant in sleep mode).
**
**  Service ID       : 0x0b
**
**  Sync/Async       : Synchronous
**
**  Reentrancy       : Reentrant
**
**  Parameters (in)  : Channel:Numeric identifier of the GPT Channel.
**
**  Parameters (out) : None
**
**  Return value     : None
**
******************************************************************************/
FUNC(void, GPT_CODE) Gpt_EnableWakeup(VAR(Gpt_ChannelType, AUTOMATIC) Channel)
{
    /*
        [SWS_Gpt_00158] [ The function Gpt_EnableWakeup is only feasible, if
        GptReportWakeupSource is statically configured available. ]
    */
#if (GPT_REPORT_WAKEUP_SOURCE == STD_OFF)
    (void)Channel;
#else
    P2VAR(Gpt_Wrapper_ChannelInfo, AUTOMATIC, GPT_APPL_DATA) pChannelInfo = NULL_PTR;

    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
    /*
        [SWS_Gpt_00156] [ The function Gpt_EnableWakeup shall be reentrant, if the
        timer channels used in concurrent calls are different. ]
    */
    if (Gpt_EnableWakeupVerify(Channel) == (Std_ReturnType)E_OK)
    {
        if (Gpt_ChannelWakeupVerify(GPT_SID_ENABLEWAKEUP, Channel) == (Std_ReturnType)E_OK)
        {
            pChannelInfo = Gpt_AutoSar_Wrapper_GetChannelInfo(Channel);

            if(pChannelInfo != NULL_PTR)
            {
				/* Set the enable wakeup attribute */
				pChannelInfo->bWakeupEnabled = (boolean)TRUE;

				if (GPT_MODE_SLEEP == sGpt_eMode[CoreIndex])
				{
					/*
						[SWS_Gpt_00160] [ The function Gpt_EnableWakeup shall enable the wakeup
						interrupt of the referenced channel configured for wakeup. The function shall save an
						attribute like "wakeup enabled" of the channel. ]
					*/
					/* Enable timer Channel interrupt */
					Gpt_AutoSar_Wrapper_EnableInterrupt 										\
					( 																	\
						((*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].pHwChannelConfig) 	\
					);
				}
        	}
        }
    }
#endif // GPT_REPORT_WAKEUP_SOURCE
}

FUNC(boolean, GPT_CODE) Gpt_GetWakeupStatus(VAR(Gpt_ChannelType, AUTOMATIC) Channel)
{
    VAR(boolean, AUTOMATIC) retrunVal = FALSE;

    if (Gpt_EnableWakeupVerify(Channel) == (Std_ReturnType)E_OK)
    {
        P2VAR(Gpt_Wrapper_ChannelInfo, AUTOMATIC, GPT_APPL_DATA) pChannelInfo = NULL_PTR;

        pChannelInfo = Gpt_AutoSar_Wrapper_GetChannelInfo(Channel);

        if(pChannelInfo != NULL_PTR)
        {
            /* Get the enable wakeup attribute */
            retrunVal = pChannelInfo->bWakeupEnabled;
        }
    }

    return retrunVal;
}


/*
    [SWS_Gpt_00328]
*/
/*****************************************************************************
**  Service Name     : Gpt_CheckWakeup
**
**  Description      : Checks if a wakeup capable GPT Channel is the source for a wakeup event and
                       calls the ECU state manager service EcuM_SetWakeupEvent in case of a valid
                       GPT Channel wakeup event.
**
**  Service ID       : 0x0c
**
**  Sync/Async       : Synchronous
**
**  Reentrancy       : Reentrant
**
**  Parameters (in)  : wakeupSource: Information on wakeup source to be checked. The associated
                                GPT Channel can be determined from configuration data
**
**  Parameters (out) : None
**
**  Return value     : None
**
******************************************************************************/
FUNC(void, GPT_CODE) Gpt_CheckWakeup(VAR(EcuM_WakeupSourceType, AUTOMATIC) u32WakeupSource)
{
    /*
        [SWS_Gpt_00322] [ The function Gpt_CheckWakeup is only feasible, if
        GptReportWakeupSource is statically configured available. ]
    */
#if (GPT_REPORT_WAKEUP_SOURCE == STD_OFF)
    (void)u32WakeupSource;
#else
    P2VAR(Gpt_Wrapper_ChannelInfo, AUTOMATIC, GPT_APPL_DATA) pChannelInfo = NULL_PTR;
    VAR(Gpt_ChannelType, AUTOMATIC) Channel = 0;

    /*
        [SWS_Gpt_00323] [ The function Gpt_CheckWakeup shall be reentrant, by reason
        of possible usage in concurrent interrupt service routines. ]
    */
    if (Gpt_CheckWakeupVerify(Channel) == (Std_ReturnType)E_OK)
    {
        for (Channel = 0U; Channel < (Gpt_ChannelType)sGpt_pConfig[Gpt_GetCoreID()]->uChannelCount; Channel++)
        {
            pChannelInfo = Gpt_AutoSar_Wrapper_GetChannelInfo(Channel);

            if(pChannelInfo != NULL_PTR)
            {
                /*
                    [SWS_Gpt_00321] [ The function Gpt_CheckWakeup shall check if a wakeup
                    capable GPT channel is the source for a wakeup event and call
                    EcuM_SetWakeupEvent to indicate a valid timer wakeup event to the ECU State
                    Manager [8]. ]
                */
                if (((*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[Channel].uWakeupSource == u32WakeupSource) \
                        && ((boolean)TRUE == pChannelInfo->bWakeupGenerated))
                {
                    /*Reset the wakeup flag */
                    pChannelInfo->bWakeupGenerated = (boolean)FALSE;

                    /*
                        [SWS_Gpt_00406]
                    */
                    /* Calling EcuM_SetWakeupEvent and exit*/
                    EcuM_SetWakeupEvent(u32WakeupSource);

                    break;
                }
            }
        }
    }
#endif // GPT_REPORT_WAKEUP_SOURCE
}
#endif /* GPT_WAKEUP_FUNCTIONALITY_API */

#if(GPT_PREDEFTIMER_FUNCTIONALITY_API == STD_ON)
/*
    [SWS_Gpt_00394]
*/
/*****************************************************************************
**  Service Name     : Gpt_GetPredefTimerValue
**
**  Description      : Delivers the current value of the desired GPT Predef Timer.
**
**  Service ID       : 0x0d
**
**  Sync/Async       : Synchronous
**
**  Reentrancy       : Reentrant
**
**  Parameters (in)  : PredefTimer: GPT Predef Timer
**  Parameters (in)  : None
**
**  Parameters (out) : TimeValuePtr: Pointer to time value destination data in RAM
**
**  Return value     : E_OK: no error has been detected
                       E_NOT_OK: aborted due to errors
**
******************************************************************************/
FUNC(Std_ReturnType, GPT_CODE) Gpt_GetPredefTimerValue	  \
(														  \
    VAR(Gpt_PredefTimerType, AUTOMATIC) ePredefTimer,	  \
    P2VAR(uint32, AUTOMATIC, GPT_APPL_DATA) pu32TimeValue \
)
{
    VAR(Std_ReturnType,AUTOMATIC) returnValue = (Std_ReturnType)E_NOT_OK;
    VAR(Gpt_ChannelType, AUTOMATIC) Channel = 0;

    /*
        [SWS_Gpt_00397] [ The function Gpt_GetPredefTimerValue shall be fully
        reentrant, this means even for the same GPT Predef Timer. ]
    */
    if(Gpt_GetPredefTimerVerify(pu32TimeValue) == (Std_ReturnType)E_OK)
    {
    	returnValue = Gpt_GetPredefTimerTimerVerify(ePredefTimer);
    	if((Std_ReturnType)E_OK == returnValue)
    	{
    		returnValue = Gpt_GetPredefTimereModeVerify(GPT_SID_GET_PREDEF_TIMERVALUE);
			if((Std_ReturnType)E_OK == returnValue)
			{
				Channel = (Gpt_ChannelType)ePredefTimer;

				Gpt_AutoSar_Wrapper_GetPredefTimerValue((sGpt_pConfig[Gpt_GetCoreID()]->pChannelPredefConfigType)[Channel],
					ePredefTimer, pu32TimeValue
				);
			}
			else
			{
				* pu32TimeValue = 0U;
			}
    	}
    	else
		{
			* pu32TimeValue = 0U;
		}
    }
    /*
        [SWS_Gpt_00402] If the GPT driver is not initialized, in sleep mode or the GPT
        Predef Timer is not enabled, the function Gpt_GetPredefTimerValue shall 
        return E_NOT_OK
    */
    return returnValue;
}
#endif /* GPT_PREDEFTIMER_FUNCTIONALITY_API */

/*****************************************************************************
**  Service Name     : Gpt_GetChannelStatus
**
**  Description      : get GPT Channel status.
**
**  Service ID       : None
**
**  Sync/Async       : Synchronous
**
**  Reentrancy       : Reentrant
**
**  Parameters (in)  : Channel:Numeric identifier of the GPT Channel
**  Parameters (in)  : None
**
**  Parameters (out) : None
**
**  Return value     : Channel status, ref@Gpt_ChannelStatus
**
******************************************************************************/
FUNC(uint8, GPT_CODE) Gpt_GetChannelStatus(VAR(Gpt_ChannelType, AUTOMATIC) Channel)
{
    P2VAR(Gpt_Wrapper_ChannelInfo, AUTOMATIC, GPT_APPL_DATA) pChannelInfo = NULL_PTR;
    VAR(uint8, AUTOMATIC) returnValue = (uint8)GPT_STATUS_UNINITIALIZED;

    if (Gpt_GetChannelStatusVerify(Channel) == (Std_ReturnType)E_OK)
    {
        pChannelInfo = Gpt_AutoSar_Wrapper_GetChannelInfo(Channel);

        if(pChannelInfo != NULL_PTR)
        {
        	returnValue = (uint8)pChannelInfo->eChannelStatus;
        }
    }

    return returnValue;
}

/*****************************************************************************
**  Service Name     : Gpt_ProcessCommonInterrupt
**
**  Description      : Gpt common handler to implements generic part of the ISR.
**
**  Service ID       : None
**
**  Sync/Async       : Synchronous
**
**  Reentrancy       : Reentrant
**
**  Parameters (in)  : Channel:Numeric identifier of the GPT Channel
**  Parameters (in)  : None
**
**  Parameters (out) : None
**
**  Return value     : None
**
******************************************************************************/
FUNC(void, GPT_CODE) Gpt_ProcessCommonIrq(VAR(Gpt_ChannelType, AUTOMATIC) Channel)
{
#if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) || (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) || (GPT_REPORT_WAKEUP_SOURCE == STD_ON))
    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
#endif

    if (NULL_PTR != sGpt_pConfig[CoreIndex])
    {
        P2VAR(Gpt_Wrapper_ChannelInfo, AUTOMATIC, GPT_APPL_DATA) pChannelInfo = NULL_PTR;

		pChannelInfo = Gpt_AutoSar_Wrapper_GetChannelInfo(Channel);

		if(pChannelInfo != NULL_PTR)
		{

			/*
				[SWS_Gpt_00185]  If a timer channel is configured in "one-shot mode":
				If the timer has reached the target time (timer value = target time), the timer shall
				stop automatically and maintain its timer value unchanged. The channel state shall
				change from "running" to "expired".
			 */
			/*Stop the timer for one-shot mode*/
			if (GPT_CH_MODE_ONESHOT == (*(sGpt_pConfig[CoreIndex]->pChannelConfig))[Channel].eChannelMode)
			{
				/* Change the Channel status to expired */
				pChannelInfo->eChannelStatus = GPT_STATUS_EXPIRED;
			}
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
			/*
				[SWS_Gpt_00209]
				[SWS_Gpt_00233]
			*/
			/*
				[SWS_Gpt_00331]  If supported by hardware, a timer channel shall be able to be
				configured to call a notification function. If enabled, the function is called when the
				target time is reached (timer value = target time).
			*/
			if ((GPT_MODE_NORMAL == sGpt_eMode[CoreIndex]) \
					&& ((boolean)TRUE == pChannelInfo->bNotificationEnabled))
			{
				if ((*(sGpt_pConfig[CoreIndex]->pChannelConfig))[Channel].pfNotification != NULL)
				{
					(*(sGpt_pConfig[CoreIndex]->pChannelConfig))[Channel].pfNotification();
				}
			}
			else if(((boolean)FALSE == pChannelInfo->bNotificationEnabled))
			{
				/*
					[SWS_Gpt_00093]
				*/
			}
			else
			{
				/* no action */
			}
#endif

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
			if ((GPT_MODE_SLEEP == sGpt_eMode[CoreIndex]) && ((boolean)TRUE == pChannelInfo->bWakeupEnabled))
			{
				pChannelInfo->bWakeupGenerated =(boolean)TRUE;

				/*	[SWS_Gpt_00406]
					[SWS_Gpt_00326]
					[SWS_Gpt_00127]  If supported by hardware, a timer channel shall be able to be
					configured as wakeup source of the ECU. If enabled, the wakeup occurs when the
					target time is reached (timer value = target time).
				*/
				EcuM_CheckWakeup((*(sGpt_pConfig[CoreIndex]->pChannelConfig))[Channel].uWakeupSource);

#if (GPT_WAKEUP_DEBUG == STD_ON)
				PSPRINTF("%s is Channel:%d, source:%d wakeup event generated\r\n", __FUNCTION__, \
						Channel, (*(sGpt_pConfig[CoreIndex]->pChannelConfig))[Channel].uWakeupSource);
#endif
			}
#endif /* GPT_REPORT_WAKEUP_SOURCE */
#endif /* GPT_WAKEUP_FUNCTIONALITY_API */

		}
	}
}

FUNC(uint8, GPT_CODE) Gpt_GetInstance   \
( 										\
    VAR(Gpt_Module, AUTOMATIC) module,  \
    VAR(uint8, AUTOMATIC) Channel 		\
)
{
    VAR(uint8, AUTOMATIC) returnVal = 0xFF;
    VAR(uint8, AUTOMATIC) u8Instance = 0;

    if (NULL_PTR != sGpt_pConfig[Gpt_GetCoreID()])
    {
        switch(module)
        {
            case GPT_MODULE_PIT:
                u8Instance = (uint8)(Channel + GPT_PIT_MODULE_INDEX);
            break;
            case GPT_MODULE_STM:
                u8Instance = (uint8)(Channel + GPT_STM_MODULE_INDEX);
            break;
#if ( defined(CCFC3012PT) )
            case GPT_MODULE_GTM:
                u8Instance = (uint8)(Channel + GPT_GTM_MODULE_INDEX);
            break;
#endif
            case GPT_MODULE_RTC:
                u8Instance = (uint8)(Channel + GPT_RTC_MODULE_INDEX);
            break;
            case GPT_MODULE_API:
                u8Instance = (uint8)(Channel + GPT_API_MODULE_INDEX);
            break;
            default:
            break;
        }
    }

    returnVal = sGpt_pConfig[Gpt_GetCoreID()]->Gpt_aHw2LogicChannelMap[u8Instance];

    return returnVal;
}

#if (GPT_SET_CLOCK_MODE == STD_ON)
FUNC(void, GPT_CODE) Gpt_SetClockMode(VAR(Gpt_ClockModeType, AUTOMATIC) eClkMode)
{
    VAR(Gpt_ChannelType, AUTOMATIC) channel;
    VAR(Std_ReturnType, AUTOMATIC)returnValue;
    
    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
    
    returnValue = Gpt_SetClockModeVerify(eClkMode);
    if((Std_ReturnType)E_OK == returnValue)
    {
        for (channel = 0U; channel < (Gpt_ChannelType)sGpt_pConfig[Gpt_GetCoreID()]->uChannelCount; channel++)
        {
            Gpt_AutoSar_Wrapper_SetClockMode( &((*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[channel].pHwChannelConfig), eClkMode);
        }
    }
}
#endif

#if (GPT_CHANGE_NEXT_TIMEOUT_VALUE == STD_ON)
FUNC(void, GPT_CODE) Gpt_ChangeNextTimeoutValue(VAR(Gpt_ChannelType, AUTOMATIC) channel, VAR(Gpt_ValueType, AUTOMATIC) value)
{
    VAR(Std_ReturnType,AUTOMATIC) returnValue;
    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();

    returnValue = Gpt_ChangeNextTimeoutValueVerify(channel, value);
    if((Std_ReturnType)E_OK == returnValue)
    {
    	Gpt_AutoSar_Wrapper_ChangeNextTimeoutValue(&((*(sGpt_pConfig[Gpt_GetCoreID()]->pChannelConfig))[channel].pHwChannelConfig), value);
    }
}
#endif


#if(GPT_ENABLE_GTMCMU == STD_ON)

FUNC(void, GPT_CODE) GPT_Gtm_Init(P2CONST( Gpt_GtmCmuConfigType, AUTOMATIC, GPT_APPL_CONST) ConfigPtr)
{

    static P2CONST(Gpt_GtmCmuConfigType, GPT_VAR,  GPT_APPL_CONST) sGpt_pCmuConfig; 

    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
#if (GPT_PRECOMPILE_SUPPORT == STD_ON)
    	GPT_CMU_CONFIG_DECLARATION;
        sGpt_pCmuConfig = &Gpt_Gtm_Cmu_PBCfg;
        (void)ConfigPtr;
#else
        if(ConfigPtr == NULL_PTR)
        {
            (void)Gpt_DetReportError    \
            (                           \
                GPT_INSTANCE_ID,        \
                GPT_SID_GPT_GTM_INIT,   \
                GPT_E_PARAM_POINTER     \
            );
        }
        sGpt_pCmuConfig = ConfigPtr;
#endif

    if(sGpt_GtmStatus[CoreIndex] == GPT_READY)
    {
        (void)Gpt_DetReportError    	\
        (                           	\
            GPT_INSTANCE_ID,        	\
            GPT_SID_GPT_GTM_INIT,    	\
            GPT_E_ALREADY_INITIALIZED   \
        );
    }
    
    Gpt_AutoSar_Wrapper_Gtm_Init(sGpt_pCmuConfig);
    sGpt_GtmStatus[CoreIndex] = GPT_READY;

}

FUNC(void, GPT_CODE) GPT_Gtm_Deinit(void)
{
    VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
	if(sGpt_GtmStatus[CoreIndex] == GPT_UNINIT)
	{
		(void)Gpt_DetReportError    	\
		(                           	\
			GPT_INSTANCE_ID,        	\
			GPT_SID_GPT_GTM_DEINIT,    	\
			GPT_E_UNINIT   				\
		);
	}
	Gpt_AutoSar_Wrapper_Gtm_Denit();
}

#endif



#ifdef __cplusplus
}
#endif


