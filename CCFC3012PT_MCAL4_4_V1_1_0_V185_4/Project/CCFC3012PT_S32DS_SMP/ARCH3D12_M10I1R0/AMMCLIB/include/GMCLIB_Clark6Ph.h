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
* @file       GMCLIB_Clark6Ph.h
*
* @brief      Header file for GSWLIBS_Clark6Ph function
*
******************************************************************************/
#ifndef GMCLIB_CLARK6PH_H
#define GMCLIB_CLARK6PH_H

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
  #define GMCLIB_Clark6PhInit(...)     macro_dispatcher(GMCLIB_Clark6PhInit, __VA_ARGS__)(__VA_ARGS__)     /* This function implements the Clark6Phe transformation. */
  #define GMCLIB_Clark6Ph(...)     macro_dispatcher(GMCLIB_Clark6Ph, __VA_ARGS__)(__VA_ARGS__)
  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_F32)
    #define GMCLIB_CLARK_6PH_T                             GMCLIB_CLARK_6PH_T_F32
    /* @remarks Implements DGMCLIB00152 */
    #define GMCLIB_Clark6PhInit_Dsptchr_2(pParam,In)       GMCLIB_Clark6PhInit_Dsptchr_3(pParam,In,F32)     /* Function dispatcher for GMCLIB_Clark6PhInit_Dsptchr_2, do not modify!!! */
    /* @remarks Implements DGMCLIB00145 */
    #define GMCLIB_Clark6Ph_Dsptchr_3(pOut,pIn,pParam)     GMCLIB_Clark6Ph_Dsptchr_4(pOut,pIn,pParam,F32)     /* Function dispatcher for GMCLIB_Clark6Ph_Dsptchr_3, do not modify!!! */
  #endif 
  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_F16)
    #define GMCLIB_CLARK_6PH_T                             GMCLIB_CLARK_6PH_T_F16
    /* @remarks Implements DGMCLIB00152 */
    #define GMCLIB_Clark6PhInit_Dsptchr_2(pParam,In)       GMCLIB_Clark6PhInit_Dsptchr_3(pParam,In,F16)     /* Function dispatcher for GMCLIB_Clark6PhInit_Dsptchr_2, do not modify!!! */
    /* @remarks Implements DGMCLIB00145 */
    #define GMCLIB_Clark6Ph_Dsptchr_3(pOut,pIn,pParam)     GMCLIB_Clark6Ph_Dsptchr_4(pOut,pIn,pParam,F16)     /* Function dispatcher for GMCLIB_Clark6Ph_Dsptchr_3, do not modify!!! */
  #endif 
  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_FLT)
    #define GMCLIB_CLARK_6PH_T                             GMCLIB_CLARK_6PH_T_FLT
    /* @remarks Implements DGMCLIB00152 */
    #define GMCLIB_Clark6PhInit_Dsptchr_2(pParam,In)       GMCLIB_Clark6PhInit_Dsptchr_3(pParam,In,FLT)     /* Function dispatcher for GMCLIB_Clark6PhInit_Dsptchr_2, do not modify!!! */
    /* @remarks Implements DGMCLIB00145 */
    #define GMCLIB_Clark6Ph_Dsptchr_3(pOut,pIn,pParam)     GMCLIB_Clark6Ph_Dsptchr_4(pOut,pIn,pParam,FLT)     /* Function dispatcher for GMCLIB_Clark6Ph_Dsptchr_3, do not modify!!! */
  #endif 
  #define GMCLIB_Clark6PhInit_Dsptchr_3(pParam,In,Impl)    GMCLIB_Clark6PhInit_Dsptchr_(pParam,In,Impl)   /* Function dispatcher for GMCLIB_Clark6Ph_Dsptchr_3, do not modify!!! */
  
  /* @remarks Implements DGMCLIB00154 */
  #define GMCLIB_Clark6PhInit_Dsptchr_(pParam,In,Impl)     GMCLIB_Clark6PhInit_##Impl(pParam,In)          /* Function dispatcher for GMCLIB_Clark6Ph_Dsptchr_, do not modify!!! */
  #define GMCLIB_Clark6Ph_Dsptchr_4(pOut,pIn,pParam,Impl)    GMCLIB_Clark6Ph_Dsptchr_(pOut,pIn,pParam,Impl)   /* Function dispatcher for GMCLIB_Clark6Ph_Dsptchr_4, do not modify!!! */
  
  /* @remarks Implements DGMCLIB00147 */
  #define GMCLIB_Clark6Ph_Dsptchr_(pOut,pIn,pParam,Impl)     GMCLIB_Clark6Ph_##Impl(pOut,pIn,pParam)          /* Function dispatcher for GMCLIB_Clark6Ph_Dsptchr_, do not modify!!! */
#endif /* if (!(defined(__MINGW32__) || defined(__MINGW64__) || defined(_MSC_VER) || defined(_MATLAB_BAM_CREATE))) */
 
