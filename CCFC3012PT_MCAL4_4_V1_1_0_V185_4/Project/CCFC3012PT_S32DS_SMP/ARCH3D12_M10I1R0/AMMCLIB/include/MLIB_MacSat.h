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
* @file       MLIB_MacSat.h
*
* @brief      Header file for MLIB_MacSat function
*
******************************************************************************/
#ifndef MLIB_MACSAT_H
#define MLIB_MACSAT_H
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
  #include "MLIB_AddSat.h"
  #include "MLIB_MulSat.h"
  #include "MLIB_ConvertPU.h"
#else
  /* Following includes serve for NXP internal testing purposes only. 
  *  These headers are not part of the release. */
  #include "CCOV_MLIB_AddSat.h"
  #include "CCOV_MLIB_MulSat.h"
  #include "CCOV_MLIB_ConvertPU.h"
#endif

/****************************************************************************
* Defines and macros            (scope: module-local)
****************************************************************************/
#if (!(defined(__MINGW32__) || defined(__MINGW64__) || defined(_MSC_VER) || defined(_MATLAB_BAM_CREATE)))
  #define MLIB_MacSat(...)     macro_dispatcher(MLIB_MacSat, __VA_ARGS__)(__VA_ARGS__)     /* This function implements the multiply accumulate function saturated if necessary. */

  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_F32)
    /* @remarks Implements DMLIB00227 */
    #define MLIB_MacSat_Dsptchr_3(In1,In2,In3)     MLIB_MacSat_Dsptchr_4(In1,In2,In3,F32)     /* Function dispatcher for MLIB_MacSat_Dsptchr_4, do not modify!!! */
  #endif 
  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_F16)
    /* @remarks Implements DMLIB00227 */
    #define MLIB_MacSat_Dsptchr_3(In1,In2,In3)     MLIB_MacSat_Dsptchr_4(In1,In2,In3,F16)     /* Function dispatcher for MLIB_MacSat_Dsptchr_4, do not modify!!! */
  #endif 

  #define MLIB_MacSat_Dsptchr_4(In1,In2,In3,Impl)    MLIB_MacSat_Dsptchr_(In1,In2,In3,Impl)     /* Function dispatcher for MLIB_MacSat_Dsptchr_5, do not modify!!! */
  
  /* @remarks Implements DMLIB00229 */
  #define MLIB_MacSat_Dsptchr_(In1,In2,In3,Impl)     MLIB_MacSat_##Impl(In1,In2,In3)            /* Function dispatcher for MLIB_MacSat_Dsptchr_, do not modify!!! */
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
/* C implementation */
SWLIBS_INLINE tFrac32 MacSat_F32_C(register tFrac32 f32In1,register tFrac32 f32In2,register tFrac32 f32In3)
{
  return(MLIB_AddSat_F32(f32In1, MLIB_MulSat_F32(f32In2, f32In3)));
} 
/* C implementation */
SWLIBS_INLINE tFrac32 MacSat_F32F16F16_C(register tFrac32 f32In1,register tFrac16 f16In2,register tFrac16 f16In3)
{
  return(MLIB_AddSat_F32(f32In1, MLIB_MulSat_F32F16F16(f16In2,f16In3)));
}
#ifdef MLIB_LSP
  #if (!(defined(__GNUC__) && defined(__PPC_EABI__)))
  #ifdef __ghs__
    #pragma ghs static_call 0
    #pragma ghs extra_stack 0
  #endif
    /* Target-specific implementation */
    SWLIBS_INLINE tFrac32 MacSat_F32_ITR_LSP(register tFrac32 f32In1,register tFrac32 f32In2,register tFrac32 f32In3)
    {
      return((tFrac32)__zmwsfaas((__lsp32_32__)f32In1, (__lsp32_32__)f32In2, (__lsp32_32__)f32In3));
    }
  #endif /* (!(defined(__GNUC__) && defined(__PPC_EABI__))) */
  #if (!(defined(__GNUC__) && defined(__PPC_EABI__)))
  #ifdef __ghs__
    #pragma ghs static_call 0
    #pragma ghs extra_stack 0
  #endif
    /* Target-specific implementation */
    SWLIBS_INLINE tFrac32 MacSat_F32F16F16_ITR_LSP(register tFrac32 f32In1,register tFrac16 f16In2,register tFrac16 f16In3)
    {
      return((tFrac32)__zmhosfaas((__lsp32_32__)f32In1, (__lsp32_16__)f16In2, (__lsp32_16__)f16In3));
    }
  #endif /* (!(defined(__GNUC__) && defined(__PPC_EABI__))) */
  #if defined(__GNUC__) && defined(__PPC_EABI__)
    /* MLIB_MacSat_F32 implementation variant - LSP assembly for S32DS for Power Architecture toolchain */
    SWLIBS_INLINE tFrac32 MacSat_F32_S32DSPPC_LSP(register tFrac32 f32In1,register tFrac32 f32In2,register tFrac32 f32In3)
    {
      register tFrac32 f32Return;
      f32Return = f32In1;
      SWLIBS_ASM(" zmwsfaas %0,%1,%2": "+r"(f32Return): "r"(f32In2), "r"(f32In3));
      return((tFrac32)f32Return);
    }
    /* MLIB_MacSat_F32F16F16 implementation variant - LSP assembly for S32DS for Power Architecture toolchain */
    SWLIBS_INLINE tFrac32 MacSat_F32F16F16_S32DSPPC_LSP(register tFrac32 f32In1,register tFrac16 f16In2,register tFrac16 f16In3)
    {
      register tFrac32 f32Return;
      f32Return = f32In1;
      SWLIBS_ASM(" zmhosfaas %0,%1,%2": "+r"(f32Return): "r"(f16In2), "r"(f16In3));
      return((tFrac32)f32Return);
    }
  #endif
