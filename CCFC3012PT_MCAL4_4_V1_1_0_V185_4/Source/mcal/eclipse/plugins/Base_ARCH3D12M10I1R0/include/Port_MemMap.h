/**
* @file Port_MemMap.h
* @version 1.0.1
**@brief   AUTOSAR PORT Rte - module interface.
* @details This file mainly contains reentrant interfaces and multi - core mutually exclusive interface definitions
*
* @addtogroup
* @{
*/
/****************************************************************************
*
* Copyright (c) 2022  C*Core -   All Rights Reserved
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS, " AND ALL WARRANTIES ARE DISCLAIMED,
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
*   @file    Port_MemMap.h
*   @version 1.0.1
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Rte MCAL driver.
*
*   @addtogroup Rte
*   @{
*/
/*====================================================================================================
                                            INCLUDE FILES
====================================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif
#include "CompilerDefinition.h"

/*====================================================================================================
                                        DISABLE WARNING START
====================================================================================================*/
#ifdef GHS_C_CCFC30XX
#pragma ghs nowarning 1512
#endif
/*====================================================================================================
                                    SOURCE FILE VERSION INFORMATION
====================================================================================================*/
/*====================================================================================================
                                         FILE VERSION CHECKS
====================================================================================================*/
/*====================================================================================================
                                             LOCAL MACROS
====================================================================================================*/
#define PORT_MEMMAP_SECTION_NOTMATCH_ERROR   "Port_MemMap.h, start - stop section defined not match."
#define MEM_ERROR

/*************************************************************************************************/
/*                                         S32DS                                                 */
/*************************************************************************************************/
#ifdef S32DS_C_CCFC30XX
/**
* MCAL MemMap defined, Used for configure data,
* Used START_SEC_CONFIG_DATA must match with STOP_SEC_CONFIG_DATA 
*/
#ifdef PORT_START_SEC_CONFIG_DATA
    #undef PORT_START_SEC_CONFIG_DATA
    #define ENTERED_PORT_START_SEC_CONFIG_DATA
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_CONFIG_DATA
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        /* no definition -> default compiler settings are used */
#endif

#ifdef PORT_STOP_SEC_CONFIG_DATA
    #ifdef ENTERED_PORT_START_SEC_CONFIG_DATA
        #undef ENTERED_PORT_START_SEC_CONFIG_DATA
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_CONFIG_DATA
    #undef MEM_ERROR
        /* no definition -> default compiler settings are used */
#endif

/**
* MCAL MemMap defined, Used for code data,
* Used START_SEC_CODE must match with STOP_SEC_CODE 
*/
#ifdef PORT_START_SEC_CODE
    #undef PORT_START_SEC_CODE
    #define ENTERED_PORT_START_SEC_CODE
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_CODE
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        /* no definition -> default compiler settings are used */
#endif

#ifdef PORT_STOP_SEC_CODE
    #ifdef ENTERED_PORT_START_SEC_CODE
        #undef ENTERED_PORT_START_SEC_CODE
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_CODE
    #undef MEM_ERROR
        /* no definition -> default compiler settings are used */
#endif

/**
* MCAL MemMap defined, Used for noinit(bss) data,
* Used START_SEC_VAR_NO_INIT must match with STOP_SEC_VAR_NO_INIT 
*/
#ifdef PORT_START_SEC_VAR_NO_INIT
    #undef PORT_START_SEC_VAR_NO_INIT
    #define ENTERED_PORT_START_SEC_VAR_NO_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_NO_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        /* no definition -> default compiler settings are used */
#endif

#ifdef PORT_STOP_SEC_VAR_NO_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_NO_INIT
        #undef ENTERED_PORT_START_SEC_VAR_NO_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_NO_INIT
    #undef MEM_ERROR
        /* no definition -> default compiler settings are used */
#endif

/**
* MCAL MemMap defined, Used for global init data,
* Used START_SEC_VAR_INIT must match with STOP_SEC_VAR_INIT 
*/
#ifdef PORT_START_SEC_VAR_INIT
    #undef PORT_START_SEC_VAR_INIT
    #define ENTERED_PORT_START_SEC_VAR_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        /* no definition -> default compiler settings are used */
#endif

#ifdef PORT_STOP_SEC_VAR_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_INIT
        #undef ENTERED_PORT_START_SEC_VAR_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_INIT
    #undef MEM_ERROR
        /* no definition -> default compiler settings are used */
#endif

/**
* MCAL MemMap defined, Used for share init data,
* Used START_SEC_VAR_SHARED_INIT must match with STOP_SEC_VAR_SHARED_INIT 
*/
#ifdef PORT_START_SEC_VAR_SHARED_INIT
    #undef PORT_START_SEC_VAR_SHARED_INIT
    #define ENTERED_PORT_START_SEC_VAR_SHARED_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_SHARED_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        __attribute__ ((section (".data_share")))
#endif

#ifdef PORT_STOP_SEC_VAR_SHARED_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_SHARED_INIT
        #undef ENTERED_PORT_START_SEC_VAR_SHARED_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_SHARED_INIT
    #undef MEM_ERROR
        /* no definition -> default compiler settings are used */
#endif

/**
* MCAL MemMap defined, Used for share zero data,
* Used START_SEC_VAR_SHARED_NO_INIT must match with STOP_SEC_VAR_SHARED_NO_INIT 
*/
#ifdef PORT_START_SEC_VAR_SHARED_NO_INIT
    #undef PORT_START_SEC_VAR_SHARED_NO_INIT
    #define ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifdef PORT_STOP_SEC_VAR_SHARED_NO_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        __attribute__ ((section (".data_share")))
#endif

#ifdef PORT_STOP_SEC_VAR_SHARED_NO_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
        #undef ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_SHARED_NO_INIT
    #undef MEM_ERROR
        /* no definition -> default compiler settings are used */
#endif

/**
* MCAL MemMap defined, Used for code running in ram,
* Used START_SEC_RAMCODE must match with STOP_SEC_RAMCODE 
*/
#ifdef PORT_START_SEC_RAMCODE
    #undef PORT_START_SEC_RAMCODE
    #define ENTERED_PORT_START_SEC_RAMCODE
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifdef PORT_STOP_SEC_RAMCODE
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        __attribute__ ((section (".data.code")))
#endif

