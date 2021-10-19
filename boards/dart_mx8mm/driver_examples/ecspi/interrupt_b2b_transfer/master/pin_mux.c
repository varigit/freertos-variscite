/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v4.1
processor: MIMX8MM6xxxLZ
package_id: MIMX8MM6DVTLZ
mcu_data: ksdk2_0
processor_version: 0.0.0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

#include "fsl_common.h"
#include "fsl_iomuxc.h"
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

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'false', coreID: cm4}
- pin_list:
  - {pin_num: E18, peripheral: UART3, signal: uart_rx, pin_signal: UART3_RXD, PE: Disabled, PUE: Disabled, DSE: X6_0}
  - {pin_num: D18, peripheral: UART3, signal: uart_tx, pin_signal: UART3_TXD, PE: Disabled, PUE: Disabled, DSE: X6_0}
  - {pin_num: D6, peripheral: ECSPI1, signal: ecspi_sclk, pin_signal: ECSPI1_SCLK, PE: Enabled, PUE: Disabled, HYS: Enabled, SION: DISABLED, FSEL: SLOW0, DSE: X6_0}
  - {pin_num: B6, peripheral: ECSPI1, signal: 'ecspi_ss, 0', pin_signal: ECSPI1_SS0, PE: Enabled, PUE: Enabled, HYS: Enabled, SION: DISABLED, FSEL: SLOW0, DSE: X6_0}
  - {pin_num: B7, peripheral: ECSPI1, signal: ecspi_mosi, pin_signal: ECSPI1_MOSI, PE: Disabled, HYS: Enabled, SION: DISABLED, FSEL: SLOW0, DSE: X6_0}
  - {pin_num: A7, peripheral: ECSPI1, signal: ecspi_miso, pin_signal: ECSPI1_MISO, PE: Disabled, HYS: Enabled, SION: DISABLED, FSEL: SLOW0, DSE: X6_0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void) {                                /*!< Function assigned for the core: Cortex-M4[m4] */
    IOMUXC_SetPinMux(IOMUXC_ECSPI1_MISO_ECSPI1_MISO, 0U);
    IOMUXC_SetPinConfig(IOMUXC_ECSPI1_MISO_ECSPI1_MISO, 
                        IOMUXC_SW_PAD_CTL_PAD_DSE(6U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);
    IOMUXC_SetPinMux(IOMUXC_ECSPI1_MOSI_ECSPI1_MOSI, 0U);
    IOMUXC_SetPinConfig(IOMUXC_ECSPI1_MOSI_ECSPI1_MOSI, 
                        IOMUXC_SW_PAD_CTL_PAD_DSE(6U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK);
    IOMUXC_SetPinMux(IOMUXC_ECSPI1_SCLK_ECSPI1_SCLK, 0U);
    IOMUXC_SetPinConfig(IOMUXC_ECSPI1_SCLK_ECSPI1_SCLK, 
                        IOMUXC_SW_PAD_CTL_PAD_DSE(6U) |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PE_MASK);
    IOMUXC_SetPinMux(IOMUXC_ECSPI1_SS0_ECSPI1_SS0, 0U);
    IOMUXC_SetPinConfig(IOMUXC_ECSPI1_SS0_ECSPI1_SS0, 
                        IOMUXC_SW_PAD_CTL_PAD_DSE(6U) |
                        IOMUXC_SW_PAD_CTL_PAD_PUE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_PE_MASK);
    IOMUXC_SetPinMux(IOMUXC_UART3_RXD_UART3_RX, 0U);
    IOMUXC_SetPinConfig(IOMUXC_UART3_RXD_UART3_RX, 
                        IOMUXC_SW_PAD_CTL_PAD_DSE(6U) |
                        IOMUXC_SW_PAD_CTL_PAD_FSEL(2U));
    IOMUXC_SetPinMux(IOMUXC_UART3_TXD_UART3_TX, 0U);
    IOMUXC_SetPinConfig(IOMUXC_UART3_TXD_UART3_TX, 
                        IOMUXC_SW_PAD_CTL_PAD_DSE(6U) |
                        IOMUXC_SW_PAD_CTL_PAD_FSEL(2U));
}

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
