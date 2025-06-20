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
* @file       GFLIB_ControllerPIp.h
*
* @brief      Header file for GFLIB_ControllerPIp function
*
******************************************************************************/
#ifndef GFLIB_CONTROLLERPIP_H
#define GFLIB_CONTROLLERPIP_H

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
  #define GFLIB_ControllerPIpInit(...)     macro_dispatcher(GFLIB_ControllerPIpInit, __VA_ARGS__)(__VA_ARGS__)     /* This function clears the state variables of the Proportional-Integral controller. */
  #define GFLIB_ControllerPIpSetState(...)     macro_dispatcher(GFLIB_ControllerPIpSetState, __VA_ARGS__)(__VA_ARGS__)     /* This function sets the state variables of the Proportional-Integral controller to achieve the required output value. */
  #define GFLIB_ControllerPIp(...)     macro_dispatcher(GFLIB_ControllerPIp, __VA_ARGS__)(__VA_ARGS__)     /* This function calculates a parallel form of the Proportional- Integral controller, without integral anti-windup. */

  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_F32)
    #define GFLIB_CONTROLLER_PI_P_T                         GFLIB_CONTROLLER_PI_P_T_F32                         /**< Definition of GFLIB_CONTROLLER_PI_P_T as alias for GFLIB_CONTROLLER_PI_P_T_F32 datatype in case the 32-bit fractional implementation is selected. */
    #define GFLIB_CONTROLLER_PI_P_DEFAULT                   GFLIB_CONTROLLER_PI_P_DEFAULT_F32                   /**< Definition of GFLIB_CONTROLLER_PI_P_DEFAULT as alias for GFLIB_CONTROLLER_PI_P_DEFAULT_F32 default value in case the 32-bit fractional implementation is selected. */
    /* @remarks Implements DGFLIB00375 */
    #define GFLIB_ControllerPIpInit_Dsptchr_1(pParam)     GFLIB_ControllerPIpInit_Dsptchr_2(pParam,F32)     /* Function dispatcher for GFLIB_ControllerPIpInit_Dsptchr_1, do not modify!!! */
    /* @remarks Implements DGFLIB00382 */
    #define GFLIB_ControllerPIpSetState_Dsptchr_2(ControllerPIpAWOut,pParam)     GFLIB_ControllerPIpSetState_Dsptchr_3(ControllerPIpAWOut,pParam,F32)     /* Function dispatcher for GFLIB_ControllerPIpSetState_Dsptchr_2, do not modify!!! */
    /* @remarks Implements DGFLIB00300 */
    #define GFLIB_ControllerPIp_Dsptchr_2(InErr,pParam)     GFLIB_ControllerPIp_Dsptchr_3(InErr,pParam,F32)     /* Function dispatcher for GFLIB_ControllerPIp_Dsptchr_2, do not modify!!! */
  #endif 
  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_F16)
    #define GFLIB_CONTROLLER_PI_P_T                         GFLIB_CONTROLLER_PI_P_T_F16                         /**< Definition of GFLIB_CONTROLLER_PI_P_T as alias for GFLIB_CONTROLLER_PI_P_T_F16 datatype in case the 16-bit fractional implementation is selected. */
    #define GFLIB_CONTROLLER_PI_P_DEFAULT                   GFLIB_CONTROLLER_PI_P_DEFAULT_F16                   /**< Definition of GFLIB_CONTROLLER_PI_P_DEFAULT as alias for GFLIB_CONTROLLER_PI_P_DEFAULT_F16 default value in case the 16-bit fractional implementation is selected. */
    /* @remarks Implements DGFLIB00375 */
    #define GFLIB_ControllerPIpInit_Dsptchr_1(pParam)     GFLIB_ControllerPIpInit_Dsptchr_2(pParam,F16)     /* Function dispatcher for GFLIB_ControllerPIpInit_Dsptchr_1, do not modify!!! */
    /* @remarks Implements DGFLIB00382 */
    #define GFLIB_ControllerPIpSetState_Dsptchr_2(ControllerPIpAWOut,pParam)     GFLIB_ControllerPIpSetState_Dsptchr_3(ControllerPIpAWOut,pParam,F16)     /* Function dispatcher for GFLIB_ControllerPIpSetState_Dsptchr_2, do not modify!!! */
    /* @remarks Implements DGFLIB00300 */
    #define GFLIB_ControllerPIp_Dsptchr_2(InErr,pParam)     GFLIB_ControllerPIp_Dsptchr_3(InErr,pParam,F16)     /* Function dispatcher for GFLIB_ControllerPIp_Dsptchr_2, do not modify!!! */
  #endif 
  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_FLT)
    #define GFLIB_CONTROLLER_PI_P_T                         GFLIB_CONTROLLER_PI_P_T_FLT                         /**< Definition of GFLIB_CONTROLLER_PI_P_T as alias for GFLIB_CONTROLLER_PI_P_T_FLT datatype in case the single precision floating point implementation is selected. */
    #define GFLIB_CONTROLLER_PI_P_DEFAULT                   GFLIB_CONTROLLER_PI_P_DEFAULT_FLT                   /**< Definition of GFLIB_CONTROLLER_PI_P_DEFAULT as alias for GFLIB_CONTROLLER_PI_P_DEFAULT_FLT default value in case the single precision floating point implementation is selected. */
    /* @remarks Implements DGFLIB00375 */
    #define GFLIB_ControllerPIpInit_Dsptchr_1(pParam)     GFLIB_ControllerPIpInit_Dsptchr_2(pParam,FLT)     /* Function dispatcher for GFLIB_ControllerPIpInit_Dsptchr_1, do not modify!!! */
    /* @remarks Implements DGFLIB00382 */
    #define GFLIB_ControllerPIpSetState_Dsptchr_2(ControllerPIpAWOut,pParam)     GFLIB_ControllerPIpSetState_Dsptchr_3(ControllerPIpAWOut,pParam,FLT)     /* Function dispatcher for GFLIB_ControllerPIpSetState_Dsptchr_2, do not modify!!! */
    /* @remarks Implements DGFLIB00300 */
    #define GFLIB_ControllerPIp_Dsptchr_2(InErr,pParam)     GFLIB_ControllerPIp_Dsptchr_3(InErr,pParam,FLT)     /* Function dispatcher for GFLIB_ControllerPIp_Dsptchr_2, do not modify!!! */
  #endif 

  #define GFLIB_ControllerPIpInit_Dsptchr_2(pParam,Impl)    GFLIB_ControllerPIpInit_Dsptchr_(pParam,Impl)     /* Function dispatcher for GFLIB_ControllerPIpInit_Dsptchr_2, do not modify!!! */
  
  /* @remarks Implements DGFLIB00377 */
  #define GFLIB_ControllerPIpInit_Dsptchr_(pParam,Impl)     GFLIB_ControllerPIpInit_##Impl(pParam)            /* Function dispatcher for GFLIB_ControllerPIpInit_Dsptchr_, do not modify!!! */

  #define GFLIB_ControllerPIpSetState_Dsptchr_3(ControllerPIpAWOut,pParam,Impl)    GFLIB_ControllerPIpSetState_Dsptchr_(ControllerPIpAWOut,pParam,Impl)     /* Function dispatcher for GFLIB_ControllerPIpSetState_Dsptchr_3, do not modify!!! */
  
  /* @remarks Implements DGFLIB00384 */
  #define GFLIB_ControllerPIpSetState_Dsptchr_(ControllerPIpAWOut,pParam,Impl)     GFLIB_ControllerPIpSetState_##Impl(ControllerPIpAWOut,pParam)            /* Function dispatcher for GFLIB_ControllerPIpSetState_Dsptchr_, do not modify!!! */

  #define GFLIB_ControllerPIp_Dsptchr_3(InErr,pParam,Impl)    GFLIB_ControllerPIp_Dsptchr_(InErr,pParam,Impl)     /* Function dispatcher for GFLIB_ControllerPIp_Dsptchr_3, do not modify!!! */
  
  /* @remarks Implements DGFLIB00303 */
  #define GFLIB_ControllerPIp_Dsptchr_(InErr,pParam,Impl)     GFLIB_ControllerPIp_##Impl(InErr,pParam)            /* Function dispatcher for GFLIB_ControllerPIp_Dsptchr_, do not modify!!! */
