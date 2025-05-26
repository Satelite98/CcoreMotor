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
* @file       GDFLIB_FilterIIR2.h
*
* @brief      Header file for GDFLIB_FilterIIR2 function
*
******************************************************************************/
#ifndef GDFLIB_FILTERIIR2_H
#define GDFLIB_FILTERIIR2_H

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
  #define GDFLIB_FilterIIR2Init(...)     macro_dispatcher(GDFLIB_FilterIIR2Init, __VA_ARGS__)(__VA_ARGS__)     /* This function initializes the second order IIR filter buffers. */
  #define GDFLIB_FilterIIR2(...)         macro_dispatcher(GDFLIB_FilterIIR2, __VA_ARGS__)(__VA_ARGS__)         /* This function implements the second order IIR filter. */

  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_F32)
    #define GDFLIB_FILTER_IIR2_T                        GDFLIB_FILTER_IIR2_T_F32                        /**< Definition of GDFLIB_FILTER_IIR2_T as alias for GDFLIB_FILTER_IIR2_T_F32 datatype in case the 32-bit fractional implementation is selected. */
    #define GDFLIB_FILTER_IIR2_DEFAULT                  GDFLIB_FILTER_IIR2_DEFAULT_F32                  /**< Definition of GDFLIB_FILTER_IIR2_DEFAULT as alias for GDFLIB_FILTER_IIR2_DEFAULT_F32 default value in case the 32-bit fractional implementation is selected. */
    /* @remarks Implements DGDFLIB00060 */
    #define GDFLIB_FilterIIR2Init_Dsptchr_1(pParam)     GDFLIB_FilterIIR2Init_Dsptchr_2(pParam,F32)     /* Function dispatcher for GDFLIB_FilterIIR2Init_Dsptchr_1, do not modify!!! */
    /* @remarks Implements DGDFLIB00043 */
    #define GDFLIB_FilterIIR2_Dsptchr_2(In,pParam)      GDFLIB_FilterIIR2_Dsptchr_3(In,pParam,F32)      /* Function dispatcher for GDFLIB_FilterIIR2_Dsptchr_2, do not modify!!! */
  #endif 
  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_F16)
    #define GDFLIB_FILTER_IIR2_T                        GDFLIB_FILTER_IIR2_T_F16                        /**< Definition of GDFLIB_FILTER_IIR2_T as alias for GDFLIB_FILTER_IIR2_T_F16 datatype in case the 16-bit fractional implementation is selected. */
    #define GDFLIB_FILTER_IIR2_DEFAULT                  GDFLIB_FILTER_IIR2_DEFAULT_F16                  /**< Definition of GDFLIB_FILTER_IIR2_DEFAULT GDFLIB_FILTER_IIR2_DEFAULT_F16 default value in case the 16-bit fractional implementation is selected. */
    /* @remarks Implements DGDFLIB00060 */
    #define GDFLIB_FilterIIR2Init_Dsptchr_1(pParam)     GDFLIB_FilterIIR2Init_Dsptchr_2(pParam,F16)     /* Function dispatcher for GDFLIB_FilterIIR2Init_Dsptchr_1, do not modify!!! */
    /* @remarks Implements DGDFLIB00043 */
    #define GDFLIB_FilterIIR2_Dsptchr_2(In,pParam)      GDFLIB_FilterIIR2_Dsptchr_3(In,pParam,F16)      /* Function dispatcher for GDFLIB_FilterIIR2_Dsptchr_2, do not modify!!! */
  #endif 
  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_FLT)
    #define GDFLIB_FILTER_IIR2_T                        GDFLIB_FILTER_IIR2_T_FLT                        /**< Definition of GDFLIB_FILTER_IIR2_T as alias for GDFLIB_FILTER_IIR2_T_FLT datatype in case the single precision floating point implementation is selected. */
    #define GDFLIB_FILTER_IIR2_DEFAULT                  GDFLIB_FILTER_IIR2_DEFAULT_FLT                  /**< Definition of GDFLIB_FILTER_IIR2_DEFAULT GDFLIB_FILTER_IIR2_DEFAULT_FLT default value in case the single precision floating point implementation is selected. */
    /* @remarks Implements DGDFLIB00060 */
    #define GDFLIB_FilterIIR2Init_Dsptchr_1(pParam)     GDFLIB_FilterIIR2Init_Dsptchr_2(pParam,FLT)     /* Function dispatcher for GDFLIB_FilterIIR2Init_Dsptchr_1, do not modify!!! */
    /* @remarks Implements DGDFLIB00043 */
    #define GDFLIB_FilterIIR2_Dsptchr_2(In,pParam)      GDFLIB_FilterIIR2_Dsptchr_3(In,pParam,FLT)      /* Function dispatcher for GDFLIB_FilterIIR2_Dsptchr_2, do not modify!!! */
  #endif 

  #define GDFLIB_FilterIIR2Init_Dsptchr_2(pParam,Impl)    GDFLIB_FilterIIR2Init_Dsptchr_(pParam,Impl)     /* Function dispatcher for GDFLIB_FilterIIR2Init_Dsptchr_2, do not modify!!! */
  /* @remarks Implements DGDFLIB00067 */
  #define GDFLIB_FilterIIR2Init_Dsptchr_(pParam,Impl)     GDFLIB_FilterIIR2Init_##Impl(pParam)            /* Function dispatcher for GDFLIB_FilterIIR2Init_Dsptchr_, do not modify!!! */

  #define GDFLIB_FilterIIR2_Dsptchr_3(In,pParam,Impl)     GDFLIB_FilterIIR2_Dsptchr_(In,pParam,Impl)      /* Function dispatcher for GDFLIB_FilterIIR2_Dsptchr_3, do not modify!!! */
  /* @remarks Implements DGDFLIB00054 */
  #define GDFLIB_FilterIIR2_Dsptchr_(In,pParam,Impl)      GDFLIB_FilterIIR2_##Impl(In,pParam)             /* Function dispatcher for GDFLIB_FilterIIR2_Dsptchr_, do not modify!!! */
