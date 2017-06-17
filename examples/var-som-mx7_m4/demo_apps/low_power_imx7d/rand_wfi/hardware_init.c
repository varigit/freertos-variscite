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

#include "board.h"
#include "gpio_pins.h"

void hardware_init(void)
{
    uint32_t i;
    /*
     * Set GPC_LPCR_M4 to run. In Low Power Demo, when M4 enters STOP, the
     * whole system may enter DSM. A7 will rekick A7 after exit DSM. GPC
     * register status will not auto reset so a manual reset is performed
     * here
     * GPC RDC is default set by U-Boot to be shared by A7 and M4
     */
    GPC_LPCR_M4 = GPC_LPCR_M4 & (~GPC_LPCR_M4_LPM0_MASK);

    /* Board specific RDC settings */
    BOARD_RdcInit();

    /* Board specific clock settings */
    BOARD_ClockInit();

    /*
     * In order to wakeup M4 from LPM, all PLLCTRLs need to be set to "NeededRun"
     */
    for (i=0; i!=33; i++) {
        CCM_BASE_PTR->PLL_CTRL[i].PLL_CTRL = ccmClockNeededRun;
    }

    
    /* Enable clock gate for wakeup mix*/
    CCM_ControlGate(CCM, BOARD_SIM_WAKEUP_CCGR, ccmClockNeededAll);

    /* initialize debug uart */
    dbg_uart_init();

    /* In this demo, we need to grasp board GPT exclusively */
    RDC_SetPdapAccess(RDC, BOARD_GPTA_RDC_PDAP, 3 << (BOARD_DOMAIN_ID * 2), false, false);

    /* Select GPTA clock derived from OSC24M */
    CCM_UpdateRoot(CCM, BOARD_GPTA_CCM_ROOT, ccmRootmuxGptOsc24m, 0, 0);

    /* Enable clock used by GPTA */
    CCM_EnableRoot(CCM, BOARD_GPTA_CCM_ROOT);
    CCM_ControlGate(CCM, BOARD_GPTA_CCM_CCGR, ccmClockNeededAll);

    /* In this demo, we need GPT4 to work as a patch to fix GPC sync issue */
    RDC_SetPdapAccess(RDC, BOARD_GPTB_RDC_PDAP, 3 << (BOARD_DOMAIN_ID * 2), false, false);

    /* Select GPTB clock derived from OSC24M */
    CCM_UpdateRoot(CCM, BOARD_GPTB_CCM_ROOT, ccmRootmuxGptOsc24m, 0, 0);

    /* Enable clock used by GPTB */
    CCM_EnableRoot(CCM, BOARD_GPTB_CCM_ROOT);
    CCM_ControlGate(CCM, BOARD_GPTB_CCM_CCGR, ccmClockNeededAll);

    /* Enable MU clock*/
    CCM_ControlGate(CCM, BOARD_MU_CCM_CCGR, ccmClockNeededAll);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
