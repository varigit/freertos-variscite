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

typedef struct _i2c_state {
    const uint8_t*    cmdBuff;         /*!< The buffer of I2C command. */
    const uint8_t*    txBuff;          /*!< The buffer of data being sent.*/
    uint8_t*          rxBuff;          /*!< The buffer of received data. */
    volatile uint32_t cmdSize;         /*!< The remaining number of commands to be transmitted. */
    volatile uint32_t txSize;          /*!< The remaining number of bytes to be transmitted. */
    volatile uint32_t rxSize;          /*!< The remaining number of bytes to be received. */
    volatile bool     isBusy;          /*!< True if there is an active transmission. */
    volatile uint32_t operateDir;      /*!< Overall I2C bus operating direction. */
    volatile uint32_t currentDir;      /*!< Current Data transfer direction. */
    volatile uint32_t currentMode;     /*!< Current I2C Bus role of this module. */
} i2c_state_t;

/* I2C runtime state structure */
static i2c_state_t i2cState;

static bool compare(uint8_t* bufA, uint8_t* bufB, uint32_t length);

static void I2C_XFER_Config(i2c_init_config_t* initConfig);
static bool I2C_XFER_Write(const uint8_t* cmdBuff, uint32_t cmdSize, const uint8_t* txBuffer, uint32_t txSize);
static bool I2C_XFER_Read(const uint8_t* cmdBuff, uint32_t cmdSize, uint8_t* rxBuffer, uint32_t rxSize);
static bool I2C_XFER_IsBusy(void);

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

    PRINTF("\n\r++++++++++++++++ I2C Send/Receive Interrupt Driven Example +++++++++++++++++\n\r");
    PRINTF("This example will write data to on board EEPROM through I2C Bus\n\r");
    PRINTF("and read them back to see if the EEPROM is programmed successfully. \n\r\n\r");

    PRINTF("[1].Initialize the I2C module with initialize structure. \n\r");
    I2C_XFER_Config(&i2cInitConfig);

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

    PRINTF("[4].Write data to EEPROM. \n\r");
    I2C_XFER_Write(cmdBuffer, 3, txBuffer, 5);
    PRINTF("[5].Wait until transmission is finished. \n\r");
    while(I2C_XFER_IsBusy());

    PRINTF("[6].Launch a I2C read action from 0x0000 address. \n\r");
    cmdBuffer[0] = EEPROM_ADDRESS << 1;
    cmdBuffer[1] = 0x00;
    cmdBuffer[2] = 0x00;
    cmdBuffer[3] = (EEPROM_ADDRESS << 1) + 1;

    PRINTF("[7].Read data from EEPROM. \n\r");
    I2C_XFER_Read(cmdBuffer, 4, rxBuffer, 5);
    PRINTF("[8].Wait until transmission is finished. \n\r");
    while (I2C_XFER_IsBusy());

    PRINTF("[9].Compare data between txBuf and rxBuf: \n\r");
    if (compare(txBuffer, rxBuffer, 5))
        PRINTF("    txBuf and rxBuf are same, example passed!!!\n\r");
    else
        PRINTF("    txBuf and rxBuf are different, example failed!!! \n\r");

    while (true);
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

static void I2C_XFER_Config(i2c_init_config_t* initConfig)
{
    /* Initialize I2C state structure content. */
    i2cState.cmdBuff = 0;
    i2cState.txBuff = 0;
    i2cState.rxBuff = 0;
    i2cState.cmdSize = 0;
    i2cState.txSize = 0;
    i2cState.rxSize = 0;
    i2cState.isBusy = false;
    i2cState.operateDir = i2cDirectionReceive;
    i2cState.currentDir = i2cDirectionReceive;
    i2cState.currentMode = i2cModeSlave;

    /* Initialize I2C baud rate, mode, transfer direction and slave address. */
    I2C_Init(BOARD_I2C_BASEADDR, initConfig);

    /* Set I2C Interrupt priority */
    NVIC_SetPriority(BOARD_I2C_IRQ_NUM, 3);

    /* Call core API to enable the IRQ. */
    NVIC_EnableIRQ(BOARD_I2C_IRQ_NUM);

    /* Finally, enable the I2C module */
    I2C_Enable(BOARD_I2C_BASEADDR);
}