#ifdef PORT_STOP_SEC_RAMCODE
    #ifdef ENTERED_PORT_START_SEC_RAMCODE
        #undef ENTERED_PORT_START_SEC_RAMCODE
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_RAMCODE
    #undef MEM_ERROR
        /* no definition -> default compiler settings are used */
#endif

#endif /* S32DS_C_CCFC30XX */

/*************************************************************************************************/
/*                                       GREENHILLS                                              */
/*************************************************************************************************/
#ifdef GHS_C_CCFC30XX
/**
* MCAL MemMap defined, Used for configure data,
* Used START_SEC_CONFIG_DATA must match with STOP_SEC_CONFIG_DATA 
*/
#ifdef PORT_START_SEC_CONFIG_DATA
    #undef PORT_START_SEC_CONFIG_DATA
    #define ENTERED_PORT_START_SEC_CONFIG_DATA
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_CONFIG_DATA
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma ghs section rodata=".rodata"
#endif

#ifdef PORT_STOP_SEC_CONFIG_DATA
    #ifdef ENTERED_PORT_START_SEC_CONFIG_DATA
        #undef ENTERED_PORT_START_SEC_CONFIG_DATA
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_CONFIG_DATA
    #undef MEM_ERROR
        #pragma ghs section
#endif

/**
* MCAL MemMap defined, Used for code data,
* Used START_SEC_CODE must match with STOP_SEC_CODE 
*/
#ifdef PORT_START_SEC_CODE
    #undef PORT_START_SEC_CODE
    #define ENTERED_PORT_START_SEC_CODE
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_CODE
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma ghs section rodata=".text"
#endif

#ifdef PORT_STOP_SEC_CODE
    #ifdef ENTERED_PORT_START_SEC_CODE
        #undef ENTERED_PORT_START_SEC_CODE
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_CODE
    #undef MEM_ERROR
        #pragma ghs section
#endif

/**
* MCAL MemMap defined, Used for noinit(bss) data,
* Used START_SEC_VAR_NO_INIT must match with STOP_SEC_VAR_NO_INIT 
*/
#ifdef PORT_START_SEC_VAR_NO_INIT
    #undef PORT_START_SEC_VAR_NO_INIT
    #define ENTERED_PORT_START_SEC_VAR_NO_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_NO_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma ghs section bss=".bss"
#endif

#ifdef PORT_STOP_SEC_VAR_NO_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_NO_INIT
        #undef ENTERED_PORT_START_SEC_VAR_NO_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_NO_INIT
    #undef MEM_ERROR
        #pragma ghs section
#endif

/**
* MCAL MemMap defined, Used for global init data,
* Used START_SEC_VAR_INIT must match with STOP_SEC_VAR_INIT 
*/
#ifdef PORT_START_SEC_VAR_INIT
    #undef PORT_START_SEC_VAR_INIT
    #define ENTERED_PORT_START_SEC_VAR_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma ghs section data = ".data"
#endif

#ifdef PORT_STOP_SEC_VAR_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_INIT
        #undef ENTERED_PORT_START_SEC_VAR_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_INIT
    #undef MEM_ERROR
        #pragma ghs section
#endif

/**
* MCAL MemMap defined, Used for share init data,
* Used START_SEC_VAR_SHARED_INIT must match with STOP_SEC_VAR_SHARED_INIT 
*/
#ifdef PORT_START_SEC_VAR_SHARED_INIT
    #undef PORT_START_SEC_VAR_SHARED_INIT
    #define ENTERED_PORT_START_SEC_VAR_SHARED_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_SHARED_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma ghs section data = ".data_share"
#endif

#ifdef PORT_STOP_SEC_VAR_SHARED_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_SHARED_INIT
        #undef ENTERED_PORT_START_SEC_VAR_SHARED_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_SHARED_INIT
    #undef MEM_ERROR
        #pragma ghs section
#endif

/**
* MCAL MemMap defined, Used for share zero data,
* Used START_SEC_VAR_SHARED_NO_INIT must match with STOP_SEC_VAR_SHARED_NO_INIT 
*/
#ifdef PORT_START_SEC_VAR_SHARED_NO_INIT
    #undef PORT_START_SEC_VAR_SHARED_NO_INIT
    #define ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifdef PORT_STOP_SEC_VAR_SHARED_NO_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma ghs section data = ".data_share"
#endif

#ifdef PORT_STOP_SEC_VAR_SHARED_NO_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
        #undef ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_SHARED_NO_INIT
    #undef MEM_ERROR
        #pragma ghs section
#endif

/**
* MCAL MemMap defined, Used for code running in ram,
* Used START_SEC_RAMCODE must match with STOP_SEC_RAMCODE 
*/
#ifdef PORT_START_SEC_RAMCODE
    #undef PORT_START_SEC_RAMCODE
    #define ENTERED_PORT_START_SEC_RAMCODE
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifdef PORT_STOP_SEC_RAMCODE
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma ghs section text=".data.code"
        #pragma ghs inlineprologue
        #pragma ghs callmode=far
#endif

#ifdef PORT_STOP_SEC_RAMCODE
    #ifdef ENTERED_PORT_START_SEC_RAMCODE
        #undef ENTERED_PORT_START_SEC_RAMCODE
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_RAMCODE
    #undef MEM_ERROR
        #pragma ghs section
        #pragma ghs noinlineprologue
        #pragma ghs callmode=default
#endif

#endif /* GHS_C_CCFC30XX */

/*************************************************************************************************/
/*                                          DIAB                                                 */
/*************************************************************************************************/
#ifdef DCC_C_CCFC30XX
/**
* MCAL MemMap defined, Used for configure data,
* Used START_SEC_CONFIG_DATA must match with STOP_SEC_CONFIG_DATA 
*/
#ifdef PORT_START_SEC_CONFIG_DATA
    #undef PORT_START_SEC_CONFIG_DATA
    #define ENTERED_PORT_START_SEC_CONFIG_DATA
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_CONFIG_DATA
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #ifdef __clang__
            #pragma clang section bss="" data="" rodata=".rodata"
        #else
            #pragma section CONST ".rodata"
        #endif
