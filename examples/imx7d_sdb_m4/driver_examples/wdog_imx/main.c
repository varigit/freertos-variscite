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

#include "wdog_imx.h"
#include "board.h"
#include "debug_console_imx.h"

/* This case will cause M4 reset after 5.5 seconds */
static uint32_t num = 5;

int main(void)
{
    wdog_init_config_t config = {
       .wdw   = false,    /*!< true: suspend in low power wait, false: not suspend */
       .wdt   = true,     /*!< true: assert WDOG_B when timeout, false: not assert WDOG_B */
       .wdbg  = true,     /*!< true: suspend in debug mode, false: not suspend */
       .wdzst = false     /*!< true: suspend in doze and stop mode, false: not suspend */
    };

    hardware_init();

    WDOG_Init(BOARD_WDOG_BASEADDR, &config);

    /* Enable WDOG interrupt 0.5 second before WDOG timeout */
    NVIC_SetPriority(BOARD_WDOG_IRQ_NUM, 3);
    NVIC_EnableIRQ(BOARD_WDOG_IRQ_NUM);
    /* Refresh WDOG to reload counter */
    WDOG_Refresh(BOARD_WDOG_BASEADDR);
    WDOG_EnableInt(BOARD_WDOG_BASEADDR, 1);

    PRINTF("WDOG with timeout 1.5 seconds will now start\n\r");
    /* Enable WDOG with timeout 1.5 second */
    WDOG_Enable(BOARD_WDOG_BASEADDR, 2);

    while (true)
    {
        __WFI();
        PRINTF("WDOG was refreshed %d\n\r", num);
	if (num == 0)
            PRINTF("Counter down to 0, WDOG is starved now...\n\r", num);
    }
}

void BOARD_WDOG_HANDLER()
{
    WDOG_ClearStatusFlag(BOARD_WDOG_BASEADDR);

    if (--num)
        WDOG_Refresh(BOARD_WDOG_BASEADDR);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
