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
* @file       GFLIB_Sin.h
*
* @brief      Header file for GFLIB_Sin function
*
******************************************************************************/
#ifndef GFLIB_SIN_H
#define GFLIB_SIN_H

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
  #define GFLIB_Sin(...)     macro_dispatcher(GFLIB_Sin, __VA_ARGS__)(__VA_ARGS__)     /* This function implements polynomial approximation of sine function. */

  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_F32)
    #define GFLIB_SIN_T                        GFLIB_SIN_T_F32                           /**< Definition of GFLIB_SIN_T as alias for GFLIB_SIN_T_F32 datatype in case the 32-bit fractional implementation is selected. */
    #define GFLIB_SIN_DEFAULT                  GFLIB_SIN_DEFAULT_F32                     /**< Definition of GFLIB_SIN_DEFAULT  as alias for GFLIB_SIN_DEFAULT_F32 default value in case the 32-bit fractional implementation is selected. */
    #define GFLIB_Sin_Dsptchr_2(In,pParam)     GFLIB_Sin_Dsptchr_3(In,pParam,F32)        /* Function dispatcher for GFLIB_Sin_Dsptchr_2, do not modify!!! */
    /* @remarks Implements DGFLIB00009 */
    #define GFLIB_Sin_Dsptchr_1(In)            GFLIB_Sin_Dsptchr_2(In,GFLIB_SIN_DEFAULT) /* Function dispatcher for GFLIB_Sin_Dsptchr_1, do not modify!!! */
  #endif 
  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_F16)
    #define GFLIB_SIN_T                        GFLIB_SIN_T_F16                           /**< Definition of GFLIB_SIN_T as alias for GFLIB_SIN_T_F16 datatype in case the 16-bit fractional implementation is selected. */
    #define GFLIB_SIN_DEFAULT                  GFLIB_SIN_DEFAULT_F16                     /**< Definition of GFLIB_SIN_DEFAULT  as alias for GFLIB_SIN_DEFAULT_F16 default value in case the 16-bit fractional implementation is selected. */
    #define GFLIB_Sin_Dsptchr_2(In,pParam)     GFLIB_Sin_Dsptchr_3(In,pParam,F16)        /* Function dispatcher for GFLIB_Sin_Dsptchr_2, do not modify!!! */
    /* @remarks Implements DGFLIB00009 */
    #define GFLIB_Sin_Dsptchr_1(In)            GFLIB_Sin_Dsptchr_2(In,GFLIB_SIN_DEFAULT) /* Function dispatcher for GFLIB_Sin_Dsptchr_1, do not modify!!! */
  #endif 
  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_FLT)
    #define GFLIB_SIN_T                        GFLIB_SIN_T_FLT                           /**< Definition of GFLIB_SIN_T as alias for GFLIB_SIN_T_FLT datatype in case the single precision floating point implementation is selected. */
    #define GFLIB_SIN_DEFAULT                  GFLIB_SIN_DEFAULT_FLT                     /**< Definition of GFLIB_SIN_DEFAULT  as alias for GFLIB_SIN_DEFAULT_FLT default value in case the single precision floating point implementation is selected. */
    #define GFLIB_Sin_Dsptchr_2(In,pParam)     GFLIB_Sin_Dsptchr_3(In,pParam,FLT)        /* Function dispatcher for GFLIB_Sin_Dsptchr_2, do not modify!!! */
    /* @remarks Implements DGFLIB00009 */
    #define GFLIB_Sin_Dsptchr_1(In)            GFLIB_Sin_Dsptchr_2(In,GFLIB_SIN_DEFAULT) /* Function dispatcher for GFLIB_Sin_Dsptchr_1, do not modify!!! */
  #endif 

  #define GFLIB_Sin_Dsptchr_3(In,pParam,Impl)    GFLIB_Sin_Dsptchr_(In,pParam,Impl)     /* Function dispatcher for GFLIB_Sin_Dsptchr_3, do not modify!!! */
  
  /* @remarks Implements DGFLIB00011 */
  #define GFLIB_Sin_Dsptchr_(In,pParam,Impl)     GFLIB_Sin_##Impl(In,pParam)            /* Function dispatcher for GFLIB_Sin_Dsptchr_, do not modify!!! */
