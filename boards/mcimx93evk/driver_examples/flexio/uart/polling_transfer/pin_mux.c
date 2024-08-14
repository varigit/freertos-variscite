/*
 * Copyright 2023 NXP
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
product: Pins v13.0
processor: MIMX9352xxxxM
package_id: MIMX9352DVVXM
mcu_data: ksdk2_0
processor_version: 0.13.6
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
  - {pin_num: K20, peripheral: FLEXIO1, signal: 'flexio_flexio, 02', pin_signal: GPIO_IO02}
  - {pin_num: K21, peripheral: FLEXIO1, signal: 'flexio_flexio, 03', pin_signal: GPIO_IO03}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void) {                                /*!< Function assigned for the core: Cortex-M33[cm33] */
    IOMUXC_SetPinMux(IOMUXC_PAD_GPIO_IO02__FLEXIO1_FLEXIO02, 0U);
    IOMUXC_SetPinMux(IOMUXC_PAD_GPIO_IO03__FLEXIO1_FLEXIO03, 0U);
}

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/