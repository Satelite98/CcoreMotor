/****************************************************************************
*
* Copyright (c) 2023  C*Core -   All Rights Reserved
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
*   Project              : AUTOSAR 4.4.0 MCAL
*   Platform             : PowerPC
*   Peripheral           :
*   Dependencies         :
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           :
*   Build Version        :
*
*****************************************************************************/

/**
*   @file    Spi_LLDriver.h
*   @version 1.0.1
*
*      AUTOSAR 4.4.0 - Common Level Driver source file.
*    Autosar layer of Mcu MCAL driver.
*
*   @addtogroup Spi
*   @{
*/

#ifndef SPI_LLDRIVER_H
#define SPI_LLDRIVER_H
#ifdef __cplusplus
extern "C"{
#endif

#include "derivative.h"
#include "Spi.h"
#include "SchM_Spi.h"

/*==================================================================================================
SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SPI_LLD_H_VENDOR_ID                   176
#define SPI_LLD_H_AR_MAJOR_VER                4
#define SPI_LLD_H_AR_MINOR_VER                4
#define SPI_LLD_H_AR_PATCH_VER                0
#define SPI_LLD_H_SW_MAJOR_VER                1
#define SPI_LLD_H_SW_MINOR_VER                0
#define SPI_LLD_H_SW_PATCH_VER                1
#define SPI_LLD_H_MODULE_ID                   83
/*==================================================================================================
FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and SPI header file are of the same vendor */
#if (SPI_LLD_H_VENDOR_ID != SPI_CFG_VENDOR_ID)
#error "NON-MATCHED DATA : SPI_LLD_H_VENDOR_ID"
#endif

/* Check if current file and SPI header file are of the same Autosar version */
#if (SPI_LLD_H_AR_MAJOR_VER != SPI_CFG_AR_MAJOR_VER)
#error "NON-MATCHED DATA : SPI_LLD_H_AR_MAJOR_VER"
#endif
#if (SPI_LLD_H_AR_MINOR_VER != SPI_CFG_AR_MINOR_VER)
#error "NON-MATCHED DATA : SPI_LLD_H_AR_MINOR_VER"
#endif
#if (SPI_LLD_H_AR_PATCH_VER != SPI_CFG_AR_PATCH_VER)
#error "NON-MATCHED DATA : SPI_LLD_H_AR_PATCH_VER"
#endif

/* Check if current file and SPI header file are of the same Software version */
#if (SPI_LLD_H_SW_MAJOR_VER != SPI_CFG_SW_MAJOR_VER)
#error "NON-MATCHED DATA : SPI_LLD_H_SW_MAJOR_VER"
#endif
#if (SPI_LLD_H_SW_MINOR_VER != SPI_CFG_SW_MINOR_VER)
#error "NON-MATCHED DATA : SPI_LLD_H_SW_MINOR_VER"
#endif
#if (SPI_LLD_H_SW_PATCH_VER != SPI_CFG_SW_PATCH_VER)
#error "NON-MATCHED DATA : SPI_LLD_H_SW_PATCH_VER"
#endif

#define DSPI_MCR_RESET_VAL      0x00FF4001U
#define DSPI_SR_RESET_VAL       0xFEFF0000U
#define DSPI_RSER_RESET_VAL     0x00000000U
#define DSPI_CTAR_RESET_VAL     0x78000000U
#define DSPI_SPI_TCNT_RESET_VAL 0x00000000U

#define DSPI_PUSH_DATA_M        0x0000FFFFU
#define DSPI_PUSH_PCS_M         0x00FF0000U
#define DSPI_PUSH_PCS_S         16U
#define DSPI_PUSH_EOQ_M         0x08000000U
#define DSPI_PUSH_CONT_M        0x8000U
#define DSPI_TCF_CLEAR          0x80000000U

#define DEFAULT_FRAMEWIDTH      8U

#define SPI_HW_NUM              22U
#define SPI_FIFO_DEEP           4U
#define SPI_FIFO_HALF           2U
/* FIFO Watermark */
#define SPI_FIFO_WMK            3U

typedef volatile struct DSPI_tag  Spi_HwSpiType;


FUNC(void, SPI_CODE) dspi_Enable( VAR(uint8, AUTOMATIC) u8Spi_HwIdx );
FUNC(void, SPI_CODE) dspi_Disable( VAR(uint8, AUTOMATIC) u8Spi_HwIdx );
FUNC(void, SPI_CODE) Spi_Job_HwInit(P2VAR(Spi_HandleType, AUTOMATIC, SPI_APPL_DATA) Spi_HandlePtr);
FUNC(void, SPI_CODE) Spi_Channel_HwInit(P2VAR(Spi_HandleType, AUTOMATIC, SPI_APPL_DATA) Spi_HandlePtr);

#if(SPI_DMA_USED == STD_ON)
FUNC(void, SPI_CODE) dspi_DmaInit(
    P2VAR(Spi_HandleType, AUTOMATIC, SPI_APPL_DATA) Spi_HandlePtr );
#endif

FUNC(void, SPI_CODE) dspi_TransmitEnd(
    P2VAR(Spi_HandleType, AUTOMATIC, SPI_APPL_DATA) Spi_HandlePtr );

FUNC(void, SPI_CODE) dspi_TransmitEndInt( 
    P2VAR(Spi_HandleType, AUTOMATIC, SPI_APPL_DATA) Spi_HandlePtr );

#if(SPI_DMA_USED == STD_ON)
FUNC(void, SPI_CODE) dspi_TransmitEndDma(
    P2VAR(Spi_HandleType, AUTOMATIC, SPI_APPL_DATA) Spi_HandlePtr );
#endif

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
FUNC(void, SPI_CODE) dspi_TransmitReceive_polling (
    P2VAR(Spi_HandleType, AUTOMATIC, SPI_APPL_DATA) Spi_HandlePtr,
    P2VAR(uint8, SPI_VAR, SPI_APPL_DATA) Spi_TranDataPtr,
    P2VAR(uint8, SPI_VAR, SPI_APPL_DATA) Spi_RecDataPtr,
    VAR(uint32, SPI_VAR) Spi_u32DataLength );
#endif

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
FUNC(void, SPI_CODE) dspi_TransmitReceive_interrupt(
    P2VAR(Spi_HandleType, AUTOMATIC, SPI_APPL_DATA) Spi_HandlePtr );

#endif

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
#if (SPI_DMA_USED == STD_ON)
FUNC(void, SPI_CODE) dspi_TransmitReceive_dma (
    P2VAR(Spi_HandleType, AUTOMATIC, SPI_APPL_DATA) Spi_HandlePtr,
    P2VAR(uint8, SPI_VAR, SPI_APPL_DATA) Spi_TranDataPtr,
    P2VAR(uint8, SPI_VAR, SPI_APPL_DATA) Spi_RecDataPtr,
    VAR(uint32, SPI_VAR) Spi_u32DataLength );
#endif
#endif

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
FUNC(void, SPI_CODE) dspi_tcf(
    P2VAR(Spi_HandleType, AUTOMATIC, SPI_APPL_DATA) Spi_HandlePtr);
#endif

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
FUNC(void, SPI_CODE)dspi_MainFunc(
    P2VAR(Spi_HandleType, AUTOMATIC, SPI_APPL_DATA) Spi_HandlePtr );
#endif

#ifdef __cplusplus
}
#endif
#endif /* DSPI_H */
