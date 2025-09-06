/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "hal_config.h"
#include "hal_clock.h"
#if SM_CLOCK
#include "sm_clock.h"
#elif CCM_CLOCK
#include "fsl_ccm.h"
#include "fsl_clock.h"
#endif

#if SM_CLOCK && CCM_CLOCK
#error "Pls not define them as 1 at the same time in hal_config.h!!!"
#endif

volatile uint64_t g_halClkFreq[HAL_CLOCK_PLATFORM_MAX_ID] = {0ULL};

#if SM_CLOCK

#ifndef HAL_CLOCK_RATE_FLAGS_ROUND
/* Refer to components/scmi/scmi_clock.h */
#define HAL_CLOCK_RATE_FLAGS_ROUND(x) SCMI_CLOCK_RATE_FLAGS_ROUND(x)
#endif

/* The api is deprecated.It's replaced by HAL_ClockGetParent, HAL_ClockSetParent, HAL_ClockGetRate, HAL_ClockSetRate and HAL_ClockEnable. */
void HAL_ClockSetRootClk(hal_clk_t *hal_clk)
{
    sm_clock_t sm_clk         = {0};
    uint32_t clk_round_option = (uint32_t)hal_clk->clk_round_opt;

    sm_clk.clk_id     = (uint32_t)hal_clk->clk_id;
    sm_clk.pclk_id    = (uint32_t)hal_clk->pclk_id;
    sm_clk.channel    = SM_PLATFORM_A2P;
    sm_clk.div        = hal_clk->div;
    sm_clk.attributes = (uint32_t)SCMI_CLOCK_CONFIG_SET_ENABLE((uint32_t)hal_clk->enable_clk);

    switch (hal_clk->clk_round_opt)
    {
        case hal_clk_round_down:
            clk_round_option = SCMI_CLOCK_ROUND_DOWN;
            break;
        case hal_clk_round_up:
            clk_round_option = SCMI_CLOCK_ROUND_UP;
            break;
        case hal_clk_round_auto:
            clk_round_option = SCMI_CLOCK_ROUND_AUTO;
            break;
        default:
	    /* do nothing but fix MISRA C-2012 Rule 16.4 */
            break;
    }
    sm_clk.flags = SCMI_CLOCK_RATE_FLAGS_ROUND(clk_round_option);

    SM_CLOCK_SetRootClock(&sm_clk);
}


/* The api is deprecated.It's replaced by HAL_ClockEnable. */
void HAL_ClockEnableRootClk(hal_clk_t *hal_clk)
{
    sm_clock_t sm_clk         = {0};
    uint32_t clk_round_option = (uint32_t)hal_clk->clk_round_opt;

    sm_clk.clk_id     = (uint32_t)hal_clk->clk_id;
    sm_clk.channel    = SM_PLATFORM_A2P;
    sm_clk.attributes = (uint32_t)SCMI_CLOCK_CONFIG_SET_ENABLE((uint32_t)hal_clk->enable_clk);

    switch (hal_clk->clk_round_opt)
    {
        case hal_clk_round_down:
            clk_round_option = SCMI_CLOCK_ROUND_DOWN;
            break;
        case hal_clk_round_up:
            clk_round_option = SCMI_CLOCK_ROUND_UP;
            break;
        case hal_clk_round_auto:
            clk_round_option = SCMI_CLOCK_ROUND_AUTO;
            break;
        default:
	    /* do nothing but fix MISRA C-2012 Rule 16.4 */
            break;
    }
    sm_clk.flags = SCMI_CLOCK_RATE_FLAGS_ROUND(clk_round_option);

    SM_CLOCK_EnableRootClock(&sm_clk);
}

/*!
 * @brief Configure PLL Clock
 *
 * @param hal_clk
 * The api is deprecated.It's replaced by HAL_ClockSetRate.
 */
void HAL_ClockSetPllClk(hal_clk_t *hal_clk)
{
    sm_clock_t sm_clk         = {0};
    uint32_t clk_round_option = (uint32_t)hal_clk->clk_round_opt;

    sm_clk.clk_id     = (uint32_t)hal_clk->clk_id;
    sm_clk.channel    = SM_PLATFORM_A2P;
    sm_clk.rateu       = hal_clk->rateu;
    sm_clk.ratel       = hal_clk->ratel;

    switch (hal_clk->clk_round_opt)
    {
        case hal_clk_round_down:
            clk_round_option = SCMI_CLOCK_ROUND_DOWN;
            break;
        case hal_clk_round_up:
            clk_round_option = SCMI_CLOCK_ROUND_UP;
            break;
        case hal_clk_round_auto:
            clk_round_option = SCMI_CLOCK_ROUND_AUTO;
            break;
        default:
	    /* do nothing but fix MISRA C-2012 Rule 16.4 */
            break;
    }
    sm_clk.flags = SCMI_CLOCK_RATE_FLAGS_ROUND(clk_round_option);

    SM_CLOCK_SetPllClock(&sm_clk);
}

