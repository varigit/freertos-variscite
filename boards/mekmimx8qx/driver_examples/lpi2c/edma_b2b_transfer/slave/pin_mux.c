/*
 * Copyright 2017-2018 NXP
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
product: Pins v4.1
processor: MIMX8QX6xxxFZ
package_id: MIMX8QX6AVLFZ
mcu_data: ksdk2_0
processor_version: 0.0.0
board: MIMX8QX-MEK-REV-B
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

#include "pin_mux.h"
#include "fsl_common.h"
#include "main/imx8qx_pads.h"
#include "svc/pad/pad_api.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
}

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'false', coreID: m4}
- pin_list:
  - {pin_num: V32, peripheral: M40__UART0, signal: uart_rx, pin_signal: ADC_IN2, sw_config: sw_config_0}
  - {pin_num: V30, peripheral: M40__UART0, signal: uart_tx, pin_signal: ADC_IN3, sw_config: sw_config_0}
  - {pin_num: H14, peripheral: ADMA__I2C1, signal: i2c_scl, pin_signal: USB_SS3_TC1, sw_config: sw_config_2}
  - {pin_num: C15, peripheral: ADMA__I2C1, signal: i2c_sda, pin_signal: USB_SS3_TC3, sw_config: sw_config_2}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(sc_ipc_t ipc)                          /*!< Function assigned for the core: Cortex-M4F[m4] */
{
  sc_err_t err = SC_ERR_NONE;

  err = sc_pad_set_all(ipc, BOARD_INITPINS_FTDI_M40_UART0_RX_PIN_FUNCTION_ID, 1U, SC_PAD_CONFIG_NORMAL, SC_PAD_ISO_OFF, 0x0 ,SC_PAD_WAKEUP_OFF);/* IOMUXD_ADC_IN2 register modification value */
  if (SC_ERR_NONE != err)
  {
      assert(false);
  }
  err = sc_pad_set_all(ipc, BOARD_INITPINS_FTDI_M40_UART0_TX_PIN_FUNCTION_ID, 1U, SC_PAD_CONFIG_NORMAL, SC_PAD_ISO_OFF, 0x0 ,SC_PAD_WAKEUP_OFF);/* IOMUXD_ADC_IN3 register modification value */
  if (SC_ERR_NONE != err)
  {
      assert(false);
  }
  err = sc_pad_set_all(ipc, BOARD_INITPINS_I2C1_SCL_PIN_FUNCTION_ID, 0U, SC_PAD_CONFIG_OD_IN, SC_PAD_ISO_OFF, 0x0 ,SC_PAD_WAKEUP_OFF);/* IOMUXD_USB_SS3_TC1 register modification value */
  if (SC_ERR_NONE != err)
  {
      assert(false);
  }
  err = sc_pad_set_all(ipc, BOARD_INITPINS_I2C1_SDA_PIN_FUNCTION_ID, 0U, SC_PAD_CONFIG_OD_IN, SC_PAD_ISO_OFF, 0x0 ,SC_PAD_WAKEUP_OFF);/* IOMUXD_USB_SS3_TC3 register modification value */
  if (SC_ERR_NONE != err)
  {
      assert(false);
  }
}

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
