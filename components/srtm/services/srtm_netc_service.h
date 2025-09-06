/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRTM_NETC_SERVICE_H__
#define __SRTM_NETC_SERVICE_H__

#include "srtm_service.h"

/*!
 * @addtogroup srtm_service
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/** @brief Switch to disable NETC service debugging messages. */
#ifndef SRTM_NETC_SERVICE_DEBUG_OFF
#define SRTM_NETC_SERVICE_DEBUG_OFF (0)
#endif

#if SRTM_NETC_SERVICE_DEBUG_OFF
#undef SRTM_DEBUG_VERBOSE_LEVEL
#define SRTM_DEBUG_VERBOSE_LEVEL SRTM_DEBUG_VERBOSE_NONE
#endif

/* Protocol definition */
#define SRTM_NETC_CATEGORY (0xCU)
#define SRTM_NETC_VERSION  (0x0100U)

#define SRTM_NETC_RETURN_CODE_SUCEESS (0x0U) /* Success                    */
#define SRTM_NETC_RETURN_CODE_FAIL    (0x1U) /* Failed                     */

/* NETC Service Notification Command definition */
typedef enum
{
    /* NETC Service Request Command definition */
    SRTM_NETC_CMD_READ_PCI_CONFIG  = 0U, /* Reserved: read the register of PCIe config space */
    SRTM_NETC_CMD_WRITE_PCI_CONFIG = 1U, /* Write the register of PCIe config space */
} srtm_netc_cmd_t;

/**
 * @brief SRTM NETC payload structure
 */
SRTM_ANON_DEC_BEGIN
SRTM_PACKED_BEGIN struct _srtm_netc_payload
{
    uint8_t bus;
    uint8_t devFn;
    uint16_t reg;
    uint8_t size;
    uint8_t retCode;
    uint32_t val;
} SRTM_PACKED_END;
SRTM_ANON_DEC_END

typedef struct _srtm_netc_payload *srtm_netc_payload_t;

/**
 * @brief SRTM NETC adapter structure pointer.
 */
typedef struct _srtm_netc_adapter *srtm_netc_adapter_t;

/**
 * @brief SRTM NETC adapter structure
 */
struct _srtm_netc_adapter
{
    /* Bound service */
    srtm_service_t service;

    /* Interfaces implemented by NETC adapter */
    srtm_status_t (*writePCIConfig)(
        srtm_netc_adapter_t adapter, uint8_t bus, uint8_t devFn, uint16_t reg, uint32_t val, uint8_t size);
};
/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*!
 * @brief Create NETC service.
 *
 * @param adapter NETC adapter to provide real NETC features.
 * @return SRTM service handle on success and NULL on failure.
 */
srtm_service_t SRTM_NETCService_Create(srtm_netc_adapter_t adapter);

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* __SRTM_NETC_SERVICE_H__ */
