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
#include "board.h"
#include "debug_console_imx.h"
#include "flexcan.h"
#include "gpt.h"

#define NODE              1
#define TX_MSG_BUF_NUM    8
#define RX_MSG_BUF_NUM    9

#if (1 == NODE)
    #define TX_IDENTIFIER     0x123
    #define RX_IDENTIFIER     0x321
    #define GLOBAL_MASK       0x321
#else
    #define TX_IDENTIFIER     0x321
    #define RX_IDENTIFIER     0x123
    #define GLOBAL_MASK       0x123
#endif

////////////////////////////////////////////////////////////////////////////////
// Constant
////////////////////////////////////////////////////////////////////////////////
const flexcan_timing_t timing_table[] = {
    {7, 3, 7, 7, 6},  /* 125 kHz from 24 MHz OSC */
    {3, 3, 7, 7, 6},  /* 250 kHz from 24 MHz OSC */
    {1, 3, 7, 7, 6},  /* 500 kHz from 24 MHz OSC */
    {0, 3, 7, 7, 6},  /* 1   MHz from 24 MHz OSC */
};

////////////////////////////////////////////////////////////////////////////////
// Global
////////////////////////////////////////////////////////////////////////////////
volatile flexcan_msgbuf_t rxBuffer;
volatile bool rxCanReceive;
volatile flexcan_msgbuf_t *txMsgBufPtr;
volatile flexcan_msgbuf_t *rxMsgBufPtr;
volatile uint8_t data = 0;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void init_flexcan(void)
{
    flexcan_init_config_t initConfig = {
        .timing = timing_table[0],
        .operatingMode = flexcanNormalMode,
        .maxMsgBufNum  = 16
    };

    /* Initialize FlexCAN module. */
    FLEXCAN_Init(BOARD_FLEXCAN_BASEADDR, &initConfig);
    /* Enable FlexCAN Clock. */
    FLEXCAN_Enable(BOARD_FLEXCAN_BASEADDR);
    /* Set FlexCAN to use Global mask mode. */
    FLEXCAN_SetRxMaskMode(BOARD_FLEXCAN_BASEADDR, flexcanRxMaskGlobal);
    /* Set FlexCAN global mask. */
    FLEXCAN_SetRxGlobalMask(BOARD_FLEXCAN_BASEADDR, ~CAN_ID_STD(GLOBAL_MASK));

    /* Clear Tx and Rx message buffer interrupt pending bit. */
    FLEXCAN_ClearMsgBufStatusFlag(BOARD_FLEXCAN_BASEADDR, TX_MSG_BUF_NUM);
    FLEXCAN_ClearMsgBufStatusFlag(BOARD_FLEXCAN_BASEADDR, RX_MSG_BUF_NUM);
    /* Enable Tx and Rx message buffer interrupt. */
    FLEXCAN_SetMsgBufIntCmd(BOARD_FLEXCAN_BASEADDR, TX_MSG_BUF_NUM, true);
    FLEXCAN_SetMsgBufIntCmd(BOARD_FLEXCAN_BASEADDR, RX_MSG_BUF_NUM, true);

    /* Initialize Global variable. */
    rxCanReceive = false;
    txMsgBufPtr = FLEXCAN_GetMsgBufPtr(BOARD_FLEXCAN_BASEADDR, TX_MSG_BUF_NUM);
    rxMsgBufPtr = FLEXCAN_GetMsgBufPtr(BOARD_FLEXCAN_BASEADDR, RX_MSG_BUF_NUM);

    /* Setup Rx MsgBuf to receive Frame. */
    rxMsgBufPtr->idStd = RX_IDENTIFIER;
    rxMsgBufPtr->code  = flexcanRxEmpty;

    txMsgBufPtr->prio  = 0x0; /* We don't use local priority */
    txMsgBufPtr->idStd = TX_IDENTIFIER; /* Set Tx Identifier */
    txMsgBufPtr->idExt = 0x0; /* We don't use Extend Id. */
    txMsgBufPtr->dlc   = 0x1; /* Send only 1 byte data. */
    txMsgBufPtr->rtr   = 0x0; /* Send data frame. */
    txMsgBufPtr->ide   = 0x0; /* Frame format is standard. */
    txMsgBufPtr->srr   = 0x1; /* Don't care in standard id mode. */

    /* Set FlexCAN interrupt priority. */
    NVIC_SetPriority(BOARD_FLEXCAN_IRQ_NUM, 3);
    /* Enable FlexCAN interrupt. */
    NVIC_EnableIRQ(BOARD_FLEXCAN_IRQ_NUM);
}