#endif /* if (!(defined(__MINGW32__) || defined(__MINGW64__) || defined(_MSC_VER) || defined(_MATLAB_BAM_CREATE))) */

/****************************************************************************
* Typedefs and structures       (scope: module-local)
****************************************************************************/




/****************************************************************************
* Implementation variant: 32-bit fractional
****************************************************************************/
#if (SWLIBS_SUPPORT_F32 == SWLIBS_STD_ON)
  #define GDFLIB_FILTER_IIR2_DEFAULT_F32 {{(tFrac32)0,(tFrac32)0,(tFrac32)0,(tFrac32)0,(tFrac32)0},{(tFrac32)0,(tFrac32)0},{(tFrac32)0,(tFrac32)0}}     /**< Default value for GDFLIB_FILTER_IIR2_T_F32. */

  /*************************************************************************/
  /**
  @struct GDFLIB_FILTER_IIR2_COEFF_T_F32 "\GDFLIB_FilterIIR2.h"

  @brief  Sub-structure containing filter coefficients.
  *//***********************************************************************/
  /* @remarks Implements DGDFLIB00048 */
  typedef struct{
    tFrac32 f32B0; /**< B0 coefficient of an IIR2 filter, fractional format normalized to fit into (-\f$2^{31}\f$, \f$2^{31}\f$-1). */
    tFrac32 f32B1; /**< B1 coefficient of an IIR2 filter, fractional format normalized to fit into (-\f$2^{31}\f$, \f$2^{31}\f$-1). */
    tFrac32 f32B2; /**< B2 coefficient of an IIR2 filter, fractional format normalized to fit into (-\f$2^{31}\f$, \f$2^{31}\f$-1). */
    tFrac32 f32A1; /**< A1 coefficient of an IIR2 filter, fractional format normalized to fit into (-\f$2^{31}\f$, \f$2^{31}\f$-1). */
    tFrac32 f32A2; /**< A2 coefficient of an IIR2 filter, fractional format normalized to fit into (-\f$2^{31}\f$, \f$2^{31}\f$-1). */
  }GDFLIB_FILTER_IIR2_COEFF_T_F32;

  /*************************************************************************/
  /**
  @struct GDFLIB_FILTER_IIR2_T_F32 "\GDFLIB_FilterIIR2.h" 

  @brief  Structure containing filter buffer and coefficients.
  *//***********************************************************************/
  /* @remarks Implements DGDFLIB00051, DGDFLIB00052, DGDFLIB00065, DGDFLIB00062, DGDFLIB00059, DGDFLIB00045 */
  typedef struct{
    GDFLIB_FILTER_IIR2_COEFF_T_F32 trFiltCoeff; /**< Sub-structure containing filter coefficients. */
    tFrac32 f32FiltBufferX[2]; /**< Input buffer of an IIR2 filter, fractional format normalized to fit into (-\f$2^{31}\f$, \f$2^{31}\f$-1). */
    tFrac32 f32FiltBufferY[2]; /**< Internal accumulator buffer, fractional format normalized to fit into (-\f$2^{31}\f$, \f$2^{31}\f$-1). */
  }GDFLIB_FILTER_IIR2_T_F32;

