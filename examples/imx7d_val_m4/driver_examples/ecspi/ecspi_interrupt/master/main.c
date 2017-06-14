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

#include <stdio.h>
#include "board.h"
#include "uart_imx.h"
#include "debug_console_imx.h"
#include "ecspi.h"
#include "clock_freq.h"

/* define ECSPI master mode parameters configuration. */
#define ECSPI_MASTER_BURSTLENGTH        (7)
#define ECSPI_MASTER_STARTMODE          (0)

typedef struct EcspiState
{
    uint8_t*                  txBuffPtr;    /* Pointer to ECSPI Transmit Buffer */
    uint8_t                   txSize;       /* The remaining number of bytes to be transmitted */
    uint8_t*                  rxBuffPtr;    /* Pointer to ECSPI Receive Buffer */
    uint8_t                   rxSize;       /* The remaining number of bytes to be received */
    volatile bool             isBusy;       /* True if there is a active transfer */
} ecspi_state_t;

/* ECSPI runtime state structure */
static ecspi_state_t ecspiState;

/* ECSPI master configure */
static void ECSPI_MasterConfig(ecspi_init_config_t* initConfig);
/* ECSPI data transfer */
static bool ECSPI_MasterTransfer(uint8_t* txBuffer, uint8_t* rxBuffer, uint32_t transferSize);
static bool ECSPI_MasterReceiveBurst(void);
static bool ECSPI_MasterTransmitBurst(void);
/* ECSPI transfer status */
static bool ECSPI_MasterGetTransferStatus(void);

/* Transferred data */
static uint8_t txData[1] = {0};
static uint8_t rxData[1] = {0};

int main(void)
{
    uint8_t control_char;
    uint8_t i;

    ecspi_init_config_t ecspiMasterInitConfig = {
        .baudRate = 500000,
        .mode = ecspiMasterMode,
        .burstLength = ECSPI_MASTER_BURSTLENGTH,
        .channelSelect = BOARD_ECSPI_MASTER_CHANNEL,
        .clockPhase = ecspiClockPhaseSecondEdge,
        .clockPolarity = ecspiClockPolarityActiveHigh,
        .ecspiAutoStart = ECSPI_MASTER_STARTMODE
    };

    /* Hardware initialize, include RDC, CLOCK, IOMUX, ENABLE MODULE */
    hardware_init();

    /* Update clock frequency of this module */
    ecspiMasterInitConfig.clockRate = get_ecspi_clock_freq(BOARD_ECSPI_MASTER_BASEADDR);

    PRINTF("\n-------------- ECSPI master driver example --------------\n\n\r");
    PRINTF("This example application demonstrates usage of SPI driver in master mode.\n\r");
    PRINTF("It transfers data to/from remote MCU in SPI slave mode.\n\r");

    /* Ecspi module initialize, include configure parameters */
    ECSPI_MasterConfig(&ecspiMasterInitConfig);

    /* Wait slave ready, then press 's' to start communication. */
    while(true) 
    {
        PRINTF("Press \"s\" when spi slave is ready.\n\r");
        control_char = GETCHAR();
        if((control_char == 's') || (control_char == 'S'))
            break;
    }

    /* Send 1~20 to slave and receive data from slave */
    for(i = 0; i < 20; i++)
    {
        txData[0]++;
        ECSPI_MasterTransfer((uint8_t*)txData, (uint8_t*)rxData, 1);
        while(ECSPI_MasterGetTransferStatus());
        PRINTF("MASTER: Transmited data: %d \n\r", txData[0]);
        PRINTF("      : Received data: %d \n\n\r", rxData[0]);
    }
    while(1);
}

/******************************************************************************
*
* Function Name: ECSPI_MasterTransmitBurst
* Comments: Fill the TXFIFO.
*
******************************************************************************/
static bool ECSPI_MasterTransmitBurst(void)
{
    uint8_t bytes;
    uint32_t data;
    uint8_t i;

    /* Fill the TXFIFO */
    while((ecspiState.txSize > 0) && (ECSPI_GetStatusFlag(BOARD_ECSPI_MASTER_BASEADDR, ecspiFlagTxfifoFull) == 0))
    {
        bytes = ecspiState.txSize & 0x3;      /* first get unaligned part transmitted */
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

        ECSPI_SendData(BOARD_ECSPI_MASTER_BASEADDR, data);
        ecspiState.txSize -= bytes;
        ecspiState.rxSize += bytes;
    }
    /* start transmission */
    ECSPI_StartBurst(BOARD_ECSPI_MASTER_BASEADDR);
    /* set transfer flag */
    ecspiState.isBusy = true;
    return true;
}

