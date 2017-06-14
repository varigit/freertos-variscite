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

#include <stdio.h>
#include "board.h"
#include "gpio_pins.h"
#include "gpio_imx.h"
#include "debug_console_imx.h"

#define GPIO_INTERRUPT         (1)
#define GPIO_POLLING           (0)
#define GPIO_DEBOUNCE_DELAY    (100000)

/* button relevent variables */
static uint8_t keyPressCount;
static bool on = false;
#ifdef BOARD_GPIO_KEY_CONFIG
static volatile uint8_t button_pressed_flag;
#endif

/*!
 * @brief Initialize GPIO_LED controller.
 */
static void GPIO_Ctrl_InitLedPin(void)
{
#ifdef BOARD_GPIO_LED_CONFIG
    /* GPIO module initialize, configure "LED" as output and drive the output high level */
    gpio_init_config_t ledInitConfig = {
        .pin = BOARD_GPIO_LED_CONFIG->pin,
        .direction = gpioDigitalOutput,
        .interruptMode = gpioNoIntmode
    };
    GPIO_Init(BOARD_GPIO_LED_CONFIG->base, &ledInitConfig);
#endif
}

/*!
 * @brief Initialize GPIO INT\POLLING controller.
 */
static void GPIO_Ctrl_InitKeyPin(uint32_t gpioMode)
{
#ifdef BOARD_GPIO_KEY_CONFIG
    if (GPIO_INTERRUPT == gpioMode)
    {
        /* GPIO module initialize, configure button as interrupt mode. */
        gpio_init_config_t keyInitConfig = {
            .pin = BOARD_GPIO_KEY_CONFIG->pin,
            .direction = gpioDigitalInput,
            .interruptMode = gpioIntFallingEdge,
        };
        GPIO_Init(BOARD_GPIO_KEY_CONFIG->base, &keyInitConfig);
        /* Enable interrupt. */
        NVIC_EnableIRQ(BOARD_GPIO_KEY_IRQ_NUM);
    }
    else
    {
        /* GPIO module initialize, configure button as GPIO functionality. */
        gpio_init_config_t keyInitConfig = {
            .pin = BOARD_GPIO_KEY_CONFIG->pin,
            .direction = gpioDigitalInput,
            .interruptMode = gpioNoIntmode,
        };
        GPIO_Init(BOARD_GPIO_KEY_CONFIG->base, &keyInitConfig);
    }
#endif
}

/*!
 * @brief Wait user to press key in INT\NOINT mode.
 */
static void GPIO_WaitKeyPressed(uint32_t gpioMode)
{
#ifdef BOARD_GPIO_KEY_CONFIG
    uint32_t i, j, debounce;

    if (GPIO_INTERRUPT == gpioMode)
    {
        do
        {
            debounce = 0;

            /* Clear the interrupt state, this operation is necessary, because the GPIO module maybe confuse
               the first rising edge as interrupt*/
            GPIO_ClearStatusFlag(BOARD_GPIO_KEY_CONFIG->base, BOARD_GPIO_KEY_CONFIG->pin);
            /* Enable GPIO pin interrupt */
            GPIO_SetPinIntMode(BOARD_GPIO_KEY_CONFIG->base, BOARD_GPIO_KEY_CONFIG->pin, true);

            /* Waitting for Key pressed. */
            while(button_pressed_flag == 0);
            button_pressed_flag = 0;

            for (i = 0; i < 3; i++)
            {
                /* Delay to wait key value stable. The cycle number should be changed
                 * according to M4 Core clock frequncy.
                 */
                for (j = 0 ; j < GPIO_DEBOUNCE_DELAY; j++)
                {
                    __NOP();
                }

                if (0 == GPIO_ReadPinInput(BOARD_GPIO_KEY_CONFIG->base, BOARD_GPIO_KEY_CONFIG->pin))
                {
                    debounce++;
                }
            }

            if (debounce > 2)
            {
                break;
            }
        } while (1);
    }
    else
    {
        /* Wait for Key Released. */
        do
        {
            debounce = 0;
            while (0 == GPIO_ReadPinInput(BOARD_GPIO_KEY_CONFIG->base, BOARD_GPIO_KEY_CONFIG->pin));

            for (i = 0; i < 3; i++)
            {
                /* Delay to wait key value stable. The cycle number should be changed
                 * according to M4 Core clock frequncy.
                 */
                for (j = 0 ; j < GPIO_DEBOUNCE_DELAY; j++)
                {
                    __NOP();
                }

                if (1 == GPIO_ReadPinInput(BOARD_GPIO_KEY_CONFIG->base, BOARD_GPIO_KEY_CONFIG->pin))
                {
                    debounce++;
                }
            }

            if (debounce > 2)
            {
                break;
            }
        }
        while (1);

        /* Wait for Key Pressed. */
        do
        {
            debounce = 0;
            while (1 == GPIO_ReadPinInput(BOARD_GPIO_KEY_CONFIG->base, BOARD_GPIO_KEY_CONFIG->pin));

            for (i = 0; i < 3; i++)
            {
                /* Delay to wait key value stable. The cycle number should be changed
                 * according to M4 Core clock frequncy.
                 */
                for (j = 0 ; j < GPIO_DEBOUNCE_DELAY; j++)
                {
                    __NOP();
                }

                if (0 == GPIO_ReadPinInput(BOARD_GPIO_KEY_CONFIG->base, BOARD_GPIO_KEY_CONFIG->pin))
                {
                    debounce++;
                }
            }

            if (debounce > 2)
            {
                break;
            }
        }
        while (1);
    }
#else
        GETCHAR();
#endif
}

