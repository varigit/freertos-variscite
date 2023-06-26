/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_EDMA_SOC_H_
#define _FSL_EDMA_SOC_H_

#include "fsl_common.h"

/*!
 * @addtogroup edma_soc
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*@{*/
/*! @brief Driver version 2.0.0. */
#define FSL_EDMA_SOC_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

/*!@brief DMA IP version */
#define FSL_EDMA_SOC_IP_DMA3 (1)
#define FSL_EDMA_SOC_IP_DMA4 (1)

/*!@brief DMA base table */
#define EDMA_BASE_PTRS \
    {                  \
        DMA3, DMA4     \
    }

#define EDMA_CHN_IRQS                                                                                                 \
    {                                                                                                                 \
        {                                                                                                             \
            DMA3_0_IRQn,  DMA3_1_IRQn,  DMA3_2_IRQn,  DMA3_3_IRQn,  DMA3_4_IRQn,  DMA3_5_IRQn,  DMA3_6_IRQn,          \
            DMA3_7_IRQn,  DMA3_8_IRQn,  DMA3_9_IRQn,  DMA3_10_IRQn, DMA3_11_IRQn, DMA3_12_IRQn, DMA3_13_IRQn,         \
            DMA3_14_IRQn, DMA3_15_IRQn, DMA3_16_IRQn, DMA3_17_IRQn, DMA3_18_IRQn, DMA3_19_IRQn, DMA3_20_IRQn,         \
            DMA3_21_IRQn, DMA3_22_IRQn, DMA3_23_IRQn, DMA3_24_IRQn, DMA3_25_IRQn, DMA3_26_IRQn, DMA3_27_IRQn,         \
            DMA3_28_IRQn, DMA3_29_IRQn, DMA3_30_IRQn,                                                                 \
        },                                                                                                            \
        {                                                                                                             \
            DMA4_0_1_IRQn, DMA4_0_1_IRQn, DMA4_2_3_IRQn, DMA4_2_3_IRQn, DMA4_4_5_IRQn, DMA4_4_5_IRQn, DMA4_6_7_IRQn,  \
                DMA4_6_7_IRQn, DMA4_8_9_IRQn, DMA4_8_9_IRQn, DMA4_10_11_IRQn, DMA4_10_11_IRQn, DMA4_12_13_IRQn,       \
                DMA4_12_13_IRQn, DMA4_14_15_IRQn, DMA4_14_15_IRQn, DMA4_16_17_IRQn, DMA4_16_17_IRQn, DMA4_18_19_IRQn, \
                DMA4_18_19_IRQn, DMA4_20_21_IRQn, DMA4_20_21_IRQn, DMA4_22_23_IRQn, DMA4_22_23_IRQn, DMA4_24_25_IRQn, \
                DMA4_24_25_IRQn, DMA4_26_27_IRQn, DMA4_26_27_IRQn, DMA4_28_29_IRQn, DMA4_28_29_IRQn, DMA4_30_31_IRQn, \
                DMA4_30_31_IRQn, DMA4_32_33_IRQn, DMA4_32_33_IRQn, DMA4_34_35_IRQn, DMA4_34_35_IRQn, DMA4_36_37_IRQn, \
                DMA4_36_37_IRQn, DMA4_38_39_IRQn, DMA4_38_39_IRQn, DMA4_40_41_IRQn, DMA4_40_41_IRQn, DMA4_42_43_IRQn, \
                DMA4_42_43_IRQn, DMA4_44_45_IRQn, DMA4_44_45_IRQn, DMA4_46_47_IRQn, DMA4_46_47_IRQn, DMA4_48_49_IRQn, \
                DMA4_48_49_IRQn, DMA4_50_51_IRQn, DMA4_50_51_IRQn, DMA4_52_53_IRQn, DMA4_52_53_IRQn, DMA4_54_55_IRQn, \
                DMA4_54_55_IRQn, DMA4_56_57_IRQn, DMA4_56_57_IRQn, DMA4_58_59_IRQn, DMA4_58_59_IRQn, DMA4_60_61_IRQn, \
                DMA4_60_61_IRQn, DMA4_62_63_IRQn, DMA4_62_63_IRQn,                                                    \
        }                                                                                                             \
    }

