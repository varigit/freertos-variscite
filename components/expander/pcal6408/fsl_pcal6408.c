/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_pcal6408.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef enum _pcal6408_reg_ops
{
    kPCAL6408_SetRegBits = 0,
    kPCAL6408_ClearRegBits,
    kPCAL6408_ToggleRegBits,
} pcal6408_reg_ops_t;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*! @brief Read port registers value. */
static status_t PCAL6408_ReadPort(pcal6408_handle_t *handle, uint8_t startReg, uint8_t *value)
{
    return handle->I2C_ReceiveFunc(handle->i2cBase, handle->i2cAddr, startReg, 1U, value, 1U, 0U);
}

/*! @brief Write port registers value. */
static status_t PCAL6408_WritePort(pcal6408_handle_t *handle, uint8_t startReg, uint8_t value)
{
    return handle->I2C_SendFunc(handle->i2cBase, handle->i2cAddr, startReg, 1U, &value, 1U, 0U);
}

/*! @brief Modify PCAL6408 port register bits. */
static status_t PCAL6408_ModifyPortRegBits(pcal6408_handle_t *handle,
                                           uint8_t startReg,
                                           uint8_t bits,
                                           pcal6408_reg_ops_t ops)
{
    uint8_t regValue;
    status_t status;

    status = PCAL6408_ReadPort(handle, startReg, &regValue);

    if (kStatus_Success == status)
    {
        if (kPCAL6408_SetRegBits == ops)
        {
            regValue |= bits;
        }
        else if (kPCAL6408_ClearRegBits == ops)
        {
            regValue &= ~bits;
        }
        else if (kPCAL6408_ToggleRegBits == ops)
        {
            regValue ^= bits;
        }
        else
        {
            /* Add for MISRA 15.7 */
        }

        status = PCAL6408_WritePort(handle, startReg, regValue);
    }

    return status;
}

/*
 * brief Initializes the PCAL6408 driver handle.
 *
 * param handle Pointer to the PCAL6408 handle.
 * param config Pointer to the PCAL6408 configuration structure.
 */
void PCAL6408_Init(pcal6408_handle_t *handle, const pcal6408_config_t *config)
{
    assert(NULL != handle);
    assert(NULL != config);

    handle->i2cBase         = config->i2cBase;
    handle->i2cAddr         = config->i2cAddr;
    handle->I2C_SendFunc    = config->I2C_SendFunc;
    handle->I2C_ReceiveFunc = config->I2C_ReceiveFunc;
}

/*
 * brief Set PCAL6408 pins direction.
 *
 * This function sets multiple pins direction, the pins to modify are passed in
 * as a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 to output:
 *
 * code
   PCAL6408_SetDirection(handle, (1<<2) | (1<<3), pkPCAL6408_Output);
   endcode
 *
 * param handle Pointer to the PCAL6408 handle.
 * param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * param dir Pin direction.
 * return Return ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCAL6408_SetDirection(pcal6408_handle_t *handle, uint8_t pins, pcal6408_dir_t dir)
{
    return PCAL6408_ModifyPortRegBits(handle, PCAL6408_CONFIG_PORT, pins,
                                      (kPCAL6408_Output != dir) ? kPCAL6408_SetRegBits : kPCAL6408_ClearRegBits);
}

/*
 * brief Set PCAL6408 pins output value to 1.
 *
 * This function changes multiple pins, the pins to modify are passed in as
 * a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 output value to 1.
 *
 * code
   PCAL6408_SetPins(handle, (1<<2) | (1<<3));
   endcode
 *
 * param handle Pointer to the PCAL6408 handle.
 * param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * return Return ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCAL6408_SetPins(pcal6408_handle_t *handle, uint8_t pins)
{
    return PCAL6408_ModifyPortRegBits(handle, PCAL6408_OUTPUT_PORT, pins, kPCAL6408_SetRegBits);
}

/*
 * brief Set PCAL6408 pins output value to 0.
 *
 * This function changes multiple pins, the pins to modify are passed in as
 * a bit OR'ed value.
 *
 * For example, the following code set pin2 and pin3 output value to 0.
 *
 * code
   PCAL6408_ClearPins(handle, (1<<2) | (1<<3));
   endcode
 *
 * param handle Pointer to the PCAL6408 handle.
 * param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * return Return ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCAL6408_ClearPins(pcal6408_handle_t *handle, uint8_t pins)
{
    return PCAL6408_ModifyPortRegBits(handle, PCAL6408_OUTPUT_PORT, pins, kPCAL6408_ClearRegBits);
}

/*
 * brief Toggle PCAL6408 pins output value.
 *
 * This function changes multiple pins, the pins to modify are passed in as
 * a bit OR'ed value.
 *
 * For example, the following code toggle pin2 and pin3 output value.
 *
 * code
   PCAL6408_TogglePins(handle, (1<<2) | (1<<3));
   endcode
 *
 * param handle Pointer to the PCAL6408 handle.
 * param pins The pins to change, for example: (1<<2) | (1<<3) means pin 2 and pin 3.
 * return Return ref kStatus_Success if successed, otherwise returns error code.
 */
status_t PCAL6408_TogglePins(pcal6408_handle_t *handle, uint8_t pins)
{
    return PCAL6408_ModifyPortRegBits(handle, PCAL6408_OUTPUT_PORT, pins, kPCAL6408_ToggleRegBits);
}
