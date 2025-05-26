/**************************************************************************** 
* 
* Copyright (c) 2024  C*Core -   All Rights Reserved
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* 
* @file     CCFC3012PT.h
* @version  1.0
* @date     2024 - 05 - 11
* @brief    Initial version.
*
*****************************************************************************/

#ifndef CCFC3012PT_H_
#define CCFC3012PT_H_
#if defined(CCFC3012PT)

#include "typedefs.h"
/*PRQA S 1536,2052,3108,0784,0636,2053 EOF*/
#ifdef __cplusplus
extern "C" {
#endif
#ifdef __MWERKS__
#pragma push
#pragma ANSI_strict off
#endif
#ifdef __ghs__
#pragma ghs nowarning 618
#endif

#include "../module/core_reg.h"
#include "../module/c55fmc_reg.h"
#include "../module/cmu_reg.h"
#include "../module/crc_reg.h"
#include "../module/dma_mux_reg.h"
#include "../module/dspi_reg.h"
#include "../module/etpu_reg.h"
#include "../module/dts_reg.h"
#include "../module/ebi_reg.h"
#include "../module/fccu_reg.h"
#include "../module/fec_reg.h"
#include "../module/fr_reg.h"
#include "../module/i2c_reg.h"
#include "../module/ima_reg.h"
#include "../module/intc_reg.h"
#include "../module/ircosc_reg.h"
#include "../module/jdc_reg.h"
#include "../module/jtagm_reg.h"
#include "../module/lfast_reg.h"
#include "../module/lin_reg.h"
#include "../module/ssi_reg.h"
#include "../module/i2s_reg.h"
#include "../module/mc_reg.h"
#include "../module/memu_reg.h"
#include "../module/can_sample.h"
#include "../module/canfd_reg.h"
#include "../module/mcan_reg.h"
#include "../module/mttcan_reg.h"
#include "../module/pass_reg.h"
#include "../module/pbridge_reg.h"
#include "../module/pcm_reg.h"
#include "../module/pfalsh_reg.h"
#include "../module/pit_reg.h"
#include "../module/plldig.h"
#include "../module/pmcdig_reg.h"
#include "../module/pramc_reg.h"
#include "../module/emios_reg.h"
#include "../module/psi5_reg.h"
#include "../module/psi5s_reg.h"
#include "../module/eqadc_reg.h"
#include "../module/port_reg.h"
#include "../module/sdadc_reg.h"
#include "../module/sema42_reg.h"
#include "../module/sipi_reg.h"
#include "../module/siul_reg.h"
#include "../module/csrx_reg.h"
#include "../module/igf_reg.h"
#include "../module/smpu_reg.h"
#include "../module/srx_reg.h"
#include "../module/sscm_reg.h"
#include "../module/stcu2_reg.h"
#include "../module/stm_reg.h"
#include "../module/swt_reg.h"
#include "../module/t40fmc_reg.h"
#include "../module/tdm_reg.h"
#include "../module/wkpu_reg.h"
#include "../module/xbar_reg.h"
#include "../module/xbic_reg.h"
#include "../module/edma_reg.h"
#include "../module/eth0_reg.h"
#include "../module/xosc_reg.h"
#include "../module/eth1_reg.h"
#include "../module/rtc_reg.h"
#include "../module/gtm410_reg.h"
#include "../module/gmac_reg.h"
#include "../module/pwm3012_reg.h"
#include "../module/sport_reg.h"
#include "../module/acmp_reg.h"
/* ============================================================================
   ================================== Address =================================
   ============================================================================ */
#define SRAM0_START     0x40000000UL;
#define C55FMC          (*(volatile struct C55FMC_tag *)   0xFFFE0000UL)
#define CMU_ADCSAR      (*(volatile struct CMU_tag *)      0xFBFB0340UL)
#define CMU_ADCSD       (*(volatile struct CMU_tag *)      0xFBFB0300UL)
#define CMU_CLKOUT      (*(volatile struct CMU_tag *)      0xFBFB04C0UL)
#define CMU_CORE        (*(volatile struct CMU_tag *)      0xFBFB0480UL)
#define CMU_FXBAR       (*(volatile struct CMU_tag *)      0xFBFB0200UL)
#define CMU_PBRIDGE     (*(volatile struct CMU_tag *)      0xFBFB0280UL)
#define CMU_PER         (*(volatile struct CMU_tag *)      0xFBFB02C0UL)
#define CMU_PLL         (*(volatile struct CMU_tag *)      0xFFFB0200UL)
#define CMU_PSI5_1US    (*(volatile struct CMU_tag *)      0xFBFB0440UL)
#define CMU_PSI5_F125   (*(volatile struct CMU_tag *)      0xFBFB0400UL)
#define CMU_PSI5_F189   (*(volatile struct CMU_tag *)      0xFBFB03C0UL)
#define CMU_SENT        (*(volatile struct CMU_tag *)      0xFBFB0380UL)
#define CMU_SXBAR       (*(volatile struct CMU_tag *)      0xFBFB0240UL)
#define CRC_0           (*(volatile struct CRC_tag *)      0xFFF64000UL)
#define CRC_1           (*(volatile struct CRC_tag *)      0xFBF64000UL)
#define DMAMUX_0        (*(volatile struct DMAMUX_tag *)   0xFFF6C000UL)
#define DMAMUX_1        (*(volatile struct DMAMUX_tag *)   0xFFF6C200UL)
#define DMAMUX_2        (*(volatile struct DMAMUX_tag *)   0xFFF6C400UL)
#define DMAMUX_3        (*(volatile struct DMAMUX_tag *)   0xFFF6C600UL)
#define DMAMUX_4        (*(volatile struct DMAMUX_tag *)   0xFFF6C800UL)
#define DMAMUX_5        (*(volatile struct DMAMUX_tag *)   0xFFF6CA00UL)
#define DMAMUX_6        (*(volatile struct DMAMUX_tag *)   0xFFF6CC00UL)
#define DMAMUX_7        (*(volatile struct DMAMUX_tag *)   0xFFF6CE00UL)
#define DMAMUX_8        (*(volatile struct DMAMUX_tag *)   0xFFF6D000UL)
#define DMAMUX_9        (*(volatile struct DMAMUX_tag *)   0xFFF6D200UL)
#define DMAMUX_10       (*(volatile struct DMAMUX_tag *)   0xFFF6D400UL)
#define DSPI_0          (*(volatile struct DSPI_tag *)     0xFFE70000UL)
#define DSPI_1          (*(volatile struct DSPI_tag *)     0xFFE74000UL)
#define DSPI_2          (*(volatile struct DSPI_tag *)     0xFBE70000UL)
#define DSPI_3          (*(volatile struct DSPI_tag *)     0xFBE74000UL)
#define DSPI_4          (*(volatile struct DSPI_tag *)     0xFFE78000UL)
#define DSPI_5          (*(volatile struct DSPI_tag *)     0xFBE78000UL)
#define DSPI_6          (*(volatile struct DSPI_tag *)     0xFFE7C000UL)
#define DSPI_7          (*(volatile struct DSPI_tag *)     0xFBE7C000UL)
#define DSPI_8          (*(volatile struct DSPI_tag *)     0xFFE80000UL)
#define DSPI_9          (*(volatile struct DSPI_tag *)     0xFBE80000UL)
#define DSPI_10         (*(volatile struct DSPI_tag *)     0xFFE84000UL)
#define DSPI_11         (*(volatile struct DSPI_tag *)     0xFBE84000UL)
#define DSPI_12         (*(volatile struct DSPI_tag *)     0xFFE88000UL)
#define DSPI_13         (*(volatile struct DSPI_tag *)     0xFBE88000UL)
#define DSPI_14         (*(volatile struct DSPI_tag *)     0xFFE60000UL)
#define DSPI_15         (*(volatile struct DSPI_tag *)     0xFFE64000UL)
#define DSPI_16         (*(volatile struct DSPI_tag *)     0xFBE44000UL)
#define DSPI_17         (*(volatile struct DSPI_tag *)     0xFBE48000UL)
#define DSPI_18         (*(volatile struct DSPI_tag *)     0xFBE4C000UL)
#define DSPI_19         (*(volatile struct DSPI_tag *)     0xFFE44000UL)
#define DSPI_20         (*(volatile struct DSPI_tag *)     0xFFE48000UL)
#define DSPI_21         (*(volatile struct DSPI_tag *)     0xFFE4C000UL)
#define DTS             (*(volatile struct DTS_tag *)      0xFFF38000UL)
#define EBI             (*(volatile struct EBI_tag *)      0xFFFF0000UL)
#define FCCU            (*(volatile struct FCCU_tag *)     0xFBF58000UL)
#define FEC             (*(volatile struct FEC_tag *)      0xFC0B0000UL)
#define FR_0            (*(volatile struct FR_tag *)       0xFFE50000UL)
#define FR_1            (*(volatile struct FR_tag *)       0xFBE50000UL)
#define GTM4            (*(volatile struct GTM4_tag *)     0xFFC00000UL)
#define GTM4_TIM0       (*(volatile struct _GTM_TIM *)     0xFFC00800UL)
#define GTM4_TIM1       (*(volatile struct _GTM_TIM *)     0xFFC20800UL)
#define GTM4_TIM2       (*(volatile struct _GTM_TIM *)     0xFFC40800UL)
#define GTM4_TIM3       (*(volatile struct _GTM_TIM *)     0xFFC60800UL)
#define GTM4_TIM4       (*(volatile struct _GTM_TIM *)     0xFFC80800UL)
#define GTM4_TIM5       (*(volatile struct _GTM_TIM *)     0xFFCA0800UL)
#define GTM4_TIM6       (*(volatile struct _GTM_TIM *)     0xFFCC0800UL)
#define GTM4_TIM7       (*(volatile struct _GTM_TIM *)     0xFFCE0800UL)
#define GTM4_TOM0       (*(volatile struct _GTM_TOM *)     0xFFC01000UL)
#define GTM4_TOM1       (*(volatile struct _GTM_TOM *)     0xFFC21000UL)
#define GTM4_TOM2       (*(volatile struct _GTM_TOM *)     0xFFC41000UL)
#define GTM4_TOM3       (*(volatile struct _GTM_TOM *)     0xFFC61000UL)
#define GTM4_TOM4       (*(volatile struct _GTM_TOM *)     0xFFC81000UL)
#define GTM4_TOM5       (*(volatile struct _GTM_TOM *)     0xFFCA1000UL)
#define GTM4_ATOM0      (*(volatile struct _GTM_ATOM *)    0xFFC01800UL)
#define GTM4_ATOM1      (*(volatile struct _GTM_ATOM *)    0xFFC21800UL)
#define GTM4_ATOM2      (*(volatile struct _GTM_ATOM *)    0xFFC41800UL)
#define GTM4_ATOM3      (*(volatile struct _GTM_ATOM *)    0xFFC61800UL)
#define GTM4_ATOM4      (*(volatile struct _GTM_ATOM *)    0xFFC81800UL)
#define GTM4_ATOM5      (*(volatile struct _GTM_ATOM *)    0xFFCA1800UL)
#define GTM4_ATOM6      (*(volatile struct _GTM_ATOM *)    0xFFCC1800UL)
#define GTM4_ATOM7      (*(volatile struct _GTM_ATOM *)    0xFFCE1800UL)
#define I2C_0           (*(volatile struct I2C_tag *)      0xFFE68000UL)
#define I2C_1           (*(volatile struct I2C_tag *)      0xFBE68000UL)
#define INTC_0          (*(volatile struct INTC_tag *)     0xFC040000UL)
#define INTC_1          (*(volatile struct INTC_tag *)     0xFC042000UL)
#define IRCOSC          (*(volatile struct IRCOSC_tag *)   0xFFFB0000UL)
#define JDC             (*(volatile struct JDC_tag *)      0xFFF3C000UL)
#define JTAGM           (*(volatile struct JTAGM_tag *)    0xFFF48000UL)
#define LFAST_0         (*(volatile struct LFAST_tag *)    0xFFFD8000UL)
#define LINFlexD_0      (*(volatile struct LINFlexD_tag *) 0xFFE8C000UL)
#define LINFlexD_1      (*(volatile struct LINFlexD_tag *) 0xFFE90000UL)
#define LINFlexD_2      (*(volatile struct LINFlexD_tag *) 0xFBE8C000UL)
#define LINFlexD_3      (*(volatile struct LINFlexD_tag *) 0xFFE94000UL)
#define LINFlexD_4      (*(volatile struct LINFlexD_tag *) 0xFFE98000UL)
#define LINFlexD_5      (*(volatile struct LINFlexD_tag *) 0xFFE9C000UL)
#define LINFlexD_6      (*(volatile struct LINFlexD_tag *) 0xFFEA0000UL)
#define LINFlexD_7      (*(volatile struct LINFlexD_tag *) 0xFBE90000UL)
#define LINFlexD_8      (*(volatile struct LINFlexD_tag *) 0xFBE94000UL)
#define LINFlexD_9      (*(volatile struct LINFlexD_tag *) 0xFBE98000UL)
#define LINFlexD_10     (*(volatile struct LINFlexD_tag *) 0xFBE9C000UL)
#define LINFlexD_11     (*(volatile struct LINFlexD_tag *) 0xFBEA0000UL)
#define LINFlexD_12     (*(volatile struct LINFlexD_tag *) 0xFBEA4000UL)
#define LINFlexD_14     (*(volatile struct LINFlexD_tag *) 0xFFEA8000UL)
#define LINFlexD_15     (*(volatile struct LINFlexD_tag *) 0xFBEA8000UL)
#define LINFlexD_16     (*(volatile struct LINFlexD_tag *) 0xFFEAC000UL)
#define I2S_1      		(*(volatile struct I2SM_tag *)     0xFBEE0000UL)
#define I2S_1_SLV      	(*(volatile struct I2SS_tag *)     0xFBEE0800UL)
#define I2S_2      		(*(volatile struct I2SM_tag *)     0xFBEE4000UL)
#define I2S_2_SLV      	(*(volatile struct I2SS_tag *)     0xFBEE4800UL)
#define MC_CGM          (*(volatile struct MC_CGM_tag *)   0xFFFB0000UL)
#define MC_ME           (*(volatile struct MC_ME_tag *)    0xFFFB8000UL)
#define MC_PCU          (*(volatile struct MC_PCU_tag *)   0xFFFA0000UL)
#define MC_RGM          (*(volatile struct MC_RGM_tag *)   0xFFFA8000UL)
#define MEMU            (*(volatile struct MEMU_tag *)     0xFFF50000UL)
#define IMA             (*(volatile struct IMA_tag *)      0xFFF54000UL)
#define CAN_SAMPLE_1	(*(volatile struct CAN_SAMPLER_tag *) 0xFFEB4000UL)
#define M_CAN_1         (*(volatile struct M_CAN_tag *)    0xFFEE4000UL)
#define M_CAN_2         (*(volatile struct M_CAN_tag *)    0xFFEE8000UL)
#define M_CAN_3         (*(volatile struct M_CAN_tag *)    0xFFEEC000UL)
#define M_CAN_4         (*(volatile struct M_CAN_tag *)    0xFFEF0000UL)
#define M_CAN_5         (*(volatile struct M_CAN_tag *)    0xFFEF4000UL)
#define M_CAN_6         (*(volatile struct M_CAN_tag *)    0xFFEF8000UL)
#define M_CAN_7         (*(volatile struct M_CAN_tag *)    0xFFEFC000UL)
#define M_CAN_8         (*(volatile struct M_CAN_tag *)    0xFFF00000UL)
#define M_CAN_9         (*(volatile struct M_CAN_tag *)    0xFFEBC000UL)
#define M_CAN_10        (*(volatile struct M_CAN_tag *)    0xFFEC0000UL)
#define M_CAN_11        (*(volatile struct M_CAN_tag *)    0xFFEC4000UL)
#define M_CAN_12        (*(volatile struct M_CAN_tag *)    0xFFEC8000UL)
#define CANFD_1         (*(volatile struct CANFD_tag *)    0xFBED8000UL)
#define CANFD_9         (*(volatile struct CANFD_tag *)    0xFBEB8000UL)
#define M_TTCAN         (*(volatile struct M_TTCAN_tag *)  0xFFEDC000UL)
#define PASS            (*(volatile struct PASS_tag *)     0xFFFF4000UL)
#define PBRIDGE_A       (*(volatile struct PBRIDGE_tag *)  0xFC000000UL)
#define PBRIDGE_B       (*(volatile struct PBRIDGE_tag *)  0xF8000000UL)
#define PCM             (*(volatile struct PCM_tag *)      0xFC028000UL)
#define PFLASH          (*(volatile struct PFLASH_tag *)   0xFC030000UL)
#define PFI0_PFLASH     (*(volatile struct PFLASH_tag *)   0xFC034000UL)
#define PFI1_PFLASH     (*(volatile struct PFLASH_tag *)   0xFC034800UL)
#define PFI2_PFLASH     (*(volatile struct PFLASH_tag *)   0xFC035000UL)
#define PFI3_PFLASH     (*(volatile struct PFLASH_tag *)   0xFC035800UL)
#define PFI4_PFLASH     (*(volatile struct PFLASH_tag *)   0xFC036000UL)
#define PFI5_PFLASH     (*(volatile struct PFLASH_tag *)   0xFC036800UL)
#define PIT_0           (*(volatile struct PIT_tag *)      0xFFF84000UL)
#define PIT_1           (*(volatile struct PIT_tag *)      0xFFF80000UL)
#define PLLDIG          (*(volatile struct PLLDIG_tag *)   0xFFFB0100UL)
#define PMCDIG          (*(volatile struct PMCDIG_tag *)   0xFFFA0400UL)
#define PRAMC           (*(volatile struct PRAMC_tag *)    0xFC020000UL)
#define PSI5_0          (*(volatile struct PSI5_tag *)     0xFFE40000UL)
#define PSI5S           (*(volatile struct PSI5S_tag *)    0xFBF74000UL)
#define EMIOS_0         (*(volatile struct eMIOS_tag *)    0xFFDEC000UL)
#define SDADC_0         (*(volatile struct SDADC_tag *)    0xFFF0C000UL)
#define SDADC_1         (*(volatile struct SDADC_tag *)    0xFBF0C000UL)
#define SDADC_2         (*(volatile struct SDADC_tag *)    0xFFF10000UL)
#define SDADC_3         (*(volatile struct SDADC_tag *)    0xFBF10000UL)
#define SDADC_4         (*(volatile struct SDADC_tag *)    0xFFF14000UL)
#define SDADC_5         (*(volatile struct SDADC_tag *)    0xFBF14000UL)
#define SDADC_6         (*(volatile struct SDADC_tag *)    0xFFF18000UL)
#define SDADC_7         (*(volatile struct SDADC_tag *)    0xFBF18000UL)
#define SDADC_8         (*(volatile struct SDADC_tag *)    0xFFF1C000UL)
#define SDADC_9         (*(volatile struct SDADC_tag *)    0xFBF1C000UL)
#define SDADC_10        (*(volatile struct SDADC_tag *)    0xFFF20000UL)
#define SDADC_11        (*(volatile struct SDADC_tag *)    0xFBF20000UL)
#define SDADC_12        (*(volatile struct SDADC_tag *)    0xFFF24000UL)
#define SDADC_13        (*(volatile struct SDADC_tag *)    0xFBF24000UL)
#define EQADC0_ADC01    (*(volatile struct EQADC_tag *)    0xFFE00000UL)
#define EQADC1_ADC23    (*(volatile struct EQADC_tag *)    0xFBE08000UL)
#define EQADC2_ADC45    (*(volatile struct EQADC_tag *)    0xFFE10000UL)
#define EQADC3_ADC67    (*(volatile struct EQADC_tag *)    0xFBE18000UL)
#define EQADC4_ADC89    (*(volatile struct EQADC_tag *)    0xFBE20000UL)
#define EQADC5_ADC1011  (*(volatile struct EQADC_tag *)    0xFFE04000UL)
#define EQADC6_ADC1213  (*(volatile struct EQADC_tag *)    0xFFE08000UL)
#define SEMA42          (*(volatile struct SEMA42_tag *)   0xFC03C000UL)
#define SIPI_0          (*(volatile struct SIPI_tag *)     0xFFFD0000UL)
#define SIUL            (*(volatile struct SIUL_tag *)     0xFFFC0000UL)
#define IGF 			(*(volatile struct IGF_tag *) 	   0xFFFC1800UL)
#define SMPU_0          (*(volatile struct SMPU_tag *)     0xFC010000UL)
#define SMPU_1          (*(volatile struct SMPU_tag *)     0xFC014000UL)
#define SRX_0           (*(volatile struct SRX_tag *)      0xFFE5C000UL)
#define SRX_1           (*(volatile struct SRX_tag *)      0xFBE5C000UL)
#define SSCM            (*(volatile struct SSCM_tag *)     0xFFFF8000UL)
#define STCU2           (*(volatile struct STCU2_tag *)    0xFFF44000UL)
#define STM_0           (*(volatile struct STM_tag *)      0xFC068000UL)
#define STM_1           (*(volatile struct STM_tag *)      0xFC06C000UL)
#define STM_2           (*(volatile struct STM_tag *)      0xFC070000UL)
#define STM_3           (*(volatile struct STM_tag *)      0xFC074000UL)
#define STM_4           (*(volatile struct STM_tag *)      0xFC078000UL)
#define STM_5           (*(volatile struct STM_tag *)      0xFC07C000UL)
#define SWT_0           (*(volatile struct SWT_tag *)      0xFC050000UL)
#define SWT_1           (*(volatile struct SWT_tag *)      0xFC054000UL)
#define SWT_2           (*(volatile struct SWT_tag *)      0xFC058000UL)
#define SWT_3           (*(volatile struct SWT_tag *)      0xFC05C000UL)
#define SWT_4           (*(volatile struct SWT_tag *)      0xFC044000UL)
#define SWT_5           (*(volatile struct SWT_tag *)      0xFC048000UL)
#define SWT_6           (*(volatile struct SWT_tag *)      0xFC04C000UL)
#define SWT_7_AO        (*(volatile struct SWT_tag *)      0xFC060000UL)
#define T40FMC0         (*(volatile struct C55FMC_tag *)   0xFFFE8000UL)
#define T40FMC1         (*(volatile struct C55FMC_tag *)   0xFFFE8800UL)
#define T40FMC2         (*(volatile struct C55FMC_tag *)   0xFFFE9000UL)
#define T40FMC3         (*(volatile struct C55FMC_tag *)   0xFFFE9800UL)
#define T40FMC4         (*(volatile struct C55FMC_tag *)   0xFFFEA000UL)
#define T40FMC5         (*(volatile struct C55FMC_tag *)   0xFFFEA800UL)
#define TDM             (*(volatile struct TDM_tag *)      0xFFF34000UL)
#define WKPU            (*(volatile struct WKPU_tag *)     0xFFF98000UL)
#define XBAR_0          (*(volatile struct XBAR_tag *)     0xFC004000UL)
#define XBAR_1          (*(volatile struct XBAR_tag *)     0xFC008000UL)
#define XBIC_0          (*(volatile struct XBIC_tag *)     0xFC018000UL)
#define XBIC_1          (*(volatile struct XBIC_tag *)     0xFC01C000UL)
#define XBIC_2          (*(volatile struct XBIC_tag *)     0xFC088000UL)
#define XBIC_3          (*(volatile struct XBIC_tag *)     0xFC098000UL)
#define XOSC            (*(volatile struct XOSC_tag *)     0xFFFB0080UL)
#define eDMA_0          (*(volatile struct eDMA_tag *)     0xFC0A0000UL)
#define eDMA_1          (*(volatile struct eDMA_tag *)     0xFC0A4000UL)
#define GMAC_0          (*(volatile struct GMAC_tag*)      0xFC0B0000UL)
#define RTC_API         (*(volatile struct RTCAPI_tag *)   0xFFEB0000UL)
#define SSI0			(*(volatile struct SSI_tag*)       0xD0000000UL)
#define SSI1			(*(volatile struct SSI_tag*)       0xE0000000UL)
#define CSRX_0          (*(volatile struct CSRX_tag *)     0xFFE58000UL)
#define PWM3012         (*(volatile struct PWM3012_tag *)  0xFC064000UL)
#define ACMP0           (*(volatile struct ACMP_tag *)     0xFFE28000UL)
#define ACMP1           (*(volatile struct ACMP_tag *)     0xFFE2C000UL)
#define ACMP2           (*(volatile struct ACMP_tag *)     0xFFE30000UL)
#define ACMP3           (*(volatile struct ACMP_tag *)     0xFFE34000UL)
#define ACMP4           (*(volatile struct ACMP_tag *)     0xFBE28000UL)
#define ACMP5           (*(volatile struct ACMP_tag *)     0xFBE2C000UL)
#define ACMP6           (*(volatile struct ACMP_tag *)     0xFBE30000UL)
#define ACMP7           (*(volatile struct ACMP_tag *)     0xFBE34000UL)
#define SPORT0          (*(volatile struct SPORT_REG *)    0xFBEE0000UL)
#define SPORT1          (*(volatile struct SPORT_REG *)    0xFBEE4000UL)

#ifdef __MWERKS__
#pragma pop
#endif
#ifdef __ghs__
#pragma ghs endnowarning
#endif
#ifdef  __cplusplus
}
#endif

#endif  /* defined(CCFC3012PT) */
#endif /* ifdef CCFC3012PT_H_ */