#endif

#ifdef PORT_STOP_SEC_CONFIG_DATA
    #ifdef ENTERED_PORT_START_SEC_CONFIG_DATA
        #undef ENTERED_PORT_START_SEC_CONFIG_DATA
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_CONFIG_DATA
    #undef MEM_ERROR
        #ifdef __clang__
            #pragma clang section bss="" data="" rodata=""
        #else
            #pragma section CONST
        #endif
#endif

/**
* MCAL MemMap defined, Used for code data,
* Used START_SEC_CODE must match with STOP_SEC_CODE 
*/
#ifdef PORT_START_SEC_CODE
    #undef PORT_START_SEC_CODE
    #define ENTERED_PORT_START_SEC_CODE
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_CODE
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #ifdef __clang__
            #pragma clang section bss="" data="" rodata="" text=".text"
        #else
            /* no definition -> default compiler settings are used */
        #endif
#endif

#ifdef PORT_STOP_SEC_CODE
    #ifdef ENTERED_PORT_START_SEC_CODE
        #undef ENTERED_PORT_START_SEC_CODE
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_CODE
    #undef MEM_ERROR
        #ifdef __clang__
            #pragma clang section bss="" data="" rodata="" text=""
        #else
            /* no definition -> default compiler settings are used */
        #endif
#endif

/**
* MCAL MemMap defined, Used for noinit(bss) data,
* Used START_SEC_VAR_NO_INIT must match with STOP_SEC_VAR_NO_INIT 
*/
#ifdef PORT_START_SEC_VAR_NO_INIT
    #undef PORT_START_SEC_VAR_NO_INIT
    #define ENTERED_PORT_START_SEC_VAR_NO_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_NO_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #ifdef __clang__
                #pragma clang section bss=".bss" data=".data" rodata=""
            #else
                #pragma section DATA ".data" ".bss"
            #endif
#endif

#ifdef PORT_STOP_SEC_VAR_NO_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_NO_INIT
        #undef ENTERED_PORT_START_SEC_VAR_NO_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_NO_INIT
    #undef MEM_ERROR
        #ifdef __clang__
        #pragma clang section bss="" data="" rodata=""
    #else
        #pragma section DATA
    #endif
#endif

/**
* MCAL MemMap defined, Used for global init data,
* Used START_SEC_VAR_INIT must match with STOP_SEC_VAR_INIT 
*/
#ifdef PORT_START_SEC_VAR_INIT
    #undef PORT_START_SEC_VAR_INIT
    #define ENTERED_PORT_START_SEC_VAR_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #ifdef __clang__
            #pragma clang section bss=".bss" data=".data" rodata=""
        #else
            #pragma section DATA ".data" ".bss"
        #endif
#endif

#ifdef PORT_STOP_SEC_VAR_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_INIT
        #undef ENTERED_PORT_START_SEC_VAR_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_INIT
    #undef MEM_ERROR
        #ifdef __clang__
            #pragma clang section bss="" data="" rodata=""
        #else
            #pragma section DATA
        #endif
#endif

/**
* MCAL MemMap defined, Used for share init data,
* Used START_SEC_VAR_SHARED_INIT must match with STOP_SEC_VAR_SHARED_INIT 
*/
#ifdef PORT_START_SEC_VAR_SHARED_INIT
    #undef PORT_START_SEC_VAR_SHARED_INIT
    #define ENTERED_PORT_START_SEC_VAR_SHARED_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_SHARED_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #ifdef __clang__
            #pragma clang section bss="data_share" data=".data_share" rodata=""
        #else
            #pragma section DATA ".data_share" ".data_share"
        #endif
#endif

#ifdef PORT_STOP_SEC_VAR_SHARED_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_SHARED_INIT
        #undef ENTERED_PORT_START_SEC_VAR_SHARED_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_SHARED_INIT
    #undef MEM_ERROR
        #ifdef __clang__
            #pragma clang section bss="" data="" rodata=""
        #else
            #pragma section DATA
        #endif
#endif

/**
* MCAL MemMap defined, Used for share zero data,
* Used START_SEC_VAR_SHARED_NO_INIT must match with STOP_SEC_VAR_SHARED_NO_INIT 
*/
#ifdef PORT_START_SEC_VAR_SHARED_NO_INIT
    #undef PORT_START_SEC_VAR_SHARED_NO_INIT
    #define ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifdef PORT_STOP_SEC_VAR_SHARED_NO_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #ifdef __clang__
            #pragma clang section bss="data_share" data=".data_share" rodata=""
        #else
            #pragma section DATA ".data_share" ".data_share"
        #endif
#endif

#ifdef PORT_STOP_SEC_VAR_SHARED_NO_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
        #undef ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_SHARED_NO_INIT
    #undef MEM_ERROR
        #ifdef __clang__
            #pragma clang section bss="" data="" rodata=""
        #else
            #pragma section DATA
        #endif
#endif

/**
* MCAL MemMap defined, Used for code running in ram,
* Used START_SEC_RAMCODE must match with STOP_SEC_RAMCODE 
*/
#ifdef PORT_START_SEC_RAMCODE
    #undef PORT_START_SEC_RAMCODE
    #define ENTERED_PORT_START_SEC_RAMCODE
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifdef PORT_STOP_SEC_RAMCODE
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #ifdef __clang__
            #pragma clang section bss="" data="" rodata="" text=".data.code"
        #else
            #pragma section CODE ".data.code" far-absolute
        #endif
#endif

#ifdef PORT_STOP_SEC_RAMCODE
    #ifdef ENTERED_PORT_START_SEC_RAMCODE
        #undef ENTERED_PORT_START_SEC_RAMCODE
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_RAMCODE
    #undef MEM_ERROR
        #ifdef __clang__
            #pragma clang section bss="" data="" rodata="" text=""-n        #else
            #pragma section CODE
        #endif
#endif

#endif /* DCC_C_CCFC30XX */

