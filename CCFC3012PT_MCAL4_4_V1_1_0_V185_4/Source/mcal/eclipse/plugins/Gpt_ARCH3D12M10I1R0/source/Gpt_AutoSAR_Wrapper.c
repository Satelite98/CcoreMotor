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
*   @file    Gpt_AutoSAR_Wrapper.c
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
#include "Gpt_AutoSar_Wrapper.h"
#include "Gpt_Gtm_HAL_Wrapper.h"
#include "Gpt_Pit_HAL_Wrapper.h"
#include "Gpt_Stm_HAL_Wrapper.h"
#include "Gpt_Rtc_HAL_Wrapper.h"
#include "Gpt.h"

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


/*============================================DEFINES AND MACROS====================================*/

/*==============================================GLOBAL FUNCTIONS====================================*/

FUNC(Gpt_Wrapper_ChannelInfo*, GPT_CODE) Gpt_AutoSar_Wrapper_GetChannelInfo \
( 																			\
    VAR(Gpt_ChannelType, AUTOMATIC) u8Gpt_Channel 							\
)
{
	/* Global array variable used to store runtime internal context of each logic channel. */
	static VAR(Gpt_Wrapper_ChannelInfo, GPT_VAR) sGpt_ChannelInfo[GPT_HW_CHANNEL_NUM];

	return (u8Gpt_Channel < GPT_HW_CHANNEL_NUM) ? ((Gpt_Wrapper_ChannelInfo*)&sGpt_ChannelInfo[u8Gpt_Channel]) : NULL_PTR;
}

FUNC(void, GPT_CODE) Gpt_AutoSar_Wrapper_Init 								\
( 																			\
    P2CONST(Gpt_HwChannelConfig, AUTOMATIC, GPT_APPL_CONST) psGpt_HwConfig  \
)
{
    /* check ptr is valid */
    if(psGpt_HwConfig!= NULL_PTR)
    {
        switch(psGpt_HwConfig->eHwModule)
        {
#if ( defined(CCFC3012PT) )
            case GPT_MODULE_GTM:
            {
                Gpt_Gtm_Wrapper_Init(psGpt_HwConfig->u8HwChannel, \
                    psGpt_HwConfig->u32GtmChannelRegCtrl1,
#if (GPT_GTM_OUTPUT_ENABLE_MODE == STD_ON)
                    psGpt_HwConfig->bGtmSupportEnableOutput,
#endif
                    psGpt_HwConfig->bFreezeEnable);
                break;
            }
#endif
            case GPT_MODULE_PIT:
            {
                if((uint8)PIT_0_CH_RTI == psGpt_HwConfig->u8HwChannel)
                {
                    PitClkFreq.u32RtiClkFreq = psGpt_HwConfig->u32ClkFreq;
                }
                else
                {
                    PitClkFreq.u32PerClkFreq = psGpt_HwConfig->u32ClkFreq;
                }
                Gpt_Pit_Wrapper_Init(psGpt_HwConfig->u8HwChannel, \
                    psGpt_HwConfig->bFreezeEnable
#if (GPT_PIT_CHAIN_MODE == STD_ON)
                    ,
                    psGpt_HwConfig->bChainMode
#endif
                );
                break;
            }
            case GPT_MODULE_STM:
            {
                Gpt_Stm_Wrapper_Init(psGpt_HwConfig->u8HwChannel, \
                    psGpt_HwConfig->u8StmPrescaler, \
                    psGpt_HwConfig->bFreezeEnable);
                break;
            }
            case GPT_MODULE_RTC:
            case GPT_MODULE_API:
            {
                Gpt_RtcApi_Wrapper_Init(psGpt_HwConfig);
            	break;
            }
            default:
            {
                /* default case, nothing todo */
                break;
            }
        }
    }
}

