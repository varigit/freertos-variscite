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
 *       rpmsg_rtos.h
 *
 * COMPONENT
 *
 *         OpenAMP stack.
 *
 * DESCRIPTION
 *
 * This file provides RTOS adaptation layer that allows:
 *  - handling of received messages outside the interrupt context
 *  - the implementation of blocking API for the RPMsg receive side
 *  - provides zero-copy receive functionality 
 *  - provides zero-copy send functionality 
 *
 * DATA STRUCTURES
 *
 *        none
 *
 * FUNCTIONS
 *
 *       rpmsg_rtos_init
 *       rpmsg_rtos_deinit
 *       rpmsg_rtos_create_ept
 *       rpmsg_rtos_destroy_ept
 *       rpmsg_rtos_recv
 *       rpmsg_rtos_recv_nocopy
 *       rpmsg_rtos_recv_nocopy_free
 *       rpmsg_rtos_alloc_tx_buffer
 *       rpmsg_rtos_send
 *       rpmsg_rtos_send_nocopy
 *
 **************************************************************************/
#ifndef __RPMSG_RTOS_H
#define __RPMSG_RTOS_H

#include "../rpmsg/rpmsg.h"

//! @addtogroup rpmsg_rtos
//! @{

/*!
 * @brief 
 * This function allocates and initializes the rpmsg driver resources for
 * given device ID (cpu id). The successful return from this function leaves
 * fully enabled IPC link. RTOS aware version.
 *
 * @param[in] dev_id    Remote device for which driver is to be initialized
 * @param[out] rdev     Pointer to newly created remote device
 * @param[in] role      Role of the other device, Master or Remote
 * @param[out] def_chnl Pointer to rpmsg channel
 *
 * @return Status of function execution
 *
 * @see rpmsg_rtos_deinit
 */
int rpmsg_rtos_init(int dev_id, struct remote_device **rdev, int role, struct rpmsg_channel **def_chnl);

/*!
 * @brief 
 * This function frees rpmsg driver resources for given remote device. RTOS aware version.
 *
 * @param[in] rdev Pointer to device to de-init
 * 
 * @see rpmsg_rtos_init
 */
void rpmsg_rtos_deinit(struct remote_device *rdev);

/*!
 * @brief 
 * This function creates rpmsg endpoint for the rpmsg channel. RTOS aware version.
 *
 * @param[in] rp_chnl Pointer to rpmsg channel
 * @param[in] addr    Endpoint src address
 *
 * @return Pointer to endpoint control block
 * 
 * @see rpmsg_rtos_destroy_ept
 */
struct rpmsg_endpoint * rpmsg_rtos_create_ept(struct rpmsg_channel *rp_chnl, unsigned long addr);

/*!
 * @brief 
 * This function deletes rpmsg endpoint and performs cleanup. RTOS aware version.
 *
 * @param[in] rp_ept Pointer to endpoint to destroy
 * 
 * @see rpmsg_rtos_create_ept
 */
void rpmsg_rtos_destroy_ept(struct rpmsg_endpoint *rp_ept);

/*!
 * @brief
 * RTOS receive function - blocking version of the received function that can be called from an RTOS task.
 * The data is copied from the receive buffer into the user supplied buffer.   
 *
 * This is the "receive with copy" version of the RPMsg receive function. This version is simple
 * to use but it requires copying data from shared memory into the user space buffer.
 * The user has no obligation or burden to manage the shared memory buffers.
 *  
 * @param[in] ept        Pointer to the RPMsg endpoint on which data is received
 * @param[in] data       Pointer to the user buffer the received data are copied to
 * @param[out] len       Pointer to an int variable that will contain the number of bytes actually copied into the buffer
 * @param[in] maxlen     Maximum number of bytes to copy (received buffer size)
 * @param[out] src       Pointer to address of the endpoint from which data is received
 * @param[in] timeout_ms Timeout, in milliseconds, to wait for a message. A value of 0 means don't wait (non-blocking call). 
 *                       A value of 0xffffffff means wait forever (blocking call). 
 *
 * @return Status of function execution
 * 
 * @see rpmsg_rtos_recv_nocopy
 */
int rpmsg_rtos_recv(struct rpmsg_endpoint *ept, void *data, int* len, int maxlen, unsigned long* src, int timeout_ms);

