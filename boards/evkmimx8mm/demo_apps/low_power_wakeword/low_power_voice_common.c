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
#include "fsl_gpc.h"
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
static LPM_POWER_STATUS_MCORE mcore_lpm_state = LPM_MCORE_STATE_RUN;

#ifndef BOARD_MU_IRQ_NUM
#define BOARD_MU_IRQ_NUM BOARD_MU_IRQ
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern volatile app_srtm_state_t srtmState;

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

void PreSleepProcessing(void)
{
    APP_SRTM_Suspend();
    DbgConsole_Deinit();
}

void PostSleepProcessing(void)
{
    APP_SRTM_Resume();
    DbgConsole_Init(BOARD_DEBUG_UART_INSTANCE, BOARD_DEBUG_UART_BAUDRATE, BOARD_DEBUG_UART_TYPE,
                    BOARD_DEBUG_UART_CLK_FREQ);
}

void ShowMCoreStatus(void)
{
    if (mcore_lpm_state == LPM_MCORE_STATE_STOP)
    {
        PRINTF("\r\nNo audio, M core enters STOP mode!\r\n");
    }
    else if (mcore_lpm_state == LPM_MCORE_STATE_RUN)
    {
        PRINTF("\r\nPlayback or record is running, M core enters RUN mode!\r\n");
    }
    else
    {
        ; /* For MISRA C-2012 rule 15.7. */
    }
}

void UpdateTargetPowerStatus(void)
{
    /*
     * The m4_lpm_state merely indicates what the power state the M core finally should be.
     * In this demo, if there is no audio playback, M core will be set to STOP mode finally.
     */
    LPM_POWER_STATUS_MCORE mcore_target_lpm;

    if (APP_SRTM_ServiceIdle())
    {
        mcore_target_lpm = LPM_MCORE_STATE_STOP;
    }
    else
    {
        mcore_target_lpm = LPM_MCORE_STATE_RUN;
    }

    if (mcore_target_lpm != mcore_lpm_state)
    {
        mcore_lpm_state = mcore_target_lpm;
        ShowMCoreStatus();
    }
}

void vPortSuppressTicksAndSleep(TickType_t xExpectedIdleTime)
{
    uint32_t irqMask;
    uint64_t counter = 0;
    uint32_t timeoutTicks;
    uint32_t timeoutMilliSec = (uint32_t)((uint64_t)1000 * xExpectedIdleTime / configTICK_RATE_HZ);

    irqMask = DisableGlobalIRQ();

    UpdateTargetPowerStatus();

    /* Only when no context switch is pending and no task is waiting for the scheduler
     * to be unsuspended then enter low power entry.
     */
    if (eTaskConfirmSleepModeStatus() != eAbortSleep)
    {
        timeoutTicks = LPM_EnterTicklessIdle(timeoutMilliSec, &counter);
        if (timeoutTicks)
        {
            if (APP_SRTM_ServiceIdle() && LPM_AllowSleep())
            {
                LPM_MCORE_ChangeMCoreClock(LPM_MCORE_LOW_FREQ);
                LPM_MCORE_SetPowerStatus(BOARD_GPC_BASEADDR, LPM_MCORE_STATE_STOP);
                PreSleepProcessing();
                ServiceFlagAddr = ServiceIdle;
                __DSB();
                __ISB();
                __WFI();
                ServiceFlagAddr = ServiceBusy;
                PostSleepProcessing();
                LPM_MCORE_ChangeMCoreClock(LPM_MCORE_HIGH_FREQ);
                LPM_MCORE_SetPowerStatus(BOARD_GPC_BASEADDR, LPM_MCORE_STATE_RUN);
            }
            else
            {
                __DSB();
                __ISB();
                __WFI();
            }
        }
        LPM_ExitTicklessIdle(timeoutTicks, counter);
    }

    EnableGlobalIRQ(irqMask);
}

void MainTask(void *pvParameters)
{
    /* Treat M core as busy status by default.*/
    ServiceFlagAddr = ServiceBusy;

    /*
     * Wait For A core Side Become Ready
     */
    PRINTF("********************************\r\n");
    PRINTF("Wait the Linux kernel boot up to create the link between M core and A core.\r\n");
    PRINTF("\r\n");
    PRINTF("********************************\r\n");
    while (srtmState != APP_SRTM_StateLinkedUp)
        ;
    PRINTF("The rpmsg channel between M core and A core created!\r\n");
    PRINTF("********************************\r\n");
    PRINTF("\r\n");

    /* Configure GPC */
    GPC_Init(BOARD_GPC_BASEADDR, APP_PowerUpSlot, APP_PowerDnSlot);
    GPC_EnableIRQ(BOARD_GPC_BASEADDR, BOARD_MU_IRQ_NUM);
    GPC_EnableIRQ(BOARD_GPC_BASEADDR, SYSTICK_IRQn);
    GPC_EnableIRQ(BOARD_GPC_BASEADDR, I2C3_IRQn);

    while (true)
    {
        /* Use App task logic to replace vTaskDelay */
        PRINTF("\r\nMain task is working now.\r\n");
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

    APP_SRTM_Init();

    voice_engine_create();

    if (xTaskCreate(MainTask, "Main Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1U, NULL) != pdPASS)
    {
        PRINTF("Task creation failed!.\r\n");
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
