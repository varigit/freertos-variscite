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
/****************************************************************************
*
* Comments:
*   This file contains the functions which write and read the SPI memories
*   using the ECSPI driver in interrupt mode.
*
****************************************************************************/

#include "FreeRTOS.h"
#include "semphr.h"
#include "gpt.h"
#include "gpt_timer.h"
#include "board.h"

#define MAXIMUM_24M_DIV 15

static SemaphoreHandle_t xSemaphore;

void GPT_Timer_Init()
{
    gpt_init_config_t config = {
        .freeRun    = false,
        .waitEnable = true,
        .stopEnable = true,
        .dozeEnable = true,
        .dbgEnable  = false,
        .enableMode = true
    };

    xSemaphore = xSemaphoreCreateBinary();

    /* Initialize GPT module */
    GPT_Init(BOARD_GPTA_BASEADDR, &config);

    /* Set GPT clock source to 24M OSC */
    GPT_SetClockSource(BOARD_GPTA_BASEADDR, gptClockSourceOsc);

    /* Set GPT interrupt priority 3 */
    NVIC_SetPriority(BOARD_GPTA_IRQ_NUM, 3);

    /* Enable NVIC interrupt */
    NVIC_EnableIRQ(BOARD_GPTA_IRQ_NUM);
}

/*
 * Set GPT to triggle interrupt in future time
 */
void GPT_Set_Timer_Delay(uint32_t ms)
{
    uint64_t counter = 24000ULL * ms; /* First get the counter needed by delay time */
    uint32_t high;
    uint32_t div24m, div;

    /* Get the value that exceed maximum register counter */
    high = (uint32_t)(counter >> 32);

    div24m = MAXIMUM_24M_DIV; /*Since we use 24MHz as GPT peripheral clock, here we set the 24M divider to maximum value*/
    div = high / (div24m + 1); /* Get PRESCALER value */

    /* Now set prescaler */
    GPT_SetOscPrescaler(BOARD_GPTA_BASEADDR, div24m);
    GPT_SetPrescaler(BOARD_GPTA_BASEADDR, div);

    /* Set GPT compare value */
    GPT_SetOutputCompareValue(BOARD_GPTA_BASEADDR, gptOutputCompareChannel1,
                              (uint32_t)(counter / (div24m + 1) / (div + 1)));

    /* Enable GPT Output Compare1 interrupt */
    GPT_SetIntCmd(BOARD_GPTA_BASEADDR, gptStatusFlagOutputCompare1, true);

    /* GPT start */
    GPT_Enable(BOARD_GPTA_BASEADDR);
}

/*
 * Block the current task until GPT interrupt happens
 */
void GPT_Wait_Timer_Expire(void)
{
    /* Wait until next GPT event happens. */
    xSemaphoreTake(xSemaphore, portMAX_DELAY);
}

/*
 * GPT Interrupt Handler
 */
void BOARD_GPTA_HANDLER()
{
    BaseType_t xHigherPriorityTaskWoken;

    /* When GPT timeout, we disable GPT to make sure this is a oneshot event */
    GPT_Disable(BOARD_GPTA_BASEADDR);
    GPT_SetIntCmd(BOARD_GPTA_BASEADDR, gptStatusFlagOutputCompare1, false);
    GPT_ClearStatusFlag(BOARD_GPTA_BASEADDR, gptStatusFlagOutputCompare1);

    xSemaphoreGiveFromISR(xSemaphore, &xHigherPriorityTaskWoken);
    /*portYIELD_FROM_ISR is necessary to activate task switch immediately*/
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