/*!
 * @brief return the rate of clk_id
 *
 * @param clk_id
 * The api is deprecated.It's replaced by HAL_ClockGetRate.
 */
uint64_t HAL_ClockGetIpFreq(hal_clk_id_e clk_id)
{
    sm_clock_t sm_clk = {0};

    if ((uint32_t)clk_id < (uint32_t)HAL_CLOCK_PLATFORM_SOURCE_NUM)
    {
        return 0UL;
    }
    sm_clk.clk_id  = (uint32_t)clk_id;
    sm_clk.channel = SM_PLATFORM_A2P;

    g_halClkFreq[clk_id] = SM_CLOCK_GetIpFreq(&sm_clk);

    return g_halClkFreq[clk_id];
}

/*!
 * @brief return the rate of clk_id
 *
 * @param clk_id
 * The api is deprecated.It's replaced by HAL_ClockGetRate.
 */

uint64_t HAL_ClockGetFreq(hal_clk_id_e clk_id)
{
    sm_clock_t sm_clk = {0};

    sm_clk.clk_id  = (uint32_t)clk_id;
    sm_clk.channel = SM_PLATFORM_A2P;
    if ((uint32_t)clk_id >= (uint32_t)HAL_CLOCK_PLATFORM_SOURCE_NUM)
    {
        g_halClkFreq[clk_id] = SM_CLOCK_GetIpFreq(&sm_clk);
    }
    else
    {
        g_halClkFreq[clk_id] = SM_CLOCK_GetSourceFreq(&sm_clk);
    }

    return g_halClkFreq[clk_id];
}

/*!
 * @brief specify a new rate for hal_clk
 *
 * @param hal_clk
 */
int32_t HAL_ClockSetRate(hal_clk_t *hal_clk)
{
    sm_clock_t sm_clk         = {0};
    uint32_t clk_round_option = (uint32_t)hal_clk->clk_round_opt;
    status_t status = kStatus_Success;
    int32_t result = SCMI_ERR_SUCCESS;

    /* check rate */
    assert(hal_clk->rate != 0UL);
    sm_clk.clk_id     = (uint32_t)hal_clk->clk_id;
    sm_clk.channel    = SM_PLATFORM_A2P;
    sm_clk.rateu       = (hal_clk->rate >> 32U) & 0xFFFFFFFF;
    sm_clk.ratel       = hal_clk->rate & 0xFFFFFFFF;

    switch (hal_clk->clk_round_opt)
    {
        case hal_clk_round_down:
            clk_round_option = SCMI_CLOCK_ROUND_DOWN;
            break;
        case hal_clk_round_up:
            clk_round_option = SCMI_CLOCK_ROUND_UP;
            break;
        case hal_clk_round_auto:
            clk_round_option = SCMI_CLOCK_ROUND_AUTO;
            break;
        default:
	    /* do nothing but fix MISRA C-2012 Rule 16.4 */
            break;
    }
    sm_clk.flags = SCMI_CLOCK_RATE_FLAGS_ROUND(clk_round_option);

    result = SM_ClockSetRate(&sm_clk);
    if (result != SCMI_ERR_SUCCESS)
    {
        status = kStatus_Fail;
    }

    return (int32_t)status;
}

/*!
 * @brief return rate of hal_clk
 *
 * @param hal_clk
 */
uint64_t HAL_ClockGetRate(hal_clk_id_e clk_id)
{
    sm_clock_t sm_clk = {0};

    if ((uint32_t)clk_id < (uint32_t)HAL_CLOCK_PLATFORM_SOURCE_NUM)
    {
        return 0UL;
    }
    sm_clk.clk_id  = (uint32_t)clk_id;
    sm_clk.channel = SM_PLATFORM_A2P;

    g_halClkFreq[clk_id] = SM_ClockGetRate(&sm_clk);

    return g_halClkFreq[clk_id];
}

int32_t HAL_ClockEnable(hal_clk_t *hal_clk)
{
    sm_clock_t sm_clk         = {0};
    status_t status = kStatus_Success;
    int32_t result = SCMI_ERR_SUCCESS;

    sm_clk.clk_id     = (uint32_t)hal_clk->clk_id;
    sm_clk.channel    = SM_PLATFORM_A2P;
    sm_clk.attributes = (uint32_t)SCMI_CLOCK_CONFIG_SET_ENABLE(SCMI_CLOCK_STATE_ENABLE);

    result = SM_ClockSetConfig(&sm_clk);
    if (result != SCMI_ERR_SUCCESS)
    {
        status = kStatus_Fail;
    }

    return (int32_t)status;
}

