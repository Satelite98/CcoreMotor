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
* @file       GMCLIB_ElimDcBusRip.h
*
* @brief      Header file for GMCLIB_ElimDcBusRip function
*
******************************************************************************/
#ifndef GMCLIB_ELIMDCBUSRIP_H
#define GMCLIB_ELIMDCBUSRIP_H

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
  #define GMCLIB_ElimDcBusRip(...)     macro_dispatcher(GMCLIB_ElimDcBusRip, __VA_ARGS__)(__VA_ARGS__)     /* This function implements the DC Bus voltage ripple elimination. */
  
  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_F32)
    #define GMCLIB_ELIMDCBUSRIP_T                              GMCLIB_ELIMDCBUSRIP_T_F32                              /**< Definition of GMCLIB_ELIMDCBUSRIP_T as alias for GMCLIB_ELIMDCBUSRIP_T_F32 datatype in case the 32-bit fractional implementation is selected. */
    #define GMCLIB_ELIMDCBUSRIP_DEFAULT                        GMCLIB_ELIMDCBUSRIP_DEFAULT_F32                        /**< Definition of GMCLIB_ELIMDCBUSRIP_DEFAULT as alias for GMCLIB_ELIMDCBUSRIP_DEFAULT_F32 default value in case the 32-bit fractional implementation is selected. */
    /* @remarks Implements DGMCLIB00044 */
    #define GMCLIB_ElimDcBusRip_Dsptchr_3(pOut,pIn,pParam)     GMCLIB_ElimDcBusRip_Dsptchr_4(pOut,pIn,pParam,F32)     /* Function dispatcher for GMCLIB_ElimDcBusRip_Dsptchr_3, do not modify!!! */
  #endif 
  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_F16)
    #define GMCLIB_ELIMDCBUSRIP_T                              GMCLIB_ELIMDCBUSRIP_T_F16                              /**< Definition of GMCLIB_ELIMDCBUSRIP_T as alias for GMCLIB_ELIMDCBUSRIP_T_F16 datatype in case the 16-bit fractional implementation is selected. */
    #define GMCLIB_ELIMDCBUSRIP_DEFAULT                        GMCLIB_ELIMDCBUSRIP_DEFAULT_F16                        /**< Definition of GMCLIB_ELIMDCBUSRIP_DEFAULT as alias for GMCLIB_ELIMDCBUSRIP_DEFAULT_F16 default value in case the 16-bit fractional implementation is selected. */
    /* @remarks Implements DGMCLIB00044 */
    #define GMCLIB_ElimDcBusRip_Dsptchr_3(pOut,pIn,pParam)     GMCLIB_ElimDcBusRip_Dsptchr_4(pOut,pIn,pParam,F16)     /* Function dispatcher for GMCLIB_ElimDcBusRip_Dsptchr_3, do not modify!!! */
  #endif 
  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_FLT)
    #define GMCLIB_ELIMDCBUSRIP_T                              GMCLIB_ELIMDCBUSRIP_T_FLT                              /**< Definition of GMCLIB_ELIMDCBUSRIP_T as alias for GMCLIB_ELIMDCBUSRIP_T_FLT datatype in case the single precision floating point implementation is selected. */
    #define GMCLIB_ELIMDCBUSRIP_DEFAULT                        GMCLIB_ELIMDCBUSRIP_DEFAULT_FLT                        /**< Definition of GMCLIB_ELIMDCBUSRIP_DEFAULT as alias for GMCLIB_ELIMDCBUSRIP_DEFAULT_FLT default value in case the single precision floating point implementation is selected. */
    /* @remarks Implements DGMCLIB00044 */
    #define GMCLIB_ElimDcBusRip_Dsptchr_3(pOut,pIn,pParam)     GMCLIB_ElimDcBusRip_Dsptchr_4(pOut,pIn,pParam,FLT)     /* Function dispatcher for GMCLIB_ElimDcBusRip_Dsptchr_3, do not modify!!! */
  #endif 

  #define GMCLIB_ElimDcBusRip_Dsptchr_4(pOut,pIn,pParam,Impl)    GMCLIB_ElimDcBusRip_Dsptchr_(pOut,pIn,pParam,Impl)   /* Function dispatcher for GMCLIB_ElimDcBusRip_Dsptchr_4, do not modify!!! */
  
  /* @remarks Implements DGMCLIB00050 */
  #define GMCLIB_ElimDcBusRip_Dsptchr_(pOut,pIn,pParam,Impl)     GMCLIB_ElimDcBusRip_##Impl(pOut,pIn,pParam)          /* Function dispatcher for GMCLIB_ElimDcBusRip_Dsptchr_, do not modify!!! */
