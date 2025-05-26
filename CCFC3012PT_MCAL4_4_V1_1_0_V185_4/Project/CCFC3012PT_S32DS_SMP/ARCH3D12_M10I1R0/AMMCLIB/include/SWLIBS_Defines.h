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
* @file     SWLIBS_Defines.h
*
* @brief    Defines and common Macros definition file.
*
*******************************************************************************
*
******************************************************************************/

#ifndef SWLIBS_DEFINES_H
#define SWLIBS_DEFINES_H


#include "SWLIBS_Typedefs.h"

/******************************************************************************
* Defines and macros            (scope: module-local)
******************************************************************************/
#ifdef __DCC__
  #define SUPPRESS_INTRINSIC_FUNCTIONS
#endif

#ifndef MLIB_LSP
/* Compiler support for LSP extension */
  #if ((defined(__ghs__) && (__LSP_APU__ == 1)) || (defined(__DCC__) && defined(__PPC_APU_LSP)) || ((defined(__GNUC__) && defined(__PPC_EABI__)) && (__LSP_APU__ == 1)))
    #ifdef __DCC__
      #include <ppcasm.h>
    #else
      #if (!(defined(__GNUC__) && defined(__PPC_EABI__)))
        #include <lsp.h>
      #endif
    #endif
    #define MLIB_LSP
  #endif
#endif

/* Compiler support for ISEL instruction */
#if (!(defined(MLIB_ISEL) || defined(MLIB_ISEL_DIAB)))
    #if (!(defined(MLIB_LSP)))
      #if (!defined(__DCC__))
        #if (defined(__ghs__) || defined(__DCC__) || (defined(__GNUC__) && defined(__PPC_EABI__)))
          #define MLIB_ISEL
        #endif
      #else /* (!defined(__DCC__)) */
        #if (defined(__ghs__) || defined(__DCC__) || (defined(__GNUC__) && defined(__PPC_EABI__)))
          #define MLIB_ISEL_DIAB
        #endif
      #endif /* (!defined(__DCC__)) */
    #endif /* if (!(defined(MLIB_LSP))) */
#endif

#ifndef MLIB_EFPU2_ASM
/* Compiler support for EFPU2 inline assembly */
  #ifdef __ghs__
    #define MLIB_EFPU2_ASM
  #endif
  #if defined(__GNUC__) && defined(__PPC_EABI__)
    #define MLIB_EFPU2_ASM
  #endif
#endif /* MLIB_EFPU2_ASM */
#ifdef __DCC__
  extern tU32 __cntlzw( tU32) __attribute__((intrinsic_pseudo(1, "cntlzw") ));
#endif
#if (!(defined(MLIB_SPE1) || defined(MLIB_SPE2)))
  #ifdef __DCC__
    #ifndef __Idiab_spe
      extern tFloat __efs_madd( tFloat,  tFloat,  tFloat) __attribute__((intrinsic_function(2110, 0, "efsmadd") ));
      extern tFloat __efs_msub( tFloat,  tFloat,  tFloat) __attribute__((intrinsic_function(2110, 0, "efsmsub") ));
      extern tFloat __efs_nmadd( tFloat,  tFloat,  tFloat) __attribute__((intrinsic_function(2110, 0, "efsnmadd") ));
      extern tFloat __efs_nmsub( tFloat,  tFloat,  tFloat) __attribute__((intrinsic_function(2110, 0, "efsnmsub") ));
    #endif
  #endif
#endif
#if (!(defined(MLIB_SPE2)))
  #ifdef __DCC__
    extern tFloat __efs_sqrt( tFloat) __attribute__((intrinsic_function(2000, 0, "efssqrt") ));
  #endif
#endif

/* Definition of inline directive for all supported compilers. */
#ifdef __ghs__
  #ifndef SWLIBS_INLINE
    #define SWLIBS_INLINE __attribute__ ((always_inline)) inline
  #endif
#elif defined(__MWERKS__) || defined(__CWCC__)
  #ifndef SWLIBS_INLINE
    #define SWLIBS_INLINE static __inline
  #endif
#elif defined(__DCC__)
  #ifndef SWLIBS_INLINE
    #define SWLIBS_INLINE static __inline__
  #endif
#elif defined(__CSMC__)
  #ifndef SWLIBS_INLINE
    #define SWLIBS_INLINE static @inline
  #endif
#elif defined(__IAR_SYSTEMS_ICC__)
  #ifndef SWLIBS_INLINE
    #define SWLIBS_INLINE static inline
  #endif
