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
#include "board.h"
#include "debug_console_imx.h"
#include "gpio_ctrl.h"
#include "hw_timer.h"

#define BLINKING_INTERVAL_MIN    (100)

static volatile uint32_t blinkingInterval = BLINKING_INTERVAL_MIN;

/******************************************************************************
*
* Function Name: ToggleTask
* Comments: this task is used to turn toggle on/off LED.
*
******************************************************************************/
void ToggleTask(void *pvParameters)
{
    while (true)
    {
        GPIO_Ctrl_ToggleLed();
        /* Use Hardware timer to get accurate delay */
        Hw_Timer_Delay(blinkingInterval);
    }
}

/******************************************************************************
*
* Function Name: SwitchTask
* Comments: this task is used to change blinking frequency.
*
******************************************************************************/
void SwitchTask(void *pvParameters)
{
    while (true)
    {
        PRINTF("\n\r====== Blinking interval %dms ======\n\r", blinkingInterval);
        GPIO_Ctrl_WaitKeyPressed();
        blinkingInterval += 100;
        if (blinkingInterval > 1000)
            blinkingInterval = BLINKING_INTERVAL_MIN;
        /* Delay for 1 second to avoid glitch */
        vTaskDelay(configTICK_RATE_HZ);
    }
}

/******************************************************************************
*
* Function Name: main
* Comments: main function, toggle LED and switch the blinking frequency by key.
*
******************************************************************************/
int main(void)
{
    /* Initialize board specified hardware. */
    hardware_init();

    Hw_Timer_Init();
    GPIO_Ctrl_Init();

    PRINTF("\n\r================= Blinking Demo ==================\n\r");

    /* Create a the APP main task. */
    xTaskCreate(ToggleTask, "Toggle Task", configMINIMAL_STACK_SIZE,
                NULL, tskIDLE_PRIORITY+1, NULL);
    xTaskCreate(SwitchTask, "Switch Task", configMINIMAL_STACK_SIZE,
                NULL, tskIDLE_PRIORITY+2, NULL);

    /* Start FreeRTOS scheduler. */
    vTaskStartScheduler();

    /* should never reach this point. */
    while (true);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
