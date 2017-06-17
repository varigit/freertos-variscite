/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
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
#include <string.h>
#include "board.h"
#include "lpm_mcore.h"
#include "debug_console_imx.h"
#include "ccm_imx7d.h"
#include "mu_imx.h"
#include "FreeRTOS.h"
#include "gpt.h"

#define MAXIMUM_24M_DIV 15

static LPM_POWER_STATUS_M4 m4_lpm_state = LPM_M4_STATE_RUN;

static P_WAKEUP_INT_ELE g_wakeup_int_list;

#if defined(__GNUC__) || defined(__CC_ARM)
static void RAM_Wfi(void) __attribute__((section(".ram_function")));
static void RAM_Wfi_End(void) __attribute__((section(".ram_function_end")));
#elif defined(__ICCARM__)
#pragma default_function_attributes = @ ".ram_function"
static void RAM_Wfi(void);
static void RAM_Wfi_End(void);
#pragma default_function_attributes =
#endif

static void GPT_Patch_Prepare(void);

static void (*runInRAM)(void) = NULL;

/*
 * Send Message to A7
 */
static void LPM_MCORE_SendMessage(uint32_t msg)
{
    while (0 == (MUB_SR & MU_SR_TEn(0x8 >> LPM_MCORE_MU_CHANNEL)));
    MUB->TR[LPM_MCORE_MU_CHANNEL] = msg;
    while ((MUB_SR & MU_SR_EP_MASK) != 0);
}

#if (defined(LPM_MCORE_PRINT_DEBUG_INFO) && (LPM_MCORE_PRINT_DEBUG_INFO))
/*
 * Provide a spinning delay, the actual delay time is dependent on the CPU freq
 */
static void my_delay(void)
{
    uint32_t i, j, k;
    for (i=0; i!=DELAY_CNT; i++)
        for (j=0; j!=DELAY_CNT; j++)
            for (k=0; k!=DELAY_CNT; k++)
                __NOP();
    return;
}

/*
 * Use the delay function to demostrate current CPU running freq
 */
static void verify_clock_speed(void)
{
    uint32_t i;
    for (i=0; i!=DELAY_LOOP_CNT_LOW_SPEED; i++) {
        my_delay();
        PRINTF("\rVerify M4 Speed : %2d of %d ... ", i+1, DELAY_LOOP_CNT_LOW_SPEED);
    }
    PRINTF("Done.\r\n");
}
#endif

/*
 * Tool function to copy function area [func_start, func_end] to M4 data area
 * which is TCM in 7Dual Project
 */
static uint8_t* RAM_Function_Copy(uint8_t* func_start, uint8_t* func_end)
{
    uint8_t* ram_code_ptr;
    uint32_t ram_function_start;

    ram_function_start = (uint32_t)func_start & ~0x3;
    ram_code_ptr = pvPortMalloc((uint8_t*)func_end - (uint8_t*)ram_function_start);
    memcpy(ram_code_ptr, (uint8_t*)ram_function_start, (uint32_t)func_end -
           (uint32_t)ram_function_start);
    ram_code_ptr = (uint8_t *)((uint32_t)ram_code_ptr | ((uint32_t)func_start & 0x3));

    return ram_code_ptr;
}

/*
 * This is the critical section of code which should run in TCM and don't
 * have any other dependency. It will be runtime copied from linked address
 * to TCM address
 * Entering it will allow A7 to shutdown highbus. After M4 get wakeup, it
 * will request A7 to resume highbus. When exiting, the highbus resouces
 * have been live again
 */
