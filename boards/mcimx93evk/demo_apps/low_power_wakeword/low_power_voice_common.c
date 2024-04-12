/*
 * Copyright 2021-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "FreeRTOS.h"
#include "task.h"

#include "pin_mux.h"
#include "board.h"
#include "app_srtm.h"
#include "low_power_voice_common.h"
#include "lpm.h"
#include "fsl_debug_console.h"
#include "voice_engine_common.h"

#include "fsl_iomuxc.h"
#include "fsl_lpuart.h"
#include "fsl_mu.h"
#include "rsc_table.h"
#include "fsl_edma.h"
#include "fsl_sai.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define APP_DEBUG_UART_BAUDRATE (115200U) /* Debug console baud rate. */
#define APP_LPTMR2_IRQ_PRIO     (5U)
#define APP_LPUART2_IRQ_PRIO    (5U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

void MainTask(void *pvParameters)
{
    PRINTF("Wait the Linux kernel boot up to create the link between M core and A core.\r\n");
    PRINTF("\r\n");

    APP_SRTM_Init();
#if defined(MIMX9352_cm33_SERIES) || defined(MIMX9322_cm33_SERIES)
    APP_SRTM_StartCommunication();
#endif
    PRINTF("The rpmsg channel between M core and A core created!\r\n");
    PRINTF("\r\n");

    voice_engine_create();

    LPM_Init();

    while (true)
    {
        /* Use App task logic to replace vTaskDelay */
        PRINTF_VERBOSE("\r\nMain task is working now.\r\n");
        vTaskDelay(portMAX_DELAY);
    }
}
/*!
 * @brief Main function
 */
int main(void)
{
    /* clang-format off */
    /* 250MHz DMA clock */
    const clock_root_config_t dmaClkCfg = {
        .clockOff = false,
	.mux = kCLOCK_WAKEUPAXI_ClockRoot_MuxSysPll1Pfd0, // 1000MHz
	.div = 4
    };
    const clock_root_config_t lpi2cClkCfg = {
        .clockOff = false,
	.mux = 0, // 24MHz oscillator source
	.div = 1
    };
    const clock_root_config_t saiClkCfg = {
        .clockOff = false,
        .mux = 1, // select audiopll1out source(393216000 Hz)
        .div = 32 // output 12288000 Hz
    };
    const clock_root_config_t pdmClkCfg = {
        .clockOff = false,
        .mux = 1,
        .div = 32
    };
    sai_master_clock_t saiMasterCfg = {
        .mclkOutputEnable = true,
     };

    BOARD_InitBootPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    CLOCK_SetRootClock(kCLOCK_Root_WakeupAxi, &dmaClkCfg);
    CLOCK_SetRootClock(kCLOCK_Root_Pdm, &pdmClkCfg);
    CLOCK_SetRootClock(kCLOCK_Root_Lpi2c1, &lpi2cClkCfg);
    CLOCK_SetRootClock(kCLOCK_Root_Sai3, &saiClkCfg);
    CLOCK_SetRootClock(BOARD_ADP5585_I2C_CLOCK_ROOT, &lpi2cClkCfg);

    CLOCK_EnableClock(kCLOCK_Lptmr1);
    CLOCK_EnableClock(kCLOCK_Lpuart2);
    CLOCK_EnableClock(kCLOCK_Lpi2c1);
    CLOCK_EnableClock(kCLOCK_Sai3);

    /* Select PDM/SAI signals */
    adp5585_handle_t handle;
    BOARD_InitADP5585(&handle);
    ADP5585_SetDirection(&handle, (1 << BOARD_ADP5585_PDM_MQS_SEL) | (1 << BOARD_ADP5585_EXP_SEL), kADP5585_Output);
    ADP5585_ClearPins(&handle, (1 << BOARD_ADP5585_PDM_MQS_SEL) | (1 << BOARD_ADP5585_EXP_SEL));

    /* Select SAI3 signals */
    ADP5585_SetDirection(&handle, (1 << BOARD_ADP5585_EXP_SEL), kADP5585_Output);
    ADP5585_ClearPins(&handle, (1 << BOARD_ADP5585_EXP_SEL));

    /* select MCLK direction(Enable MCLK clock) */
    saiMasterCfg.mclkSourceClkHz = CLOCK_GetIpFreq(kCLOCK_Root_Sai3);  /* setup source clock for MCLK */
    saiMasterCfg.mclkHz          = saiMasterCfg.mclkSourceClkHz;       /* setup target clock of MCLK */
    SAI_SetMasterClockConfig(SAI3, &saiMasterCfg);

    /* copy resource table to destination address(TCM) */
    copyResourceTable();

    /* Config OSCPLL LPM setting for M33 SUSPEND */
    for (unsigned int i = OSCPLL_LPM_START; i <= OSCPLL_LPM_END; i++)
    {
        CCM_CTRL->OSCPLL[i].LPM0 |= CCM_OSCPLL_LPM0_LPM_SETTING_D2(3);
    }

#if APP_SRTM_CODEC_AK4497_USED
    APP_SRTM_I2C_ReleaseBus();
    BOARD_I2C_ConfigurePins();
#endif
#if APP_SRTM_PDM_USED
    BOARD_PDM_ConfigurePins();
#endif
    PRINTF("\r\n#################### LOW POWER VOICE DEMO START ####################\n\r\n");
    PRINTF("Build Time: %s--%s \r\n", __DATE__, __TIME__);

    if (xTaskCreate(MainTask, "Main Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1U, NULL) != pdPASS)
    {
        PRINTF_VERBOSE("Task creation failed!.\r\n");
        while (1)
            ;
    }

    /* Start FreeRTOS scheduler. */
    vTaskStartScheduler();

    /* Application should never reach this point. */
    for (;;)
    {
    }
}
void vApplicationMallocFailedHook(void)
{
    PRINTF("Malloc Failed!!!\r\n");
}