/****************************************************************************
* Exported function prototypes
****************************************************************************/
  extern void GDFLIB_FilterIIR2Init_F32(GDFLIB_FILTER_IIR2_T_F32 *const pParam);
  extern tFrac32 GDFLIB_FilterIIR2_F32(tFrac32 f32In,GDFLIB_FILTER_IIR2_T_F32 *const pParam);
#endif /* SWLIBS_SUPPORT_F32 == SWLIBS_STD_ON */




/****************************************************************************
* Implementation variant: 16-bit fractional
****************************************************************************/
#if (SWLIBS_SUPPORT_F16 == SWLIBS_STD_ON)
  #define GDFLIB_FILTER_IIR2_DEFAULT_F16 {{(tFrac16)0,(tFrac16)0,(tFrac16)0,(tFrac16)0,(tFrac16)0},{(tFrac16)0,(tFrac16)0},{(tFrac16)0,(tFrac16)0}}     /**< Default value for GDFLIB_FILTER_IIR2_T_F16. */

  /*************************************************************************/
  /**
  @struct GDFLIB_FILTER_IIR2_COEFF_T_F16 "\GDFLIB_FilterIIR2.h"

  @brief  Sub-structure containing filter coefficients.
  *//***********************************************************************/
  /* @remarks Implements DGDFLIB00049 */
  typedef struct{    
    tFrac16 f16B0; /**< B0 coefficient of an IIR2 filter, fractional format normalized to fit into (-\f$2^{15}\f$, \f$2^{15}\f$-1). */
    tFrac16 f16B1; /**< B1 coefficient of an IIR2 filter, fractional format normalized to fit into (-\f$2^{15}\f$, \f$2^{15}\f$-1). */
    tFrac16 f16B2; /**< B2 coefficient of an IIR2 filter, fractional format normalized to fit into (-\f$2^{15}\f$, \f$2^{15}\f$-1). */
    tFrac16 f16A1; /**< A1 coefficient of an IIR2 filter, fractional format normalized to fit into (-\f$2^{15}\f$, \f$2^{15}\f$-1). */
    tFrac16 f16A2; /**< A2 coefficient of an IIR2 filter, fractional format normalized to fit into (-\f$2^{15}\f$, \f$2^{15}\f$-1). */
  }GDFLIB_FILTER_IIR2_COEFF_T_F16;

  /*************************************************************************/
  /**
  @struct GDFLIB_FILTER_IIR2_T_F16 "\GDFLIB_FilterIIR2.h" 

  @brief  Structure containing filter buffer and coefficients.
  *//***********************************************************************/
  /* @remarks Implements DGDFLIB00051, DGDFLIB00052, DGDFLIB00065, DGDFLIB00063, DGDFLIB00059, DGDFLIB00046 */
  typedef struct{
    GDFLIB_FILTER_IIR2_COEFF_T_F16 trFiltCoeff; /**< Sub-structure containing filter coefficients. */
    tFrac16 f16FiltBufferX[2]; /**< Input buffer of an IIR2 filter, fractional format normalized to fit into (-\f$2^{15}\f$, \f$2^{15}\f$-1). */
    tFrac32 f32FiltBufferY[2]; /**< Internal accumulator buffer, fractional format normalized to fit into (-\f$2^{15}\f$, \f$2^{15}\f$-1). */
  }GDFLIB_FILTER_IIR2_T_F16;

