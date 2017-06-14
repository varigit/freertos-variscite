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
#include "adc_imx7d.h"
#include "debug_console_imx.h"
#include "board.h"

int main(void)
{
    adc_init_config_t adcConfig = {
        .sampleRate = 2000,
        // For i.MX7D this value should always be set to true.
        .levelShifterEnable = true
    };

    adc_logic_ch_init_config_t adcChannelConfig = {
        .inputChannel = BOARD_ADC_INPUT_CHANNEL,
        .coutinuousEnable = true,
        .convertRate = 1,
        .averageEnable = true,
        .averageNumber = adcAvgNum32
    };

    // Initialize board specified hardware.
    hardware_init();

    PRINTF("\n-------------- ADC imx7d driver example --------------\n\n\r");
    PRINTF("This example demonstrates usage of ADC driver on i.MX processor.\n\r");
    PRINTF("It Continuous convert Analog Input, and print the result to terminal \n\r");

    // Initialize ADC module.
    ADC_Init(BOARD_ADC_BASEADDR, &adcConfig);

    // Enable Convert finish interrupt on Logic Channel A
    ADC_SetIntSigCmd(BOARD_ADC_BASEADDR, adcIntConvertChA, true);
    ADC_SetIntCmd(BOARD_ADC_BASEADDR, adcIntConvertChA, true);

    /* Set ADC Interrupt priority */
    NVIC_SetPriority(BOARD_ADC_IRQ_NUM, 3);

    /* Call core API to enable the IRQ. */
    NVIC_EnableIRQ(BOARD_ADC_IRQ_NUM);

    // Initialize ADC Logic Channel A module.
    ADC_LogicChInit(BOARD_ADC_BASEADDR, adcLogicChA, &adcChannelConfig);

    // Start Continuous Conversion on Logic Channel A.
    ADC_SetConvertCmd(BOARD_ADC_BASEADDR, adcLogicChA, true);

    while(1);
}

void BOARD_ADC_HANDLER(void)
{
    float voltage;
    ADC_ClearStatusFlag(BOARD_ADC_BASEADDR, adcStatusConvertChA);
    voltage = (1.8 * ADC_GetConvertResult(BOARD_ADC_BASEADDR, adcLogicChA))/0xFFF;
    PRINTF("Current analog value: %3.2fv\n\r", voltage);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