/*!
 * @brief 
 * RTOS receive function - blocking version of the received function that can be called from an RTOS task.
 * The data is NOT copied into the user-app. buffer.   
 *
 * This is the "zero-copy receive" version of the RPMsg receive function. No data is copied. 
 * Only the pointer to the data is returned. This version is fast, but it requires the user to manage
 * buffer allocation. Specifically, the user must decide when a buffer is no longer in use and
 * make the appropriate API call to free it, see rpmsg_rtos_recv_nocopy_free().
 * 
 * @param[in] ept        Pointer to the RPMsg endpoint on which data is received
 * @param[out] data      Pointer to the RPMsg buffer of the shared memory where the received data is stored
 * @param[out] len       Pointer to an int variable that that will contain the number of valid bytes in the RPMsg buffer
 * @param[out] src       Pointer to address of the endpoint from which data is received
 * @param[in] timeout_ms Timeout, in milliseconds, to wait for a message. A value of 0 means don't wait (non-blocking call). 
 *                       A value of 0xffffffff means wait forever (blocking call).
 *
 * @return Status of function execution
 * 
 * @see rpmsg_rtos_recv_nocopy_free
 * @see rpmsg_rtos_recv
 */
int rpmsg_rtos_recv_nocopy(struct rpmsg_endpoint *ept, void **data, int* len, unsigned long* src, int timeout_ms);

/*!
 * @brief This function frees a buffer previously returned by rpmsg_rtos_recv_nocopy().
 *  
 * Once the zero-copy mechanism of receiving data is used, this function
 * has to be called to free a buffer and to make it available for the next data
 * transfer.
 *  
 * @param[in] ept  Pointer to the RPMsg endpoint that has consumed received data
 * @param[in] data Pointer to the RPMsg buffer of the shared memory that has to be freed
 *
 * @return Status of function execution
 * 
 * @see rpmsg_rtos_recv_nocopy
 */
int rpmsg_rtos_recv_nocopy_free(struct rpmsg_endpoint *ept, void* data);

/*!
 * @brief Allocates the tx buffer for message payload.
 *
 * This API can only be called at process context to get the tx buffer in vring. By this way, the
 * application can directly put its message into the vring tx buffer without copy from an application buffer.
 * It is the application responsibility to correctly fill the allocated tx buffer by data and passing correct
 * parameters to the rpmsg_rtos_send_nocopy() function to perform data no-copy-send mechanism.
 *
 * @param[in] ept   Pointer to the RPMsg endpoint that requests tx buffer allocation
 * @param[out] size Pointer to store tx buffer size
 *
 * @return The tx buffer address on success and NULL on failure
 * 
 * @see rpmsg_rtos_send_nocopy
 */
void *rpmsg_rtos_alloc_tx_buffer(struct rpmsg_endpoint *ept, unsigned long *size);

/*!
 * @brief Sends a message across to the remote processor.
 *  
 * This function sends data of length len to the remote dst address.
 * In case there are no TX buffers available, the function will block until
 * one becomes available, or a timeout of 15 seconds elapses. When the latter
 * happens, -ERESTARTSYS is returned.
 *  
 * @param[in] ept  Pointer to the RPMsg endpoint
 * @param[in] data Pointer to the application buffer containing data to be sent
 * @param[in] len  Size of the data, in bytes, to transmit
 * @param[in] dst  Destination address of the message
 *
 * @return 0 on success and an appropriate error value on failure
 * 
 * @see rpmsg_rtos_send_nocopy
 */
int rpmsg_rtos_send(struct rpmsg_endpoint *ept, void *data, int len, unsigned long dst);

/*!
 * @brief Sends a message in tx buffer allocated by rpmsg_rtos_alloc_tx_buffer() 
 * to the remote processor.
 * 
 * This function sends txbuf of length len to the remote dst address.
 * The application has to take the responsibility for:
 *  1. tx buffer allocation (rpmsg_rtos_alloc_tx_buffer() )
 *  2. filling the data to be sent into the pre-allocated tx buffer
 *  3. not exceeding the buffer size when filling the data
 *  4. data cache coherency
 *
 * After the rpmsg_rtos_send_nocopy() function is issued the tx buffer is no more owned 
 * by the sending task and must not be touched anymore unless the rpmsg_rtos_send_nocopy() 
 * function fails and returns an error. In that case the application should try 
 * to re-issue the rpmsg_rtos_send_nocopy() again and if it is still not possible to send 
 * the message and the application wants to give it up from whatever reasons 
 * the rpmsg_rtos_recv_nocopy_free function could be called, 
 * passing the pointer to the tx buffer to be released as a parameter.     
 *
 * @param[in] ept   Pointer to the RPMsg endpoint
 * @param[in] txbuf Tx buffer with message filled
 * @param[in] len   Size of the data, in bytes, to transmit
 * @param[in] dst   Destination address of the message
 *
 * @return 0 on success and an appropriate error value on failure
 * 
 * @see rpmsg_rtos_alloc_tx_buffer
 * @see rpmsg_rtos_send
 */
int rpmsg_rtos_send_nocopy(struct rpmsg_endpoint *ept, void *txbuf, int len, unsigned long dst);

//! @}

#endif /* __RPMSG_RTOS_H */
