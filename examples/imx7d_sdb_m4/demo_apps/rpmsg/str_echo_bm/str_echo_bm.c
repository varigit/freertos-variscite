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

#include "rpmsg/rpmsg_ext.h"
#include "string.h"
#include "assert.h"
#include "board.h"
#include "mu_imx.h"
#include "debug_console_imx.h"

/*
 * APP decided interrupt priority
 */
#define APP_MU_IRQ_PRIORITY 3

/*
 * For the most worst case, master will send 3 consecutive messages which remote
 * do not process.
 * The synchronization between remote and master is that each time endpoint callback
 * is called, the MU Receive interrupt is temperorily disabled. Until the next time
 * remote consumes the message, the interrupt will not be enabled again.
 * When the interrupt is not enabled, Master can not send the notify, it will blocks
 * there and can not send further message.
 * In the worst case, master send the first message, it triggles the ISR in remote
 * side, remote ISR clear the MU status bit so master can send the second message
 * and notify again, master can continue to send the 3rd message but will blocks
 * when trying to notify. Meanwhile, remote side is still in the first ISR which
 * has a loop to receive all the 3 messages.
 * Master is blocked and can not send the 4th message, remote side ISR stores all
 * this 3 messages to app buffer and informs the app layer to consume them. After
 * 3 messages are consumed, the ISR is enabled again and the second notify is received.
 * This unblocks the master to complete the 3rd notify and send the 4th message.
 * The situation goes on and we can see application layer need a maximum size 3
 * buffer to hold the unconsumed messages. STRING_BUFFER_CNT is therefore set to 3
 */
#define STRING_BUFFER_CNT 3

typedef struct
{
    unsigned long src;
    void* data;
    int len;
} app_message_t;

/* Globals */
static struct rpmsg_channel *app_chnl = NULL;
static app_message_t app_msg[STRING_BUFFER_CNT];
static char app_buf[512]; /* Each RPMSG buffer can carry less than 512 payload */
static uint8_t app_idx = 0;
static uint8_t handler_idx = 0;
static volatile int32_t msg_count = 0;

static void rpmsg_enable_rx_int(bool enable)
{
    if (enable)
    {
        if ((--msg_count) == 0)
            MU_EnableRxFullInt(MUB, RPMSG_MU_CHANNEL);
    }
    else
    {
        if ((msg_count++) == 0)
            MU_DisableRxFullInt(MUB, RPMSG_MU_CHANNEL);
    }
}

static void rpmsg_read_cb(struct rpmsg_channel *rp_chnl, void *data, int len,
                void * priv, unsigned long src)
{
    /*
     * Temperorily Disable MU Receive Interrupt to avoid master
     * sending too many messages and remote will fail to keep pace
     * to consume (flow control)
     */
    rpmsg_enable_rx_int(false);

    /* Hold the RPMsg rx buffer to be used in main loop */
    rpmsg_hold_rx_buffer(rp_chnl, data);
    app_msg[handler_idx].src = src;
    app_msg[handler_idx].data = data;
    app_msg[handler_idx].len = len;

    /* Move to next free message index */
    handler_idx = (handler_idx + 1) % STRING_BUFFER_CNT;
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
int main(void)
{
    struct remote_device *rdev;
    int len;
    void *tx_buf;
    unsigned long size;

    hardware_init();

    /*
     * Prepare for the MU Interrupt
     *  MU must be initialized before rpmsg init is called
     */
    MU_Init(BOARD_MU_BASE_ADDR);
    NVIC_SetPriority(BOARD_MU_IRQ_NUM, APP_MU_IRQ_PRIORITY);
    NVIC_EnableIRQ(BOARD_MU_IRQ_NUM);

    /* Print the initial banner */
    PRINTF("\r\nRPMSG String Echo Bare Metal Demo...\r\n");

    /* RPMSG Init as REMOTE */
    PRINTF("RPMSG Init as Remote\r\n");
    rpmsg_init(0, &rdev, rpmsg_channel_created, rpmsg_channel_deleted, rpmsg_read_cb, RPMSG_MASTER);

    /*
     * str_echo demo loop
     */
    for (;;)
    {
        /* Wait message to be available */
        while (msg_count == 0)
	{
	}

        /* Copy string from RPMsg rx buffer */
        len = app_msg[app_idx].len;
        assert(len < sizeof(app_buf));
        memcpy(app_buf, app_msg[app_idx].data, len);
        app_buf[len] = 0; /* End string by '\0' */

        if ((len == 2) && (app_buf[0] == 0xd) && (app_buf[1] == 0xa))
            PRINTF("Get New Line From Master Side From Slot %d\r\n", app_idx);
        else
            PRINTF("Get Message From Master Side : \"%s\" [len : %d] from slot %d\r\n", app_buf, len, app_idx);

        /* Get tx buffer from RPMsg */
        tx_buf = rpmsg_alloc_tx_buffer(app_chnl, &size, RPMSG_TRUE);
        assert(tx_buf);
        /* Copy string to RPMsg tx buffer */
        memcpy(tx_buf, app_buf, len);
        /* Echo back received message with nocopy send */
        rpmsg_sendto_nocopy(app_chnl, tx_buf, len, app_msg[app_idx].src);

        /* Release held RPMsg rx buffer */
        rpmsg_release_rx_buffer(app_chnl, app_msg[app_idx].data);
        app_idx = (app_idx + 1) % STRING_BUFFER_CNT;

        /* Once a message is consumed, minus the msg_count and might enable MU interrupt again */
        rpmsg_enable_rx_int(true);
    }
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
