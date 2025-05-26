#ifndef WKPU_HAL_IRQ_H
#define WKPU_HAL_IRQ_H



/*====================================================================================================
                                        FILE VERSION CHECKS
====================================================================================================*/
#define ICU_WKPU_HAL_IRQ_VENDOR_ID_H                   176

#define ICU_WKPU_HAL_IRQ_MAJOR_VER_H                   4
#define ICU_WKPU_HAL_IRQ_MINOR_VER_H                   4
#define ICU_WKPU_HAL_IRQ_REVISION_VER_H                0

#define ICU_WKPU_HAL_IRQ_SW_MAJOR_VER_H                1
#define ICU_WKPU_HAL_IRQ_SW_MINOR_VER_H                0
#define ICU_WKPU_HAL_IRQ_SW_PATCH_VER_H                1

#if (ICU_WKPU_HAL_IRQ_VENDOR_ID_H != ICU_VENDOR_ID_H)
#error "NON-MATCHED DATA : ICU_VENDOR_ID_CFG"
#endif

/* Check if current file and ICU header file are of the same Autosar version */
#if (ICU_WKPU_HAL_IRQ_MAJOR_VER_H != ICU_MAJOR_VER_H)
#error "NON-MATCHED DATA : ICU_MAJOR_VER_H"
#endif
#if (ICU_WKPU_HAL_IRQ_MINOR_VER_H != ICU_MINOR_VER_H)
#error "NON-MATCHED DATA : ICU_MINOR_VER_H"
#endif
#if (ICU_WKPU_HAL_IRQ_REVISION_VER_H != ICU_REVISION_VER_H)
#error "NON-MATCHED DATA : ICU_REVISION_VER_H"
#endif

/* Check if current file and ICU header file are of the same Software version */
#if (ICU_WKPU_HAL_IRQ_SW_MAJOR_VER_H != ICU_SW_MAJOR_VER_H)
#error "NON-MATCHED DATA : ICU_SW_MAJOR_VER_H"
#endif
#if (ICU_WKPU_HAL_IRQ_SW_MINOR_VER_H != ICU_SW_MINOR_VER_H)
#error "NON-MATCHED DATA : ICU_SW_MINOR_VER_H"
#endif
#if (ICU_WKPU_HAL_IRQ_SW_PATCH_VER_H != ICU_SW_PATCH_VER_H)
#error "NON-MATCHED DATA : ICU_SW_PATCH_VER_H"
#endif

#if defined(CCFC3012PT)
ISR(WKPU_IRQ0_Handler);
ISR(WKPU_IRQ1_Handler);
ISR(WKPU_IRQ2_Handler);
ISR(WKPU_IRQ3_Handler);
ISR(WKPU_IRQ4_Handler);
ISR(WKPU_IRQ5_Handler);
ISR(WKPU_IRQ6_Handler);
ISR(WKPU_IRQ7_Handler);
#endif

#endif