static void RAM_Wfi(void) {

    /* 
     * Use MU to tell A7 high bus can be released
     *      Note : Function call is not working in this RAM migrated function
     */
    while (0 == (MUB_SR & MU_SR_TEn(0x8 >> LPM_MCORE_MU_CHANNEL)));
    MUB->TR[LPM_MCORE_MU_CHANNEL] = MSG_LPM_M4_RELEASE_HIGHBUS;
    while ((MUB_SR & MU_SR_EP_MASK) != 0);

    /* 
     * this WFI will only be wakeup by wakeup interrupt registered
     * by "LPM_MCORE_RegisterWakeupInterrupt"
     */
    __WFI();

    /*
     * Tell A7 that M4 has return from LPM mode
     */
    while (0 == (MUB_SR & MU_SR_TEn(0x8 >> LPM_MCORE_MU_CHANNEL)));
    MUB->TR[LPM_MCORE_MU_CHANNEL] = MSG_LPM_M4_RUN;
    while ((MUB_SR & MU_SR_EP_MASK) != 0);
    /* 
     * After wakeup, req A7 to resume clock, wait until getting ACK
     */
    while (0 == (MUB_SR & MU_SR_TEn(0x8 >> LPM_MCORE_MU_CHANNEL)));
    MUB->TR[LPM_MCORE_MU_CHANNEL] = MSG_LPM_M4_REQUEST_HIGHBUS;
    while ((MUB_SR & MU_SR_EP_MASK) != 0);

    while (1)
    {
        if ((MUB_SR & (MU_SR_RFn(0x8 >> LPM_MCORE_MU_CHANNEL))) != 0)
            if (MUB->RR[LPM_MCORE_MU_CHANNEL] == MSG_LPM_A7_HIGHBUS_READY)
                break;
    }

    /* 
     * manual clear MU pending interrupt
     */
    NVIC->ICPR[((uint32_t)(MU_M4_IRQn) >> 5)] = (1 << ((uint32_t)(MU_M4_IRQn) & 0x1F));
}

/*
 * Stub function which only serves as the end address of function "RAM_Wfi"
 */
static void RAM_Wfi_End(void)
{
    return;
}

/*!
 * @brief Check if "RAM_Wfi" is located inside TCM, if not so, copy it to TCM
 */
void prepare_ram_wfi()
{
    if (((uint32_t)RAM_Wfi < 0x1FFF8000) || ((uint32_t)RAM_Wfi > 0x20007FFF))
        // If no, copy the RAM_Wfi function to TCM.
        runInRAM = (void(*)(void))RAM_Function_Copy((uint8_t *)RAM_Wfi,
                                                    (uint8_t *)RAM_Wfi_End);
    else
        // If yes, just assign RAM_Wfi to runInRAM pointer.
        runInRAM = RAM_Wfi;
}

/*
 * initialize the wakeup interrupt list
 */
static void lpm_init_wakeup_interrupt_list() {
    g_wakeup_int_list = NULL;
}

/*
 * add a new irq to wakeup interrupt link list
 */
static void lpm_add_wakeup_interrupt_list(uint32_t irq_no)
{
    P_WAKEUP_INT_ELE cur_ele = g_wakeup_int_list;
    P_WAKEUP_INT_ELE p;

    if (cur_ele == NULL) {
        /*
         * first element to add
         */
        p = pvPortMalloc(sizeof(WAKEUP_INT_ELE));
        p->irq_no = irq_no;
        p->next = NULL;
        g_wakeup_int_list = p;
    } else {
        for (;;) {
            if (cur_ele->irq_no == irq_no) {
                /*
                 * already in the link list
                 *      - return directly
                 */
                break;
            }
            else if (cur_ele->next == NULL) {
                /*
                 * can't find the element
                 *      - insert into the end
                 */
                p = pvPortMalloc(sizeof(WAKEUP_INT_ELE));
                p->irq_no = irq_no;
                p->next = NULL;
                cur_ele->next = p;
            } else {
                cur_ele = cur_ele->next;
            }
        }
    }
}

/*
 * remove an exsiting irq to wakeup interrupt link list
 */
