/*
 * Copyright 2017 NXP Semiconductor, Inc.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_WM8524_H_
#define _FSL_WM8524_H_

#include "fsl_common.h"
#include "fsl_gpio.h"

/*!
 * @addtogroup wm8524
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief The audio data transfer protocol. */
typedef enum _wm8524_protocol
{
    kWM8524_ProtocolLeftJustified = 0x0,  /*!< Left justified mode */
    kWM8524_ProtocolI2S = 0x1,            /*!< I2S mode */
    kWM8524_ProtocolRightJustified = 0x2, /*!< Right justified mode */
} wm8524_protocol_t;

typedef struct _wm8524_config
{
    GPIO_Type *busPin;          /*!< GPIO type for protocol control */
    uint32_t busPinNum;         /*!< Pin number for protocol control */
    GPIO_Type *mutePin;         /*!< GPIO type for mute control */
    uint32_t mutePinNum;        /*!< Pin number for mute control */
    wm8524_protocol_t protocol; /*!< Protocol of the codec */
} wm8524_config_t;

/*! @brief WM8542 codec handler. */
typedef struct _wm8524_handle
{
    GPIO_Type *busPin;   /*!< GPIO type for protocol control */
    uint32_t busPinNum;  /*!< Pin number for protocol control */
    GPIO_Type *mutePin;  /*!< GPIO type for mute control */
    uint32_t mutePinNum; /*!< Pin number for mute control */
} wm8524_handle_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes WM8524.
 *
 * @param handle WM8524 handle structure.
 * @param config WM8524 configure structure.
 */
void WM8524_Init(wm8524_handle_t *handle, wm8524_config_t *config);

/*!
 * @brief Configure WM8524 audio protocol.
 *
 * @param handle WM8524 handle structure.
 * @param protocol WM8524 configuration structure.
 */
void WM8524_ConfigFormat(wm8524_handle_t *handle, wm8524_protocol_t protocol);

/*!
 * @brief Sets the codec mute state.
 *
 * @param handle WM8524 handle structure.
 * @param isMute true means mute, false means normal.
 */
void WM8524_SetMute(wm8524_handle_t *handle, bool isMute);
#if defined(__cplusplus)
}
#endif

/*! @} */
#endif /* _FSL_WM8524_H_ */
