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
*   @file    Spi_LLDriver.c
*   @version 1.0.1
*
*      AUTOSAR 4.4.0 - Common Level Driver source file.
*    Autosar layer of SPI MCAL driver.
*
*   @addtogroup Spi
*   @{
*/
#include "SchM_Spi.h"
#ifdef __cplusplus
extern "C"{
#endif

#include "Spi_AutoSAR_Wrapper.h"
#if(SPI_DMA_USED == STD_ON)
#include "eDma.h"
#endif

/*==================================================================================================
SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SPI_LLD_C_VENDOR_ID                   176
#define SPI_LLD_C_AR_MAJOR_VER                4
#define SPI_LLD_C_AR_MINOR_VER                4
#define SPI_LLD_C_AR_PATCH_VER                0
#define SPI_LLD_C_SW_MAJOR_VER                1
#define SPI_LLD_C_SW_MINOR_VER                0
#define SPI_LLD_C_SW_PATCH_VER                1
#define SPI_LLD_C_MODULE_ID                   83
/*==================================================================================================
FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and SPI header file are of the same vendor */
#if (SPI_LLD_C_VENDOR_ID != SPI_CFG_VENDOR_ID)
#error "NON-MATCHED DATA : SPI_LLD_C_VENDOR_ID"
#endif

/* Check if current file and SPI header file are of the same Autosar version */
#if (SPI_LLD_C_AR_MAJOR_VER != SPI_CFG_AR_MAJOR_VER)
#error "NON-MATCHED DATA : SPI_LLD_C_AR_MAJOR_VER"
#endif
#if (SPI_LLD_C_AR_MINOR_VER != SPI_CFG_AR_MINOR_VER)
#error "NON-MATCHED DATA : SPI_LLD_C_AR_MINOR_VER"
#endif
#if (SPI_LLD_C_AR_PATCH_VER != SPI_CFG_AR_PATCH_VER)
#error "NON-MATCHED DATA : SPI_LLD_C_AR_PATCH_VER"
#endif

/* Check if current file and SPI header file are of the same Software version */
#if (SPI_LLD_C_SW_MAJOR_VER != SPI_CFG_SW_MAJOR_VER)
#error "NON-MATCHED DATA : SPI_LLD_C_SW_MAJOR_VER"
#endif
#if (SPI_LLD_C_SW_MINOR_VER != SPI_CFG_SW_MINOR_VER)
#error "NON-MATCHED DATA : SPI_LLD_C_SW_MINOR_VER"
#endif
#if (SPI_LLD_C_SW_PATCH_VER != SPI_CFG_SW_PATCH_VER)
#error "NON-MATCHED DATA : SPI_LLD_C_SW_PATCH_VER"
#endif

#define DSPI_FORCE8(addr,offset)             ((uint32)((uint32)((uint8 *)(addr))[(offset)] /* >> 0U */) & (uint32)(DSPI_PUSH_DATA_M))
#define DSPI_FORCE16(addr,offset)            ((uint32)((uint32)((uint16 *)(addr))[(offset)] /* >> 0U */) & (uint32)(DSPI_PUSH_DATA_M))
#define DSPI_FORCE32_L(addr,offset)          ((uint32)((uint32)((uint32 *)(addr))[(offset)] >> 16U) & (uint32)(DSPI_PUSH_DATA_M))
#define DSPI_FORCE32_H(addr,offset)          ((uint32)((uint32)((uint32 *)(addr))[(offset)] /* >> 0U */) & (uint32)(DSPI_PUSH_DATA_M))


#define SPI_START_SEC_VAR_INIT
#include "Spi_MemMap.h"

static CONSTP2VAR(Spi_HwSpiType, SPI_CONST, SPI_APPL_CODE) \
    SpiHwUnit[SPI_HW_NUM] = \
    {
        ((Spi_HwSpiType* )0xFFE70000UL),((Spi_HwSpiType* )0xFFE74000UL), \
        ((Spi_HwSpiType* )0xFBE70000UL),((Spi_HwSpiType* )0xFBE74000UL), \
        ((Spi_HwSpiType* )0xFFE78000UL),((Spi_HwSpiType* )0xFBE78000UL), \
        ((Spi_HwSpiType* )0xFFE7C000UL),((Spi_HwSpiType* )0xFBE7C000UL), \
        ((Spi_HwSpiType* )0xFFE80000UL),((Spi_HwSpiType* )0xFBE80000UL), \
        ((Spi_HwSpiType* )0xFFE84000UL),((Spi_HwSpiType* )0xFBE84000UL), \
        ((Spi_HwSpiType* )0xFFE88000UL),((Spi_HwSpiType* )0xFBE88000UL), \
        ((Spi_HwSpiType* )0xFFE60000UL),((Spi_HwSpiType* )0xFFE64000UL), \
        ((Spi_HwSpiType* )0xFBE44000UL),((Spi_HwSpiType* )0xFBE48000UL), \
        ((Spi_HwSpiType* )0xFBE4C000UL),((Spi_HwSpiType* )0xFFE44000UL), \
        ((Spi_HwSpiType* )0xFFE48000UL),((Spi_HwSpiType* )0xFFE4C000UL), \
    };

#define SPI_STOP_SEC_VAR_INIT
#include "Spi_MemMap.h"


/* ********************************************************************** */
/* Read Write 8 Bit */
/* ********************************************************************** */
LOCAL_INLINE FUNC(void, SPI_CODE) WriteReadData_RW_B \
( \
    P2VAR(uint32, SPI_VAR, SPI_APPL_DATA)Spi_RxCnt, \
    P2VAR(uint32, SPI_VAR, SPI_APPL_DATA)Spi_TxCnt, \
    VAR(uint32, SPI_VAR)Spi_DataLen, \
    P2VAR(uint8, SPI_VAR, SPI_APPL_DATA)Spi_RxBuf, \
    P2VAR(uint8, SPI_VAR, SPI_APPL_DATA)Spi_TxBuf, \
    P2VAR(uint8, SPI_VAR, SPI_APPL_DATA)Spi_FifoTxCnt, \
    P2VAR(Spi_HwSpiType , SPI_VAR, SPI_APPL_DATA) Spi_HwPtr \
)
{
    while((*Spi_RxCnt) < Spi_DataLen)
    {
        if(Spi_HwPtr->SR.B.RXCTR != 0U)
        {
            ((uint8 *)Spi_RxBuf)[(*Spi_RxCnt)] \
                = (uint8)(Spi_HwPtr->POPR.R);
            (*Spi_RxCnt)++;
            (*Spi_FifoTxCnt)--;
        }
        else
        {
            break;
        }
    }
    while(((*Spi_TxCnt) < Spi_DataLen) && ((*Spi_FifoTxCnt) < SPI_FIFO_DEEP))
    {
        Spi_HwPtr->PUSHR.PUSHR.B.TXDATA = DSPI_FORCE8(Spi_TxBuf,(*Spi_TxCnt));
        (*Spi_TxCnt)++;
        (*Spi_FifoTxCnt)++;
    }
}

/* ********************************************************************** */
/* Read Write 16 Bit */
/* ********************************************************************** */
LOCAL_INLINE FUNC(void, SPI_CODE) WriteReadData_RW_W \
( \
    P2VAR(uint32, SPI_VAR, SPI_APPL_DATA)Spi_RxCnt, \
    P2VAR(uint32, SPI_VAR, SPI_APPL_DATA)Spi_TxCnt, \
    VAR(uint32, SPI_VAR)Spi_DataLen, \
    P2VAR(uint16, SPI_VAR, SPI_APPL_DATA)Spi_RxBuf, \
    P2VAR(uint16, SPI_VAR, SPI_APPL_DATA)Spi_TxBuf, \
    P2VAR(uint8, SPI_VAR, SPI_APPL_DATA)Spi_FifoTxCnt, \
    P2VAR(Spi_HwSpiType , SPI_VAR, SPI_APPL_DATA) Spi_HwPtr \
)
{
    while((*Spi_RxCnt) < Spi_DataLen)
    {
        if(Spi_HwPtr->SR.B.RXCTR != 0U)
        {
            ((uint16 *)Spi_RxBuf)[(*Spi_RxCnt)] \
                = (uint16)(Spi_HwPtr->POPR.R);
            (*Spi_RxCnt)++;
            (*Spi_FifoTxCnt)--;
        }
        else
        {
            break;
        }
    }
    while(((*Spi_TxCnt) < Spi_DataLen) && ((*Spi_FifoTxCnt) < SPI_FIFO_DEEP))
    {
        Spi_HwPtr->PUSHR.PUSHR.B.TXDATA = DSPI_FORCE16(Spi_TxBuf,(*Spi_TxCnt));
        (*Spi_TxCnt)++;
        (*Spi_FifoTxCnt)++;
    }
}

/* ********************************************************************** */
/* Read Write 32 Bit */
/* ********************************************************************** */
LOCAL_INLINE FUNC(void, SPI_CODE) WriteReadData_RW_I \
( \
    P2VAR(uint32, SPI_VAR, SPI_APPL_DATA)Spi_RxCnt, \
    P2VAR(uint32, SPI_VAR, SPI_APPL_DATA)Spi_TxCnt, \
    VAR(uint32, SPI_VAR)Spi_DataLen, \
    P2VAR(uint32, SPI_VAR, SPI_APPL_DATA)Spi_RxBuf, \
    P2VAR(uint32, SPI_VAR, SPI_APPL_DATA)Spi_TxBuf, \
    P2VAR(uint8, SPI_VAR, SPI_APPL_DATA)Spi_FifoTxCnt, \
    P2VAR(Spi_HwSpiType , SPI_VAR, SPI_APPL_DATA) Spi_HwPtr \
)
{
    while((*Spi_RxCnt) < Spi_DataLen)
    {
        if(Spi_HwPtr->SR.B.RXCTR != 0U)
        {
            ((uint32 *)Spi_RxBuf)[(*Spi_RxCnt)] \
                = (uint32)(Spi_HwPtr->POPR.R);
            (*Spi_RxCnt)++;
            (*Spi_FifoTxCnt)--;
        }
        else
        {
            break;
        }
    }
    while(((*Spi_TxCnt) < Spi_DataLen) && ((*Spi_FifoTxCnt) < SPI_FIFO_HALF))
    {
        Spi_HwPtr->PUSHR.PUSHR.B.TXDATA = (uint16)DSPI_FORCE32_L(Spi_TxBuf,(*Spi_TxCnt));
        Spi_HwPtr->PUSHR.PUSHR.B.TXDATA = (uint16)DSPI_FORCE32_H(Spi_TxBuf, (*Spi_TxCnt));
        (*Spi_TxCnt)++;
        (*Spi_FifoTxCnt)++;
    }
}

/* ********************************************************************** */
/* Write 8 Bit */
/* ********************************************************************** */
LOCAL_INLINE FUNC(void, SPI_CODE) WriteReadData_W_B \
( \
    P2VAR(uint32, SPI_VAR, SPI_APPL_DATA)Spi_RxCnt, \
    P2VAR(uint32, SPI_VAR, SPI_APPL_DATA)Spi_TxCnt, \
    VAR(uint32, SPI_VAR)Spi_DataLen, \
    P2VAR(uint8, SPI_VAR, SPI_APPL_DATA)Spi_TxBuf, \
    P2VAR(uint8, SPI_VAR, SPI_APPL_DATA)Spi_FifoTxCnt, \
    P2VAR(Spi_HwSpiType , SPI_VAR, SPI_APPL_DATA) Spi_HwPtr \
)
{
    VAR(uint8, SPI_VAR)Spi_TempData;
    while((*Spi_RxCnt) < Spi_DataLen)
    {
        if(Spi_HwPtr->SR.B.RXCTR != 0U)
        {
            Spi_TempData = (uint8)(Spi_HwPtr->POPR.R);
            (*Spi_RxCnt)++;
            (*Spi_FifoTxCnt)--;
        }
        else
        {
            break;
        }
    }
    (void)Spi_TempData;
    while(((*Spi_TxCnt) < Spi_DataLen) && ((*Spi_FifoTxCnt) < SPI_FIFO_DEEP))
    {
        Spi_HwPtr->PUSHR.PUSHR.B.TXDATA = DSPI_FORCE8(Spi_TxBuf,(*Spi_TxCnt));
        (*Spi_TxCnt)++;
        (*Spi_FifoTxCnt)++;
    }
}

/* ********************************************************************** */
/* Write 16 Bit */
/* ********************************************************************** */
LOCAL_INLINE FUNC(void, SPI_CODE) WriteReadData_W_W \
( \
    P2VAR(uint32, SPI_VAR, SPI_APPL_DATA)Spi_RxCnt, \
    P2VAR(uint32, SPI_VAR, SPI_APPL_DATA)Spi_TxCnt, \
    VAR(uint32, SPI_VAR)Spi_DataLen, \
    P2VAR(uint16, SPI_VAR, SPI_APPL_DATA)Spi_TxBuf, \
    P2VAR(uint8, SPI_VAR, SPI_APPL_DATA)Spi_FifoTxCnt, \
    P2VAR(Spi_HwSpiType , SPI_VAR, SPI_APPL_DATA) Spi_HwPtr \
)
{
    VAR(uint16, SPI_VAR)Spi_TempData;
    while((*Spi_RxCnt) < Spi_DataLen)
    {
        if(Spi_HwPtr->SR.B.RXCTR != 0U)
        {
            Spi_TempData = (uint16)(Spi_HwPtr->POPR.R);
            (*Spi_RxCnt)++;
            (*Spi_FifoTxCnt)--;
        }
        else
        {
            break;
        }
    }
    (void)Spi_TempData;
    while(((*Spi_TxCnt) < Spi_DataLen) && ((*Spi_FifoTxCnt) < SPI_FIFO_DEEP))
    {
        Spi_HwPtr->PUSHR.PUSHR.B.TXDATA = DSPI_FORCE16(Spi_TxBuf,(*Spi_TxCnt));
        (*Spi_TxCnt)++;
        (*Spi_FifoTxCnt)++;
    }
}

/* ********************************************************************** */
/* Write 32 Bit */
/* ********************************************************************** */
LOCAL_INLINE FUNC(void, SPI_CODE) WriteReadData_W_I \
( \
    P2VAR(uint32, SPI_VAR, SPI_APPL_DATA)Spi_RxCnt, \
    P2VAR(uint32, SPI_VAR, SPI_APPL_DATA)Spi_TxCnt, \
    VAR(uint32, SPI_VAR)Spi_DataLen, \
    P2VAR(uint32, SPI_VAR, SPI_APPL_DATA)Spi_TxBuf, \
    P2VAR(uint8, SPI_VAR, SPI_APPL_DATA)Spi_FifoTxCnt, \
    P2VAR(Spi_HwSpiType , SPI_VAR, SPI_APPL_DATA) Spi_HwPtr \
)
{
    VAR(uint32, SPI_VAR)Spi_TempData;
    while((*Spi_RxCnt) < Spi_DataLen)
    {
        if(Spi_HwPtr->SR.B.RXCTR != 0U)
        {
            Spi_TempData = (uint32)(Spi_HwPtr->POPR.R);
            (*Spi_RxCnt)++;
            (*Spi_FifoTxCnt)--;
        }
        else
        {
            break;
        }
    }
    (void)Spi_TempData;
    while(((*Spi_TxCnt) < Spi_DataLen) && ((*Spi_FifoTxCnt) < SPI_FIFO_HALF))
    {
        Spi_HwPtr->PUSHR.PUSHR.B.TXDATA = DSPI_FORCE32_L(Spi_TxBuf,(*Spi_TxCnt));
        Spi_HwPtr->PUSHR.PUSHR.B.TXDATA = DSPI_FORCE32_H(Spi_TxBuf, (*Spi_TxCnt));
        (*Spi_TxCnt)++;
        (*Spi_FifoTxCnt)++;
    }
}

/* ********************************************************************** */
/* Read 8 Bit */
/* ********************************************************************** */
LOCAL_INLINE FUNC(void, SPI_CODE) WriteReadData_R_B \
( \
    P2VAR(uint32, SPI_VAR, SPI_APPL_DATA)Spi_RxCnt, \
    P2VAR(uint32, SPI_VAR, SPI_APPL_DATA)Spi_TxCnt, \
    VAR(uint32, SPI_VAR)Spi_DataLen, \
    P2VAR(uint8, SPI_VAR, SPI_APPL_DATA)Spi_RxBuf, \
    VAR(uint32, SPI_VAR) Spi_TxData, \
    P2VAR(uint8, SPI_VAR, SPI_APPL_DATA)Spi_FifoTxCnt, \
    P2VAR(Spi_HwSpiType , SPI_VAR, SPI_APPL_DATA) Spi_HwPtr \
)
{
    while((*Spi_RxCnt) < Spi_DataLen)
    {
        if(Spi_HwPtr->SR.B.RXCTR != 0U)
        {
            ((uint8 *)Spi_RxBuf)[(*Spi_RxCnt)] \
                = (uint8)(Spi_HwPtr->POPR.R);
            (*Spi_RxCnt)++;
            (*Spi_FifoTxCnt)--;
        }
        else
        {
            break;
        }
    }
    while(((*Spi_TxCnt) < Spi_DataLen) && ((*Spi_FifoTxCnt) < SPI_FIFO_DEEP))
    {
        Spi_HwPtr->PUSHR.PUSHR.B.TXDATA = ((uint32)Spi_TxData & (uint32)DSPI_PUSH_DATA_M);
        (*Spi_TxCnt)++;
        (*Spi_FifoTxCnt)++;
    }
}

/* ********************************************************************** */
/* Read 16 Bit */
/* ********************************************************************** */
LOCAL_INLINE FUNC(void, SPI_CODE) WriteReadData_R_W \
( \
    P2VAR(uint32, SPI_VAR, SPI_APPL_DATA)Spi_RxCnt, \
    P2VAR(uint32, SPI_VAR, SPI_APPL_DATA)Spi_TxCnt, \
    VAR(uint32, SPI_VAR)Spi_DataLen, \
    P2VAR(uint16, SPI_VAR, SPI_APPL_DATA)Spi_RxBuf, \
    VAR(uint32, SPI_VAR) Spi_TxData, \
    P2VAR(uint8, SPI_VAR, SPI_APPL_DATA)Spi_FifoTxCnt, \
    P2VAR(Spi_HwSpiType , SPI_VAR, SPI_APPL_DATA) Spi_HwPtr \
)
{
    while((*Spi_RxCnt) < Spi_DataLen)
    {
        if(Spi_HwPtr->SR.B.RXCTR != 0U)
        {
            ((uint16 *)Spi_RxBuf)[(*Spi_RxCnt)] \
                = (uint16)(Spi_HwPtr->POPR.R);
            (*Spi_RxCnt)++;
            (*Spi_FifoTxCnt)--;
        }
        else
        {
            break;
        }
    }
    while(((*Spi_TxCnt) < Spi_DataLen) && ((*Spi_FifoTxCnt) < SPI_FIFO_DEEP))
    {
        Spi_HwPtr->PUSHR.PUSHR.B.TXDATA = ((uint32)Spi_TxData & (uint32)DSPI_PUSH_DATA_M);
        (*Spi_TxCnt)++;
        (*Spi_FifoTxCnt)++;
    }
}

/* ********************************************************************** */
/* Read 32 Bit */
/* ********************************************************************** */
LOCAL_INLINE FUNC(void, SPI_CODE) WriteReadData_R_I \
( \
    P2VAR(uint32, SPI_VAR, SPI_APPL_DATA)Spi_RxCnt, \
    P2VAR(uint32, SPI_VAR, SPI_APPL_DATA)Spi_TxCnt, \
    VAR(uint32, SPI_VAR)Spi_DataLen, \
    P2VAR(uint32, SPI_VAR, SPI_APPL_DATA)Spi_RxBuf, \
    VAR(uint32, SPI_VAR) Spi_TxData, \
    P2VAR(uint8, SPI_VAR, SPI_APPL_DATA)Spi_FifoTxCnt, \
    P2VAR(Spi_HwSpiType , SPI_VAR, SPI_APPL_DATA) Spi_HwPtr \
)
{
    while((*Spi_RxCnt) < Spi_DataLen)
    {
        if(Spi_HwPtr->SR.B.RXCTR != 0U)
        {
            ((uint32 *)Spi_RxBuf)[(*Spi_RxCnt)] \
                = (uint32)(Spi_HwPtr->POPR.R);
            (*Spi_RxCnt)++;
            (*Spi_FifoTxCnt)--;
        }
        else
        {
            break;
        }
    }
    while(((*Spi_TxCnt) < Spi_DataLen) && ((*Spi_FifoTxCnt) < SPI_FIFO_HALF))
    {
        Spi_HwPtr->PUSHR.PUSHR.B.TXDATA = (((uint32)Spi_TxData >> 0U) & DSPI_PUSH_DATA_M);
        Spi_HwPtr->PUSHR.PUSHR.B.TXDATA = (((uint32)Spi_TxData >> 16U) & DSPI_PUSH_DATA_M);
        (*Spi_TxCnt)++;
        (*Spi_FifoTxCnt)++;
    }
}


FUNC(void, SPI_CODE) dspi_Enable( VAR(uint8, AUTOMATIC) u8Spi_HwIdx )
{
    // Interrupts are disabled
    P2VAR(Spi_HwSpiType , SPI_VAR, SPI_APPL_DATA) Spi_HwPtr = SpiHwUnit[u8Spi_HwIdx];
    VAR(uint8, MCU_VAR) Idx;
    /*Reset DSPI*/
    Spi_HwPtr->MCR.B.MDIS = (uint32)TRUE;
    Spi_HwPtr->MCR.B.MSTR = (uint32)TRUE;
    Spi_HwPtr->MCR.B.XSPI = (uint32)TRUE;
    /*Clear FIFO*/
    Spi_HwPtr->MCR.B.CLR_TXF = (uint32)TRUE;
    Spi_HwPtr->MCR.B.CLR_RXF = (uint32)TRUE;

    Spi_HwPtr->MCR.B.PCSIS = 0xFFU;
    /*Enable DSPI*/
    Spi_HwPtr->MCR.B.MDIS = (uint32)FALSE;
    Spi_HwPtr->MCR.B.HALT = (uint32)FALSE;
    for(Idx = 0U; Idx < 8U; Idx++)
    {
        Spi_HwPtr->MODE.CTAR[Idx].R = (uint32)DSPI_CTAR_RESET_VAL;
    }
    // Spi_HwPtr->MCR.B.HALT = (uint32)TRUE;
    // Interrupts are disabled
}

FUNC(void, SPI_CODE) dspi_Disable(VAR(uint8, AUTOMATIC) u8Spi_HwIdx)
{
    // Interrupts are disabled
    P2VAR(Spi_HwSpiType , SPI_VAR, SPI_APPL_DATA) Spi_HwPtr = SpiHwUnit[u8Spi_HwIdx];/* polyspace RTE:OBAI */
    VAR(uint8, MCU_VAR) Idx;
    Spi_HwPtr->MCR.B.MDIS = (uint32)TRUE;
    Spi_HwPtr->MCR.R = (uint32)DSPI_MCR_RESET_VAL;
    for(Idx = 0U; Idx < 8U; Idx++)
    {
        Spi_HwPtr->MODE.CTAR[Idx].R = (uint32)DSPI_CTAR_RESET_VAL;
    }
    Spi_HwPtr->TCR.B.SPI_TCNT = (uint32)DSPI_SPI_TCNT_RESET_VAL;
    Spi_HwPtr->RSER.R = (uint32)DSPI_RSER_RESET_VAL;
    Spi_HwPtr->SR.R = (uint32)DSPI_SR_RESET_VAL;
    // Interrupts are disabled
}

FUNC(void, SPI_CODE) Spi_Job_HwInit(
    P2VAR(Spi_HandleType, AUTOMATIC, SPI_APPL_DATA) Spi_HandlePtr)
{
    P2VAR(Spi_HwSpiType , SPI_VAR, SPI_APPL_DATA) Spi_HwPtr \
        = SpiHwUnit[(uint8)Spi_HandlePtr->HwDevice];
    /*Initialize the transfer Attributes*/
    if(Spi_HandlePtr->Pcs_Idle == 0U)
    {
        Spi_HwPtr->MCR.B.PCSIS = 0xFFU;
    }
    else
    {
        Spi_HwPtr->MCR.B.PCSIS = 0x00U;
    }
    // Spi_HwPtr->MODE.CTAR[Spi_HandlePtr->CtarSel].R = Spi_HandlePtr->Ctar;
    // Spi_HwPtr->MODE.CTAR[Spi_HandlePtr->CtarSel+1U].R = Spi_HandlePtr->Ctar;
    /*Clear Interrupt Enable Register*/
    Spi_HwPtr->RSER.R = (uint32)DSPI_RSER_RESET_VAL;
    /*Clear Status Register*/
    Spi_HwPtr->SR.R = (uint32)DSPI_SR_RESET_VAL;
    // Spi_HwPtr->MCR.B.HALT = (uint32)FALSE;
}

FUNC(void, SPI_CODE) Spi_Channel_HwInit(
    P2VAR(Spi_HandleType, AUTOMATIC, SPI_APPL_DATA) Spi_HandlePtr)
{
    P2VAR(uint16, SPI_VAR, SPI_APPL_DATA) Spi_PushCmd = NULL_PTR;
    P2VAR(Spi_HwSpiType , SPI_VAR, SPI_APPL_DATA) Spi_HwPtr \
        = SpiHwUnit[Spi_HandlePtr->HwDevice];/* polyspace RTE:OBAI */
    Spi_PushCmd = (uint16 *)(&Spi_HwPtr->PUSHR.PUSHR.R);
    /*Initialize the transfer Attributes*/
    if(Spi_HandlePtr->FrameSize > (uint8)16U)
    {
        Spi_HwPtr->CTARE[Spi_HandlePtr->CtarSel].R |= (uint32)0x10000U;/* polyspace RTE:OBAI */
        Spi_HwPtr->CTARE[Spi_HandlePtr->CtarSel+1U].R |= (uint32)0x10000U;/* polyspace RTE:OBAI */
    }
    else
    {
        Spi_HwPtr->CTARE[Spi_HandlePtr->CtarSel].R &= ~(uint32)0x10000U;/* polyspace RTE:OBAI */
        Spi_HwPtr->CTARE[Spi_HandlePtr->CtarSel+1U].R &= ~(uint32)0x10000U;/* polyspace RTE:OBAI */
    }
    Spi_HwPtr->MODE.CTAR[Spi_HandlePtr->CtarSel].R = Spi_HandlePtr->Ctar;
    Spi_HwPtr->MODE.CTAR[Spi_HandlePtr->CtarSel+1U].R = Spi_HandlePtr->Ctar;

    Spi_HwPtr->MCR.B.CLR_TXF = (uint32)TRUE;
    Spi_HwPtr->MCR.B.CLR_RXF = (uint32)TRUE;
    /*Clear Status Register*/
    Spi_HwPtr->SR.R = (uint32)DSPI_SR_RESET_VAL;

    if(Spi_HandlePtr->LastChannel)
    {
        Spi_HwPtr->CTARE[Spi_HandlePtr->CtarSel+1U].B.DTCP = (uint32)1U;
        if(Spi_HandlePtr->Spi_DataLength != 1U)
        {
            Spi_HwPtr->CTARE[Spi_HandlePtr->CtarSel].B.DTCP = (uint32)(Spi_HandlePtr->Spi_DataLength - 1U);
            *Spi_PushCmd = (uint16)(Spi_HandlePtr->PushCmd | (uint16)(Spi_HandlePtr->CtarSel << 12U));
        }
        *Spi_PushCmd = (uint16)((Spi_HandlePtr->PushCmd | (uint16)((Spi_HandlePtr->CtarSel+1U) << 12U) ) & ~0x8000U);
    }
    else
    {
        Spi_HwPtr->CTARE[Spi_HandlePtr->CtarSel].B.DTCP = (uint32)Spi_HandlePtr->Spi_DataLength;
        *Spi_PushCmd = (uint16)(Spi_HandlePtr->PushCmd | (uint16)(Spi_HandlePtr->CtarSel << 12U));
    }
}



#if(SPI_DMA_USED == STD_ON)
FUNC(void, SPI_CODE) dspi_DmaInit(
    P2VAR(Spi_HandleType, AUTOMATIC, SPI_APPL_DATA) Spi_HandlePtr)
{
    P2VAR(Spi_HwSpiType , SPI_VAR, SPI_APPL_DATA) Spi_HwPtr = SpiHwUnit[Spi_HandlePtr->HwDevice];
    Spi_HwPtr->RSER.B.RFDF_DIRS = 1U;
    Spi_HwPtr->RSER.B.TFFF_DIRS = 1U;
    Spi_HwPtr->RSER.B.RFDF_RE = 1U;
    Spi_HwPtr->RSER.B.TFFF_RE = 1U;

    if(Spi_gAsyncMode == SPI_INTERRUPT_MODE)
    {
        EDMA_SetUpCallback(Spi_HandlePtr->Spi_RxDmaChannelID, (eDMACallbackType)Spi_AsyncHandle, (void *)Spi_HandlePtr);
    }
}
#endif
FUNC(void, SPI_CODE) dspi_TransmitEnd( 
    P2VAR(Spi_HandleType, AUTOMATIC, SPI_APPL_DATA) Spi_HandlePtr )
{
    P2VAR(Spi_HwSpiType , SPI_VAR, SPI_APPL_DATA) Spi_HwPtr \
        = SpiHwUnit[Spi_HandlePtr->HwDevice];/* polyspace RTE:OBAI */
    // Spi_HwPtr->MCR.B.HALT = (uint32)TRUE;
    Spi_HwPtr->MCR.B.CLR_TXF = (uint32)TRUE;
    Spi_HwPtr->MCR.B.CLR_RXF = (uint32)TRUE;
    Spi_HwPtr->SR.R = (uint32)DSPI_SR_RESET_VAL;
}

FUNC(void, SPI_CODE) dspi_TransmitEndInt( 
    P2VAR(Spi_HandleType, AUTOMATIC, SPI_APPL_DATA) Spi_HandlePtr )
{
    P2VAR(Spi_HwSpiType , SPI_VAR, SPI_APPL_DATA) Spi_HwPtr \
        = SpiHwUnit[Spi_HandlePtr->HwDevice];/* polyspace RTE:OBAI */
    // Spi_HwPtr->MCR.B.HALT = (uint32)TRUE;
    Spi_HwPtr->RSER.R = (uint32)DSPI_RSER_RESET_VAL;
    Spi_HwPtr->MCR.B.CLR_TXF = (uint32)TRUE;
    Spi_HwPtr->MCR.B.CLR_RXF = (uint32)TRUE;
    Spi_HwPtr->SR.R = (uint32)DSPI_SR_RESET_VAL;
}

#if(SPI_DMA_USED == STD_ON)
FUNC(void, SPI_CODE) dspi_TransmitEndDma( 
    P2VAR(Spi_HandleType, AUTOMATIC, SPI_APPL_DATA) Spi_HandlePtr )
{
    P2VAR(Spi_HwSpiType , SPI_VAR, SPI_APPL_DATA) Spi_HwPtr \
        = SpiHwUnit[Spi_HandlePtr->HwDevice];
    EDMA_SetInterruptConfig(Spi_HandlePtr->Spi_RxDmaChannelID, EDMA_CHN_ENABLE_MAJOR_LOOP_DONE_INT, FALSE);
    EDMA_SetInterruptConfig(Spi_HandlePtr->Spi_TxDmaChannelID, EDMA_CHN_ENABLE_MAJOR_LOOP_DONE_INT, FALSE);
    // Spi_HwPtr->MCR.B.HALT = (uint32)TRUE;
    Spi_HwPtr->MCR.B.CLR_TXF = (uint32)TRUE;
    Spi_HwPtr->MCR.B.CLR_RXF = (uint32)TRUE;
    Spi_HwPtr->RSER.B.RFDF_DIRS = 0U;
    Spi_HwPtr->RSER.B.TFFF_DIRS = 0U;
    Spi_HwPtr->RSER.B.RFDF_RE = 0U;
    Spi_HwPtr->RSER.B.TFFF_RE = 0U;
    Spi_HwPtr->SR.R = (uint32)DSPI_SR_RESET_VAL;
}
#endif


#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
FUNC(void, SPI_CODE) dspi_TransmitReceive_polling ( 
    P2VAR(Spi_HandleType, AUTOMATIC, SPI_APPL_DATA) Spi_HandlePtr,
    P2VAR(uint8, SPI_VAR, SPI_APPL_DATA) Spi_TranDataPtr,
    P2VAR(uint8, SPI_VAR, SPI_APPL_DATA) Spi_RecDataPtr,
    VAR(uint32, SPI_VAR) Spi_u32DataLength )
{
    P2VAR(Spi_HwSpiType , SPI_VAR, SPI_APPL_DATA) Spi_HwPtr
        = SpiHwUnit[(uint32)Spi_HandlePtr->HwDevice];

    VAR(uint32, SPI_VAR)Spi_RxCnt = 0;
    VAR(uint32, SPI_VAR)Spi_TxCnt = 0;
    VAR(uint8, SPI_VAR) Spi_FifoTxCnt = 0;

    if((Spi_TranDataPtr != NULL_PTR) && (Spi_RecDataPtr != NULL_PTR))
    {
        if(Spi_HandlePtr->FrameSize <= 8U)
        {
            while((Spi_RxCnt < Spi_u32DataLength) || (Spi_TxCnt < Spi_u32DataLength))
            {
                WriteReadData_RW_B( &Spi_RxCnt,
                                    &Spi_TxCnt,
                                    Spi_u32DataLength,
                                    (uint8 *)Spi_RecDataPtr,
                                    (uint8 *)Spi_TranDataPtr,
                                    &Spi_FifoTxCnt,
                                    Spi_HwPtr);
            }
        }
        else if(Spi_HandlePtr->FrameSize <= 16U)
        {
            while((Spi_RxCnt < Spi_u32DataLength) || (Spi_TxCnt < Spi_u32DataLength))
            {
                WriteReadData_RW_W( &Spi_RxCnt,
                                    &Spi_TxCnt,
                                    Spi_u32DataLength,
                                    (uint16 *)Spi_RecDataPtr,
                                    (uint16 *)Spi_TranDataPtr,
                                    &Spi_FifoTxCnt,
                                    Spi_HwPtr);
            }
        }
        else if(Spi_HandlePtr->FrameSize <= 32U)
        {
            while((Spi_RxCnt < Spi_u32DataLength) || (Spi_TxCnt < Spi_u32DataLength))
            {
                WriteReadData_RW_I( &Spi_RxCnt,
                                    &Spi_TxCnt,
                                    Spi_u32DataLength,
                                    (uint32 *)Spi_RecDataPtr,
                                    (uint32 *)Spi_TranDataPtr,
                                    &Spi_FifoTxCnt,
                                    Spi_HwPtr);
            }
        }
        else
        {
            /* Do nothing */
        }
    }
    else if((Spi_TranDataPtr != NULL_PTR) && (Spi_RecDataPtr == NULL_PTR))
    {
        if(Spi_HandlePtr->FrameSize <= 8U)
        {
            while((Spi_RxCnt < Spi_u32DataLength) || (Spi_TxCnt < Spi_u32DataLength))
            {
                WriteReadData_W_B( &Spi_RxCnt,
                                   &Spi_TxCnt,
                                   Spi_u32DataLength,
                                   (uint8 *)Spi_TranDataPtr,
                                   &Spi_FifoTxCnt,
                                   Spi_HwPtr);
            }
        }
        else if(Spi_HandlePtr->FrameSize <= 16U)
        {
            while((Spi_RxCnt < Spi_u32DataLength) || (Spi_TxCnt < Spi_u32DataLength))
            {
                WriteReadData_W_W( &Spi_RxCnt,
                                   &Spi_TxCnt,
                                   Spi_u32DataLength,
                                   (uint16 *)Spi_TranDataPtr,
                                   &Spi_FifoTxCnt,
                                   Spi_HwPtr);
            }
        }
        else if(Spi_HandlePtr->FrameSize <= 32U)
        {
            while((Spi_RxCnt < Spi_u32DataLength) || (Spi_TxCnt < Spi_u32DataLength))
            {
                WriteReadData_W_I( &Spi_RxCnt,
                                   &Spi_TxCnt,
                                   Spi_u32DataLength,
                                   (uint32 *)Spi_TranDataPtr,
                                   &Spi_FifoTxCnt,
                                   Spi_HwPtr);
            }
        }
        else
        {
            /* Do nothing */
        }
    }
    else if((Spi_TranDataPtr == NULL_PTR) && (Spi_RecDataPtr != NULL_PTR))
    {
        if(Spi_HandlePtr->FrameSize <= 8U)
        {
            while((Spi_RxCnt < Spi_u32DataLength) || (Spi_TxCnt < Spi_u32DataLength))
            {
                WriteReadData_R_B( &Spi_RxCnt,
                                   &Spi_TxCnt,
                                   Spi_u32DataLength,
                                   (uint8 *)Spi_RecDataPtr,
                                   (uint8)Spi_HandlePtr->TranDefaultData,
                                   &Spi_FifoTxCnt,
                                   Spi_HwPtr);
            }
        }
        else if(Spi_HandlePtr->FrameSize <= 16U)
        {
            while((Spi_RxCnt < Spi_u32DataLength) || (Spi_TxCnt < Spi_u32DataLength))
            {
                WriteReadData_R_W( &Spi_RxCnt,
                                   &Spi_TxCnt,
                                   Spi_u32DataLength,
                                   (uint16 *)Spi_RecDataPtr,
                                   (uint16)Spi_HandlePtr->TranDefaultData,
                                   &Spi_FifoTxCnt,
                                   Spi_HwPtr);
            }
        }
        else if(Spi_HandlePtr->FrameSize <= 32U)
        {
            while((Spi_RxCnt < Spi_u32DataLength) || (Spi_TxCnt < Spi_u32DataLength))
            {
                WriteReadData_R_I( &Spi_RxCnt,
                                   &Spi_TxCnt,
                                   Spi_u32DataLength,
                                   (uint32 *)Spi_RecDataPtr,
                                   (uint32)Spi_HandlePtr->TranDefaultData,
                                   &Spi_FifoTxCnt,
                                   Spi_HwPtr);
            }
        }
        else
        {
            /* Do nothing */
        }
    }
    else
    {
        /* Do nothing */
    }
}
#endif

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
LOCAL_INLINE FUNC(void, SPI_CODE) dspi_DataHandle(
    P2VAR(Spi_HandleType, AUTOMATIC, SPI_APPL_DATA) Spi_HandlePtr
)
{
    SchM_Enter_SPI_EXCLUSIVE_AREA_x(12);  /* Critical region protection */
    P2VAR(Spi_HwSpiType , SPI_VAR, SPI_APPL_DATA) Spi_HwPtr
        = SpiHwUnit[(uint32)Spi_HandlePtr->HwDevice];
    switch (Spi_HandlePtr->Spi_TranFuncType)
    {
        case RW_B:
        {
            WriteReadData_RW_B( &Spi_HandlePtr->Spi_RxCnt,
                                &Spi_HandlePtr->Spi_TxCnt,
                                Spi_HandlePtr->Spi_DataLength,
                                (uint8 *)Spi_HandlePtr->Spi_RecBufPtr,
                                (uint8 *)Spi_HandlePtr->Spi_TranBufPtr,
                                &Spi_HandlePtr->Spi_FifoTxCnt,
                                Spi_HwPtr);
        }break;
        case RW_W:
        {
            WriteReadData_RW_W( &Spi_HandlePtr->Spi_RxCnt,
                                &Spi_HandlePtr->Spi_TxCnt,
                                Spi_HandlePtr->Spi_DataLength,
                                (uint16 *)Spi_HandlePtr->Spi_RecBufPtr,
                                (uint16 *)Spi_HandlePtr->Spi_TranBufPtr,
                                &Spi_HandlePtr->Spi_FifoTxCnt,
                                Spi_HwPtr);
        }break;
        case RW_I:
        {
            WriteReadData_RW_I( &Spi_HandlePtr->Spi_RxCnt,
                                &Spi_HandlePtr->Spi_TxCnt,
                                Spi_HandlePtr->Spi_DataLength,
                                (uint32 *)Spi_HandlePtr->Spi_RecBufPtr,
                                (uint32 *)Spi_HandlePtr->Spi_TranBufPtr,
                                &Spi_HandlePtr->Spi_FifoTxCnt,
                                Spi_HwPtr);
        }break;
        case W_B:
        {
            WriteReadData_W_B( &Spi_HandlePtr->Spi_RxCnt,
                               &Spi_HandlePtr->Spi_TxCnt,
                               Spi_HandlePtr->Spi_DataLength,
                               (uint8 *)Spi_HandlePtr->Spi_TranBufPtr,
                               &Spi_HandlePtr->Spi_FifoTxCnt,
                               Spi_HwPtr);
        }break;
        case W_W:
        {
            WriteReadData_W_W( &Spi_HandlePtr->Spi_RxCnt,
                               &Spi_HandlePtr->Spi_TxCnt,
                               Spi_HandlePtr->Spi_DataLength,
                               (uint16 *)Spi_HandlePtr->Spi_TranBufPtr,
                               &Spi_HandlePtr->Spi_FifoTxCnt,
                               Spi_HwPtr);
        }break;
        case W_I:
        {
            WriteReadData_W_I( &Spi_HandlePtr->Spi_RxCnt,
                               &Spi_HandlePtr->Spi_TxCnt,
                               Spi_HandlePtr->Spi_DataLength,
                               (uint32 *)Spi_HandlePtr->Spi_TranBufPtr,
                               &Spi_HandlePtr->Spi_FifoTxCnt,
                               Spi_HwPtr);
        }break;
        case R_B:
        {
            WriteReadData_R_B( &Spi_HandlePtr->Spi_RxCnt,
                               &Spi_HandlePtr->Spi_TxCnt,
                               Spi_HandlePtr->Spi_DataLength,
                               (uint8 *)Spi_HandlePtr->Spi_RecBufPtr,
                               (uint32)Spi_HandlePtr->TranDefaultData,
                               &Spi_HandlePtr->Spi_FifoTxCnt,
                               Spi_HwPtr);
        }break;
        case R_W:
        {
            WriteReadData_R_W( &Spi_HandlePtr->Spi_RxCnt,
                               &Spi_HandlePtr->Spi_TxCnt,
                               Spi_HandlePtr->Spi_DataLength,
                               (uint16 *)Spi_HandlePtr->Spi_RecBufPtr,
                               (uint32)Spi_HandlePtr->TranDefaultData,
                               &Spi_HandlePtr->Spi_FifoTxCnt,
                               Spi_HwPtr);
        }break;
        case R_I:
        {
            WriteReadData_R_I( &Spi_HandlePtr->Spi_RxCnt,
                               &Spi_HandlePtr->Spi_TxCnt,
                               Spi_HandlePtr->Spi_DataLength,
                               (uint32 *)Spi_HandlePtr->Spi_RecBufPtr,
                               (uint32)Spi_HandlePtr->TranDefaultData,
                               &Spi_HandlePtr->Spi_FifoTxCnt,
                               Spi_HwPtr);
        }break;
    default:
        break;
    }
    SchM_Exit_SPI_EXCLUSIVE_AREA_x(12);  /* Critical region protection */
}
#endif


#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
FUNC(void, SPI_CODE) dspi_TransmitReceive_interrupt ( 
    P2VAR(Spi_HandleType, AUTOMATIC, SPI_APPL_DATA) Spi_HandlePtr )
{
    P2VAR(Spi_HwSpiType , SPI_VAR, SPI_APPL_DATA) Spi_HwPtr
        = SpiHwUnit[Spi_HandlePtr->HwDevice];

    Spi_HandlePtr->Spi_RxCnt = 0U;
    Spi_HandlePtr->Spi_TxCnt = 0U;
    Spi_HandlePtr->Spi_FifoTxCnt = 0U;
    if(Spi_gAsyncMode == SPI_INTERRUPT_MODE)
    {
        Spi_HwPtr->RSER.B.TCF_RE = (uint32)TRUE;
    }

    if((Spi_HandlePtr->Spi_TranBufPtr != NULL_PTR) && (Spi_HandlePtr->Spi_RecBufPtr != NULL_PTR))
    {
        if(Spi_HandlePtr->FrameSize <= 8U)
        {
            Spi_HandlePtr->Spi_TranFuncType = RW_B;
        }
        else if(Spi_HandlePtr->FrameSize <= 16U)
        {
            Spi_HandlePtr->Spi_TranFuncType = RW_W;
        }
        else if(Spi_HandlePtr->FrameSize <= 32U)
        {
            Spi_HandlePtr->Spi_TranFuncType = RW_I;
        }
        else
        {
            /* Do nothing */
        }
    }
    else if((Spi_HandlePtr->Spi_TranBufPtr != NULL_PTR) && (Spi_HandlePtr->Spi_RecBufPtr == NULL_PTR))
    {
        if(Spi_HandlePtr->FrameSize <= 8U)
        {
            Spi_HandlePtr->Spi_TranFuncType = W_B;
        }
        else if(Spi_HandlePtr->FrameSize <= 16U)
        {
            Spi_HandlePtr->Spi_TranFuncType = W_W;
        }
        else if(Spi_HandlePtr->FrameSize <= 32U)
        {
            Spi_HandlePtr->Spi_TranFuncType = W_I;
        }
        else
        {
            /* Do nothing */
        }
    }
    else if((Spi_HandlePtr->Spi_TranBufPtr == NULL_PTR) && (Spi_HandlePtr->Spi_RecBufPtr != NULL_PTR))
    {
        if(Spi_HandlePtr->FrameSize <= 8U)
        {
            Spi_HandlePtr->Spi_TranFuncType = R_B;
        }
        else if(Spi_HandlePtr->FrameSize <= 16U)
        {
            Spi_HandlePtr->Spi_TranFuncType = R_W;
        }
        else if(Spi_HandlePtr->FrameSize <= 32U)
        {
            Spi_HandlePtr->Spi_TranFuncType = R_I;
        }
        else
        {
            /* Do nothing */
        }
    }
    else
    {
        /* Do nothing */
    }

    dspi_DataHandle(Spi_HandlePtr);
}
#endif

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
#if(SPI_DMA_USED == STD_ON)
FUNC(void, SPI_CODE) dspi_TransmitReceive_dma (
    P2VAR(Spi_HandleType, AUTOMATIC, SPI_APPL_DATA) Spi_HandlePtr,
    P2VAR(uint8, SPI_VAR, SPI_APPL_DATA) Spi_TranDataPtr,
    P2VAR(uint8, SPI_VAR, SPI_APPL_DATA) Spi_RecDataPtr,
    VAR(uint32, SPI_VAR) Spi_u32DataLength )
{
    P2VAR(Spi_HwSpiType , SPI_VAR, SPI_APPL_DATA) Spi_HwPtr
        = SpiHwUnit[Spi_HandlePtr->HwDevice];
    static VAR(uint32, SPI_VAR)TempData = 0U;
    (void)TempData;

    if((Spi_TranDataPtr != NULL_PTR) && (Spi_RecDataPtr != NULL_PTR))
    {
        if(Spi_HandlePtr->FrameSize <= 8U)
        {
            EDMA_SetMultiTransferConfig( Spi_HandlePtr->Spi_TxDmaChannelID,
                                         EDMA_TRANSFER_TYPE_MEMTOPERIPH,
                                         (uint32)Spi_TranDataPtr,
                                         ((uint32)(&(Spi_HwPtr->PUSHR.PUSHR.R)) + (uint32)3U),
                                         EDMA_TRANSFER_SIZE_1B,
                                         1U,
                                         Spi_u32DataLength,
                                         true);

            EDMA_SetMultiTransferConfig( Spi_HandlePtr->Spi_RxDmaChannelID,
                                         EDMA_TRANSFER_TYPE_PERIPHTOMEM,
                                         ((uint32)(&(Spi_HwPtr->POPR.R)) + (uint32)3U),
                                         (uint32)Spi_RecDataPtr,
                                         EDMA_TRANSFER_SIZE_1B,
                                         1U,
                                         Spi_u32DataLength,
                                         true);
        }
        else if(Spi_HandlePtr->FrameSize <= 16U)
        {
            EDMA_SetMultiTransferConfig( Spi_HandlePtr->Spi_TxDmaChannelID,
                                         EDMA_TRANSFER_TYPE_MEMTOPERIPH,
                                         (uint32)Spi_TranDataPtr,
                                         ((uint32)(&(Spi_HwPtr->PUSHR.PUSHR.R)) + (uint32)2U),
                                         EDMA_TRANSFER_SIZE_2B,
                                         2U,
                                         Spi_u32DataLength,
                                         true);

            EDMA_SetMultiTransferConfig( Spi_HandlePtr->Spi_RxDmaChannelID,
                                         EDMA_TRANSFER_TYPE_PERIPHTOMEM,
                                         ((uint32)(&(Spi_HwPtr->POPR.R)) + (uint32)2U),
                                         (uint32)Spi_RecDataPtr,
                                         EDMA_TRANSFER_SIZE_2B,
                                         2U,
                                         Spi_u32DataLength,
                                         true);
        }
        else if(Spi_HandlePtr->FrameSize <= 32U)
        {
            EDMA_SetMultiTransferConfig( Spi_HandlePtr->Spi_TxDmaChannelID,
                                         EDMA_TRANSFER_TYPE_MEMTOPERIPH,
                                         (uint32)Spi_TranDataPtr,
                                         ((uint32)(&(Spi_HwPtr->PUSHR.PUSHR.R)) + (uint32)2U),
                                         EDMA_TRANSFER_SIZE_2B,
                                         2U,
                                         Spi_u32DataLength * 2,
                                         true);

            EDMA_SetMultiTransferConfig( Spi_HandlePtr->Spi_RxDmaChannelID,
                                         EDMA_TRANSFER_TYPE_PERIPHTOMEM,
                                         ((uint32)(&(Spi_HwPtr->POPR.R))/* + (uint32)2U */),
                                         (uint32)Spi_RecDataPtr,
                                         EDMA_TRANSFER_SIZE_4B,
                                         4U,
                                         Spi_u32DataLength,
                                         true);
        }
        else
        {
            /* Do nothing */
        }
    }
    else if((Spi_TranDataPtr != NULL_PTR) && (Spi_RecDataPtr == NULL_PTR))
    {
        if(Spi_HandlePtr->FrameSize <= 8U)
        {
            EDMA_SetMultiTransferConfig( Spi_HandlePtr->Spi_TxDmaChannelID,
                                         EDMA_TRANSFER_TYPE_MEMTOPERIPH,
                                         (uint32)Spi_TranDataPtr,
                                         ((uint32)(&(Spi_HwPtr->PUSHR.PUSHR.R)) + (uint32)3U),
                                         EDMA_TRANSFER_SIZE_1B,
                                         1U,
                                         Spi_u32DataLength,
                                         true);

            EDMA_SetMultiTransferConfig( Spi_HandlePtr->Spi_RxDmaChannelID,
                                         EDMA_TRANSFER_TYPE_PERIPHTOPERIPH,
                                         ((uint32)(&(Spi_HwPtr->POPR.R)) + (uint32)3U),
                                         (uint32)&TempData,
                                         EDMA_TRANSFER_SIZE_1B,
                                         1U,
                                         Spi_u32DataLength,
                                         true);
        }
        else if(Spi_HandlePtr->FrameSize <= 16U)
        {
            EDMA_SetMultiTransferConfig( Spi_HandlePtr->Spi_TxDmaChannelID,
                                         EDMA_TRANSFER_TYPE_MEMTOPERIPH,
                                         (uint32)Spi_TranDataPtr,
                                         ((uint32)(&(Spi_HwPtr->PUSHR.PUSHR.R)) + (uint32)2U),
                                         EDMA_TRANSFER_SIZE_2B,
                                         2U,
                                         Spi_u32DataLength,
                                         true);

            EDMA_SetMultiTransferConfig( Spi_HandlePtr->Spi_RxDmaChannelID,
                                         EDMA_TRANSFER_TYPE_PERIPHTOPERIPH,
                                         ((uint32)(&(Spi_HwPtr->POPR.R)) + (uint32)2U),
                                         (uint32)&TempData,
                                         EDMA_TRANSFER_SIZE_2B,
                                         2U,
                                         Spi_u32DataLength,
                                         true);
        }
        else if(Spi_HandlePtr->FrameSize <= 32U)
        {
            EDMA_SetMultiTransferConfig( Spi_HandlePtr->Spi_TxDmaChannelID,
                                         EDMA_TRANSFER_TYPE_MEMTOPERIPH,
                                         (uint32)Spi_TranDataPtr,
                                         ((uint32)(&(Spi_HwPtr->PUSHR.PUSHR.R)) + (uint32)2U),
                                         EDMA_TRANSFER_SIZE_2B,
                                         2U,
                                         Spi_u32DataLength * 2,
                                         true);

            EDMA_SetMultiTransferConfig( Spi_HandlePtr->Spi_RxDmaChannelID,
                                         EDMA_TRANSFER_TYPE_PERIPHTOPERIPH,
                                         ((uint32)(&(Spi_HwPtr->POPR.R))/* + (uint32)2U */),
                                         (uint32)&TempData,
                                         EDMA_TRANSFER_SIZE_4B,
                                         4U,
                                         Spi_u32DataLength,
                                         true);
        }
        else
        {
            /* Do nothing */
        }
    }
    else if((Spi_TranDataPtr == NULL_PTR) && (Spi_RecDataPtr != NULL_PTR))
    {
        if(Spi_HandlePtr->FrameSize <= 8U)
        {
            EDMA_SetMultiTransferConfig( Spi_HandlePtr->Spi_TxDmaChannelID,
                                         EDMA_TRANSFER_TYPE_PERIPHTOPERIPH,
                                         (uint32)((uint32)(&Spi_HandlePtr->TranDefaultData) + (uint32)3U),
                                         ((uint32)(&(Spi_HwPtr->PUSHR.PUSHR.R)) + (uint32)3U),
                                         EDMA_TRANSFER_SIZE_1B,
                                         1U,
                                         Spi_u32DataLength,
                                         true);

            EDMA_SetMultiTransferConfig( Spi_HandlePtr->Spi_RxDmaChannelID,
                                         EDMA_TRANSFER_TYPE_PERIPHTOMEM,
                                         ((uint32)(&(Spi_HwPtr->POPR.R)) + (uint32)3U),
                                         (uint32)Spi_RecDataPtr,
                                         EDMA_TRANSFER_SIZE_1B,
                                         1U,
                                         Spi_u32DataLength,
                                         true);
        }
        else if(Spi_HandlePtr->FrameSize <= 16U)
        {
            EDMA_SetMultiTransferConfig( Spi_HandlePtr->Spi_TxDmaChannelID,
                                         EDMA_TRANSFER_TYPE_PERIPHTOPERIPH,
                                         (uint32)((uint32)(&Spi_HandlePtr->TranDefaultData) + (uint32)2U),
                                         ((uint32)(&(Spi_HwPtr->PUSHR.PUSHR.R)) + (uint32)2U),
                                         EDMA_TRANSFER_SIZE_2B,
                                         2U,
                                         Spi_u32DataLength,
                                         true);

            EDMA_SetMultiTransferConfig( Spi_HandlePtr->Spi_RxDmaChannelID,
                                         EDMA_TRANSFER_TYPE_PERIPHTOMEM,
                                         ((uint32)(&(Spi_HwPtr->POPR.R)) + (uint32)2U),
                                         (uint32)Spi_RecDataPtr,
                                         EDMA_TRANSFER_SIZE_2B,
                                         2U,
                                         Spi_u32DataLength,
                                         true);
        }
        else if(Spi_HandlePtr->FrameSize <= 32U)
        {
            EDMA_SetMultiTransferConfig( Spi_HandlePtr->Spi_TxDmaChannelID,
                                         EDMA_TRANSFER_TYPE_PERIPHTOPERIPH,
                                         (uint32)((uint32)(&Spi_HandlePtr->TranDefaultData) + (uint32)2U),
                                         ((uint32)(&(Spi_HwPtr->PUSHR.PUSHR.R)) + (uint32)2U),
                                         EDMA_TRANSFER_SIZE_2B,
                                         2U,
                                         Spi_u32DataLength *2,
                                         true);

            EDMA_SetMultiTransferConfig( Spi_HandlePtr->Spi_RxDmaChannelID,
                                         EDMA_TRANSFER_TYPE_PERIPHTOMEM,
                                         ((uint32)(&(Spi_HwPtr->POPR.R))/* + (uint32)2U */),
                                         (uint32)Spi_RecDataPtr,
                                         EDMA_TRANSFER_SIZE_4B,
                                         4U,
                                         Spi_u32DataLength,
                                         true);
        }
        else
        {
            /* Do nothing */
        }
    }
    else
    {
        /* Do nothing */
    }
    if(Spi_gAsyncMode == SPI_INTERRUPT_MODE)
    {
        EDMA_SetInterruptConfig(Spi_HandlePtr->Spi_RxDmaChannelID, EDMA_CHN_ENABLE_MAJOR_LOOP_DONE_INT, TRUE);
    }
    EDMA_SetChannelRequest(Spi_HandlePtr->Spi_RxDmaChannelID);
    EDMA_SetChannelRequest(Spi_HandlePtr->Spi_TxDmaChannelID);
}
#endif
#endif

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
FUNC(void, SPI_CODE) dspi_tcf(
    P2VAR(Spi_HandleType, AUTOMATIC, SPI_APPL_DATA) Spi_HandlePtr)
{
    P2VAR(Spi_HwSpiType, SPI_VAR, SPI_APPL_DATA) Spi_HwPtr = SpiHwUnit[Spi_HandlePtr->HwDevice];
    if(Spi_HwPtr->SR.B.TXCTR >= (uint32)1U)
    {
        Spi_HwPtr->SR.R = DSPI_TCF_CLEAR;
    }
    else
    {
        Spi_HwPtr->SR.R = DSPI_TCF_CLEAR;
        dspi_DataHandle(Spi_HandlePtr);
        if((Spi_HandlePtr->Spi_TxCnt >= Spi_HandlePtr->Spi_DataLength) && (Spi_HandlePtr->Spi_RxCnt >= Spi_HandlePtr->Spi_DataLength))
        {
            Spi_AsyncHandle(Spi_HandlePtr);
        }
    }
}

#endif

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
FUNC(void, SPI_CODE)dspi_MainFunc(
    P2VAR(Spi_HandleType, AUTOMATIC, SPI_APPL_DATA) Spi_HandlePtr )
{
    P2VAR(Spi_HwSpiType, SPI_VAR, SPI_APPL_DATA) Spi_HwPtr;
    #if (SPI_DMA_USED == STD_ON)
    if(Spi_HandlePtr->Spi_DmaEnable == TRUE)
    {
        if(EDMA_GetChnRemainingIterationsCount(Spi_HandlePtr->Spi_RxDmaChannelID) == 1U)
        {
            Spi_AsyncHandle(Spi_HandlePtr);
        }
    }
    else
    {
    #endif
        Spi_HwPtr = SpiHwUnit[(uint32)Spi_HandlePtr->HwDevice];
        if(Spi_HwPtr->SR.B.TCF == (uint32)TRUE)
        {
            dspi_tcf( Spi_HandlePtr );
        }
#if (SPI_DMA_USED == STD_ON)
    }
#endif
}
#endif

#ifdef __cplusplus
}
#endif
