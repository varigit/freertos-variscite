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

#include <assert.h>
#include "gpio_pins.h"

gpio_config_t gpioLed = {
    "LED",                         /* name */
    &IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO13,  /* muxReg */
    0,                                  /* muxConfig */
    &IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO13,  /* padReg */
    0,                                  /* padConfig */
    GPIO1,                              /* base */
    13                                  /* pin */
};

gpio_config_t gpioKeyMenu = {
    "MENU",                                         /* name */
    &IOMUXC_SW_MUX_CTL_PAD_EPDC_BDR0,               /* muxReg */
    5,                                              /* muxConfig */
    &IOMUXC_SW_PAD_CTL_PAD_EPDC_BDR0,               /* padReg */
    IOMUXC_SW_PAD_CTL_PAD_EPDC_BDR0_PS(2) |         /* padConfig */
    IOMUXC_SW_PAD_CTL_PAD_EPDC_BDR0_PE_MASK |
    IOMUXC_SW_PAD_CTL_PAD_EPDC_BDR0_HYS_MASK,
    GPIO2,                                          /* base */
    28                                              /* pin */
};

gpio_config_t gpioKeyHome = {
    "HOME",                                         /* name */
    &IOMUXC_SW_MUX_CTL_PAD_EPDC_BDR1,               /* muxReg */
    5,                                              /* muxConfig */
    &IOMUXC_SW_PAD_CTL_PAD_EPDC_BDR1,               /* padReg */
    IOMUXC_SW_PAD_CTL_PAD_EPDC_BDR1_PS(2) |         /* padConfig */
    IOMUXC_SW_PAD_CTL_PAD_EPDC_BDR1_PE_MASK |
    IOMUXC_SW_PAD_CTL_PAD_EPDC_BDR1_HYS_MASK,
    GPIO2,                                          /* base */
    29                                              /* pin */
};

gpio_config_t gpioKeyBack = {
    "BACK",                                         /* name */
    &IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO11,              /* muxReg */
    0,                                              /* muxConfig */
    &IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO11,              /* padReg */
    IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO11_PS(2) |        /* padConfig */
    IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO11_PE_MASK |
    IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO11_HYS_MASK,
    GPIO1,                                          /* base */
    11                                              /* pin */
};

void configure_gpio_pin(gpio_config_t *config)
{
    assert(config);

    *(config->muxReg) = config->muxConfig;
    *(config->padReg) = config->padConfig;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