/****************************************************************************
* Typedefs and structures       (scope: module-local)
****************************************************************************/




/****************************************************************************
* Implementation variant: 32-bit fractional
****************************************************************************/
#if (SWLIBS_SUPPORT_F32 == SWLIBS_STD_ON)
/************************************************************************/
/**
@struct GMCLIB_CLARK_6PH_T_F32 "\GMCLIB_Clark6Ph.h" 

@brief  Parameters structure for 6-phase Clark function containing transformation
        coefficients calculated by GMCLIB_Clark6PhInit function.
*//**********************************************************************/
  typedef struct
  {
    tFrac32 f32AlphaD;  /**< Transformation coefficient AlphaD */
    tFrac32 f32AlphaE;  /**< Transformation coefficient AlphaE */
    tFrac32 f32AlphaF;  /**< Transformation coefficient AlphaF */
    tFrac32 f32BetaD;   /**< Transformation coefficient BetaD */
    tFrac32 f32BetaE;   /**< Transformation coefficient BetaE */
    tFrac32 f32BetaF;   /**< Transformation coefficient BetaF */
  }GMCLIB_CLARK_6PH_T_F32;

/****************************************************************************
* Exported function prototypes
****************************************************************************/
  extern void GMCLIB_Clark6PhInit_F32(GMCLIB_CLARK_6PH_T_F32 *const pParam, tFrac32 f32WindingShift);
  extern void GMCLIB_Clark6Ph_F32(SWLIBS_2Syst_F32 *const pOut, const SWLIBS_6Syst_F32 *const pIn, const GMCLIB_CLARK_6PH_T_F32 *const pParam);
#endif /* SWLIBS_SUPPORT_F32 == SWLIBS_STD_ON */




/****************************************************************************
* Implementation variant: 16-bit fractional
****************************************************************************/
#if (SWLIBS_SUPPORT_F16 == SWLIBS_STD_ON)
/************************************************************************/
/**
@struct GMCLIB_CLARK_6PH_T_F16 "\GMCLIB_Clark6Ph.h" 

@brief  Parameters structure for 6-phase Clark function containing transformation
        coefficients calculated by GMCLIB_Clark6PhInit function.
*//**********************************************************************/
  typedef struct
  {
    tFrac16 f16AlphaD;  /**< Transformation coefficient AlphaD */
    tFrac16 f16AlphaE;  /**< Transformation coefficient AlphaE */
    tFrac16 f16AlphaF;  /**< Transformation coefficient AlphaF */
    tFrac16 f16BetaD;   /**< Transformation coefficient BetaD */
    tFrac16 f16BetaE;   /**< Transformation coefficient BetaE */
    tFrac16 f16BetaF;   /**< Transformation coefficient BetaF */
  }GMCLIB_CLARK_6PH_T_F16;
  
/****************************************************************************
* Exported function prototypes
****************************************************************************/
  extern void GMCLIB_Clark6PhInit_F16(GMCLIB_CLARK_6PH_T_F16 *const pParam, tFrac16 f16WindingShift);
  extern void GMCLIB_Clark6Ph_F16(SWLIBS_2Syst_F16 *const pOut, const SWLIBS_6Syst_F16 *const pIn, const GMCLIB_CLARK_6PH_T_F16 *const pParam);
#endif /* SWLIBS_SUPPORT_F16 == SWLIBS_STD_ON */




/****************************************************************************
* Implementation variant: Single precision floating point
****************************************************************************/
#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/************************************************************************/
/**
@struct GMCLIB_CLARK_6PH_T_FLT "\GMCLIB_Clark6Ph.h" 

@brief  Parameters structure for 6-phase Clark function containing transformation
        coefficients calculated by GMCLIB_Clark6PhInit function.
*//**********************************************************************/
  typedef struct
  {
    tFloat fltAlphaD;  /**< Transformation coefficient AlphaD */
    tFloat fltAlphaE;  /**< Transformation coefficient AlphaE */
    tFloat fltAlphaF;  /**< Transformation coefficient AlphaF */
    tFloat fltBetaD;   /**< Transformation coefficient BetaD */
    tFloat fltBetaE;   /**< Transformation coefficient BetaE */
    tFloat fltBetaF;   /**< Transformation coefficient BetaF */
  }GMCLIB_CLARK_6PH_T_FLT;
  
/****************************************************************************
* Exported function prototypes
****************************************************************************/
  extern void GMCLIB_Clark6PhInit_FLT(GMCLIB_CLARK_6PH_T_FLT *const pParam, tFloat fltWindingShift);
  extern void GMCLIB_Clark6Ph_FLT(SWLIBS_2Syst_FLT *const pOut, const SWLIBS_6Syst_FLT *const pIn, const GMCLIB_CLARK_6PH_T_FLT *const pParam);
#endif /* SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON */
/****************************************************************************
* Inline functions
****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* GMCLIB_CLARK6PH_H */