int32_t HAL_ClockDisable(hal_clk_t *hal_clk)
{
    sm_clock_t sm_clk         = {0};
    status_t status = kStatus_Success;
    int32_t result = SCMI_ERR_SUCCESS;

    sm_clk.clk_id     = (uint32_t)hal_clk->clk_id;
    sm_clk.channel    = SM_PLATFORM_A2P;
    sm_clk.attributes = (uint32_t)SCMI_CLOCK_CONFIG_SET_ENABLE(SCMI_CLOCK_STATE_DISABLE);

    result = SM_ClockSetConfig(&sm_clk);
    if (result != SCMI_ERR_SUCCESS)
    {
        status = kStatus_Fail;
    }

    return (int32_t)status;
}

/*!
 * @brief Set clock parent
 *
 * @param hal_clk
 */
int32_t HAL_ClockSetParent(hal_clk_t *hal_clk)
{
    sm_clock_t sm_clk         = {0};
    status_t status = kStatus_Success;
    int32_t result = SCMI_ERR_SUCCESS;

    sm_clk.clk_id     = (uint32_t)hal_clk->clk_id;
    sm_clk.pclk_id     = (uint32_t)hal_clk->pclk_id;
    sm_clk.channel    = SM_PLATFORM_A2P;

    result = SM_ClockSetParent(&sm_clk);
    if (result != SCMI_ERR_SUCCESS)
    {
        status = kStatus_Fail;
    }

    return (int32_t)status;
}

/*!
 * @brief Get clock parent
 *
 * @param hal_clk
 * @param pclk_id: parent clock id
 */
int32_t HAL_ClockGetParent(hal_clk_t *hal_clk, hal_clk_id_e *pclk_id)
{
    sm_clock_t sm_clk         = {0};
    status_t status = kStatus_Success;
    int32_t result = SCMI_ERR_SUCCESS;
    uint32_t parentId;

    sm_clk.clk_id     = (uint32_t)hal_clk->clk_id;
    sm_clk.channel    = SM_PLATFORM_A2P;

    result = SM_ClockGetParent(&sm_clk, &parentId);
    if (result != SCMI_ERR_SUCCESS)
    {
        return (int32_t)kStatus_Fail;
    }
    *pclk_id = (hal_clk_id_e)parentId;

    return (int32_t)status;
}
#elif CCM_CLOCK
#ifndef HAL_CLOCK_RATE_FLAGS_ROUND
#define HAL_CLOCK_RATE_FLAGS_ROUND(x) (x)
#endif

void HAL_ClockSetRootClk(hal_clk_t *hal_clk)
{
    clock_root_t name                   = (clock_root_t)0;
    clock_root_config_t config          = {0};
    const clock_root_config_t *p_config = &config;
    uint32_t mux_id                     = 0;

    config.clockOff = !hal_clk->enable_clk;

    if (hal_clk->clk_id < HAL_CLOCK_PLATFORM_SOURCE_NUM)
    {
        return;
    }
    name = (clock_root_t)(hal_clk->clk_id - HAL_CLOCK_PLATFORM_SOURCE_NUM);
    if (hal_clk->pclk_id > HAL_CLOCK_PLATFORM_SOURCE_NUM)
    {
        return;
    }

    mux_id = HAL_ClockPlatformGetMuxId(hal_clk->clk_id, hal_clk->pclk_id);
    if (mux_id == HAL_CLOCK_PLATFORM_MUX_MAX_ID)
    {
        return;
    }

    config.mux = mux_id;
    config.div = hal_clk->div;

    CLOCK_SetRootClock(name, p_config);
}

/*!
 * @brief Configure PLL Clock
 *
 * @param hal_clk
 * The api is deprecated.It's replaced by HAL_ClockSetRate.
 */
void HAL_ClockSetPllClk(hal_clk_t *hal_clk)
{
}

uint64_t HAL_ClockGetIpFreq(hal_clk_id_e clk_id)
{
    clock_root_t name = (clock_root_t)(clk_id - HAL_CLOCK_PLATFORM_SOURCE_NUM);

    g_halClkFreq[clk_id] = CLOCK_GetIpFreq(name);

    return g_halClkFreq[clk_id];
}

/*!
 * @brief return the rate of clk_id
 *
 * @param clk_id
 * The api is deprecated.It's replaced by HAL_ClockGetRate.
 */
uint64_t HAL_ClockGetFreq(hal_clk_id_e clk_id)
{
    if (clk_id >= HAL_CLOCK_PLATFORM_SOURCE_NUM)
    {
        g_halClkFreq[clk_id] = CLOCK_GetIpFreq((clock_root_t)(clk_id - HAL_CLOCK_PLATFORM_SOURCE_NUM));
    }
    else
    {
        g_halClkFreq[clk_id] = CLOCK_GetSourceFreq((uint32_t)clk_id);
    }

    return g_halClkFreq[clk_id];
}