#endif
 
/****************************************************************************
* Typedefs and structures       (scope: module-local)
****************************************************************************/




/****************************************************************************
* Implementation variant: 32-bit fractional
****************************************************************************/
#if (SWLIBS_SUPPORT_F32 == SWLIBS_STD_ON)
  #define GFLIB_CONTROLLER_PI_P_DEFAULT_F32 {(tFrac32)0,(tFrac32)0,(tS16)0,(tS16)0,(tFrac32)0,(tFrac32)0}     /**< Default value for GFLIB_CONTROLLER_PI_P_T_F32. */

  /************************************************************************/
  /**
  @struct GFLIB_CONTROLLER_PI_P_T_F32 "\GFLIB_ControllerPIp.h" 

  @brief  Structure containing parameters and states of the parallel form PI controller.
  *//**********************************************************************/
  /* @remarks Implements DGFLIB00302 */
  typedef struct{
    tFrac32 f32PropGain;        /**< Proportional Gain, fractional format normalized to fit into (-\f$2^{31}\f$, \f$2^{31}\f$-1). */
    tFrac32 f32IntegGain;       /**< Integral Gain, fractional format normalized to fit into  (-\f$2^{31}\f$, \f$2^{31}\f$-1). */
    tS16 s16PropGainShift;      /**< Proportional Gain Shift, integer format [-31, 31]. */
    tS16 s16IntegGainShift;     /**< Integral Gain Shift, integer format [-31, 31]. */
    tFrac32 f32IntegPartK_1;    /**< State variable integral part at step k-1. */
    tFrac32 f32InK_1;           /**< State variable input error at step k-1. */
  }GFLIB_CONTROLLER_PI_P_T_F32;

