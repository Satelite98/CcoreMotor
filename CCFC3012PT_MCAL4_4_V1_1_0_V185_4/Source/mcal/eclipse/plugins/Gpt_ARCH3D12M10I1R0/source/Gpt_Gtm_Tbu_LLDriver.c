
/****************************************************************************
*
* Copyright (c) 2023  C*Core -   All Rights Reserved
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* PROJECT     : CCFC3008PT
* DESCRIPTION : CCFC3008PT GTM TOM low level drivers code
* HISTORY     : Initial version
* @file     Gpt_Gtm_Tbu_LLDriver.c
* @version  1.0
* @date     2023 - 05 - 11
* @brief    Initial version.
*
*****************************************************************************/
 /*PRQA S 0380,1296,1503,1317,1338,1881,2016,2023,2024,4442 EOF*/
#if ( defined(CCFC3007PT) || defined(CCFC3008PT))
#include "Gpt_Gtm_LLDriver.h"
#include "Gpt_Irq.h"
#include "Gpt_Cfg.h"

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

 
typedef volatile struct GTM_TBU_tag st_Gpt_GTM_TBU_tag;

#define GPT_GTM_TBU_BASE_ADDR							 (&GTM_TBU)

static P2VAR(st_Gpt_GTM_TBU_tag, AUTOMATIC, GPT_APPL_DATA) g_GPT_GTM_TBU_Base[1u] = {
										 GPT_GTM_TBU_BASE_ADDR
};


FUNC(Std_ReturnType, GPT_CODE) GPT_GTM_TBU_LLD_IsEnableClock
(
    VAR(GPT_GTM_TBU_CHEN_Type, AUTOMATIC) Clock,       \
    VAR(uint32, AUTOMATIC) IsEnable        \
)
{
	VAR(Std_ReturnType, AUTOMATIC) Ret = (Std_ReturnType)E_NOT_OK;

    switch(Clock)
    {
        case GPT_GTM_TBU_CHEN_CH0:
        {

            g_GPT_GTM_TBU_Base[0]->CHEN.B.ENDIS_CH0 = IsEnable;
            break;
        }
        case GPT_GTM_TBU_CHEN_CH1:
        {
            g_GPT_GTM_TBU_Base[0]->CHEN.B.ENDIS_CH1 = IsEnable;
            break;
        }
        case GPT_GTM_TBU_CHEN_CH2:
        {
            g_GPT_GTM_TBU_Base[0]->CHEN.B.ENDIS_CH2 = IsEnable;
            break;
        }
        default:
        {
            Ret = (Std_ReturnType)E_NOT_OK;
            break;
        }
    }

    return Ret;
}

FUNC(Std_ReturnType, GPT_CODE) GPT_GTM_TBU_LLD_SetSLK  \
(                                                      \
    VAR(GPT_GTM_TBU_CHEN_Type, AUTOMATIC) Chn,         \
    VAR(uint8, AUTOMATIC) Clksrc \
)
{
	VAR(Std_ReturnType, AUTOMATIC) Ret = (Std_ReturnType)E_NOT_OK;


    if((uint8)Clksrc < 8u )
    {
        switch(Chn)
        {
            case GPT_GTM_TBU_CHEN_CH0:
            {
                g_GPT_GTM_TBU_Base[0]->CH0_CTRL.B.CH_CLK_SRC = (uint32)Clksrc;
                break;
            }
            case GPT_GTM_TBU_CHEN_CH1:
            {
                g_GPT_GTM_TBU_Base[0]->CH1_CTRL.B.CH_CLK_SRC = (uint32)Clksrc;
                break;
            }
            case GPT_GTM_TBU_CHEN_CH2:
            {
                g_GPT_GTM_TBU_Base[0]->CH2_CTRL.B.CH_CLK_SRC = (uint32)Clksrc;
                break;
            }
            default:
            {
                Ret = (Std_ReturnType)E_NOT_OK;
                break;
            }
        }
    }
    else
    {
        Ret = (Std_ReturnType)E_NOT_OK;
    }
    
    return Ret;
}


FUNC(void, GPT_CODE) GPT_GTM_TBU_LLD_SetCH0_LOWRES  \
(                                                   \
    VAR(uint8, AUTOMATIC) IsEnable                  \
)
{
    g_GPT_GTM_TBU_Base[0]->CH0_CTRL.B.LOW_RES = (uint32)IsEnable;
}

FUNC(Std_ReturnType, GPT_CODE) GPT_GTM_TBU_LLD_SetBASE \
(                                               \
    VAR(GPT_GTM_TBU_CHEN_Type, AUTOMATIC) Chn,  \
    VAR(uint32, AUTOMATIC) Base                 \
)
{
	VAR(Std_ReturnType, AUTOMATIC) Ret = (Std_ReturnType)E_NOT_OK;

    switch(Chn)
    {
        case GPT_GTM_TBU_CHEN_CH0:
        {
            g_GPT_GTM_TBU_Base[0]->CH0_BASE.B.BASE = Base;
            break;
        }
        case GPT_GTM_TBU_CHEN_CH1:
        {
            g_GPT_GTM_TBU_Base[0]->CH1_BASE.B.BASE = Base;
            break;
        }
        case GPT_GTM_TBU_CHEN_CH2:
        {
            g_GPT_GTM_TBU_Base[0]->CH2_BASE.B.BASE = Base;
            break;
        }
        default:
        {
            Ret = (Std_ReturnType)E_NOT_OK;
            break;
        }
    }

    return Ret;
}

FUNC(Std_ReturnType, GPT_CODE) GPT_GTM_TBU_LLD_SetCHMODE  \
(                                                   \
    VAR(GPT_GTM_TBU_CHEN_Type, AUTOMATIC) Chn,      \
    VAR(uint32, AUTOMATIC) Mode                     \
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret = (Std_ReturnType)E_NOT_OK;

    switch(Chn)
    {
        case GPT_GTM_TBU_CHEN_CH1:
        {
            g_GPT_GTM_TBU_Base[0]->CH1_CTRL.B.CH_MODE = Mode;
            break;
        }
        case GPT_GTM_TBU_CHEN_CH2:
        {
            g_GPT_GTM_TBU_Base[0]->CH2_CTRL.B.CH_MODE = Mode;
            break;
        }
        default:
        {
            Ret = (Std_ReturnType)E_NOT_OK;
            break;
        }
    }

    return Ret;
}
#endif

