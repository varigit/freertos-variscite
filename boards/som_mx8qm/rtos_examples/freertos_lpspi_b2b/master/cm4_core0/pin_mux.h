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

#ifdef SPEAR_MX8

/* M40_I2C0_SCL (number AM44), M40_UART0_RX */
#define BOARD_DEBUG_UART_RX_PERIPHERAL                                M40__UART0   /*!< Device name: M40__UART0 */
#define BOARD_DEBUG_UART_RX_SIGNAL                                       uart_rx   /*!< M40__UART0 signal: uart_rx */
#define BOARD_DEBUG_UART_RX_PIN_NAME                                M40_I2C0_SCL   /*!< Pin name */
#define BOARD_DEBUG_UART_RX_PIN_FUNCTION_ID                    SC_P_M40_I2C0_SCL   /*!< Pin function id */
#define BOARD_DEBUG_UART_RX_PIN_MUX                                           1U   /*!< mux settings */
#define BOARD_DEBUG_UART_RX_LABEL                                 "M40_UART0_RX"   /*!< Label */
#define BOARD_DEBUG_UART_RX_NAME                                  "M40_UART0_RX"   /*!< Identifier name */

/* M40_I2C0_SDA (number AU51), M40_UART0_TX */
#define BOARD_DEBUG_UART_TX_PERIPHERAL                                M40__UART0   /*!< Device name: M40__UART0 */
#define BOARD_DEBUG_UART_TX_SIGNAL                                       uart_tx   /*!< M40__UART0 signal: uart_tx */
#define BOARD_DEBUG_UART_TX_PIN_NAME                                M40_I2C0_SDA   /*!< Pin name */
#define BOARD_DEBUG_UART_TX_PIN_FUNCTION_ID                    SC_P_M40_I2C0_SDA   /*!< Pin function id */
#define BOARD_DEBUG_UART_TX_PIN_MUX                                           1U   /*!< mux settings */
#define BOARD_DEBUG_UART_TX_LABEL                                 "M40_UART0_TX"   /*!< Label */
#define BOARD_DEBUG_UART_TX_NAME                                  "M40_UART0_TX"   /*!< Identifier name */

#else /* defines for VAR-SOM-MX8 */

/* M40_GPIO0_00 (number AR47), DMA_UART4_RX */
#define BOARD_DEBUG_UART_RX_PERIPHERAL                                DMA__UART4   /*!< Device name: DMA__UART4 */
#define BOARD_DEBUG_UART_RX_SIGNAL                                       uart_rx   /*!< DMA__UART4 signal: uart_rx */
#define BOARD_DEBUG_UART_RX_PIN_NAME                                M40_GPIO0_00   /*!< Pin name */
#define BOARD_DEBUG_UART_RX_PIN_FUNCTION_ID                    SC_P_M40_GPIO0_00   /*!< Pin function id */
#define BOARD_DEBUG_UART_RX_PIN_MUX                                           2U   /*!< mux settings */
#define BOARD_DEBUG_UART_RX_LABEL                                 "DMA_UART4_RX"   /*!< Label */
#define BOARD_DEBUG_UART_RX_NAME                                  "DMA_UART4_RX"   /*!< Identifier name */

/* M40_GPIO0_01 (number AU53), DMA_UART4_TX */
#define BOARD_DEBUG_UART_TX_PERIPHERAL                                DMA__UART4   /*!< Device name: DMA__UART4 */
#define BOARD_DEBUG_UART_TX_SIGNAL                                       uart_tx   /*!< DMA__UART4 signal: uart_tx */
#define BOARD_DEBUG_UART_TX_PIN_NAME                                M40_GPIO0_01   /*!< Pin name */
#define BOARD_DEBUG_UART_TX_PIN_FUNCTION_ID                    SC_P_M40_GPIO0_01   /*!< Pin function id */
#define BOARD_DEBUG_UART_TX_PIN_MUX                                           2U   /*!< mux settings */
#define BOARD_DEBUG_UART_TX_LABEL                                 "DMA_UART4_TX"   /*!< Label */
#define BOARD_DEBUG_UART_TX_NAME                                  "DMA_UART4_TX"   /*!< Identifier name */

#endif /* SPEAR_MX8 */

