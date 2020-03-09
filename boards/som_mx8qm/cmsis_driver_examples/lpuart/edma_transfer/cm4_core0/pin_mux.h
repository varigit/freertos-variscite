/*
 * Copyright 2017-2018 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

#include "board.h"

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

/* LVDS0_I2C1_SDA (number BE35), DMA_UART2_RX */
#define BOARD_INITPINSEX_DEBUG_UART_RX_PERIPHERAL                     DMA__UART2   /*!< Device name: DMA__UART2 */
#define BOARD_INITPINSEX_DEBUG_UART_RX_SIGNAL                            uart_rx   /*!< DMA__UART2 signal: uart_rx */
#define BOARD_INITPINSEX_DEBUG_UART_RX_PIN_NAME                   LVDS0_I2C1_SDA   /*!< Pin name */
#define BOARD_INITPINSEX_DEBUG_UART_RX_PIN_FUNCTION_ID       SC_P_LVDS0_I2C1_SDA   /*!< Pin function id */
#define BOARD_INITPINSEX_DEBUG_UART_RX_PIN_MUX                                1U   /*!< mux settings */
#define BOARD_INITPINSEX_DEBUG_UART_RX_LABEL                      "DMA_UART2_RX"   /*!< Label */
#define BOARD_INITPINSEX_DEBUG_UART_RX_NAME                       "DMA_UART2_RX"   /*!< Identifier name */

/* LVDS0_I2C1_SCL (number BE37), DMA_UART2_TX */
#define BOARD_INITPINSEX_DEBUG_UART_TX_PERIPHERAL                     DMA__UART2   /*!< Device name: DMA__UART2 */
#define BOARD_INITPINSEX_DEBUG_UART_TX_SIGNAL                            uart_tx   /*!< DMA__UART2 signal: uart_tx */
#define BOARD_INITPINSEX_DEBUG_UART_TX_PIN_NAME                   LVDS0_I2C1_SCL   /*!< Pin name */
#define BOARD_INITPINSEX_DEBUG_UART_TX_PIN_FUNCTION_ID       SC_P_LVDS0_I2C1_SCL   /*!< Pin function id */
#define BOARD_INITPINSEX_DEBUG_UART_TX_PIN_MUX                                1U   /*!< mux settings */
#define BOARD_INITPINSEX_DEBUG_UART_TX_LABEL                      "DMA_UART2_TX"   /*!< Label */
#define BOARD_INITPINSEX_DEBUG_UART_TX_NAME                       "DMA_UART2_TX"   /*!< Identifier name */

/* LVDS0_I2C1_SDA (number BE35), DMA_UART2_RX */
#define BOARD_DEINITPINSEX_DEBUG_UART_RX_GPIO                        LSIO__GPIO1   /*!< GPIO device name: LSIO__GPIO1 */
#define BOARD_DEINITPINSEX_DEBUG_UART_RX_GPIO_PIN                             9U   /*!< LSIO__GPIO1 pin index: 9 */
#define BOARD_DEINITPINSEX_DEBUG_UART_RX_PIN_NAME                 LVDS0_I2C1_SDA   /*!< Pin name */
#define BOARD_DEINITPINSEX_DEBUG_UART_RX_PIN_FUNCTION_ID     SC_P_LVDS0_I2C1_SDA   /*!< Pin function id */
#define BOARD_DEINITPINSEX_DEBUG_UART_RX_PIN_MUX                              3U   /*!< mux settings */
#define BOARD_DEINITPINSEX_DEBUG_UART_RX_LABEL                    "DMA_UART2_RX"   /*!< Label */
#define BOARD_DEINITPINSEX_DEBUG_UART_RX_NAME                     "DMA_UART2_RX"   /*!< Identifier name */
#define BOARD_DEINITPINSEX_DEBUG_UART_RX_DIRECTION            kGPIO_DigitalInput   /*!< Direction */

/* LVDS0_I2C1_SCL (number BE37), DMA_UART2_TX */
#define BOARD_DEINITPINSEX_DEBUG_UART_TX_GPIO                        LSIO__GPIO1   /*!< GPIO device name: LSIO__GPIO1 */
#define BOARD_DEINITPINSEX_DEBUG_UART_TX_GPIO_PIN                             8U   /*!< LSIO__GPIO1 pin index: 8 */
#define BOARD_DEINITPINSEX_DEBUG_UART_TX_PIN_NAME                 LVDS0_I2C1_SCL   /*!< Pin name */
#define BOARD_DEINITPINSEX_DEBUG_UART_TX_PIN_FUNCTION_ID     SC_P_LVDS0_I2C1_SCL   /*!< Pin function id */
#define BOARD_DEINITPINSEX_DEBUG_UART_TX_PIN_MUX                              3U   /*!< mux settings */
#define BOARD_DEINITPINSEX_DEBUG_UART_TX_LABEL                    "DMA_UART2_TX"   /*!< Label */
#define BOARD_DEINITPINSEX_DEBUG_UART_TX_NAME                     "DMA_UART2_TX"   /*!< Identifier name */
#define BOARD_DEINITPINSEX_DEBUG_UART_TX_DIRECTION            kGPIO_DigitalInput   /*!< Direction */

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif


/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 * @param ipc scfw ipchandle.
 *
 */
void LPUART4_InitPinsEx(sc_ipc_t ipc);                     /*!< Function assigned for the core: Cortex-M4F[cm4_0] */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 * @param ipc scfw ipchandle.
 *
 */
void LPUART4_DeinitPinsEx(sc_ipc_t ipc);                   /*!< Function assigned for the core: Cortex-M4F[cm4_0] */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
