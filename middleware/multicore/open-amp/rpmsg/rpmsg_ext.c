/*
 * Copyright (c) 2015 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of Freescale Semiconductor nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/**************************************************************************
 * FILE NAME
 *
 *       rpmsg_ext.c
 *
 * COMPONENT
 *
 *       OpenAMP
 *
 * DESCRIPTION
 *
 * Main file for the RPMSG driver extension. This file implements APIs for
 * achieving zero copy received message process and zero copy message
 * transmission.
 *
 **************************************************************************/
#include "rpmsg_ext.h"

/*!
 * @brief Holds the rx buffer for usage outside the receive callback.
 * 
 * Calling this function prevents the RPMsg receive buffer from being released back to the pool
 * of shmem buffers. This API can only be called at rx callback context (rpmsg_rx_cb_t). With this API, 
 * the application doesn't need to copy the message in rx callback. Instead, the rx buffer base address
 * is saved in application context and further processed in application process. After the message
 * is processed, the application can release the rx buffer for future reuse in vring by calling the
 * rpmsg_release_rx_buffer() function.
 * 
 * @param[in] rpdev The rpmsg channel
 * @param[in] rxbuf RX buffer with message payload
 * 
 * @see rpmsg_release_rx_buffer
*/
void rpmsg_hold_rx_buffer(struct rpmsg_channel *rpdev, void *rxbuf) {
    struct rpmsg_hdr *rp_hdr = NULL;
    if (!rpdev || !rxbuf)
        return;

    rp_hdr = RPMSG_HDR_FROM_BUF(rxbuf);

    /* set held status to keep buffer */
    rp_hdr->reserved |= RPMSG_BUF_HELD;
}

/*!
 * @brief Releases the rx buffer for future reuse in vring.
 * 
 * This API can be called at process context when the message in rx buffer is processed.
 * 
 * @param rpdev - the rpmsg channel
 * @param rxbuf - rx buffer with message payload
 * 
 * @see rpmsg_hold_rx_buffer
 */
void rpmsg_release_rx_buffer(struct rpmsg_channel *rpdev, void *rxbuf) {
    struct rpmsg_hdr *hdr;
    struct remote_device *rdev;
    struct rpmsg_hdr_reserved * reserved = NULL;

    if (!rpdev || !rxbuf)
        return;

    rdev = rpdev->rdev;
    hdr = RPMSG_HDR_FROM_BUF(rxbuf);

    /* Get the pointer to the reserved field that contains buffer size and the index */
    reserved = (struct rpmsg_hdr_reserved*)&hdr->reserved;

    env_lock_mutex(rdev->lock);

    /* Return used buffer, with total length (header length + buffer size). */
    rpmsg_return_buffer(rdev, hdr, (unsigned long)reserved->totlen, reserved->idx);

    env_unlock_mutex(rdev->lock);
}

/*!
 * @brief Allocates the tx buffer for message payload.
 *
 * This API can only be called at process context to get the tx buffer in vring. By this way, the
 * application can directly put its message into the vring tx buffer without copy from an application buffer.
 * It is the application responsibility to correctly fill the allocated tx buffer by data and passing correct
 * parameters to the rpmsg_send_nocopy() or rpmsg_sendto_nocopy() function to perform data no-copy-send mechanism.
 *
 * @param[in] rpdev Pointer to rpmsg channel
 * @param[in] size  Pointer to store tx buffer size
 * @param[in] wait  Boolean, wait or not for buffer to become available
 *
 * @return The tx buffer address on success and NULL on failure
 * 
 * @see rpmsg_send_offchannel_nocopy
 * @see rpmsg_sendto_nocopy
 * @see rpmsg_send_nocopy
 */
