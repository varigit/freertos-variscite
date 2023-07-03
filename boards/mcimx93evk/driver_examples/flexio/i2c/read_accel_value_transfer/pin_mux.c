/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
}

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)
{
    IOMUXC_SetPinMux(IOMUXC_PAD_UART2_RXD__LPUART2_RX, 0);
    IOMUXC_SetPinConfig(IOMUXC_PAD_UART2_RXD__LPUART2_RX, IOMUXC_PAD_PD(1));

    IOMUXC_SetPinMux(IOMUXC_PAD_UART2_TXD__LPUART2_TX, 0);
    IOMUXC_SetPinConfig(IOMUXC_PAD_UART2_TXD__LPUART2_TX, IOMUXC_PAD_DSE(0xf));

    IOMUXC_SetPinMux(IOMUXC_PAD_GPIO_IO02__FLEXIO1_FLEXIO02, 1);
    IOMUXC_SetPinConfig(IOMUXC_PAD_GPIO_IO02__FLEXIO1_FLEXIO02, IOMUXC_PAD_OD(1) | IOMUXC_PAD_FSEL1(2) | IOMUXC_PAD_DSE(0xf));
    IOMUXC_SetPinMux(IOMUXC_PAD_GPIO_IO03__FLEXIO1_FLEXIO03, 1);
    IOMUXC_SetPinConfig(IOMUXC_PAD_GPIO_IO03__FLEXIO1_FLEXIO03, IOMUXC_PAD_OD(1) | IOMUXC_PAD_FSEL1(2) | IOMUXC_PAD_DSE(0xf));
}

void BOARD_I2C_ConfigurePins(void) 
{
    IOMUXC_SetPinMux(IOMUXC_PAD_I2C1_SDA__LPI2C1_SDA, 1);
    IOMUXC_SetPinConfig(IOMUXC_PAD_I2C1_SDA__LPI2C1_SDA, IOMUXC_PAD_OD(1) | IOMUXC_PAD_FSEL1(2) | IOMUXC_PAD_DSE(0xf));

    IOMUXC_SetPinMux(IOMUXC_PAD_I2C1_SCL__LPI2C1_SCL, 1);
    IOMUXC_SetPinConfig(IOMUXC_PAD_I2C1_SCL__LPI2C1_SCL, IOMUXC_PAD_OD(1) | IOMUXC_PAD_FSEL1(2) | IOMUXC_PAD_DSE(0xf));
}