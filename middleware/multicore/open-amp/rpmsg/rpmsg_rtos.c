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
 *       rpmsg_rtos.c
 *
 * COMPONENT
 *
 *       OpenAMP
 *
 * DESCRIPTION
 *
 * This file provides RTOS adaptation layer that allows:
 *  - handling of received messages outside the interrupt context
 *  - the implementation of blocking API for the RPMsg receive side
 *  - provides zero-copy receive functionality 
 *  - provides zero-copy send functionality 
 *
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include "rpmsg.h"
#include "rpmsg_ext.h"
#include "rpmsg_rtos.h"

#define RPMSG_RECV_NOCOPY_CHECK_PTRS (0)

typedef struct
{
    unsigned long src;
    void* data;
    short int len;
} rpmsg_callback_message_t;

#if RPMSG_RECV_NOCOPY_CHECK_PTRS

typedef struct rpmsg_ptr_llist
{
    void* ptr;
    struct rpmsg_ptr_llist* next;

} rpmsg_ptr_llist_t;

static rpmsg_ptr_llist_t* rpmsg_in_app_buffers_head = NULL;
static rpmsg_ptr_llist_t* rpmsg_in_app_buffers_tail = NULL;

#endif

static struct rpmsg_channel *default_chnl = NULL;
static void *default_q = NULL;
static void *callback_sync = NULL;
static int   rpmsg_queue_size;

extern int platform_get_processor_info(struct hil_proc *proc, int cpu_id);

/* This callback gets invoked when the remote chanl is created */
static void rpmsg_channel_created_rtos(struct rpmsg_channel *rp_chnl) 
{
    assert(rp_chnl && rp_chnl->rp_ept);
    /* message queue for channel default endpoint should be available */
    assert(default_q);
    rp_chnl->rp_ept->priv = default_q;

    default_chnl = rp_chnl;

    /* Unblock the task by releasing the semaphore. */
    env_release_sync_lock(callback_sync);
}

/* This callback gets invoked when the remote channel is deleted */
static void rpmsg_channel_deleted_rtos(struct rpmsg_channel *rp_chnl) 
{
    assert(rp_chnl);

    default_chnl = NULL;
}

/**
 * rpmsg_read_rtos_cb
 *
 * This is the RPMsg receive callback function used in an RTOS environment.   
 *
 * @param rp_chnl - pointer to the RPMsg channel on which data is received
 * @param data - pointer to the buffer containing received data
 * @param len -  size of data received, in bytes
 * @param priv - private data provided during endpoint creation
 * @param src - pointer to address of the endpoint from which data is received
 *
 * @return void
 */
static void rpmsg_read_rtos_cb(struct rpmsg_channel *rp_chnl, void *data, int len,
                void * priv, unsigned long src) 
{
    rpmsg_callback_message_t msg;

    assert(priv);
    assert(rp_chnl);

    msg.data = data;
    msg.len = len;
    msg.src = src;

    /* if message is successfully added into queue then hold rpmsg buffer */
    if(env_put_queue(priv, &msg, 0))
    {
        /* hold the rx buffer */
        rpmsg_hold_rx_buffer(rp_chnl, data);
    }
}

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
int rpmsg_rtos_init(int dev_id, struct remote_device **rdev, int role, struct rpmsg_channel **def_chnl) 
{
    int status;
    struct hil_proc proc;

    /* single instance allowed! */
    if(callback_sync != NULL)
    {
        return RPMSG_ERR_NO_MEM; 
    }

    /* get HW specific info */
    status = platform_get_processor_info(&proc, dev_id);
    if(status)
    {
        return RPMSG_ERR_DEV_ID;
    }

    /* create synchronization object used during the initialization process */
    status = env_create_sync_lock(&callback_sync, 0);
    if((status) || (callback_sync == NULL))
    {
        return RPMSG_ERR_NO_MEM;
    }

    /* get rpmsg vring rx buffer count */
    rpmsg_queue_size = role == RPMSG_MASTER ? proc.vdev.vring_info[1].num_descs : proc.vdev.vring_info[0].num_descs;
    /* create message queue for channel default endpoint */
    status = env_create_queue(&default_q, rpmsg_queue_size, sizeof(rpmsg_callback_message_t));
    if((status) || (default_q == NULL))
    {
        env_delete_sync_lock(callback_sync);
        return RPMSG_ERR_NO_MEM;
    }

#if RPMSG_RECV_NOCOPY_CHECK_PTRS
    rpmsg_in_app_buffers_head = (rpmsg_ptr_llist_t*)env_allocate_memory(sizeof(rpmsg_ptr_llist_t));
    assert(rpmsg_in_app_buffers_head != NULL);
    memset((void*)rpmsg_in_app_buffers_head, 0, sizeof(rpmsg_ptr_llist_t));
    rpmsg_in_app_buffers_tail = rpmsg_in_app_buffers_head;
#endif

    /* initialize the RPMsg communication */
    status = rpmsg_init(dev_id, rdev, rpmsg_channel_created_rtos, rpmsg_channel_deleted_rtos, rpmsg_read_rtos_cb, role);

     /* wait until the channel is established (rpmsg_channel_created callback is issued) */ 
    env_acquire_sync_lock(callback_sync);

    /* delete synchronization object used during the initialization process */
    env_delete_sync_lock(callback_sync);
    callback_sync = NULL;

    if(default_chnl == NULL) 
    {
        return RPMSG_ERR_NO_MEM;
    }
    else
    {
        *def_chnl = default_chnl;
        return status;
    }
}