#endif
 
/****************************************************************************
* Typedefs and structures       (scope: module-local)
****************************************************************************/




/****************************************************************************
* Implementation variant: 32-bit fractional
****************************************************************************/
#if (SWLIBS_SUPPORT_F32 == SWLIBS_STD_ON)
  #define GFLIB_SIN_DEFAULT_F32  &f32gflibSinCoef     /**< Default approximation coefficients for GFLIB_Sin_F32 function. */
  
  /************************************************************************/
  /**
  @struct GFLIB_SIN_T_F32 "\GFLIB_Sin.h"

  @brief  Array of five 32-bit elements for storing coefficients of the Taylor polynomial.
  *//**********************************************************************/
  typedef struct{
    tFrac32  f32A[5];
  }GFLIB_SIN_T_F32;

  /************************************************************************/
  /**
  @brief  Default approximation coefficients for Sine approximation.
  *//**********************************************************************/

  extern const GFLIB_SIN_T_F32 f32gflibSinCoef;

/****************************************************************************
* Exported function prototypes
****************************************************************************/
  extern tFrac32 GFLIB_Sin_F32(tFrac32 f32In, const GFLIB_SIN_T_F32 *const pParam);
#endif /* SWLIBS_SUPPORT_F32 == SWLIBS_STD_ON */




/****************************************************************************
* Implementation variant: 16-bit fractional
****************************************************************************/
#if (SWLIBS_SUPPORT_F16 == SWLIBS_STD_ON)
  #define GFLIB_SIN_DEFAULT_F16  &f16gflibSinCoef     /**< Default approximation coefficients for GFLIB_Sin_F16 function. */
  
  /************************************************************************/
  /**
  @struct GFLIB_SIN_T_F16 "\GFLIB_Sin.h"

  @brief  Array of four 16-bit elements for storing coefficients of the Taylor polynomial.
  *//**********************************************************************/
  typedef struct{
    tFrac16  f16A[4];
  }GFLIB_SIN_T_F16;

  /************************************************************************/
  /**
  @brief  Default approximation coefficients for Sine approximation.
  *//**********************************************************************/

  extern const GFLIB_SIN_T_F16 f16gflibSinCoef;

/****************************************************************************
* Exported function prototypes
****************************************************************************/
  extern tFrac16 GFLIB_Sin_F16(tFrac16 f16In, const GFLIB_SIN_T_F16 *const pParam);
#endif /* SWLIBS_SUPPORT_F16 == SWLIBS_STD_ON */




/****************************************************************************
* Implementation variant: Single precision floating point
****************************************************************************/
#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
  #define GFLIB_SIN_DEFAULT_FLT  &fltgflibSinCoef     /**< Default approximation coefficients for GFLIB_Sin_FLT function. */

  /************************************************************************/
  /**
  @struct GFLIB_SIN_T_FLT "\GFLIB_Sin.h"

  @brief  Array of three single precision floating point elements for storing coefficients of the floating point optimized
          minimax approximation polynomial.
  *//**********************************************************************/
  typedef struct{
    tFloat  fltA[3];
  }GFLIB_SIN_T_FLT;

  /************************************************************************/
  /**
  @brief  Default approximation coefficients for Sine approximation.
  *//**********************************************************************/

  extern const GFLIB_SIN_T_FLT fltgflibSinCoef;
  
/****************************************************************************
* Exported function prototypes
****************************************************************************/
  extern tFloat GFLIB_Sin_FLT(tFloat fltIn, const GFLIB_SIN_T_FLT *const pParam);
#endif /* SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON */
/****************************************************************************
* Inline functions
****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* GFLIB_SIN_H */