static void lpm_del_wakeup_interrupt_list(uint32_t irq_no)
{
    P_WAKEUP_INT_ELE cur_ele = g_wakeup_int_list;
    P_WAKEUP_INT_ELE p;

    if (cur_ele != NULL) {
        if (cur_ele->irq_no == irq_no) {
            /*first element is the target*/
            p = g_wakeup_int_list;
            g_wakeup_int_list = p->next;
            vPortFree(p);
        } else {
            for (;;) {
                p = cur_ele->next;
                if (p == NULL) {
                    /*
                     * can't find the element
                     *      - return directly
                     */
                    break;
                } else {
                    if (p->irq_no == irq_no) {
                        /*
                         * Find the target "p"
                         */
                        cur_ele->next = p->next;
                        vPortFree(p);
                        break;
                    } else {
                        cur_ele = cur_ele->next;
                    }
                }
            }
        }
    }
}


/*
 * register a IRQ source as M4 wakeup source
 */
void LPM_MCORE_RegisterWakeupInterrupt(GPC_Type * base, uint32_t irq_no, GPC_IRQ_WAKEUP_MODE wakeup_mode)
{
    /*register wakeup interrupt for M4 in GPC*/
    GPC_EnableM4WakeupIRQ(base, irq_no, wakeup_mode);

    if (wakeup_mode == GPC_IRQ_WAKEUP_ENABLE) {
        /*add an element to link list*/
        lpm_add_wakeup_interrupt_list(irq_no);
    } else {
        /*delete an element to link list*/
        lpm_del_wakeup_interrupt_list(irq_no);
    }
}


/*
 * Low Power Management initialization
 */
void LPM_MCORE_Init(GPC_Type * base)
{
    // Init GPC
    GPC_Init(base);

    // Copy critical function to TCM Space
    prepare_ram_wfi();

    // Init the wakeup interrupt link list
    lpm_init_wakeup_interrupt_list();

    // GPT4 Patch, see function implementation for details
    GPT_Patch_Prepare();
}


/*
 * get the current m4 LPM state
 */
LPM_POWER_STATUS_M4 LPM_MCORE_GetPowerStatus(GPC_Type * base)
{
    return m4_lpm_state;
} 

/*
 * on-the-fly change m4 parent clock between 24MHz and 240MHz
 */
void LPM_MCORE_ChangeM4Clock(LPM_M4_CLOCK_SPEED target)
{
    // change CCM Root to change M4 clock
    switch (target) {
        case LPM_M4_LOW_FREQ:
            if (CCM_GetRootMux(CCM, ccmRootM4) != ccmRootmuxM4Osc24m) {
            #if (defined(LPM_MCORE_PRINT_DEBUG_INFO) && (LPM_MCORE_PRINT_DEBUG_INFO))
                PRINTF("Change M4 clock freq to 24M\r\n");
            #endif
                CCM_SetRootMux(CCM, ccmRootM4, ccmRootmuxM4Osc24m);
            }
            break;
        case LPM_M4_HIGH_FREQ:
            if (CCM_GetRootMux(CCM, ccmRootM4) != ccmRootmuxM4SysPllDiv2) {
            #if (defined(LPM_MCORE_PRINT_DEBUG_INFO) && (LPM_MCORE_PRINT_DEBUG_INFO))
                PRINTF("Change M4 clock freq to SysPLL Div2 (240M)\r\n");
            #endif
                CCM_SetRootMux(CCM, ccmRootM4, ccmRootmuxM4SysPllDiv2);
            }
            break;
        default:
            break;
    }
#if (defined(LPM_MCORE_PRINT_DEBUG_INFO) && (LPM_MCORE_PRINT_DEBUG_INFO))
    verify_clock_speed();
#endif
}

/*
 * cycle M4 low power mode to next state, the state machine is
 *
 *        +---> "RUN" ---> "WAIT" ---> "STOP" ---+
 *        |                                      |
 *        +--------------------------------------+
 */
