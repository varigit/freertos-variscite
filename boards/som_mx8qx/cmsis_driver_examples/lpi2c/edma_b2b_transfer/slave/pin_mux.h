/*
 * Copyright 2017-2019 NXP
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

/* SPI3_CS1 (coord K30), I2C3_SCL */
#define LPI2C_INITPINS_I2C3_SCL_PERIPHERAL                            ADMA__I2C3   /*!< Device name: ADMA__I2C3 */
#define LPI2C_INITPINS_I2C3_SCL_SIGNAL                                   i2c_scl   /*!< ADMA__I2C3 signal: i2c_scl */
#define LPI2C_INITPINS_I2C3_SCL_PIN_NAME                                SPI3_CS1   /*!< Pin name */
#define LPI2C_INITPINS_I2C3_SCL_PIN_FUNCTION_ID                    SC_P_SPI3_CS1   /*!< Pin function id */
#define LPI2C_INITPINS_I2C3_SCL_LABEL                                 "I2C3_SCL"   /*!< Label */
#define LPI2C_INITPINS_I2C3_SCL_NAME                                  "I2C3_SCL"   /*!< Identifier name */

/* MCLK_IN1 (coord M28), I2C3_SDA */
#define LPI2C_INITPINS_I2C3_SDA_PERIPHERAL                            ADMA__I2C3   /*!< Device name: ADMA__I2C3 */
#define LPI2C_INITPINS_I2C3_SDA_SIGNAL                                   i2c_sda   /*!< ADMA__I2C3 signal: i2c_sda */
#define LPI2C_INITPINS_I2C3_SDA_PIN_NAME                                MCLK_IN1   /*!< Pin name */
#define LPI2C_INITPINS_I2C3_SDA_PIN_FUNCTION_ID                    SC_P_MCLK_IN1   /*!< Pin function id */
#define LPI2C_INITPINS_I2C3_SDA_LABEL                                 "I2C3_SDA"   /*!< Label */
#define LPI2C_INITPINS_I2C3_SDA_NAME                                  "I2C3_SDA"   /*!< Identifier name */

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

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 * @param ipc scfw ipchandle.
 *
 */
void LPI2C_InitPins(sc_ipc_t ipc);                         /*!< Function assigned for the core: Cortex-M4F[m4] */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 * @param ipc scfw ipchandle.
 *
 */
void LPI2C_DeinitPins(sc_ipc_t ipc);                       /*!< Function assigned for the core: Cortex-M4F[m4] */

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
