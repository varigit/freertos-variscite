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
#include "fxas21002.h"

/*FUNCTION****************************************************************
*
* Function Name    : FXAS_Init
* Returned Value   : result
* Comments         : Initialize FXAS21002 Gyro sensor.
*
*END*********************************************************************/
bool FXAS_Init(fxas_handle_t *handle, const fxas_init_t *fxas_config)
{
    // Place FXAS21002 in Standby.
    FXAS_WriteReg(handle, FXAS21002_CTRL_REG1, 0x00);

    // Configure full scale range.
    FXAS_WriteReg(handle, FXAS21002_CTRL_REG0, (uint8_t)fxas_config->range);

    // Configure output data rate.
    FXAS_WriteReg(handle, FXAS21002_CTRL_REG1, (uint8_t)fxas_config->dataRate);

    return true;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FXAS_Deinit
 * Description   : Disable the FXAS21002 and reset register content.
 *
 *END**************************************************************************/
bool FXAS_Deinit(fxas_handle_t *handle)
{
    // Reset Register content and place FXAS21002 into Standby Mode.
    return FXAS_WriteReg(handle, FXAS21002_CTRL_REG1, 0x40);
}

/*FUNCTION****************************************************************
*
* Function Name    : FXAS_Enable
* Returned Value   : result
* Comments         : Enable the FXAS21002 sensor.
*
*END*********************************************************************/
bool FXAS_Enable(fxas_handle_t *handle)
{
    uint8_t regVal;

    if (!FXAS_ReadReg(handle, FXAS21002_CTRL_REG1, &regVal))
        return false;

    /* Active FXAS21002 */
    regVal |= 0x02;

    if (!FXAS_WriteReg(handle, FXAS21002_CTRL_REG1, regVal))
        return false;

    return true;
}

/*FUNCTION****************************************************************
*
* Function Name    : FXAS_Disable
* Returned Value   : result
* Comments         : Disable the FXAS21002 sensor.
*
*END*********************************************************************/
bool FXAS_Disable(fxas_handle_t *handle)
{
    uint8_t regVal;

    if (!FXAS_ReadReg(handle, FXAS21002_CTRL_REG1, &regVal))
        return false;

    /* De-active FXAS21002 */
    regVal &= ~0x02;

    if (!FXAS_WriteReg(handle, FXAS21002_CTRL_REG1, regVal))
        return false;

    return true;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FXAS_WriteReg
 * Description   : Write the specified register of FXAS21002.
 * The writing process is through I2C.
 *
 *END**************************************************************************/
bool FXAS_WriteReg(fxas_handle_t *handle, uint8_t regAddr, uint8_t regVal)
{
    uint8_t cmdBuffer[2];

    cmdBuffer[0] = handle->address << 1;
    cmdBuffer[1] = regAddr;

    return I2C_XFER_SendDataBlocking(handle->device, cmdBuffer, 2, &regVal, 1); 
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FXAS_ReadReg
 * Description   : Read the specified register value of FXAS21002.
 * The reading process is through I2C.
 *
 *END**************************************************************************/
bool FXAS_ReadReg(fxas_handle_t *handle, uint8_t regAddr, uint8_t *regValPtr)
{
    uint8_t cmdBuffer[3];

    cmdBuffer[0] = handle->address << 1;
    cmdBuffer[1] = regAddr;
    cmdBuffer[2] = (handle->address << 1) + 1;

    return I2C_XFER_ReceiveDataBlocking(handle->device, cmdBuffer, 3, regValPtr, 1);
}

/*FUNCTION****************************************************************
*
* Function Name    : FXAS_ReadData
* Returned Value   : result
* Comments         : Get 3-Axes Gyro from fxas21002.
*
*END*********************************************************************/
bool FXAS_ReadData(fxas_handle_t *handle, fxas_data_t *val)
{
    uint8_t rxBuffer[6];
    uint8_t cmdBuffer[3];

    // Store the gain terms in the GyroSensor data structure.
    cmdBuffer[0] = handle->address << 1;
    cmdBuffer[1] = FXAS21002_OUT_X_MSB;
    cmdBuffer[2] = (handle->address << 1) + 1;
    if (!I2C_XFER_ReceiveDataBlocking(handle->device, cmdBuffer, 3, rxBuffer, 6))
        return false;

    val->gyroX = (rxBuffer[0] << 8) | rxBuffer[1];
    val->gyroY = (rxBuffer[2] << 8) | rxBuffer[3];
    val->gyroZ = (rxBuffer[4] << 8) | rxBuffer[5];

    return true;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