/*!
 * @brief 
 * This function frees rpmsg driver resources for given remote device. RTOS aware version.
 *
 * @param[in] rdev Pointer to device to de-init
 * 
 * @see rpmsg_rtos_init
 */
void rpmsg_rtos_deinit(struct remote_device *rdev) 
{
    assert(rdev != NULL);

#if RPMSG_RECV_NOCOPY_CHECK_PTRS
    rpmsg_ptr_llist_t * iterator = NULL;
    rpmsg_ptr_llist_t * next = NULL;

    env_lock_mutex(rdev->lock);

    assert(rpmsg_in_app_buffers_head != NULL);

    for(iterator = rpmsg_in_app_buffers_head; iterator != NULL; iterator = next)
    {
        next = iterator->next;     
        env_free_memory((void*)iterator);   
    }
    
    rpmsg_in_app_buffers_head = NULL;
    rpmsg_in_app_buffers_tail = NULL;
    
    env_unlock_mutex(rdev->lock);
#endif
    /* de-initialize the RPMsg communication */
    rpmsg_deinit(rdev);

    /* delete message queue used by the channel default endpoint */
    if (default_q)
    {
        env_delete_queue(default_q);
        default_q = NULL;
    }
}

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
struct rpmsg_endpoint * rpmsg_rtos_create_ept(struct rpmsg_channel *rp_chnl, unsigned long addr)
{
    struct rpmsg_endpoint * retval;
    void *q = NULL;

    if (!rp_chnl) return NULL;
    if (!rp_chnl->rdev) return NULL;

    /* create message queue for the specified endpoint */
    env_create_queue(&q, rpmsg_queue_size, sizeof(rpmsg_callback_message_t));
    if(q == NULL)
    {
        return NULL;
    }

    /* create the RPMsg endpoint */
    retval = rpmsg_create_ept(rp_chnl, rpmsg_read_rtos_cb, (void*)q, addr);

    if(retval == NULL)
    {
        env_delete_queue(q);
        return NULL;
    }
    else
    {
        return retval;
    }
}

/*!
 * @brief 
 * This function deletes rpmsg endpoint and performs cleanup. RTOS aware version.
 *
 * @param[in] rp_ept Pointer to endpoint to destroy
 * 
 * @see rpmsg_rtos_create_ept
 */
