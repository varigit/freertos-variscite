/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RTE_DEVICE_H
#define _RTE_DEVICE_H

extern void UART3_InitPins();
extern void UART3_DeinitPins();

/* Driver name mapping. */
/* User needs to provide the implementation of UARTX_GetFreq/UARTX_InitPins/UARTX_DeinitPins for the enabled UART
 * instance. */
#define RTE_USART3            1
#define RTE_USART3_PIN_INIT   UART3_InitPins
#define RTE_USART3_PIN_DEINIT UART3_DeinitPins
#define RTE_USART3_DMA_EN     1

/* UART configuration. */
#define USART_RX_BUFFER_LEN     64
#define USART3_RX_BUFFER_ENABLE 0

#define RTE_USART3_SDMA_TX_CH       2
#define RTE_USART3_SDMA_TX_REQUEST  (27)
#define RTE_USART3_SDMA_TX_DMA_BASE SDMAARM1
#define RTE_USART3_SDMA_TX_PRIORITY (3)
#define RTE_USART3_SDMA_RX_CH       1
#define RTE_USART3_SDMA_RX_REQUEST  (26)
#define RTE_USART3_SDMA_RX_DMA_BASE SDMAARM1
#define RTE_USART3_SDMA_RX_PRIORITY (4)

#endif /* _RTE_DEVICE_H */
