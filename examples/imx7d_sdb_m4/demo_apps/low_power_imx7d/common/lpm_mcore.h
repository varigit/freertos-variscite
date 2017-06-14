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

#ifndef __LPM_MCORE_H__
#define __LPM_MCORE_H__

#include "gpc.h"
#include "device_imx.h"

#define DELAY_LOOP_CNT_LOW_SPEED 10
#define DELAY_CNT 100

#define LPCR_M4_RUN  0
#define LPCR_M4_WAIT 1
#define LPCR_M4_STOP 2

#define LPM_MCORE_MU_CHANNEL    0

#define LPM_MCORE_PRINT_DEBUG_INFO      0

#define MSG_LPM_M4_RUN                  0x5A5A0001
#define MSG_LPM_M4_WAIT                 0x5A5A0002
#define MSG_LPM_M4_STOP                 0x5A5A0003

#define MSG_LPM_M4_REQUEST_HIGHBUS      0x2222CCCC
#define MSG_LPM_M4_RELEASE_HIGHBUS      0x2222BBBB

#define MSG_LPM_A7_HIGHBUS_READY        0xFFFF6666

#define GPC_SYNC_DELAY_CNT              65536

/*
 * LPM state of M4 core
 */
typedef enum lpm_power_status_m4 {
    LPM_M4_STATE_RUN,
    LPM_M4_STATE_WAIT,
    LPM_M4_STATE_STOP,
} LPM_POWER_STATUS_M4;

/*
 * Clock Speed of M4 core
 */
typedef enum lpm_m4_clock_speed {
    LPM_M4_HIGH_FREQ,
    LPM_M4_LOW_FREQ
} LPM_M4_CLOCK_SPEED;

/*
 * Linklist of wakeup interrupt
 */
typedef struct wakeup_int_ele WAKEUP_INT_ELE, *P_WAKEUP_INT_ELE;
struct wakeup_int_ele {
    P_WAKEUP_INT_ELE next;
    uint32_t irq_no;
    uint32_t irq_priority_backup;
};

/*
 * low power driver initialization
 */
void LPM_MCORE_Init(GPC_Type * base);

/*
 * get the current lpm state of M4 core
 */
LPM_POWER_STATUS_M4 LPM_MCORE_GetPowerStatus(GPC_Type * base);

/*
 * set the next lpm state of M4 core, the state will be entered
 * next time WFI is executed
 */
void LPM_MCORE_SetPowerStatus(GPC_Type * base, LPM_POWER_STATUS_M4 m4_next_lpm);

/*
 * provide readable information of current m4 core lpm state
 */
const char* LPM_MCORE_GetPowerStatusString(void);

/*
 * register/unregister a peripherail interrupt to M4 core wakeup interrupt
 */
void LPM_MCORE_RegisterWakeupInterrupt(GPC_Type * base, uint32_t irq_no, GPC_IRQ_WAKEUP_MODE wakeup_mode);

/*
 * change the m4 core clock between 24MHz(OSC) and 240MHz (SysPllDiv2)
 */
void LPM_MCORE_ChangeM4Clock(LPM_M4_CLOCK_SPEED target);

/*
 * Check if A7 LPM driver is ready
 */
uint32_t LPM_MCORE_CheckPeerReady(void);

/*
 * Set M4 LPM driver ready flag to A7 Peer
 */
void LPM_MCORE_SetSelfReady(void);

/*
 * Function to inserted into FreeRTOS idletask hook
 */
void LPM_MCORE_WaitForInt(void);

#endif