void rpmsg_rtos_destroy_ept(struct rpmsg_endpoint *rp_ept)
{
    void *q = rp_ept->priv;

    /* delete the RPMsg endpoint */
    rpmsg_destroy_ept(rp_ept);

    /* delete message queue used by the specified endpoint */
    env_delete_queue(q);
}

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
int rpmsg_rtos_recv(struct rpmsg_endpoint *ept, void *data, int* len, int maxlen, unsigned long* src, int timeout_ms)
{
    rpmsg_callback_message_t msg;
    int retval = RPMSG_SUCCESS;

    if (!data) return RPMSG_ERR_PARAM;
    if (!ept) return RPMSG_ERR_PARAM;
    if (!ept->rp_chnl) return RPMSG_ERR_PARAM;
    if (!ept->rp_chnl->rdev) return RPMSG_ERR_PARAM;

    /* Get an element out of the message queue for the selected endpoint */
    if(env_get_queue(ept->priv, &msg, timeout_ms))
    {
        if(src != NULL) *src = msg.src;
        if(len != NULL) *len = msg.len;

        if(maxlen >= msg.len)
        {
            memcpy(data, msg.data, maxlen);
        }
        else
        {
            retval = RPMSG_ERR_BUFF_SIZE;
        }

        /* Return used buffers. */
        rpmsg_release_rx_buffer(ept->rp_chnl, msg.data);

        return retval;
    }
    else
    {
        return RPMSG_ERR_NO_BUFF; /* failed */
    }
}

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
int rpmsg_rtos_recv_nocopy(struct rpmsg_endpoint *ept, void **data, int* len, unsigned long* src, int timeout_ms)
{
    rpmsg_callback_message_t msg;

    if (!data) return RPMSG_ERR_PARAM;
    if (!ept) return RPMSG_ERR_PARAM;
    if (!ept->rp_chnl) return RPMSG_ERR_PARAM;
    if (!ept->rp_chnl->rdev) return RPMSG_ERR_PARAM;

    /* Get an element out of the message queue for the selected endpoint */
    if(env_get_queue(ept->priv, &msg, timeout_ms))
    {
        if(src != NULL) *src = msg.src;
        if(len != NULL) *len = msg.len;

        *data = msg.data;

#if RPMSG_RECV_NOCOPY_CHECK_PTRS
        {
            struct remote_device * rdev = NULL;
            
            if (!ept->rp_chnl->rdev) return RPMSG_ERR_PARAM;
            rdev = ept->rp_chnl->rdev;
            
            env_lock_mutex(rdev->lock);
            assert(rpmsg_in_app_buffers_tail != NULL);  
            assert(msg.data != NULL);   
            rpmsg_in_app_buffers_tail->ptr = msg.data;
            rpmsg_in_app_buffers_tail->next = (rpmsg_ptr_llist_t*)env_allocate_memory(sizeof(rpmsg_ptr_llist_t));
            assert(rpmsg_in_app_buffers_tail->next);
            rpmsg_in_app_buffers_tail = rpmsg_in_app_buffers_tail->next;
            memset((void*)rpmsg_in_app_buffers_tail, 0, sizeof(rpmsg_ptr_llist_t));
            env_unlock_mutex(rdev->lock);
        }
#endif

        return RPMSG_SUCCESS; /* success */
        
    }

    return RPMSG_ERR_NO_BUFF; /* failed */
}

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
int rpmsg_rtos_recv_nocopy_free(struct rpmsg_endpoint *ept, void* data)
{
    if (!data) return RPMSG_ERR_PARAM;
    if (!ept) return RPMSG_ERR_PARAM;
    if (!ept->rp_chnl) return RPMSG_ERR_PARAM;
    if (!ept->rp_chnl->rdev) return RPMSG_ERR_PARAM;
    
#if RPMSG_RECV_NOCOPY_CHECK_PTRS
    {
        /* Allow only previously allocated buffers to be freed,
          * invalid pointer values could influence the destination core,
          * which is a security issue. */
        struct remote_device * rdev = NULL;
        rpmsg_ptr_llist_t * iterator = NULL;
        rpmsg_ptr_llist_t * prev = NULL;

        if (!ept->rp_chnl->rdev) return RPMSG_ERR_PARAM;
        rdev = ept->rp_chnl->rdev;

        env_lock_mutex(rdev->lock);

        assert(rpmsg_in_app_buffers_head != NULL);

        for(iterator = rpmsg_in_app_buffers_head, prev = NULL; iterator->ptr != NULL; iterator = iterator->next)
        {
            if(iterator->ptr == data)
            {
                assert(iterator->next != NULL);
                if(prev != NULL)
                {
                    prev->next = iterator->next;
                    if(prev->next->ptr == NULL)
                    {
                        rpmsg_in_app_buffers_tail = prev->next;
                    }
                }
                else
                {
                    rpmsg_in_app_buffers_head = iterator->next;
                    if(rpmsg_in_app_buffers_head->ptr == NULL)
                    {
                        rpmsg_in_app_buffers_tail = rpmsg_in_app_buffers_head;
                    }
                }

                env_unlock_mutex(rdev->lock);

                env_free_memory((void*)iterator);

                /* Return used buffer. */ 
                rpmsg_release_rx_buffer(ept->rp_chnl, data);

                return RPMSG_SUCCESS;
            }
            prev = iterator;
        }

        env_unlock_mutex(rdev->lock); 
    }
    return RPMSG_ERR_PARAM; 
#else
    
    /* Return used buffer. */ 
    rpmsg_release_rx_buffer(ept->rp_chnl, data);

    return RPMSG_SUCCESS;
#endif
}

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
void *rpmsg_rtos_alloc_tx_buffer(struct rpmsg_endpoint *ept, unsigned long *size)
{
    if (!size) return NULL;
    if (!ept) return NULL;
    if (!ept->rp_chnl) return NULL;
    if (!ept->rp_chnl->rdev) return NULL;

    return rpmsg_alloc_tx_buffer(ept->rp_chnl, size, RPMSG_TRUE);
}

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
int rpmsg_rtos_send(struct rpmsg_endpoint *ept, void *data, int len, unsigned long dst)
{
    if (!data) return RPMSG_ERR_PARAM;
    if (!ept) return RPMSG_ERR_PARAM;
    if (!ept->rp_chnl) return RPMSG_ERR_PARAM;
    if (!ept->rp_chnl->rdev) return RPMSG_ERR_PARAM;
    
    return rpmsg_send_offchannel_raw(ept->rp_chnl, ept->addr, dst, (char *)data, len, RPMSG_TRUE);
}

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
int rpmsg_rtos_send_nocopy(struct rpmsg_endpoint *ept, void *txbuf, int len, unsigned long dst)
{
    if (!txbuf) return RPMSG_ERR_PARAM;
    if (!ept) return RPMSG_ERR_PARAM;
    if (!ept->rp_chnl) return RPMSG_ERR_PARAM;
    if (!ept->rp_chnl->rdev) return RPMSG_ERR_PARAM;

    return rpmsg_send_offchannel_nocopy(ept->rp_chnl, ept->addr, dst, txbuf, len);
}