/****************************************************************************
* Exported function prototypes
****************************************************************************/
  extern void GDFLIB_FilterIIR2Init_F16(GDFLIB_FILTER_IIR2_T_F16 *const pParam);
  extern tFrac16 GDFLIB_FilterIIR2_F16(tFrac16 f16In,GDFLIB_FILTER_IIR2_T_F16 *const pParam);
#endif /* SWLIBS_SUPPORT_F16 == SWLIBS_STD_ON */




/****************************************************************************
* Implementation variant: Single precision floating point
****************************************************************************/
#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
  #define GDFLIB_FILTER_IIR2_DEFAULT_FLT {{(tFloat)0,(tFloat)0,(tFloat)0,(tFloat)0,(tFloat)0},{(tFloat)0,(tFloat)0},{(tFloat)0,(tFloat)0}}     /**< Default value for GDFLIB_FILTER_IIR2_T_FLT. */

  /*************************************************************************/
  /**
  @struct GDFLIB_FILTER_IIR2_COEFF_T_FLT "\GDFLIB_FilterIIR2.h"

  @brief  Sub-structure containing filter coefficients.
  *//***********************************************************************/
  /* @remarks Implements DGDFLIB00050 */
  typedef struct{    
    tFloat fltB0; /**< B0 coefficient of an IIR2 filter. The parameter is in full range single precision floating point format. */
    tFloat fltB1; /**< B1 coefficient of an IIR2 filter. The parameter is in full range single precision floating point format. */
    tFloat fltB2; /**< B2 coefficient of an IIR2 filter. The parameter is in full range single precision floating point format. */
    tFloat fltA1; /**< A1 coefficient of an IIR2 filter. The parameter is in full range single precision floating point format. */
    tFloat fltA2; /**< A2 coefficient of an IIR2 filter. The parameter is in full range single precision floating point format. */
  }GDFLIB_FILTER_IIR2_COEFF_T_FLT;

  /*************************************************************************/
  /**
  @struct GDFLIB_FILTER_IIR2_T_FLT "\GDFLIB_FilterIIR2.h" 

  @brief  Structure containing filter buffer and coefficients.
  *//***********************************************************************/
  /* @remarks Implements DGDFLIB00051, DGDFLIB00052, DGDFLIB00065, DGDFLIB00059, DGDFLIB00047 */
  typedef struct{
    GDFLIB_FILTER_IIR2_COEFF_T_FLT trFiltCoeff; /**< Sub-structure containing filter coefficients. */
    tFloat fltFiltBufferX[2]; /**< Input buffer of an IIR2 filter. The input values are in full range single precision floating point format. */
    tFloat fltFiltBufferY[2]; /**< Internal accumulator buffer. The values are in full range single precision floating point format. */
  }GDFLIB_FILTER_IIR2_T_FLT;

/****************************************************************************
* Exported function prototypes
****************************************************************************/
  extern void GDFLIB_FilterIIR2Init_FLT(GDFLIB_FILTER_IIR2_T_FLT *const pParam);
  extern tFloat GDFLIB_FilterIIR2_FLT(tFloat fltIn,GDFLIB_FILTER_IIR2_T_FLT *const pParam);
#endif /* SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON */
/****************************************************************************
* Inline functions
****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* GDFLIB_FILTERIIR2_H */
