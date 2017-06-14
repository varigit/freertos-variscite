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
#include "debug_console_imx.h"
#include "ecspi.h"
#include "clock_freq.h"

/* define ECSPI master mode parameters configuration. */
#define ECSPI_MASTER_BURSTLENGTH        (7)
#define ECSPI_MASTER_STARTMODE          (0)
#define BURST_LENGTH_IN_BYTES(x)        ((8 * x) - 1)

/* ECSPI data transfer */
static bool ECSPI_MasterTransfer(uint8_t* txBuffer, uint8_t* rxBuffer, uint32_t transferSize);

int main(void)
{
    uint8_t txData = 0;
    uint8_t rxData = 0;
    uint8_t control_char;

    ecspi_init_config_t initConfig = {
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
    initConfig.clockRate = get_ecspi_clock_freq(BOARD_ECSPI_MASTER_BASEADDR);

    PRINTF("\n-------------- ECSPI master driver example --------------\n\n\r");
    PRINTF("This example application demonstrates usage of SPI driver in master mode.\n\r");
    PRINTF("It transfers data to/from remote MCU in SPI slave mode.\n\r");

    /* Ecspi module initialize, include configure parameters */
    ECSPI_Init(BOARD_ECSPI_MASTER_BASEADDR, &initConfig);

    /* Wait slave ready, then press 's' to start communication. */
    while (true)
    {
        PRINTF("Press \"s\" when SPI slave is ready.\n\r");
        control_char = GETCHAR();
        if ((control_char == 's') || (control_char == 'S'))
            break;
    }

    /* Send 1~20 to slave and receive data from slave */
    for (uint8_t i = 0; i < 20; i++)
    {
        txData++;
        ECSPI_MasterTransfer(&txData, &rxData, 1);
        PRINTF("MASTER: Transmited data: %d \n\r", txData);
        PRINTF("      : Received   data: %d \n\r", rxData);
    }

    PRINTF("Example finish!!!\n\r");
    while (1)
        __WFI();
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
    if (0 == transferSize)
        return false;

    /* Set the burst length to one byte(8 bits) */
    ECSPI_SetBurstLength(BOARD_ECSPI_MASTER_BASEADDR, BURST_LENGTH_IN_BYTES(1));

    while (transferSize)
    {
        /* Fill the TXFIFO */
        ECSPI_SendData(BOARD_ECSPI_MASTER_BASEADDR, *txBuffer++);

        /* start transmission */
        ECSPI_StartBurst(BOARD_ECSPI_MASTER_BASEADDR);

        /* Wait transmission finish */
        while (!ECSPI_GetStatusFlag(BOARD_ECSPI_MASTER_BASEADDR, ecspiFlagTxfifoTc));
        ECSPI_ClearStatusFlag(BOARD_ECSPI_MASTER_BASEADDR, ecspiFlagTxfifoTc);

        /* Fill the RXFIFO */
        *rxBuffer = ECSPI_ReceiveData(BOARD_ECSPI_MASTER_BASEADDR);

        transferSize--;
    }

    return true;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