/*************************************************************************************************/
/*                                       CODEWARRIOR                                             */
/*************************************************************************************************/
#ifdef MWERKS_C_CCFC30XX
/**
* MCAL MemMap defined, Used for configure data,
* Used START_SEC_CONFIG_DATA must match with STOP_SEC_CONFIG_DATA 
*/
#ifdef PORT_START_SEC_CONFIG_DATA
    #undef PORT_START_SEC_CONFIG_DATA
    #define ENTERED_PORT_START_SEC_CONFIG_DATA
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_CONFIG_DATA
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma CONST_SEG rodata
#endif

#ifdef PORT_STOP_SEC_CONFIG_DATA
    #ifdef ENTERED_PORT_START_SEC_CONFIG_DATA
        #undef ENTERED_PORT_START_SEC_CONFIG_DATA
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_CONFIG_DATA
    #undef MEM_ERROR
        #pragma CONST_SEG DEFAULT
#endif

/**
* MCAL MemMap defined, Used for code data,
* Used START_SEC_CODE must match with STOP_SEC_CODE 
*/
#ifdef PORT_START_SEC_CODE
    #undef PORT_START_SEC_CODE
    #define ENTERED_PORT_START_SEC_CODE
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_CODE
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma CODE_SEG text
#endif

#ifdef PORT_STOP_SEC_CODE
    #ifdef ENTERED_PORT_START_SEC_CODE
        #undef ENTERED_PORT_START_SEC_CODE
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_CODE
    #undef MEM_ERROR
        #pragma CODE_SEG DEFAULT
#endif

/**
* MCAL MemMap defined, Used for noinit(bss) data,
* Used START_SEC_VAR_NO_INIT must match with STOP_SEC_VAR_NO_INIT 
*/
#ifdef PORT_START_SEC_VAR_NO_INIT
    #undef PORT_START_SEC_VAR_NO_INIT
    #define ENTERED_PORT_START_SEC_VAR_NO_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_NO_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma DATA_SEG bss
#endif

#ifdef PORT_STOP_SEC_VAR_NO_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_NO_INIT
        #undef ENTERED_PORT_START_SEC_VAR_NO_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_NO_INIT
    #undef MEM_ERROR
        #pragma DATA_SEG DEFAULT
#endif

/**
* MCAL MemMap defined, Used for global init data,
* Used START_SEC_VAR_INIT must match with STOP_SEC_VAR_INIT 
*/
#ifdef PORT_START_SEC_VAR_INIT
    #undef PORT_START_SEC_VAR_INIT
    #define ENTERED_PORT_START_SEC_VAR_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma DATA_SEG data
#endif

#ifdef PORT_STOP_SEC_VAR_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_INIT
        #undef ENTERED_PORT_START_SEC_VAR_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_INIT
    #undef MEM_ERROR
        #pragma DATA_SEG DEFAULT
#endif

/**
* MCAL MemMap defined, Used for share init data,
* Used START_SEC_VAR_SHARED_INIT must match with STOP_SEC_VAR_SHARED_INIT 
*/
#ifdef PORT_START_SEC_VAR_SHARED_INIT
    #undef PORT_START_SEC_VAR_SHARED_INIT
    #define ENTERED_PORT_START_SEC_VAR_SHARED_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_SHARED_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma DATA_SEG .data_share
#endif

#ifdef PORT_STOP_SEC_VAR_SHARED_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_SHARED_INIT
        #undef ENTERED_PORT_START_SEC_VAR_SHARED_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_SHARED_INIT
    #undef MEM_ERROR
        #pragma DATA_SEG DEFAULT
#endif

/**
* MCAL MemMap defined, Used for share zero data,
* Used START_SEC_VAR_SHARED_NO_INIT must match with STOP_SEC_VAR_SHARED_NO_INIT 
*/
#ifdef PORT_START_SEC_VAR_SHARED_NO_INIT
    #undef PORT_START_SEC_VAR_SHARED_NO_INIT
    #define ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifdef PORT_STOP_SEC_VAR_SHARED_NO_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma DATA_SEG .data_share
#endif

#ifdef PORT_STOP_SEC_VAR_SHARED_NO_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
        #undef ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_SHARED_NO_INIT
    #undef MEM_ERROR
        #pragma DATA_SEG DEFAULT
#endif

/**
* MCAL MemMap defined, Used for code running in ram,
* Used START_SEC_RAMCODE must match with STOP_SEC_RAMCODE 
*/
#ifdef PORT_START_SEC_RAMCODE
    #undef PORT_START_SEC_RAMCODE
    #define ENTERED_PORT_START_SEC_RAMCODE
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifdef PORT_STOP_SEC_RAMCODE
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma CODE_SEG data.code
#endif

#ifdef PORT_STOP_SEC_RAMCODE
    #ifdef ENTERED_PORT_START_SEC_RAMCODE
        #undef ENTERED_PORT_START_SEC_RAMCODE
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_RAMCODE
    #undef MEM_ERROR
        #pragma CODE_SEG DEFAULT
#endif

#endif /* MWERKS_C_CCFC30XX */

/*************************************************************************************************/
/*                                         COSMIC                                                */
/*************************************************************************************************/
#ifdef CSMC_C_CCFC30XX
/**
* MCAL MemMap defined, Used for configure data,
* Used START_SEC_CONFIG_DATA must match with STOP_SEC_CONFIG_DATA 
*/
#ifdef PORT_START_SEC_CONFIG_DATA
    #undef PORT_START_SEC_CONFIG_DATA
    #define ENTERED_PORT_START_SEC_CONFIG_DATA
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_CONFIG_DATA
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma section const {rodata}
#endif

#ifdef PORT_STOP_SEC_CONFIG_DATA
    #ifdef ENTERED_PORT_START_SEC_CONFIG_DATA
        #undef ENTERED_PORT_START_SEC_CONFIG_DATA
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_CONFIG_DATA
    #undef MEM_ERROR
        #pragma section const {}
#endif

