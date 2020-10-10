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

/* UART1_RX (coord L31), UART1_RX */
#define BOARD_INITPINS_DEBUG_UART_RX_PERIPHERAL          ADMA__UART1        /*!< Device name: ADMA__UART1 */
#define BOARD_INITPINS_DEBUG_UART_RX_SIGNAL              uart_rx            /*!< ADMA__UART1 signal: uart_rx */
#define BOARD_INITPINS_DEBUG_UART_RX_PIN_NAME            UART1_RX           /*!< Pin name */
#define BOARD_INITPINS_DEBUG_UART_RX_PIN_FUNCTION_ID     SC_P_UART1_RX      /*!< Pin function id */
#define BOARD_INITPINS_DEBUG_UART_RX_LABEL               "DEBUG_UART1_RX"   /*!< Label */
#define BOARD_INITPINS_DEBUG_UART_RX_NAME                "DEBUG_UART1_RX"   /*!< Identifier name */

/* UART1_TX (coord H34), UART1_TX */
#define BOARD_INITPINS_DEBUG_UART_TX_PERIPHERAL          ADMA__UART1        /*!< Device name: ADMA__UART1 */
#define BOARD_INITPINS_DEBUG_UART_TX_SIGNAL              uart_tx            /*!< ADMA__UART1 signal: uart_tx */
#define BOARD_INITPINS_DEBUG_UART_TX_PIN_NAME            UART1_TX           /*!< Pin name */
#define BOARD_INITPINS_DEBUG_UART_TX_PIN_FUNCTION_ID     SC_P_UART1_TX      /*!< Pin function id */
#define BOARD_INITPINS_DEBUG_UART_TX_LABEL               "DEBUG_UART1_TX"   /*!< Label */
#define BOARD_INITPINS_DEBUG_UART_TX_NAME                "DEBUG_UART1_TX"   /*!< Identifier name */

/* SPI0_SCK (coord P30), M4_GPIO0_IO0 */
#define BOARD_INITPINS_SPI0_SCK_GPIO                           M40__GPIO0   /*!< GPIO device name: M40__GPIO0 */
#define BOARD_INITPINS_SPI0_SCK_GPIO_PIN                               0U   /*!< M40__GPIO0 pin index: 0 */
#define BOARD_INITPINS_SPI0_SCK_PIN_NAME                         SPI0_SCK   /*!< Pin name */
#define BOARD_INITPINS_SPI0_SCK_PIN_FUNCTION_ID             SC_P_SPI0_SCK   /*!< Pin function id */
#define BOARD_INITPINS_SPI0_SCK_LABEL                      "M4_GPIO0_IO0"   /*!< Label */
#define BOARD_INITPINS_SPI0_SCK_NAME                       "M4_GPIO0_IO0"   /*!< Identifier name */

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
void BOARD_InitPins(sc_ipc_t ipc);                         /*!< Function assigned for the core: Cortex-M4F[m4] */

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
