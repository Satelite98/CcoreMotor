/****************************************************************************
*
* Copyright (c) 2023  C*Core -   All Rights Reserved
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* @file     Gpt_Stm_LLDriver.c
* @version  1.0
* @date     2023 - 01 - 01
* @brief    Initial version.
*
*****************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

/*PRQA S 1503,4404,1505,3469 EOF*/
#include "Gpt_Stm_LLDriver.h"/*PRQA S 0380*/
#include "Gpt_Irq.h"
#include "Gpt_AutoSar_Wrapper.h"
#include "Gpt_Stm_HAL_Wrapper.h"
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

extern P2CONST(Gpt_ConfigType, GPT_VAR,  GPT_APPL_CONST)  sGpt_pConfig[GPT_MAX_PARTITION];
static CONSTP2VAR(STM_tag_Type, AUTOMATIC, GPT_APPL_CONST) g_STMBase[STM_INSTANCE_NUM] = STM_BASE_ARRAY;

FUNC(STM_ChannelID_Type, GPT_CODE) Gpt_Stm_LLD_ConvertChanId    
(                                                
   VAR(uint8, AUTOMATIC) u8ChannelId
) 
{
   VAR(STM_ChannelID_Type, AUTOMATIC) eChannelId;
   switch(u8ChannelId)
   {
      case 0u:
         eChannelId = STM_Channel0;
      break;
      case 1u:
         eChannelId = STM_Channel1;
      break;
      case 2u:
         eChannelId = STM_Channel2;
      break;
      case 3u:
         eChannelId = STM_Channel3;
      break;
      default:
         eChannelId = STM_Channel0;
      break;
   }

   return eChannelId;
}

FUNC(STM_ModuleID_Type, GPT_CODE) Gpt_Stm_LLD_ConvertModuleId    
(                                                
   VAR(uint8, AUTOMATIC) u8ModuleId
) 
{
   VAR(STM_ModuleID_Type, AUTOMATIC) eModuleId;
   switch(u8ModuleId)
   {
      case 0u:
         eModuleId = STM0;
      break;
      case 1u:
         eModuleId = STM1;
      break;
      case 2u:
         eModuleId = STM2;
      break;
      case 3u:
         eModuleId = STM3;
      break;
      case 4u:
         eModuleId = STM4;
      break;
      case 5u:
         eModuleId = STM5;
      break;
      default:
         eModuleId = STM0;
      break;
   }

   return eModuleId;
}

FUNC(void, GPT_CODE) Gpt_Stm_LLD_ClearIntFlag    \
(                                                \
   VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID,  \
   VAR(STM_ChannelID_Type, AUTOMATIC) STM_ChannelID \
)
{ 
   DEV_ASSERT((uint8)STM_ModuleID < (uint8)STM_INSTANCE_NUM);
   DEV_ASSERT((uint8)STM_ChannelID < 4u);

   CONSTP2VAR(STM_tag_Type, AUTOMATIC, GPT_APPL_CONST) base =  g_STMBase[(uint8)STM_ModuleID];

   /*Clear channel interrupt flag*/
   base->CHANNEL[STM_ChannelID].CIR.R = TRUE;

}

FUNC(void, GPT_CODE) Gpt_Stm_LLD_ModuleDisable (VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID)
{
   DEV_ASSERT((uint8)STM_ModuleID < (uint8)STM_INSTANCE_NUM);

   CONSTP2VAR(STM_tag_Type, AUTOMATIC, GPT_APPL_CONST) base = g_STMBase[(uint8)STM_ModuleID];

   /*Enable module clock*/
   base->CR.B.TEN = (uint8)STM_Disable;

}

/*******************************************************************************
* @brief      :Enable module clock
* @param[in]  :STM_ModuleID STM peripheral instance number
* @param[out] :None
* @retval     :Error or success status returned by API
*******************************************************************************/
FUNC(Std_ReturnType, GPT_CODE) Gpt_Stm_LLD_ModuleEnable (VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID)
{
   /*Check Module ID*/
   DEV_ASSERT((uint8)STM_ModuleID < (uint8)STM_INSTANCE_NUM);

   CONSTP2VAR(STM_tag_Type, AUTOMATIC, GPT_APPL_CONST) base = g_STMBase[STM_ModuleID];

   /*Enable module clock*/
   base->CR.B.TEN = (uint8)STM_Enable;

   return (Std_ReturnType)E_OK;
}

