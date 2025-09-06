/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_PCAL6408_H_
#define _FSL_PCAL6408_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fsl_common.h"

/*
 * Change log:
 *
 *   1.0.0
 *     - Initial version
 */

/*!
 * @addtogroup pcal6408
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Define the Register Memory Map of PCAL6408. */
#define PCAL6408_OUTPUT_PORT (0x01U)
#define PCAL6408_CONFIG_PORT (0x03U)

/*! @brief PCAL6408 IO direction. */
typedef enum _pcal6408_dir
{
    kPCAL6408_Input = 0U, /*!< Set pin as input. */
    kPCAL6408_Output,     /*!< Set pin as output. */
} pcal6408_dir_t;

/*! @brief PCAL6408 I2C receive function. */
typedef status_t (*pcal6408_i2c_receive_func_t)(void *base,
                                                uint8_t deviceAddress,
                                                uint32_t subAddress,
                                                uint8_t subaddressSize,
                                                uint8_t *rxBuff,
                                                uint8_t rxBuffSize,
                                                uint32_t flags);

/*! @brief PCAL6408 I2C send function. */
typedef status_t (*pcal6408_i2c_send_func_t)(void *base,
                                             uint8_t deviceAddress,
                                             uint32_t subAddress,
                                             uint8_t subaddressSize,
                                             const uint8_t *txBuff,
                                             uint8_t txBuffSize,
                                             uint32_t flags);

/*! @brief PCAL6408 configure structure.*/
typedef struct _pcal6408_config
{
    void *i2cBase;                               /*!< I2C instance base address. */
    uint8_t i2cAddr;                             /*!< I2C address. */
    pcal6408_i2c_send_func_t I2C_SendFunc;       /*!< Function to send I2C data. */
    pcal6408_i2c_receive_func_t I2C_ReceiveFunc; /*!< Function to receive I2C data. */
} pcal6408_config_t;

/*! @brief PCAL6408 driver handle. */
typedef struct _pcal6408_handle
{
    void *i2cBase;                               /*!< I2C instance base address. */
    uint8_t i2cAddr;                             /*!< I2C address. */
    pcal6408_i2c_send_func_t I2C_SendFunc;       /*!< Function to send I2C data. */
    pcal6408_i2c_receive_func_t I2C_ReceiveFunc; /*!< Function to receive I2C data. */
} pcal6408_handle_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and Control function
 * @{
 */

/*!
 * @brief Initializes the PCAL6408 driver handle.
 *
 * @param handle Pointer to the PCAL6408 handle.
 * @param config Pointer to the PCAL6408 configuration structure.
 */
void PCAL6408_Init(pcal6408_handle_t *handle, const pcal6408_config_t *config);

/*!
 * @brief Set PCAL6408 pins direction.
 *
 * This function sets multiple pins direction, the pins to modify are passed in
 * as a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 to output:
 *
 * @code
   PCAL6408_SetDirection(handle, (1<<2) | (1<<3), pkPCAL6408_Output);
   @endcode
 *
 * @param handle Pointer to the PCAL6408 handle.
 * @param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * @param dir Pin direction.
 * @return Return @ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCAL6408_SetDirection(pcal6408_handle_t *handle, uint8_t pins, pcal6408_dir_t dir);

/*!
 * @brief Set PCAL6408 pins output value to 1.
 *
 * This function changes multiple pins, the pins to modify are passed in as
 * a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 output value to 1.
 *
 * @code
   PCAL6408_SetPins(handle, (1<<2) | (1<<3));
   @endcode
 *
 * @param handle Pointer to the PCAL6408 handle.
 * @param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * @return Return @ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCAL6408_SetPins(pcal6408_handle_t *handle, uint8_t pins);

/*!
 * @brief Set PCAL6408 pins output value to 0.
 *
 * This function changes multiple pins, the pins to modify are passed in as
 * a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 output value to 0.
 *
 * @code
   PCAL6408_ClearPins(handle, (1<<2) | (1<<3));
   @endcode
 *
 * @param handle Pointer to the PCAL6408 handle.
 * @param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * @return Return @ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCAL6408_ClearPins(pcal6408_handle_t *handle, uint8_t pins);

/*!
 * @brief Toggle PCAL6408 pins output value.
 *
 * This function changes multiple pins, the pins to modify are passed in as
 * a bit OR'ed value.
 *
 * For example, the following code toggle pin2 and pin3 output value.
 *
 * @code
   PCAL6408_ClearPins(handle, (1<<2) | (1<<3));
   @endcode
 *
 * @param handle Pointer to the PCAL6408 handle.
 * @param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * @return Return @ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCAL6408_TogglePins(pcal6408_handle_t *handle, uint8_t pins);

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_PCAL6408_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