void *rpmsg_alloc_tx_buffer(struct rpmsg_channel *rpdev, unsigned long *size, int wait) {
    struct rpmsg_hdr *hdr;
    struct remote_device *rdev;
    unsigned short idx;
    int buff_len, tick_count = 0;

    if (!rpdev || !size)
        return NULL;

    rdev = rpdev->rdev;

    env_lock_mutex(rdev->lock);

    /* Get tx buffer from vring */
    hdr = (struct rpmsg_hdr *) rpmsg_get_tx_buffer(rdev, &buff_len, &idx);

    env_unlock_mutex(rdev->lock);

    if (!hdr && !wait) {
        return NULL;
    } else {
        while (!hdr) {
            /*
             * Wait parameter is true - pool the buffer for
             * 15 secs as defined by the APIs.
             */
            env_sleep_msec(RPMSG_TICKS_PER_INTERVAL);
            env_lock_mutex(rdev->lock);
            hdr = (struct rpmsg_hdr *) rpmsg_get_tx_buffer(rdev, &buff_len, &idx);
            env_unlock_mutex(rdev->lock);
            tick_count += RPMSG_TICKS_PER_INTERVAL;
            if (tick_count >= (RPMSG_TICK_COUNT / RPMSG_TICKS_PER_INTERVAL)) {
                return NULL;
            }
        }

        /* Store buffer size and the index into the reserved field to be used when sending */
        ((struct rpmsg_hdr_reserved*)&hdr->reserved)->idx = idx;
        ((struct rpmsg_hdr_reserved*)&hdr->reserved)->totlen = buff_len;

        /* Actual data buffer size is vring buffer size minus rpmsg header length */
        *size = buff_len - offsetof(struct rpmsg_hdr, data);
        return hdr->data;
    }
}

/*!
 * @brief Sends a message in tx buffer allocated by rpmsg_alloc_tx_buffer() 
 * using explicit src/dst addresses.
 * 
 * This function sends txbuf of length len to the remote dst address,
 * and uses src as the source address.
 * The message will be sent to the remote processor which the rpdev
 * channel belongs to.
 * The application has to take the responsibility for:
 *  1. tx buffer allocation (rpmsg_alloc_tx_buffer() )
 *  2. filling the data to be sent into the pre-allocated tx buffer
 *  3. not exceeding the buffer size when filling the data
 *  4. data cache coherency
 *
 * After the rpmsg_send_offchannel_nocopy() function is issued the tx buffer is no more owned 
 * by the sending task and must not be touched anymore unless the rpmsg_send_offchannel_nocopy() 
 * function fails and returns an error. In that case the application should try 
 * to re-issue the rpmsg_send_offchannel_nocopy() again and if it is still not possible to send 
 * the message and the application wants to give it up from whatever reasons 
 * the rpmsg_release_rx_buffer function could be called, 
 * passing the pointer to the tx buffer to be released as a parameter.     
 *
 * @param[in] rpdev The rpmsg channel
 * @param[in] src   Source address
 * @param[in] dst   Destination address
 * @param[in] txbuf TX buffer with message filled
 * @param[in] len   Length of payload
 *
 * @return 0 on success and an appropriate error value on failure
 * 
 * @see rpmsg_alloc_tx_buffer
 * @see rpmsg_sendto_nocopy
 * @see rpmsg_send_nocopy
 */
int rpmsg_send_offchannel_nocopy(struct rpmsg_channel *rpdev, unsigned long src, unsigned long dst,
                                    void *txbuf, int len) {
    struct rpmsg_hdr *hdr;
    struct remote_device *rdev;
    struct rpmsg_hdr_reserved * reserved = NULL;
    int status;

    if (!rpdev || !txbuf)
        return RPMSG_ERR_PARAM;

    rdev = rpdev->rdev;
    hdr = RPMSG_HDR_FROM_BUF(txbuf);

    /* Initialize RPMSG header. */
    hdr->dst = dst;
    hdr->src = src;
    hdr->len = len;
    hdr->flags = 0;

    /* Get the pointer to the reserved field that contains buffer size and the index */
    reserved = (struct rpmsg_hdr_reserved*)&hdr->reserved;

    env_lock_mutex(rdev->lock);

    status = rpmsg_enqueue_buffer(rdev, hdr, (unsigned long)reserved->totlen, reserved->idx);
    if (status == RPMSG_SUCCESS) {
        /* Let the other side know that there is a job to process. */
        virtqueue_kick(rdev->tvq);
    }

    env_unlock_mutex(rdev->lock);

    return status;
}
