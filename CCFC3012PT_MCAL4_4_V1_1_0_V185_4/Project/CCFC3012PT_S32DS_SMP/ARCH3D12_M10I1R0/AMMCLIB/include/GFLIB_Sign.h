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
* @file       GFLIB_Sign.h
*
* @brief      Header file for GFLIB_Sign function
*
******************************************************************************/
#ifndef GFLIB_SIGN_H
#define GFLIB_SIGN_H

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
  #define GFLIB_Sign(...)     macro_dispatcher(GFLIB_Sign, __VA_ARGS__)(__VA_ARGS__)     /* This function returns the signum of input value. */

  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_F32)
    /* @remarks Implements DGFLIB00124 */
    #define GFLIB_Sign_Dsptchr_1(In)     GFLIB_Sign_Dsptchr_2(In,F32)     /* Function dispatcher for GFLIB_Sign_Dsptchr_1, do not modify!!! */
  #endif 
  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_F16)
    /* @remarks Implements DGFLIB00124 */
    #define GFLIB_Sign_Dsptchr_1(In)     GFLIB_Sign_Dsptchr_2(In,F16)     /* Function dispatcher for GFLIB_Sign_Dsptchr_1, do not modify!!! */
  #endif 
  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_FLT)
    /* @remarks Implements DGFLIB00124 */
    #define GFLIB_Sign_Dsptchr_1(In)     GFLIB_Sign_Dsptchr_2(In,FLT)     /* Function dispatcher for GFLIB_Sign_Dsptchr_1, do not modify!!! */
  #endif 

  #define GFLIB_Sign_Dsptchr_2(In,Impl)    GFLIB_Sign_Dsptchr_(In,Impl)   /* Function dispatcher for GFLIB_Sign_Dsptchr_2, do not modify!!! */
  
  /* @remarks Implements DGFLIB00126 */
  #define GFLIB_Sign_Dsptchr_(In,Impl)     GFLIB_Sign_##Impl(In)          /* Function dispatcher for GFLIB_Sign_Dsptchr_, do not modify!!! */
#endif /* if (!(defined(__MINGW32__) || defined(__MINGW64__) || defined(_MSC_VER) || defined(_MATLAB_BAM_CREATE))) */
 
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
  extern tFrac32 GFLIB_Sign_F32(tFrac32 f32In);
#endif /* SWLIBS_SUPPORT_F32 == SWLIBS_STD_ON */




/****************************************************************************
* Implementation variant: 16-bit fractional
****************************************************************************/
#if (SWLIBS_SUPPORT_F16 == SWLIBS_STD_ON)

/****************************************************************************
* Exported function prototypes
****************************************************************************/
  extern tFrac16 GFLIB_Sign_F16(tFrac16 f16In);
#endif /* SWLIBS_SUPPORT_F16 == SWLIBS_STD_ON */




/****************************************************************************
* Implementation variant: Single precision floating point
****************************************************************************/
#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)

/****************************************************************************
* Exported function prototypes
****************************************************************************/
  extern tFloat GFLIB_Sign_FLT(tFloat fltIn);
#endif /* SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON */
/****************************************************************************
* Inline functions
****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* GFLIB_SIGN_H */
