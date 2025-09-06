/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <string.h>
#include <assert.h>
#include <string.h>

#include "fsl_common.h"

#include "srtm_heap.h"
#include "srtm_list.h"
#include "srtm_dispatcher.h"
#include "srtm_netc_service.h"
#include "srtm_service_struct.h"
#include "srtm_message.h"
#include "srtm_message_struct.h"
#include "srtm_channel.h"
#include "srtm_channel_struct.h"

typedef struct _srtm_netc_service
{
    struct _srtm_service service;
    srtm_netc_adapter_t adapter;
} *srtm_netc_service_t;

static srtm_status_t SRTM_NETCService_WritePCIConfig(
    srtm_service_t service, uint8_t bus, uint8_t devFn, uint16_t reg, uint32_t val, uint8_t size)
{
    srtm_netc_service_t handle  = (srtm_netc_service_t)(void *)service;
    srtm_netc_adapter_t adapter = handle->adapter;

    return adapter->writePCIConfig(adapter, bus, devFn, reg, val, size); // APP_SRTM_NETC_WritePCIConfig
}

static srtm_status_t SRTM_NETCService_Request(srtm_service_t service, srtm_request_t request)
{
    srtm_status_t status;
    srtm_channel_t channel;
    uint8_t command;
    uint32_t payloadLen;
    srtm_response_t response;
    struct _srtm_netc_payload *netcReq;
    struct _srtm_netc_payload *netcResp;

    assert(service->dispatcher);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    channel    = SRTM_CommMessage_GetChannel(request);
    command    = SRTM_CommMessage_GetCommand(request);
    netcReq    = (struct _srtm_netc_payload *)(void *)SRTM_CommMessage_GetPayload(request);
    payloadLen = SRTM_CommMessage_GetPayloadLen(request);
    (void)payloadLen; /* try to fix warning: variable 'payloadLen' set but not used */
    assert(netcReq);
    assert((uint32_t)(sizeof(struct _srtm_netc_payload) == payloadLen));

    response = SRTM_Response_Create(channel, SRTM_NETC_CATEGORY, SRTM_NETC_VERSION, command,
                                    (uint16_t)(sizeof(struct _srtm_netc_payload)));
    if (response == NULL)
    {
        return SRTM_Status_OutOfMemory;
    }

    netcResp = (struct _srtm_netc_payload *)(void *)SRTM_CommMessage_GetPayload(response);

    status = SRTM_Service_CheckVersion(service, request, SRTM_NETC_VERSION);
    if (status != SRTM_Status_Success)
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s: format error!\r\n", __func__);
        netcResp->retCode = SRTM_NETC_RETURN_CODE_FAIL;
    }
    else
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO,
                           "SRTM receive NETC request:cmd=0x%x, bus %d, devFn %d, reg 0x%x, val 0x%x, size %d\r\n",
                           command, netcReq->bus, netcReq->devFn, netcReq->reg, netcReq->val, netcReq->size);
        (void)memcpy(netcResp, netcReq, sizeof(struct _srtm_netc_payload));

        switch (command)
        {
            case (uint8_t)SRTM_NETC_CMD_WRITE_PCI_CONFIG:
                status = SRTM_NETCService_WritePCIConfig(service, netcReq->bus, netcReq->devFn, netcReq->reg,
                                                         netcReq->val, netcReq->size);
                netcResp->retCode =
                    status == SRTM_Status_Success ? SRTM_NETC_RETURN_CODE_SUCEESS : SRTM_NETC_RETURN_CODE_FAIL;
                break;
            default:
                SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s: command %d unsupported!\r\n", __func__, command);
                assert(false);
                break;
        }
    }

    return SRTM_Dispatcher_DeliverResponse(service->dispatcher, response);
}

static srtm_status_t SRTM_NETCService_Notify(srtm_service_t service, srtm_notification_t notif)
{
    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s: command %d unsupported!\r\n", __func__,
                       SRTM_CommMessage_GetCommand(notif));

    return SRTM_Status_ServiceNotFound;
}

static void SRTM_NETCService_Destroy(srtm_service_t service)
{
    srtm_netc_service_t handle = (srtm_netc_service_t)(void *)service;

    assert(service);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    /* Service must be unregistered from dispatcher before destroy */
    assert(SRTM_List_IsEmpty(&service->node));

    SRTM_Heap_Free(handle);
}

srtm_service_t SRTM_NETCService_Create(srtm_netc_adapter_t adapter)
{
    srtm_netc_service_t handle;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);
    handle = (srtm_netc_service_t)SRTM_Heap_Malloc(sizeof(struct _srtm_netc_service));
    assert(handle);

    adapter->service = &handle->service;
    handle->adapter  = adapter;

    SRTM_List_Init(&handle->service.node);
    handle->service.dispatcher = NULL;
    handle->service.category   = SRTM_NETC_CATEGORY;
    handle->service.destroy    = SRTM_NETCService_Destroy;
    handle->service.request    = SRTM_NETCService_Request;
    handle->service.notify     = SRTM_NETCService_Notify;

    return &handle->service;
}
