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

/* define ECSPI slave mode burst length */
#define ECSPI_SLAVE_BURSTLENGTH    (7)
#define FIRST_DATA                 0xFF

int main(void)
{
    uint8_t txBuffer[20] = {0};
    uint8_t rxBuffer[20] = {0};
    uint8_t txData = FIRST_DATA;

    ecspi_init_config_t initConfig = {
        .clockRate = 0,
        .baudRate = 0,
        .mode = ecspiSlaveMode,
        .burstLength = ECSPI_SLAVE_BURSTLENGTH,
        .channelSelect = BOARD_ECSPI_SLAVE_CHANNEL,
        .clockPhase = ecspiClockPhaseSecondEdge,
        .clockPolarity = ecspiClockPolarityActiveHigh,
        .ecspiAutoStart = 0
    };

    /* Hardware initialize, include RDC, CLOCK, IOMUX, ENABLE MODULE */
    hardware_init();

    PRINTF("\n-------------- ECSPI slave driver example --------------\n\n\r");
    PRINTF("This example application demonstrates usage of ECSPI slave driver.\n\r");
    PRINTF("It responding to master via SPI bus.\n\n\r");

    /* Initialize ECSPI, parameter configure */
    ECSPI_Init(BOARD_ECSPI_SLAVE_BASEADDR, &initConfig);

    PRINTF("SLAVE: Initial transmit data: %d\n\n\r", FIRST_DATA);
    /* Move first data to tx data register to be ready for first transmission. */
    ECSPI_SendData(BOARD_ECSPI_SLAVE_BASEADDR, txData);

    /* Send data to master and receive data from master */
    txData = 0;

    for(uint8_t i = 0; i < 20; i++)
    {
        /* Wait for data received */
        while(!ECSPI_GetStatusFlag(BOARD_ECSPI_SLAVE_BASEADDR, ecspiFlagRxfifoReady));
        /* Fill rxBuffer */
        rxBuffer[i] = ECSPI_ReceiveData(BOARD_ECSPI_SLAVE_BASEADDR);
        /* Store tx data to tx data register for next transmission */
        ECSPI_SendData(BOARD_ECSPI_SLAVE_BASEADDR, txData);
        txBuffer[i] = txData;
        txData++;
    }

    for(uint8_t i = 0; i < 20; i++)
    {
        PRINTF("SLAVE: Next step transmit data: %d\n\r", txBuffer[i]);
        PRINTF("     : Currently received data: %d\n\n\r", rxBuffer[i]);
    }

    PRINTF("Example finish!!!\n\r");
    while(1)
        __WFI();
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