FUNC(STM_Std_ReturnTypeype, GPT_CODE) Gpt_Stm_LLD_IsModuleEnable (VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID)
{
   DEV_ASSERT((uint8)STM_ModuleID < (uint8)STM_INSTANCE_NUM);

   STM_tag_Type * const base = g_STMBase[(uint8)STM_ModuleID];

   /* module clock*/
   return (base->CR.B.TEN == (uint32)1) ? STM_Enable : STM_Disable;
}

FUNC(void, GPT_CODE) Gpt_Stm_LLD_ChannelEnable   \
(                                                \
   VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID,  \
   VAR(STM_ChannelID_Type, AUTOMATIC) STM_ChannelID \
)
{
   DEV_ASSERT((uint8)STM_ModuleID < (uint8)STM_INSTANCE_NUM);
   DEV_ASSERT((uint8)STM_ChannelID < 4u);

   CONSTP2VAR(STM_tag_Type, AUTOMATIC, GPT_APPL_CONST) base = g_STMBase[(uint8)STM_ModuleID];

   /*Enable channel clock*/
   base->CHANNEL[STM_ChannelID].CCR.B.CEN = (uint8)STM_Enable;
}

FUNC(void, GPT_CODE) Gpt_Stm_LLD_ChannelDisable      \
(                                                    \
   VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID,   \
   VAR(STM_ChannelID_Type, AUTOMATIC) STM_ChannelID  \
)
{
   DEV_ASSERT((uint8)STM_ModuleID < (uint8)STM_INSTANCE_NUM);
   DEV_ASSERT((uint8)STM_ChannelID < 4u);

   CONSTP2VAR(STM_tag_Type, AUTOMATIC, GPT_APPL_CONST) base = g_STMBase[(uint8)STM_ModuleID];

   /*Disable channel clock*/
   base->CHANNEL[STM_ChannelID].CCR.B.CEN = (uint8)STM_Disable;

}

FUNC(void, GPT_CODE) Gpt_Stm_LLD_SetCounter        \
(                                                  \
   VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID, \
   VAR(uint32, AUTOMATIC) value                    \
)
{
   DEV_ASSERT((uint8)STM_ModuleID < (uint8)STM_INSTANCE_NUM);

   CONSTP2VAR(STM_tag_Type, AUTOMATIC, GPT_APPL_CONST) base = g_STMBase[(uint8)STM_ModuleID];

   /*Set Counter value*/
   base->CNT.R = value;
}

FUNC(uint32, GPT_CODE) Gpt_Stm_LLD_GetCounter(VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID)
{
   DEV_ASSERT((uint8)STM_ModuleID < (uint8)STM_INSTANCE_NUM);

   P2CONST(STM_tag_Type, AUTOMATIC, GPT_APPL_CONST) base = g_STMBase[(uint8)STM_ModuleID];

   /*Return module current counter value*/
   return base->CNT.R;
}

FUNC(void, GPT_CODE) Gpt_Stm_LLD_SetDebugFreeze     \
(                                                   \
   VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID,  \
   VAR(STM_DebugMode_Type, AUTOMATIC) STM_DebugMode \
)
{
   DEV_ASSERT((uint8)STM_ModuleID < (uint8)STM_INSTANCE_NUM);

   CONSTP2VAR(STM_tag_Type, AUTOMATIC, GPT_APPL_CONST) base = g_STMBase[(uint8)STM_ModuleID];

   /*Set module freeze mode*/ 
   base->CR.B.FRZ = (uint8)STM_DebugMode;

}

