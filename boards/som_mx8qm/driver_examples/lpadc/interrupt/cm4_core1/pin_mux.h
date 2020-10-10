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

/* ADC_IN6 (number AL9), ADC_IN6 */
#define BOARD_ADC_IN_PERIPHERAL                                        DMA__ADC1   /*!< Device name: DMA__ADC */
#define BOARD_ADC_IN_SIGNAL                                               adc_in   /*!< DMA__ADC1 signal: adc_in */
#define BOARD_ADC_IN_CHANNEL                                                   2   /*!< DMA__ADC1 adc_in channel: 2 */
#define BOARD_ADC_IN_PIN_NAME                                            ADC_IN6   /*!< Pin name */
#define BOARD_ADC_IN_PIN_FUNCTION_ID                                SC_P_ADC_IN6   /*!< Pin function id */
#define BOARD_ADC_IN_LABEL                                             "ADC_IN6"   /*!< Label */
#define BOARD_ADC_IN_NAME                                              "ADC_IN6"   /*!< Identifier name */

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
