/**
*   @file    WdgIf.c
*   @implements        Wdg_HLD_unit
*   @version 1.0.1
*
*   @brief   AUTOSAR WdgIf high level code.
*   @details This file contains the Autosar WDG driver high level code.
*
*   @addtogroup WDG_MODULE
*   @{
*/
/*=================================================================================================
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
=================================================================================================*/
/*=================================================================================================
=================================================================================================*/

#ifdef __cplusplus
extern "C"{
#endif




/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/


#include "WdgIf.h"
#if (WDGIF_NUMBER_OF_DEVICES == 1U) 
    #include "Wdg.h"
#endif

#if (WDGIF_NUMBER_OF_DEVICES != 1U)     
#ifdef WDGINSTANCE0
#if (WDGINSTANCE0 == STD_ON)
    #include "Wdg_176_ModId0.h"
#endif
#endif

#ifdef WDGINSTANCE1
#if (WDGINSTANCE1 == STD_ON)
    #include "Wdg_176_ModId1.h"
#endif
#endif

#ifdef WDGINSTANCE2
#if (WDGINSTANCE2 == STD_ON)
    #include "Wdg_176_ModId2.h"
#endif
#endif

#ifdef WDGINSTANCE3
#if (WDGINSTANCE3 == STD_ON)
    #include "Wdg_176_ModId3.h"
#endif
#endif


#endif

/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/


#if (WDGIF_NUMBER_OF_DEVICES == 1U)
const WdgIf_SetModeFctPtrType WdgIf_SetModeFctPtr[WDGIF_NUMBER_OF_DEVICES] =
    {
        Wdg_SetMode
    };
    
const WdgIf_SetTriggerFctPtrType WdgIf_SetTriggerConditionFctPtr[WDGIF_NUMBER_OF_DEVICES] =
    {
        Wdg_SetTriggerCondition
    };
#else
const    WdgIf_SetModeFctPtrType WdgIf_SetModeFctPtr[WDGIF_NUMBER_OF_DEVICES] =
    {
        #if(WDGINSTANCE0 == STD_ON)
    		&Wdg_176_ModId0_SetMode
            #else
            NULL_PTR
        #endif
        #ifdef WDGINSTANCE1
            #if(WDGINSTANCE1 == STD_ON)
            ,&Wdg_176_ModId1_SetMode
            #else
            ,NULL_PTR
            #endif
        #endif
        #ifdef WDGINSTANCE2
            #if(WDGINSTANCE2 == STD_ON)
            ,&Wdg_176_ModId2_SetMode
            #else
            ,NULL_PTR
            #endif
        #endif
        #ifdef WDGINSTANCE3
            #if(WDGINSTANCE3 == STD_ON)
            ,&Wdg_176_ModId3_SetMode
            #else
            ,NULL_PTR
            #endif
        #endif
    };
    
    
const    WdgIf_SetTriggerFctPtrType WdgIf_SetTriggerConditionFctPtr[WDGIF_NUMBER_OF_DEVICES] =
    {
        #if(WDGINSTANCE0 == STD_ON)
    		&Wdg_176_ModId0_SetTriggerCondition
            #else
            NULL_PTR
        #endif
        #ifdef WDGINSTANCE1
            #if(WDGINSTANCE1 == STD_ON)
            ,&Wdg_176_ModId1_SetTriggerCondition
            #else
            ,NULL_PTR
            #endif
        #endif
        #ifdef WDGINSTANCE2
            #if(WDGINSTANCE2 == STD_ON)
            ,&Wdg_176_ModId2_SetTriggerCondition
            #else
            ,NULL_PTR
            #endif
        #endif
        #ifdef WDGINSTANCE3
            #if(WDGINSTANCE3 == STD_ON)
            ,&Wdg_176_ModId3_SetTriggerCondition
            #else
            ,NULL_PTR
            #endif
        #endif
    };
#endif
/*=================================================================================================
*                                      GLOBAL VARIABLES
=================================================================================================*/



#ifdef __cplusplus
}
#endif

/** @} */
