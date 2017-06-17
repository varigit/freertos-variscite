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

///////////////////////////////////////////////////////////////////////////////
//  Includes
///////////////////////////////////////////////////////////////////////////////
#include "FreeRTOS.h"
#include "task.h"
#include "board.h"
#include "debug_console_imx.h"
#include "sema4_mutex.h"

#define SEMA4_DEMO_GATE        (3)

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////
static void Sema4Test()
{
    SEMA4_Mutex_Lock(SEMA4_DEMO_GATE);
    PRINTF("\n\r...SEMA4 mutex lock successfully!\n\r");
    SEMA4_Mutex_Unlock(SEMA4_DEMO_GATE);
}

/*!
 * @brief A basic user-defined task
 */
void Sema4Task(void *pvParameters)
{
    uint8_t receiveBuff;

    // Print the initial banner
    PRINTF("================== SEMA4 demo ==================\n\r");

    while(1)
    {
        // Main routine that triggers a SEMA4 lock
        PRINTF("Enter command:\n\r");
        PRINTF("----- 'm' to manually trigger a SEMA4 lock\n\r");
        PRINTF("----- 'a' to automatically trigger SEMA4 lock every 5 seconds\n\r");

        // First, get character
        receiveBuff = GETCHAR();
        // Now echo the received character
        PUTCHAR(receiveBuff);

        if (receiveBuff == 'm')
        {
            Sema4Test();
        }
        else if (receiveBuff == 'a')
        {
            while (true)
            {
                Sema4Test();
                PRINTF("Wait for 5 seconds......\n\r");
                vTaskDelay(5 * configTICK_RATE_HZ);
            }
        }
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    // Initialize demo application pins setting and clock setting.
    hardware_init();

    // Initialize SEMA4 mutex gate and reset
    SEMA4_Mutex_Init(SEMA4_DEMO_GATE, true);

    // Create a demo task.
    xTaskCreate(Sema4Task, "SEMA4 Task", configMINIMAL_STACK_SIZE,
                NULL, tskIDLE_PRIORITY+1, NULL);

    // Start FreeRTOS scheduler.
    vTaskStartScheduler();

    // Should never reach this point.
    while (true);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
