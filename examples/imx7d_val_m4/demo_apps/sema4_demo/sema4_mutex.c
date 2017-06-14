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
#include "task.h"
#include "board.h"
#include "sema4_mutex.h"
#include "sema4.h"
#include "debug_console_imx.h"

static SemaphoreHandle_t xSemaphore[16];
static uint32_t recursiveDepth[16];
static bool nvicInit;

void SEMA4_Mutex_Init(uint32_t gate, bool reset)
{
    assert(gate < 16);
    assert(!xSemaphore[gate]);

    /* We use counting semaphore because the sequence of take/give could not
     * be guarenteed. */
    xSemaphore[gate] = xSemaphoreCreateCounting(1, 0);

    /* Reset the gate when required */
    if (reset)
    {
        SEMA4_ResetGate(BOARD_SEMA4_BASEADDR, gate);
        SEMA4_ResetNotification(BOARD_SEMA4_BASEADDR, gate);
    }

    /* NVIC initialize */
    if (!nvicInit)
    {
        NVIC_SetPriority(BOARD_SEMA4_IRQ_NUM, 3);
        NVIC_EnableIRQ(BOARD_SEMA4_IRQ_NUM);
        nvicInit = true;
    }
}

void SEMA4_Mutex_Lock(uint32_t gate)
{
    bool locked = false;

    assert(gate < 16);

    /* If already locked by this processor, just add recursive depth */
    if (SEMA4_GetLockProcessor(BOARD_SEMA4_BASEADDR, gate) == SEMA4_PROCESSOR_SELF)
    {
        recursiveDepth[gate]++;
        return;
    }

    while (true)
    {
        /* Critical section with ISR */
        taskDISABLE_INTERRUPTS();

        /* Enable unlock interrupt of this gate */
        SEMA4_SetIntCmd(BOARD_SEMA4_BASEADDR, SEMA4_GATE_STATUS_FLAG(gate), true);
        if (SEMA4_TryLock(BOARD_SEMA4_BASEADDR, gate) == statusSema4Success)
        {
            recursiveDepth[gate]++;
            /* Got the SEMA4, unlock interrupt is not needed any more */
            SEMA4_SetIntCmd(BOARD_SEMA4_BASEADDR, SEMA4_GATE_STATUS_FLAG(gate), false);
            locked = true;
        }

        taskENABLE_INTERRUPTS();

        if (locked)
            break;
        else
        {
            PRINTF("\n\r...Lock pending, waiting for the other core unlock the gate\n\r");
            /* Wait for unlock interrupt */
            xSemaphoreTake(xSemaphore[gate], portMAX_DELAY);
            /* Got the unlock event, indicating the interrupt was disabled in ISR */
        }
    }
}

void SEMA4_Mutex_Unlock(uint32_t gate)
{
    if ((--recursiveDepth[gate]) == 0)
        SEMA4_Unlock(BOARD_SEMA4_BASEADDR, gate);
}

void BOARD_SEMA4_HANDLER()
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uint32_t i;
    uint16_t flag;

    for (i = 0; i < 16; i++)
    {
        flag = SEMA4_GATE_STATUS_FLAG(i);
        if (xSemaphore[i] && SEMA4_GetIntEnabled(BOARD_SEMA4_BASEADDR, flag) &&
            SEMA4_GetStatusFlag(BOARD_SEMA4_BASEADDR, flag))
        {
            /* Because the status cannot be cleared manually, we have to disable the gate's
             * interrupt to avoid endlessly going into ISR */
            SEMA4_SetIntCmd(BOARD_SEMA4_BASEADDR, flag, false);

            /* Unlock the task to process the event. */
            xSemaphoreGiveFromISR(xSemaphore[i], &xHigherPriorityTaskWoken);

            /* Perform a context switch to wake the higher priority task. */
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
    }
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
