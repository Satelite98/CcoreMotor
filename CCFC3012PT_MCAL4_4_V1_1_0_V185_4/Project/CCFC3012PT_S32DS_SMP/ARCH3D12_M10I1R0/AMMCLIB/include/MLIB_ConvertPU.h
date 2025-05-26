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
* @file       MLIB_ConvertPU.h
*
* @brief      Header file for MLIB_ConvertPU function
*
******************************************************************************/
#ifndef MLIB_CONVERTPU_H
#define MLIB_CONVERTPU_H
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
  #include "MLIB_Mul.h"
  #include "MLIB_ShR.h"
  #include "MLIB_Div.h"
#else
  /* Following includes serve for NXP internal testing purposes only. 
  *  These headers are not part of the release. */
  #include "CCOV_MLIB_ShL.h"
  #include "CCOV_MLIB_Mul.h"
  #include "CCOV_MLIB_ShR.h"
  #include "CCOV_MLIB_Div.h"
#endif

/****************************************************************************
* Defines and macros            (scope: module-local)
****************************************************************************/
#if (!(defined(__MINGW32__) || defined(__MINGW64__) || defined(_MSC_VER) || defined(_MATLAB_BAM_CREATE)))
  #define MLIB_ConvertPU(...)     macro_dispatcher(MLIB_ConvertPU, __VA_ARGS__)(__VA_ARGS__)     /* This function converts the input value to different representation with scale. */

  #define MLIB_ConvertPU_Dsptchr_2(In,Impl)    MLIB_ConvertPU_Dsptchr_(In,Impl)     /* Function dispatcher for MLIB_ConvertPU_Dsptchr_2, do not modify!!! */
  
  /* @remarks Implements DMLIB00252*/
  #define MLIB_ConvertPU_Dsptchr_(In,Impl)     MLIB_ConvertPU_##Impl(In)            /* Function dispatcher for MLIB_ConvertPU_Dsptchr_, do not modify!!! */
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
/* C implementation */
SWLIBS_INLINE tFrac32 ConvertPU_F32F16_C(register tFrac16 f16In)
{
  return((tFrac32)((tFrac32)f16In << ((tU16)16)));
}
#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/* C implementation */
SWLIBS_INLINE tFrac32 ConvertPU_F32FLT_C(register tFloat fltIn)
{
  return((fltIn>=1.0f) ? (tFrac32)SWLIBS_INT32_MAX : ((fltIn<-1.0f) ? (tFrac32)SWLIBS_INT32_MIN : ((tFrac32)(fltIn * 2147483648.0f))));
}
#ifdef MLIB_EFPU2_ASM
  #ifdef __ghs__
    #pragma ghs static_call 0
    #pragma ghs extra_stack 0
  #endif
  /* Target-specific implementation */
  SWLIBS_INLINE tFrac32 ConvertPU_F32FLT_ASM_EFPU2(register tFloat fltIn)
  {
    tFrac32 f32Return;
    #ifdef __ghs__
      #pragma ghs optasm
    #endif
    SWLIBS_ASM(" efsctsf %0,%1": "=r"(f32Return): "r"(fltIn));
    return((tFrac32)f32Return);
  }
#endif /* MLIB_EFPU2_ASM */
#endif /* SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON */
/* C implementation */
SWLIBS_INLINE tFrac16 ConvertPU_F16F32_C(register tFrac32 f32In)
{
  return((tFrac16)(f32In >> ((tU16)16)));
}
#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/* C implementation */
SWLIBS_INLINE tFrac16 ConvertPU_F16FLT_C(register tFloat fltIn)
{
  return((fltIn>=1.0f) ? (tFrac16)SWLIBS_INT16_MAX : ((fltIn<-1.0f) ? (tFrac16)SWLIBS_INT16_MIN : ((tFrac16)(fltIn * (((tFloat)SWLIBS_INT16_MAX)+1.0f)))));
}
#ifdef MLIB_EFPU2_ASM
  #ifdef __ghs__
    #pragma ghs static_call 0
    #pragma ghs extra_stack 0
  #endif
  /* Target-specific implementation */
  SWLIBS_INLINE tFrac16 ConvertPU_F16FLT_ASM_EFPU2(register tFloat fltIn)
  {
    tFrac32 f32Tmp;
    tFrac16 f16Return;
    #ifdef __ghs__
      #pragma ghs optasm
    #endif
    SWLIBS_ASM(" efsctsf %0,%1": "=r"(f32Tmp): "r"(fltIn));
    #ifdef __ghs__
      #pragma ghs optasm
    #endif
    SWLIBS_ASM(" srawi %0,%1,%2": "=r"(f16Return): "r"(f32Tmp), "I"(16));
    return((tFrac16)f16Return);
  }  
