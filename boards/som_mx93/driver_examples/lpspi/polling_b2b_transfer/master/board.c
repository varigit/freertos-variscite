/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "fsl_cache.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/* Initialize debug console. */
void BOARD_InitDebugConsole(void)
{
    /* clang-format off */
    const clock_root_config_t uartClkCfg = {
        .clockOff = false,
	.mux = 0, // 24MHz oscillator source
	.div = 1
    };
    /* clang-format on */

    CLOCK_SetRootClock(BOARD_DEBUG_UART_CLOCK_ROOT, &uartClkCfg);
    DbgConsole_Init(BOARD_DEBUG_UART_INSTANCE, BOARD_DEBUG_UART_BAUDRATE, BOARD_DEBUG_UART_TYPE,
                    BOARD_DEBUG_UART_CLK_FREQ);
}


void BOARD_McoreSUSPEND(void)
{
    uint32_t value = 0U;
    /* Config OSCPLL LPM setting for M33 SUSPEND */
    for (unsigned int i = OSCPLL_LPM_START; i <= OSCPLL_LPM_END; i++)
    {
        CCM_CTRL->OSCPLL[i].LPM0 |= CCM_OSCPLL_LPM0_LPM_SETTING_D2_MASK;
    }

    /* Config GPC_CTRL_CM33 to set Mcore as SUSPEND mode */
    GPC_CTRL_CM33->CM_MODE_CTRL |= GPC_CM_MODE_CTRL_CPU_MODE_TARGET_MASK;

    /* Stop SysTick and enter WFI
     * System will goes into system sleep flow
     * The STBY LED on board will light with red color
     */
    /* Save old value of SYST_CSR */
    value            = SYSTICK_CTRL_REG;
    SYSTICK_CTRL_REG = SYSTICK_CLOSE;
    __WFI();
    /* Enable systick */
    SYSTICK_CTRL_REG = value;
}

void BOARD_ConfigMPU(void)
{
    uint8_t attr;

    /* Disable code cache(ICache) and system cache(DCache) */
    XCACHE_DisableCache(LPCAC_PC);
    XCACHE_DisableCache(LPCAC_PS);

    /* NOTE: All TCRAM is non-cacheable regardless of MPU setting. */

    /*
     * default cache policy(default memory access behavior) after enable mpu on cortex-m33(according to RM of
     * cortex-m33): 0x00000000-0x1FFFFFFF Normal memory, Non-shareable, Write-Through, not Write Allocate
     * 0x20000000-0x3FFFFFFF Normal memory, Non-shareable, Write-Back, Write Allocate
     * 0x40000000-0x5FFFFFFF Device, Shareable
     * 0x60000000-0x7FFFFFFF Normal memory, Non-shareable, Write-Back, Write Allocate
     * 0x80000000-0x9FFFFFFF Normal memory, Non-shareable, Write-Through, not Write Allocate
     * 0xA0000000-0xDFFFFFFF Device, Shareable
     * 0xE0000000-0xE003FFFF Device, Shareable
     * 0xE0040000-0xE0043FFF Device, Shareable
     * 0xE0044000-0xE00EFFFF Device, Shareable
     * 0xF0000000-0xFFFFFFFF Device, Shareable
     */
    /* Disable MPU */
    ARM_MPU_Disable();

    /* Attr0: Device-nGnRnE */
    ARM_MPU_SetMemAttr(0U, ARM_MPU_ATTR(ARM_MPU_ATTR_DEVICE, ARM_MPU_ATTR_DEVICE));

    /* Attr1: Normal memory, Outer non-cacheable, Inner non-cacheable */
    ARM_MPU_SetMemAttr(1U, ARM_MPU_ATTR(ARM_MPU_ATTR_NON_CACHEABLE, ARM_MPU_ATTR_NON_CACHEABLE));

    /* Attr2: Normal memory, Inner write-through transient, read allocate. Inner write-through transient, read allocate
     */
    attr = ARM_MPU_ATTR_MEMORY_(0U, 0U, 1U, 0U);
    ARM_MPU_SetMemAttr(2U, ARM_MPU_ATTR(attr, attr));

    /* Attr3: Normal memory, Outer write-back transient, read/write allocate. Inner write-back transient, read/write
     * allocate */
    attr = ARM_MPU_ATTR_MEMORY_(0U, 1U, 1U, 1U);
    ARM_MPU_SetMemAttr(3U, ARM_MPU_ATTR(attr, attr));

    /*
     * Change macro definitions as follows when choose cache policy as non-cacheable:
     * #define DDR_NONCACHEABLE (1U)
     * #define DDR_WRITE_THROUGH (0U)
     * #define DDR_WRITE_BACK (0U)
     *
     *
     * Change macro definitions as follows when choose cache policy as Write-Through:
     * #define DDR_NONCACHEABLE (0U)
     * #define DDR_WRITE_THROUGH (1U)
     * #define DDR_WRITE_BACK (0U)
     *
     *
     * Change macro definitions as follows when choose cache policy as Write-Back:
     * #define DDR_NONCACHEABLE (0U)
     * #define DDR_WRITE_THROUGH (0U)
     * #define DDR_WRITE_BACK (1U)
     */
#define DDR_NONCACHEABLE  (1U)
#define DDR_WRITE_THROUGH (0U)
#define DDR_WRITE_BACK    (0U)
#if DDR_NONCACHEABLE
    /* NOTE: DDR is used as shared memory for A/M core communication, set it to non-cacheable. */
    /* Region 0: [0x80000000, 0xDFFFFFFF](DRAM), outer shareable, read/write, any privileged, executable. Attr 1
     * (non-cacheable). */
    ARM_MPU_SetRegion(0U, ARM_MPU_RBAR(0x80000000, ARM_MPU_SH_OUTER, 0U, 1U, 0U), ARM_MPU_RLAR(0xDFFFFFFF, 1U));
#elif DDR_WRITE_THROUGH
    /* Region 0: [0x80000000, 0xDFFFFFFF](DRAM), outer shareable, read/write, any privileged, executable. Attr 2
     * (Normal memory, Inner write-through transient, read allocate. Inner write-through transient, read allocate). */
    ARM_MPU_SetRegion(0U, ARM_MPU_RBAR(0x80000000, ARM_MPU_SH_OUTER, 0U, 1U, 0U), ARM_MPU_RLAR(0xDFFFFFFF, 2U));
#elif DDR_WRITE_BACK
    /* Region 0: [0x80000000, 0xDFFFFFFF](DRAM), outer shareable, read/write, any privileged, executable. Attr 3
     * (Normal memory, Outer write-back transient, read/write allocate. Inner write-back transient, read/write
     * allocate). */
    ARM_MPU_SetRegion(0U, ARM_MPU_RBAR(0x80000000, ARM_MPU_SH_OUTER, 0U, 1U, 0U), ARM_MPU_RLAR(0xDFFFFFFF, 3U));
#endif

    /* Enable MPU(use default memory map when access the memory within region) */
    ARM_MPU_Enable(MPU_CTRL_PRIVDEFENA_Msk);

    /* Enable ICache and DCache */
    XCACHE_EnableCache(LPCAC_PC);
    XCACHE_EnableCache(LPCAC_PS);
    /* flush pipeline */
    __DSB();
    __ISB();
}
