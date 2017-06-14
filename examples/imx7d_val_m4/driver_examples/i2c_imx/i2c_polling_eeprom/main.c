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
#include "debug_console_imx.h"
#include "i2c_imx.h"

#define EEPROM_ADDRESS    (0x50)

static bool compare(uint8_t* bufA, uint8_t* bufB, uint32_t length);

static bool I2C_MasterSendDataPolling(I2C_Type *base,
                                      const uint8_t *cmdBuff,
                                      uint32_t cmdSize,
                                      const uint8_t *txBuff,
                                      uint32_t txSize);
static bool I2C_MasterReceiveDataPolling(I2C_Type *base,
                                         const uint8_t *cmdBuff,
                                         uint32_t cmdSize,
                                         uint8_t *rxBuff,
                                         uint32_t rxSize);

int main(void)
{
    /* Setup I2C init structure. */
    i2c_init_config_t i2cInitConfig = {
        .baudRate     = 400000u,
        .slaveAddress = 0x00
    };
    uint8_t txBuffer[5];
    uint8_t rxBuffer[5];
    uint8_t cmdBuffer[5];

    /* Initialize board specified hardware. */
    hardware_init();

    /* Get current module clock frequency. */
    i2cInitConfig.clockRate = get_i2c_clock_freq(BOARD_I2C_BASEADDR);

    PRINTF("\n\r++++++++++++++++ I2C Send/Receive polling Example ++++++++++++++++\n\r");
    PRINTF("This example will write data to on board EEPROM through I2C Bus\n\r");
    PRINTF("and read them back to see if the EEPROM is programmed successfully. \n\r\n\r");

    PRINTF("[1].Initialize the I2C module with initialize structure. \n\r");
    I2C_Init(BOARD_I2C_BASEADDR, &i2cInitConfig);

    /* Finally, enable the I2C module */
    I2C_Enable(BOARD_I2C_BASEADDR);

    PRINTF("[2].Launch a I2C write action to 0x0000 address. \n\r");
    cmdBuffer[0] = EEPROM_ADDRESS << 1;
    cmdBuffer[1] = 0x00;
    cmdBuffer[2] = 0x00;

    PRINTF("[3].Prepare Data for Sending. \n\r");
    txBuffer[0] = 0x11;
    txBuffer[1] = 0x22;
    txBuffer[2] = 0x33;
    txBuffer[3] = 0x44;
    txBuffer[4] = 0x55;

    PRINTF("[4].Write data to EEPROM and wait until transmission finished. \n\r");
    I2C_MasterSendDataPolling(BOARD_I2C_BASEADDR, cmdBuffer, 3, txBuffer, 5);

    PRINTF("[5].Launch a I2C read action from 0x0000 address. \n\r");
    cmdBuffer[0] = EEPROM_ADDRESS << 1;
    cmdBuffer[1] = 0x00;
    cmdBuffer[2] = 0x00;
    cmdBuffer[3] = (EEPROM_ADDRESS << 1) + 1;

    PRINTF("[6].Read data from EEPROM and wait until transmission finished. \n\r");
    I2C_MasterReceiveDataPolling(BOARD_I2C_BASEADDR, cmdBuffer, 4, rxBuffer, 5);

    PRINTF("[7].Compare data between txBuf and rxBuf: \n\r");
    if (compare(txBuffer, rxBuffer, 5))
        PRINTF("    txBuf and rxBuf are same, example passed!!!\n\r");
    else
        PRINTF("    txBuf and rxBuf are different, example failed!!! \n\r");

    while (true)
        __WFI();
}

static bool compare(uint8_t* bufA, uint8_t* bufB, uint32_t length)
{
    for (uint32_t i = 0; i < length; i++)
    {
        if (bufA[i] != bufB[i])
            return false;
    }

    return true;
}

