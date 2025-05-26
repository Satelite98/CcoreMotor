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
* @file       MLIB_AbsSat.h
*
* @brief      Header file for MLIB_AbsSat function
*
******************************************************************************/
#ifndef MLIB_ABSSAT_H
#define MLIB_ABSSAT_H
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
  #include "MLIB_Abs.h"
  #include "MLIB_ShL.h"
  #include "MLIB_ShR.h"
#else
  /* Following include serves for NXP internal testing purposes only. 
  *  This header is not part of the release. */
  #include "CCOV_MLIB_Abs.h"
  #include "CCOV_MLIB_ShL.h"
  #include "CCOV_MLIB_ShR.h"
#endif

/****************************************************************************
* Defines and macros            (scope: module-local)
****************************************************************************/
#if (!(defined(__MINGW32__) || defined(__MINGW64__) || defined(_MSC_VER) || defined(_MATLAB_BAM_CREATE)))
  #define MLIB_AbsSat(...)     macro_dispatcher(MLIB_AbsSat, __VA_ARGS__)(__VA_ARGS__)     /* This function returns absolute value of input parameter and saturate if necessary. */

  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_F32)
    /* @remarks Implements DMLIB00015 */
    #define MLIB_AbsSat_Dsptchr_1(In)     MLIB_AbsSat_Dsptchr_2(In,F32)     /* Function dispatcher for MLIB_AbsSat_Dsptchr_1, do not modify!!! */
  #endif 
  #if (SWLIBS_DEFAULT_IMPLEMENTATION == SWLIBS_DEFAULT_IMPLEMENTATION_F16)
    /* @remarks Implements DMLIB00015 */
    #define MLIB_AbsSat_Dsptchr_1(In)     MLIB_AbsSat_Dsptchr_2(In,F16)     /* Function dispatcher for MLIB_AbsSat_Dsptchr_1, do not modify!!! */
  #endif 

  #define MLIB_AbsSat_Dsptchr_2(In,Impl)    MLIB_AbsSat_Dsptchr_(In,Impl)     /* Function dispatcher for MLIB_AbsSat_Dsptchr_2, do not modify!!! */
  
  /* @remarks Implements DMLIB00017 */
  #define MLIB_AbsSat_Dsptchr_(In,Impl)     MLIB_AbsSat_##Impl(In)            /* Function dispatcher for MLIB_AbsSat_Dsptchr_, do not modify!!! */
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
/* MLIB_AbsSat_F32 implementation variant - C */
/* C implementation */
SWLIBS_INLINE tFrac32 AbsSat_F32_C(register tFrac32 f32In)
{
  register tS32 s32Temp;
  
  s32Temp = F32TOINT32(f32In);
  if (s32Temp == SWLIBS_INT32_MIN){
    s32Temp = SWLIBS_INT32_MAX;  
  }
  return(MLIB_Abs_F32(INT32TOF32(s32Temp)));
}
#ifdef MLIB_LSP
  #if (!(defined(__GNUC__) && defined(__PPC_EABI__)))
  #ifdef __ghs__
    #pragma ghs static_call 0
    #pragma ghs extra_stack 0
  #endif
    /* Target-specific implementation */
    SWLIBS_INLINE tFrac32 AbsSat_F32_ITR_LSP(register tFrac32 f32In)
    {
      return((tFrac32)__zabsws((__lsp32_32__)f32In));
    }
  #endif /* (!(defined(__GNUC__) && defined(__PPC_EABI__))) */
  #if defined(__GNUC__) && defined(__PPC_EABI__)
    /* MLIB_AbsSat_F32 implementation variant - LSP assembly for S32DS for Power Architecture toolchain */
    SWLIBS_INLINE tFrac32 AbsSat_F32_S32DSPPC_LSP(register tFrac32 f32In)
    {
      register tFrac32 f32Return;
      SWLIBS_ASM(" zabsws %0,%1": "=r"(f32Return): "r"(f32In));
      return((tFrac32)f32Return);
    }
  #endif
#endif
#ifdef MLIB_ISEL
  #ifdef __ghs__
    #pragma ghs static_call 0
    #pragma ghs extra_stack 0
  #endif
  /* Target-specific implementation */
  SWLIBS_INLINE tFrac32 AbsSat_F32_ASM_ISEL(register tFrac32 f32In)
  {
    register tFrac32 f32Tmp1, f32Tmp2, f32Return, f32SatMax;

    f32SatMax = SWLIBS_INT32_MAX;
    #ifdef __ghs__
      #pragma ghs optasm
    #endif
    SWLIBS_ASM(" mcrxr 0" ::: "cc");  /* clear XER summary overflow flag */
    #ifdef __ghs__
      #pragma ghs optasm
    #endif
    SWLIBS_ASM(" nego. %0,%1": "=r"(f32Tmp2): "r"(f32In): "cc");
    #ifdef __ghs__
      #pragma ghs optasm
    #endif
    SWLIBS_ASM(" isel %0,%1,%2,0": "=r"(f32Tmp1): "b"(f32In), "b"(f32Tmp2): "cc");
    #ifdef __ghs__
      #pragma ghs optasm
    #endif
    SWLIBS_ASM(" isel %0,%1,%2,3": "=r"(f32Return): "b"(f32SatMax), "b"(f32Tmp1): "cc");
    return(f32Return);
  }
