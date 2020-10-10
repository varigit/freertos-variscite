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
#define BOARD_DEBUG_UART_RX_PERIPHERAL                                DMA__UART2   /*!< Device name: DMA__UART2 */
#define BOARD_DEBUG_UART_RX_SIGNAL                                       uart_rx   /*!< DMA__UART2 signal: uart_rx */
#define BOARD_DEBUG_UART_RX_PIN_NAME                              LVDS0_I2C1_SDA   /*!< Pin name */
#define BOARD_DEBUG_UART_RX_PIN_FUNCTION_ID                  SC_P_LVDS0_I2C1_SDA   /*!< Pin function id */
#define BOARD_DEBUG_UART_RX_PIN_MUX                                           1U   /*!< mux settings */
#define BOARD_DEBUG_UART_RX_LABEL                                 "DMA_UART2_RX"   /*!< Label */
#define BOARD_DEBUG_UART_RX_NAME                                  "DMA_UART2_RX"   /*!< Identifier name */

/* LVDS0_I2C1_SCL (number BE37), DMA_UART2_TX */
#define BOARD_DEBUG_UART_TX_PERIPHERAL                                DMA__UART2   /*!< Device name: DMA__UART2 */
#define BOARD_DEBUG_UART_TX_SIGNAL                                       uart_tx   /*!< DMA__UART2 signal: uart_tx */
#define BOARD_DEBUG_UART_TX_PIN_NAME                              LVDS0_I2C1_SCL   /*!< Pin name */
#define BOARD_DEBUG_UART_TX_PIN_FUNCTION_ID                  SC_P_LVDS0_I2C1_SCL   /*!< Pin function id */
#define BOARD_DEBUG_UART_TX_PIN_MUX                                           1U   /*!< mux settings */
#define BOARD_DEBUG_UART_TX_LABEL                                 "DMA_UART2_TX"   /*!< Label */
#define BOARD_DEBUG_UART_TX_NAME                                  "DMA_UART2_TX"   /*!< Identifier name */

/* FLEXCAN0_RX (coord C5), BB_CAN0_RX */
#define BOARD_INITPINS_BB_CAN0_RX_PERIPHERAL                       DMA__FLEXCAN0   /*!< Device name: DMA__FLEXCAN0 */
#define BOARD_INITPINS_BB_CAN0_RX_SIGNAL                              flexcan_rx   /*!< DMA__FLEXCAN0 signal: flexcan_rx */
#define BOARD_INITPINS_BB_CAN0_RX_PIN_NAME                           FLEXCAN0_RX   /*!< Pin name */
#define BOARD_INITPINS_BB_CAN0_RX_PIN_FUNCTION_ID               SC_P_FLEXCAN0_RX   /*!< Pin function id */
#define BOARD_INITPINS_BB_CAN0_RX_LABEL                    "BB_CAN0_RX"   /*!< Label */
#define BOARD_INITPINS_BB_CAN0_RX_NAME                              "BB_CAN0_RX"   /*!< Identifier name */

/* FLEXCAN0_TX (coord H6), BB_CAN0_TX */
#define BOARD_INITPINS_BB_CAN0_TX_PERIPHERAL                       DMA__FLEXCAN0   /*!< Device name: DMA__FLEXCAN0 */
#define BOARD_INITPINS_BB_CAN0_TX_SIGNAL                              flexcan_tx   /*!< DMA__FLEXCAN0 signal: flexcan_tx */
#define BOARD_INITPINS_BB_CAN0_TX_PIN_NAME                           FLEXCAN0_TX   /*!< Pin name */
#define BOARD_INITPINS_BB_CAN0_TX_PIN_FUNCTION_ID               SC_P_FLEXCAN0_TX   /*!< Pin function id */
#define BOARD_INITPINS_BB_CAN0_TX_LABEL                    "BB_CAN0_TX"   /*!< Label */
#define BOARD_INITPINS_BB_CAN0_TX_NAME                              "BB_CAN0_TX"   /*!< Identifier name */

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
void BOARD_InitPins(sc_ipc_t ipc);                         /*!< Function assigned for the core: Cortex-M4F[cm4_1] */

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
