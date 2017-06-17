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

#define DS1307_REG_SECS         0x00    /* 00-59 */
#define DS1307_REG_MIN          0x01    /* 00-59 */
#define DS1307_REG_HOUR         0x02    /* 00-23, or 1-12{am,pm} */
#define DS1307_BIT_12HR         0x40    /* in REG_HOUR */
#define DS1307_BIT_PM           0x20    /* in REG_HOUR */
#define DS1307_REG_WDAY         0x03    /* 01-07 */
#define DS1307_REG_MDAY         0x04    /* 01-31 */
#define DS1307_REG_MONTH        0x05    /* 01-12 */
#define DS1307_REG_YEAR         0x06    /* 00-99 */
#define DS1337_REG_CONTROL      0x0e
#define DS1337_BIT_nEOSC        0x80
#define DS1337_REG_STATUS       0x0f
#define DS1337_BIT_OSF          0x80

#define bcd2bin(x)              (((x) & 0x0f) + ((x) >> 4) * 10)
#define bin2bcd(x)              ((((x) / 10) << 4) + (x) % 10)

static uint8_t txBuffer[5];
static uint8_t rxBuffer[7];
static uint8_t cmdBuffer[5];

static void report_date(void);
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

    /* Initialize board specified hardware. */
    hardware_init();

    /* Get current module clock frequency. */
    i2cInitConfig.clockRate = get_i2c_clock_freq(BOARD_I2C_BASEADDR);

    PRINTF("\n\r++++++++++++++++ I2C Send/Receive polling Example ++++++++++++++++\n\r");
    PRINTF("This example will configure on board RTC through I2C Bus\n\r");
    PRINTF("and read the date to see if the RTC is configured successfully. \n\r");

    PRINTF("[1].Initialize the I2C module with initialize structure. \n\r");
    I2C_Init(BOARD_I2C_BASEADDR, &i2cInitConfig);

    /* Finally, enable the I2C module */
    I2C_Enable(BOARD_I2C_BASEADDR);

    PRINTF("[2].Read on-board RTC control & status registers\n\r");
    cmdBuffer[0] = BOARD_I2C_ISL12057_ADDR << 1;
    cmdBuffer[1] = DS1337_REG_CONTROL;
    cmdBuffer[2] = (BOARD_I2C_ISL12057_ADDR << 1) + 1;
    I2C_MasterReceiveDataPolling(BOARD_I2C_BASEADDR, cmdBuffer, 3, rxBuffer, 2);

    PRINTF("[3].If oscillator off, turn it on, so clock can tick\n\r");
    if (rxBuffer[0] & DS1337_BIT_nEOSC) {
        cmdBuffer[0] = BOARD_I2C_ISL12057_ADDR << 1;
        cmdBuffer[1] = DS1337_REG_CONTROL;
        txBuffer[0]  = rxBuffer[0] & ~DS1337_BIT_nEOSC;
        I2C_MasterSendDataPolling(BOARD_I2C_BASEADDR, cmdBuffer, 2, txBuffer, 1);
        PRINTF("Oscillator turned on!\n\r");
    }

    PRINTF("[4].If oscillator fault, clear flag, and warn\n\r");
    if (rxBuffer[1] & DS1337_BIT_OSF) {
        cmdBuffer[0] = BOARD_I2C_ISL12057_ADDR << 1;
        cmdBuffer[1] = DS1337_REG_STATUS;
        txBuffer[0]  = rxBuffer[1] & ~DS1337_BIT_OSF;
        I2C_MasterSendDataPolling(BOARD_I2C_BASEADDR, cmdBuffer, 2, txBuffer, 1);
        PRINTF("SET TIME!\n\r");
    }

    PRINTF("[5].Ensure RTC uses in 24-hours format\n\r");
    cmdBuffer[0] = BOARD_I2C_ISL12057_ADDR << 1;
    cmdBuffer[1] = DS1307_REG_HOUR;
    cmdBuffer[2] = (BOARD_I2C_ISL12057_ADDR << 1) + 1;
    I2C_MasterReceiveDataPolling(BOARD_I2C_BASEADDR, cmdBuffer, 3, rxBuffer, 1);
    if (rxBuffer[0] & DS1307_BIT_12HR) {
        /* use txBuffer[1] for binary conversion before swtching to bcd */
        txBuffer[1] = bcd2bin(rxBuffer[0] & 0x1f);
        if (txBuffer[1] == 12)
            txBuffer[1] = 0;
        if (rxBuffer[0] & DS1307_BIT_PM)
            txBuffer[1] += 12;
        cmdBuffer[0] = BOARD_I2C_ISL12057_ADDR << 1;
        cmdBuffer[1] = DS1307_REG_HOUR;
        txBuffer[0] = bin2bcd(txBuffer[1]);
        I2C_MasterSendDataPolling(BOARD_I2C_BASEADDR, cmdBuffer, 2, txBuffer, 1);
        PRINTF("RTC switched to 24-hours format!\n\r");
    }

    PRINTF("[6].Get current date\n\r");
    report_date();

    PRINTF("\n\rExample finished!!!\n\r");
    while (true)
        __WFI();
}

static void report_date(void)
{
    cmdBuffer[0] = BOARD_I2C_ISL12057_ADDR << 1;
    cmdBuffer[1] = DS1307_REG_SECS;
    cmdBuffer[2] = (BOARD_I2C_ISL12057_ADDR << 1) + 1;
    I2C_MasterReceiveDataPolling(BOARD_I2C_BASEADDR, cmdBuffer, 3, rxBuffer, 7);

    PRINTF("DATE [gg/mm/yyyy hh:mm:ss]: %02d/%02d/%04d %02d:%02d:%02d\n\r",
           bcd2bin(rxBuffer[DS1307_REG_MDAY] & 0x3f),
           bcd2bin(rxBuffer[DS1307_REG_MONTH] & 0x1f),
           2000 + bcd2bin(rxBuffer[DS1307_REG_YEAR]),
           bcd2bin(rxBuffer[DS1307_REG_HOUR] & 0x3f),
           bcd2bin(rxBuffer[DS1307_REG_MIN] & 0x7f),
           bcd2bin(rxBuffer[DS1307_REG_SECS] & 0x7f));
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