FUNC(uint8, GPT_CODE) Gpt_Stm_LLD_GetDebugFreeze(VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID)
{
   /*Check Module ID*/
   DEV_ASSERT((uint8)STM_ModuleID < (uint8)STM_INSTANCE_NUM);

   P2CONST(STM_tag_Type, AUTOMATIC, GPT_APPL_CONST) base = g_STMBase[STM_ModuleID];
   /*return module freeze mode*/
   return (uint8)base->CR.B.FRZ;
}

FUNC(uint32, GPT_CODE) Gpt_Stm_LLD_GetIntFlag    \
(                                                \
   VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID,  \
   VAR(STM_ChannelID_Type, AUTOMATIC) STM_ChannelID \
)
{
   DEV_ASSERT((uint8)STM_ModuleID < (uint8)STM_INSTANCE_NUM);
   DEV_ASSERT((uint8)STM_ChannelID < 4u);

   P2CONST(STM_tag_Type, AUTOMATIC, GPT_APPL_CONST) base = g_STMBase[STM_ModuleID];
   /*return channel interrupt flag*/
   return (uint32)base->CHANNEL[STM_ChannelID].CIR.R;
}

FUNC(void, GPT_CODE) Gpt_Stm_LLD_SetCompareValue     \
( 													 \
   VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID,   \
   VAR(STM_ChannelID_Type, AUTOMATIC) STM_ChannelID, \
   VAR(uint32, AUTOMATIC) CompareValue \
)
{
   DEV_ASSERT((uint8)STM_ModuleID < (uint8)STM_INSTANCE_NUM);
   DEV_ASSERT((uint8)STM_ChannelID < 4u);
   VAR(uint8, AUTOMATIC) offset = 1U;
   CONSTP2VAR(STM_tag_Type, AUTOMATIC, GPT_APPL_CONST) base = g_STMBase[(uint8)STM_ModuleID];
   if(CompareValue == 0U)
   {
       offset = 0U;
   }

   /*Set channel compare value*/
   base->CHANNEL[STM_ChannelID].CMP.R = (CompareValue - offset);

}

FUNC(uint32, GPT_CODE) Gpt_Stm_LLD_GetCompareValue  \
(                                                   \
   VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID,  \
   VAR(STM_ChannelID_Type, AUTOMATIC) STM_ChannelID \
)
{
   /*Check Module ID*/
   DEV_ASSERT((uint8)STM_ModuleID < (uint8)STM_INSTANCE_NUM);
   /*Check Channel ID*/
   DEV_ASSERT((uint8)STM_ChannelID < 4u);

   P2CONST(STM_tag_Type, AUTOMATIC, GPT_APPL_CONST) base = g_STMBase[STM_ModuleID];
   /*return channel compare value*/
   return (uint32)base->CHANNEL[STM_ChannelID].CMP.R;
}

FUNC(void, GPT_CODE) Gpt_Stm_LLD_SetPrescaler      \
(                                                  \
   VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID, \
   VAR(uint32, AUTOMATIC) ClockDivision            \
)
{
   DEV_ASSERT((uint8)STM_ModuleID < (uint8)STM_INSTANCE_NUM);
   VAR(uint32, AUTOMATIC) STM_CRvalue;
   CONSTP2VAR(STM_tag_Type, AUTOMATIC, GPT_APPL_CONST) base = g_STMBase[(uint8)STM_ModuleID];

   /*Set module prescaler*/
   STM_CRvalue = base->CR.R;
   STM_CRvalue &= ~(STM_CR_CPS_MASK);
   STM_CRvalue |= (((uint32)(((uint32)(ClockDivision)) << STM_CR_CPS_SHIFT)) & STM_CR_CPS_MASK);   

   base->CR.R = STM_CRvalue; 
}