/**
* MCAL MemMap defined, Used for code data,
* Used START_SEC_CODE must match with STOP_SEC_CODE 
*/
#ifdef PORT_START_SEC_CODE
    #undef PORT_START_SEC_CODE
    #define ENTERED_PORT_START_SEC_CODE
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_CODE
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma section (text)
#endif

#ifdef PORT_STOP_SEC_CODE
    #ifdef ENTERED_PORT_START_SEC_CODE
        #undef ENTERED_PORT_START_SEC_CODE
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_CODE
    #undef MEM_ERROR
        #pragma section ()
#endif

/**
* MCAL MemMap defined, Used for noinit(bss) data,
* Used START_SEC_VAR_NO_INIT must match with STOP_SEC_VAR_NO_INIT 
*/
#ifdef PORT_START_SEC_VAR_NO_INIT
    #undef PORT_START_SEC_VAR_NO_INIT
    #define ENTERED_PORT_START_SEC_VAR_NO_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_NO_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma section [bss]
#endif

#ifdef PORT_STOP_SEC_VAR_NO_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_NO_INIT
        #undef ENTERED_PORT_START_SEC_VAR_NO_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_NO_INIT
    #undef MEM_ERROR
        #pragma section []
#endif

/**
* MCAL MemMap defined, Used for global init data,
* Used START_SEC_VAR_INIT must match with STOP_SEC_VAR_INIT 
*/
#ifdef PORT_START_SEC_VAR_INIT
    #undef PORT_START_SEC_VAR_INIT
    #define ENTERED_PORT_START_SEC_VAR_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma section {data}
#endif

#ifdef PORT_STOP_SEC_VAR_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_INIT
        #undef ENTERED_PORT_START_SEC_VAR_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_INIT
    #undef MEM_ERROR
        #pragma section {}
#endif

/**
* MCAL MemMap defined, Used for share init data,
* Used START_SEC_VAR_SHARED_INIT must match with STOP_SEC_VAR_SHARED_INIT 
*/
#ifdef PORT_START_SEC_VAR_SHARED_INIT
    #undef PORT_START_SEC_VAR_SHARED_INIT
    #define ENTERED_PORT_START_SEC_VAR_SHARED_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_SHARED_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma section {.data_share}
#endif

#ifdef PORT_STOP_SEC_VAR_SHARED_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_SHARED_INIT
        #undef ENTERED_PORT_START_SEC_VAR_SHARED_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_SHARED_INIT
    #undef MEM_ERROR
        #pragma section {}
#endif

/**
* MCAL MemMap defined, Used for share zero data,
* Used START_SEC_VAR_SHARED_NO_INIT must match with STOP_SEC_VAR_SHARED_NO_INIT 
*/
#ifdef PORT_START_SEC_VAR_SHARED_NO_INIT
    #undef PORT_START_SEC_VAR_SHARED_NO_INIT
    #define ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifdef PORT_STOP_SEC_VAR_SHARED_NO_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma section {.data_share}
#endif

#ifdef PORT_STOP_SEC_VAR_SHARED_NO_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
        #undef ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_SHARED_NO_INIT
    #undef MEM_ERROR
        #pragma section {}
#endif

/**
* MCAL MemMap defined, Used for code running in ram,
* Used START_SEC_RAMCODE must match with STOP_SEC_RAMCODE 
*/
#ifdef PORT_START_SEC_RAMCODE
    #undef PORT_START_SEC_RAMCODE
    #define ENTERED_PORT_START_SEC_RAMCODE
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifdef PORT_STOP_SEC_RAMCODE
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma section (data.code)
#endif

#ifdef PORT_STOP_SEC_RAMCODE
    #ifdef ENTERED_PORT_START_SEC_RAMCODE
        #undef ENTERED_PORT_START_SEC_RAMCODE
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_RAMCODE
    #undef MEM_ERROR
        #pragma section ()
#endif

#endif /* CSMC_C_CCFC30XX */

/*************************************************************************************************/
/*                                        HighTec                                                */
/*************************************************************************************************/
#ifdef HITECH_C_CCFC30XX
/**
* MCAL MemMap defined, Used for configure data,
* Used START_SEC_CONFIG_DATA must match with STOP_SEC_CONFIG_DATA 
*/
#ifdef PORT_START_SEC_CONFIG_DATA
    #undef PORT_START_SEC_CONFIG_DATA
    #define ENTERED_PORT_START_SEC_CONFIG_DATA
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_CONFIG_DATA
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma section ".rodata" a
#endif

#ifdef PORT_STOP_SEC_CONFIG_DATA
    #ifdef ENTERED_PORT_START_SEC_CONFIG_DATA
        #undef ENTERED_PORT_START_SEC_CONFIG_DATA
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_CONFIG_DATA
    #undef MEM_ERROR
        #pragma section
#endif

/**
* MCAL MemMap defined, Used for code data,
* Used START_SEC_CODE must match with STOP_SEC_CODE 
*/
#ifdef PORT_START_SEC_CODE
    #undef PORT_START_SEC_CODE
    #define ENTERED_PORT_START_SEC_CODE
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_CODE
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma section ".text" avx
#endif

#ifdef PORT_STOP_SEC_CODE
    #ifdef ENTERED_PORT_START_SEC_CODE
        #undef ENTERED_PORT_START_SEC_CODE
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_CODE
    #undef MEM_ERROR
        #pragma section
#endif

/**
* MCAL MemMap defined, Used for noinit(bss) data,
* Used START_SEC_VAR_NO_INIT must match with STOP_SEC_VAR_NO_INIT 
*/
#ifdef PORT_START_SEC_VAR_NO_INIT
    #undef PORT_START_SEC_VAR_NO_INIT
    #define ENTERED_PORT_START_SEC_VAR_NO_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_NO_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma section ".bss"
#endif

#ifdef PORT_STOP_SEC_VAR_NO_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_NO_INIT
        #undef ENTERED_PORT_START_SEC_VAR_NO_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_NO_INIT
    #undef MEM_ERROR
        #pragma section
#endif

/**
* MCAL MemMap defined, Used for global init data,
* Used START_SEC_VAR_INIT must match with STOP_SEC_VAR_INIT 
*/
#ifdef PORT_START_SEC_VAR_INIT
    #undef PORT_START_SEC_VAR_INIT
    #define ENTERED_PORT_START_SEC_VAR_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma section ".data"