void LPM_MCORE_SetPowerStatus(GPC_Type * base, LPM_POWER_STATUS_M4 m4_next_lpm)
{
    uint32_t next_lpm = GPC_LPCR_M4_LPM0(0);
    switch (m4_next_lpm) {
        case LPM_M4_STATE_RUN:
            next_lpm = GPC_LPCR_M4_LPM0(0);
            break;
        case LPM_M4_STATE_WAIT:
            next_lpm = GPC_LPCR_M4_LPM0(1);
            break;
        case LPM_M4_STATE_STOP:
            next_lpm = GPC_LPCR_M4_LPM0(2);
            break;
        default:
            break;
    }

    /*
     * Patch, let GPC-M4 observe the GPR0 interrupt for a period as long
     * as 5 32KHz clock cycle before set it to a Low power status
     */
    if (m4_next_lpm != LPM_M4_STATE_RUN)
    {
        uint32_t i;
        LPM_MCORE_RegisterWakeupInterrupt(GPC, GPT4_IRQn, GPC_IRQ_WAKEUP_ENABLE);
        for (i=0; i!=GPC_SYNC_DELAY_CNT; i++)
            __NOP();
        LPM_MCORE_RegisterWakeupInterrupt(GPC, GPT4_IRQn, GPC_IRQ_WAKEUP_DISABLE);
    }

    GPC_SetM4NextLPM(base, next_lpm);

    /*change lpm state variable*/
    m4_lpm_state = m4_next_lpm;
}



/*
 * Give readable string of current M4 lpm state
 */
const char* LPM_MCORE_GetPowerStatusString(void)
{
    switch (m4_lpm_state) {
        case LPM_M4_STATE_RUN:
            return "RUN";
        case LPM_M4_STATE_WAIT:
            return "WAIT";
        case LPM_M4_STATE_STOP:
            return "STOP";
        default:
            return "UNKNOWN";
    }
}

/*
 * Check if A7 LPM Driver is ready, an "Once Ready, Always Ready" logic is used
 */
uint32_t LPM_MCORE_CheckPeerReady(void) 
{
    static uint32_t a7_ready = 0;
    if (!a7_ready) {
        a7_ready = MU_GetFlags(MUB) & MU_SR_Fn(1);
    }
    return a7_ready;
}

/*
 * Use MU Flag to indicate to A7 that low power management in M4 is ready
 */
void LPM_MCORE_SetSelfReady(void)
{
    MU_SetFlags(MUB, MU_CR_Fn(1));
}

/*
 * This function modify BASEPRI to configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY and
 * wakeup interrupt's NVIC->Priority to configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY - 1
 * The effect is all non-wakeup interrupt gets mute
 * The original basepri settings are stored into pBasepriBackup
 * The original wakeup interrupt nvic->priority settings are stored into linklist
 */
void lpm_disable_non_wakeup_interrupt(uint32_t* pBasepriBackup)
{
    P_WAKEUP_INT_ELE ele;
    uint32_t irq_no;
#if defined(__CC_ARM)
    register uint32_t __regBasePri __ASM("basepri");
    *pBasepriBackup = __regBasePri;
    __regBasePri  = (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - __NVIC_PRIO_BITS));
#else
    *pBasepriBackup = __get_BASEPRI();
    __set_BASEPRI(configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - __NVIC_PRIO_BITS));
#endif
    /*
     * Make exceptions to wakeup interrupts, they are stored in "g_wakeup_int_list"
     */
    ele = g_wakeup_int_list;
    for (;;) {
        if (ele == NULL)
            break;

        /* 
         * Store the current Priority into ele backup field
         * Change the Priority to "configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY - 1"
         */
        irq_no = ele->irq_no;
        ele->irq_priority_backup = NVIC->IP[irq_no];
        NVIC->IP[irq_no] = (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY - 1) << (8 - __NVIC_PRIO_BITS);

        /*
         * Move to next
         */
        ele = ele->next;
    }
    __DSB();
    __ISB();
}

/*
 * This function restores BASEPRI and wakeup interrupt nvic priority settings
 * It recover interrupt settings made by lpm_disable_non_wakeup_interrupt
 */
