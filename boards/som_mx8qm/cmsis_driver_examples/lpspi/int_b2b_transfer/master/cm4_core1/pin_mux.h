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

/* SPI0_CS0 (number BC1), BB_SPI0_CS0 */
#define LPSPI0_INITPINSEX_BB_SPI0_CS0_PERIPHERAL                       DMA__SPI0   /*!< Device name: DMA__SPI0 */
#define LPSPI0_INITPINSEX_BB_SPI0_CS0_SIGNAL                              spi_cs   /*!< DMA__SPI0 signal: spi_cs */
#define LPSPI0_INITPINSEX_BB_SPI0_CS0_CHANNEL                                  0   /*!< DMA__SPI0 spi_cs channel: 0 */
#define LPSPI0_INITPINSEX_BB_SPI0_CS0_PIN_NAME                          SPI0_CS0   /*!< Pin name */
#define LPSPI0_INITPINSEX_BB_SPI0_CS0_PIN_FUNCTION_ID              SC_P_SPI0_CS0   /*!< Pin function id */
#define LPSPI0_INITPINSEX_BB_SPI0_CS0_LABEL                        "BB_SPI0_CS0"   /*!< Label */
#define LPSPI0_INITPINSEX_BB_SPI0_CS0_NAME                         "BB_SPI0_CS0"   /*!< Identifier name */

/* SPI0_SCK (number BB4), BB_SPI0_SCLK */
#define LPSPI0_INITPINSEX_BB_SPI0_SCLK_PERIPHERAL                      DMA__SPI0   /*!< Device name: DMA__SPI0 */
#define LPSPI0_INITPINSEX_BB_SPI0_SCLK_SIGNAL                            spi_sck   /*!< DMA__SPI0 signal: spi_sck */
#define LPSPI0_INITPINSEX_BB_SPI0_SCLK_PIN_NAME                         SPI0_SCK   /*!< Pin name */
#define LPSPI0_INITPINSEX_BB_SPI0_SCLK_PIN_FUNCTION_ID             SC_P_SPI0_SCK   /*!< Pin function id */
#define LPSPI0_INITPINSEX_BB_SPI0_SCLK_LABEL                      "BB_SPI0_SCLK"   /*!< Label */
#define LPSPI0_INITPINSEX_BB_SPI0_SCLK_NAME                       "BB_SPI0_SCLK"   /*!< Identifier name */

/* SPI0_SDI (number BA5), BB_SPI0_MISO */
#define LPSPI0_INITPINSEX_BB_SPI0_MISO_PERIPHERAL                      DMA__SPI0   /*!< Device name: DMA__SPI0 */
#define LPSPI0_INITPINSEX_BB_SPI0_MISO_SIGNAL                            spi_sdi   /*!< DMA__SPI0 signal: spi_sdi */
#define LPSPI0_INITPINSEX_BB_SPI0_MISO_PIN_NAME                         SPI0_SDI   /*!< Pin name */
#define LPSPI0_INITPINSEX_BB_SPI0_MISO_PIN_FUNCTION_ID             SC_P_SPI0_SDI   /*!< Pin function id */
#define LPSPI0_INITPINSEX_BB_SPI0_MISO_LABEL                      "BB_SPI0_MISO"   /*!< Label */
#define LPSPI0_INITPINSEX_BB_SPI0_MISO_NAME                       "BB_SPI0_MISO"   /*!< Identifier name */

/* SPI0_SDO (number AY6), BB_SPI0_MOSI */
#define LPSPI0_INITPINSEX_BB_SPI0_MOSI_PERIPHERAL                      DMA__SPI0   /*!< Device name: DMA__SPI0 */
#define LPSPI0_INITPINSEX_BB_SPI0_MOSI_SIGNAL                            spi_sdo   /*!< DMA__SPI0 signal: spi_sdo */
#define LPSPI0_INITPINSEX_BB_SPI0_MOSI_PIN_NAME                         SPI0_SDO   /*!< Pin name */
#define LPSPI0_INITPINSEX_BB_SPI0_MOSI_PIN_FUNCTION_ID             SC_P_SPI0_SDO   /*!< Pin function id */
#define LPSPI0_INITPINSEX_BB_SPI0_MOSI_LABEL                      "BB_SPI0_MOSI"   /*!< Label */
#define LPSPI0_INITPINSEX_BB_SPI0_MOSI_NAME                       "BB_SPI0_MOSI"   /*!< Identifier name */

