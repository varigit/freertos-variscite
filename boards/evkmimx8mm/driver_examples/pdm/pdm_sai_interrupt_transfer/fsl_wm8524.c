/*
 * Copyright 2017 NXP Semiconductor, Inc.
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_wm8524.h"
#include "fsl_gpio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

void WM8524_Init(wm8524_handle_t *handle, wm8524_config_t *config)
{
    gpio_pin_config_t gpioConfig = {kGPIO_DigitalOutput, 1};

    /* Configure contents to handle */
    handle->busPin = config->busPin;
    handle->busPinNum = config->busPinNum;
    handle->mutePin = config->mutePin;
    handle->mutePinNum = config->mutePinNum;

    /* Initialize GPIO pins */
    if (handle->busPin)
    {
        GPIO_PinInit(config->busPin, config->busPinNum, &gpioConfig);
        /* Initialize codec protocol */
        WM8524_ConfigFormat(handle, config->protocol);
    }

    /* Unmute codec */
    GPIO_PinInit(config->mutePin, config->mutePinNum, &gpioConfig);
    WM8524_SetMute(handle, false);
}

void WM8524_ConfigFormat(wm8524_handle_t *handle, wm8524_protocol_t protocol)
{
    if (protocol != kWM8524_ProtocolRightJustified)
    {
        GPIO_PinWrite(handle->busPin, handle->busPinNum, protocol);
    }
}

void WM8524_SetMute(wm8524_handle_t *handle, bool isMute)
{
    GPIO_PinWrite(handle->mutePin, handle->mutePinNum, (!isMute));
}
