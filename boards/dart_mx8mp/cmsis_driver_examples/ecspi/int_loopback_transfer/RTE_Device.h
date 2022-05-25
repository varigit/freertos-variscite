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
#define RTE_SPI1_DMA_EN 0

/* ECSPI configuration. */
#define RTE_SPI1_PIN_INIT         ECSPI1_InitPins
#define RTE_SPI1_PIN_DEINIT       ECSPI1_DeinitPins
#define RTE_SPI1_TRANSFER_CHANNEL kECSPI_Channel0

#endif /* _RTE_DEVICE_H */