FUNC (void, GPT_CODE) Gpt_AutoSar_Wrapper_DeInit 							\
( 																			\
    P2CONST(Gpt_HwChannelConfig, AUTOMATIC, GPT_APPL_CONST) psGpt_HwConfig  \
)
{
    /* check ptr is valid */
    if(psGpt_HwConfig!= NULL_PTR)
    {
		switch(psGpt_HwConfig->eHwModule)
		{
#if ( defined(CCFC3012PT) )
		case GPT_MODULE_GTM:
		{
			Gpt_Gtm_Wrapper_DeInit(psGpt_HwConfig->u8HwChannel);
		    break;
		}
#endif
		case GPT_MODULE_PIT:
		{
			Gpt_Pit_Wrapper_DeInit(psGpt_HwConfig->u8HwChannel);
		    break;
		}

		case GPT_MODULE_STM:
		{
			Gpt_Stm_Wrapper_DeInit(psGpt_HwConfig->u8HwChannel);
		    break;
		}

        case GPT_MODULE_RTC:
        case GPT_MODULE_API:
        {
            Gpt_Rtc_Wrapper_DeInit();
            break;
        }
		default:
		{
			/* default case, nothing todo */
			break;
		}
		}
    }
}

FUNC (Gpt_ValueType, GPT_CODE) Gpt_AutoSar_Wrapper_GetTimeElapsed 						\
( 																						\
    P2CONST(Gpt_HwChannelConfig, AUTOMATIC, GPT_APPL_CONST) psGpt_HwConfig, 			\
    P2VAR(Gpt_Wrapper_HwChannelInfo, AUTOMATIC, GPT_APPL_DATA) psGpt_HwChannelInfoPtr   \
)
{
    VAR(Gpt_ValueType, AUTOMATIC) u32Gpt_ReturnValue = 0U;

    DEV_ASSERT(psGpt_HwConfig != NULL_PTR);
    DEV_ASSERT(psGpt_HwChannelInfoPtr != NULL_PTR);

    switch(psGpt_HwConfig->eHwModule)
    {
#if ( defined(CCFC3012PT) )
        case GPT_MODULE_GTM:
        {
            u32Gpt_ReturnValue = Gpt_Gtm_Wrapper_GetTimeElapsed	\
                (psGpt_HwConfig->u8HwChannel, 					\
                &psGpt_HwChannelInfoPtr->bChannelRollover, 		\
                &psGpt_HwChannelInfoPtr->uTargetTime);
            break;
        }
#endif
        case GPT_MODULE_PIT:
        {
            u32Gpt_ReturnValue = Gpt_Pit_Wrapper_GetTimeElapsed \
                (psGpt_HwConfig->u8HwChannel, 					\
                &psGpt_HwChannelInfoPtr->bChannelRollover, 		\
                &psGpt_HwChannelInfoPtr->uTargetTime);
            break;
        }

        case GPT_MODULE_STM:
        {
            u32Gpt_ReturnValue = Gpt_Stm_Wrapper_GetTimeElapsed \
                (psGpt_HwConfig->u8HwChannel, 					\
                &psGpt_HwChannelInfoPtr->bChannelRollover, 		\
                &psGpt_HwChannelInfoPtr->uTargetTime);
            break;
        }

        case GPT_MODULE_RTC:
        case GPT_MODULE_API:
        {
            u32Gpt_ReturnValue = Gpt_Rtc_Wrapper_GetTimeElapsed  \
                (&psGpt_HwChannelInfoPtr->bChannelRollover, 	 \
                &psGpt_HwChannelInfoPtr->uTargetTime);
            break;
        }

        default:
        {
            /* default case, nothing todo */
            break;
        }
    }

    return u32Gpt_ReturnValue;
}

