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

#include "gpt.h"
#include "board.h"
#include "clock_freq.h"
#include "debug_console_imx.h"

/* This case will run for 5 seconds */
static volatile uint32_t num = 10;
static uint32_t counterA, counterB;

int main(void)
{
    uint32_t freqA, freqB;
    gpt_init_config_t config = {
        .freeRun     = false,
        .waitEnable  = true,
        .stopEnable  = true,
        .dozeEnable  = true,
        .dbgEnable   = false,
        .enableMode  = true
    };

    hardware_init();

    /* Initialize GPT module */
    GPT_Init(BOARD_GPTA_BASEADDR, &config);
    GPT_Init(BOARD_GPTB_BASEADDR, &config);

    /* Set GPT clock source, when use OSC as clock source, we need to make sure the OSC freq
     * after divided by OscPrescaler should be less than half of the peripheral clock set by
     * CCM */
    GPT_SetClockSource(BOARD_GPTA_BASEADDR, gptClockSourceOsc);
    GPT_SetClockSource(BOARD_GPTB_BASEADDR, gptClockSourcePeriph);

    /* Divide GPTA osc clock source frequency by 2, and divide additional 2 inside GPT module  */
    GPT_SetOscPrescaler(BOARD_GPTA_BASEADDR, 1);
    GPT_SetPrescaler(BOARD_GPTA_BASEADDR, 1);
    /* Divide GPTB clock source frequency by 2 inside GPT module */
    GPT_SetPrescaler(BOARD_GPTB_BASEADDR, 1);

    /* Get GPT clock frequency */
    freqA = 24000000 / 2; /* A is bound to OSC directly, with OSC divider 2 */
    freqB = get_gpt_clock_freq(BOARD_GPTB_BASEADDR); /* Get B peripheral clock freq */
    /* GPTA and GPTB frequency is divided by 2 inside module */
    freqA /= 2;
    freqB /= 2;

    /* Set both GPT modules to 1 second duration */
    GPT_SetOutputCompareValue(BOARD_GPTA_BASEADDR, gptOutputCompareChannel1, freqA);
    GPT_SetOutputCompareValue(BOARD_GPTB_BASEADDR, gptOutputCompareChannel1, freqB);

    /* Set GPT interrupt priority to same value to avoid handler preemption */
    NVIC_SetPriority(BOARD_GPTA_IRQ_NUM, 3);
    NVIC_SetPriority(BOARD_GPTB_IRQ_NUM, 3);
    /* Enable NVIC interrupt */
    NVIC_EnableIRQ(BOARD_GPTA_IRQ_NUM);
    NVIC_EnableIRQ(BOARD_GPTB_IRQ_NUM);

    /* Enable GPT Output Compare1 interrupt */
    GPT_SetIntCmd(BOARD_GPTA_BASEADDR, gptStatusFlagOutputCompare1, true);
    GPT_SetIntCmd(BOARD_GPTB_BASEADDR, gptStatusFlagOutputCompare1, true);

    PRINTF("GPT timer will now start\n\r");
    PRINTF("counter/freq ratio should be close to 0.0 or 1.0 ...\n\r");
    /* GPT start */
    GPT_Enable(BOARD_GPTA_BASEADDR);
    GPT_Enable(BOARD_GPTB_BASEADDR);

    while (true)
    {
        __WFI();

        while ((num & 1) != 0); /* wait both timer handled */

        PRINTF("\tGPT A freq %u, counter %u.\n\r", freqA, counterA);
        PRINTF("\tGPT B freq %u, counter %u.\n\r", freqB, counterB);

        if (num == 0)
        {
            /* Stop GPT */
            GPT_Disable(BOARD_GPTA_BASEADDR);
            GPT_Disable(BOARD_GPTB_BASEADDR);
            PRINTF("GPT example finished...\n\r");
        }
    }
}

void BOARD_GPTA_HANDLER()
{
    GPT_ClearStatusFlag(BOARD_GPTA_BASEADDR, gptStatusFlagOutputCompare1);

    if (num && --num)
        counterB = GPT_ReadCounter(BOARD_GPTB_BASEADDR);
}

void BOARD_GPTB_HANDLER()
{
    GPT_ClearStatusFlag(BOARD_GPTB_BASEADDR, gptStatusFlagOutputCompare1);

    if (num && --num)
        counterA = GPT_ReadCounter(BOARD_GPTA_BASEADDR);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