#endif

/* C implementation */
SWLIBS_INLINE tFrac16 MacSat_F16_C(register tFrac16 f16In1,register tFrac16 f16In2,register tFrac16 f16In3)
{
  return(MLIB_ConvertPU_F16F32(MLIB_AddSat_F32(MLIB_ConvertPU_F32F16(f16In1), MLIB_MulSat_F32F16F16(f16In2,f16In3))));
}
#ifdef MLIB_LSP
  #if (!(defined(__GNUC__) && defined(__PPC_EABI__)))
  #ifdef __ghs__
    #pragma ghs static_call 0
    #pragma ghs extra_stack 0
  #endif
    /* Target-specific implementation */
    SWLIBS_INLINE tFrac16 MacSat_F16_ITR_LSP(register tFrac16 f16In1,register tFrac16 f16In2,register tFrac16 f16In3)
    {
      tFrac32 f32Temp;
      
      f32Temp = MLIB_ConvertPU_F32F16(f16In1);
      /* Compiler_Warning: This is side effect of non static inline usage. */
      return((tFrac16)__lsp_extract_upper_hword((__lsp32_16__)__zmhosfaas((__lsp32_32__)f32Temp, (__lsp32_32__)f16In2, (__lsp32_32__)f16In3)));
    }
  #endif /* (!(defined(__GNUC__) && defined(__PPC_EABI__))) */
  #if defined(__GNUC__) && defined(__PPC_EABI__)
    /* MLIB_MacSat_F16 implementation variant - LSP assembly for S32DS for Power Architecture toolchain */
    SWLIBS_INLINE tFrac16 MacSat_F16_S32DSPPC_LSP(register tFrac16 f16In1,register tFrac16 f16In2,register tFrac16 f16In3)
    {
      tFrac32 f32Return;
      
      f32Return = MLIB_ConvertPU_F32F16(f16In1);
      SWLIBS_ASM(" zmhosfaas %0,%1,%2": "+r"(f32Return): "r"(f16In2), "r"(f16In3));
      SWLIBS_ASM(" srawi %0,%1,16": "=r"(f32Return): "r"(f32Return));
      SWLIBS_ASM(" extsh %0,%1": "=r"(f32Return): "r"(f32Return));
      return((tFrac16)f32Return);
    }
  #endif
#endif


