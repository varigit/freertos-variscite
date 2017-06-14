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

/* define ECSPI slave mode burst length */
#define ECSPI_SLAVE_BURSTLENGTH            (7)
#define FIRST_DATA                         0xFF

/* ECSPI module slave mode configure */
static void ECSPI_SlaveConfig(ecspi_init_config_t* initConfig);
/* ECSPI slave mode transfer Status */
static bool ECSPI_SlaveGetTransferStatus(void);

static volatile uint8_t txData;
static volatile uint8_t rxData;
static uint8_t txBuffer[20];
static uint8_t rxBuffer[20];
static volatile bool isBusy;

int main(void)
{
    uint8_t i;

    ecspi_init_config_t ecspiSlaveInitConfig = {
        .clockRate = 0,
        .baudRate = 0,
        .mode = ecspiSlaveMode,
        .burstLength = ECSPI_SLAVE_BURSTLENGTH,
        .channelSelect = BOARD_ECSPI_SLAVE_CHANNEL,
        .clockPhase = ecspiClockPhaseSecondEdge,
        .clockPolarity = ecspiClockPolarityActiveHigh,
        .ecspiAutoStart = 0
    };

    /* Hardware initialiize, include RDC, CLOCK, IOMUX, ENABLE MODULE */
    hardware_init();

    PRINTF("\n-------------- ECSPI slave driver example --------------\n\n\r");
    PRINTF("This example application demonstrates usage of ECSPI slave driver.\n\r");
    PRINTF("It responding to master via SPI bus.\n\n\r");

    /* Ecspi slave initialize, include configure parameters */
    txData = FIRST_DATA;
    ECSPI_SlaveConfig(&ecspiSlaveInitConfig);

    PRINTF("SLAVE: Initial transmit data: %d\n\n\r", txData);

    /* Send data to master and receive data from master */
    txData = 0;
    for(i = 0; i < 20; i++)
    {
        /* Wait for transfer */
        while(ECSPI_SlaveGetTransferStatus());
        txBuffer[i] = txData;
        rxBuffer[i] = rxData;
        txData = txData + 1;
        /* Set transfer status */
        isBusy = true;
    }

    for(i = 0; i < 20; i++)
    {
        PRINTF("SLAVE: Next step transmit data: %d\n\r", txBuffer[i]);
        PRINTF("     : Currently received data: %d\n\n\r", rxBuffer[i]);
    }

    /* Disable ecspi slave module */
    ECSPI_Disable(BOARD_ECSPI_SLAVE_BASEADDR);
    while(1);
}

/******************************************************************************
*
* Function Name: ECSPI_SlaveGetTransferStatus
* Comments: Get Slave transfer status.
* 
******************************************************************************/
static bool ECSPI_SlaveGetTransferStatus(void)
{
    return isBusy;
}

/******************************************************************************
*
* Function Name: ECSPI_SlaveConfig
* Comments: ECSPI slave initialize
* 
******************************************************************************/
static void ECSPI_SlaveConfig(ecspi_init_config_t* initConfig)
{
    /* Initialize ECSPI, parameter configure */
    ECSPI_Init(BOARD_ECSPI_SLAVE_BASEADDR, initConfig);

    /* Move first data to tx data register to be ready for first transmition. */
    ECSPI_SendData(BOARD_ECSPI_SLAVE_BASEADDR, txData);

    /* Call core API to enable the IRQ. */
    NVIC_EnableIRQ(BOARD_ECSPI_SLAVE_IRQ_NUM);

    /* Clear ECSPI status register */
    ECSPI_ClearStatusFlag(BOARD_ECSPI_SLAVE_BASEADDR, ecspiFlagTxfifoTc);
    ECSPI_ClearStatusFlag(BOARD_ECSPI_SLAVE_BASEADDR, ecspiFlagRxfifoOverflow);

    /* Enable RXFIFO Ready Interrupt.*/
    ECSPI_SetIntCmd(BOARD_ECSPI_SLAVE_BASEADDR, ecspiFlagRxfifoReady, true);

    /* Set ECSPI transfer state. */
    isBusy = true;
}

/******************************************************************************
*
* Function Name    : BOARD_ECSPI_SLAVE_HANDLER
* Returned Value   : none
* Comments         : 
*    ECSPI slave IRQ handler.
*    Copy txData to tx data register (will be send in next step) and received
*    data to rxData. 
* 
******************************************************************************/
void BOARD_ECSPI_SLAVE_HANDLER(void)
{
    /* Are one word or more in RX FIFO */
    if(ECSPI_GetStatusFlag(BOARD_ECSPI_SLAVE_BASEADDR, ecspiFlagRxfifoReady) != 0)
    {
        /* Read byte from rx data register */
        rxData = ECSPI_ReceiveData(BOARD_ECSPI_SLAVE_BASEADDR);

        /* Store tx data to tx data register for next transmition */
        ECSPI_SendData(BOARD_ECSPI_SLAVE_BASEADDR, txData);

        /* Clear the status */
        ECSPI_ClearStatusFlag(BOARD_ECSPI_SLAVE_BASEADDR, ecspiFlagTxfifoTc);
        ECSPI_ClearStatusFlag(BOARD_ECSPI_SLAVE_BASEADDR, ecspiFlagRxfifoOverflow);

        /* Set transfer status */
        isBusy = false;
    }
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
