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
#include "semphr.h"
#include "device_imx.h"
#include "board.h"
#include "ecspi_xfer.h"
#include "uart_imx.h"
#include "debug_console_imx.h"

typedef struct EcspiState
{
    uint8_t*                  txBuffPtr;    /* Pointer to ECSPI Transmission Buffer */
    uint32_t                  txSize;       /* The remaining number of bytes to be transmitted */
    uint8_t*                  rxBuffPtr;    /* Pointer to ECSPI Receive Buffer */
    uint32_t                  rxSize;       /* The remaining number of bytes to be transmitted */
    SemaphoreHandle_t         xSemaphore;   /* ECSPI internal synchronize semaphore. */
} ecspi_state_t;

/* ECSPI runtime state structure */
static ecspi_state_t ecspiState;

/******************************************************************************
*
* Function Name: ECSPI_XFER_Config
* Comments: ECSPI module initialize
* 
******************************************************************************/
void ECSPI_XFER_Config(const ecspi_init_config_t* initConfig)
{
    /* Initialize ECSPI state structure content. */
    ecspiState.txBuffPtr = 0;
    ecspiState.rxBuffPtr = 0;
    ecspiState.txSize = 0;
    ecspiState.rxSize = 0;
    ecspiState.xSemaphore = xSemaphoreCreateBinary();

    /* Initialize ECSPI, parameter configure */
    ECSPI_Init(BOARD_ECSPI_BASEADDR, initConfig);

    /* Call core API to enable the IRQ. */
    NVIC_EnableIRQ(BOARD_ECSPI_IRQ_NUM);

    /* The interrupt calls an interrupt safe API function - so its priority must
       be equal to or lower than configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY. */
    NVIC_SetPriority(BOARD_ECSPI_IRQ_NUM, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
}

/******************************************************************************
*
* Function Name: ECSPI_XFER_TransmitBurst
* Comments: Fill the TXFIFO.
* 
******************************************************************************/
bool ECSPI_XFER_TransmitBurst(void)
{
    uint8_t bytes;
    uint32_t data;
    uint8_t i;

    /* Fill the TXFIFO */
    while((ecspiState.txSize > 0) && (ECSPI_GetStatusFlag(BOARD_ECSPI_BASEADDR, ecspiFlagTxfifoFull) == 0))
    {
        bytes = ecspiState.txSize & 0x3;       /* first get unaligned part trasmitted */
        bytes = bytes ? bytes : 4;             /* if aligned, then must be 4 */

        if(!(ecspiState.txBuffPtr))
        {
            data = 0xFFFFFFFF;                 /* half-duplex receive data */
        }
        else
        {
          data = 0;
          for(i = 0; i < bytes; i++)
              data = (data << 8) | *(ecspiState.txBuffPtr)++;
        }

        ECSPI_SendData(BOARD_ECSPI_BASEADDR, data);
        ecspiState.txSize -= bytes;
        ecspiState.rxSize += bytes;
    }
    /* start transmission */
    ECSPI_StartBurst(BOARD_ECSPI_BASEADDR);
    return true;
}

/******************************************************************************
*
* Function Name: ECSPI_XFER_ReceiveBurst
* Comments: Receive data from RXFIFO
* 
******************************************************************************/
bool ECSPI_XFER_ReceiveBurst(void)
{
    uint32_t data;
    uint32_t bytes;
    uint32_t i;

    while ((ecspiState.rxSize > 0) && (ECSPI_GetStatusFlag(BOARD_ECSPI_BASEADDR, ecspiFlagRxfifoReady) != 0))
    {
        data = ECSPI_ReceiveData(BOARD_ECSPI_BASEADDR);   /* read data from register */
        bytes = ecspiState.rxSize & 0x3;                  /* first get unaligned part received */
        bytes = bytes ? bytes : 4;                        /* if aligned, then must be 4 */

        if(ecspiState.rxBuffPtr)                          /* not half-duplex transmit */
        {
            for(i = bytes; i > 0; i--)
            {
                *(ecspiState.rxBuffPtr + i - 1) = data & 0xFF;
                data >>= 8;
            }
            ecspiState.rxBuffPtr += bytes;
        }
        ecspiState.rxSize -= bytes;
    }
    return true;
}

/******************************************************************************
*
* Function Name: ECSPI_XFER_TransferBlocking
* Comments: Transmit and Receive an amount of data in blocking mode with
*           interrupt.
* 
******************************************************************************/
bool ECSPI_XFER_TransferBlocking(uint8_t *txBuffer, uint8_t *rxBuffer, uint32_t transferSize)
{
    uint32_t len;
  
    if((transferSize == 0) || ((txBuffer == 0)&&(rxBuffer == 0)))
    {
        return false;
    }

    /* Update the burst length to real size */
    len = (uint32_t)(transferSize * 8 - 1);
    ECSPI_SetBurstLength(BOARD_ECSPI_BASEADDR, len);

    /* Configure the transfer */
    ecspiState.txBuffPtr = txBuffer;
    ecspiState.rxBuffPtr = rxBuffer;
    ecspiState.txSize = transferSize;
    ecspiState.rxSize = 0;
  
    /* Fill the TXFIFO */
    ECSPI_XFER_TransmitBurst();
    /* Enable interrupts */
    ECSPI_SetIntCmd(BOARD_ECSPI_BASEADDR, ecspiFlagTxfifoEmpty, true);

    /* Wait until transfer data finish. */
    xSemaphoreTake(ecspiState.xSemaphore, portMAX_DELAY);
    return true;
}

/******************************************************************************
*
* Function Name: BOARD_ECSPI_HANDLER
* Comments: The interrupt service routine triggered by ECSPI interrupt
* 
******************************************************************************/
void BOARD_ECSPI_HANDLER(void)
{
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

    /* Receive data from RXFIFO */
    ECSPI_XFER_ReceiveBurst();

    /* Push data left */
    if(ecspiState.txSize)
    {
        ECSPI_XFER_TransmitBurst();
        return;
    }

    /* No data left to push, but still waiting for rx data, enable receive data available interrupt. */
    if(ecspiState.rxSize)
    {
        ECSPI_SetIntCmd(BOARD_ECSPI_BASEADDR, ecspiFlagRxfifoReady, true);
        return;
    }

    /* Disable interrupt */
    ECSPI_SetIntCmd(BOARD_ECSPI_BASEADDR, ecspiFlagTxfifoEmpty, false);
    ECSPI_SetIntCmd(BOARD_ECSPI_BASEADDR, ecspiFlagRxfifoReady, false);

    /* Clear the status */
    ECSPI_ClearStatusFlag(BOARD_ECSPI_BASEADDR, ecspiFlagTxfifoTc);
    ECSPI_ClearStatusFlag(BOARD_ECSPI_BASEADDR, ecspiFlagRxfifoOverflow);

    /* Unlock the task to process the event. */
    xSemaphoreGiveFromISR(ecspiState.xSemaphore, &xHigherPriorityTaskWoken);

    /* Perform a context switch to wake the higher priority task. */
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