/****************************************************************************
* Exported function prototypes
****************************************************************************/
  extern void GFLIB_ControllerPIpInit_F32(GFLIB_CONTROLLER_PI_P_T_F32 *const pParam);
  extern void GFLIB_ControllerPIpSetState_F32(tFrac32 f32ControllerPIpOut,GFLIB_CONTROLLER_PI_P_T_F32 *const pParam);
  extern tFrac32 GFLIB_ControllerPIp_F32(tFrac32 f32InErr,GFLIB_CONTROLLER_PI_P_T_F32 *const pParam);
#endif /* SWLIBS_SUPPORT_F32 == SWLIBS_STD_ON */




/****************************************************************************
* Implementation variant: 16-bit fractional
****************************************************************************/
#if (SWLIBS_SUPPORT_F16 == SWLIBS_STD_ON)
  #define GFLIB_CONTROLLER_PI_P_DEFAULT_F16 {(tFrac16)0,(tFrac16)0,(tS16)0,(tS16)0,(tFrac32)0,(tFrac16)0}     /**< Default value for GFLIB_CONTROLLER_PI_P_T_F16. */

  /************************************************************************/
  /**
  @struct GFLIB_CONTROLLER_PI_P_T_F16 "\GFLIB_ControllerPIp.h" 

  @brief  Structure containing parameters and states of the parallel form PI controller.
  *//**********************************************************************/
  /* @remarks Implements DGFLIB00302 */
  typedef struct{
    tFrac16 f16PropGain;        /**< Proportional Gain, fractional format normalized to fit into (-\f$2^{15}\f$, \f$2^{15}\f$-1). */
    tFrac16 f16IntegGain;       /**< Integral Gain, fractional format normalized to fit into  (-\f$2^{15}\f$, \f$2^{15}\f$-1). */
    tS16 s16PropGainShift;      /**< Proportional Gain Shift, integer format [-15, 15]. */
    tS16 s16IntegGainShift;     /**< Integral Gain Shift, integer format [-15, 15]. */
    tFrac32 f32IntegPartK_1;    /**< State variable integral part at step k-1. */
    tFrac16 f16InK_1;           /**< State variable input error at step k-1. */
  }GFLIB_CONTROLLER_PI_P_T_F16;

/****************************************************************************
* Exported function prototypes
****************************************************************************/
  extern void GFLIB_ControllerPIpInit_F16(GFLIB_CONTROLLER_PI_P_T_F16 *const pParam);
  extern void GFLIB_ControllerPIpSetState_F16(tFrac16 f16ControllerPIpOut,GFLIB_CONTROLLER_PI_P_T_F16 *const pParam);
  extern tFrac16 GFLIB_ControllerPIp_F16(tFrac16 f16InErr,GFLIB_CONTROLLER_PI_P_T_F16 *const pParam);
#endif /* SWLIBS_SUPPORT_F16 == SWLIBS_STD_ON */




/****************************************************************************
* Implementation variant: Single precision floating point
****************************************************************************/
#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
  #define GFLIB_CONTROLLER_PI_P_DEFAULT_FLT {(tFloat)0,(tFloat)0,(tFloat)0,(tFloat)0}     /**< Default value for GFLIB_CONTROLLER_PI_P_T_FLT. */

  /************************************************************************/
  /**
  @struct GFLIB_CONTROLLER_PI_P_T_FLT "\GFLIB_ControllerPIp.h" 

  @brief  Structure containing parameters and states of the parallel form PI controller.
  *//**********************************************************************/
  /* @remarks Implements DGFLIB00302 */
  typedef struct{
    tFloat fltPropGain;     /**< Proportional Gain, single precision floating point format. */
    tFloat fltIntegGain;    /**< Integral Gain, single precision floating point format. */
    tFloat fltIntegPartK_1; /**< State variable integral part at step k-1, single precision floating point format. */
    tFloat fltInK_1;        /**< State variable input error at step k-1, single precision floating point format. */
  }GFLIB_CONTROLLER_PI_P_T_FLT;

/****************************************************************************
* Exported function prototypes
****************************************************************************/
  extern void GFLIB_ControllerPIpInit_FLT(GFLIB_CONTROLLER_PI_P_T_FLT *const pParam);
  extern void GFLIB_ControllerPIpSetState_FLT(tFloat fltControllerPIpOut,GFLIB_CONTROLLER_PI_P_T_FLT *const pParam);
  extern tFloat GFLIB_ControllerPIp_FLT(tFloat fltInErr,GFLIB_CONTROLLER_PI_P_T_FLT *const pParam);
#endif /* SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON */
/****************************************************************************
* Inline functions
****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* GFLIB_CONTROLLERPIP_H */
