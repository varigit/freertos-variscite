/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __RTE_DEVICE_H
#define __RTE_DEVICE_H

/* Driver name mapping. */
#define RTE_USART3 1
#define RTE_USART3_DMA_EN 1

/* UART configuration. */
#define USART_RX_BUFFER_LEN 64
#define USART3_RX_BUFFER_ENABLE 0

#define RTE_USART3_SDMA_TX_CH 2
#define RTE_USART3_SDMA_TX_REQUEST (27)
#define RTE_USART3_SDMA_TX_DMA_BASE SDMAARM1
#define RTE_USART3_SDMA_TX_PRIORITY (3)
#define RTE_USART3_SDMA_RX_CH 1
#define RTE_USART3_SDMA_RX_REQUEST (26)
#define RTE_USART3_SDMA_RX_DMA_BASE SDMAARM1
#define RTE_USART3_SDMA_RX_PRIORITY (4)

#endif /* __RTE_DEVICE_H */
