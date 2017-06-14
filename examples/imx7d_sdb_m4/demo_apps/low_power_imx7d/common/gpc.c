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

#include "gpc.h"

/*
 * Initialize GPC settings for dual core low power management
 */
void GPC_Init(GPC_Type * base)
{
    /*
     * Disable all M4 interrupt as GPC wakeup source
     */
    base->IMR1_M4 = GPC_IMR1_M4_IMR1_M4_MASK;
    base->IMR2_M4 = GPC_IMR2_M4_IMR2_M4_MASK;
    base->IMR3_M4 = GPC_IMR3_M4_IMR3_M4_MASK;
    base->IMR4_M4 = GPC_IMR4_M4_IMR4_M4_MASK;

    /*
     * Initialize the GPC settings for M4
     */
    base->LPCR_M4 |= GPC_LPCR_M4_EN_M4_PUP_MASK |
        GPC_LPCR_M4_EN_M4_PDN_MASK;  /* EN_M4_PUP, EN_M4_PDN*/
    base->PGC_ACK_SEL_M4 = GPC_PGC_ACK_SEL_M4_M4_VIRTUAL_PGC_PUP_ACK_MASK |
        GPC_PGC_ACK_SEL_M4_M4_VIRTUAL_PGC_PDN_ACK_MASK; /* change dummy to virtual*/
    base->MISC |= GPC_MISC_M4_PDN_REQ_MASK_MASK; /* not mask M4 power down*/

    /*
     * M4 Virtual domain and Fast Mega domain must use the same PUP/PDN slot
     * Align to A7, SLT 1 and SLT 5 are used for Fast Mega and M4 Virtual domain
     */
    base->SLT_CFG[1] = GPC_SLT_CFG_M4_VIRTUAL_PDN_SLOT_CONTROL_MASK | GPC_SLT_CFG_FASTMEGA_PDN_SLOT_CONTROL_MASK;
    base->SLT_CFG[5] = GPC_SLT_CFG_M4_VIRTUAL_PUP_SLOT_CONTROL_MASK | GPC_SLT_CFG_FASTMEGA_PUP_SLOT_CONTROL_MASK;

    /* 
     * Fast map to both A7 and M4
     *      - M4 only have access to byte 1, A7 only have access to byte 0
     *      - set to 1 for "map" 
     */
    base->PGC_CPU_MAPPING = GPC_PGC_CPU_MAPPING_FASTMEGA_M4_DOMAIN_MASK; 
}

/*
 * Enable an interrupt source as GPC wakeup source for M4 core
 */
void GPC_EnableM4WakeupIRQ(GPC_Type* base, uint32_t irq_no, GPC_IRQ_WAKEUP_MODE wakeup_mode)
{
    uint32_t reg_index, reg_offset;
    volatile uint32_t* target_reg;

    if (irq_no < TOTAL_IRQ_NUM) {
        reg_index = irq_no / IRQ_PER_REGISTER;
        reg_offset = irq_no % IRQ_PER_REGISTER;
        target_reg = &base->IMR1_M4 + reg_index;
        if (wakeup_mode == GPC_IRQ_WAKEUP_ENABLE) {
            /*enable the IRQ as wakeup source*/
            *target_reg &= ~(1 << reg_offset);
        }
        else {
            /*disable the IRQ as wakeup source*/
            *target_reg |= 1 << reg_offset;
        }
    }
}

/*
 * Configure LPCR_M4_LPM, the configured LPM state will be entered
 * the next time WFI is executed
 */
void GPC_SetM4NextLPM(GPC_Type* base, uint32_t lpm_val)
{
    if (lpm_val < 4) {
        base->LPCR_M4 = (base->LPCR_M4 & ~GPC_LPCR_M4_LPM0_MASK) | lpm_val;
    }
}
