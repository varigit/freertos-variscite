/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdint.h>
#include <stdbool.h>
#include "board.h"
#include "i2c_xfer.h"
#include "mpl3115.h"

/*FUNCTION****************************************************************
*
* Function Name    : MPL3115_Init
* Returned Value   : result
* Comments         : Initialize MPL3115 pressure and temperature sensor.
*
*END*********************************************************************/
bool MPL3115_Init(mpl_handle_t *handle, const mpl3115_init_t *mpl3115_config)
{
    uint8_t regVal;
    /* Place the MPL3115 in Standby */
    if (!MPL3115_WriteReg(handle, MPL3115_CTRL_REG1, 0x00))
        return false;

    // Set CTRL_REG1 according to mpl3115 init struct and switch it
    // to active mode.
    regVal = ((uint8_t)mpl3115_config->outputFormat    |
              (uint8_t)mpl3115_config->outputMode      |
              (uint8_t)mpl3115_config->oversampleRatio);

    if (!MPL3115_WriteReg(handle, MPL3115_CTRL_REG1, regVal))
        return false;

    return true;
}

/*FUNCTION****************************************************************
*
* Function Name    : MPL3115_Deinit
* Returned Value   : result
* Comments         : Deinit the mpl3115 sensor.
*
*END*********************************************************************/
bool MPL3115_Deinit(mpl_handle_t *handle)
{
    // Switch mpl3115 to STANDBY mode.
    if (!MPL3115_WriteReg(handle, MPL3115_CTRL_REG1, 0x00))
        return false;

    // Reset all Register content.
    if (!MPL3115_WriteReg(handle, MPL3115_CTRL_REG1, 0x04))
        return false;

    return true;
}

/*FUNCTION****************************************************************
*
* Function Name    : MPL3115_Enable
* Returned Value   : result
* Comments         : Enable the MPL3115 sensor.
*
*END*********************************************************************/
bool MPL3115_Enable(mpl_handle_t *handle)
{
    uint8_t regVal;

    if (!MPL3115_ReadReg(handle, MPL3115_CTRL_REG1, &regVal))
        return false;

    /* Active MPL3115 */
    regVal |= 0x01;

    if (!MPL3115_WriteReg(handle, MPL3115_CTRL_REG1, regVal))
        return false;

    return true;
}

/*FUNCTION****************************************************************
*
* Function Name    : MPL3115_Disable
* Returned Value   : result
* Comments         : Disable the MPL3115 sensor.
*
*END*********************************************************************/
bool MPL3115_Disable(mpl_handle_t *handle)
{
    uint8_t regVal;

    if (!MPL3115_ReadReg(handle, MPL3115_CTRL_REG1, &regVal))
        return false;

    /* De-active MPL3115 */
    regVal &= ~0x01;

    if (!MPL3115_WriteReg(handle, MPL3115_CTRL_REG1, regVal))
        return false;

    return true;
}

/*FUNCTION****************************************************************
*
* Function Name    : MPL3115_WriteReg
* Returned Value   : result
* Comments         : Write to MPL3115 single register.
*
*END*********************************************************************/
bool MPL3115_WriteReg(mpl_handle_t *handle, uint8_t regAddr, uint8_t regVal)
{
    uint8_t cmdBuffer[2];

    cmdBuffer[0] = MPL3115_ADDRESS << 1;
    cmdBuffer[1] = regAddr;

    return I2C_XFER_SendDataBlocking(handle->device, cmdBuffer, 2, &regVal, 1);
}

/*FUNCTION****************************************************************
*
* Function Name    : MPL3115_ReadReg
* Returned Value   : result
* Comments         : Read from MPL3115 single register.
*
*END*********************************************************************/
bool MPL3115_ReadReg(mpl_handle_t *handle, uint8_t regAddr, uint8_t *regValPtr)
{
    uint8_t cmdBuffer[3];

    cmdBuffer[0] = MPL3115_ADDRESS << 1;
    cmdBuffer[1] = regAddr;
    cmdBuffer[2] = (MPL3115_ADDRESS << 1) + 1;

    return I2C_XFER_ReceiveDataBlocking(handle->device, cmdBuffer, 3, regValPtr, 1);
}

/*FUNCTION****************************************************************
*
* Function Name    : MPL3115_ReadData
* Returned Value   : result
* Comments         : Get current height and temperature from mpl3115.
*
*END*********************************************************************/
bool MPL3115_ReadData(mpl_handle_t *handle, mpl3115_data_t *val)
{
    uint8_t rxBuffer[5];
    uint8_t cmdBuffer[3];

    cmdBuffer[0] = MPL3115_ADDRESS << 1;
    cmdBuffer[1] = MPL3115_OUT_P_MSB;
    cmdBuffer[2] = (MPL3115_ADDRESS << 1) + 1;
    if (!I2C_XFER_ReceiveDataBlocking(handle->device, cmdBuffer, 3, rxBuffer, 5))
        return false;

    // place the read buffer into the 32 bit pressure/altitude and 16 bit temperature.
    val->presData = (rxBuffer[0] << 24) | (rxBuffer[1] << 16) | (rxBuffer[2] << 8);
    val->tempData = (rxBuffer[3] << 8) | rxBuffer[4];

    return true;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