#elif (defined(__GNUC__) && defined(__PPC_EABI__))
  #ifndef SWLIBS_INLINE
    #define SWLIBS_INLINE static inline
  #endif
#elif (defined(__GNUC__) && (defined(__ARM_EABI__) || defined(__aarch64__)) && (!defined(__DCC__)))
  #ifndef SWLIBS_INLINE
    #define SWLIBS_INLINE __attribute__ ((always_inline)) static __inline__
  #endif
#elif defined(_MATLAB_BAM_CREATE)
  #ifndef SWLIBS_INLINE
    #define SWLIBS_INLINE static __inline
  #endif
#elif defined(__clang__)
  #ifndef SWLIBS_INLINE
    #define SWLIBS_INLINE static inline
  #endif
#else
  #ifndef SWLIBS_INLINE
    #define SWLIBS_INLINE static inline
  #endif
#endif

/* Definition of SWLIBS_ASM keyword for all supported compilers. */
#ifdef __ghs__
  #ifndef SWLIBS_ASM
    #define SWLIBS_ASM __asm
  #endif
#elif defined(__DCC__)
  #ifndef SWLIBS_ASM
    #define SWLIBS_ASM __asm
  #endif
#elif (defined(__GNUC__) && defined(__PPC_EABI__))
  #ifndef SWLIBS_ASM
    #define SWLIBS_ASM __asm__ volatile
  #endif
#else
  #define SWLIBS_ASM __asm
#endif

#if (defined(__DCC__) && defined(__PPC_APU_LSP))
  #ifndef __lsp_create_32_16
    #define __lsp_create_32_16(a, b) (((__lsp32_16__)(a) << 16u) | (__lsp16_16__)(b))
  #endif
  #ifndef __lsp_create_64_32
    #define __lsp_create_64_32(a, b) ((((__lsp64_32__)(a)) << 32) | (((__lsp64_32__)(b)) & 0x00000000FFFFFFFFULL))
  #endif
  SWLIBS_INLINE __lsp16_16__ __lsp_extract_upper_hword(__lsp32_16__ a)
  {
    return((__lsp16_16__)(a >> 16u));
  }
  #ifndef __lsp_extract_lower_hword
    #define __lsp_extract_lower_hword(a) ((__lsp32_16__)(a))
  #endif
  /* Compiler_Warning: This construct is is required for LSP intrinsics. */
  SWLIBS_INLINE __lsp32_32__ __lsp_extract_upper_word(__lsp64_32__ a)
  {
    /* Compiler_Warning: This construct is is required for LSP intrinsics. */
    return((__lsp32_32__)(a >> 32u));
  }
  #ifndef __lsp_extract_lower_word
    #define __lsp_extract_lower_word(a) ((__lsp32_32__)(a))
  #endif
#endif

/** Constant representing the maximal negative value of a signed 16-bit fixed point fractional number, floating point representation. */
#define SFRACT_MIN          (-1.0)

/** Constant representing the maximal positive value of a signed 16-bit fixed point fractional
 *  number,  floating point representation. */
#define SFRACT_MAX          (0.999969482421875)

/** Constant representing the maximal negative value of signed 32-bit fixed point fractional number,  floating point representation. */
#define FRACT_MIN           (-1.0)

/** Constant representing the maximal positive value of a signed 32-bit fixed point fractional
 *  number,  floating point representation. */
#define FRACT_MAX           (0.9999999995343387126922607421875)

/** Value 0.5 in 32-bit fixed point fractional format. */
#define FRAC32_0_5           ((tFrac32) 0x40000000U)

/** Value 0.5 in 16-bit fixed point fractional format. */
#define FRAC16_0_5           ((tFrac16) 0x4000U)

/** Value 0.25 in 32-bit fixed point fractional format. */
#define FRAC32_0_25           ((tFrac32) 0x20000000U)

/** Value 0.25 in 16-bit fixed point fractional format. */
#define FRAC16_0_25           ((tFrac16) 0x2000U)

/** Constant representing the maximal positive value of a unsigned 16-bit fixed point integer
 *  number, equal to \f$2^{15}\f$ = 0x8000. */
#ifndef SWLIBS_UINT16_MAX
#define SWLIBS_UINT16_MAX          ((tU16) 0x8000U)
#endif

/** Constant representing the maximal positive value of a signed 16-bit fixed point integer
 *  number, equal to \f$2^{15}\f$-1 = 0x7fff. */
#ifndef SWLIBS_INT16_MAX
#define SWLIBS_INT16_MAX           ((tS16) 0x7fffU)
#endif