/*!@brief dma request source */
typedef enum _dma_request_source
{
    kDmaRequestDisabled                = 0U,           /**< DSisabled*/
    Dma3RequestMuxCAN1                 = 1U | 0x100U,  /**< CAN1 */
    Dma3RequestMuxGPIO1Request0        = 3U | 0x100U,  /**< GPIO1 channel 0 */
    Dma3RequestMuxGPIO1Request1        = 4U | 0x100U,  /**< GPIO1 channel 1 */
    Dma3RequestMuxI3C1ToBusRequest     = 5U | 0x100U,  /**< I3C1 To-bus Request */
    Dma3RequestMuxI3C1FromBusRequest   = 6U | 0x100U,  /**< I3C1 From-bus Request */
    Dma3RequestMuxLPI2C1Tx             = 7U | 0x100U,  /**< LPI2C1 */
    Dma3RequestMuxLPI2C1Rx             = 8U | 0x100U,  /**< LPI2C1 */
    Dma3RequestMuxLPI2C2Tx             = 9U | 0x100U,  /**< LPI2C2 */
    Dma3RequestMuxLPI2C2Rx             = 10U | 0x100U, /**< LPI2C2 */
    Dma3RequestMuxLPSPI1Tx             = 11U | 0x100U, /**< LPSPI1 Transmit */
    Dma3RequestMuxLPSPI1Rx             = 12U | 0x100U, /**< LPSPI1 Receive */
    Dma3RequestMuxLPSPI2Tx             = 13U | 0x100U, /**< LPSPI2 Transmit */
    Dma3RequestMuxLPSPI2Rx             = 14U | 0x100U, /**< LPSPI2 Receive */
    Dma3RequestMuxLPTMR1Request        = 15U | 0x100U, /**< LPTMR1 Request */
    Dma3RequestMuxLPUART1Tx            = 16U | 0x100U, /**< LPUART1 Transmit */
    Dma3RequestMuxLPUART1Rx            = 17U | 0x100U, /**< LPUART1 Receive */
    Dma3RequestMuxLPUART2Tx            = 18U | 0x100U, /**< LPUART2 Transmit */
    Dma3RequestMuxLPUART2Rx            = 19U | 0x100U, /**< LPUART2 Receive */
    Dma3RequestMuxEdgelockRequest      = 20U | 0x100U, /**< Edgelock enclave DMA Request */
    Dma3RequestMuxSai1Tx               = 21U | 0x100U, /**< SAI1 Transmit */
    Dma3RequestMuxSai1Rx               = 22U | 0x100U, /**< SAI1 Receive */
    Dma3RequestMuxTPM1Request0Request2 = 23U | 0x100U, /**< TPM1 request 0 and request 2 */
    Dma3RequestMuxTPM1Request1Request3 = 24U | 0x100U, /**< TPM1 request 1 and request 3 */
    Dma3RequestMuxTPM1OverflowRequest  = 25U | 0x100U, /**< TPM1 Overflow request */
    Dma3RequestMuxTPM2Request0Request2 = 26U | 0x100U, /**< TPM2 request 0 and request 2 */
    Dma3RequestMuxTPM2Request1Request3 = 27U | 0x100U, /**< TPM2 request 1 and request 3 */
    Dma3RequestMuxTPM2OverflowRequest  = 28U | 0x100U, /**< TPM2 Overflow request */
    Dma3RequestMuxPDMRequest           = 29U | 0x100U, /**< PDM */
    Dma3RequestMuxADC1Request          = 30U | 0x100U, /**< ADC1 */
    Dma4RequestMuxCAN2                 = 1U | 0x200U,  /**< CAN2 */
    Dma4RequestMuxGPIO2Request0        = 2U | 0x200U,  /**< GPIO2 channel 0 */
    Dma4RequestMuxGPIO2Request1        = 3U | 0x200U,  /**< GPIO2 channel 1 */
    Dma4RequestMuxGPIO3Request0        = 4U | 0x200U,  /**< GPIO3 channel 0 */
    Dma4RequestMuxGPIO3Request1        = 5U | 0x200U,  /**< GPIO3 channel 1 */
    Dma4RequestMuxI3C2ToBusRequest     = 6U | 0x200U,  /**< I3C2 To-bus Request */
    Dma4RequestMuxI3C2FromBusRequest   = 7U | 0x200U,  /**< I3C2 From-bus Request */
    Dma4RequestMuxLPI2C3Tx             = 8U | 0x200U,  /**< LPI2C3 */
    Dma4RequestMuxLPI2C3Rx             = 9U | 0x200U,  /**< LPI2C3 */
    Dma4RequestMuxLPI2C4Tx             = 10U | 0x200U, /**< LPI2C4 */
    Dma4RequestMuxLPI2C4Rx             = 11U | 0x200U, /**< LPI2C4 */
    Dma4RequestMuxLPSPI3Tx             = 12U | 0x200U, /**< LPSPI3 Transmit */
    Dma4RequestMuxLPSPI3Rx             = 13U | 0x200U, /**< LPSPI3 Receive */
    Dma4RequestMuxLPSPI4Tx             = 14U | 0x200U, /**< LPSPI4 Transmit */
    Dma4RequestMuxLPSPI4Rx             = 15U | 0x200U, /**< LPSPI4 Receive */
    Dma4RequestMuxLPTMR2Request        = 16U | 0x200U, /**< LPTMR2 Request */
    Dma4RequestMuxLPUART3Tx            = 17U | 0x200U, /**< LPUART3 Transmit */
    Dma4RequestMuxLPUART3Rx            = 18U | 0x200U, /**< LPUART3 Receive */
    Dma4RequestMuxLPUART4Tx            = 19U | 0x200U, /**< LPUART4 Transmit */
    Dma4RequestMuxLPUART4Rx            = 20U | 0x200U, /**< LPUART4 Receive */
    Dma4RequestMuxLPUART5Tx            = 21U | 0x200U, /**< LPUART5 Transmit */
    Dma4RequestMuxLPUART5Rx            = 22U | 0x200U, /**< LPUART5 Receive */
    Dma4RequestMuxLPUART6Tx            = 23U | 0x200U, /**< LPUART6 Transmit */
    Dma4RequestMuxLPUART6Rx            = 24U | 0x200U, /**< LPUART6 Receive */
    Dma4RequestMuxTPM3Request0Request2 = 25U | 0x200U, /**< TPM3 request 0 and request 2 */
    Dma4RequestMuxTPM3Request1Request3 = 26U | 0x200U, /**< TPM3 request 1 and request 3 */
    Dma4RequestMuxTPM3OverflowRequest  = 27U | 0x200U, /**< TPM3 Overflow request */
    Dma4RequestMuxTPM4Request0Request2 = 28U | 0x200U, /**< TPM4 request 0 and request 2 */
    Dma4RequestMuxTPM4Request1Request3 = 29U | 0x200U, /**< TPM4 request 1 and request 3 */
    Dma4RequestMuxTPM4OverflowRequest  = 30U | 0x200U, /**< TPM4 Overflow request */
    Dma4RequestMuxTPM5Request0Request2 = 31U | 0x200U, /**< TPM5 request 0 and request 2 */
    Dma4RequestMuxTPM5Request1Request3 = 32U | 0x200U, /**< TPM5 request 1 and request 3 */
    Dma4RequestMuxTPM5OverflowRequest  = 33U | 0x200U, /**< TPM5 Overflow request */
    Dma4RequestMuxTPM6Request0Request2 = 34U | 0x200U, /**< TPM6 request 0 and request 2 */
    Dma4RequestMuxTPM6Request1Request3 = 35U | 0x200U, /**< TPM6 request 1 and request 3 */
    Dma4RequestMuxTPM6OverflowRequest  = 36U | 0x200U, /**< TPM6 Overflow request */
    Dma4RequestMuxFlexIO1Request0      = 37U | 0x200U, /**< FlexIO1 Request0 */
    Dma4RequestMuxFlexIO1Request1      = 38U | 0x200U, /**< FlexIO1 Request1 */
    Dma4RequestMuxFlexIO1Request2      = 39U | 0x200U, /**< FlexIO1 Request2 */
    Dma4RequestMuxFlexIO1Request3      = 40U | 0x200U, /**< FlexIO1 Request3 */
    Dma4RequestMuxFlexIO1Request4      = 41U | 0x200U, /**< FlexIO1 Request4 */
    Dma4RequestMuxFlexIO1Request5      = 42U | 0x200U, /**< FlexIO1 Request5 */
    Dma4RequestMuxFlexIO1Request6      = 43U | 0x200U, /**< FlexIO1 Request6 */
    Dma4RequestMuxFlexIO1Request7      = 44U | 0x200U, /**< FlexIO1 Request7 */
    Dma4RequestMuxFlexIO2Request0      = 45U | 0x200U, /**< FlexIO2 Request0 */
    Dma4RequestMuxFlexIO2Request1      = 46U | 0x200U, /**< FlexIO2 Request1 */
    Dma4RequestMuxFlexIO2Request2      = 47U | 0x200U, /**< FlexIO2 Request2 */
    Dma4RequestMuxFlexIO2Request3      = 48U | 0x200U, /**< FlexIO2 Request3 */
    Dma4RequestMuxFlexIO2Request4      = 49U | 0x200U, /**< FlexIO2 Request4 */
    Dma4RequestMuxFlexIO2Request5      = 50U | 0x200U, /**< FlexIO2 Request5 */
    Dma4RequestMuxFlexIO2Request6      = 51U | 0x200U, /**< FlexIO2 Request6 */
    Dma4RequestMuxFlexIO2Request7      = 52U | 0x200U, /**< FlexIO2 Request7 */
    Dma4RequestMuxFlexSPI1Tx           = 53U | 0x200U, /**< FlexSPI1 Transmit */
    Dma4RequestMuxSai2Tx               = 58U | 0x200U, /**< SAI2 Transmit */
    Dma4RequestMuxSai2Rx               = 59U | 0x200U, /**< SAI2 Receive */
    Dma4RequestMuxSai3Tx               = 60U | 0x200U, /**< SAI3 Transmit */
    Dma4RequestMuxSai3Rx               = 61U | 0x200U, /**< SAI3 Receive */
    Dma4RequestMuxGPIO4Request0        = 62U | 0x200U, /**< GPIO4 channel 0 */
    Dma4RequestMuxGPIO4Request1        = 63U | 0x200U, /**< GPIO4 channel 1 */
    Dma4RequestMuxSPDIFRequest         = 65U | 0x200U, /**< SPDIF */
    Dma4RequestMuxSPDIFRequest1        = 66U | 0x200U, /**< SPDIF */
    Dma4RequestMuxENETRequest          = 67U | 0x200U, /**< ENET */
    Dma4RequestMuxENETRequest1         = 68U | 0x200U, /**< ENET */
    Dma4RequestMuxENETRequest2         = 69U | 0x200U, /**< ENET */
    Dma4RequestMuxENETRequest3         = 70U | 0x200U, /**< ENET */
    Dma4RequestMuxLPI2C5Tx             = 71U | 0x200U, /**< LPI2C5 */
    Dma4RequestMuxLPI2C5Rx             = 72U | 0x200U, /**< LPI2C5 */
    Dma4RequestMuxLPI2C6Tx             = 73U | 0x200U, /**< LPI2C6 */
    Dma4RequestMuxLPI2C6Rx             = 74U | 0x200U, /**< LPI2C6 */
    Dma4RequestMuxLPI2C7Tx             = 75U | 0x200U, /**< LPI2C7 */
    Dma4RequestMuxLPI2C7Rx             = 76U | 0x200U, /**< LPI2C7 */
    Dma4RequestMuxLPI2C8Tx             = 77U | 0x200U, /**< LPI2C8 */
    Dma4RequestMuxLPI2C8Rx             = 78U | 0x200U, /**< LPI2C8 */
    Dma4RequestMuxLPSPI5Tx             = 79U | 0x200U, /**< LPSPI5 Transmit */
    Dma4RequestMuxLPSPI5Rx             = 80U | 0x200U, /**< LPSPI5 Receive */
    Dma4RequestMuxLPSPI6Tx             = 81U | 0x200U, /**< LPSPI6 Transmit */
    Dma4RequestMuxLPSPI6Rx             = 82U | 0x200U, /**< LPSPI6 Receive */
    Dma4RequestMuxLPSPI7Tx             = 83U | 0x200U, /**< LPSPI7 Transmit */
    Dma4RequestMuxLPSPI7Rx             = 84U | 0x200U, /**< LPSPI7 Receive */
    Dma4RequestMuxLPSPI8Tx             = 85U | 0x200U, /**< LPSPI8 Transmit */
    Dma4RequestMuxLPSPI8Rx             = 86U | 0x200U, /**< LPSPI8 Receive */
    Dma4RequestMuxLPUART7Tx            = 87U | 0x200U, /**< LPUART7 Transmit */
    Dma4RequestMuxLPUART7Rx            = 88U | 0x200U, /**< LPUART7 Receive */
    Dma4RequestMuxLPUART8Tx            = 89U | 0x200U, /**< LPUART8 Transmit */
    Dma4RequestMuxLPUART8Rx            = 90U | 0x200U, /**< LPUART8 Receive */
    Dma4RequestMuxENET_QOSRequest      = 91U | 0x200U, /**< ENET_QOS */
    Dma4RequestMuxENET_QOSRequest1     = 92U | 0x200U, /**< ENET_QOS */
    Dma4RequestMuxENET_QOSRequest2     = 93U | 0x200U, /**< ENET_QOS */
    Dma4RequestMuxENET_QOSRequest3     = 94U | 0x200U, /**< ENET_QOS */
} dma_request_source_t;