#endif /* MLIB_EFPU2_ASM */
#endif /* SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON */
#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/* C implementation */
SWLIBS_INLINE tFloat ConvertPU_FLTF16_C(register tFrac16 f16In)
{
  return(MLIB_Mul_FLT((tFloat)f16In,3.0517578e-5f));
}
#ifdef MLIB_EFPU2_ASM
  #ifdef __ghs__
    #pragma ghs static_call 0
    #pragma ghs extra_stack 0
  #endif
  /* Target-specific implementation */
  SWLIBS_INLINE tFloat ConvertPU_FLTF16_ASM_EFPU2(register tFrac16 f16In)
  {
    tFloat fltReturn;
    tFrac32 f32Tmp;
    f32Tmp = MLIB_ShL_F32((tFrac32)f16In, 16u);
    #ifdef __ghs__
      #pragma ghs optasm
    #endif
    SWLIBS_ASM(" efscfsf %0,%1": "=r"(fltReturn): "r"(f32Tmp));
    return((tFloat)fltReturn);
  }  
#endif /* MLIB_EFPU2_ASM */
#endif /* SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON */
#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/* C implementation */
SWLIBS_INLINE tFloat ConvertPU_FLTF32_C(register tFrac32 f32In)
{
  return(MLIB_Mul_FLT((tFloat)f32In,4.6566129e-10f));
}
#ifdef MLIB_EFPU2_ASM
  #ifdef __ghs__
    #pragma ghs static_call 0
    #pragma ghs extra_stack 0
  #endif
  /* Target-specific implementation */
  SWLIBS_INLINE tFloat ConvertPU_FLTF32_ASM_EFPU2(register tFrac32 f32In)
  {
    tFloat fltReturn;
    #ifdef __ghs__
      #pragma ghs optasm
    #endif
    SWLIBS_ASM(" efscfsf %0,%1": "=r"(fltReturn): "r"(f32In));
    return((tFloat)fltReturn);
  }  
#endif /* MLIB_EFPU2_ASM */
#endif /* SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON */





/****************************************************************************
* Implementation variant: 32-bit fractional
****************************************************************************/
/***************************************************************************/
/**
@ingroup    MLIB_GROUP

@functionality MLIB_ConvertPU

@param[in]    f16In     Input value in 16-bit fractional format to be converted.

@return       Converted input value in 32-bit fractional format.

@details      The input value is considered as 16-bit fractional data type and output value is
              considered as 32-bit fractional data type.

              \par
              
              The output of the function is defined by the following simple equation:
              \anchor eq1_ConvertPU_F32F16
              \image rtf convertpuF32F16Eq1.math "MLIB_ConvertPU_F32F16_Eq1"

*/
/**
@note         This function is implemented as inline, and thus is not ANSI-C compliant.
*/
/**

@par Code Example
\code
#include "mlib.h"

tFrac16 f16In;
tFrac32 f32Out;

void main(void)
{
    // input value = 0.25 = 0x2000
    f16In = FRAC16(0.25);

    // output should be FRAC32(0.25) = 0x20000000
    f32Out = MLIB_ConvertPU_F32F16(f16In);

    // output should be FRAC32(0.25) = 0x20000000
    f32Out = MLIB_ConvertPU(f16In, F32F16);
}
\endcode
****************************************************************************/
/* @remarks Implements DMLIB00251, DMLIB00247, DMLIB00250 */
SWLIBS_INLINE tFrac32 MLIB_ConvertPU_F32F16(register tFrac16 f16In)
{
  /* @remarks Implements DMLIB00247 */
  return(ConvertPU_F32F16_C(f16In));
}





