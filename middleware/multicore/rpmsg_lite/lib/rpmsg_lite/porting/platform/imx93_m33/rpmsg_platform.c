/*
 * Copyright 2021-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdio.h>
#include <string.h>
#include "rpmsg_platform.h"
#include "rpmsg_env.h"

#include "fsl_device_registers.h"
#include "fsl_mu.h"

#if defined(RL_USE_ENVIRONMENT_CONTEXT) && (RL_USE_ENVIRONMENT_CONTEXT == 1)
#error "This RPMsg-Lite port requires RL_USE_ENVIRONMENT_CONTEXT set to 0"
#endif

static int32_t isr_counter0 = 0; /* RL_PLATFORM_IMX93_M33_A55_USER_LINK_ID isr counter */

static int32_t disable_counter0 = 0;
static void *platform_lock;
#if defined(RL_USE_STATIC_API) && (RL_USE_STATIC_API == 1)
static LOCK_STATIC_CONTEXT platform_lock_static_ctxt;
#endif

static void platform_global_isr_disable(void)
{
    __asm volatile("cpsid i");
}

static void platform_global_isr_enable(void)
{
    __asm volatile("cpsie i");
}

int32_t platform_init_interrupt(uint32_t vector_id, void *isr_data)
{
    /* Register ISR to environment layer */
    env_register_isr(vector_id, isr_data);

    /* Prepare the MU Hardware, enable channel 1 interrupt */
    env_lock_mutex(platform_lock);

    switch (RL_GET_COM_ID(vector_id))
    {
        case RL_PLATFORM_IMX93_M33_A55_COM_ID:
            RL_ASSERT(0 <= isr_counter0);
            if (isr_counter0 == 0)
            {
                MU_EnableInterrupts(RPMSG_LITE_M33_A55_MU, (uint32_t)kMU_Rx0FullInterruptEnable << RPMSG_MU_CHANNEL);
            }
            isr_counter0++;
            break;
        default:
            /* All the cases have been listed above, the default clause should not be reached. */
            break;
    }

    env_unlock_mutex(platform_lock);

    return 0;
}

int32_t platform_deinit_interrupt(uint32_t vector_id)
{
    /* Prepare the MU Hardware */
    env_lock_mutex(platform_lock);

    switch (RL_GET_COM_ID(vector_id))
    {
        case RL_PLATFORM_IMX93_M33_A55_COM_ID:
            RL_ASSERT(0 < isr_counter0);
            isr_counter0--;
            if (isr_counter0 == 0)
            {
                MU_DisableInterrupts(RPMSG_LITE_M33_A55_MU, (uint32_t)kMU_Rx0FullInterruptEnable << RPMSG_MU_CHANNEL);
            }
            break;
        default:
            /* All the cases have been listed above, the default clause should not be reached. */
            break;
    }

    /* Unregister ISR from environment layer */
    env_unregister_isr(vector_id);

    env_unlock_mutex(platform_lock);

    return 0;
}

void platform_notify(uint32_t vector_id)
{
    /* Only vring id and queue id is needed in msg */
    uint32_t msg = RL_GEN_MU_MSG(vector_id);

    env_lock_mutex(platform_lock);
    /* As Linux suggests, use MU->Data Channel 1 as communication channel */
    switch (RL_GET_COM_ID(vector_id))
    {
        case RL_PLATFORM_IMX93_M33_A55_COM_ID:
            MU_SendMsg(RPMSG_LITE_M33_A55_MU, RPMSG_MU_CHANNEL, msg);
            break;
        default:
            /* All the cases have been listed above, the default clause should not be reached. */
            break;
    }
    env_unlock_mutex(platform_lock);
}

/*
 * MU Interrrupt RPMsg handler
 */
int32_t MU1_A_IRQHandler(void)
{
    uint32_t channel;

    if ((((uint32_t)kMU_Rx0FullFlag << RPMSG_MU_CHANNEL) & MU_GetStatusFlags(RPMSG_LITE_M33_A55_MU)) != 0UL)
    {
        channel = MU_ReceiveMsgNonBlocking(RPMSG_LITE_M33_A55_MU, RPMSG_MU_CHANNEL); // Read message from RX register.
        env_isr((uint32_t)((channel >> 16) | (RL_PLATFORM_IMX93_M33_A55_COM_ID << 3)));
    }

    return 0;
}

/**
 * platform_time_delay
 *
 * @param num_msec Delay time in ms.
 *
 * This is not an accurate delay, it ensures at least num_msec passed when return.
 */