void lpm_enable_non_wakeup_interrupt(uint32_t basePriBackup)
{
    P_WAKEUP_INT_ELE ele;
    uint32_t irq_no;
#if defined(__CC_ARM)
    register uint32_t __regBasePri __ASM("basepri");
#endif
    /*
     * first restore wakeup interrupt priority
     */
    ele = g_wakeup_int_list;
    for (;;) {
        if (ele == NULL)
            break;

        /* 
         * Restore the original priority
         */
        irq_no = ele->irq_no;
        NVIC->IP[irq_no] = ele->irq_priority_backup;

        /*
         * Move to next
         */
        ele = ele->next;
    }
#if defined(__CC_ARM)
    __regBasePri = basePriBackup & 0xFF;
#else
    __set_BASEPRI(basePriBackup);
#endif
    // infinite_loop();
    // Are these necessary?
    __DSB();
    __ISB();
}


/*
 * The sleep function inserted into FreeRTOS idle task hook
 */
void LPM_MCORE_WaitForInt(void)
{
    uint32_t priMaskBackup;

    /* 
     * Only when 
     *      1. A7 peer is ready
     *      2. safe sleep function has been put into TCM
     *      3. m4 true sleep mode has been allowed
     *      4. m4 current lpm mode is wait / stop
     *  The "power save wfi" routine will be executed
     *  Otherwise "normal wfi" will be executed
     *
     *  In Power Save WFI
     *      - PRIMASK is set, so all interrupt handler won't be executed
     *      - BASEPRI and NVIC->Priority is modified so that only wakeup interrupt can
     *        wake up M4 from WFI
     *      - After M4 wake up, NVIC->Priority, BASEPRI and PRIMASK are restored so that
     *        the system return to normal mode
     *
     *  There is a critical section code which is in "runInRAM", inside it M4 will
     *  inform A7 it release the high bus. A7 can then shutdown the high bus which
     *  will make all highbus related peripherals losing functionality, including
     *  DDR, so code in "runInRAM" should run in TCM and don't have any access to
     *  other part of memory
     */
    if (LPM_MCORE_CheckPeerReady() && (runInRAM != NULL))
    {
        volatile uint32_t* reg_lpcr_m4 = &GPC->LPCR_M4;

        uint32_t next_lpm_mode = *reg_lpcr_m4 & GPC_LPCR_M4_LPM0_MASK;
        uint32_t basePriBackup;

        /* Save current PRIMASK value. */
        priMaskBackup = __get_PRIMASK();

        /* 
         * Set PRIMASK to avoid execution of any enabled ISR. 
         *      Note : PRIMASK will not prevent interrupt to wake up M4 from WFI
         *             but it will prevent interrupt handler from running
         */
        __set_PRIMASK(1);
        /* Barriers are normally not required but do ensure the code is completely
         * within the specified behaviour for the architecture.
         */
        __DSB();
        __ISB();
        /*
         * Some of the code should be moved out of "runInRAM"
         */
        switch (next_lpm_mode) {
            case LPCR_M4_RUN:
                /*
                 * STOP -> RUN
                 */
                /*
                 * tell A7 the next LPM mode is RUN
                 */
                /*
                 * the WFI will be wakeup by any enabled interrupt
                 */
                __WFI();
                break;
            case LPCR_M4_WAIT:
            case LPCR_M4_STOP:
                /*
                 * RUN -> WAIT or WAIT -> STOP
                 */
                /*
                 * tell A7 the next LPM mode is WAIT/STOP
                 */
                if (next_lpm_mode == LPCR_M4_WAIT)
                    LPM_MCORE_SendMessage(MSG_LPM_M4_WAIT);
                else if (next_lpm_mode == LPCR_M4_STOP)
                    LPM_MCORE_SendMessage(MSG_LPM_M4_STOP);
                /* 
                 * do modification to BASEPRI and NVIC->Priority settings so that
                 * all interrupt except wakeup interrupt are disabled
                 */
                lpm_disable_non_wakeup_interrupt(&basePriBackup);

                /*
                 * Inside "runInRAM", M4 will inform A7 that it release the highbus. Later
                 * when M4 is waken up, it will request A7 to resume highbus. This section
                 * of code must run in TCM to avoid accessing highbus dependent resouces
                 */
                runInRAM();

                // Restore Basepri and NVIC->Priority settings
                lpm_enable_non_wakeup_interrupt(basePriBackup);
                break;
            default:
                break;
        }
        /* 
         * Recover PRIMASK register value. this will enable the wakeup interrupt
         * handler and will activate the main task immediately
         */
        __set_PRIMASK(priMaskBackup);

        /* Barriers are normally not required but do ensure the code is completely
         * within the specified behaviour for the architecture. */
        __DSB();
        __ISB();
    }
    else {
        /*
         * Normal WFI which will be wakeup by any enabled interrupt
         */
        __WFI();
    }
}