void init_gpt(void)
{
    uint32_t freq;
    gpt_init_config_t config = {
        .freeRun     = false,
        .waitEnable  = true,
        .stopEnable  = true,
        .dozeEnable  = true,
        .dbgEnable   = false,
        .enableMode  = true
    };

    /* Initialize GPT module */
    GPT_Init(BOARD_GPTA_BASEADDR, &config);
    /* Set GPT clock source */
    GPT_SetClockSource(BOARD_GPTA_BASEADDR, gptClockSourceOsc);
    /* Divide GPTA osc clock source frequency by 2, and divide additional 2 inside GPT module  */
    GPT_SetOscPrescaler(BOARD_GPTA_BASEADDR, 1);
    GPT_SetPrescaler(BOARD_GPTA_BASEADDR, 1);

    /* Get GPT clock frequency */
    freq = 24000000/4; /* A is bound to OSC directly, with OSC divider 2 */
    /* Set both GPT modules to 1 second duration */
    GPT_SetOutputCompareValue(BOARD_GPTA_BASEADDR, gptOutputCompareChannel1, freq);
    /* Set GPT interrupt priority to same value to avoid handler preemption */
    NVIC_SetPriority(BOARD_GPTA_IRQ_NUM, 3);
    /* Enable NVIC interrupt */
    NVIC_EnableIRQ(BOARD_GPTA_IRQ_NUM);
    /* Enable GPT Output Compare1 interrupt */
    GPT_SetIntCmd(BOARD_GPTA_BASEADDR, gptStatusFlagOutputCompare1, true);
    /* GPT start */
    GPT_Enable(BOARD_GPTA_BASEADDR);
}

int main(void)
{
    /* Initialize board specified hardware. */
    hardware_init();

    PRINTF("\n\r********* FLEXCAN NETWORK TEST *********");
    PRINTF("\n\r   Message format: Standard (11 bit id)");
    PRINTF("\n\r   Message buffer %d used for Rx.", RX_MSG_BUF_NUM);
    PRINTF("\n\r   Message buffer %d used for Tx.", TX_MSG_BUF_NUM);
    PRINTF("\n\r   Interrupt Mode: Enabled");
    PRINTF("\n\r   Operating Mode: TX and RX --> Normal");
    PRINTF("\n\r****************************************\n\r");

    PRINTF("\n\r\n\rNODE is %d\n\r", NODE);

    init_flexcan();
    init_gpt();

    while (true)
    {
        if (rxCanReceive)
        {
            rxCanReceive = false;
            PRINTF("\r\n\r\nDLC=%d, mb_idx=0x%3x", rxBuffer.dlc, rxBuffer.idStd);
            PRINTF("\r\nRX MB data: 0x");
            for (uint8_t i = 0; i < rxBuffer.dlc; i++)
                PRINTF("%x ", *(&rxBuffer.data0 + i));
        }
    }
}

void BOARD_GPTA_HANDLER(void)
{
    GPT_ClearStatusFlag(BOARD_GPTA_BASEADDR, gptStatusFlagOutputCompare1);

    /* Prepare data for transmit */
    txMsgBufPtr->data0 = data; /* Load data to message buf. */
    txMsgBufPtr->code  = flexcanTxDataOrRemte; /* Start transmit. */
}

void BOARD_FLEXCAN_HANDLER(void)
{
    /* Solve Tx interrupt */
    if (FLEXCAN_GetMsgBufStatusFlag(BOARD_FLEXCAN_BASEADDR, TX_MSG_BUF_NUM))
    {
        FLEXCAN_ClearMsgBufStatusFlag(BOARD_FLEXCAN_BASEADDR, TX_MSG_BUF_NUM);
        data++;
    }

    /* Solve Rx interrupt */
    if (FLEXCAN_GetMsgBufStatusFlag(BOARD_FLEXCAN_BASEADDR, RX_MSG_BUF_NUM))
    {
        /* Lock message buffer for receive data. */
        FLEXCAN_LockRxMsgBuf(BOARD_FLEXCAN_BASEADDR, RX_MSG_BUF_NUM);
        rxBuffer = *rxMsgBufPtr;
        FLEXCAN_UnlockAllRxMsgBuf(BOARD_FLEXCAN_BASEADDR);

        FLEXCAN_ClearMsgBufStatusFlag(BOARD_FLEXCAN_BASEADDR, RX_MSG_BUF_NUM);

        rxCanReceive = true;
    }
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