/****************************************************************************
* Implementation variant: 32-bit fractional
****************************************************************************/
/***************************************************************************/
/**
@ingroup    MLIB_GROUP

@functionality MLIB_MacSat

@param[in]    f32In1     Input value to be add.

@param[in]    f32In2     First value to be multiplied.

@param[in]    f32In3     Second value to be multiplied.

@return       Multiplied second and third input value with adding of first input value. The output value is saturated
              if necessary.

@details      The input values as well as output value is considered as 32-bit fractional 
              values.

              \par

              The output of the function is defined by the following simple equation:
              \anchor eq1_MacSat_F32
              \image rtf macsatF32Eq1.math "MLIB_MacSat_F32_Eq1"

*/
/**
@note         This function is implemented as inline assembly and thus is not ANSI-C compliant.
*/
/**

@par Code Example
\code
#include "mlib.h"

tFrac32 f32In1;
tFrac32 f32In2;
tFrac32 f32In3;
tFrac32 f32Out;

void main(void)
{
  // input1 value = 0.25
  f32In1  = FRAC32(0.25);

  // input2 value = 0.15
  f32In2  = FRAC32(0.15);

  // input3 value = 0.35
  f32In3  = FRAC32(0.35);

  // output should be FRAC32(0.3025) = 0x26B851EB
  f32Out = MLIB_MacSat_F32(f32In1, f32In2, f32In3);

  // output should be FRAC32(0.3025) = 0x26B851EB
  f32Out = MLIB_MacSat(f32In1, f32In2, f32In3, F32);

  // ##############################################################
  // Available only if 32-bit fractional implementation selected
  // as default
  // ##############################################################

  // output should be FRAC32(0.3025) = 0x26B851EB
  f32Out = MLIB_MacSat(f32In1, f32In2, f32In3);
}
\endcode
****************************************************************************/
/* @remarks Implements DMLIB00228, DMLIB00220, DMLIB00223, DMLIB00226 */
SWLIBS_INLINE tFrac32 MLIB_MacSat_F32(register tFrac32 f32In1,register tFrac32 f32In2,register tFrac32 f32In3)
{
  #ifdef MLIB_LSP
    #if defined(__GNUC__) && defined(__PPC_EABI__)
      /* @remarks Implements DMLIB00224, DMLIB00231 */
      return(MacSat_F32_S32DSPPC_LSP(f32In1,f32In2,f32In3));
    #else
      /* @remarks Implements DMLIB00224, DMLIB00231 */
      return(MacSat_F32_ITR_LSP(f32In1,f32In2,f32In3));
    #endif
  #else
    /* @remarks Implements DMLIB00224, DMLIB00231 */
    return(MacSat_F32_C(f32In1,f32In2,f32In3));
  #endif
}





/***************************************************************************/
/**
@ingroup    MLIB_GROUP

@functionality MLIB_MacSat

@param[in]    f32In1     Input value to be add.

@param[in]    f16In2     First value to be multiplied.

@param[in]    f16In3     Second value to be multiplied.

@return       Multiplied second and third input value with adding of first input value. The output value is saturated
              if necessary.

@details      The first input values as well as output value is considered as 32-bit fractional
              values, second and third input values are considered as 16-bit fractional values.

              \par

              The output of the function is defined by the following simple equation:
              \anchor eq1_MacSat_F32F16F16
              \image rtf macsatF32F16F16Eq1.math "MLIB_MacSat_F32F16F16_Eq1"

*/
/**
@note         This function is implemented as inline assembly and thus is not ANSI-C compliant.
*/
/**

@par Code Example
\code
#include "mlib.h"

tFrac32 f32In1;
tFrac16 f16In2;
tFrac16 f16In3;
tFrac32 f32Out;

void main(void)
{
  // input1 value = 0.25
  f32In1 = FRAC32(0.25);

  // input2 value = 0.15
  f16In2 = FRAC16(0.15);

  // input3 value = 0.35
  f16In3 = FRAC16(0.35);

  // output should be FRAC32(0.3025) = 0x26B851EB
  f32Out = MLIB_MacSat_F32F16F16(f32In1, f16In2, f16In3);

  // output should be FRAC32(0.3025) = 0x26B851EB
  f32Out = MLIB_MacSat(f32In1, f16In2, f16In3, F32F16F16);
}
\endcode
****************************************************************************/
/* @remarks Implements DMLIB00228, DMLIB00220, DMLIB00225, DMLIB00226 */
SWLIBS_INLINE tFrac32 MLIB_MacSat_F32F16F16(register tFrac32 f32In1,register tFrac16 f16In2,register tFrac16 f16In3)
{
  #ifdef MLIB_LSP
    #if defined(__GNUC__) && defined(__PPC_EABI__)
      /* @remarks Implements DMLIB00224, DMLIB00231 */
      return(MacSat_F32F16F16_S32DSPPC_LSP(f32In1,f16In2,f16In3));
    #else
      /* @remarks Implements DMLIB00224, DMLIB00231 */
      return(MacSat_F32F16F16_ITR_LSP(f32In1,f16In2,f16In3));
    #endif
  #else
    /* @remarks Implements DMLIB00224, DMLIB00231 */
    return(MacSat_F32F16F16_C(f32In1,f16In2,f16In3));
  #endif
}





