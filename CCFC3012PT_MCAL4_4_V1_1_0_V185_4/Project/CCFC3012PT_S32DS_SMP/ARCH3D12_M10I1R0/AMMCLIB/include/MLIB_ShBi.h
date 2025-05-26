/******************************************************************************
*
*   Copyright 2013-2015 Freescale Semiconductor
*   Copyright 2016-2024 NXP
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
* @file       MLIB_ShBi.h
*
* @brief      Header file for MLIB_ShBi function
*
******************************************************************************/
#ifndef MLIB_SHBI_H
#define MLIB_SHBI_H
/**
@if MLIB_GROUP
    @addtogroup MLIB_GROUP
@else
    @defgroup MLIB_GROUP   MLIB
@endif
*/

#ifdef __cplusplus
extern "C" {
#endif


#include "SWLIBS_Defines.h"
#ifndef AMMCLIB_TESTING_ENV
  #include "MLIB_ShL.h"
  #include "MLIB_ShR.h"
#else
  /* Following includes serve for NXP internal testing purposes only. 
  *  These headers are not part of the release. */
  #include "CCOV_MLIB_ShL.h"
  #include "CCOV_MLIB_ShR.h"
#endif

/****************************************************************************
* Defines and macros            (scope: module-local)
****************************************************************************/
#if (!(defined(__MINGW32__) || defined(__MINGW64__) || defined(_MSC_VER) || defined(_MATLAB_BAM_CREATE)))
  #define MLIB_ShBi(...)     macro_dispatcher(MLIB_ShBi, __VA_ARGS__)(__VA_ARGS__)    /* Based on sign of second parameter this function shifts the first parameter to right or left. If the sign of second parameter is negative, shift to right. */

  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_F32)
    /* @remarks Implements DMLIB00145 */
    #define MLIB_ShBi_Dsptchr_2(In1,In2)     MLIB_ShBi_Dsptchr_3(In1,In2,F32)     /* Function dispatcher for MLIB_ShBi_Dsptchr_2, do not modify!!! */
  #endif 
  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_F16)
    /* @remarks Implements DMLIB00145 */
    #define MLIB_ShBi_Dsptchr_2(In1,In2)     MLIB_ShBi_Dsptchr_3(In1,In2,F16)     /* Function dispatcher for MLIB_ShBi_Dsptchr_2, do not modify!!! */
  #endif 

  #define MLIB_ShBi_Dsptchr_3(In1,In2,Impl)    MLIB_ShBi_Dsptchr_(In1,In2,Impl)   /* Function dispatcher for MLIB_ShBi_Dsptchr_3, do not modify!!! */
  
  /* @remarks Implements DMLIB00147 */
  #define MLIB_ShBi_Dsptchr_(In1,In2,Impl)     MLIB_ShBi_##Impl(In1,In2)          /* Function dispatcher for MLIB_ShBi_Dsptchr_, do not modify!!! */
#endif /* if (!(defined(__MINGW32__) || defined(__MINGW64__) || defined(_MSC_VER) || defined(_MATLAB_BAM_CREATE))) */
 
/****************************************************************************
* Typedefs and structures       (scope: module-local)
****************************************************************************/

/****************************************************************************
* Exported function prototypes
****************************************************************************/

/****************************************************************************
* Inline functions
****************************************************************************/
/* MLIB_ShBi_F32 implementation variant - C */
/* C implementation */
SWLIBS_INLINE tFrac32 ShBi_F32_C(register tFrac32 f32In,register tS16 s16In)
{
  return(s16In<(tS16)0) ? MLIB_ShR_F32(f32In, (tU16)(-s16In)) : MLIB_ShL_F32(f32In, (tU16)(s16In));
}

/* MLIB_ShBi_F16 implementation variant - C */
/* C implementation */
SWLIBS_INLINE tFrac16 ShBi_F16_C(register tFrac16 f16In,register tS16 s16In)
{
  return (s16In<(tS16)0) ? MLIB_ShR_F16(f16In,(tU16)(-s16In)) : MLIB_ShL_F16(f16In,(tU16)(s16In));
}





