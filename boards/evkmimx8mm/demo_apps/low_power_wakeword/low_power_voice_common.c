/*
 * Copyright 2021-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "FreeRTOS.h"
#include "task.h"

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "app_srtm.h"
#include "low_power_voice_common.h"
#include "lpm.h"
#include "fsl_debug_console.h"
#include "voice_engine_common.h"

#include "fsl_rdc.h"
#include "fsl_gpio.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define RDC_DISABLE_A53_ACCESS 0xFC
#define RDC_DISABLE_M4_ACCESS  0xF3


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
void Peripheral_RdcSetting(void)
{
    rdc_domain_assignment_t assignment = {0};
    rdc_periph_access_config_t periphConfig;

    assignment.domainId = BOARD_DOMAIN_ID;

    /* Only configure the RDC if the RDC peripheral write access is allowed. */
    if ((0x1U & RDC_GetPeriphAccessPolicy(RDC, kRDC_Periph_RDC, assignment.domainId)) != 0U)
    {
        RDC_SetMasterDomainAssignment(RDC, kRDC_Master_SDMA3_PERIPH, &assignment);
        RDC_SetMasterDomainAssignment(RDC, kRDC_Master_SDMA3_BURST, &assignment);
        RDC_SetMasterDomainAssignment(RDC, kRDC_Master_SDMA3_SPBA2, &assignment);

        RDC_GetDefaultPeriphAccessConfig(&periphConfig);
        /* Do not allow the A53 domain(domain0) to access the following peripherals. */
        periphConfig.policy = RDC_DISABLE_A53_ACCESS;
        periphConfig.periph = kRDC_Periph_SAI1;
        RDC_SetPeriphAccessConfig(RDC, &periphConfig);
        periphConfig.periph = kRDC_Periph_UART4;
        RDC_SetPeriphAccessConfig(RDC, &periphConfig);
        periphConfig.periph = kRDC_Periph_I2C3;
        RDC_SetPeriphAccessConfig(RDC, &periphConfig);
        periphConfig.periph = kRDC_Periph_GPT1;
        RDC_SetPeriphAccessConfig(RDC, &periphConfig);
#if APP_SRTM_PDM_USED
        periphConfig.periph = kRDC_Periph_MICFIL;
        RDC_SetPeriphAccessConfig(RDC, &periphConfig);
#endif
        periphConfig.periph = kRDC_Periph_SDMA3;
        RDC_SetPeriphAccessConfig(RDC, &periphConfig);
        /* For SAI3, both kRDC_Periph_SAI3_ACCESS and kRDC_Periph_SAI3_LPM registers need set.*/
        periphConfig.periph = kRDC_Periph_SAI3_ACCESS;
        RDC_SetPeriphAccessConfig(RDC, &periphConfig);
        periphConfig.periph = kRDC_Periph_SAI3_LPM;
        RDC_SetPeriphAccessConfig(RDC, &periphConfig);
        /* Remove the SAI2 power control in RDC from M4 to avoid A53 hang when it touches SAI2 under M core enters STOP
         * mode.*/
        periphConfig.policy = RDC_DISABLE_M4_ACCESS;
        periphConfig.periph = kRDC_Periph_SAI2_LPM;
        RDC_SetPeriphAccessConfig(RDC, &periphConfig);
    }
}

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
    uint32_t i = 0;

    BOARD_RdcInit();
    Peripheral_RdcSetting();
    BOARD_InitBootPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    BOARD_InitMemory();
    /*
     * In order to wakeup M4 from LPM, all PLLCTRLs need to be set to "NeededRun"
     */
    for (i = 0; i != 39; i++)
    {
        CCM->PLL_CTRL[i].PLL_CTRL = kCLOCK_ClockNeededRun;
    }
    CLOCK_SetRootMux(kCLOCK_RootI2c3, kCLOCK_I2cRootmuxSysPll1Div5); /* Set I2C source to SysPLL1 Div5 160MHZ */
    CLOCK_SetRootDivider(kCLOCK_RootI2c3, 1U, 10U);                  /* Set root clock to 160MHZ / 10 = 16MHZ */
    CLOCK_SetRootMux(kCLOCK_RootGpt1, kCLOCK_GptRootmuxOsc24M);      /* Set GPT source to Osc24 MHZ */
    CLOCK_SetRootDivider(kCLOCK_RootGpt1, 1U, 1U);

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