#endif

#ifdef PORT_STOP_SEC_VAR_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_INIT
        #undef ENTERED_PORT_START_SEC_VAR_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_INIT
    #undef MEM_ERROR
        #pragma section
#endif

/**
* MCAL MemMap defined, Used for share init data,
* Used START_SEC_VAR_SHARED_INIT must match with STOP_SEC_VAR_SHARED_INIT 
*/
#ifdef PORT_START_SEC_VAR_SHARED_INIT
    #undef PORT_START_SEC_VAR_SHARED_INIT
    #define ENTERED_PORT_START_SEC_VAR_SHARED_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_SHARED_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma section ".data_share"
#endif

#ifdef PORT_STOP_SEC_VAR_SHARED_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_SHARED_INIT
        #undef ENTERED_PORT_START_SEC_VAR_SHARED_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_SHARED_INIT
    #undef MEM_ERROR
        #pragma section
#endif

/**
* MCAL MemMap defined, Used for share zero data,
* Used START_SEC_VAR_SHARED_NO_INIT must match with STOP_SEC_VAR_SHARED_NO_INIT 
*/
#ifdef PORT_START_SEC_VAR_SHARED_NO_INIT
    #undef PORT_START_SEC_VAR_SHARED_NO_INIT
    #define ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifdef PORT_STOP_SEC_VAR_SHARED_NO_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma section ".data_share"
#endif

#ifdef PORT_STOP_SEC_VAR_SHARED_NO_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
        #undef ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_SHARED_NO_INIT
    #undef MEM_ERROR
        #pragma section
#endif

/**
* MCAL MemMap defined, Used for code running in ram,
* Used START_SEC_RAMCODE must match with STOP_SEC_RAMCODE 
*/
#ifdef PORT_START_SEC_RAMCODE
    #undef PORT_START_SEC_RAMCODE
    #define ENTERED_PORT_START_SEC_RAMCODE
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifdef PORT_STOP_SEC_RAMCODE
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma section ".data.code" avx
#endif

#ifdef PORT_STOP_SEC_RAMCODE
    #ifdef ENTERED_PORT_START_SEC_RAMCODE
        #undef ENTERED_PORT_START_SEC_RAMCODE
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_RAMCODE
    #undef MEM_ERROR
        #pragma  section
#endif

#endif /* HITECH_C_CCFC30XX */

/*************************************************************************************************/
/*                                         Linaro                                                */
/*************************************************************************************************/
#ifdef LINARO_C_CCFC30XX
/**
* MCAL MemMap defined, Used for configure data,
* Used START_SEC_CONFIG_DATA must match with STOP_SEC_CONFIG_DATA 
*/
#ifdef PORT_START_SEC_CONFIG_DATA
    #undef PORT_START_SEC_CONFIG_DATA
    #define ENTERED_PORT_START_SEC_CONFIG_DATA
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_CONFIG_DATA
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma GCC section rodata ".rodata"
#endif

#ifdef PORT_STOP_SEC_CONFIG_DATA
    #ifdef ENTERED_PORT_START_SEC_CONFIG_DATA
        #undef ENTERED_PORT_START_SEC_CONFIG_DATA
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_CONFIG_DATA
    #undef MEM_ERROR
        #pragma GCC section rodata
#endif

/**
* MCAL MemMap defined, Used for code data,
* Used START_SEC_CODE must match with STOP_SEC_CODE 
*/
#ifdef PORT_START_SEC_CODE
    #undef PORT_START_SEC_CODE
    #define ENTERED_PORT_START_SEC_CODE
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_CODE
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma GCC section text ".text"
#endif

#ifdef PORT_STOP_SEC_CODE
    #ifdef ENTERED_PORT_START_SEC_CODE
        #undef ENTERED_PORT_START_SEC_CODE
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_CODE
    #undef MEM_ERROR
        #pragma GCC section text
#endif

/**
* MCAL MemMap defined, Used for noinit(bss) data,
* Used START_SEC_VAR_NO_INIT must match with STOP_SEC_VAR_NO_INIT 
*/
#ifdef PORT_START_SEC_VAR_NO_INIT
    #undef PORT_START_SEC_VAR_NO_INIT
    #define ENTERED_PORT_START_SEC_VAR_NO_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_NO_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma GCC section bss ".bss"
#endif

#ifdef PORT_STOP_SEC_VAR_NO_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_NO_INIT
        #undef ENTERED_PORT_START_SEC_VAR_NO_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_NO_INIT
    #undef MEM_ERROR
        #pragma GCC section bss
#endif

/**
* MCAL MemMap defined, Used for global init data,
* Used START_SEC_VAR_INIT must match with STOP_SEC_VAR_INIT 
*/
#ifdef PORT_START_SEC_VAR_INIT
    #undef PORT_START_SEC_VAR_INIT
    #define ENTERED_PORT_START_SEC_VAR_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma GCC section data ".data"
#endif

#ifdef PORT_STOP_SEC_VAR_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_INIT
        #undef ENTERED_PORT_START_SEC_VAR_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_INIT
    #undef MEM_ERROR
        #pragma GCC section data
#endif

/**
* MCAL MemMap defined, Used for share init data,
* Used START_SEC_VAR_SHARED_INIT must match with STOP_SEC_VAR_SHARED_INIT 
*/
#ifdef PORT_START_SEC_VAR_SHARED_INIT
    #undef PORT_START_SEC_VAR_SHARED_INIT
    #define ENTERED_PORT_START_SEC_VAR_SHARED_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_SHARED_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma GCC section data ".data_share"
#endif

#ifdef PORT_STOP_SEC_VAR_SHARED_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_SHARED_INIT
        #undef ENTERED_PORT_START_SEC_VAR_SHARED_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_SHARED_INIT
    #undef MEM_ERROR
        #pragma GCC section data
#endif