#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/***************************************************************************/
/**
@ingroup    MLIB_GROUP

@functionality MLIB_ConvertPU

@param[in]    fltIn     Input value in single precision floating point format to be converted.

@return       Converted input value in 32-bit fractional format.

@details      The input value is considered as single precision floating point data type and output
              value is considered as 32-bit fractional data type. The output saturation is
              implemented in this function, thus in case the input value is outside the [-1, 1)
              interval, the output value is limited to the boundary value.

              \par

              The output of the function is defined by the following simple equation:
              \anchor eq1_ConvertPU_F32FLT
              \image rtf convertpuF32FLTEq1.math "MLIB_ConvertPU_F32FLT_Eq1"

*/
/**
@note         The function may raise floating-point exceptions (floating-point
              inexact, invalid operation).
*/
/**
@note         This function is implemented as inline assembly,
              and thus is not ANSI-C compliant.
*/
/**

@par Code Example
\code
#include "mlib.h"

tFloat fltIn;
tFrac32 f32Out;

void main(void)
{
    // input value = 0.25
    fltIn = (tFloat)0.25;

    // output should be FRAC32(0.25) = 0x20000000
    f32Out = MLIB_ConvertPU_F32FLT(fltIn);

    // output should be FRAC32(0.25) = 0x20000000
    f32Out = MLIB_ConvertPU(fltIn, F32FLT);
}
\endcode
****************************************************************************/
/* @remarks Implements DMLIB00251, DMLIB00248, DMLIB00250 */
SWLIBS_INLINE tFrac32 MLIB_ConvertPU_F32FLT(register tFloat fltIn)
{
  #ifdef __ghs__
    /* @remarks Implements DMLIB00248 */
    return(ConvertPU_F32FLT_ASM_EFPU2(fltIn));
  #elif defined(__GNUC__) && defined(__PPC_EABI__)
    /* @remarks Implements DMLIB00248 */
    return(ConvertPU_F32FLT_ASM_EFPU2(fltIn));
  #else
    /* @remarks Implements DMLIB00248 */
    return(ConvertPU_F32FLT_C(fltIn));
  #endif
}





#endif /* SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON */
/****************************************************************************
* Implementation variant: 16-bit fractional
****************************************************************************/
/***************************************************************************/
/**
@ingroup    MLIB_GROUP

@functionality MLIB_ConvertPU

@param[in]    f32In     Input value in 32-bit fractional format to be converted.

@return       Converted input value in 16-bit fractional format.

@details      The input value is considered as 32-bit fractional data type and output value is
              considered as 16-bit fractional data type.

              \par

              The output of the function is defined by the following simple equation:
              \anchor eq1_ConvertPU_F16F32
              \image rtf convertpuF16F32Eq1.math "MLIB_ConvertPU_F16F32_Eq1"

*/
/**
@note         This function is implemented as inline, and thus is not ANSI-C compliant.
*/
/**

@par Code Example
\code
#include "mlib.h"

tFrac32 f32In;
tFrac16 f16Out;

void main(void)
{
    // input value = 0.25 = 0x2000 0000
    f32In = FRAC32(0.25);

    // output should be FRAC16(0.25) = 0x2000
    f16Out = MLIB_ConvertPU_F16F32(f32In);

    // output should be FRAC16(0.25) = 0x2000
    f16Out = MLIB_ConvertPU(f32In, F16F32);
}
\endcode
****************************************************************************/
/* @remarks Implements DMLIB00251, DMLIB00244, DMLIB00250 */
SWLIBS_INLINE tFrac16 MLIB_ConvertPU_F16F32(register tFrac32 f32In)
{
  /* @remarks Implements DMLIB00244 */
  return(ConvertPU_F16F32_C(f32In));
}





#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/***************************************************************************/
/**
@ingroup    MLIB_GROUP

@functionality MLIB_ConvertPU

@param[in]    fltIn     Input value in single precision floating point format to be converted.

@return       Converted input value in 16-bit fractional format.

@details      The input value is considered as single precision floating  point data type and output
              value is considered as 16-bit fractional data type. The output saturation is
              implemented in this function, thus in case the input value is outside the [-1, 1)
              interval, the output value is limited to the boundary value.

              \par

              The output of the function is defined by the following simple equation:
              \anchor eq1_ConvertPU_F16FLT
              \image rtf convertpuF16FLTEq1.math "MLIB_ConvertPU_F16FLT_Eq1"

*/
/**
@note         The function may raise floating-point exceptions (floating-point
              inexact, invalid operation).
*/
/**
@note         This function is implemented as inline assembly,
              and thus is not ANSI-C compliant.
*/
/**

@par Code Example
\code
#include "mlib.h"

tFloat fltIn;
tFrac16 f16Out;

void main(void)
{
    // input value = 0.25
    fltIn = (tFloat)0.25;

    // output should be FRAC16(0.25) = 0x2000
    f16Out = MLIB_ConvertPU_F16FLT(fltIn);

    // output should be FRAC16(0.25) = 0x2000
    f16Out = MLIB_ConvertPU(fltIn, F16FLT);
}
\endcode
****************************************************************************/
/* @remarks Implements DMLIB00251, DMLIB00249, DMLIB00250 */
SWLIBS_INLINE tFrac16 MLIB_ConvertPU_F16FLT(register tFloat fltIn)
{
  #ifdef __ghs__
    /* @remarks Implements DMLIB00249 */
    return(ConvertPU_F16FLT_ASM_EFPU2(fltIn));
  #elif defined(__GNUC__) && defined(__PPC_EABI__)
    /* @remarks Implements DMLIB00249 */
    return(ConvertPU_F16FLT_ASM_EFPU2(fltIn));
  #else
    /* @remarks Implements DMLIB00249 */
    return(ConvertPU_F16FLT_C(fltIn));
  #endif
}





