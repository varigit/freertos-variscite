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
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "device_imx.h"
#include "i2c_imx.h"
#include "i2c_xfer.h"

void I2C_XFER_Init(i2c_handle_t *handle, i2c_xfer_init_config_t *initConfig)
{
    /* Initialize I2C state structure content. */
    handle->base        = initConfig->base;
    handle->irqNum      = initConfig->irqNum;
    handle->irqPrio     = initConfig->irqPrio;
    handle->cmdBuff     = 0;
    handle->txBuff      = 0;
    handle->rxBuff      = 0;
    handle->cmdSize     = 0;
    handle->txSize      = 0;
    handle->rxSize      = 0;
    handle->isBusy      = false;
    handle->operateDir  = i2cDirectionReceive;
    handle->currentDir  = i2cDirectionReceive;
    handle->currentMode = i2cModeSlave;
    handle->xSemaphore  = xSemaphoreCreateBinary();

    /* Initialize I2C baud rate, mode, transfer direction and slave address. */
    I2C_Init(handle->base, &initConfig->config);

    /* Set I2C Interrupt priority */
    NVIC_SetPriority(handle->irqNum, handle->irqPrio);

    /* Call core API to enable the IRQ. */
    NVIC_EnableIRQ(handle->irqNum);

    /* Finally, enable the I2C module */
    I2C_Enable(handle->base);
}

bool I2C_XFER_SendDataBlocking(i2c_handle_t *handle, const uint8_t *cmdBuff, uint32_t cmdSize,
                               const uint8_t *txBuffer, uint32_t txSize)
{
    TickType_t tickOld, tickNew;

    if ((handle->isBusy) || (0 == txSize))
        return false;

    /* Initialize i2c transfer struct */
    handle->cmdBuff = cmdBuff;
    handle->cmdSize = cmdSize;
    handle->txBuff  = txBuffer;
    handle->txSize  = txSize;
    handle->isBusy  = true;
    handle->operateDir = i2cDirectionTransmit;

    /* Clear I2C interrupt flag to avoid spurious interrupt */
    I2C_ClearStatusFlag(handle->base, i2cStatusInterrupt);

    if (I2C_GetStatusFlag(handle->base, i2cStatusBusBusy))
    {
        /* Reset i2c transfer state. */
        handle->operateDir = i2cDirectionReceive;
        handle->isBusy = false;
        return false;
    }

    /* Set I2C work under Tx mode */
    I2C_SetDirMode(handle->base, i2cDirectionTransmit);
    handle->currentDir = i2cDirectionTransmit;

    /* Switch to Master Mode and Send Start Signal. */
    I2C_SetWorkMode(handle->base, i2cModeMaster);
    handle->currentMode = i2cModeMaster;

    if (0 != cmdSize)
    {
        I2C_WriteByte(handle->base, *handle->cmdBuff);
        handle->cmdBuff++;
        handle->cmdSize--;
    }
    else
    {
        I2C_WriteByte(handle->base, *handle->txBuff);
        handle->txBuff++;
        handle->txSize--;
    }

    /* Enable I2C interrupt, subsequent data transfer will be handled in ISR. */
    I2C_SetIntCmd(handle->base, true);

    /* Wait until send data finish. */
    xSemaphoreTake(handle->xSemaphore, portMAX_DELAY);

    /* Wait bus idle */
    tickOld = xTaskGetTickCount();

    while (I2C_GetStatusFlag(handle->base, i2cStatusBusBusy))
    {
        tickNew = xTaskGetTickCount();

        /* A 50ms time-out to wait bus idle */
        if ((50 * portTICK_PERIOD_MS) < (tickNew - tickOld))
            return false;
    }

    return true;
}

uint32_t I2C_XFER_GetSendStatus(i2c_handle_t *handle)
{
    return handle->txSize;
}

bool I2C_XFER_ReceiveDataBlocking(i2c_handle_t *handle, const uint8_t* cmdBuff, uint32_t cmdSize,
                                  uint8_t* rxBuffer, uint32_t rxSize)
{
    TickType_t tickOld, tickNew;

    if ((handle->isBusy) || (0 == rxSize))
        return false;

    /* Initialize i2c transfer struct */
    handle->cmdBuff = cmdBuff;
    handle->cmdSize = cmdSize;
    handle->rxBuff  = rxBuffer;
    handle->rxSize  = rxSize;
    handle->isBusy  = true;
    handle->operateDir = i2cDirectionReceive;

    /* Clear I2C interrupt flag to avoid spurious interrupt */
    I2C_ClearStatusFlag(handle->base, i2cStatusInterrupt);

    if (I2C_GetStatusFlag(handle->base, i2cStatusBusBusy))
    {
        /* Reset i2c transfer state. */
        handle->operateDir = i2cDirectionReceive;
        handle->isBusy = false;
        return false;
    }

    /* Set I2C work under Tx mode */
    I2C_SetDirMode(handle->base, i2cDirectionTransmit);
    handle->currentDir = i2cDirectionTransmit;

    /* Switch to Master Mode and Send Start Signal. */
    I2C_SetWorkMode(handle->base, i2cModeMaster);
    handle->currentMode = i2cModeMaster;

    /* Is there command to be sent before receive data? */
    if (0 != handle->cmdSize)
    {
        if (1 == handle->cmdSize)
            I2C_SendRepeatStart(handle->base);
        I2C_WriteByte(handle->base, *handle->cmdBuff);
        handle->cmdBuff++;
        handle->cmdSize--;
    }
    else
    {
        /* Change to receive state. */
        I2C_SetDirMode(handle->base, i2cDirectionReceive);
        handle->currentDir = i2cDirectionReceive;

        if (1 == rxSize)
            /* Send Nack */
            I2C_SetAckBit(handle->base, false);
        else
            /* Send Ack */
            I2C_SetAckBit(handle->base, true);
        /* dummy read to clock in 1st byte */
        I2C_ReadByte(handle->base);
    }

    /* Enable I2C interrupt, subsequent data transfer will be handled in ISR. */
    I2C_SetIntCmd(handle->base, true);

    /* Wait until receive data finish. */
    xSemaphoreTake(handle->xSemaphore, portMAX_DELAY);

    /* Wait bus idle */
    tickOld = xTaskGetTickCount();

    while (I2C_GetStatusFlag(handle->base, i2cStatusBusBusy))
    {
        tickNew = xTaskGetTickCount();

        /* A 50ms time-out to wait bus idle */
        if ((50 * portTICK_PERIOD_MS) < (tickNew - tickOld))
            return false;
    }

    return true;
}