/**
* MCAL MemMap defined, Used for share zero data,
* Used START_SEC_VAR_SHARED_NO_INIT must match with STOP_SEC_VAR_SHARED_NO_INIT 
*/
#ifdef PORT_START_SEC_VAR_SHARED_NO_INIT
    #undef PORT_START_SEC_VAR_SHARED_NO_INIT
    #define ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifdef PORT_STOP_SEC_VAR_SHARED_NO_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma GCC section data ".data_share"
#endif

#ifdef PORT_STOP_SEC_VAR_SHARED_NO_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
        #undef ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_SHARED_NO_INIT
    #undef MEM_ERROR
        #pragma GCC section data
#endif

/**
* MCAL MemMap defined, Used for code running in ram,
* Used START_SEC_RAMCODE must match with STOP_SEC_RAMCODE 
*/
#ifdef PORT_START_SEC_RAMCODE
    #undef PORT_START_SEC_RAMCODE
    #define ENTERED_PORT_START_SEC_RAMCODE
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifdef PORT_STOP_SEC_RAMCODE
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma GCC section text ".data.code" 
#endif

#ifdef PORT_STOP_SEC_RAMCODE
    #ifdef ENTERED_PORT_START_SEC_RAMCODE
        #undef ENTERED_PORT_START_SEC_RAMCODE
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_RAMCODE
    #undef MEM_ERROR
        #pragma GCC section text
#endif

#endif /* LINARO_C_CCFC30XX */

/*************************************************************************************************/
/*                                          DS5                                                  */
/*************************************************************************************************/
#ifdef DS5_C_CCFC30XX
/**
* MCAL MemMap defined, Used for configure data,
* Used START_SEC_CONFIG_DATA must match with STOP_SEC_CONFIG_DATA 
*/
#ifdef PORT_START_SEC_CONFIG_DATA
    #undef PORT_START_SEC_CONFIG_DATA
    #define ENTERED_PORT_START_SEC_CONFIG_DATA
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_CONFIG_DATA
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma arm section rodata=".rodata"
#endif

#ifdef PORT_STOP_SEC_CONFIG_DATA
    #ifdef ENTERED_PORT_START_SEC_CONFIG_DATA
        #undef ENTERED_PORT_START_SEC_CONFIG_DATA
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_CONFIG_DATA
    #undef MEM_ERROR
        /* no definition -> default compiler settings are used */
#endif

/**
* MCAL MemMap defined, Used for code data,
* Used START_SEC_CODE must match with STOP_SEC_CODE 
*/
#ifdef PORT_START_SEC_CODE
    #undef PORT_START_SEC_CODE
    #define ENTERED_PORT_START_SEC_CODE
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_CODE
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma arm section code=".text"
#endif

#ifdef PORT_STOP_SEC_CODE
    #ifdef ENTERED_PORT_START_SEC_CODE
        #undef ENTERED_PORT_START_SEC_CODE
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_CODE
    #undef MEM_ERROR
        /* no definition -> default compiler settings are used */
#endif

/**
* MCAL MemMap defined, Used for noinit(bss) data,
* Used START_SEC_VAR_NO_INIT must match with STOP_SEC_VAR_NO_INIT 
*/
#ifdef PORT_START_SEC_VAR_NO_INIT
    #undef PORT_START_SEC_VAR_NO_INIT
    #define ENTERED_PORT_START_SEC_VAR_NO_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_NO_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma arm section zidata=".bss"
#endif

#ifdef PORT_STOP_SEC_VAR_NO_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_NO_INIT
        #undef ENTERED_PORT_START_SEC_VAR_NO_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_NO_INIT
    #undef MEM_ERROR
        /* no definition -> default compiler settings are used */
#endif

/**
* MCAL MemMap defined, Used for global init data,
* Used START_SEC_VAR_INIT must match with STOP_SEC_VAR_INIT 
*/
#ifdef PORT_START_SEC_VAR_INIT
    #undef PORT_START_SEC_VAR_INIT
    #define ENTERED_PORT_START_SEC_VAR_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma arm section rwdata=".data"
#endif

#ifdef PORT_STOP_SEC_VAR_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_INIT
        #undef ENTERED_PORT_START_SEC_VAR_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_INIT
    #undef MEM_ERROR
        /* no definition -> default compiler settings are used */
#endif

/**
* MCAL MemMap defined, Used for share init data,
* Used START_SEC_VAR_SHARED_INIT must match with STOP_SEC_VAR_SHARED_INIT 
*/
#ifdef PORT_START_SEC_VAR_SHARED_INIT
    #undef PORT_START_SEC_VAR_SHARED_INIT
    #define ENTERED_PORT_START_SEC_VAR_SHARED_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_SHARED_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma arm section rwdata=".data_share"
#endif

#ifdef PORT_STOP_SEC_VAR_SHARED_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_SHARED_INIT
        #undef ENTERED_PORT_START_SEC_VAR_SHARED_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_SHARED_INIT
    #undef MEM_ERROR
        /* no definition -> default compiler settings are used */
#endif

/**
* MCAL MemMap defined, Used for share zero data,
* Used START_SEC_VAR_SHARED_NO_INIT must match with STOP_SEC_VAR_SHARED_NO_INIT 
*/
#ifdef PORT_START_SEC_VAR_SHARED_NO_INIT
    #undef PORT_START_SEC_VAR_SHARED_NO_INIT
    #define ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifdef PORT_STOP_SEC_VAR_SHARED_NO_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma arm section rwdata=".data_share"
#endif

#ifdef PORT_STOP_SEC_VAR_SHARED_NO_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
        #undef ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_SHARED_NO_INIT
    #undef MEM_ERROR
        /* no definition -> default compiler settings are used */
#endif

/**
* MCAL MemMap defined, Used for code running in ram,
* Used START_SEC_RAMCODE must match with STOP_SEC_RAMCODE 
*/
#ifdef PORT_START_SEC_RAMCODE
    #undef PORT_START_SEC_RAMCODE
    #define ENTERED_PORT_START_SEC_RAMCODE
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifdef PORT_STOP_SEC_RAMCODE
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma arm section code=".data.code"
#endif