/****************************************************************************
* Implementation variant: 32-bit fractional
****************************************************************************/
/***************************************************************************/
/**
@ingroup    MLIB_GROUP

@functionality MLIB_ShBi

@param[in]         f32In1     First value to be shift.

@param[in]         s16In2     The shift amount value.

@return       32-bit fractional value shifted to left or right by the shift amount.
              The bits beyond the 32-bit boundary are discarded.

*/
/**
@note         The shift amount cannot exceed in magnitude the bit-width of the
              shift value, that means must be within the range -31...31. Otherwise
              the result of the function is undefined.
              This function is implemented as inline,
              and thus is not ANSI-C compliant.
*/
/**

@par Code Example
\code
#include "mlib.h"

tFrac32 f32In1;
tFrac32 f32Out;
tS16 s16In2;

void main(void)
{
    // first input = 0.25
    f32In1 = FRAC32(0.25);
    // second input = -1
    s16In2 = (tS16)-1;

    // output should be 0x10000000 ~ FRAC32(0.125)
    f32Out = MLIB_ShBi_F32(f32In1, s16In2);

    // output should be 0x10000000 ~ FRAC32(0.125)
    f32Out = MLIB_ShBi(f32In1, s16In2, F32);

    // ##############################################################
    // Available only if 32-bit fractional implementation selected
    // as default
    // ##############################################################

    // output should be 0x10000000 ~ FRAC32(0.125)
    f32Out = MLIB_ShBi(f32In1, s16In2);
}
\endcode
****************************************************************************/
/* @remarks Implements DMLIB00146, DMLIB00140, DMLIB00144 */
SWLIBS_INLINE tFrac32 MLIB_ShBi_F32(register tFrac32 f32In1,register tS16 s16In2)
{
  /* @remarks Implements DMLIB00142, DMLIB00143 */
  return(ShBi_F32_C(f32In1,s16In2));
}





/****************************************************************************
* Implementation variant: 16-bit fractional
****************************************************************************/
/***************************************************************************/
/**
@ingroup    MLIB_GROUP

@functionality MLIB_ShBi

@param[in]         f16In1     First value to be left shift.

@param[in]         s16In2     The shift amount value.

@return       16-bit fractional value shifted to left or right by the shift amount.
              The bits beyond the 16-bit boundary are discarded.

*/
/**
@note         The shift amount cannot exceed in magnitude the bit-width of the
              shift value, that means must be within the range -15...15. Otherwise
              the result of the function is undefined.
              This function is implemented as inline,
              and thus is not ANSI-C compliant.
*/
/**

@par Code Example
\code
#include "mlib.h"

tFrac16 f16In1;
tFrac16 f16Out;
tS16 s16In2;

void main(void)
{
    // first input = 0.25
    f16In1 = FRAC16(0.25);
    // second input = -1
    s16In2 = (tS16)-1;

    // output should be 0x1000 ~ FRAC16(0.125)
    f16Out = MLIB_ShBi_F16(f16In1, s16In2);

    // output should be 0x1000 ~ FRAC16(0.125)
    f16Out = MLIB_ShBi(f16In1, s16In2, F16);

    // ##############################################################
    // Available only if 16-bit fractional implementation selected
    // as default
    // ##############################################################

    // output should be 0x1000 ~ FRAC16(0.125)
    f16Out = MLIB_ShBi(f16In1, s16In2);
}
\endcode
****************************************************************************/
/* @remarks Implements DMLIB00146, DMLIB00140, DMLIB00144 */
SWLIBS_INLINE tFrac16 MLIB_ShBi_F16(register tFrac16 f16In1,register tS16 s16In2)
{
  /* @remarks Implements DMLIB00141, DMLIB00143 */
  return(ShBi_F16_C(f16In1,s16In2));
}

#ifdef __cplusplus
}
#endif

#endif /* MLIB_SHBI_H */
