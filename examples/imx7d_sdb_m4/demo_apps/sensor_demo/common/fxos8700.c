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
#include "fxos8700.h"

/*FUNCTION****************************************************************
*
* Function Name    : FXOS_Init
* Returned Value   : result
* Comments         : Initialize FXOS8700 Acc and Mag sensor.
*
*END*********************************************************************/
bool FXOS_Init(fxos_handle_t *handle, const fxos_init_t *fxos_config)
{
    // Place FXOS8700 into standby
    if (!FXOS_WriteReg(handle, FXOS8700_CTRL_REG1, 0x00))
        return false;

    // Set oversampling to reduce magnetometer noise
    // Select hybrid mode with accel and magnetometer active
    if (!FXOS_WriteReg(handle, FXOS8700_M_CTRL_REG1, (uint8_t)fxos_config->osr | (uint8_t)fxos_config->hms))
        return false;

    // Map the magnetometer registers to follow the accelerometer registers
    if (!FXOS_WriteReg(handle, FXOS8700_M_CTRL_REG2, 0x20))
        return false;

    // Set accelerometer range(2G, 4G or 8G)
    if (!FXOS_WriteReg(handle, FXOS8700_XYZ_DATA_CFG, (uint8_t)fxos_config->range))
        return false;

    // Setting for high resolution (maximum over sampling)
    if (!FXOS_WriteReg(handle, FXOS8700_CTRL_REG2, 0x02))
        return false;

    // Set the data rate.
    if (!FXOS_WriteReg(handle, FXOS8700_CTRL_REG1, ((uint8_t)fxos_config->dataRate)))
        return false;

    return true;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FXOS_Deinit
 * Description   : Disable the FXOS8700 and reset register content.
 *
 *END**************************************************************************/
bool FXOS_Deinit(fxos_handle_t *handle)
{
    // Write 0000 0000 = 0x00 to CTRL_REG1 to place FXOS8700 into standby.
    if (!FXOS_WriteReg(handle, FXOS8700_CTRL_REG1, 0x00))
        return false;

    // Reset Register content.
    return FXOS_WriteReg(handle, FXOS8700_CTRL_REG2, 0x40);
}

/*FUNCTION****************************************************************
*
* Function Name    : FXOS_Enable
* Returned Value   : result
* Comments         : Enable the FXOS8700 sensor.
*
*END*********************************************************************/
bool FXOS_Enable(fxos_handle_t *handle)
{
    uint8_t regVal;

    if (!FXOS_ReadReg(handle, FXOS8700_CTRL_REG1, &regVal))
        return false;

    /* Active FXOS8700 and Enable Reduced noise mode */
    regVal |= 0x05;

    if (!FXOS_WriteReg(handle, FXOS8700_CTRL_REG1, regVal))
        return false;

    return true;
}

/*FUNCTION****************************************************************
*
* Function Name    : FXOS_Disable
* Returned Value   : result
* Comments         : Disable the FXOS8700 sensor.
*
*END*********************************************************************/
bool FXOS_Disable(fxos_handle_t *handle)
{
    uint8_t regVal;

    if (!FXOS_ReadReg(handle, FXOS8700_CTRL_REG1, &regVal))
        return false;

    /* De-active FXOS8700 & Disable Reduced noise mode*/
    regVal &= ~0x05;

    if (!FXOS_WriteReg(handle, FXOS8700_CTRL_REG1, regVal))
        return false;

    return true;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FXOS_WriteReg
 * Description   : Write the specified register of fxos8700.
 * The writing process is through I2C.
 *END**************************************************************************/
bool FXOS_WriteReg(fxos_handle_t *handle, uint8_t regAddr, uint8_t regVal)
{
    uint8_t cmdBuffer[2];

    cmdBuffer[0] = handle->address << 1;
    cmdBuffer[1] = regAddr;

    return I2C_XFER_SendDataBlocking(handle->device, cmdBuffer, 2, &regVal, 1); 
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FXOS_ReadReg
 * Description   : Read the specified register value of fxos8700.
 * The reading process is through I2C.
 *END**************************************************************************/
bool FXOS_ReadReg(fxos_handle_t *handle, uint8_t regAddr, uint8_t *regValPtr)
{
    uint8_t cmdBuffer[3];

    cmdBuffer[0] = handle->address << 1;
    cmdBuffer[1] = regAddr;
    cmdBuffer[2] = (handle->address << 1) + 1;

    return I2C_XFER_ReceiveDataBlocking(handle->device, cmdBuffer, 3, regValPtr, 1);
}

/*FUNCTION****************************************************************
*
* Function Name    : FXOS_ReadData
* Returned Value   : result
* Comments         : Get current Acc and Mag from FXOS8700 6-axis sensor.
*
*END*********************************************************************/
bool FXOS_ReadData(fxos_handle_t *handle, fxos_data_t *val)
{
    uint8_t rxBuffer[12];
    uint8_t cmdBuffer[3];

    // Fetch Current Acc and Mag in all Axis
    cmdBuffer[0] = handle->address << 1;
    cmdBuffer[1] = FXOS8700_OUT_X_MSB;
    cmdBuffer[2] = (handle->address << 1) + 1;
    if (!I2C_XFER_ReceiveDataBlocking(handle->device, cmdBuffer, 3, rxBuffer, 12))
        return false;

    val->accX = (rxBuffer[2] << 8) | rxBuffer[3];
    val->accY = (rxBuffer[0] << 8) | rxBuffer[1];
    val->accZ = (rxBuffer[4] << 8) | rxBuffer[5];
    val->magX = (rxBuffer[8] << 8) | rxBuffer[9];
    val->magY = (rxBuffer[6] << 8) | rxBuffer[7];
    val->magZ = (rxBuffer[10] << 8) | rxBuffer[11];

    return true;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