/** Constant representing the maximal negative value of a signed 16-bit fixed point integer
 *  number, equal to -\f$2^{15}\f$ = 0x8000. */
#ifndef SWLIBS_INT16_MIN
#define SWLIBS_INT16_MIN           ((tS16) 0x8000U)
#endif

/** Constant representing the maximal positive value of a unsigned 32-bit fixed point integer
 *  number, equal to \f$2^{31}\f$ = 0x80000000. */
#ifndef SWLIBS_UINT32_MAX
#define SWLIBS_UINT32_MAX          ((tU32) 0x80000000U)
#endif

/** Constant representing the maximal positive value of a signed 32-bit fixed point integer
 *  number, equal to \f$2^{31}\f$-1 = 0x7fff ffff. */
#ifndef SWLIBS_INT32_MAX
#define SWLIBS_INT32_MAX           ((tS32) 0x7fffffffU)
#endif

/** Constant representing the maximal negative value of a signed 32-bit fixed point integer
 *  number, equal to -\f$2^{31}\f$ = 0x8000 0000. */
#ifndef SWLIBS_INT32_MIN
#define SWLIBS_INT32_MIN           ((tS32) 0x80000000U)
#endif

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** Constant representing the maximal negative value of the 32-bit float type. */
#ifndef FLOAT_MIN
#define FLOAT_MIN           ((tFloat)(-3.4028234e+38F))
#endif
#endif 

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** Constant representing the maximal positive value of the 32-bit float type. */
#ifndef FLOAT_MAX
#define FLOAT_MAX           ((tFloat)(3.4028234e+38F))
#endif
#endif 

/** Type casting - signed 16-bit integer value cast to a signed 32-bit integer. */
#define INT16TOINT32(x)        ((tS32) (x))

/** Type casting - signed 32-bit integer value cast to a signed 16-bit integer. */
#define INT32TOINT16(x)        ((tS16) (x))

/** Type casting - signed 32-bit integer value cast to a signed 64-bit integer. */
#define INT32TOINT64(x)        ((tS64) (x))

/** Type casting - signed 64-bit integer value cast to a signed 32-bit integer. */
#define INT64TOINT32(x)        ((tS32) (x))

/** Type casting - signed 16-bit fractional value cast to a signed 16-bit integer. */
#define F16TOINT16(x)       ((tS16) (x))

/** Type casting - lower 16 bits of a signed 32-bit fractional value cast to a signed 16-bit integer. */
#define F32TOINT16(x)       ((tS16) (x))

/** Type casting - lower 16 bits of a signed 64-bit fractional value cast to a signed 16-bit integer. */
#define F64TOINT16(x)       ((tS16) (x))

/** Type casting - a signed 16-bit fractional value cast to a signed 32-bit integer, the value placed at the lower
*   16-bits of the 32-bit result. */
#define F16TOINT32(x)       ((tS32) (x))

/** Type casting - signed 32-bit fractional value cast to a signed 32-bit integer. */
#define F32TOINT32(x)       ((tS32) (x))

/** Type casting - lower 32 bits of a signed 64-bit fractional value cast to a signed 32-bit integer. */
#define F64TOINT32(x)       ((tS32) (x))

/** Type casting - signed 16-bit fractional value cast to a signed 64-bit integer, the value placed at the lower
*   16-bits of the 64-bit result. */
#define F16TOINT64(x)       ((tS64) (x))

/** Type casting - signed 32-bit fractional value cast to a signed 64-bit integer, the value placed at the lower
*   32-bits of the 64-bit result. */
#define F32TOINT64(x)       ((tS64) (x))

/** Type casting - signed 64-bit fractional value cast to a signed 64-bit integer. */
#define F64TOINT64(x)       ((tS64) (x))

/** Type casting - signed 16-bit integer value cast to a signed 16-bit fractional. */
#define INT16TOF16(x)       ((tFrac16) (x))

/** Type casting - signed 16-bit integer value cast to a signed 32-bit fractional, the value placed at the lower
*   16 bits of the 32-bit result. */
#define INT16TOF32(x)       ((tFrac32) (x))

/** Type casting - lower 16-bits of a signed 32-bit integer value cast to a signed 16-bit fractional. */
#define INT32TOF16(x)       ((tFrac16) (x))

/** Type casting - signed 32-bit integer value cast to a signed 32-bit fractional. */
#define INT32TOF32(x)       ((tFrac32) (x))

/** Type casting - lower 16-bits of a signed 64-bit integer value cast to a signed 16-bit fractional. */
#define INT64TOF16(x)       ((tFrac16) (x))