/****************************************************************************
* Implementation variant: 16-bit fractional
****************************************************************************/
/***************************************************************************/
/**
@ingroup    MLIB_GROUP

@functionality MLIB_MacSat

@param[in]    f16In1     Input value to be add.

@param[in]    f16In2     First value to be multiplied.

@param[in]    f16In3     Second value to be multiplied.

@return       Multiplied second and third input value with adding of first input value. The output value is saturated
              if necessary.

@details      The input values as well as output value is considered as 16-bit fractional 
              values.

              \par

              The output of the function is defined by the following simple equation:
              \anchor eq1_MacSat_F16
              \image rtf macsatF16Eq1.math "MLIB_MacSat_F16_Eq1"

*/
/**
@note         This function is implemented as inline assembly and thus is not ANSI-C compliant.
*/
/**

@par Code Example
\code
#include "mlib.h"

tFrac16 f16In1;
tFrac16 f16In2;
tFrac16 f16In3;
tFrac16 f16Out;

void main(void)
{
  // input1 value = 0.25
  f16In1 = FRAC16(0.25);

  // input2 value = 0.15
  f16In2 = FRAC16(0.15);

  // input3 value = 0.35
  f16In3 = FRAC16(0.35);

  // output should be FRAC16(0.3025) = 0x26B8
  f16Out = MLIB_MacSat_F16(f16In1, f16In2, f16In3);

  // output should be FRAC16(0.3025) = 0x26B8
  f16Out = MLIB_MacSat(f16In1, f16In2, f16In3, F16);

  // ##############################################################
  // Available only if 16-bit fractional implementation selected
  // as default
  // ##############################################################

  // output should be FRAC16(0.3025) = 0x26B8
  f16Out = MLIB_MacSat(f16In1, f16In2, f16In3);
}
\endcode
****************************************************************************/
/* @remarks Implements DMLIB00228, DMLIB00222, DMLIB00220, DMLIB00226 */
SWLIBS_INLINE tFrac16 MLIB_MacSat_F16(register tFrac16 f16In1,register tFrac16 f16In2,register tFrac16 f16In3)
{
  #ifdef MLIB_LSP
    #if defined(__GNUC__) && defined(__PPC_EABI__)
      /* @remarks Implements DMLIB00224, DMLIB00232 */
      return(MacSat_F16_S32DSPPC_LSP(f16In1,f16In2,f16In3));
    #else
      #ifdef __DCC__
        /* Workaround for Wind River Diab compiler bug */
        /* @remarks Implements DMLIB00224, DMLIB00232 */
        return(MacSat_F16_C(f16In1,f16In2,f16In3));
      #else
        /* @remarks Implements DMLIB00224, DMLIB00232 */
        return(MacSat_F16_ITR_LSP(f16In1,f16In2,f16In3));
      #endif
    #endif
  #else
    /* @remarks Implements DMLIB00224, DMLIB00232 */
    return(MacSat_F16_C(f16In1,f16In2,f16In3));
  #endif
}


#ifdef __cplusplus
}
#endif /* ifdef __cplusplus */

#endif /* ifndef MLIB_MACSAT_H */