FUNC(uint32, GPT_CODE) Gpt_AutoSar_Wrapper_GetTimeRemaining 				\
( 																			\
    P2CONST(Gpt_HwChannelConfig, AUTOMATIC, GPT_APPL_CONST) psGpt_HwConfig  \
)
{
    VAR(uint32, AUTOMATIC) u32Gpt_ReturnValue = 0U;

    DEV_ASSERT(psGpt_HwConfig != NULL_PTR);

    switch(psGpt_HwConfig->eHwModule)
    {
#if ( defined(CCFC3012PT) )
        case GPT_MODULE_GTM:
        {
            u32Gpt_ReturnValue = Gpt_Gtm_Wrapper_GetTimeRemaining(psGpt_HwConfig->u8HwChannel);
            break;
        }
#endif
        case GPT_MODULE_PIT:
        {
            u32Gpt_ReturnValue = Gpt_Pit_Wrapper_GetTimeRemaining(psGpt_HwConfig->u8HwChannel);
            break;
        }

        case GPT_MODULE_STM:
        {
            u32Gpt_ReturnValue = Gpt_Stm_Wrapper_GetTimeRemaining(psGpt_HwConfig->u8HwChannel);
            break;
        }
        
        case GPT_MODULE_RTC:
        case GPT_MODULE_API:
        {
            u32Gpt_ReturnValue = Gpt_Rtc_Wrapper_GetTimeRemaining();
            break;
        }
        default:
        {
            /* default case, nothing todo */
            break;
        }
    }

    return u32Gpt_ReturnValue;
}

FUNC (void, GPT_CODE) Gpt_AutoSar_Wrapper_StartTimer 						\
( 																			\
    P2CONST(Gpt_HwChannelConfig, AUTOMATIC,GPT_APPL_CONST) psGpt_HwConfig,  \
    VAR(Gpt_ValueType, AUTOMATIC) u32Gpt_Value 								\
)
{
	if(psGpt_HwConfig != NULL_PTR)
	{
		switch(psGpt_HwConfig->eHwModule)
		{
#if ( defined(CCFC3012PT) )
			case GPT_MODULE_GTM:
			{
				Gpt_Gtm_Wrapper_Channel_StartTimer(psGpt_HwConfig->u8HwChannel, u32Gpt_Value);
				break;
			}
#endif
			case GPT_MODULE_PIT:
			{
				Gpt_Pit_Wrapper_StartTimer(psGpt_HwConfig->u8HwChannel, u32Gpt_Value);
				break;
			}

			case GPT_MODULE_STM:
			{
				Gpt_Stm_Wrapper_StartTimer(psGpt_HwConfig->u8HwChannel, u32Gpt_Value);
				break;
			}
            
            case GPT_MODULE_RTC:
            {
                Gpt_Rtc_Wrapper_StartTimer(u32Gpt_Value);
                break;
            }
            case GPT_MODULE_API:
            {
            	Gpt_Api_Wrapper_StartTimer(u32Gpt_Value);
                break;
            }
			default:
			{
				/* default case, nothing todo */
				break;
			}
		}
	}
}

FUNC (void, GPT_CODE) Gpt_AutoSar_Wrapper_StopTimer 						\
( 																			\
    P2CONST(Gpt_HwChannelConfig, AUTOMATIC,GPT_APPL_CONST) psGpt_HwConfig 	\
)
{
	if(psGpt_HwConfig != NULL_PTR)
	{
		switch(psGpt_HwConfig->eHwModule)
		{
#if ( defined(CCFC3012PT))
			case GPT_MODULE_GTM:
			{
				Gpt_Gtm_Wrapper_StopTimer(psGpt_HwConfig->u8HwChannel);
				break;
			}
#endif
			case GPT_MODULE_PIT:
			{
				Gpt_Pit_Wrapper_StopTimer(psGpt_HwConfig->u8HwChannel);
				break;
			}

			case GPT_MODULE_STM:
			{
				Gpt_Stm_Wrapper_StopTimer(psGpt_HwConfig->u8HwChannel);
				break;
			}
        
            case GPT_MODULE_RTC:
            {
                Gpt_Rtc_Wrapper_StopTimer();
                break;
            }
            
            case GPT_MODULE_API:
            {
                Gpt_Api_Wrapper_StopTimer();
                break;
            }

			default:
			{
				/* default case, nothing todo */
				break;
			}
		}
	}
}