#ifdef PORT_STOP_SEC_RAMCODE
    #ifdef ENTERED_PORT_START_SEC_RAMCODE
        #undef ENTERED_PORT_START_SEC_RAMCODE
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_RAMCODE
    #undef MEM_ERROR
        /* no definition -> default compiler settings are used */
#endif

#endif /* DS5_C_CCFC30XX */

/*************************************************************************************************/
/*                                          IAR                                                  */
/*************************************************************************************************/
#ifdef IAR_C_CCFC30XX
/**
* MCAL MemMap defined, Used for configure data,
* Used START_SEC_CONFIG_DATA must match with STOP_SEC_CONFIG_DATA 
*/
#ifdef PORT_START_SEC_CONFIG_DATA
    #undef PORT_START_SEC_CONFIG_DATA
    #define ENTERED_PORT_START_SEC_CONFIG_DATA
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_CONFIG_DATA
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma default_variable_attributes = @ ".rodata"
#endif

#ifdef PORT_STOP_SEC_CONFIG_DATA
    #ifdef ENTERED_PORT_START_SEC_CONFIG_DATA
        #undef ENTERED_PORT_START_SEC_CONFIG_DATA
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_CONFIG_DATA
    #undef MEM_ERROR
        #pragma default_variable_attributes = 
#endif

/**
* MCAL MemMap defined, Used for code data,
* Used START_SEC_CODE must match with STOP_SEC_CODE 
*/
#ifdef PORT_START_SEC_CODE
    #undef PORT_START_SEC_CODE
    #define ENTERED_PORT_START_SEC_CODE
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_CODE
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma default_function_attributes = @ ".text"
#endif

#ifdef PORT_STOP_SEC_CODE
    #ifdef ENTERED_PORT_START_SEC_CODE
        #undef ENTERED_PORT_START_SEC_CODE
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_CODE
    #undef MEM_ERROR
        #pragma default_function_attributes =
#endif

/**
* MCAL MemMap defined, Used for noinit(bss) data,
* Used START_SEC_VAR_NO_INIT must match with STOP_SEC_VAR_NO_INIT 
*/
#ifdef PORT_START_SEC_VAR_NO_INIT
    #undef PORT_START_SEC_VAR_NO_INIT
    #define ENTERED_PORT_START_SEC_VAR_NO_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_NO_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma default_variable_attributes = @ ".bss"
#endif

#ifdef PORT_STOP_SEC_VAR_NO_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_NO_INIT
        #undef ENTERED_PORT_START_SEC_VAR_NO_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_NO_INIT
    #undef MEM_ERROR
        #pragma default_variable_attributes =
#endif

/**
* MCAL MemMap defined, Used for global init data,
* Used START_SEC_VAR_INIT must match with STOP_SEC_VAR_INIT 
*/
#ifdef PORT_START_SEC_VAR_INIT
    #undef PORT_START_SEC_VAR_INIT
    #define ENTERED_PORT_START_SEC_VAR_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma default_variable_attributes = @ ".data"
#endif

#ifdef PORT_STOP_SEC_VAR_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_INIT
        #undef ENTERED_PORT_START_SEC_VAR_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_INIT
    #undef MEM_ERROR
        #pragma default_variable_attributes =
#endif

/**
* MCAL MemMap defined, Used for share init data,
* Used START_SEC_VAR_SHARED_INIT must match with STOP_SEC_VAR_SHARED_INIT 
*/
#ifdef PORT_START_SEC_VAR_SHARED_INIT
    #undef PORT_START_SEC_VAR_SHARED_INIT
    #define ENTERED_PORT_START_SEC_VAR_SHARED_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef PORT_STOP_SEC_VAR_SHARED_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma default_variable_attributes = @ ".data_share"
#endif

#ifdef PORT_STOP_SEC_VAR_SHARED_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_SHARED_INIT
        #undef ENTERED_PORT_START_SEC_VAR_SHARED_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_SHARED_INIT
    #undef MEM_ERROR
        #pragma default_variable_attributes =
#endif

/**
* MCAL MemMap defined, Used for share zero data,
* Used START_SEC_VAR_SHARED_NO_INIT must match with STOP_SEC_VAR_SHARED_NO_INIT 
*/
#ifdef PORT_START_SEC_VAR_SHARED_NO_INIT
    #undef PORT_START_SEC_VAR_SHARED_NO_INIT
    #define ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifdef PORT_STOP_SEC_VAR_SHARED_NO_INIT
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma default_variable_attributes = @ ".data_share"
#endif

#ifdef PORT_STOP_SEC_VAR_SHARED_NO_INIT
    #ifdef ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
        #undef ENTERED_PORT_START_SEC_VAR_SHARED_NO_INIT
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_VAR_SHARED_NO_INIT
    #undef MEM_ERROR
        #pragma default_variable_attributes =
#endif

/**
* MCAL MemMap defined, Used for code running in ram,
* Used START_SEC_RAMCODE must match with STOP_SEC_RAMCODE 
*/
#ifdef PORT_START_SEC_RAMCODE
    #undef PORT_START_SEC_RAMCODE
    #define ENTERED_PORT_START_SEC_RAMCODE
    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifdef PORT_STOP_SEC_RAMCODE
            #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
        #endif
    #endif
    #undef MEM_ERROR
        #pragma default_function_attributes = @ ".data.code"
#endif

#ifdef PORT_STOP_SEC_RAMCODE
    #ifdef ENTERED_PORT_START_SEC_RAMCODE
        #undef ENTERED_PORT_START_SEC_RAMCODE
    #else
        #error PORT_MEMMAP_SECTION_NOTMATCH_ERROR
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef PORT_STOP_SEC_RAMCODE
    #undef MEM_ERROR
        #pragma default_function_attributes =
#endif

#endif /* IAR_C_CCFC30XX */

#ifdef MEM_ERROR
    #error "Port_MemMap.h, no valid memory mapping symbol defined."
#endif
        
/*====================================================================================================
                                         DISABLE WARNING END
====================================================================================================*/
#ifdef GHS_C_CCFC30XX
#pragma ghs  endnowarning 1512
#endif

#ifdef __cplusplus
}
#endif

