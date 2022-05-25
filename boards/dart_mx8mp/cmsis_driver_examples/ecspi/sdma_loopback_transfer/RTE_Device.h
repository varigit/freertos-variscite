/*
 * Copyright 2019,2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RTE_DEVICE_H
#define _RTE_DEVICE_H

extern void ECSPI1_InitPins();
extern void ECSPI1_DeinitPins();

/* Driver name mapping. */
#define RTE_SPI1        1
#define RTE_SPI1_DMA_EN 1

/* ECSPI configuration. */
#define RTE_SPI1_TRANSFER_CHANNEL   kECSPI_Channel0
#define RTE_SPI1_PIN_INIT           ECSPI1_InitPins
#define RTE_SPI1_PIN_DEINIT         ECSPI1_DeinitPins
#define RTE_SPI1_DMA_TX_DMA_BASE    SDMAARM1
#define RTE_SPI1_DMA_TX_CH          (2U)
#define RTE_SPI1_DMA_TX_CH_REQUEST  (1U)
#define RTE_SPI1_DMA_TX_CH_PRIORITY (3U)
#define RTE_SPI1_DMA_RX_DMA_BASE    SDMAARM1
#define RTE_SPI1_DMA_RX_CH          (1U)
#define RTE_SPI1_DMA_RX_CH_REQUEST  (0U)
#define RTE_SPI1_DMA_RX_CH_PRIORITY (2U)

#endif /* _RTE_DEVICE_H */