/******************************************************************************
*
* Function Name: ECSPI_MasterReceiveBurst
* Comments: Receive data from RXFIFO
*
******************************************************************************/
static bool ECSPI_MasterReceiveBurst(void)
{
    uint32_t data;
    uint32_t bytes;
    uint32_t i;

    while ((ecspiState.rxSize > 0) && (ECSPI_GetStatusFlag(BOARD_ECSPI_MASTER_BASEADDR, ecspiFlagRxfifoReady) != 0))
    {
        data = ECSPI_ReceiveData(BOARD_ECSPI_MASTER_BASEADDR);   /* read data from register */
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
* Function Name: ECSPI_MasterTransfer
* Comments: Transmit and Receive an amount of data in no-blocking mode with
*           interrupt.
*
******************************************************************************/
static bool ECSPI_MasterTransfer(uint8_t* txBuffer, uint8_t* rxBuffer, uint32_t transferSize)
{
    uint32_t len;

    if((ecspiState.isBusy) || (transferSize == 0))
    {
        return false;
    }

    /* Update the burst length to real size */
    len = (uint32_t)(transferSize * 8 - 1);
    ECSPI_SetBurstLength(BOARD_ECSPI_MASTER_BASEADDR, len);

    /* Configure the transfer */
    ecspiState.txBuffPtr = txBuffer;
    ecspiState.rxBuffPtr = rxBuffer;
    ecspiState.txSize = transferSize;
    ecspiState.rxSize = 0;

    /* Fill the TXFIFO */
    ECSPI_MasterTransmitBurst();
    /* Enable interrupts */
    ECSPI_SetIntCmd(BOARD_ECSPI_MASTER_BASEADDR, ecspiFlagTxfifoEmpty, true);
    return true;
}

/******************************************************************************
*
* Function Name: ECSPI_MasterGetTransferStatus
* Comments: Get transfer status.
*
******************************************************************************/
static bool ECSPI_MasterGetTransferStatus(void)
{
    return ecspiState.isBusy;
}

/******************************************************************************
*
* Function Name: ECSPI_MasterConfig
* Comments: ECSPI module initialize
*
******************************************************************************/
static void ECSPI_MasterConfig(ecspi_init_config_t* initConfig)
{
    /* Initialize ECSPI transfer state. */
    ecspiState.isBusy = false;

    /* Initialize ECSPI, parameter configure */
    ECSPI_Init(BOARD_ECSPI_MASTER_BASEADDR, initConfig);

    /* Call core API to enable the IRQ. */
    NVIC_EnableIRQ(BOARD_ECSPI_MASTER_IRQ_NUM);
}

/******************************************************************************
*
* Function Name: BOARD_ECSPI_MASTER_HANDLER
* Comments: The interrupt service routine triggered by ECSPI interrupt
*
******************************************************************************/
void BOARD_ECSPI_MASTER_HANDLER(void)
{
    /* Receive data from RXFIFO */
    ECSPI_MasterReceiveBurst();

    /* Push data left */
    if(ecspiState.txSize)
    {
        ECSPI_MasterTransmitBurst();
        return;
    }

    /* No data left to push, but still waiting for rx data, enable receive data available interrupt. */
    if(ecspiState.rxSize)
    {
        ECSPI_SetIntCmd(BOARD_ECSPI_MASTER_BASEADDR, ecspiFlagRxfifoReady, true);
        return;
    }

    /* Disable interrupt */
    ECSPI_SetIntCmd(BOARD_ECSPI_MASTER_BASEADDR, ecspiFlagTxfifoEmpty, false);
    ECSPI_SetIntCmd(BOARD_ECSPI_MASTER_BASEADDR, ecspiFlagRxfifoReady, false);

    /* Clear the status */
    ECSPI_ClearStatusFlag(BOARD_ECSPI_MASTER_BASEADDR, ecspiFlagTxfifoTc);
    ECSPI_ClearStatusFlag(BOARD_ECSPI_MASTER_BASEADDR, ecspiFlagRxfifoOverflow);

    ecspiState.isBusy = false;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
