/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v12.0
processor: MIMX9352xxxxM
package_id: MIMX9352DVVXM
mcu_data: ksdk2_0
processor_version: 0.12.3
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
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

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: cm33}
- pin_list:
  - {pin_num: M20, peripheral: LPUART7, signal: lpuart_tx, pin_signal: GPIO_IO08, HYS: DISABLED, PD: DISABLED, FSEL1: SlOW_SLEW_RATE}
  - {pin_num: M21, peripheral: LPUART7, signal: lpuart_rx, pin_signal: GPIO_IO09, HYS: DISABLED, FSEL1: SlOW_SLEW_RATE, DSE: NO_DRIVE}
  - {pin_num: J17, peripheral: CAN1, signal: can_rx, pin_signal: PDM_BIT_STREAM0, HYS: DISABLED}
  - {pin_num: G17, peripheral: CAN1, signal: can_tx, pin_signal: PDM_CLK, HYS: DISABLED}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void) {                                /*!< Function assigned for the core: undefined[cm33] */
    IOMUXC_SetPinMux(IOMUXC_PAD_PDM_CLK__CAN1_TX, 0U);
    IOMUXC_SetPinMux(IOMUXC_PAD_PDM_BIT_STREAM0__CAN1_RX, 0U);
    IOMUXC_SetPinMux(IOMUXC_PAD_GPIO_IO09__LPUART7_RX, 0U);
    IOMUXC_SetPinMux(IOMUXC_PAD_GPIO_IO08__LPUART7_TX, 0U);

    IOMUXC_SetPinConfig(IOMUXC_PAD_PDM_CLK__CAN1_TX, 
                        IOMUXC_PAD_DSE(15U) |
                        IOMUXC_PAD_FSEL1(2U) |
                        IOMUXC_PAD_PD_MASK);
    IOMUXC_SetPinConfig(IOMUXC_PAD_PDM_BIT_STREAM0__CAN1_RX, 
                        IOMUXC_PAD_DSE(15U) |
                        IOMUXC_PAD_FSEL1(2U) |
                        IOMUXC_PAD_PD_MASK);
    IOMUXC_SetPinConfig(IOMUXC_PAD_GPIO_IO09__LPUART7_RX, 
                        IOMUXC_PAD_PD_MASK);
    IOMUXC_SetPinConfig(IOMUXC_PAD_GPIO_IO08__LPUART7_TX, 
                        IOMUXC_PAD_DSE(15U));
}

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