FUNC (void, GPT_CODE) Gpt_AutoSar_Wrapper_EnableInterrupt 					\
( 																			\
    P2CONST(Gpt_HwChannelConfig, AUTOMATIC,GPT_APPL_CONST) psGpt_HwConfig 	\
)
{
	if(psGpt_HwConfig != NULL_PTR)
	{
		switch(psGpt_HwConfig->eHwModule)
		{
#if ( defined(CCFC3012PT) )
			case GPT_MODULE_GTM:
			{
				Gpt_Gtm_Wrapper_EnableInterrupt(psGpt_HwConfig->u8HwChannel);
				break;
			}
#endif
			case GPT_MODULE_PIT:
			{
				Gpt_Pit_Wrapper_EnableNotification(psGpt_HwConfig->u8HwChannel);
				break;
			}

			case GPT_MODULE_STM:
			{
                /*For a STM enabled channel, the interrupts are allways activated*/
				break;
			}
            
            case GPT_MODULE_RTC:
            {
                Gpt_Rtc_Wrapper_EnableNotification();
                break;
            }
            case GPT_MODULE_API:
            {
                Gpt_Api_Wrapper_EnableNotification();
                break;
            }
			default:
			{
				/* default case, nothing todo */
				break;
			}
		}
	}
}

FUNC (void, GPT_CODE) Gpt_AutoSar_Wrapper_DisableInterrupt 					\
( 																			\
    P2CONST(Gpt_HwChannelConfig, AUTOMATIC,GPT_APPL_CONST) psGpt_HwConfig   \
)
{
	if(psGpt_HwConfig != NULL_PTR)
	{
		switch(psGpt_HwConfig->eHwModule)
		{
#if ( defined(CCFC3012PT))
			case GPT_MODULE_GTM:
			{
				Gpt_Gtm_Wrapper_DisableInterrupt(psGpt_HwConfig->u8HwChannel);
				break;
			}
#endif
			case GPT_MODULE_PIT:
			{
				Gpt_Pit_Wrapper_DisableNotification(psGpt_HwConfig->u8HwChannel);
				break;
			}

			case GPT_MODULE_STM:
			{
				/*For a STM enabled channel, the interrupts are allways activated*/
				break;
			}
            
            case GPT_MODULE_RTC:
            {
                Gpt_Rtc_Wrapper_DisableNotification();
                break;
            }
            case GPT_MODULE_API:
            {
                Gpt_Api_Wrapper_DisableNotification();
                break;
            }

			default:
			{
				/* default case, nothing todo */
				break;
			}
		}
	}
}

#if(GPT_PREDEFTIMER_FUNCTIONALITY_API == STD_ON)
FUNC (void, GPT_CODE) Gpt_AutoSar_Wrapper_GetPredefTimerValue 						\
( 																					\
    P2CONST(Gpt_HwPredefChannelConfig, AUTOMATIC,GPT_APPL_CONST) psGpt_HwConfig, 	\
    VAR(Gpt_PredefTimerType, AUTOMATIC) eGpt_PredefTimer, 							\
    P2VAR(uint32, AUTOMATIC, GPT_APPL_DATA) pu32Gpt_TimeValuePtr 					\
)
{
    switch(psGpt_HwConfig->eHwModule)
    {
        case GPT_MODULE_GTM:
        {
            /* GTM has not PredefTimer */
            break;
        }

        case GPT_MODULE_PIT:
        {
            /* PIT has not PredefTimer */
            break;
        }

        case GPT_MODULE_STM:
        {
            *pu32Gpt_TimeValuePtr = Gpt_Stm_Wrapper_GetPredefTimerValue \
                                    (psGpt_HwConfig->u8HwChannel, eGpt_PredefTimer);
            break;
        }

        default:
            /* default case, nothing todo */
            break;
    }
}