uint32_t I2C_XFER_GetReceiveStatus(i2c_handle_t *handle)
{
    return handle->rxSize;
}

void I2C_XFER_Handler(i2c_handle_t *handle)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    /* Clear interrupt flag. */
    I2C_ClearStatusFlag(handle->base, i2cStatusInterrupt);

    /* Exit the ISR if no transfer is happening for this instance. */
    if (!handle->isBusy)
        return;

    if (i2cModeMaster == handle->currentMode)
    {
        if (i2cDirectionTransmit == handle->currentDir)
        {
            if ((I2C_GetStatusFlag(handle->base, i2cStatusReceivedAck)) ||
                ((0 == handle->txSize) && (0 == handle->cmdSize)))
            {
                if ((i2cDirectionTransmit == handle->operateDir) ||
                    (I2C_GetStatusFlag(handle->base, i2cStatusReceivedAck)))
                {
                    /* Switch to Slave mode and Generate a Stop Signal. */
                    I2C_SetWorkMode(handle->base, i2cModeSlave);
                    handle->currentMode = i2cModeSlave;

                    /* Switch back to Rx direction. */
                    I2C_SetDirMode(handle->base, i2cDirectionReceive);
                    handle->currentDir = i2cDirectionReceive;

                    /* Close I2C interrupt. */
                    I2C_SetIntCmd(handle->base, false);
                    /* Release I2C Bus. */
                    handle->isBusy = false;
                    xSemaphoreGiveFromISR(handle->xSemaphore, &xHigherPriorityTaskWoken);
                    /* Perform a context switch to wake the higher priority task. */
                    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
                }
                else
                {
                    /* Switch back to Rx direction. */
                    I2C_SetDirMode(handle->base, i2cDirectionReceive);
                    handle->currentDir = i2cDirectionReceive;

                    if (1 == handle->rxSize)
                        /* Send Nack */
                        I2C_SetAckBit(handle->base, false);
                    else
                        /* Send Ack */
                        I2C_SetAckBit(handle->base, true);
                    /* dummy read to clock in 1st byte */
                    *handle->rxBuff = I2C_ReadByte(handle->base);
                }
            }
            else
            {
                if (0 != handle->cmdSize)
                {
                    if ((1 == handle->cmdSize) && (i2cDirectionReceive == handle->operateDir))
                        I2C_SendRepeatStart(handle->base);
                    I2C_WriteByte(handle->base, *handle->cmdBuff);
                    handle->cmdBuff++;
                    handle->cmdSize--;
                }
                else
                {
                    I2C_WriteByte(handle->base, *handle->txBuff);
                    handle->txBuff++;
                    handle->txSize--;
                }
            }
        }
        else
        {
            /* Normal read operation. */
            if (2 == handle->rxSize)
                /* Send Nack */
                I2C_SetAckBit(handle->base, false);
            else
                /* Send Nack */
                I2C_SetAckBit(handle->base, true);

            if (1 == handle->rxSize)
            {
                /* Switch back to Tx direction to avoid additional I2C bus read. */
                I2C_SetDirMode(handle->base, i2cDirectionTransmit);
                handle->currentDir = i2cDirectionTransmit;
            }
            *handle->rxBuff = I2C_ReadByte(handle->base);
            handle->rxBuff++;
            handle->rxSize--;

            /* receive finished. */
            if (0 == handle->rxSize)
            {
                /* Switch to Slave mode and Generate a Stop Signal. */
                I2C_SetWorkMode(handle->base, i2cModeSlave);
                handle->currentMode = i2cModeSlave;

                /* Switch back to Rx direction. */
                I2C_SetDirMode(handle->base, i2cDirectionReceive);
                handle->currentDir = i2cDirectionReceive;

                /* Close I2C interrupt. */
                I2C_SetIntCmd(handle->base, false);
                /* Release I2C Bus. */
                handle->isBusy = false;
                /* Release I2C Sem4 */
                xSemaphoreGiveFromISR(handle->xSemaphore, &xHigherPriorityTaskWoken);
                /* Perform a context switch to wake the higher priority task. */
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            }
        }
    }
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