FUNC(void, GPT_CODE) Gpt_Stm_LLD_Deinit(VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID)
{
   /*Check Module ID*/
   DEV_ASSERT((uint8)STM_ModuleID < (uint8)STM_INSTANCE_NUM);

   /*Reset prescaler*/
   Gpt_Stm_LLD_SetPrescaler(STM_ModuleID, 0U);
   /*Disable freeze mode*/
   Gpt_Stm_LLD_SetDebugFreeze(STM_ModuleID, STM_FREEZEOFF);
   /*Disable module clock*/
   Gpt_Stm_LLD_ModuleDisable(STM_ModuleID);
   /*Reset counter*/
   Gpt_Stm_LLD_SetCounter(STM_ModuleID, 0U);

   /*Disable channel*/
   Gpt_Stm_LLD_ChannelDisable(STM_ModuleID, STM_Channel0);/*PRQA S 4442*/
   /*Clear channel interrupt flag*/
   Gpt_Stm_LLD_ClearIntFlag(STM_ModuleID, STM_Channel0);/*PRQA S 4442*/
   /*Reset channel compare value*/
   Gpt_Stm_LLD_SetCompareValue(STM_ModuleID, STM_Channel0, 0u);/*PRQA S 4442*/
   /*Disable channel*/
   Gpt_Stm_LLD_ChannelDisable(STM_ModuleID, STM_Channel1);/*PRQA S 4442*/
   /*Clear channel interrupt flag*/
   Gpt_Stm_LLD_ClearIntFlag(STM_ModuleID, STM_Channel1);/*PRQA S 4442*/
   /*Reset channel compare value*/
   Gpt_Stm_LLD_SetCompareValue(STM_ModuleID, STM_Channel1, 0u);/*PRQA S 4442*/
   /*Disable channel*/
   Gpt_Stm_LLD_ChannelDisable(STM_ModuleID, STM_Channel2);/*PRQA S 4442*/
   /*Clear channel interrupt flag*/
   Gpt_Stm_LLD_ClearIntFlag(STM_ModuleID, STM_Channel2);/*PRQA S 4442*/
   /*Reset channel compare value*/
   Gpt_Stm_LLD_SetCompareValue(STM_ModuleID, STM_Channel2, 0u);/*PRQA S 4442*/
   /*Disable channel*/
   Gpt_Stm_LLD_ChannelDisable(STM_ModuleID, STM_Channel3);/*PRQA S 4442*/
   /*Clear channel interrupt flag*/
   Gpt_Stm_LLD_ClearIntFlag(STM_ModuleID, STM_Channel3);/*PRQA S 4442*/
   /*Reset channel compare value*/
   Gpt_Stm_LLD_SetCompareValue(STM_ModuleID, STM_Channel3, 0u);/*PRQA S 4442*/
}

FUNC(Std_ReturnType, GPT_CODE) Gpt_STM_LLD_DelayInit(VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID)
{
   /*Check Module ID*/
   DEV_ASSERT((uint8)STM_ModuleID < (uint8)STM_INSTANCE_NUM);

   VAR(uint8, AUTOMATIC) prescaler;

   /*Get module prescaler*/
   prescaler = (uint8)((uint32)(50000000u / 1000000u) - 1U);
   /*Reset module*/
   (void)Gpt_Stm_LLD_Deinit(STM_ModuleID);
   /*Set prescaler*/
   Gpt_Stm_LLD_SetPrescaler(STM_ModuleID, prescaler);
   /*Reset counter*/
   Gpt_Stm_LLD_SetCounter(STM_ModuleID, 0u);
   /*Enable module clock*/
   (void)Gpt_Stm_LLD_ModuleEnable(STM_ModuleID);

   return (Std_ReturnType)E_OK;
}

FUNC(void, GPT_CODE) Gpt_Stm_LLD_DelayMs(VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID, VAR(uint32, AUTOMATIC) ms)
{
	/*Check Module ID*/
	DEV_ASSERT((uint8)STM_ModuleID < (uint8)STM_INSTANCE_NUM);

    VAR(uint32, AUTOMATIC) tempValue;

    P2CONST(STM_tag_Type, AUTOMATIC, GPT_APPL_CONST) base = g_STMBase[STM_ModuleID];

	/*Get current counter value*/
	tempValue = Gpt_Stm_LLD_GetCounter(STM_ModuleID);

	if((tempValue + (ms*1000u)) > 0xFFFFFFFFU)
	{
		Gpt_Stm_LLD_SetCounter(STM_ModuleID, 0);
		tempValue = Gpt_Stm_LLD_GetCounter(STM_ModuleID);
	}

	/*Calculate the value that the counter should reach*/
	tempValue += ms*1000u;

	/*Wait for the counter to reach the count value*/
	while ((base->CNT.R) < (tempValue))
	{}
}