static bool I2C_MasterSendDataPolling(I2C_Type *base,
                                      const uint8_t *cmdBuff,
                                      uint32_t cmdSize,
                                      const uint8_t *txBuff,
                                      uint32_t txSize)
{
    if (I2C_GetStatusFlag(base, i2cStatusBusBusy))
        return false;

    /* Set I2C work under Tx mode */
    I2C_SetDirMode(base, i2cDirectionTransmit);

    /* Switch to Master Mode and Send Start Signal. */
    I2C_SetWorkMode(base, i2cModeMaster);

    /* Send first byte */
    if (0 != cmdSize)
    {
        I2C_WriteByte(base, *cmdBuff++);
        cmdSize--;
    }
    else
    {
        I2C_WriteByte(base, *txBuff++);
        txSize--;
    }

    while (1)
    {
        /* Wait I2C transmission status flag assert.  */
        while (!I2C_GetStatusFlag(base, i2cStatusInterrupt));

        /* Clear I2C transmission status flag. */
        I2C_ClearStatusFlag(base, i2cStatusInterrupt);

        /* Transmit complete. */
        if ((I2C_GetStatusFlag(base, i2cStatusReceivedAck)) ||
            ((0 == txSize) && (0 == cmdSize)))
        {
            /* Switch to Slave mode and Generate a Stop Signal. */
            I2C_SetWorkMode(base, i2cModeSlave);

            /* Switch back to Rx direction. */
            I2C_SetDirMode(base, i2cDirectionReceive);
            return true;
        }
        else
        {
            if (0 != cmdSize)
            {
                I2C_WriteByte(base, *cmdBuff++);
                cmdSize--;
            }
            else
            {
                I2C_WriteByte(base, *txBuff++);
                txSize--;
            }
        }
    }
}

static bool I2C_MasterReceiveDataPolling(I2C_Type *base,
                                         const uint8_t *cmdBuff,
                                         uint32_t cmdSize,
                                         uint8_t *rxBuff,
                                         uint32_t rxSize)
{
    uint32_t currentDir = i2cDirectionReceive;

    /* Clear I2C interrupt flag to avoid spurious interrupt */
    I2C_ClearStatusFlag(base, i2cStatusInterrupt);

    if (I2C_GetStatusFlag(base, i2cStatusBusBusy))
    {
        return false;
    }

    /* Set I2C work under Tx mode */
    I2C_SetDirMode(base, i2cDirectionTransmit);

    /* Switch to Master Mode and Send Start Signal. */
    I2C_SetWorkMode(base, i2cModeMaster);

    if (0 != cmdSize)
    {
        currentDir = i2cDirectionTransmit;
        if (1 == cmdSize)
            I2C_SendRepeatStart(base);
        I2C_WriteByte(base, *cmdBuff++);
        cmdSize--;
    }
    else
    {
        /* Change to receive state. */
        I2C_SetDirMode(base, i2cDirectionReceive);

        if (1 == rxSize)
            /* Send Nack */
            I2C_SetAckBit(base, false);
        else
            /* Send Ack */
            I2C_SetAckBit(base, true);
        /* dummy read to clock in 1st byte */
        *rxBuff = I2C_ReadByte(base);
    }

    while (1)
    {
        /* Wait I2C transmission status flag assert.  */
        while (!I2C_GetStatusFlag(base, i2cStatusInterrupt));

        /* Clear I2C transmission status flag. */
        I2C_ClearStatusFlag(base, i2cStatusInterrupt);

        if (i2cDirectionTransmit == currentDir)
        {
            if (0 < cmdSize)
            {
                if (I2C_GetStatusFlag(base, i2cStatusReceivedAck))
                {
                    /* Switch to Slave mode and Generate a Stop Signal. */
                    I2C_SetWorkMode(base, i2cModeSlave);

                    /* Switch back to Rx direction. */
                    I2C_SetDirMode(base, i2cDirectionReceive);
                    return false;
                }
                else
                {
                    if (1 == cmdSize)
                        I2C_SendRepeatStart(base);
                    I2C_WriteByte(base, *cmdBuff++);
                    cmdSize--;
                }
            }
            else
            {
                /* Change to receive state. */
                I2C_SetDirMode(base, i2cDirectionReceive);
                currentDir = i2cDirectionReceive;

                if (1 == rxSize)
                    /* Send Nack */
                    I2C_SetAckBit(base, false);
                else
                    /* Send Ack */
                    I2C_SetAckBit(base, true);
                /* dummy read to clock in 1st byte */
                *rxBuff = I2C_ReadByte(base);
            }
        }
        else
        {
            /* Normal read operation. */
            if (2 == rxSize)
                /* Send Nack */
                I2C_SetAckBit(base, false);
            else
                /* Send Nack */
                I2C_SetAckBit(base, true);

            if (1 == rxSize)
                /* Switch back to Tx direction to avoid additional I2C bus read. */
                I2C_SetDirMode(base, i2cDirectionTransmit);
            *rxBuff = I2C_ReadByte(base);
            rxBuff++;
            rxSize--;

            /* receive finished. */
            if (0 == rxSize)
            {
                /* Switch to Slave mode and Generate a Stop Signal. */
                I2C_SetWorkMode(base, i2cModeSlave);

                /* Switch back to Rx direction. */
                I2C_SetDirMode(base, i2cDirectionReceive);

                return true;
            }
        }
    }
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