/** Type casting - lower 32-bits of a signed 64-bit integer value cast to a signed 32-bit fractional. */
#define INT64TOF32(x)       ((tFrac32) (x))

/** One over sqrt(3) with a 16-bit result, the result is rounded for a better accuracy. */
#define F16_1_DIVBY_SQRT3   ((tFrac16) 0x49E7U)

/** One over sqrt(3) with a 32-bit result, the result is rounded for a better accuracy. */
#define F32_1_DIVBY_SQRT3   ((tFrac32) 0x49E69D16U)

/** Sqrt(3) divided by two with a 16-bit result, the result is rounded for a better accuracy. */
#define F16_SQRT3_DIVBY_2   ((tFrac16) 0x6EDAU)

/** Minus sqrt(3) divided by two with a 16-bit result, the result is rounded for a better accuracy. */
#define F16_MINUS_SQRT3_DIVBY_2   ((tFrac16) 0x9126U)

/** Sqrt(3) divided by four with a 16-bit result. */
#define F16_SQRT3_DIVBY_4   ((tFrac16) 0x376DU)

/** Sqrt(3) divided by six with a 16-bit result. */
#define F16_SQRT3_DIVBY_6   ((tFrac16) 0x24F3U)

/** Sqrt(3) divided by two with a 32-bit result, the result is rounded for a better accuracy. */
#define F32_SQRT3_DIVBY_2   ((tFrac32) 0x6ED9EBA1U)

/** Minus sqrt(3) divided by two with a 32-bit result, the result is rounded for a better accuracy. */
#define F32_MINUS_SQRT3_DIVBY_2   ((tFrac32) 0x9126145FU)

/** Sqrt(3) divided by four with a 32-bit result. */
#define F32_SQRT3_DIVBY_4   ((tFrac32) 0x376CF5D1U)

/** Sqrt(3) divided by six with a 32-bit result. */
#define F32_SQRT3_DIVBY_6   ((tFrac32) 0x24F34E8BU)

/** Sqrt(2) divided by two with a 16-bit result, the result is rounded for a better accuracy. */
#define F16_SQRT2_DIVBY_2   ((tFrac16) 0x5A82U)

/** Sqrt(2) divided by two with a 32-bit result, the result is rounded for a better accuracy. */
#define F32_SQRT2_DIVBY_2   ((tFrac32) 0x5A82799AU)

/** One third in 16-bit resolution, the result is rounded for a better accuracy. */
#define F16_1_DIVBY_3   ((tFrac16) 0x2AABU)

/** One third in 32-bit resolution, the result is rounded for a better accuracy. */
#define F32_1_DIVBY_3   ((tFrac32) 0x2AAAAAABU)

/** One third in 16-bit resolution, the result is rounded for a better accuracy. */
#define F16_MINUS_1_DIVBY_3   ((tFrac16) 0xD556U)

/** One third in 32-bit resolution, the result is rounded for a better accuracy. */
#define F32_MINUS_1_DIVBY_3   ((tFrac32) 0xD5555556U)

/** One half in 16-bit resolution, the result is rounded for a better accuracy. */
#define F16_MINUS_1_DIVBY_2   ((tFrac16) 0xC000U)

/** One half in 32-bit resolution, the result is rounded for a better accuracy. */
#define F32_MINUS_1_DIVBY_2   ((tFrac32) 0xC0000000U)

/** Two thirds in 16-bit resolution, the result is rounded for a better accuracy. */
#define F16_2_DIVBY_3   ((tFrac16) 0x5555U)

/** Two thirds in 32-bit resolution, the result is rounded for a better accuracy. */
#define F32_2_DIVBY_3   ((tFrac32) 0x55555555U)

/** Macro converting a signed fractional [-1,1) number into a 16-bit fixed point number in format Q1.15.*/
#define FRAC16(x)           ((tFrac16) (((x) < SFRACT_MAX) ? (((x) >= SFRACT_MIN) ? ((x)*32768.0) : SWLIBS_INT16_MIN) : SWLIBS_INT16_MAX))