FUNC(void, GPT_CODE) Gpt_Stm_LLD_DelayUs(VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID, VAR(uint32, AUTOMATIC) us)
{
   /*Check Module ID*/
   DEV_ASSERT((uint8)STM_ModuleID < (uint8)STM_INSTANCE_NUM);

   VAR(uint32, AUTOMATIC) tempValue;

   P2CONST(STM_tag_Type, AUTOMATIC, GPT_APPL_CONST) base = g_STMBase[STM_ModuleID];

   /*Calculate the value that the counter should reach*/
   tempValue = Gpt_Stm_LLD_GetCounter(STM_ModuleID);

	if((tempValue + us) > 0xFFFFFFFFU)
	{
		Gpt_Stm_LLD_SetCounter(STM_ModuleID, 0);
		tempValue = Gpt_Stm_LLD_GetCounter(STM_ModuleID);
	}
   /*Calculate the value that the counter should reach*/
   tempValue += us;

   /*Wait for the counter to reach the count value*/
   while ((base->CNT.R) < (tempValue))
   {}
}

FUNC(void, GPT_CODE) Gpt_Stm_IRQHandler 		       \
( 												                \
   VAR(STM_ModuleID_Type, AUTOMATIC) STM_ModuleID,  \
   VAR(STM_ChannelID_Type, AUTOMATIC) STM_ChannelID \
)
{

   VAR(uint32, AUTOMATIC) tempValue;
   VAR(uint32, AUTOMATIC) CoreIndex = Gpt_GetCoreID();
   CONSTP2VAR(STM_tag_Type, AUTOMATIC, GPT_APPL_CONST) base = g_STMBase[(uint8)STM_ModuleID];

   VAR(Gpt_ChannelType, AUTOMATIC) u8Gpt_Instance = (uint8)((STM_ModuleID * GPT_STM_CHANNEL_MAX) + STM_ChannelID + GPT_STM_MODULE_INDEX);
   VAR(uint8, AUTOMATIC) u8Channel = sGpt_pConfig[CoreIndex]->Gpt_aHw2LogicChannelMap[u8Gpt_Instance];


#if (GPT_ENABLE_MULTICORE == STD_ON)
   P2VAR(Gpt_Wrapper_ChannelInfo, AUTOMATIC, GPT_APPL_DATA) pChannelInfo = NULL_PTR;

   VAR(uint32, AUTOMATIC) CurrentCoreId = 1 << Gpt_GetCoreID();

   pChannelInfo = Gpt_AutoSar_Wrapper_GetChannelInfo(u8Channel);

   VAR(uint8, AUTOMATCI) Temp = CurrentCoreId & pChannelInfo->pGpt_CoreId[u8Channel];

   if(Temp != (uint8)0u)
#endif
   {
	   base->CHANNEL[STM_ChannelID].CCR.R = (uint8)STM_Disable;
	   base->CHANNEL[STM_ChannelID].CIR.R = TRUE;
	   tempValue = (uint32)base->CHANNEL[STM_ChannelID].CMP.R;
	   tempValue += u32StmTargetValue[STM_ModuleID][STM_ChannelID];

	   base->CHANNEL[STM_ChannelID].CMP.R = (tempValue);
	   base->CHANNEL[STM_ChannelID].CCR.R = (uint8)STM_Enable;

	   if (GPT_CH_MODE_ONESHOT == (*(sGpt_pConfig[CoreIndex]->pChannelConfig))[u8Channel].eChannelMode)
	  {
		   SchM_Enter_GPT_EXCLUSIVE_AREA_03();
		   base->CHANNEL[STM_ChannelID].CCR.R = (uint8)STM_Disable;
		   SchM_Exit_GPT_EXCLUSIVE_AREA_03();
	  }

	   Gpt_ProcessCommonIrq(u8Channel);
   }
}

#ifdef __cplusplus
}
#endif