/* SPI0_CS0 (number BC1), BB_SPI0_CS0 */
#define LPSPI0_DEINITPINSEX_BB_SPI0_CS0_GPIO                         LSIO__GPIO3   /*!< GPIO device name: LSIO__GPIO3 */
#define LPSPI0_DEINITPINSEX_BB_SPI0_CS0_GPIO_PIN                              5U   /*!< LSIO__GPIO3 pin index: 5 */
#define LPSPI0_DEINITPINSEX_BB_SPI0_CS0_PIN_NAME                        SPI0_CS0   /*!< Pin name */
#define LPSPI0_DEINITPINSEX_BB_SPI0_CS0_PIN_FUNCTION_ID            SC_P_SPI0_CS0   /*!< Pin function id */
#define LPSPI0_DEINITPINSEX_BB_SPI0_CS0_LABEL                      "BB_SPI0_CS0"   /*!< Label */
#define LPSPI0_DEINITPINSEX_BB_SPI0_CS0_NAME                       "BB_SPI0_CS0"   /*!< Identifier name */

/* SPI0_SCK (number BB4), BB_SPI0_SCLK */
#define LPSPI0_DEINITPINSEX_BB_SPI0_SCLK_GPIO                        LSIO__GPIO3   /*!< GPIO device name: LSIO__GPIO3 */
#define LPSPI0_DEINITPINSEX_BB_SPI0_SCLK_GPIO_PIN                             2U   /*!< LSIO__GPIO3 pin index: 2 */
#define LPSPI0_DEINITPINSEX_BB_SPI0_SCLK_PIN_NAME                       SPI0_SCK   /*!< Pin name */
#define LPSPI0_DEINITPINSEX_BB_SPI0_SCLK_PIN_FUNCTION_ID           SC_P_SPI0_SCK   /*!< Pin function id */
#define LPSPI0_DEINITPINSEX_BB_SPI0_SCLK_LABEL                    "BB_SPI0_SCLK"   /*!< Label */
#define LPSPI0_DEINITPINSEX_BB_SPI0_SCLK_NAME                     "BB_SPI0_SCLK"   /*!< Identifier name */

/* SPI0_SDI (number BA5), BB_SPI0_MISO */
#define LPSPI0_DEINITPINSEX_BB_SPI0_MISO_GPIO                        LSIO__GPIO3   /*!< GPIO device name: LSIO__GPIO3 */
#define LPSPI0_DEINITPINSEX_BB_SPI0_MISO_GPIO_PIN                             4U   /*!< LSIO__GPIO3 pin index: 4 */
#define LPSPI0_DEINITPINSEX_BB_SPI0_MISO_PIN_NAME                       SPI0_SDI   /*!< Pin name */
#define LPSPI0_DEINITPINSEX_BB_SPI0_MISO_PIN_FUNCTION_ID           SC_P_SPI0_SDI   /*!< Pin function id */
#define LPSPI0_DEINITPINSEX_BB_SPI0_MISO_LABEL                    "BB_SPI0_MISO"   /*!< Label */
#define LPSPI0_DEINITPINSEX_BB_SPI0_MISO_NAME                     "BB_SPI0_MISO"   /*!< Identifier name */

/* SPI0_SDO (number AY6), BB_SPI0_MOSI */
#define LPSPI0_DEINITPINSEX_BB_SPI0_MOSI_GPIO                        LSIO__GPIO3   /*!< GPIO device name: LSIO__GPIO3 */
#define LPSPI0_DEINITPINSEX_BB_SPI0_MOSI_GPIO_PIN                             3U   /*!< LSIO__GPIO3 pin index: 3 */
#define LPSPI0_DEINITPINSEX_BB_SPI0_MOSI_PIN_NAME                       SPI0_SDO   /*!< Pin name */
#define LPSPI0_DEINITPINSEX_BB_SPI0_MOSI_PIN_FUNCTION_ID           SC_P_SPI0_SDO   /*!< Pin function id */
#define LPSPI0_DEINITPINSEX_BB_SPI0_MOSI_LABEL                    "BB_SPI0_MOSI"   /*!< Label */
#define LPSPI0_DEINITPINSEX_BB_SPI0_MOSI_NAME                     "BB_SPI0_MOSI"   /*!< Identifier name */

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

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 * @param ipc scfw ipchandle.
 *
 */
void LPSPI0_InitPinsEx(sc_ipc_t ipc);                      /*!< Function assigned for the core: Cortex-M4F[cm4_1] */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 * @param ipc scfw ipchandle.
 *
 */
void LPSPI0_DeinitPinsEx(sc_ipc_t ipc);                    /*!< Function assigned for the core: Cortex-M4F[cm4_1] */

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