int32_t HAL_ClockSetRate(hal_clk_t *hal_clk)
{
    status_t status = kStatus_Success;
    uint64_t rate = hal_clk->rate;
    uint32_t clk_round_option = (uint32_t)hal_clk->clk_round_opt;

    /* check rate */
    assert(hal_clk->rate != 0UL);

    if (hal_clk->clk_id >= HAL_CLOCK_PLATFORM_SOURCE_NUM)
    {
        if (!CCM_RootSetRate((uint32_t)(hal_clk->clk_id - HAL_CLOCK_PLATFORM_SOURCE_NUM), rate, HAL_CLOCK_RATE_FLAGS_ROUND(clk_round_option)))
        {
            status = kStatus_InvalidArgument;
        }
    }
    else
    {
        if (!CLOCK_SourceSetRate((uint32_t)hal_clk->clk_id, rate, HAL_CLOCK_RATE_FLAGS_ROUND(clk_round_option)))
        {
            status = kStatus_InvalidArgument;
        }
    }

    return (int32_t)status;
}

uint64_t HAL_ClockGetRate(hal_clk_id_e clk_id)
{
    if (clk_id >= HAL_CLOCK_PLATFORM_SOURCE_NUM)
    {
        g_halClkFreq[clk_id] = CCM_RootGetRate((uint32_t)(clk_id - HAL_CLOCK_PLATFORM_SOURCE_NUM));
    }
    else
    {
        g_halClkFreq[clk_id] = CLOCK_SourceGetRate((uint32_t)clk_id);
    }

    return g_halClkFreq[clk_id];
}

/*!
 * @brief ungate a clock
 *
 * @param hal_clk
 */
int32_t HAL_ClockEnable(hal_clk_t *hal_clk)
{
    status_t status = kStatus_Success;

    if (hal_clk->clk_id >= HAL_CLOCK_PLATFORM_SOURCE_NUM)
    {
        if (!CCM_RootSetEnable((uint32_t)(hal_clk->clk_id - HAL_CLOCK_PLATFORM_SOURCE_NUM), true))
        {
            status = kStatus_InvalidArgument;
        }
    }
    else
    {
        if (!CLOCK_SourceSetEnable((uint32_t)hal_clk->clk_id, true))
        {
            status = kStatus_InvalidArgument;
        }
    }

    return (int32_t)status;
}

/*!
 * @brief gate a clock
 *
 * @param hal_clk
 */
int32_t HAL_ClockDisable(hal_clk_t *hal_clk)
{
    status_t status = kStatus_Success;

    if (hal_clk->clk_id >= HAL_CLOCK_PLATFORM_SOURCE_NUM)
    {
        if (!CCM_RootSetEnable((uint32_t)(hal_clk->clk_id - HAL_CLOCK_PLATFORM_SOURCE_NUM), false))
        {
            status = kStatus_InvalidArgument;
        }
    }
    else
    {
        if (!CLOCK_SourceSetEnable((uint32_t)hal_clk->clk_id, false))
        {
            status = kStatus_InvalidArgument;
        }
    }

    return (int32_t)status;
}

/*!
 * @brief Set clock parent
 *
 * @param hal_clk
 */
int32_t HAL_ClockSetParent(hal_clk_t *hal_clk)
{
    status_t status = kStatus_Success;

    if (hal_clk->clk_id >= HAL_CLOCK_PLATFORM_SOURCE_NUM)
    {
        if (!CCM_RootSetParent((uint32_t)(hal_clk->clk_id - HAL_CLOCK_PLATFORM_SOURCE_NUM), (uint32_t)hal_clk->pclk_id))
        {
            status = kStatus_InvalidArgument;
        }
    }
    else
    {
        status = kStatus_InvalidArgument;
    }

    return (int32_t)status;
}

/*!
 * @brief Get clock parent
 *
 * @param hal_clk
 * @param pclk_id: parent clock id
 */
int32_t HAL_ClockGetParent(hal_clk_t *hal_clk, hal_clk_id_e *pclk_id)
{
    status_t status = kStatus_Success;
    uint32_t sourceIdx;

    if (hal_clk->clk_id >= HAL_CLOCK_PLATFORM_MAX_ID)
    {
        status = kStatus_OutOfRange;
    }

    if (hal_clk->clk_id < HAL_CLOCK_PLATFORM_SOURCE_NUM)
    {
        status = kStatus_InvalidArgument;
    }

    if (status == kStatus_Success)
    {
        if (!CCM_RootGetParent((uint32_t)(hal_clk->clk_id - HAL_CLOCK_PLATFORM_SOURCE_NUM), &sourceIdx))
        {
            status = kStatus_InvalidArgument;
        }
    }

    return (int32_t)status;
}
#else
#error "Pls define macro SM_CLOCK or CCM_CLOCK in hal_config.h.!!!"
#endif