/*!< Verify dma base and request source */
#define EDMA_CHANNEL_HAS_REQUEST_SOURCE(base, source) ((base) == DMA3 ? ((source)&0x100U) : ((source)&0x200U))

#undef FSL_FEATURE_EDMA_HAS_CHANNEL_MUX
#define FSL_FEATURE_EDMA_HAS_CHANNEL_MUX                  (1)
#define FSL_FEATURE_EDMA_HAS_GLOBAL_MASTER_ID_REPLICATION (1)
#define FSL_FEATURE_EDMA_HAS_CONTINUOUS_LINK_MODE         (0)
#define FSL_FEATURE_EDMA_HAS_CHANNEL_CONFIG               (1)
#define FSL_FEATURE_EDMA_HAS_CHANNEL_SWAP_SIZE            (1) /* decided by module support */
#define FSL_FEATURE_EDMA_HAS_CHANNEL_ACCESS_TYPE          (1) /* decided by module support */
#define FSL_FEATURE_EDMA_HAS_CHANNEL_MEMRORY_ATTRIBUTE    (1) /* decided by module support */
#define FSL_FEATURE_EDMA_HAS_CHANNEL_SIGN_EXTENSION       (1) /* decided by module support */
#define FSL_FEATURE_EDMA_SUPPORT_128_BYTES_TRANSFER       (1) /* decided by module support */

