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
#ifndef __I2C_XFER_H__
#define __I2C_XFER_H__

#include <stdint.h>
#include <stdbool.h>
#include "FreeRTOS.h"
#include "semphr.h"
#include "i2c_imx.h"

/* Type definitions */
typedef struct _i2c_handle {
    I2C_Type         *base;            /*!< The base address of I2C instance. */
    IRQn_Type         irqNum;          /*!< The interrupt interrupt request number. */
    uint32_t          irqPrio;         /*!< The interrupt interrupt request priority. */
    const uint8_t    *cmdBuff;         /*!< The buffer of I2C command. */
    const uint8_t    *txBuff;          /*!< The buffer of data being sent.*/
    uint8_t          *rxBuff;          /*!< The buffer of received data. */
    uint32_t          cmdSize;         /*!< The remaining number of commands to be transmitted. */
    uint32_t          txSize;          /*!< The remaining number of bytes to be transmitted. */
    uint32_t          rxSize;          /*!< The remaining number of bytes to be received. */
    bool              isBusy;          /*!< True if there is an active transmission. */
    uint32_t          operateDir;      /*!< Overall I2C bus operating direction. */
    uint32_t          currentDir;      /*!< Current Data transfer direction. */
    uint32_t          currentMode;     /*!< Current I2C Bus role of this module. */
    SemaphoreHandle_t xSemaphore;      /*!< I2C internal synchronize semaphore. */
} volatile i2c_handle_t;

typedef struct _i2c_xfer_init_config {
    I2C_Type         *base;            /*!< The base address of I2C instance. */
    i2c_init_config_t config;          /*!< The I2C module low-level initialize structure. */
    IRQn_Type         irqNum;          /*!< The interrupt interrupt request number. */
    uint8_t           irqPrio;         /*!< The interrupt interrupt request priority. */
} i2c_xfer_init_config_t;

/* Function prototypes */
#if defined(__cplusplus)
extern "C" {
#endif

void I2C_XFER_Init(i2c_handle_t *handle, i2c_xfer_init_config_t *initConfig);
bool I2C_XFER_SendDataBlocking(i2c_handle_t *handle, const uint8_t *cmdBuff, uint32_t cmdSize,
                               const uint8_t *txBuffer, uint32_t txSize);
uint32_t I2C_XFER_GetSendStatus(i2c_handle_t *handle);
bool I2C_XFER_ReceiveDataBlocking(i2c_handle_t *handle, const uint8_t* cmdBuff, uint32_t cmdSize,
                                  uint8_t* rxBuffer, uint32_t rxSize);
uint32_t I2C_XFER_GetReceiveStatus(i2c_handle_t *handle);
void I2C_XFER_Handler(i2c_handle_t *handle);

#ifdef __cplusplus
}
#endif

#endif /* __I2C_XFER_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