void platform_time_delay(uint32_t num_msec)
{
    uint32_t loop;

    /* Recalculate the CPU frequency */
    SystemCoreClockUpdate();

    /* Calculate the CPU loops to delay, each loop has 3 cycles */
    loop = SystemCoreClock / 3U / 1000U * num_msec;

    /* There's some difference among toolchains, 3 or 4 cycles each loop */
    while (loop > 0U)
    {
        __NOP();
        loop--;
    }
}

/**
 * platform_in_isr
 *
 * Return whether CPU is processing IRQ
 *
 * @return True for IRQ, false otherwise.
 *
 */
int32_t platform_in_isr(void)
{
    return (((SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0UL) ? 1 : 0);
}

/**
 * platform_interrupt_enable
 *
 * Enable peripheral-related interrupt
 *
 * @param vector_id Virtual vector ID that needs to be converted to IRQ number
 *
 * @return vector_id Return value is never checked.
 *
 */
int32_t platform_interrupt_enable(uint32_t vector_id)
{
    platform_global_isr_disable();
    switch (RL_GET_COM_ID(vector_id))
    {
        case RL_PLATFORM_IMX93_M33_A55_COM_ID:
            RL_ASSERT(0 < disable_counter0);
            disable_counter0--;
            if (disable_counter0 == 0)
            {
                NVIC_EnableIRQ(RPMSG_LITE_M33_A55_MU_IRQn);
            }
            break;
        default:
            /* All the cases have been listed above, the default clause should not be reached. */
            break;
    }
    platform_global_isr_enable();
    return ((int32_t)vector_id);
}

/**
 * platform_interrupt_disable
 *
 * Disable peripheral-related interrupt.
 *
 * @param vector_id Virtual vector ID that needs to be converted to IRQ number
 *
 * @return vector_id Return value is never checked.
 *
 */
int32_t platform_interrupt_disable(uint32_t vector_id)
{
    platform_global_isr_disable();
    /* virtqueues use the same NVIC vector
       if counter is set - the interrupts are disabled */
    switch (RL_GET_COM_ID(vector_id))
    {
        case RL_PLATFORM_IMX93_M33_A55_COM_ID:
            RL_ASSERT(0 <= disable_counter0);
            disable_counter0++;
            if (disable_counter0 == 0)
            {
                NVIC_DisableIRQ(RPMSG_LITE_M33_A55_MU_IRQn);
            }
            break;
        default:
            /* All the cases have been listed above, the default clause should not be reached. */
            break;
    }
    platform_global_isr_enable();
    return ((int32_t)vector_id);
}

/**
 * platform_map_mem_region
 *
 * Dummy implementation
 *
 */
void platform_map_mem_region(uint32_t vrt_addr, uint32_t phy_addr, uint32_t size, uint32_t flags)
{
}

/**
 * platform_cache_all_flush_invalidate
 *
 * Dummy implementation
 *
 */
void platform_cache_all_flush_invalidate(void)
{
}

/**
 * platform_cache_disable
 *
 * Dummy implementation
 *
 */
void platform_cache_disable(void)
{
}

/**
 * platform_vatopa
 *
 * Dummy implementation
 *
 */
uintptr_t platform_vatopa(void *addr)
{
    return ((uintptr_t)(char *)addr);
}

/**
 * platform_patova
 *
 * Dummy implementation
 *
 */
void *platform_patova(uintptr_t addr)
{
    return ((void *)(char *)addr);
}

/**
 * platform_init
 *
 * platform/environment init
 */
int32_t platform_init(void)
{
    /*
     * Prepare for the MU Interrupt
     *  MU must be initialized before rpmsg init is called
     */
    MU_Init(RPMSG_LITE_M33_A55_MU);
    NVIC_SetPriority(RPMSG_LITE_M33_A55_MU_IRQn, RPMSG_LITE_MU_IRQ_PRIORITY);
    NVIC_EnableIRQ(RPMSG_LITE_M33_A55_MU_IRQn);

    /* Create lock used in multi-instanced RPMsg */
#if defined(RL_USE_STATIC_API) && (RL_USE_STATIC_API == 1)
    if (0 != env_create_mutex(&platform_lock, 1, &platform_lock_static_ctxt))
#else
    if (0 != env_create_mutex(&platform_lock, 1))
#endif
    {
        return -1;
    }

    return 0;
}

/**
 * platform_deinit
 *
 * platform/environment deinit process
 */
int32_t platform_deinit(void)
{
    MU_Deinit(RPMSG_LITE_M33_A55_MU);
    /* Delete lock used in multi-instanced RPMsg */
    env_delete_mutex(platform_lock);
    platform_lock = ((void *)0);
    return 0;
}