#endif /* if (!(defined(__MINGW32__) || defined(__MINGW64__) || defined(_MSC_VER) || defined(_MATLAB_BAM_CREATE))) */
 
/****************************************************************************
* Typedefs and structures       (scope: module-local)
****************************************************************************/




/****************************************************************************
* Implementation variant: 32-bit fractional
****************************************************************************/
#if (SWLIBS_SUPPORT_F32 == SWLIBS_STD_ON)
  #define GMCLIB_ELIMDCBUSRIP_DEFAULT_F32 {(tFrac32)0,(tFrac32)0}     /**< Default value for GMCLIB_ELIMDCBUSRIP_T_F32. */

  /************************************************************************/
  /**
  @struct GMCLIB_ELIMDCBUSRIP_T_F32 "\GMCLIB_ElimDcBusRip.h" 

  @brief  Structure containing the PWM modulation index and the measured value of the DC bus voltage.
  *//*************************************************************************/
  /* @remarks Implements DGMCLIB00048, DGMCLIB00052, DGMCLIB00047 */
  typedef struct{
    tFrac32 f32ArgDcBusMsr; /**< Measured DC bus voltage. */
    tFrac32 f32ModIndex; /**< Inverse Modulation Index. */
  }GMCLIB_ELIMDCBUSRIP_T_F32;

/****************************************************************************
* Exported function prototypes
****************************************************************************/
  extern void GMCLIB_ElimDcBusRip_F32(SWLIBS_2Syst_F32 *const pOut, const SWLIBS_2Syst_F32 *const pIn, const GMCLIB_ELIMDCBUSRIP_T_F32 *const pParam);
#endif /* SWLIBS_SUPPORT_F32 == SWLIBS_STD_ON */




/****************************************************************************
* Implementation variant: 16-bit fractional
****************************************************************************/
#if (SWLIBS_SUPPORT_F16 == SWLIBS_STD_ON)
  #define GMCLIB_ELIMDCBUSRIP_DEFAULT_F16 {(tFrac16)0,(tFrac16)0}     /**< Default value for GMCLIB_ELIMDCBUSRIP_T_F16. */

  /************************************************************************/
  /**
  @struct GMCLIB_ELIMDCBUSRIP_T_F16 "\GMCLIB_ElimDcBusRip.h" 

  @brief  Structure containing the PWM modulation index and the measured value of the DC bus voltage.
  *//*************************************************************************/
  /* @remarks Implements DGMCLIB00048, DGMCLIB00052, DGMCLIB00046 */
  typedef struct{
    tFrac16 f16ArgDcBusMsr; /**< Measured DC bus voltage. */
    tFrac16 f16ModIndex; /**< Inverse Modulation Index. */
  }GMCLIB_ELIMDCBUSRIP_T_F16;

/****************************************************************************
* Exported function prototypes
****************************************************************************/
  extern void GMCLIB_ElimDcBusRip_F16(SWLIBS_2Syst_F16 *const pOut, const SWLIBS_2Syst_F16 *const pIn, const GMCLIB_ELIMDCBUSRIP_T_F16 *const pParam);
#endif /* SWLIBS_SUPPORT_F16 == SWLIBS_STD_ON */




/****************************************************************************
* Implementation variant: Single precision floating point
****************************************************************************/
#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
  #define GMCLIB_ELIMDCBUSRIP_DEFAULT_FLT {(tFloat)0,(tFloat)0}     /**< Default value for GMCLIB_ELIMDCBUSRIP_T_FLT. */

  /************************************************************************/
  /**
  @struct GMCLIB_ELIMDCBUSRIP_T_FLT "\GMCLIB_ElimDcBusRip.h" 

  @brief  Structure containing the PWM modulation index and the measured value of the DC bus voltage.
  *//*************************************************************************/
  /* @remarks Implements DGMCLIB00048, DGMCLIB00052, DGMCLIB00045 */
  typedef struct{
    tFloat fltArgDcBusMsr; /**< Measured DC bus voltage. */
    tFloat fltModIndex; /**< Inverse Modulation Index. */
  }GMCLIB_ELIMDCBUSRIP_T_FLT;

/****************************************************************************
* Exported function prototypes
****************************************************************************/
  extern void GMCLIB_ElimDcBusRip_FLT(SWLIBS_2Syst_FLT *const pOut, const SWLIBS_2Syst_FLT *const pIn, const GMCLIB_ELIMDCBUSRIP_T_FLT *const pParam);
#endif /* SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON */
/****************************************************************************
* Inline functions
****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* GMCLIB_ELIMDCBUSRIP_H */
