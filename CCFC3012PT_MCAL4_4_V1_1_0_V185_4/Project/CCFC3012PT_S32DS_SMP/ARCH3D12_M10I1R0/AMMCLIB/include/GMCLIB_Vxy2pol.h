/******************************************************************************
*
*   Copyright 2020-2023 NXP
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
* @file       GMCLIB_Vxy2pol.h
*
* @brief      Header file for GMCLIB_Vxy2pol function
*
******************************************************************************/
#ifndef GMCLIB_VXY2POL_H
#define GMCLIB_VXY2POL_H
/**
@if GMCLIB_GROUP
    @addtogroup GMCLIB_GROUP
@else
    @defgroup GMCLIB_GROUP   GMCLIB
@endif
*/

#ifdef __cplusplus
extern "C" {
#endif

#include "SWLIBS_Defines.h"

/****************************************************************************
* Defines and macros            (scope: module-local)
****************************************************************************/
#if (!(defined(__MINGW32__) || defined(__MINGW64__) || defined(_MSC_VER) || defined(_MATLAB_BAM_CREATE)))
  #define GMCLIB_Vxy2pol(...)     macro_dispatcher(GMCLIB_Vxy2pol, __VA_ARGS__)(__VA_ARGS__)     /* This function returns sum of two input parameters. */

  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_F32)
    /* @remarks Implements DGMCLIB00187 */
    #define GMCLIB_Vxy2pol_Dsptchr_2(Out,In)     GMCLIB_Vxy2pol_Dsptchr_3(Out,In,F32)       /* Function dispatcher for GMCLIB_Vxy2pol_Dsptchr_2, do not modify!!! */
  #endif
  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_F16)
    /* @remarks Implements DGMCLIB00187 */
    #define GMCLIB_Vxy2pol_Dsptchr_2(Out,In)     GMCLIB_Vxy2pol_Dsptchr_3(Out,In,F16)       /* Function dispatcher for GMCLIB_Vxy2pol_Dsptchr_2, do not modify!!! */
  #endif
#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_FLT)
    /* @remarks Implements DGMCLIB00187 */
    #define GMCLIB_Vxy2pol_Dsptchr_2(Out,In)     GMCLIB_Vxy2pol_Dsptchr_3(Out,In,FLT)       /* Function dispatcher for GMCLIB_Vxy2pol_Dsptchr_2, do not modify!!! */
  #endif
#endif /* SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON */
  #define GMCLIB_Vxy2pol_Dsptchr_3(Out,In,Impl)    GMCLIB_Vxy2pol_Dsptchr_(Out,In,Impl)     /* Function dispatcher for GMCLIB_Vxy2pol_Dsptchr_3, do not modify!!! */
  
  /* @remarks Implements DGMCLIB00189*/
  #define GMCLIB_Vxy2pol_Dsptchr_(Out,In,Impl)     GMCLIB_Vxy2pol_##Impl(Out,In)            /* Function dispatcher for GMCLIB_Vxy2pol_Dsptchr_, do not modify!!! */
#endif

/****************************************************************************
* Typedefs and structures       (scope: module-local)
****************************************************************************/

/****************************************************************************
* Exported function prototypes
****************************************************************************/

/****************************************************************************
* Inline functions
****************************************************************************/


/****************************************************************************
* Implementation variant: 32-bit fractional
****************************************************************************/
#if (SWLIBS_SUPPORT_F32 == SWLIBS_STD_ON)
extern void GMCLIB_Vxy2pol_F32(SWLIBS_2Syst_F32 *const f32OutVec, const SWLIBS_2Syst_F32 *const f32InVec);

#endif /* SWLIBS_SUPPORT_F32 == SWLIBS_STD_ON */
/****************************************************************************
* Implementation variant: 16-bit fractional
****************************************************************************/
#if (SWLIBS_SUPPORT_F16 == SWLIBS_STD_ON)
extern void GMCLIB_Vxy2pol_F16(SWLIBS_2Syst_F16 *const f16OutVec, const SWLIBS_2Syst_F16 *const f16InVec);

#endif /* SWLIBS_SUPPORT_F16 == SWLIBS_STD_ON */
#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
extern void GMCLIB_Vxy2pol_FLT(SWLIBS_2Syst_FLT *const fltOutVec, const SWLIBS_2Syst_FLT *const fltInVec);

#endif /* SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON */
#ifdef __cplusplus
}
#endif

#endif /* GMCLIB_VXY2POL_H */