/** Macro converting a signed fractional [-1,1) number into a 32-bit fixed point number in format Q1.31.*/
#define FRAC32(x)           ((tFrac32) (((x) < FRACT_MAX) ? (((x) >= FRACT_MIN) ? ((x)*2147483648.0) : SWLIBS_INT32_MIN) : SWLIBS_INT32_MAX))

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** One over sqrt(3) in single precision floating point format. */
#define FLOAT_DIVBY_SQRT3   ((tFloat) 0.5773502691896258)
#endif 

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** Sqrt(3) in single precision floating point format. */
#define FLOAT_SQRT3 ((tFloat) 1.732050776481628)
#endif 

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** Sqrt(3) divided by two in single precision floating point format. */
#define FLOAT_SQRT3_DIVBY_2 ((tFloat) 0.866025403784439)
#endif

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** Sqrt(3) divided by two in single precision floating point format. */
#define FLOAT_MINUS_SQRT3_DIVBY_2 ((tFloat) -0.866025403784439)
#endif 

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** Sqrt(3) divided by four in single precision floating point format. */
#define FLOAT_SQRT3_DIVBY_4 ((tFloat) 0.4330127018922190)
#endif

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** Sqrt(3) divided by six in single precision floating point format. */
#define FLOAT_SQRT3_DIVBY_6 ((tFloat) 0.2886751)
#endif 

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** Sqrt(3) divided by four correction constant. */
#define FLOAT_SQRT3_DIVBY_4_CORRECTION ((tFloat)0)
#endif 

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** 2*\f$\Pi\f$ in single precision floating point format. */
#define FLOAT_2_PI          ((tFloat) 6.28318530717958)
#endif

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** 2*\f$\Pi\f$ divided by three in single precision floating point format. */
#define FLOAT_2_PI_DIVBY_3  ((tFloat) 2.094395160675049)
#endif 

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** \f$\Pi\f$ in single precision floating point format. */
#define FLOAT_PI            ((tFloat) 3.14159265358979)
#endif 

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** \f$\Pi\f$/2 in single precision floating point format. */
#define FLOAT_PI_DIVBY_2    ((tFloat) 1.57079632679490)
#endif 

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** Tan(\f$\Pi\f$/6) in single precision floating point format. */
#define FLOAT_TAN_PI_DIVBY_6   ((tFloat)0.577350269189626000)
#endif 

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** Tan(\f$\Pi\f$/12) in single precision floating point format. */
#define FLOAT_TAN_PI_DIVBY_12   ((tFloat)0.267949192431123000)
#endif 

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** \f$\Pi\f$/6 in single precision floating point format. */
#define FLOAT_PI_DIVBY_6   ((tFloat)0.523598775598299000)  
#endif 

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** Double to single precision correction constant for \f$\Pi\f$, equal to (\f$\Pi\f$(Double) - \f$\Pi\f$(Single)). */
#define FLOAT_PI_SINGLE_CORRECTION ((tFloat)4.371139006309477e-08)
#endif 

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** Double to single precision correction constant for \f$\Pi\f$, equal to  (2*(\f$\Pi\f$(Double) - \f$\Pi\f$(Single)). */
#define FLOAT_PI_CORRECTION ((tFloat)8.742278012618954e-08)
#endif 

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** \f$\Pi\f$/4 in single precision floating point format. */
#define FLOAT_PI_DIVBY_4    ((tFloat) 0.7853981633974480)
#endif 

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** Number four divided by \f$\Pi\f$ in single precision floating point format. */
#define FLOAT_4_DIVBY_PI    ((tFloat) 1.2732395447351600) 
#endif 

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** Value 0.5 in single precision floating point format. */
#define FLOAT_0_5           ((tFloat) 0.5)
#endif 

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** Value -0.5 in single precision floating point format. */
#define FLOAT_MINUS_0_5     ((tFloat) -0.5)
#endif 

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** Value 1 in single precision floating point format. */
#define FLOAT_PLUS_1        ((tFloat) 1)
#endif 

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** Value -1 in single precision floating point format. */
#define FLOAT_MINUS_1       ((tFloat) -1)
#endif 

#if (SWLIBS_SUPPORT_FLT == SWLIBS_STD_ON)
/** Constant representing the smallest positive normalized 32-bit floating-point value. */
#define FLOAT_MIN_NORM       ((tFloat) 1.175494350822288e-38)
#endif 

#ifdef __cplusplus
  #ifndef SWLIBS_RESTRICT
    #ifdef _MSC_VER
      #define SWLIBS_RESTRICT __restrict
    #else
      #define SWLIBS_RESTRICT __restrict__
    #endif
  #endif
#elif defined(__cevacxd__)
  #define SWLIBS_RESTRICT __restrict__
#else
  #ifndef SWLIBS_RESTRICT
    #ifdef _MSC_VER
      #define SWLIBS_RESTRICT __restrict
    #else
      #define SWLIBS_RESTRICT restrict
    #endif
  #endif
#endif

#endif /* SWLIBS_DEFINES_H */
