/******************************************************************************
*
*   Copyright 2013-2015 Freescale Semiconductor
*   Copyright 2016-2023 NXP
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms.  By expressly accepting such
*   terms or by downloading, installing, activating and/or otherwise using the software, you are
*   agreeing that you have read, and that you agree to comply with and are bound by, such license
*   terms. If you do not agree to be bound by the applicable license terms, then you may not retain,
*   install, activate or otherwise use the software.
*
******************************************************************************/
/**
*
* @file       GMCLIB_SvmStd.h
*
* @brief      Header file for GMCLIB_SvmStd function
*
******************************************************************************/
#ifndef GMCLIB_SVMSTD_H
#define GMCLIB_SVMSTD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "SWLIBS_Typedefs.h"
#include "SWLIBS_Defines.h"
#include "SWLIBS_MacroDisp.h"
#include "mlib.h"

/****************************************************************************
* Defines and macros            (scope: module-local)
****************************************************************************/
#if (!(defined(__MINGW32__) || defined(__MINGW64__) || defined(_MSC_VER) || defined(_MATLAB_BAM_CREATE)))
  #define GMCLIB_SvmStd(...)     macro_dispatcher(GMCLIB_SvmStd, __VA_ARGS__)(__VA_ARGS__)     /* This function calculates the duty-cycle ratios using the Standard Space Vector Modulation technique. */

  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_F32)
    /* @remarks Implements DGMCLIB00074 */
    #define GMCLIB_SvmStd_Dsptchr_2(pOut,pIn)     GMCLIB_SvmStd_Dsptchr_3(pOut,pIn,F32)     /* Function dispatcher for GMCLIB_SvmStd_Dsptchr_2, do not modify!!! */
  #endif 
  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_F16)
    /* @remarks Implements DGMCLIB00074 */
    #define GMCLIB_SvmStd_Dsptchr_2(pOut,pIn)     GMCLIB_SvmStd_Dsptchr_3(pOut,pIn,F16)     /* Function dispatcher for GMCLIB_SvmStd_Dsptchr_2, do not modify!!! */
  #endif 
  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_FLT)
    /* @remarks Implements DGMCLIB00074 */
    #define GMCLIB_SvmStd_Dsptchr_2(pOut,pIn)     GMCLIB_SvmStd_Dsptchr_3(pOut,pIn,FLT)     /* Function dispatcher for GMCLIB_SvmStd_Dsptchr_2, do not modify!!! */
  #endif 

  #define GMCLIB_SvmStd_Dsptchr_3(pOut,pIn,Impl)    GMCLIB_SvmStd_Dsptchr_(pOut,pIn,Impl)     /* Function dispatcher for GMCLIB_SvmStd_Dsptchr_3, do not modify!!! */
  
  /* @remarks Implements DGMCLIB00078 */
  #define GMCLIB_SvmStd_Dsptchr_(pOut,pIn,Impl)     GMCLIB_SvmStd_##Impl(pOut,pIn)            /* Function dispatcher for GMCLIB_SvmStd_Dsptchr_, do not modify!!! */
#endif
 
/****************************************************************************
* Typedefs and structures       (scope: module-local)
****************************************************************************/




/****************************************************************************
* Implementation variant: 32-bit fractional
****************************************************************************/
#if (SWLIBS_SUPPORT_F32 == SWLIBS_STD_ON)

/****************************************************************************
* Exported function prototypes
****************************************************************************/
  extern tU32 GMCLIB_SvmStd_F32(SWLIBS_3Syst_F32 * pOut, const SWLIBS_2Syst_F32 *const pIn);
#endif /* SWLIBS_SUPPORT_F32 == SWLIBS_STD_ON */




/****************************************************************************
* Implementation variant: 16-bit fractional
****************************************************************************/
#if (SWLIBS_SUPPORT_F16 == SWLIBS_STD_ON)

/****************************************************************************
* Exported function prototypes
****************************************************************************/
  extern tU16 GMCLIB_SvmStd_F16(SWLIBS_3Syst_F16 * pOut, const SWLIBS_2Syst_F16 *const pIn);
#endif /* SWLIBS_SUPPORT_F16 == SWLIBS_STD_ON */




/****************************************************************************
* Implementation variant: Single precision floating point
****************************************************************************/
#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)

/****************************************************************************
* Exported function prototypes
****************************************************************************/
  extern tU32 GMCLIB_SvmStd_FLT(SWLIBS_3Syst_FLT * pOut, const SWLIBS_2Syst_FLT *const pIn);
#endif /* SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON */
/****************************************************************************
* Inline functions
****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* GMCLIB_SVMSTD_H */