/*!
 * @brief Toggle the led
 */
static void GPIO_LED_Toggle(void)
{
#ifdef  BOARD_GPIO_LED_CONFIG
    GPIO_WritePinOutput(BOARD_GPIO_LED_CONFIG->base,BOARD_GPIO_LED_CONFIG->pin, on ? gpioPinSet : gpioPinClear);
    keyPressCount++;
    PRINTF("Button pressed %d times\n\r", keyPressCount);
#else
    PRINTF("%c ", on ? '+' : '-');
#endif
    on = !on;
}

/******************************************************************************
*
* Function Name: main
* Comments: GPIO module initialize, interrupt and IO operation.
*   This example include 2 step:
*   1)Configure BUTTON1 as interrupt mode, falling edge, and test
*     by pressing the button 3 times to trigger interrupt.
*   2)Configure BUTTON1 as GPIO functionality
*     and check the button's state(pressed or released) through switch LED
*     to on or off if this board has LED.
*
******************************************************************************/
int main(void)
{
    /* hardware initialiize, include RDC, IOMUX, Uart debug initialize */
    hardware_init();
    PRINTF("\n\r====================== GPIO Example ========================\n\r");

    /* GPIO module initialize, configure "LED" as output and button as interrupt mode. */
    GPIO_Ctrl_InitLedPin();
    GPIO_Ctrl_InitKeyPin(GPIO_INTERRUPT);

    /* wait for user to press button */
#ifdef BOARD_GPIO_KEY_CONFIG
    PRINTF("\n\r=================== GPIO Interrupt =====================\n\r");
    PRINTF("The (%s) button is configured to trigger GPIO interrupt\n\r", BOARD_GPIO_KEY_CONFIG->name);
    PRINTF("Press the (%s) button 3 times to continue.\n\n\r", BOARD_GPIO_KEY_CONFIG->name);
#else
    PRINTF("\n\r============ Use key to simulate GPIO button ==============\n\r");
    PRINTF("Input any data from terminal 3 times to continues.\n\n\r");
#endif
    keyPressCount = 0;
    while(keyPressCount < 3)
    {
        GPIO_WaitKeyPressed(GPIO_INTERRUPT);
        keyPressCount++;
        PRINTF("Button pressed %d time. \n\r", keyPressCount);
    }

    GPIO_Ctrl_InitKeyPin(GPIO_POLLING);
    keyPressCount = 0;

    /* Configure button as GPIO functionality
       and check the button's state(pressed or released) to switch LED on or off */
    /* Check the buttion's status(pressed or released) */
    PRINTF("\n\r================= GPIO Functionality==================\n\r");
    PRINTF("The button state is now polled.\n\r");
    PRINTF("Press the button to switch LED on or off\n\n\r");
    while(true)
    {
        GPIO_WaitKeyPressed(GPIO_POLLING);
        GPIO_LED_Toggle();
    }
}

/******************************************************************************
* Function Name: BOARD_GPIO_BTN_HANDLER
* Comments: The interrupt service routine triggered by gpio
* Note: Need to consider how to eliminate the button shake problem
******************************************************************************/
#ifdef BOARD_GPIO_KEY_CONFIG
void BOARD_GPIO_KEY_HANDLER(void)
{
    button_pressed_flag = 1;
    /* clear the interrupt status */
    GPIO_ClearStatusFlag(BOARD_GPIO_KEY_CONFIG->base, BOARD_GPIO_KEY_CONFIG->pin);

    /* Disable GPIO pin interrupt */
    GPIO_SetPinIntMode(BOARD_GPIO_KEY_CONFIG->base, BOARD_GPIO_KEY_CONFIG->pin, false);
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/
