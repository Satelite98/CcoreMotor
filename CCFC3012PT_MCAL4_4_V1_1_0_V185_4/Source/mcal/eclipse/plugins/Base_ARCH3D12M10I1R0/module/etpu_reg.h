#ifndef ETPU_REG_H_
#define ETPU_REG_H_

/* ============================================================================
   =============================== Module: ETPU ===============================
   ============================================================================ */

typedef struct {
    union {                 /* MODULE CONFIGURATION REGISTER */
        vuint32_t R;
        struct {
            vuint32_t GEC:1;        /* Global Exception Clear */
            vuint32_t SDMERR:1;     /* SDM Read Error */
            vuint32_t WDTOA:1;      /* Watchdog Timeout-eTPU_A */
            vuint32_t WDTOB:1;      /* Watchdog Timeout-eTPU_B */
            vuint32_t MGE1:1;       /* Microcode Global Exception-ETPU_A */
            vuint32_t MGE2:1;       /* Microcode Global Exception-ETPU_B */
            vuint32_t ILF1:1;       /* Illegal Instruction Flag-ETPU_A */
            vuint32_t ILF2:1;       /* Illegal Instruction Flag-ETPU_B */
            vuint32_t:3;
            vuint32_t SCMSIZE:5;    /* Shared Code Memory size */
            vuint32_t:4;
            vuint32_t SCMMISC:1;    /* SCM MISC Complete/Clear */
            vuint32_t SCMMISF:1;    /* SCM MISC Flag */
            vuint32_t SCMMISEN:1;   /* SCM MISC Enable */
            vuint32_t SCMERR:1;     /* SCM Read Error */
            vuint32_t:1;
            vuint32_t VIS:1;        /* SCM Visability */
            vuint32_t:5;
            vuint32_t GTBE:1;       /* Global Time Base Enable */
        } B;
    } MCR;

    union {                 /* COHERENT DUAL-PARAMETER CONTROL */
        vuint32_t R;
        struct {
            vuint32_t STS:1;        /* Start Status bit */
            vuint32_t CTBASE:5;     /* Channel Transfer Base */
            vuint32_t PBASE:10;     /* Parameter Buffer Base Address */
            vuint32_t PWIDTH:1;     /* Parameter Width */
            vuint32_t PARAM0:7;     /* Channel Parameter 0 */
            vuint32_t WR:1;         /* Read/Write selection */
            vuint32_t PARAM1:7;     /* Channel Parameter 1 */
        } B;
    } CDCR;

    uint32_t eTPU_reserved0008;  /* 0x0008-0x000B */

    union {                 /* MISC Compare Register */
        uint32_t R;
        struct {
            vuint32_t ETPUMISCCMP:32;
        } B;
    } MISCCMPR;

    union {                 /* SCM off-range Date Register */
        uint32_t R;
        struct {
            vuint32_t ETPUSCMOFFDATA:32;
        } B;
    } SCMOFFDATAR;

    union {                 /* ETPU_A Configuration Register */
        vuint32_t R;
        struct {
            vuint32_t FEND:1;       /* Force END */
            vuint32_t MDIS:1;       /* Low power Stop */
            vuint32_t:1;
            vuint32_t STF:1;        /* Stop Flag */
            vuint32_t:4;
            vuint32_t HLTF:1;       /* Halt Mode Flag */
            vuint32_t:3;
            vuint32_t FCSS:1;       /* Filter Clock Source Select */
            vuint32_t FPSCK:3;      /* Filter Prescaler Clock Control */
            vuint32_t CDFC:2;
            vuint32_t:1;
            vuint32_t ERBA:5;       /* Engine Relative Base Address */
            vuint32_t SPPDIS:1;     /* Schedule Priority Passing Disable */
            vuint32_t:2;
            vuint32_t ETB:5;        /* Entry Table Base */
        } B;
    } ECR_A;

    union {                 /* ETPU_B Configuration Register */
        vuint32_t R;
        struct {
            vuint32_t FEND:1;       /* Force END */
            vuint32_t MDIS:1;       /* Low power Stop */
            vuint32_t:1;
            vuint32_t STF:1;        /* Stop Flag */
            vuint32_t:4;
            vuint32_t HLTF:1;       /* Halt Mode Flag */
            vuint32_t:3;
            vuint32_t FCSS:1;       /* Filter Clock Source Select */
            vuint32_t FPSCK:3;      /* Filter Prescaler Clock Control */
            vuint32_t CDFC:2;
            vuint32_t:1;
            vuint32_t ERBA:5;       /* Engine Relative Base Address */
            vuint32_t SPPDIS:1;     /* Schedule Priority Passing Disable */
            vuint32_t:2;
            vuint32_t ETB:5;        /* Entry Table Base */
        } B;
    } ECR_B;

    uint32_t eTPU_reserved001C;  /* 0x001C-0x001F */

    union {                 /* ETPU_A Timebase Configuration Register */
        uint32_t R;
        struct {
            vuint32_t TCR2CTL:3;     /* TCR2 Clock/Gate Control */
            vuint32_t TCRCF:2;       /* TCRCLK Signal Filter Control */
            vuint32_t AM:2;          /* Angle Mode */
            vuint32_t:3;
            vuint32_t TCR2P:6;       /* TCR2 Prescaler Control */
            vuint32_t TCR1CTL:2;     /* TCR1 Clock/Gate Control */
            vuint32_t TCR1CS:1;      /* TCR1 Clock Source */
            vuint32_t:5;
            vuint32_t TCR1P:8;       /* TCR1 Prescaler Control */
        } B;
    } TBCR_A;

    union {                 /* ETPU_A TCR1 Visibility Register */
        vuint32_t R;
        struct {
            vuint32_t:8;
            vuint32_t TCR1:24;
        } B;
    } TB1R_A;

    union {                 /* ETPU_A TCR2 Visibility Register */
        vuint32_t R;
        struct {
            vuint32_t:8;
            vuint32_t TCR2:24;
        } B;
    } TB2R_A;

    union {                 /* ETPU_A STAC Configuration Register */
        vuint32_t R;
        struct {
            vuint32_t REN1:1;       /* Resource Enable TCR1 */
            vuint32_t RSC1:1;       /* Resource Control TCR1 */
            vuint32_t:2;
            vuint32_t SERVER_ID1:4;   /* TCR1 Server ID */
            vuint32_t:4;
            vuint32_t SRV1:4;       /* Resource Server Slot */
            vuint32_t REN2:1;       /* Resource Enable TCR2 */
            vuint32_t RSC2:1;       /* Resource Control TCR2 */
            vuint32_t:2;
            vuint32_t SERVER_ID2:4;   /* TCR2 Server ID */
            vuint32_t:4;
            vuint32_t SRV2:4;       /* Resource Server Slot */
        } B;
    } REDCR_A;

    uint32_t eTPU_reserved0030[4];  /* 0x0030-0x003F */

    union {                 /* ETPU_B Timebase Configuration Register */
        uint32_t R;
        struct {
            vuint32_t TCR2CTL:3;     /* TCR2 Clock/Gate Control */
            vuint32_t TCRCF:2;       /* TCRCLK Signal Filter Control */
            vuint32_t AM:2;          /* Angle Mode */
            vuint32_t:3;
            vuint32_t TCR2P:6;       /* TCR2 Prescaler Control */
            vuint32_t TCR1CTL:2;     /* TCR1 Clock/Gate Control */
            vuint32_t TCR1CS:1;      /* TCR1 Clock Source */
            vuint32_t:5;
            vuint32_t TCR1P:8;       /* TCR1 Prescaler Control */
        } B;
    } TBCR_B;

    union {                 /* ETPU_B TCR1 Visibility Register */
        vuint32_t R;
        struct {
            vuint32_t:8;
            vuint32_t TCR1:24;
        } B;
    } TB1R_B;

    union {                 /* ETPU_B TCR2 Visibility Register */
        vuint32_t R;
        struct {
            vuint32_t:8;
            vuint32_t TCR2:24;
        } B;
    } TB2R_B;

    union {                 /* ETPU_B STAC Configuration Register */
        vuint32_t R;
        struct {
            vuint32_t REN1:1;       /* Resource Enable TCR1 */
            vuint32_t RSC1:1;       /* Resource Control TCR1 */
            vuint32_t:2;
            vuint32_t SERVER_ID1:4;   /* TCR1 Server ID */
            vuint32_t:4;
            vuint32_t SRV1:4;       /* Resource Server Slot */
            vuint32_t REN2:1;       /* Resource Enable TCR2 */
            vuint32_t RSC2:1;       /* Resource Control TCR2 */
            vuint32_t:2;
            vuint32_t SERVER_ID2:4;   /* TCR2 Server ID */
            vuint32_t:4;
            vuint32_t SRV2:4;       /* Resource Server Slot */
        } B;
    } REDCR_B;

    uint32_t eTPU_reserved0050[4];  /* 0x0050-0x005F */

    union {                 /* Watchdog Timer Register A */
        vuint32_t R;
        struct {
            vuint32_t WDM:2;          /* Watchdog Mode */
            vuint32_t:14;
            vuint32_t WDCNT:16;       /* Watchdog Count */
        } B;
    } WDTR_A;

    uint32_t eTPU_reserved0064;  /* 0x0064-0x0067 */

    union {                 /* Idle Counter Register A*/
        vuint32_t R;
        struct {
            vuint32_t:31;
            vuint32_t ICLR:1;       /* Idle Clear */
        } B;

    } IDLE_A;

    uint32_t eTPU_reserved006C;  /* 0x006C-0x006F */

    union {                 /* Watchdog Timer Register B */
        vuint32_t R;
        struct {
            vuint32_t WDM:2;          /* Watchdog Mode */
            vuint32_t:14;
            vuint32_t WDCNT:16;       /* Watchdog Count */
        } B;
    } WDTR_B;

    uint32_t eTPU_reserved0074;  /* 0x0074-0x0077 */

    union {                 /* Idle Counter Register B*/
        vuint32_t R;
        struct {
            vuint32_t:31;
            vuint32_t ICLR:1;       /* Idle Clear */
        } B;
    } IDLE_B;

    uint32_t eTPU_reserved007C;  /* 0x007C-0x007F */

    uint32_t eTPU_reserved0080[96];  /* 0x0080-0x01FF */

/*****************************Status and Control Registers**************************/

    union {                 /* ETPU_A Channel Interrut Status */
        vuint32_t R;
        struct {
            vuint32_t CIS31:1;      /* Channel 31 Interrut Status */
            vuint32_t CIS30:1;      /* Channel 30 Interrut Status */
            vuint32_t CIS29:1;      /* Channel 29 Interrut Status */
            vuint32_t CIS28:1;      /* Channel 28 Interrut Status */
            vuint32_t CIS27:1;      /* Channel 27 Interrut Status */
            vuint32_t CIS26:1;      /* Channel 26 Interrut Status */
            vuint32_t CIS25:1;      /* Channel 25 Interrut Status */
            vuint32_t CIS24:1;      /* Channel 24 Interrut Status */
            vuint32_t CIS23:1;      /* Channel 23 Interrut Status */
            vuint32_t CIS22:1;      /* Channel 22 Interrut Status */
            vuint32_t CIS21:1;      /* Channel 21 Interrut Status */
            vuint32_t CIS20:1;      /* Channel 20 Interrut Status */
            vuint32_t CIS19:1;      /* Channel 19 Interrut Status */
            vuint32_t CIS18:1;      /* Channel 18 Interrut Status */
            vuint32_t CIS17:1;      /* Channel 17 Interrut Status */
            vuint32_t CIS16:1;      /* Channel 16 Interrut Status */
            vuint32_t CIS15:1;      /* Channel 15 Interrut Status */
            vuint32_t CIS14:1;      /* Channel 14 Interrut Status */
            vuint32_t CIS13:1;      /* Channel 13 Interrut Status */
            vuint32_t CIS12:1;      /* Channel 12 Interrut Status */
            vuint32_t CIS11:1;      /* Channel 11 Interrut Status */
            vuint32_t CIS10:1;      /* Channel 10 Interrut Status */
            vuint32_t CIS9:1;       /* Channel 9 Interrut Status */
            vuint32_t CIS8:1;       /* Channel 8 Interrut Status */
            vuint32_t CIS7:1;       /* Channel 7 Interrut Status */
            vuint32_t CIS6:1;       /* Channel 6 Interrut Status */
            vuint32_t CIS5:1;       /* Channel 5 Interrut Status */
            vuint32_t CIS4:1;       /* Channel 4 Interrut Status */
            vuint32_t CIS3:1;       /* Channel 3 Interrut Status */
            vuint32_t CIS2:1;       /* Channel 2 Interrut Status */
            vuint32_t CIS1:1;       /* Channel 1 Interrut Status */
            vuint32_t CIS0:1;       /* Channel 0 Interrut Status */
        } B;
    } CISR_A;

    union {                 /* ETPU_B Channel Interruput Status */
        vuint32_t R;
        struct {
            vuint32_t CIS31:1;      /* Channel 31 Interrut Status */
            vuint32_t CIS30:1;      /* Channel 30 Interrut Status */
            vuint32_t CIS29:1;      /* Channel 29 Interrut Status */
            vuint32_t CIS28:1;      /* Channel 28 Interrut Status */
            vuint32_t CIS27:1;      /* Channel 27 Interrut Status */
            vuint32_t CIS26:1;      /* Channel 26 Interrut Status */
            vuint32_t CIS25:1;      /* Channel 25 Interrut Status */
            vuint32_t CIS24:1;      /* Channel 24 Interrut Status */
            vuint32_t CIS23:1;      /* Channel 23 Interrut Status */
            vuint32_t CIS22:1;      /* Channel 22 Interrut Status */
            vuint32_t CIS21:1;      /* Channel 21 Interrut Status */
            vuint32_t CIS20:1;      /* Channel 20 Interrut Status */
            vuint32_t CIS19:1;      /* Channel 19 Interrut Status */
            vuint32_t CIS18:1;      /* Channel 18 Interrut Status */
            vuint32_t CIS17:1;      /* Channel 17 Interrut Status */
            vuint32_t CIS16:1;      /* Channel 16 Interrut Status */
            vuint32_t CIS15:1;      /* Channel 15 Interrut Status */
            vuint32_t CIS14:1;      /* Channel 14 Interrut Status */
            vuint32_t CIS13:1;      /* Channel 13 Interrut Status */
            vuint32_t CIS12:1;      /* Channel 12 Interrut Status */
            vuint32_t CIS11:1;      /* Channel 11 Interrut Status */
            vuint32_t CIS10:1;      /* Channel 10 Interrut Status */
            vuint32_t CIS9:1;       /* Channel 9 Interrut Status */
            vuint32_t CIS8:1;       /* Channel 8 Interrut Status */
            vuint32_t CIS7:1;       /* Channel 7 Interrut Status */
            vuint32_t CIS6:1;       /* Channel 6 Interrut Status */
            vuint32_t CIS5:1;       /* Channel 5 Interrut Status */
            vuint32_t CIS4:1;       /* Channel 4 Interrut Status */
            vuint32_t CIS3:1;       /* Channel 3 Interrut Status */
            vuint32_t CIS2:1;       /* Channel 2 Interrut Status */
            vuint32_t CIS1:1;       /* Channel 1 Interrupt Status */
            vuint32_t CIS0:1;       /* Channel 0 Interrupt Status */
        } B;
    } CISR_B;

    uint32_t eTPU_reserved0208[2];  /* 0x0208-0x020F */

    union {                 /* ETPU_A Data Transfer Request Status */
        vuint32_t R;
        struct {
            vuint32_t DTRS31:1;     /* Channel 31 Data Transfer Request Status */
            vuint32_t DTRS30:1;     /* Channel 30 Data Transfer Request Status */
            vuint32_t DTRS29:1;     /* Channel 29 Data Transfer Request Status */
            vuint32_t DTRS28:1;     /* Channel 28 Data Transfer Request Status */
            vuint32_t DTRS27:1;     /* Channel 27 Data Transfer Request Status */
            vuint32_t DTRS26:1;     /* Channel 26 Data Transfer Request Status */
            vuint32_t DTRS25:1;     /* Channel 25 Data Transfer Request Status */
            vuint32_t DTRS24:1;     /* Channel 24 Data Transfer Request Status */
            vuint32_t DTRS23:1;     /* Channel 23 Data Transfer Request Status */
            vuint32_t DTRS22:1;     /* Channel 22 Data Transfer Request Status */
            vuint32_t DTRS21:1;     /* Channel 21 Data Transfer Request Status */
            vuint32_t DTRS20:1;     /* Channel 20 Data Transfer Request Status */
            vuint32_t DTRS19:1;     /* Channel 19 Data Transfer Request Status */
            vuint32_t DTRS18:1;     /* Channel 18 Data Transfer Request Status */
            vuint32_t DTRS17:1;     /* Channel 17 Data Transfer Request Status */
            vuint32_t DTRS16:1;     /* Channel 16 Data Transfer Request Status */
            vuint32_t DTRS15:1;     /* Channel 15 Data Transfer Request Status */
            vuint32_t DTRS14:1;     /* Channel 14 Data Transfer Request Status */
            vuint32_t DTRS13:1;     /* Channel 13 Data Transfer Request Status */
            vuint32_t DTRS12:1;     /* Channel 12 Data Transfer Request Status */
            vuint32_t DTRS11:1;     /* Channel 11 Data Transfer Request Status */
            vuint32_t DTRS10:1;     /* Channel 10 Data Transfer Request Status */
            vuint32_t DTRS9:1;      /* Channel 9 Data Transfer Request Status */
            vuint32_t DTRS8:1;      /* Channel 8 Data Transfer Request Status */
            vuint32_t DTRS7:1;      /* Channel 7 Data Transfer Request Status */
            vuint32_t DTRS6:1;      /* Channel 6 Data Transfer Request Status */
            vuint32_t DTRS5:1;      /* Channel 5 Data Transfer Request Status */
            vuint32_t DTRS4:1;      /* Channel 4 Data Transfer Request Status */
            vuint32_t DTRS3:1;      /* Channel 3 Data Transfer Request Status */
            vuint32_t DTRS2:1;      /* Channel 2 Data Transfer Request Status */
            vuint32_t DTRS1:1;      /* Channel 1 Data Transfer Request Status */
            vuint32_t DTRS0:1;      /* Channel 0 Data Transfer Request Status */
        } B;
    } CDTRSR_A;

    union {                 /* ETPU_B Data Transfer Request Status */
        vuint32_t R;
        struct {
            vuint32_t DTRS31:1;     /* Channel 31 Data Transfer Request Status */
            vuint32_t DTRS30:1;     /* Channel 30 Data Transfer Request Status */
            vuint32_t DTRS29:1;     /* Channel 29 Data Transfer Request Status */
            vuint32_t DTRS28:1;     /* Channel 28 Data Transfer Request Status */
            vuint32_t DTRS27:1;     /* Channel 27 Data Transfer Request Status */
            vuint32_t DTRS26:1;     /* Channel 26 Data Transfer Request Status */
            vuint32_t DTRS25:1;     /* Channel 25 Data Transfer Request Status */
            vuint32_t DTRS24:1;     /* Channel 24 Data Transfer Request Status */
            vuint32_t DTRS23:1;     /* Channel 23 Data Transfer Request Status */
            vuint32_t DTRS22:1;     /* Channel 22 Data Transfer Request Status */
            vuint32_t DTRS21:1;     /* Channel 21 Data Transfer Request Status */
            vuint32_t DTRS20:1;     /* Channel 20 Data Transfer Request Status */
            vuint32_t DTRS19:1;     /* Channel 19 Data Transfer Request Status */
            vuint32_t DTRS18:1;     /* Channel 18 Data Transfer Request Status */
            vuint32_t DTRS17:1;     /* Channel 17 Data Transfer Request Status */
            vuint32_t DTRS16:1;     /* Channel 16 Data Transfer Request Status */
            vuint32_t DTRS15:1;     /* Channel 15 Data Transfer Request Status */
            vuint32_t DTRS14:1;     /* Channel 14 Data Transfer Request Status */
            vuint32_t DTRS13:1;     /* Channel 13 Data Transfer Request Status */
            vuint32_t DTRS12:1;     /* Channel 12 Data Transfer Request Status */
            vuint32_t DTRS11:1;     /* Channel 11 Data Transfer Request Status */
            vuint32_t DTRS10:1;     /* Channel 10 Data Transfer Request Status */
            vuint32_t DTRS9:1;      /* Channel 9 Data Transfer Request Status */
            vuint32_t DTRS8:1;      /* Channel 8 Data Transfer Request Status */
            vuint32_t DTRS7:1;      /* Channel 7 Data Transfer Request Status */
            vuint32_t DTRS6:1;      /* Channel 6 Data Transfer Request Status */
            vuint32_t DTRS5:1;      /* Channel 5 Data Transfer Request Status */
            vuint32_t DTRS4:1;      /* Channel 4 Data Transfer Request Status */
            vuint32_t DTRS3:1;      /* Channel 3 Data Transfer Request Status */
            vuint32_t DTRS2:1;      /* Channel 2 Data Transfer Request Status */
            vuint32_t DTRS1:1;      /* Channel 1 Data Transfer Request Status */
            vuint32_t DTRS0:1;      /* Channel 0 Data Transfer Request Status */
        } B;
    } CDTRSR_B;

    uint32_t eTPU_reserved0218[2];  /* 0x0218-0x021F */

    union {                 /* ETPU_A Interruput Overflow Status */
        vuint32_t R;
        struct {
            vuint32_t CIOS31:1;     /* Channel 31 Interruput Overflow Status */
            vuint32_t CIOS30:1;     /* Channel 30 Interruput Overflow Status */
            vuint32_t CIOS29:1;     /* Channel 29 Interruput Overflow Status */
            vuint32_t CIOS28:1;     /* Channel 28 Interruput Overflow Status */
            vuint32_t CIOS27:1;     /* Channel 27 Interruput Overflow Status */
            vuint32_t CIOS26:1;     /* Channel 26 Interruput Overflow Status */
            vuint32_t CIOS25:1;     /* Channel 25 Interruput Overflow Status */
            vuint32_t CIOS24:1;     /* Channel 24 Interruput Overflow Status */
            vuint32_t CIOS23:1;     /* Channel 23 Interruput Overflow Status */
            vuint32_t CIOS22:1;     /* Channel 22 Interruput Overflow Status */
            vuint32_t CIOS21:1;     /* Channel 21 Interruput Overflow Status */
            vuint32_t CIOS20:1;     /* Channel 20 Interruput Overflow Status */
            vuint32_t CIOS19:1;     /* Channel 19 Interruput Overflow Status */
            vuint32_t CIOS18:1;     /* Channel 18 Interruput Overflow Status */
            vuint32_t CIOS17:1;     /* Channel 17 Interruput Overflow Status */
            vuint32_t CIOS16:1;     /* Channel 16 Interruput Overflow Status */
            vuint32_t CIOS15:1;     /* Channel 15 Interruput Overflow Status */
            vuint32_t CIOS14:1;     /* Channel 14 Interruput Overflow Status */
            vuint32_t CIOS13:1;     /* Channel 13 Interruput Overflow Status */
            vuint32_t CIOS12:1;     /* Channel 12 Interruput Overflow Status */
            vuint32_t CIOS11:1;     /* Channel 11 Interruput Overflow Status */
            vuint32_t CIOS10:1;     /* Channel 10 Interruput Overflow Status */
            vuint32_t CIOS9:1;      /* Channel 9 Interruput Overflow Status */
            vuint32_t CIOS8:1;      /* Channel 8 Interruput Overflow Status */
            vuint32_t CIOS7:1;      /* Channel 7 Interruput Overflow Status */
            vuint32_t CIOS6:1;      /* Channel 6 Interruput Overflow Status */
            vuint32_t CIOS5:1;      /* Channel 5 Interruput Overflow Status */
            vuint32_t CIOS4:1;      /* Channel 4 Interruput Overflow Status */
            vuint32_t CIOS3:1;      /* Channel 3 Interruput Overflow Status */
            vuint32_t CIOS2:1;      /* Channel 2 Interruput Overflow Status */
            vuint32_t CIOS1:1;      /* Channel 1 Interruput Overflow Status */
            vuint32_t CIOS0:1;      /* Channel 0 Interruput Overflow Status */
        } B;
    } CIOSR_A;

    union {                 /* ETPU_B Interruput Overflow Status */
        vuint32_t R;
        struct {
            vuint32_t CIOS31:1;     /* Channel 31 Interruput Overflow Status */
            vuint32_t CIOS30:1;     /* Channel 30 Interruput Overflow Status */
            vuint32_t CIOS29:1;     /* Channel 29 Interruput Overflow Status */
            vuint32_t CIOS28:1;     /* Channel 28 Interruput Overflow Status */
            vuint32_t CIOS27:1;     /* Channel 27 Interruput Overflow Status */
            vuint32_t CIOS26:1;     /* Channel 26 Interruput Overflow Status */
            vuint32_t CIOS25:1;     /* Channel 25 Interruput Overflow Status */
            vuint32_t CIOS24:1;     /* Channel 24 Interruput Overflow Status */
            vuint32_t CIOS23:1;     /* Channel 23 Interruput Overflow Status */
            vuint32_t CIOS22:1;     /* Channel 22 Interruput Overflow Status */
            vuint32_t CIOS21:1;     /* Channel 21 Interruput Overflow Status */
            vuint32_t CIOS20:1;     /* Channel 20 Interruput Overflow Status */
            vuint32_t CIOS19:1;     /* Channel 19 Interruput Overflow Status */
            vuint32_t CIOS18:1;     /* Channel 18 Interruput Overflow Status */
            vuint32_t CIOS17:1;     /* Channel 17 Interruput Overflow Status */
            vuint32_t CIOS16:1;     /* Channel 16 Interruput Overflow Status */
            vuint32_t CIOS15:1;     /* Channel 15 Interruput Overflow Status */
            vuint32_t CIOS14:1;     /* Channel 14 Interruput Overflow Status */
            vuint32_t CIOS13:1;     /* Channel 13 Interruput Overflow Status */
            vuint32_t CIOS12:1;     /* Channel 12 Interruput Overflow Status */
            vuint32_t CIOS11:1;     /* Channel 11 Interruput Overflow Status */
            vuint32_t CIOS10:1;     /* Channel 10 Interruput Overflow Status */
            vuint32_t CIOS9:1;      /* Channel 9 Interruput Overflow Status */
            vuint32_t CIOS8:1;      /* Channel 8 Interruput Overflow Status */
            vuint32_t CIOS7:1;      /* Channel 7 Interruput Overflow Status */
            vuint32_t CIOS6:1;      /* Channel 6 Interruput Overflow Status */
            vuint32_t CIOS5:1;      /* Channel 5 Interruput Overflow Status */
            vuint32_t CIOS4:1;      /* Channel 4 Interruput Overflow Status */
            vuint32_t CIOS3:1;      /* Channel 3 Interruput Overflow Status */
            vuint32_t CIOS2:1;      /* Channel 2 Interruput Overflow Status */
            vuint32_t CIOS1:1;      /* Channel 1 Interruput Overflow Status */
            vuint32_t CIOS0:1;      /* Channel 0 Interruput Overflow Status */
        } B;
    } CIOSR_B;

    uint32_t eTPU_reserved0228[2];  /* 0x0228-0x022F */

    union {                 /* ETPU_A Data Transfer Overflow Status */
        vuint32_t R;
        struct {
            vuint32_t DTROS31:1;    /* Channel 31 Data Transfer Overflow Status */
            vuint32_t DTROS30:1;    /* Channel 30 Data Transfer Overflow Status */
            vuint32_t DTROS29:1;    /* Channel 29 Data Transfer Overflow Status */
            vuint32_t DTROS28:1;    /* Channel 28 Data Transfer Overflow Status */
            vuint32_t DTROS27:1;    /* Channel 27 Data Transfer Overflow Status */
            vuint32_t DTROS26:1;    /* Channel 26 Data Transfer Overflow Status */
            vuint32_t DTROS25:1;    /* Channel 25 Data Transfer Overflow Status */
            vuint32_t DTROS24:1;    /* Channel 24 Data Transfer Overflow Status */
            vuint32_t DTROS23:1;    /* Channel 23 Data Transfer Overflow Status */
            vuint32_t DTROS22:1;    /* Channel 22 Data Transfer Overflow Status */
            vuint32_t DTROS21:1;    /* Channel 21 Data Transfer Overflow Status */
            vuint32_t DTROS20:1;    /* Channel 20 Data Transfer Overflow Status */
            vuint32_t DTROS19:1;    /* Channel 19 Data Transfer Overflow Status */
            vuint32_t DTROS18:1;    /* Channel 18 Data Transfer Overflow Status */
            vuint32_t DTROS17:1;    /* Channel 17 Data Transfer Overflow Status */
            vuint32_t DTROS16:1;    /* Channel 16 Data Transfer Overflow Status */
            vuint32_t DTROS15:1;    /* Channel 15 Data Transfer Overflow Status */
            vuint32_t DTROS14:1;    /* Channel 14 Data Transfer Overflow Status */
            vuint32_t DTROS13:1;    /* Channel 13 Data Transfer Overflow Status */
            vuint32_t DTROS12:1;    /* Channel 12 Data Transfer Overflow Status */
            vuint32_t DTROS11:1;    /* Channel 11 Data Transfer Overflow Status */
            vuint32_t DTROS10:1;    /* Channel 10 Data Transfer Overflow Status */
            vuint32_t DTROS9:1;     /* Channel 9 Data Transfer Overflow Status */
            vuint32_t DTROS8:1;     /* Channel 8 Data Transfer Overflow Status */
            vuint32_t DTROS7:1;     /* Channel 7 Data Transfer Overflow Status */
            vuint32_t DTROS6:1;     /* Channel 6 Data Transfer Overflow Status */
            vuint32_t DTROS5:1;     /* Channel 5 Data Transfer Overflow Status */
            vuint32_t DTROS4:1;     /* Channel 4 Data Transfer Overflow Status */
            vuint32_t DTROS3:1;     /* Channel 3 Data Transfer Overflow Status */
            vuint32_t DTROS2:1;     /* Channel 2 Data Transfer Overflow Status */
            vuint32_t DTROS1:1;     /* Channel 1 Data Transfer Overflow Status */
            vuint32_t DTROS0:1;     /* Channel 0 Data Transfer Overflow Status */
        } B;
    } CDTROSR_A;

    union {                 /* ETPU_B Data Transfer Overflow Status */
        vuint32_t R;
        struct {
            vuint32_t DTROS31:1;    /* Channel 31 Data Transfer Overflow Status */
            vuint32_t DTROS30:1;    /* Channel 30 Data Transfer Overflow Status */
            vuint32_t DTROS29:1;    /* Channel 29 Data Transfer Overflow Status */
            vuint32_t DTROS28:1;    /* Channel 28 Data Transfer Overflow Status */
            vuint32_t DTROS27:1;    /* Channel 27 Data Transfer Overflow Status */
            vuint32_t DTROS26:1;    /* Channel 26 Data Transfer Overflow Status */
            vuint32_t DTROS25:1;    /* Channel 25 Data Transfer Overflow Status */
            vuint32_t DTROS24:1;    /* Channel 24 Data Transfer Overflow Status */
            vuint32_t DTROS23:1;    /* Channel 23 Data Transfer Overflow Status */
            vuint32_t DTROS22:1;    /* Channel 22 Data Transfer Overflow Status */
            vuint32_t DTROS21:1;    /* Channel 21 Data Transfer Overflow Status */
            vuint32_t DTROS20:1;    /* Channel 20 Data Transfer Overflow Status */
            vuint32_t DTROS19:1;    /* Channel 19 Data Transfer Overflow Status */
            vuint32_t DTROS18:1;    /* Channel 18 Data Transfer Overflow Status */
            vuint32_t DTROS17:1;    /* Channel 17 Data Transfer Overflow Status */
            vuint32_t DTROS16:1;    /* Channel 16 Data Transfer Overflow Status */
            vuint32_t DTROS15:1;    /* Channel 15 Data Transfer Overflow Status */
            vuint32_t DTROS14:1;    /* Channel 14 Data Transfer Overflow Status */
            vuint32_t DTROS13:1;    /* Channel 13 Data Transfer Overflow Status */
            vuint32_t DTROS12:1;    /* Channel 12 Data Transfer Overflow Status */
            vuint32_t DTROS11:1;    /* Channel 11 Data Transfer Overflow Status */
            vuint32_t DTROS10:1;    /* Channel 10 Data Transfer Overflow Status */
            vuint32_t DTROS9:1;     /* Channel 9 Data Transfer Overflow Status */
            vuint32_t DTROS8:1;     /* Channel 8 Data Transfer Overflow Status */
            vuint32_t DTROS7:1;     /* Channel 7 Data Transfer Overflow Status */
            vuint32_t DTROS6:1;     /* Channel 6 Data Transfer Overflow Status */
            vuint32_t DTROS5:1;     /* Channel 5 Data Transfer Overflow Status */
            vuint32_t DTROS4:1;     /* Channel 4 Data Transfer Overflow Status */
            vuint32_t DTROS3:1;     /* Channel 3 Data Transfer Overflow Status */
            vuint32_t DTROS2:1;     /* Channel 2 Data Transfer Overflow Status */
            vuint32_t DTROS1:1;     /* Channel 1 Data Transfer Overflow Status */
            vuint32_t DTROS0:1;     /* Channel 0 Data Transfer Overflow Status */
        } B;
    } CDTROSR_B;

    uint32_t eTPU_reserved0238[2];  /* 0x0238-0x023F */

    union {                 /* ETPU_A Channel Interruput Enable */
        vuint32_t R;
        struct {
            vuint32_t CIE31:1;      /* Channel 31 Interruput Enable */
            vuint32_t CIE30:1;      /* Channel 30 Interruput Enable */
            vuint32_t CIE29:1;      /* Channel 29 Interruput Enable */
            vuint32_t CIE28:1;      /* Channel 28 Interruput Enable */
            vuint32_t CIE27:1;      /* Channel 27 Interruput Enable */
            vuint32_t CIE26:1;      /* Channel 26 Interruput Enable */
            vuint32_t CIE25:1;      /* Channel 25 Interruput Enable */
            vuint32_t CIE24:1;      /* Channel 24 Interruput Enable */
            vuint32_t CIE23:1;      /* Channel 23 Interruput Enable */
            vuint32_t CIE22:1;      /* Channel 22 Interruput Enable */
            vuint32_t CIE21:1;      /* Channel 21 Interruput Enable */
            vuint32_t CIE20:1;      /* Channel 20 Interruput Enable */
            vuint32_t CIE19:1;      /* Channel 19 Interruput Enable */
            vuint32_t CIE18:1;      /* Channel 18 Interruput Enable */
            vuint32_t CIE17:1;      /* Channel 17 Interruput Enable */
            vuint32_t CIE16:1;      /* Channel 16 Interruput Enable */
            vuint32_t CIE15:1;      /* Channel 15 Interruput Enable */
            vuint32_t CIE14:1;      /* Channel 14 Interruput Enable */
            vuint32_t CIE13:1;      /* Channel 13 Interruput Enable */
            vuint32_t CIE12:1;      /* Channel 12 Interruput Enable */
            vuint32_t CIE11:1;      /* Channel 11 Interruput Enable */
            vuint32_t CIE10:1;      /* Channel 10 Interruput Enable */
            vuint32_t CIE9:1;       /* Channel 9 Interruput Enable */
            vuint32_t CIE8:1;       /* Channel 8 Interruput Enable */
            vuint32_t CIE7:1;       /* Channel 7 Interruput Enable */
            vuint32_t CIE6:1;       /* Channel 6 Interruput Enable */
            vuint32_t CIE5:1;       /* Channel 5 Interruput Enable */
            vuint32_t CIE4:1;       /* Channel 4 Interruput Enable */
            vuint32_t CIE3:1;       /* Channel 3 Interruput Enable */
            vuint32_t CIE2:1;       /* Channel 2 Interruput Enable */
            vuint32_t CIE1:1;       /* Channel 1 Interruput Enable */
            vuint32_t CIE0:1;       /* Channel 0 Interruput Enable */
        } B;
    } CIER_A;

    union {                 /* ETPU_B Channel Interruput Enable */
        vuint32_t R;
        struct {
            vuint32_t CIE31:1;      /* Channel 31 Interruput Enable */
            vuint32_t CIE30:1;      /* Channel 30 Interruput Enable */
            vuint32_t CIE29:1;      /* Channel 29 Interruput Enable */
            vuint32_t CIE28:1;      /* Channel 28 Interruput Enable */
            vuint32_t CIE27:1;      /* Channel 27 Interruput Enable */
            vuint32_t CIE26:1;      /* Channel 26 Interruput Enable */
            vuint32_t CIE25:1;      /* Channel 25 Interruput Enable */
            vuint32_t CIE24:1;      /* Channel 24 Interruput Enable */
            vuint32_t CIE23:1;      /* Channel 23 Interruput Enable */
            vuint32_t CIE22:1;      /* Channel 22 Interruput Enable */
            vuint32_t CIE21:1;      /* Channel 21 Interruput Enable */
            vuint32_t CIE20:1;      /* Channel 20 Interruput Enable */
            vuint32_t CIE19:1;      /* Channel 19 Interruput Enable */
            vuint32_t CIE18:1;      /* Channel 18 Interruput Enable */
            vuint32_t CIE17:1;      /* Channel 17 Interruput Enable */
            vuint32_t CIE16:1;      /* Channel 16 Interruput Enable */
            vuint32_t CIE15:1;      /* Channel 15 Interruput Enable */
            vuint32_t CIE14:1;      /* Channel 14 Interruput Enable */
            vuint32_t CIE13:1;      /* Channel 13 Interruput Enable */
            vuint32_t CIE12:1;      /* Channel 12 Interruput Enable */
            vuint32_t CIE11:1;      /* Channel 11 Interruput Enable */
            vuint32_t CIE10:1;      /* Channel 10 Interruput Enable */
            vuint32_t CIE9:1;       /* Channel 9 Interruput Enable */
            vuint32_t CIE8:1;       /* Channel 8 Interruput Enable */
            vuint32_t CIE7:1;       /* Channel 7 Interruput Enable */
            vuint32_t CIE6:1;       /* Channel 6 Interruput Enable */
            vuint32_t CIE5:1;       /* Channel 5 Interruput Enable */
            vuint32_t CIE4:1;       /* Channel 4 Interruput Enable */
            vuint32_t CIE3:1;       /* Channel 3 Interruput Enable */
            vuint32_t CIE2:1;       /* Channel 2 Interruput Enable */
            vuint32_t CIE1:1;       /* Channel 1 Interruput Enable */
            vuint32_t CIE0:1;       /* Channel 0 Interruput Enable */
        } B;
    } CIER_B;

    uint32_t eTPU_reserved0248[2];  /* 0x0248-0x024F */

    union {                 /* ETPU_A Channel Data Transfer Request Enable */
        vuint32_t R;
        struct {
            vuint32_t DTRE31:1;     /* Channel 31 Data Transfer Request Enable */
            vuint32_t DTRE30:1;     /* Channel 30 Data Transfer Request Enable */
            vuint32_t DTRE29:1;     /* Channel 29 Data Transfer Request Enable */
            vuint32_t DTRE28:1;     /* Channel 28 Data Transfer Request Enable */
            vuint32_t DTRE27:1;     /* Channel 27 Data Transfer Request Enable */
            vuint32_t DTRE26:1;     /* Channel 26 Data Transfer Request Enable */
            vuint32_t DTRE25:1;     /* Channel 25 Data Transfer Request Enable */
            vuint32_t DTRE24:1;     /* Channel 24 Data Transfer Request Enable */
            vuint32_t DTRE23:1;     /* Channel 23 Data Transfer Request Enable */
            vuint32_t DTRE22:1;     /* Channel 22 Data Transfer Request Enable */
            vuint32_t DTRE21:1;     /* Channel 21 Data Transfer Request Enable */
            vuint32_t DTRE20:1;     /* Channel 20 Data Transfer Request Enable */
            vuint32_t DTRE19:1;     /* Channel 19 Data Transfer Request Enable */
            vuint32_t DTRE18:1;     /* Channel 18 Data Transfer Request Enable */
            vuint32_t DTRE17:1;     /* Channel 17 Data Transfer Request Enable */
            vuint32_t DTRE16:1;     /* Channel 16 Data Transfer Request Enable */
            vuint32_t DTRE15:1;     /* Channel 15 Data Transfer Request Enable */
            vuint32_t DTRE14:1;     /* Channel 14 Data Transfer Request Enable */
            vuint32_t DTRE13:1;     /* Channel 13 Data Transfer Request Enable */
            vuint32_t DTRE12:1;     /* Channel 12 Data Transfer Request Enable */
            vuint32_t DTRE11:1;     /* Channel 11 Data Transfer Request Enable */
            vuint32_t DTRE10:1;     /* Channel 10 Data Transfer Request Enable */
            vuint32_t DTRE9:1;      /* Channel 9 Data Transfer Request Enable */
            vuint32_t DTRE8:1;      /* Channel 8 Data Transfer Request Enable */
            vuint32_t DTRE7:1;      /* Channel 7 Data Transfer Request Enable */
            vuint32_t DTRE6:1;      /* Channel 6 Data Transfer Request Enable */
            vuint32_t DTRE5:1;      /* Channel 5 Data Transfer Request Enable */
            vuint32_t DTRE4:1;      /* Channel 4 Data Transfer Request Enable */
            vuint32_t DTRE3:1;      /* Channel 3 Data Transfer Request Enable */
            vuint32_t DTRE2:1;      /* Channel 2 Data Transfer Request Enable */
            vuint32_t DTRE1:1;      /* Channel 1 Data Transfer Request Enable */
            vuint32_t DTRE0:1;      /* Channel 0 Data Transfer Request Enable */
        } B;
    } CDTRER_A;

    union {                 /* ETPU_B Channel Data Transfer Request Enable */
        vuint32_t R;
        struct {
            vuint32_t DTRE31:1;     /* Channel 31 Data Transfer Request Enable */
            vuint32_t DTRE30:1;     /* Channel 30 Data Transfer Request Enable */
            vuint32_t DTRE29:1;     /* Channel 29 Data Transfer Request Enable */
            vuint32_t DTRE28:1;     /* Channel 28 Data Transfer Request Enable */
            vuint32_t DTRE27:1;     /* Channel 27 Data Transfer Request Enable */
            vuint32_t DTRE26:1;     /* Channel 26 Data Transfer Request Enable */
            vuint32_t DTRE25:1;     /* Channel 25 Data Transfer Request Enable */
            vuint32_t DTRE24:1;     /* Channel 24 Data Transfer Request Enable */
            vuint32_t DTRE23:1;     /* Channel 23 Data Transfer Request Enable */
            vuint32_t DTRE22:1;     /* Channel 22 Data Transfer Request Enable */
            vuint32_t DTRE21:1;     /* Channel 21 Data Transfer Request Enable */
            vuint32_t DTRE20:1;     /* Channel 20 Data Transfer Request Enable */
            vuint32_t DTRE19:1;     /* Channel 19 Data Transfer Request Enable */
            vuint32_t DTRE18:1;     /* Channel 18 Data Transfer Request Enable */
            vuint32_t DTRE17:1;     /* Channel 17 Data Transfer Request Enable */
            vuint32_t DTRE16:1;     /* Channel 16 Data Transfer Request Enable */
            vuint32_t DTRE15:1;     /* Channel 15 Data Transfer Request Enable */
            vuint32_t DTRE14:1;     /* Channel 14 Data Transfer Request Enable */
            vuint32_t DTRE13:1;     /* Channel 13 Data Transfer Request Enable */
            vuint32_t DTRE12:1;     /* Channel 12 Data Transfer Request Enable */
            vuint32_t DTRE11:1;     /* Channel 11 Data Transfer Request Enable */
            vuint32_t DTRE10:1;     /* Channel 10 Data Transfer Request Enable */
            vuint32_t DTRE9:1;      /* Channel 9 Data Transfer Request Enable */
            vuint32_t DTRE8:1;      /* Channel 8 Data Transfer Request Enable */
            vuint32_t DTRE7:1;      /* Channel 7 Data Transfer Request Enable */
            vuint32_t DTRE6:1;      /* Channel 6 Data Transfer Request Enable */
            vuint32_t DTRE5:1;      /* Channel 5 Data Transfer Request Enable */
            vuint32_t DTRE4:1;      /* Channel 4 Data Transfer Request Enable */
            vuint32_t DTRE3:1;      /* Channel 3 Data Transfer Request Enable */
            vuint32_t DTRE2:1;      /* Channel 2 Data Transfer Request Enable */
            vuint32_t DTRE1:1;      /* Channel 1 Data Transfer Request Enable */
            vuint32_t DTRE0:1;      /* Channel 0 Data Transfer Request Enable */
        } B;
    } CDTRER_B;

    uint32_t eTPU_reserved0258[2];  /* 0x0258-0x025F */

    union {                 /* Watchdog Status Register A */
        vuint32_t R;
        struct {
            vuint32_t WDS31:1;
            vuint32_t WDS30:1;
            vuint32_t WDS29:1;
            vuint32_t WDS28:1;
            vuint32_t WDS27:1;
            vuint32_t WDS26:1;
            vuint32_t WDS25:1;
            vuint32_t WDS24:1;
            vuint32_t WDS23:1;
            vuint32_t WDS22:1;
            vuint32_t WDS21:1;
            vuint32_t WDS20:1;
            vuint32_t WDS19:1;
            vuint32_t WDS18:1;
            vuint32_t WDS17:1;
            vuint32_t WDS16:1;
            vuint32_t WDS15:1;
            vuint32_t WDS14:1;
            vuint32_t WDS13:1;
            vuint32_t WDS12:1;
            vuint32_t WDS11:1;
            vuint32_t WDS10:1;
            vuint32_t WDS9:1;
            vuint32_t WDS8:1;
            vuint32_t WDS7:1;
            vuint32_t WDS6:1;
            vuint32_t WDS5:1;
            vuint32_t WDS4:1;
            vuint32_t WDS3:1;
            vuint32_t WDS2:1;
            vuint32_t WDS1:1;
            vuint32_t WDS0:1;
        } B;
    } WDSR_A;

    union {                 /* Watchdog Status Register B */
        vuint32_t R;
        struct {
            vuint32_t WDS31:1;
            vuint32_t WDS30:1;
            vuint32_t WDS29:1;
            vuint32_t WDS28:1;
            vuint32_t WDS27:1;
            vuint32_t WDS26:1;
            vuint32_t WDS25:1;
            vuint32_t WDS24:1;
            vuint32_t WDS23:1;
            vuint32_t WDS22:1;
            vuint32_t WDS21:1;
            vuint32_t WDS20:1;
            vuint32_t WDS19:1;
            vuint32_t WDS18:1;
            vuint32_t WDS17:1;
            vuint32_t WDS16:1;
            vuint32_t WDS15:1;
            vuint32_t WDS14:1;
            vuint32_t WDS13:1;
            vuint32_t WDS12:1;
            vuint32_t WDS11:1;
            vuint32_t WDS10:1;
            vuint32_t WDS9:1;
            vuint32_t WDS8:1;
            vuint32_t WDS7:1;
            vuint32_t WDS6:1;
            vuint32_t WDS5:1;
            vuint32_t WDS4:1;
            vuint32_t WDS3:1;
            vuint32_t WDS2:1;
            vuint32_t WDS1:1;
            vuint32_t WDS0:1;
        } B;
    } WDSR_B;

    uint32_t eTPU_reserved0268[6];  /* 0x0268-0x027F */

    union {                 /* ETPU_A Channel Pending Service Status */
        vuint32_t R;
        struct {
            vuint32_t SR31:1;       /* Channel 31 Pending Service Status */
            vuint32_t SR30:1;       /* Channel 30 Pending Service Status */
            vuint32_t SR29:1;       /* Channel 29 Pending Service Status */
            vuint32_t SR28:1;       /* Channel 28 Pending Service Status */
            vuint32_t SR27:1;       /* Channel 27 Pending Service Status */
            vuint32_t SR26:1;       /* Channel 26 Pending Service Status */
            vuint32_t SR25:1;       /* Channel 25 Pending Service Status */
            vuint32_t SR24:1;       /* Channel 24 Pending Service Status */
            vuint32_t SR23:1;       /* Channel 23 Pending Service Status */
            vuint32_t SR22:1;       /* Channel 22 Pending Service Status */
            vuint32_t SR21:1;       /* Channel 21 Pending Service Status */
            vuint32_t SR20:1;       /* Channel 20 Pending Service Status */
            vuint32_t SR19:1;       /* Channel 19 Pending Service Status */
            vuint32_t SR18:1;       /* Channel 18 Pending Service Status */
            vuint32_t SR17:1;       /* Channel 17 Pending Service Status */
            vuint32_t SR16:1;       /* Channel 16 Pending Service Status */
            vuint32_t SR15:1;       /* Channel 15 Pending Service Status */
            vuint32_t SR14:1;       /* Channel 14 Pending Service Status */
            vuint32_t SR13:1;       /* Channel 13 Pending Service Status */
            vuint32_t SR12:1;       /* Channel 12 Pending Service Status */
            vuint32_t SR11:1;       /* Channel 11 Pending Service Status */
            vuint32_t SR10:1;       /* Channel 10 Pending Service Status */
            vuint32_t SR9:1;        /* Channel 9 Pending Service Status */
            vuint32_t SR8:1;        /* Channel 8 Pending Service Status */
            vuint32_t SR7:1;        /* Channel 7 Pending Service Status */
            vuint32_t SR6:1;        /* Channel 6 Pending Service Status */
            vuint32_t SR5:1;        /* Channel 5 Pending Service Status */
            vuint32_t SR4:1;        /* Channel 4 Pending Service Status */
            vuint32_t SR3:1;        /* Channel 3 Pending Service Status */
            vuint32_t SR2:1;        /* Channel 2 Pending Service Status */
            vuint32_t SR1:1;        /* Channel 1 Pending Service Status */
            vuint32_t SR0:1;        /* Channel 0 Pending Service Status */
        } B;
    } CPSSR_A;

    union {                 /* ETPU_B Channel Pending Service Status */
        vuint32_t R;
        struct {
            vuint32_t SR31:1;       /* Channel 31 Pending Service Status */
            vuint32_t SR30:1;       /* Channel 30 Pending Service Status */
            vuint32_t SR29:1;       /* Channel 29 Pending Service Status */
            vuint32_t SR28:1;       /* Channel 28 Pending Service Status */
            vuint32_t SR27:1;       /* Channel 27 Pending Service Status */
            vuint32_t SR26:1;       /* Channel 26 Pending Service Status */
            vuint32_t SR25:1;       /* Channel 25 Pending Service Status */
            vuint32_t SR24:1;       /* Channel 24 Pending Service Status */
            vuint32_t SR23:1;       /* Channel 23 Pending Service Status */
            vuint32_t SR22:1;       /* Channel 22 Pending Service Status */
            vuint32_t SR21:1;       /* Channel 21 Pending Service Status */
            vuint32_t SR20:1;       /* Channel 20 Pending Service Status */
            vuint32_t SR19:1;       /* Channel 19 Pending Service Status */
            vuint32_t SR18:1;       /* Channel 18 Pending Service Status */
            vuint32_t SR17:1;       /* Channel 17 Pending Service Status */
            vuint32_t SR16:1;       /* Channel 16 Pending Service Status */
            vuint32_t SR15:1;       /* Channel 15 Pending Service Status */
            vuint32_t SR14:1;       /* Channel 14 Pending Service Status */
            vuint32_t SR13:1;       /* Channel 13 Pending Service Status */
            vuint32_t SR12:1;       /* Channel 12 Pending Service Status */
            vuint32_t SR11:1;       /* Channel 11 Pending Service Status */
            vuint32_t SR10:1;       /* Channel 10 Pending Service Status */
            vuint32_t SR9:1;        /* Channel 9 Pending Service Status */
            vuint32_t SR8:1;        /* Channel 8 Pending Service Status */
            vuint32_t SR7:1;        /* Channel 7 Pending Service Status */
            vuint32_t SR6:1;        /* Channel 6 Pending Service Status */
            vuint32_t SR5:1;        /* Channel 5 Pending Service Status */
            vuint32_t SR4:1;        /* Channel 4 Pending Service Status */
            vuint32_t SR3:1;        /* Channel 3 Pending Service Status */
            vuint32_t SR2:1;        /* Channel 2 Pending Service Status */
            vuint32_t SR1:1;        /* Channel 1 Pending Service Status */
            vuint32_t SR0:1;        /* Channel 0 Pending Service Status */
        } B;
    } CPSSR_B;

    uint32_t eTPU_reserved0288[2];  /* 0x0288-0x028F */

    union {                 /* ETPU_A Channel Service Status */
        vuint32_t R;
        struct {
            vuint32_t SS31:1;       /* Channel 31 Service Status */
            vuint32_t SS30:1;       /* Channel 30 Service Status */
            vuint32_t SS29:1;       /* Channel 29 Service Status */
            vuint32_t SS28:1;       /* Channel 28 Service Status */
            vuint32_t SS27:1;       /* Channel 27 Service Status */
            vuint32_t SS26:1;       /* Channel 26 Service Status */
            vuint32_t SS25:1;       /* Channel 25 Service Status */
            vuint32_t SS24:1;       /* Channel 24 Service Status */
            vuint32_t SS23:1;       /* Channel 23 Service Status */
            vuint32_t SS22:1;       /* Channel 22 Service Status */
            vuint32_t SS21:1;       /* Channel 21 Service Status */
            vuint32_t SS20:1;       /* Channel 20 Service Status */
            vuint32_t SS19:1;       /* Channel 19 Service Status */
            vuint32_t SS18:1;       /* Channel 18 Service Status */
            vuint32_t SS17:1;       /* Channel 17 Service Status */
            vuint32_t SS16:1;       /* Channel 16 Service Status */
            vuint32_t SS15:1;       /* Channel 15 Service Status */
            vuint32_t SS14:1;       /* Channel 14 Service Status */
            vuint32_t SS13:1;       /* Channel 13 Service Status */
            vuint32_t SS12:1;       /* Channel 12 Service Status */
            vuint32_t SS11:1;       /* Channel 11 Service Status */
            vuint32_t SS10:1;       /* Channel 10 Service Status */
            vuint32_t SS9:1;        /* Channel 9 Service Status */
            vuint32_t SS8:1;        /* Channel 8 Service Status */
            vuint32_t SS7:1;        /* Channel 7 Service Status */
            vuint32_t SS6:1;        /* Channel 6 Service Status */
            vuint32_t SS5:1;        /* Channel 5 Service Status */
            vuint32_t SS4:1;        /* Channel 4 Service Status */
            vuint32_t SS3:1;        /* Channel 3 Service Status */
            vuint32_t SS2:1;        /* Channel 2 Service Status */
            vuint32_t SS1:1;        /* Channel 1 Service Status */
            vuint32_t SS0:1;        /* Channel 0 Service Status */
        } B;
    } CSSR_A;

    union {                 /* ETPU_B Channel Service Status */
        vuint32_t R;
        struct {
            vuint32_t SS31:1;       /* Channel 31 Service Status */
            vuint32_t SS30:1;       /* Channel 30 Service Status */
            vuint32_t SS29:1;       /* Channel 29 Service Status */
            vuint32_t SS28:1;       /* Channel 28 Service Status */
            vuint32_t SS27:1;       /* Channel 27 Service Status */
            vuint32_t SS26:1;       /* Channel 26 Service Status */
            vuint32_t SS25:1;       /* Channel 25 Service Status */
            vuint32_t SS24:1;       /* Channel 24 Service Status */
            vuint32_t SS23:1;       /* Channel 23 Service Status */
            vuint32_t SS22:1;       /* Channel 22 Service Status */
            vuint32_t SS21:1;       /* Channel 21 Service Status */
            vuint32_t SS20:1;       /* Channel 20 Service Status */
            vuint32_t SS19:1;       /* Channel 19 Service Status */
            vuint32_t SS18:1;       /* Channel 18 Service Status */
            vuint32_t SS17:1;       /* Channel 17 Service Status */
            vuint32_t SS16:1;       /* Channel 16 Service Status */
            vuint32_t SS15:1;       /* Channel 15 Service Status */
            vuint32_t SS14:1;       /* Channel 14 Service Status */
            vuint32_t SS13:1;       /* Channel 13 Service Status */
            vuint32_t SS12:1;       /* Channel 12 Service Status */
            vuint32_t SS11:1;       /* Channel 11 Service Status */
            vuint32_t SS10:1;       /* Channel 10 Service Status */
            vuint32_t SS9:1;        /* Channel 9 Service Status */
            vuint32_t SS8:1;        /* Channel 8 Service Status */
            vuint32_t SS7:1;        /* Channel 7 Service Status */
            vuint32_t SS6:1;        /* Channel 6 Service Status */
            vuint32_t SS5:1;        /* Channel 5 Service Status */
            vuint32_t SS4:1;        /* Channel 4 Service Status */
            vuint32_t SS3:1;        /* Channel 3 Service Status */
            vuint32_t SS2:1;        /* Channel 2 Service Status */
            vuint32_t SS1:1;        /* Channel 1 Service Status */
            vuint32_t SS0:1;        /* Channel 0 Service Status */
        } B;
    } CSSR_B;

    uint32_t eTPU_reserved0298[2];  /* 0x0298-0x029F */

    uint32_t eTPU_reserved02A0[88];  /* 0x02A0-0x03FF */

/*****************************Channels********************************/

    struct {
        union {    /* Channel Configuration Register */
            vuint32_t R;
            struct {
                vuint32_t CIE:1;    /* Channel Interruput Enable */
                vuint32_t DTRE:1;   /* Data Transfer Request Enable */
                vuint32_t CPR:2;    /* Channel Priority */
                vuint32_t:2;
                vuint32_t ETPD:1;
                vuint32_t ETCS:1;   /* Entry Table Condition Select */
                vuint32_t:3;
                vuint32_t CFS:5;    /* Channel Function Select */
                vuint32_t ODIS:1;   /* Output disable */
                vuint32_t OPOL:1;   /* output polarity */
                vuint32_t:3;
                vuint32_t CPBA:11;  /* Channel Parameter Base Address */
            } B;
        } CR;

        union {    /* Channel Status Control Register */
            vuint32_t R;
            struct {
                vuint32_t CIS:1;    /* Channel Interruput Status */
                vuint32_t CIOS:1;   /* Channel Interruput Overflow Status */
                vuint32_t:6;
                vuint32_t DTRS:1;   /* Data Transfer Status */
                vuint32_t DTROS:1;  /* Data Transfer Overflow Status */
                vuint32_t:6;
                vuint32_t IPS:1;    /* Input Pin State */
                vuint32_t OPS:1;    /* Output Pin State */
                vuint32_t OBE:1;    /* Output Buffer Enable */
                vuint32_t:11;
                vuint32_t FM1:1;    /* Function mode */
                vuint32_t FM0:1;    /* Function mode */
            } B;
        } SCR;

        union {    /* Channel Host Service Request Register */
            vuint32_t R;
            struct {
                vuint32_t:29;       /* Host Service Request */
                vuint32_t HSR:3;
            } B;
        } HSRR;

        uint32_t eTPU_ch_reserved00C;  /* channel offset 0x00C-0x00F */

    } CHAN[127];

    uint32_t eTPU_reserved1000[7168];  /* 0x1000-0x7FFF */

} eTPU_Type;

#endif
