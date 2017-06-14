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

static uint8_t txBuffer[5];
static uint8_t rxBuffer[7];
static uint8_t cmdBuffer[5];

static void report_abs(void);
static void I2C_XFER_Config(i2c_init_config_t* initConfig);
static bool I2C_XFER_Write(const uint8_t* cmdBuff, uint32_t cmdSize, const uint8_t* txBuffer, uint32_t txSize);
static bool I2C_XFER_Read(const uint8_t* cmdBuff, uint32_t cmdSize, uint8_t* rxBuffer, uint32_t rxSize);
static bool I2C_XFER_IsBusy(void);

int main(void)
{
    uint8_t i;

    /* Setup I2C init structure. */
    i2c_init_config_t i2cInitConfig = {
        .baudRate     = 400000u,
        .slaveAddress = 0x00
    };

    /* Initialize board specified hardware. */
    hardware_init();

    /* Get current module clock frequency. */
    i2cInitConfig.clockRate = get_i2c_clock_freq(BOARD_I2C_BASEADDR);

    PRINTF("\n\r++++++++++++++++ I2C Send/Receive interrupt Example ++++++++++++++++\n\r");
    PRINTF("This example will configure on board accelerometer through I2C Bus\n\r");
    PRINTF("and read 10 samples back to see if the accelerometer is configured successfully. \n\r\n\r");

    PRINTF("[1].Initialize the I2C module with initialize structure. \n\r");
    I2C_XFER_Config(&i2cInitConfig);

    /* Finally, enable the I2C module */
    I2C_Enable(BOARD_I2C_BASEADDR);

    PRINTF("[2].Set on-board Acc sensor range to 2G\n\r");
    // Place FXOS8700 into standby
    cmdBuffer[0] = BOARD_I2C_FXOS8700_ADDR << 1;
    cmdBuffer[1] = 0x2A;
    txBuffer[0]  = 0x00;
    I2C_XFER_Write(cmdBuffer, 2, txBuffer, 1);
    while(I2C_XFER_IsBusy());

    // Disable FXOS8700's magnetometer only
    cmdBuffer[0] = BOARD_I2C_FXOS8700_ADDR << 1;
    cmdBuffer[1] = 0x5B;
    txBuffer[0]  = 0x00;
    I2C_XFER_Write(cmdBuffer, 2, txBuffer, 1);
    while(I2C_XFER_IsBusy());

    cmdBuffer[0] = BOARD_I2C_FXOS8700_ADDR << 1;
    cmdBuffer[1] = 0x5C;
    txBuffer[0]  = 0x00;
    I2C_XFER_Write(cmdBuffer, 2, txBuffer, 1);
    while(I2C_XFER_IsBusy());

    // Set accelerometer range to 2G
    cmdBuffer[0] = BOARD_I2C_FXOS8700_ADDR << 1;
    cmdBuffer[1] = 0x0E;
    txBuffer[0]  = 0x00;
    I2C_XFER_Write(cmdBuffer, 2, txBuffer, 1);
    while(I2C_XFER_IsBusy());

    // Set accelerometer for high resolution (maximum over sampling)
    cmdBuffer[0] = BOARD_I2C_FXOS8700_ADDR << 1;
    cmdBuffer[1] = 0x2B;
    txBuffer[0]  = 0x02;
    I2C_XFER_Write(cmdBuffer, 2, txBuffer, 1);
    while(I2C_XFER_IsBusy());

    PRINTF("[3].Set on-board Acc sensor working at fast read and active mode\n\r");
    cmdBuffer[0] = BOARD_I2C_FXOS8700_ADDR << 1;
    cmdBuffer[1] = 0x2A;
    txBuffer[0]  = 0x09;
    I2C_XFER_Write(cmdBuffer, 2, txBuffer, 1);
    while(I2C_XFER_IsBusy());

    PRINTF("[4].Acc sensor WHO_AM_I check... ");
    cmdBuffer[0] = BOARD_I2C_FXOS8700_ADDR << 1;
    cmdBuffer[1] = 0x0D;
    cmdBuffer[2] = (BOARD_I2C_FXOS8700_ADDR << 1) + 1;
    I2C_XFER_Read(cmdBuffer, 3, rxBuffer, 1);
    while (I2C_XFER_IsBusy());
    if (0xC7 == rxBuffer[0])
        PRINTF("OK\n\r");
    else
        PRINTF("ERROR\n\r");

    PRINTF("[5].Acquire 10 samples from Acc sensor\n\r");
    for (i = 0; i < 10; i++)
        report_abs();

    PRINTF("\n\rExample finished!!!\n\r");
    while (true)
        __WFI();
}

static void report_abs(void)
{
    int16_t x, y, z;
    float Ax, Ay, Az;

    cmdBuffer[0] = BOARD_I2C_FXOS8700_ADDR << 1;
    cmdBuffer[1] = 0x01;
    cmdBuffer[2] = (BOARD_I2C_FXOS8700_ADDR << 1) + 1;
    I2C_XFER_Read(cmdBuffer, 3, rxBuffer, 6);
    while (I2C_XFER_IsBusy());

    x = ((rxBuffer[0] << 8) & 0xff00) | rxBuffer[1];
    y = ((rxBuffer[2] << 8) & 0xff00) | rxBuffer[3];
    z = ((rxBuffer[4] << 8) & 0xff00) | rxBuffer[5];
    x = (int16_t)(x) >> 2;
    y = (int16_t)(y) >> 2;
    z = (int16_t)(z) >> 2;

    Ax = x / (4.0 * 1024);     //For full scale range 2g mode.
    Ay = y / (4.0 * 1024);
    Az = z / (4.0 * 1024);
    PRINTF("2G MODE: X=%6.3fg Y=%6.3fg Z=%6.3fg\n\r",Ax, Ay, Az);
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