static bool I2C_XFER_Write(const uint8_t* cmdBuff, uint32_t cmdSize,
                      const uint8_t* txBuffer, uint32_t txSize)
{
    if ((i2cState.isBusy) || (0 == txSize))
        return false;

    /* Initialize i2c transfer struct */
    i2cState.cmdBuff = cmdBuff;
    i2cState.cmdSize = cmdSize;
    i2cState.txBuff = txBuffer;
    i2cState.txSize = txSize;
    i2cState.isBusy = true;
    i2cState.operateDir = i2cDirectionTransmit;

    /* Clear I2C interrupt flag to avoid spurious interrupt */
    I2C_ClearStatusFlag(BOARD_I2C_BASEADDR, i2cStatusInterrupt);

    if (I2C_GetStatusFlag(BOARD_I2C_BASEADDR, i2cStatusBusBusy))
    {
        /* Reset i2c transfer state. */
        i2cState.operateDir = i2cDirectionReceive;
        i2cState.isBusy = false;
        return false;
    }

    /* Set I2C work under Tx mode */
    I2C_SetDirMode(BOARD_I2C_BASEADDR, i2cDirectionTransmit);
    i2cState.currentDir = i2cDirectionTransmit;

    /* Switch to Master Mode and Send Start Signal. */
    I2C_SetWorkMode(BOARD_I2C_BASEADDR, i2cModeMaster);
    i2cState.currentMode = i2cModeMaster;

    if (0 != cmdSize)
    {
        I2C_WriteByte(BOARD_I2C_BASEADDR, *i2cState.cmdBuff);
        i2cState.cmdBuff++;
        i2cState.cmdSize--;
    }
    else
    {
        I2C_WriteByte(BOARD_I2C_BASEADDR, *i2cState.txBuff);
        i2cState.txBuff++;
        i2cState.txSize--;
    }

    /* Enable I2C interrupt, subsequent data transfer will be handled in ISR. */
    I2C_SetIntCmd(BOARD_I2C_BASEADDR, true);

    return true;
}

static bool I2C_XFER_Read(const uint8_t* cmdBuff, uint32_t cmdSize,
                     uint8_t* rxBuffer, uint32_t rxSize)
{
    if ((i2cState.isBusy) || (0 == rxSize))
        return false;

    /* Initialize i2c transfer struct */
    i2cState.cmdBuff = cmdBuff;
    i2cState.cmdSize = cmdSize;
    i2cState.rxBuff = rxBuffer;
    i2cState.rxSize = rxSize;
    i2cState.isBusy = true;
    i2cState.operateDir = i2cDirectionReceive;

    /* Clear I2C interrupt flag to avoid spurious interrupt */
    I2C_ClearStatusFlag(BOARD_I2C_BASEADDR, i2cStatusInterrupt);

    if (I2C_GetStatusFlag(BOARD_I2C_BASEADDR, i2cStatusBusBusy))
    {
        /* Reset i2c transfer state. */
        i2cState.operateDir = i2cDirectionReceive;
        i2cState.isBusy = false;
        return false;
    }

    /* Set I2C work under Tx mode */
    I2C_SetDirMode(BOARD_I2C_BASEADDR, i2cDirectionTransmit);
    i2cState.currentDir = i2cDirectionTransmit;

    /* Switch to Master Mode and Send Start Signal. */
    I2C_SetWorkMode(BOARD_I2C_BASEADDR, i2cModeMaster);
    i2cState.currentMode = i2cModeMaster;

    /* Is there command to be sent before receive data? */
    if (0 != i2cState.cmdSize)
    {
        if (1 == i2cState.cmdSize)
            I2C_SendRepeatStart(BOARD_I2C_BASEADDR);
        I2C_WriteByte(BOARD_I2C_BASEADDR, *i2cState.cmdBuff);
        i2cState.cmdBuff++;
        i2cState.cmdSize--;
    }
    else
    {
        /* Change to receive state. */
        I2C_SetDirMode(BOARD_I2C_BASEADDR, i2cDirectionReceive);
        i2cState.currentDir = i2cDirectionReceive;

        if (1 == rxSize)
            /* Send Nack */
            I2C_SetAckBit(BOARD_I2C_BASEADDR, false);
        else
            /* Send Ack */
            I2C_SetAckBit(BOARD_I2C_BASEADDR, true);
        /* dummy read to clock in 1st byte */
        I2C_ReadByte(BOARD_I2C_BASEADDR);
    }

    /* Enable I2C interrupt, subsequent data transfer will be handled in ISR. */
    I2C_SetIntCmd(BOARD_I2C_BASEADDR, true);

    return true;
}

