/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
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

///////////////////////////////////////////////////////////////////////////////
//  Includes
///////////////////////////////////////////////////////////////////////////////
#include "FreeRTOS.h"
#include "stdlib.h"
#include "task.h"
#include "board.h"
#include "debug_console_imx.h"
#include "gpt_timer.h"
#include "lpm_mcore.h"
#if defined(__GNUC__)
#include <errno.h>
#include <stdio.h>
#endif

///////////////////////////////////////////////////////////////////////////////
//  Macros
///////////////////////////////////////////////////////////////////////////////
#define PERIOD_MIN                      15
#define PERIOD_MAX                      20

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

/*!
 * @brief Set random time gpt timer to wakeup the system
 */
static uint32_t gpt_set_ramdom_period(uint32_t min_s, uint32_t max_s)
{
    uint32_t delay_s, delta_s;
    /*Generate the random number*/
    if (max_s <= min_s)
        delay_s = min_s;
    else {
        delta_s = max_s - min_s;
        delay_s = rand() % delta_s + min_s;
    }

    /*Set the GPT with delay_s, Taks will blocks until GPT event happens*/
    GPT_Set_Timer_Delay(1000 * delay_s);
    return delay_s;
}

/*!
 * @brief the main power mode cycling task
 */
void LowPowerTask(void *pvParameters)
{
    uint32_t elapsed_time, total_time;
    char control_char;

    PRINTF("\r\nLow Power Demo\r\n");

    /*
     * Wait For A7 Side Become Ready
     */
    PRINTF("********************************\r\n");
    PRINTF("Please wait :\r\n");
    PRINTF("    1) A7 peer is ready\r\n");
    PRINTF("Then press \"S\" to start the demo\r\n");
    PRINTF("********************************\r\n");

    for (;;) {
        PRINTF("\r\nPress \"S\" to start the demo : ");
        control_char = GETCHAR();
        PRINTF("%c", control_char);
        if ((control_char == 's') || (control_char == 'S')) {
            break;
        }
    }
    PRINTF("\r\n");

    while (!LPM_MCORE_CheckPeerReady()) {
        /*
         * Note, when vTaskDelay is called, idle task hook function
         * get opportunity to run
         */
        vTaskDelay(5);
    }

    LPM_MCORE_RegisterWakeupInterrupt(BOARD_GPC_BASEADDR, BOARD_GPTA_IRQ_NUM, GPC_IRQ_WAKEUP_ENABLE);

    LPM_MCORE_SetSelfReady();

    total_time = 0;
    while(1)
    {
        switch (LPM_MCORE_GetPowerStatus(BOARD_GPC_BASEADDR)) {
            case LPM_M4_STATE_RUN:
                /*---> WAIT*/
                LPM_MCORE_ChangeM4Clock(LPM_M4_LOW_FREQ);
                LPM_MCORE_SetPowerStatus(BOARD_GPC_BASEADDR, LPM_M4_STATE_WAIT);
                break;
            case LPM_M4_STATE_WAIT:
                /*---> STOP*/
                LPM_MCORE_ChangeM4Clock(LPM_M4_LOW_FREQ);
                LPM_MCORE_SetPowerStatus(BOARD_GPC_BASEADDR, LPM_M4_STATE_STOP);
                break;
            case LPM_M4_STATE_STOP:
                /*---> RUN*/
                LPM_MCORE_ChangeM4Clock(LPM_M4_HIGH_FREQ);
                LPM_MCORE_SetPowerStatus(BOARD_GPC_BASEADDR, LPM_M4_STATE_RUN);
                break;
            default:
                break;
        }

        elapsed_time = gpt_set_ramdom_period(PERIOD_MIN, PERIOD_MAX);
        PRINTF("GPT will triggle interrupt in %ds\r\n", elapsed_time);

        PRINTF("go to mode %s\r\n", LPM_MCORE_GetPowerStatusString());

        /*wait GPT interrupt handler getting executed*/
        GPT_Wait_Timer_Expire();
        total_time += elapsed_time;
        PRINTF("GPT Event! Total time %ds\r\n", total_time);
    }
}

/*!
 * @brief Custom function to be run in idletask
 */
void vApplicationIdleHook(void)
{
    /* Waiting for Wake up event. */
    LPM_MCORE_WaitForInt();
}

/*!
 * @brief Main function
 */
int main(void)
{
    // Initialize demo application pins setting and clock setting.
    hardware_init();

    PRINTF(" ************************************************************************\r\n");
    PRINTF(" *          i.MX 7Dual Dual Core Low Power Demo - M4 side               *\r\n");
    PRINTF(" *                                                                      *\r\n");
    PRINTF(" *        A GPT will change the M4 Power Mode with random period        *\r\n");
    PRINTF(" *                                                                      *\r\n");
    PRINTF(" ************************************************************************\r\n");

    // Init the GPT Timer
    GPT_Timer_Init();

    // Low Power Management Initialization
    LPM_MCORE_Init(BOARD_GPC_BASEADDR);

    // Create a demo task which will demo M4 core cycling through different power modes.
    xTaskCreate(LowPowerTask, "Low Power Task", configMINIMAL_STACK_SIZE,           // xTaskGenericCreate
                NULL, tskIDLE_PRIORITY+1, NULL);

    // Start FreeRTOS scheduler.
    vTaskStartScheduler();

    // Should never reach this point.
    while (true);
}

#if defined(__GNUC__)
/*!
 * @brief Function to override ARMGCC default function _sbrk
 *
 * _sbrk is called by malloc. ARMGCC default _sbrk compares "SP" register and
 * heap end, if heap end is larger than "SP", then _sbrk returns error and
 * memory allocation failed. This function changes to compare __HeapLimit with
 * heap end.
 *
 * Then rand() function used in this project will call malloc in GCC compiler,
 * so the customized version of _sbrk is needed here
 */
caddr_t _sbrk(int incr)
{
    extern uint32_t end __asm("end");
    extern uint32_t heap_limit __asm("__HeapLimit");
    static uint32_t *heap_end;
    char *prev_heap_end;

    if (heap_end == NULL)
        heap_end = &end;

    prev_heap_end = (char*)heap_end;

    if (heap_end + incr > &heap_limit)
    {
        errno = ENOMEM;
        return (caddr_t)-1;
    }

    heap_end += incr;

    return (caddr_t)prev_heap_end;
}
#endif
/*******************************************************************************
 * EOF
 ******************************************************************************/