/*
    [SWS_Gpt_00382]  A GPT Predef Timer is a free running up counter (user point of
    view). If the timer has reached the maximum value (max value = 2n
    -1, n=number of bits), the timer shall continue running with the value "0" at next timer tick. 
    [SWS_Gpt_00386]  If a GPT Predef Timer is enabled, the timer(s) with the same
    tick duration and lower bit number(s) shall be enabled also. 
    [SWS_Gpt_00385]  It shall be possible to configure which GPT Predef Timers are
    enabled. 
    [SWS_Gpt_00384]  A GPT Predef Timer shall have a maximum tick tolerance of
    +/- 1 tick to ensure accuracy of time based functionality. 
*/
FUNC (void, GPT_CODE) Gpt_Wrapper_StartPredefTimer
(
    P2CONST(Gpt_ConfigType, AUTOMATIC,GPT_APPL_CONST) pGptConfig
)
{
    VAR(Gpt_ChannelType, AUTOMATIC) channel = 0;
    P2CONST(Gpt_HwPredefChannelConfig, AUTOMATIC, GPT_APPL_CONST) pHwChannelConfig = NULL_PTR;

    for(channel = 0U; channel < GPT_HW_PREDEFTIMER_NUM; channel++)
    {
        pHwChannelConfig = (pGptConfig->pChannelPredefConfigType)[channel];

        if(NULL_PTR != pHwChannelConfig)
        {
            switch(pHwChannelConfig->eHwModule)
            {
            case GPT_MODULE_STM:
            {
                Gpt_Stm_Wrapper_StartPredefTimer(pHwChannelConfig->u8HwChannel,
                                            pHwChannelConfig->u8StmPrescaler,
                                            pHwChannelConfig->bFreezeEnable);
            }
            break;

            default:
                /* Not support */
            break;
            }
        }
    }

    return;
}

FUNC (void, GPT_CODE) Gpt_Wrapper_StopPredefTimer
(
    P2CONST(Gpt_ConfigType, AUTOMATIC,GPT_APPL_CONST) pGptConfig
)
{
    VAR(Gpt_ChannelType, AUTOMATIC) channel = 0;
    P2CONST(Gpt_HwPredefChannelConfig, AUTOMATIC, GPT_APPL_CONST) pHwChannelConfig = NULL_PTR;

    for(channel = 0U; channel < GPT_HW_PREDEFTIMER_NUM; channel++)
    {
        pHwChannelConfig = (pGptConfig->pChannelPredefConfigType)[channel];
        if(NULL_PTR != pHwChannelConfig)
        {
            switch(pHwChannelConfig->eHwModule)
            {
                case GPT_MODULE_STM:
                {
                    Gpt_Stm_Wrapper_StopPredefTimer(pHwChannelConfig->u8HwChannel);
                    break;
                }
                default:
                    /* Not support */
                break;
            }
        }
    }
    return;
}
#endif /* GPT_PREDEFTIMER_FUNCTIONALITY_API */
#if ( defined(CCFC3012PT))
FUNC(void, GPT_CODE) Gpt_AutoSar_Wrapper_Gtm_Init   \
(                                                   \
    P2CONST( Gpt_GtmCmuConfigType, AUTOMATIC, MCL_APPL_CONST) ConfigPtr \
)
{
    Gpt_GtmCmu_Wrapper_Init(&ConfigPtr->cmu_configuration);
    Gpt_GtmTbu_Wrapper_Init(&ConfigPtr->tbu_configuration);
}

FUNC(void, GPT_CODE) Gpt_AutoSar_Wrapper_Gtm_Denit(void)
{
	Gpt_GtmCmu_Wrapper_Deinit();
    Gpt_GtmTbu_Wrapper_Deinit();
}
#endif
#ifdef __cplusplus
}
#endif