/*
 * This function implement a patch for "TO1.1" chips
 *     - In "TO1.1" chips. Everytime a WFI is executed, IC set an internal
 *       "dsm-request" signal. The signal is NOT deasserted when WFI is
 *       executed, until a GPC wakeup interrupt happens. When this signal
 *       asserts, setting "LPM_M4" to "WAIT" or "STOP" will immediately
 *       cause the M4 core enter sleep mode, rather than the next time "WFI"
 *       is executed. Only a wakeup interrupt can clear the "dsm-request" signal
 *
 *     - The issue is like IC Errata ticket "ERR007265" in i.MX6
 *
 *     - As suggested by IC, software should let GPC observe an interrupt long
 *       enough before setting "LPM_M4". Here we utilize an GPT to trigger this
 *       interrupt.
 *
 *       An GPT will be configured to generate a interrupt at the very beginning,
 *       this interrupt is masked by M4 NVIC so M4 will not respond to it. But
 *       every time M4 is wake up, before the next time GPC.LPM_M4 is modified,
 *       GPC.M4_IMR will be set to unmask this pending interrupt to GPC module
 *       only, the IRQ will be unmasked for a interval long enough (longer than
 *       5 32K clock cycle as suggested by IC) and then be masked again.
 *
 *     - The function configures GPTB to generate a pending interrupt. 
 */
static void GPT_Patch_Prepare(void) {
    uint64_t counter = 24000 * 5; /* Requrie 5ms to generate the pending interrupt*/
    uint32_t high;
    uint32_t div24m, div;

    gpt_init_config_t config = {
        .freeRun    = false,
        .waitEnable = true,
        .stopEnable = true,
        .dozeEnable = true,
        .dbgEnable  = false,
        .enableMode = true
    };

    GPT_Init(BOARD_GPTB_BASEADDR, &config);

    /* Set GPT clock source to 24M OSC */
    GPT_SetClockSource(BOARD_GPTB_BASEADDR, gptClockSourceOsc);

    /* Get the value that exceed maximum register counter */
    high = (uint32_t)(counter >> 32);

    div24m = MAXIMUM_24M_DIV; /*Since we use 24MHz as GPT peripheral clock, here we set the 24M divider to maximum value*/
    div = high / (div24m + 1); /* Get PRESCALER value */

    /* Now set prescaler */
    GPT_SetOscPrescaler(BOARD_GPTB_BASEADDR, div24m);
    GPT_SetPrescaler(BOARD_GPTB_BASEADDR, div);

    /* Set GPT compare value */
    GPT_SetOutputCompareValue(BOARD_GPTB_BASEADDR, gptOutputCompareChannel1,
                              (uint32_t)(counter / (div24m + 1) / (div + 1)));

    /* Enable GPT Output Compare1 interrupt */
    GPT_SetIntCmd(BOARD_GPTB_BASEADDR, gptStatusFlagOutputCompare1, true);

    /* GPT start */
    GPT_Enable(BOARD_GPTB_BASEADDR);

    /* Wait until timer reaches*/
    while ((BOARD_GPTB_BASEADDR->SR & gptStatusFlagOutputCompare1) == gptStatusFlagOutputCompare1) {
        GPT_Disable(BOARD_GPTB_BASEADDR);
    }
}