#endif /* SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON */
#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/****************************************************************************
* Implementation variant: Single precision floating point
****************************************************************************/
/***************************************************************************/
/**
@ingroup    MLIB_GROUP

@functionality MLIB_ConvertPU

@param[in]    f16In     Input value in 16-bit fractional format to be converted.

@return       Converted input value in single precision floating point format.

@details      The input value is considered as 16-bit fractional data type and output value is
              considered as single precision floating point data type. The output saturation is not
              implemented in this function.

              \par

              The output of the function is defined by the following simple equation:
              \anchor eq1_ConvertPU_FLTF16
              \image rtf convertpuFLTF16Eq1.math "MLIB_ConvertPU_FLTF16_Eq1"

*/
/**
@note         The function may raise floating-point exceptions (floating-point
              inexact, invalid operation).
*/
/**
@note         This function is implemented as inline assembly,
              and thus is not ANSI-C compliant.
*/
/**

@par Code Example
\code
#include "mlib.h"

tF16 f16In;
tFloat fltOut;

void main(void)
{
    // input value = 0.25 = 0x2000
    f16In = FRAC16(0.25);

    // output should be 0.25
    fltOut = MLIB_ConvertPU_FLTF16(f16In);

    // output should be 0.25
    fltOut = MLIB_ConvertPU(f16In, FLTF16);
}
\endcode
****************************************************************************/
/* @remarks Implements DMLIB00251, DMLIB00246, DMLIB00250 */
SWLIBS_INLINE tFloat MLIB_ConvertPU_FLTF16(register tFrac16 f16In)
{
  #ifdef __ghs__
    /* @remarks Implements DMLIB00246 */
    return(ConvertPU_FLTF16_ASM_EFPU2(f16In));
  #elif defined(__GNUC__) && defined(__PPC_EABI__)
    /* @remarks Implements DMLIB00246 */
    return(ConvertPU_FLTF16_ASM_EFPU2(f16In));
  #else
    /* @remarks Implements DMLIB00246 */
    return(ConvertPU_FLTF16_C(f16In));
  #endif
}





#endif /* SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON */
#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/***************************************************************************/
/**
@ingroup    MLIB_GROUP

@functionality MLIB_ConvertPU

@param[in]    f32In     Input value in 32-bit fractional format to be converted.

@return       Converted input value in single precision floating point format.

@details      The input value is considered as 32-bit fractional data type and output value is
              considered as single precision floating point data type. The output saturation is not
              implemented in this function.

              \par

              The output of the function is defined by the following simple equation:
              \anchor eq1_ConvertPU_FLTF32
              \image rtf convertpuFLTF32Eq1.math "MLIB_ConvertPU_FLTF32_Eq1"

*/
/**
@note         The function may raise floating-point exceptions (floating-point
              inexact, invalid operation).
*/
/**
@note         This function is implemented as inline assembly,
              and thus is not ANSI-C compliant.
*/
/**

@par Code Example
\code
#include "mlib.h"

tF32 f32In;
tFloat fltOut;

void main(void)
{
    // input value = 0.25 = 0x20000000
    f32In = FRAC32(0.25);

    // output should be 0.25
    fltOut = MLIB_ConvertPU_FLTF32(f32In);

    // output should be 0.25
    fltOut = MLIB_ConvertPU(f32In, FLTF32);
}
\endcode
****************************************************************************/
/* @remarks Implements DMLIB00251, DMLIB00245, DMLIB00250 */
SWLIBS_INLINE tFloat MLIB_ConvertPU_FLTF32(register tFrac32 f32In)
{
  #ifdef __ghs__
    /* @remarks Implements DMLIB00245 */
    return(ConvertPU_FLTF32_ASM_EFPU2(f32In));
  #elif defined(__GNUC__) && defined(__PPC_EABI__)
    /* @remarks Implements DMLIB00245 */
    return(ConvertPU_FLTF32_ASM_EFPU2(f32In));
  #else
    /* @remarks Implements DMLIB00245 */
    return(ConvertPU_FLTF32_C(f32In));
  #endif
}


#endif /* SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON */
#ifdef __cplusplus
}
#endif

#endif /* MLIB_CONVERTPU_H */