#endif /* ifdef MLIB_ISEL */
/* MLIB_AbsSat_F16 implementation variant - C */
/* C implementation */
SWLIBS_INLINE tFrac16 AbsSat_F16_C(register tFrac16 f16In)
{
  register tS16 s16Temp;

  s16Temp = F16TOINT16(f16In);
  if (s16Temp == SWLIBS_INT16_MIN){
    s16Temp = SWLIBS_INT16_MAX;
  }
  return(MLIB_Abs_F16(INT16TOF16(s16Temp)));
}
#ifdef MLIB_LSP
  #if (!(defined(__GNUC__) && defined(__PPC_EABI__)))
  #ifdef __ghs__
    #pragma ghs static_call 0
    #pragma ghs extra_stack 0
  #endif
    /* Target-specific implementation */
    SWLIBS_INLINE tFrac16 AbsSat_F16_ITR_LSP(register tFrac16 f16In)
    {
      /* Compiler_Warning: This is side effect of non static inline usage. */
      return((tFrac16)__lsp_extract_lower_hword(__zvabshs((__lsp32_16__)f16In)));
    }
  #endif /* (!(defined(__GNUC__) && defined(__PPC_EABI__))) */
  #if defined(__GNUC__) && defined(__PPC_EABI__)
    /* MLIB_AbsSat_F16 implementation variant - LSP assembly for S32DS for Power Architecture toolchain */
    SWLIBS_INLINE tFrac16 AbsSat_F16_S32DSPPC_LSP(register tFrac16 f16In)
    {
      register tFrac16 f16Return;
      SWLIBS_ASM(" zvabshs %0,%1": "=r"(f16Return): "r"(f16In));
      SWLIBS_ASM(" extsh %0,%1": "=r"(f16Return): "r"(f16Return));
      return((tFrac16)f16Return);
    }
  #endif
#endif





/****************************************************************************
* Implementation variant: 32-bit fractional
****************************************************************************/
/***************************************************************************/
/**
@ingroup    MLIB_GROUP

@functionality MLIB_AbsSat

@param[in]    f32In      Input value.

@return       Absolute value of input parameter, saturated if necessary.

@details      The input values as well as output value is considered as 32-bit fractional data 
              type.

              \par

              The output of the function is defined by the following simple equation:
              \anchor eq1_AbsSat_F32
              \image rtf abssatF32Eq1.math "MLIB_AbsSat_F32_Eq1"

*/
/**
@note         This function is implemented as inline assembly, and thus is not ANSI-C compliant.
*/
/**

@par Code Example
\code
#include "mlib.h"

tFrac32 f32In;
tFrac32 f32Out;

void main(void)
{
    // input value = -0.25
    f32In = FRAC32(-0.25);

    // output should be FRAC32(0.25)
    f32Out = MLIB_AbsSat_F32(f32In);

    // output should be FRAC32(0.25)
    f32Out = MLIB_AbsSat(f32In, F32);

    // ##############################################################
    // Available only if 32-bit fractional implementation selected
    // as default
    // ##############################################################

    // output should be FRAC32(0.25)
    f32Out = MLIB_AbsSat(f32In);
}
\endcode
****************************************************************************/
/* @remarks Implements DMLIB00016, DMLIB00010, DMLIB00012, DMLIB00014, DMLIB00019 */
SWLIBS_INLINE tFrac32 MLIB_AbsSat_F32(register tFrac32 f32In)
{
  #ifdef MLIB_LSP
    #if defined(__GNUC__) && defined(__PPC_EABI__)
      /* @remarks Implements DMLIB00013 */
      return(AbsSat_F32_S32DSPPC_LSP(f32In));
    #else
      /* @remarks Implements DMLIB00013 */
      return(AbsSat_F32_ITR_LSP(f32In));
    #endif
  #else
    #ifdef MLIB_ISEL
      /* @remarks Implements DMLIB00013 */
      return(AbsSat_F32_ASM_ISEL(f32In));
    #else
      /* @remarks Implements DMLIB00013 */
      return(AbsSat_F32_C(f32In));
    #endif
  #endif
}





/****************************************************************************
* Implementation variant: 16-bit fractional
****************************************************************************/
/***************************************************************************/
/**
@ingroup    MLIB_GROUP

@functionality MLIB_AbsSat

@param[in]    f16In      Input value.

@return       Absolute value of input parameter, saturated if necessary.

@details      The input values as well as output value is considered as 16-bit fractional data 
              type.

              \par

              The output of the function is defined by the following simple equation:
              \anchor eq1_AbsSat_F16
              \image rtf abssatF16Eq1.math "MLIB_AbsSat_F16_Eq1"

*/
/**
@note         This function is implemented as inline assembly, and thus is not ANSI-C compliant.
*/
/**

@par Code Example
\code
#include "mlib.h"

tFrac16 f16In;
tFrac16 f16Out;

void main(void)
{
    // input value = -0.25
    f16In = FRAC16(-0.25);

    // output should be FRAC16(0.25)
    f16Out = MLIB_AbsSat_F16(f16In);

    // output should be FRAC16(0.25)
    f16Out = MLIB_AbsSat(f16In, F16);

    // ##############################################################
    // Available only if 16-bit fractional implementation selected
    // as default
    // ##############################################################

    // output should be FRAC16(0.25)
    f16Out = MLIB_AbsSat(f16In);
}
\endcode
****************************************************************************/
/* @remarks Implements DMLIB00016, DMLIB00010, DMLIB00011, DMLIB00014, DMLIB00020 */
SWLIBS_INLINE tFrac16 MLIB_AbsSat_F16(register tFrac16 f16In)
{
  #ifdef MLIB_LSP
    #if defined(__GNUC__) && defined(__PPC_EABI__)
      /* @remarks Implements DMLIB00013 */
      return(AbsSat_F16_S32DSPPC_LSP(f16In));
    #else
      /* @remarks Implements DMLIB00013 */
      return(AbsSat_F16_ITR_LSP(f16In));
    #endif
  #else
    /* @remarks Implements DMLIB00013 */
    return(AbsSat_F16_C(f16In));
  #endif
}

#ifdef __cplusplus
}
#endif

#endif /* MLIB_ABSSAT_H */