static bool I2C_XFER_IsBusy(void)
{
    return i2cState.isBusy;
}

void BOARD_I2C_HANDLER(void)
{
    /* Clear interrupt flag. */
    I2C_ClearStatusFlag(BOARD_I2C_BASEADDR, i2cStatusInterrupt);

    /* Exit the ISR if no transfer is happening for this instance. */
    if (!i2cState.isBusy)
        return;

    if (i2cModeMaster == i2cState.currentMode)
    {
        if (i2cDirectionTransmit == i2cState.currentDir)
        {
            if ((I2C_GetStatusFlag(BOARD_I2C_BASEADDR, i2cStatusReceivedAck)) ||
                ((0 == i2cState.txSize) && (0 == i2cState.cmdSize)))
            {
                if ((i2cDirectionTransmit == i2cState.operateDir) ||
                    (I2C_GetStatusFlag(BOARD_I2C_BASEADDR, i2cStatusReceivedAck)))
                {
                    /* Switch to Slave mode and Generate a Stop Signal. */
                    I2C_SetWorkMode(BOARD_I2C_BASEADDR, i2cModeSlave);
                    i2cState.currentMode = i2cModeSlave;

                    /* Switch back to Rx direction. */
                    I2C_SetDirMode(BOARD_I2C_BASEADDR, i2cDirectionReceive);
                    i2cState.currentDir = i2cDirectionReceive;

                    /* Close I2C interrupt. */
                    I2C_SetIntCmd(BOARD_I2C_BASEADDR, false);
                    /* Release I2C Bus. */
                    i2cState.isBusy = false;
                }
                else
                {
                    /* Switch back to Rx direction. */
                    I2C_SetDirMode(BOARD_I2C_BASEADDR, i2cDirectionReceive);
                    i2cState.currentDir = i2cDirectionReceive;

                    if (1 == i2cState.rxSize)
                        /* Send Nack */
                        I2C_SetAckBit(BOARD_I2C_BASEADDR, false);
                    else
                        /* Send Ack */
                        I2C_SetAckBit(BOARD_I2C_BASEADDR, true);
                    /* dummy read to clock in 1st byte */
                    *i2cState.rxBuff = I2C_ReadByte(BOARD_I2C_BASEADDR);
                }
            }
            else
            {
                if (0 != i2cState.cmdSize)
                {
                    if ((1 == i2cState.cmdSize) && (i2cDirectionReceive == i2cState.operateDir))
                        I2C_SendRepeatStart(BOARD_I2C_BASEADDR);
                    I2C_WriteByte(BOARD_I2C_BASEADDR, *i2cState.cmdBuff);
                    i2cState.cmdBuff++;
                    i2cState.cmdSize--;
                }
                else
                {
                    I2C_WriteByte(BOARD_I2C_BASEADDR, *i2cState.txBuff);
                    i2cState.txBuff++;
                    i2cState.txSize--;
                }
            }
        }
        else
        {
            /* Normal read operation. */
            if (2 == i2cState.rxSize)
                /* Send Nack */
                I2C_SetAckBit(BOARD_I2C_BASEADDR, false);
            else
                /* Send Nack */
                I2C_SetAckBit(BOARD_I2C_BASEADDR, true);

            if (1 == i2cState.rxSize)
            {
                /* Switch back to Tx direction to avoid additional I2C bus read. */
                I2C_SetDirMode(BOARD_I2C_BASEADDR, i2cDirectionTransmit);
                i2cState.currentDir = i2cDirectionTransmit;
            }
            *i2cState.rxBuff = I2C_ReadByte(BOARD_I2C_BASEADDR);
            i2cState.rxBuff++;
            i2cState.rxSize--;

            /* receive finished. */
            if (0 == i2cState.rxSize)
            {
                /* Switch to Slave mode and Generate a Stop Signal. */
                I2C_SetWorkMode(BOARD_I2C_BASEADDR, i2cModeSlave);
                i2cState.currentMode = i2cModeSlave;

                /* Switch back to Rx direction. */
                I2C_SetDirMode(BOARD_I2C_BASEADDR, i2cDirectionReceive);
                i2cState.currentDir = i2cDirectionReceive;

                /* Close I2C interrupt. */
                I2C_SetIntCmd(BOARD_I2C_BASEADDR, false);
                /* Release I2C Bus. */
                i2cState.isBusy = false;
            }
        }
    }
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
