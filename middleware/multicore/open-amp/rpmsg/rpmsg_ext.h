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
 *       rpmsg_ext.h
 *
 * COMPONENT
 *
 *         OpenAMP stack.
 *
 * DESCRIPTION
 *
 * This file provides RPMsg extension that allows:
 *  - allocation/release of the virtio tx buffer
 *  - zero-copy send functionality
 *
 * DATA STRUCTURES
 *
 *        none
 *
 * FUNCTIONS
 *
 *       rpmsg_hold_rx_buffer
 *       rpmsg_release_rx_buffer
 *       rpmsg_alloc_tx_buffer
 *       rpmsg_sendto_nocopy
 *       rpmsg_send_nocopy
 *
 **************************************************************************/
#ifndef _RPMSG_EXT_H_
#define _RPMSG_EXT_H_

#include "../rpmsg/rpmsg.h"

//! @addtogroup rpmsg_ext
//! @{

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
void rpmsg_hold_rx_buffer(struct rpmsg_channel *rpdev, void *rxbuf);

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
void rpmsg_release_rx_buffer(struct rpmsg_channel *rpdev, void *rxbuf);

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
void *rpmsg_alloc_tx_buffer(struct rpmsg_channel *rpdev, unsigned long *size, int wait);

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
                                    void *txbuf, int len);

/*!
 * @brief Sends a message in tx buffer allocated by rpmsg_alloc_tx_buffer()
 * across to the remote processor, specify dst.
 * 
 * This function sends txbuf of length len to the remote dst address.
 * The message will be sent to the remote processor which the rpdev
 * channel belongs to, using rpdev's source address.
 * The application has to take the responsibility for:
 *  1. tx buffer allocation (rpmsg_alloc_tx_buffer() )
 *  2. filling the data to be sent into the pre-allocated tx buffer
 *  3. not exceeding the buffer size when filling the data
 *  4. data cache coherency
 *
 * After the rpmsg_sendto_nocopy() function is issued the tx buffer is no more owned 
 * by the sending task and must not be touched anymore unless the rpmsg_sendto_nocopy() 
 * function fails and returns an error. In that case the application should try 
 * to re-issue the rpmsg_sendto_nocopy() again and if it is still not possible to send 
 * the message and the application wants to give it up from whatever reasons 
 * the rpmsg_release_rx_buffer function could be called, 
 * passing the pointer to the tx buffer to be released as a parameter.     
 *
 * @param[in] rpdev The rpmsg channel
 * @param[in] txbuf TX buffer with message filled
 * @param[in] len   Length of payload
 * @param[in] dst   Destination address
 *
 * @return 0 on success and an appropriate error value on failure
 * 
 * @see rpmsg_alloc_tx_buffer
 * @see rpmsg_send_offchannel_nocopy
 * @see rpmsg_send_nocopy
 */
static inline
int rpmsg_sendto_nocopy(struct rpmsg_channel *rpdev, void *txbuf, int len, unsigned long dst)
{
    return rpmsg_send_offchannel_nocopy(rpdev, rpdev->src, dst, txbuf, len);
}

/*!
 * @brief Sends a message in tx buffer allocated by rpmsg_alloc_tx_buffer()
 * across to the remote processor.
 *
 * This function sends txbuf of length len on the rpdev channel.
 * The message will be sent to the remote processor which the rpdev
 * channel belongs to, using rpdev's source and destination addresses.
 * The application has to take the responsibility for:
 *  1. tx buffer allocation (rpmsg_alloc_tx_buffer() )
 *  2. filling the data to be sent into the pre-allocated tx buffer
 *  3. not exceeding the buffer size when filling the data
 *  4. data cache coherency
 *
 * After the rpmsg_send_nocopy() function is issued the tx buffer is no more owned 
 * by the sending task and must not be touched anymore unless the rpmsg_send_nocopy() 
 * function fails and returns an error. In that case the application should try 
 * to re-issue the rpmsg_send_nocopy() again and if it is still not possible to send 
 * the message and the application wants to give it up from whatever reasons 
 * the rpmsg_release_rx_buffer function could be called, 
 * passing the pointer to the tx buffer to be released as a parameter.     
 * 
 * @param[in] rpdev The rpmsg channel
 * @param[in] txbuf TX buffer with message filled
 * @param[in] len   Length of payload
 *
 * @return 0 on success and an appropriate error value on failure
 * 
 * @see rpmsg_alloc_tx_buffer
 * @see rpmsg_send_offchannel_nocopy
 * @see rpmsg_sendto_nocopy
 */
static inline
int rpmsg_send_nocopy(struct rpmsg_channel *rpdev, void *txbuf, int len)
{
    return rpmsg_send_offchannel_nocopy(rpdev, rpdev->src, rpdev->dst, txbuf, len);
}

//! @}


#endif /* _RPMSG_EXT_H_ */
