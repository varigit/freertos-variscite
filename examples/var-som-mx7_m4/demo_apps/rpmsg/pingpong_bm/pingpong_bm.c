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
#include <string.h>
#include "rpmsg/rpmsg.h"
#include "board.h"
#include "mu_imx.h"
#include "debug_console_imx.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////
/*
 * APP decided interrupt priority
 */
#define APP_MU_IRQ_PRIORITY 3

typedef struct the_message
{
   uint32_t  DATA;
} THE_MESSAGE, * THE_MESSAGE_PTR;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////
/* Globals */
static volatile struct rpmsg_channel *app_chnl;
static volatile int pingpong_finished = 0;
static THE_MESSAGE msg;

static void rpmsg_read_cb(struct rpmsg_channel *rp_chnl, void *data, int len,
                void * priv, unsigned long src)
{
    if(len > sizeof(THE_MESSAGE))
    {
        PRINTF("Received size %d exceed pingpong buffer size\r\n", len);
        return;
    }

    /* Drop extra message received after pingpong finished */
    if (pingpong_finished)
        return;

    /* Store received message to global buffer */
    memcpy(&msg, data, len);

    PRINTF("Get Data From Master Side : %d\r\n", msg.DATA);

    /* Send the message back to the remoteproc */
    msg.DATA++;
    rpmsg_send((struct rpmsg_channel *)app_chnl, &msg, sizeof(THE_MESSAGE));

    /* Set pingpong_finished to 1 per requirement */
}

/* rpmsg_rx_callback will call into this for a channel creation event*/
static void rpmsg_channel_created(struct rpmsg_channel *rp_chnl)
{
    /* We should give the created rp_chnl handler to app layer */
    app_chnl = rp_chnl;
    PRINTF("Name service handshake is done, M4 has setup a rpmsg channel [%d ---> %d]\r\n", app_chnl->src, app_chnl->dst);
}

static void rpmsg_channel_deleted(struct rpmsg_channel *rp_chnl)
{
}

/*
 * MU Interrrupt ISR
 */
void BOARD_MU_HANDLER(void)
{
    /*
     * calls into rpmsg_handler provided by middleware
     */
    rpmsg_handler();
}

/*!
 * @brief Main function
 */
int main (void)
{
    struct remote_device *rdev;

    hardware_init();

    /*
     * Prepare for the MU Interrupt
     *  MU must be initialized before rpmsg init is called
     */
    MU_Init(BOARD_MU_BASE_ADDR);
    NVIC_SetPriority(BOARD_MU_IRQ_NUM, APP_MU_IRQ_PRIORITY);
    NVIC_EnableIRQ(BOARD_MU_IRQ_NUM);

    /* Print the initial banner */
    PRINTF("\r\nRPMSG PingPong Bare Metal Demo...\r\n");

    /* RPMSG Init as REMOTE */
    PRINTF("RPMSG Init as Remote\r\n");
    rpmsg_init(0 /*REMOTE_CPU_ID*/, &rdev, rpmsg_channel_created, rpmsg_channel_deleted, rpmsg_read_cb, RPMSG_MASTER);

    /* wait until the pingpong demo finished */
    while (!pingpong_finished)
    {
    }

    PRINTF("\r\nMessage pingpong finished\r\n");

    rpmsg_deinit(rdev);

    return 0;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/