/* SPI0_CS0 (number BC1), BB_SPI0_CS0 */
#define BOARD_INITPINS_BB_SPI0_CS0_PERIPHERAL                          DMA__SPI0   /*!< Device name: DMA__SPI0 */
#define BOARD_INITPINS_BB_SPI0_CS0_SIGNAL                                 spi_cs   /*!< DMA__SPI0 signal: spi_cs */
#define BOARD_INITPINS_BB_SPI0_CS0_CHANNEL                                     0   /*!< DMA__SPI0 spi_cs channel: 0 */
#define BOARD_INITPINS_BB_SPI0_CS0_PIN_NAME                             SPI0_CS0   /*!< Pin name */
#define BOARD_INITPINS_BB_SPI0_CS0_PIN_FUNCTION_ID                 SC_P_SPI0_CS0   /*!< Pin function id */
#define BOARD_INITPINS_BB_SPI0_CS0_LABEL                           "BB_SPI0_CS0"   /*!< Label */
#define BOARD_INITPINS_BB_SPI0_CS0_NAME                            "BB_SPI0_CS0"   /*!< Identifier name */

/* SPI0_SCK (number BB4), BB_SPI0_SCLK */
#define BOARD_INITPINS_BB_SPI0_SCLK_PERIPHERAL                         DMA__SPI0   /*!< Device name: DMA__SPI0 */
#define BOARD_INITPINS_BB_SPI0_SCLK_SIGNAL                               spi_sck   /*!< DMA__SPI0 signal: spi_sck */
#define BOARD_INITPINS_BB_SPI0_SCLK_PIN_NAME                            SPI0_SCK   /*!< Pin name */
#define BOARD_INITPINS_BB_SPI0_SCLK_PIN_FUNCTION_ID                SC_P_SPI0_SCK   /*!< Pin function id */
#define BOARD_INITPINS_BB_SPI0_SCLK_LABEL                         "BB_SPI0_SCLK"   /*!< Label */
#define BOARD_INITPINS_BB_SPI0_SCLK_NAME                          "BB_SPI0_SCLK"   /*!< Identifier name */

/* SPI0_SDI (number BA5), BB_SPI0_MISO */
#define BOARD_INITPINS_BB_SPI0_MISO_PERIPHERAL                         DMA__SPI0   /*!< Device name: DMA__SPI0 */
#define BOARD_INITPINS_BB_SPI0_MISO_SIGNAL                               spi_sdi   /*!< DMA__SPI0 signal: spi_sdi */
#define BOARD_INITPINS_BB_SPI0_MISO_PIN_NAME                            SPI0_SDI   /*!< Pin name */
#define BOARD_INITPINS_BB_SPI0_MISO_PIN_FUNCTION_ID                SC_P_SPI0_SDI   /*!< Pin function id */
#define BOARD_INITPINS_BB_SPI0_MISO_LABEL                         "BB_SPI0_MISO"   /*!< Label */
#define BOARD_INITPINS_BB_SPI0_MISO_NAME                          "BB_SPI0_MISO"   /*!< Identifier name */

/* SPI0_SDO (number AY6), BB_SPI0_MOSI */
#define BOARD_INITPINS_BB_SPI0_MOSI_PERIPHERAL                         DMA__SPI0   /*!< Device name: DMA__SPI0 */
#define BOARD_INITPINS_BB_SPI0_MOSI_SIGNAL                               spi_sdo   /*!< DMA__SPI0 signal: spi_sdo */
#define BOARD_INITPINS_BB_SPI0_MOSI_PIN_NAME                            SPI0_SDO   /*!< Pin name */
#define BOARD_INITPINS_BB_SPI0_MOSI_PIN_FUNCTION_ID                SC_P_SPI0_SDO   /*!< Pin function id */
#define BOARD_INITPINS_BB_SPI0_MOSI_LABEL                         "BB_SPI0_MOSI"   /*!< Label */
#define BOARD_INITPINS_BB_SPI0_MOSI_NAME                          "BB_SPI0_MOSI"   /*!< Identifier name */

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
void BOARD_InitPins(sc_ipc_t ipc);                         /*!< Function assigned for the core: Cortex-M4F[cm4_0] */

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
