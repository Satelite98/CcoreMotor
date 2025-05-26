#ifndef ICU_WKPU_WRAPPER_H
#define ICU_WKPU_WRAPPER_H

#include "Icu_Wkpu_LLDrivers.h"
/*====================================================================================================
                                        FILE VERSION CHECKS
====================================================================================================*/
#define ICU_WKPU_WRAPPER_VENDOR_ID_H                   176

#define ICU_WKPU_WRAPPER_MAJOR_VER_H                   4
#define ICU_WKPU_WRAPPER_MINOR_VER_H                   4
#define ICU_WKPU_WRAPPER_REVISION_VER_H                0

#define ICU_WKPU_WRAPPER_SW_MAJOR_VER_H                1
#define ICU_WKPU_WRAPPER_SW_MINOR_VER_H                0
#define ICU_WKPU_WRAPPER_SW_PATCH_VER_H                1

#if (ICU_WKPU_WRAPPER_VENDOR_ID_H != ICU_VENDOR_ID_H)
#error "NON-MATCHED DATA : ICU_VENDOR_ID_CFG"
#endif

/* Check if current file and ICU header file are of the same Autosar version */
#if (ICU_WKPU_WRAPPER_MAJOR_VER_H != ICU_MAJOR_VER_H)
#error "NON-MATCHED DATA : ICU_MAJOR_VER_H"
#endif
#if (ICU_WKPU_WRAPPER_MINOR_VER_H != ICU_MINOR_VER_H)
#error "NON-MATCHED DATA : ICU_MINOR_VER_H"
#endif
#if (ICU_WKPU_WRAPPER_REVISION_VER_H != ICU_REVISION_VER_H)
#error "NON-MATCHED DATA : ICU_REVISION_VER_H"
#endif

/* Check if current file and ICU header file are of the same Software version */
#if (ICU_WKPU_WRAPPER_SW_MAJOR_VER_H != ICU_SW_MAJOR_VER_H)
#error "NON-MATCHED DATA : ICU_SW_MAJOR_VER_H"
#endif
#if (ICU_WKPU_WRAPPER_SW_MINOR_VER_H != ICU_SW_MINOR_VER_H)
#error "NON-MATCHED DATA : ICU_SW_MINOR_VER_H"
#endif
#if (ICU_WKPU_WRAPPER_SW_PATCH_VER_H != ICU_SW_PATCH_VER_H)
#error "NON-MATCHED DATA : ICU_SW_PATCH_VER_H"
#endif



FUNC(void, ICU_CODE) Icu_Wkpu_Wrapper_Init \
( \
    P2CONST(ICU_Wkpu_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);

FUNC(void, ICU_CODE) Icu_Wkpu_Wrapper_DeInit \
( \
    P2CONST(ICU_Wkpu_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);
#if defined(CCFC3012PT)
FUNC (void, ICU_CODE) Icu_Wkpu_Wrapper_EnableEdgeDetection
(
    VAR(Icu_ChannelType,                 AUTOMATIC) nChannel, \
    P2CONST(ICU_Wkpu_ConfigType,  ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);

FUNC (void, ICU_CODE) Icu_Wkpu_Wrapper_DisableEdgeDetection
(
    VAR(Icu_ChannelType,                 AUTOMATIC) nChannel, \
    P2CONST(ICU_Wkpu_ConfigType,  ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);

FUNC(void, ICU_CODE) Icu_Wkpu_Wrapper_SetActivationCondition(
    VAR(Icu_ChannelType,                 AUTOMATIC) nChannel, \
    VAR(Icu_ActivationType,              AUTOMATIC) eActivation, \
    P2CONST(ICU_Wkpu_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr \
);

FUNC(void, ICU_CODE) Icu_Wkpu_Wrapper_IrqConfig
(
    VAR(Icu_ChannelType,                               AUTOMATIC) nChannel, \
    P2CONST(ICU_Wkpu_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr, \
    VAR(boolean,                                       AUTOMATIC) IsEnable
);

FUNC(void, ICU_CODE) Icu_Wkpu_Wrapper_WakeupConfig
(
    VAR(Icu_ChannelType,                               AUTOMATIC) nChannel, \
    P2CONST(ICU_Wkpu_ConfigType, ICU_VAR, ICU_APPL_CONST) sIcu_WrapperConfigPtr, \
    VAR(boolean,                                       AUTOMATIC) IsEnable
);
#endif

#endif
