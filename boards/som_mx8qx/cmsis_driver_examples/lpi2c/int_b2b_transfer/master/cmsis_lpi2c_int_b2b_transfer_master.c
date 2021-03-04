/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*  Standard C Included Files */
#include <stdio.h>
#include <string.h>
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_lpi2c.h"
#include "fsl_lpi2c_cmsis.h"

#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_irqsteer.h"
#include "fsl_gpio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_I2C_MASTER Driver_I2C4
#define I2C_MASTER_SLAVE_ADDR_7BIT (0x7EU)
#define I2C_DATA_LENGTH (32) /* MAX is 256 */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

uint8_t g_master_txBuff[I2C_DATA_LENGTH];
uint8_t g_master_rxBuff[I2C_DATA_LENGTH];
volatile bool g_MasterCompletionFlag = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
void LPI2C4_InitPins(void)
{
    sc_ipc_t ipc;

    ipc = BOARD_InitRpc();
    LPI2C_InitPins(ipc);
}

void LPI2C4_DeinitPins(void)
{
    sc_ipc_t ipc;

    ipc = BOARD_InitRpc();
    LPI2C_DeinitPins(ipc);
}

uint32_t LPI2C4_GetFreq(void)
{
    return CLOCK_GetIpFreq(kCLOCK_DMA_Lpi2c3);
}

static void lpi2c_master_callback(uint32_t event)
{
    switch (event)
    {
        /* The master has sent a stop transition on the bus */
        case ARM_I2C_EVENT_TRANSFER_DONE:
            g_MasterCompletionFlag = true;
            break;

        /* master arbitration lost */
        case ARM_I2C_EVENT_ARBITRATION_LOST:
            g_MasterCompletionFlag = true;
            break;

        default:
            break;
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint32_t i = 0;

    /*Init BOARD*/
    sc_ipc_t ipc;
    sc_pm_clock_rate_t src_rate = SC_133MHZ;

    ipc = BOARD_InitRpc();
    BOARD_InitPins(ipc);
    LPI2C_InitPins(ipc);
    BOARD_BootClockRUN();
    BOARD_InitMemory();
    BOARD_InitDebugConsole();

    /* open the lpi2c power and clock */
    if (sc_pm_set_resource_power_mode(ipc, SC_R_I2C_3, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on SC_R_I2C_3\r\n");
    }

    if (sc_pm_clock_enable(ipc, SC_R_I2C_3, SC_PM_CLK_PER, true, false) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to enable SC_R_I2C_3 clock \r\n");
    }

    if (sc_pm_set_clock_rate(ipc, SC_R_I2C_3, SC_PM_CLK_PER, &src_rate) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to set SC_R_I2C_3 clock rate\r\n");
    }

    /* Power on IRQSteer . */
    if (sc_pm_set_resource_power_mode(ipc, SC_R_IRQSTR_M4_0, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
    {
        PRINTF("Error: Failed to power on IRQSTR\r\n");
    }

    /* Enable interrupt in irqsteer */
    IRQSTEER_Init(IRQSTEER);
    IRQSTEER_EnableInterrupt(IRQSTEER, ADMA_I2C3_INT_IRQn);

    /* Initialize the LPI2C master peripheral */
    EXAMPLE_I2C_MASTER.Initialize(lpi2c_master_callback);
    EXAMPLE_I2C_MASTER.PowerControl(ARM_POWER_FULL);

    /* Change the default baudrate configuration */
    EXAMPLE_I2C_MASTER.Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_STANDARD);

    PRINTF("\r\nCMSIS LPI2C board2board interrupt example -- Master transfer.\r\n");

    /* Set up lpi2c master to send data to slave */
    for (i = 0; i < I2C_DATA_LENGTH; i++)
    {
        g_master_txBuff[i] = i;
    }

    /* Display the data the master will send */
    PRINTF("Master will send data :");
    for (i = 0; i < I2C_DATA_LENGTH; i++)
    {
        if (i % 8 == 0)
        {
            PRINTF("\r\n");
        }
        PRINTF("0x%2x  ", g_master_txBuff[i]);
    }
    PRINTF("\r\n\r\n");

    /* Start transmitting I2C transfers on the LPI2C master peripheral */
    EXAMPLE_I2C_MASTER.MasterTransmit(I2C_MASTER_SLAVE_ADDR_7BIT, g_master_txBuff, I2C_DATA_LENGTH, false);

    /*wait for master complete*/
    while (!g_MasterCompletionFlag)
    {
    }

    /*  Reset master completion flag to false. */
    g_MasterCompletionFlag = false;

    PRINTF("Receive sent data from slave :");

    /* Start accepting I2C transfers on the LPI2C master peripheral */
    EXAMPLE_I2C_MASTER.MasterReceive(I2C_MASTER_SLAVE_ADDR_7BIT, g_master_rxBuff, I2C_DATA_LENGTH, false);

    /*wait for master complete*/
    while (!g_MasterCompletionFlag)
    {
    }

    /*  Reset master completion flag to false. */
    g_MasterCompletionFlag = false;

    for (i = 0; i < I2C_DATA_LENGTH; i++)
    {
        if (i % 8 == 0)
        {
            PRINTF("\r\n");
        }
        PRINTF("0x%2x  ", g_master_rxBuff[i]);
    }
    PRINTF("\r\n\r\n");

    /* Transfer completed. Check the data.*/
    for (i = 0; i < I2C_DATA_LENGTH; i++)
    {
        if (g_master_rxBuff[i] != g_master_txBuff[i])
        {
            PRINTF("\r\nError occurred in the transfer ! \r\n");
            break;
        }
    }

    PRINTF("\r\nEnd of LPI2C example .\r\n");
    while (1)
    {
    }
}
