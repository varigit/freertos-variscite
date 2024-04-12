/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_clock.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.clock"
#endif

/* ROM initializes PLLs with default frequencies except audio/video/ext */
volatile uint32_t g_clockSourceFreq[kCLOCK_Ext + 1] = {
    24000000U,   /* kCLOCK_Osc24M          */
    2000000000U, /* kCLOCK_ArmPll          */
    2000000000U, /* kCLOCK_ArmPllOut       */
    1000000000U, /* kCLOCK_DramPll         */
    1000000000U, /* kCLOCK_DramPllOut      */
    4000000000U, /* kCLOCK_SysPll1         */
    1000000000U, /* kCLOCK_SysPll1Pfd0     */
    500000000U,  /* kCLOCK_SysPll1Pfd0Div2 */
    800000000U,  /* kCLOCK_SysPll1Pfd1     */
    400000000U,  /* kCLOCK_SysPll1Pfd1Div2 */
    625000000U,  /* kCLOCK_SysPll1Pfd2     */
    312500000U,  /* kCLOCK_SysPll1Pfd2Div2 */
    0U,          /* kCLOCK_AudioPll1       */
    0U,          /* kCLOCK_AudioPll1Out    */
    0U,          /* kCLOCK_VideoPll1       */
    0U,          /* kCLOCK_VideoPll1Out    */
    0U           /* kCLOCK_Ext             */
};

uint32_t CLOCK_GetIpFreq(clock_root_t name)
{
    clock_name_t clock;
    uint32_t mux;
    uint32_t div;

    mux = CLOCK_GetRootClockMux(name);
    div = CLOCK_GetRootClockDiv(name);

    clock = CLOCK_GetRootClockSource(name, mux);
    assert(clock <= kCLOCK_Ext);

    return g_clockSourceFreq[clock] / div;
}