#undef FSL_FEATURE_EDMA_MODULE_CHANNEL
#define FSL_FEATURE_EDMA_MODULE_CHANNEL(base)                    ((base) == DMA3 ? 31U : 64U)
#define FSL_FEATURE_EDMA_MODULE_MAX_CHANNEL                      (64)
#define FSL_FEATURE_EDMA_MODULE_COUNT                            (2)
#define FSL_FEATURE_EDMA_MODULE_SUPPORT_SWAP(base)               ((base) == DMA3 ? 0U : 1U)
#define FSL_FEATURE_EDMA_MODULE_SUPPORT_INSTR(base)              ((base) == DMA3 ? 0U : 1U)
#define FSL_FEATURE_EDMA_MODULE_SUPPORT_MATTR(base)              ((base) == DMA3 ? 0U : 1U)
#define FSL_FEATURE_EDMA_MODULE_SUPPORT_SIGN_EXTENSION(base)     ((base) == DMA3 ? 0U : 1U)
#define FSL_FEATURE_EDMA_MODULE_SUPPORT_128_BYTES_TRANSFER(base) ((base) == DMA3 ? 0U : 1U)
#define FSL_FEATURE_EDMA_MODULE_SUPPORT_CHANNEL_MUX(base)        ((base) == DMA3 ? 0U : 1U)

/*!@brief EDMA base address convert macro */
#define EDMA_CHANNEL_OFFSET           0x10000U
#define EDMA_CHANNEL_ARRAY_STEP(base) ((base) == DMA3 ? 0x10000U : 0x8000U)

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* _FSL_EDMA_SOC_H_ */
