/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "sm_platform.h"
#include "sm_clock.h"
#include "scmi_clock.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*!
 * @brief Configure Root Clock
 *
 * @param sm_clk
 * The api is deprecated.It's replaced by SM_ClockGetParent, SM_ClockSetParent, SM_ClockGetRate, SM_ClockSetRate and SM_ClockEnable.
 */
void SM_CLOCK_SetRootClock(sm_clock_t *sm_clk)
{
    scmi_clock_rate_t rate = {0, 0};
    uint32_t channel       = sm_clk->channel;
    uint32_t clockId       = sm_clk->clk_id;
    uint32_t pclkId        = sm_clk->pclk_id;
    uint32_t div           = sm_clk->div;
    uint32_t attributes    = sm_clk->attributes;
    uint32_t oemConfigVal  = sm_clk->oem_config_val;
    uint32_t flags         = sm_clk->flags;
    uint32_t oldPclkId     = 0; /* parent clock id */
    uint64_t srcRate, rootRate;
    int32_t status = -1;

    if (div == 0U)
    {
        return;
    }
    status = SCMI_ClockParentGet(channel, clockId, &oldPclkId);
    if (status != 0)
    {
        return;
    }
    if (oldPclkId != pclkId)
    {
        status = SCMI_ClockParentSet(channel, clockId, pclkId);
        if (status != 0)
        {
            return;
        }
    }
    status = SCMI_ClockRateGet(channel, pclkId, &rate);
    if (status != 0)
    {
        return;
    }
    srcRate = rate.upper;
    srcRate = (srcRate << 32);
    srcRate |= rate.lower;

    rootRate = srcRate / div;

    rate.lower = (uint32_t)(rootRate & SM_CLOCK_RATE_MASK);
    rate.upper = (uint32_t)((rootRate >> 32) & SM_CLOCK_RATE_MASK);

    status = SCMI_ClockRateSet(channel, clockId, flags, rate);
    if (status != 0)
    {
        return;
    }
    status = SCMI_ClockConfigSet(channel, clockId, attributes, oemConfigVal);
    if (status != 0)
    {
        return;
    }
    return;
}

/*!
 * @brief Enable/Disable Root Clock
 *
 * @param sm_clk
 * The api is deprecated.It's replaced by SM_ClockConfigSet.
 */
void SM_CLOCK_EnableRootClock(sm_clock_t *sm_clk)
{
    uint32_t channel       = sm_clk->channel;
    uint32_t clockId       = sm_clk->clk_id;
    uint32_t attributes    = sm_clk->attributes;
    uint32_t oemConfigVal  = sm_clk->oem_config_val;
    int32_t status = -1;

    status = SCMI_ClockConfigSet(channel, clockId, attributes, oemConfigVal);
    if (status != 0)
    {
        return;
    }
    return;
}

uint64_t SM_CLOCK_GetIpFreq(sm_clock_t *sm_clk)
{
    scmi_clock_rate_t rate = {0, 0};
    uint32_t channel       = sm_clk->channel;
    uint32_t clockId       = sm_clk->clk_id;
    uint32_t pclkId        = sm_clk->pclk_id;
    int32_t status         = 0;

    status = SCMI_ClockParentGet(channel, clockId, &pclkId);
    if (status != 0)
    {
        return 0;
    }
    status = SCMI_ClockRateGet(channel, clockId, &rate);
    if (status != 0)
    {
        return 0;
    }
    return rate.lower | ((uint64_t)(rate.upper) << 32U);
}

/*!
 * @brief Configure PLL Clock
 *
 * @param sm_clk
 * The api is deprecated.It's replaced by SM_ClockSetRate.
 */
void SM_CLOCK_SetPllClock(sm_clock_t *sm_clk)
{
    scmi_clock_rate_t rate = {0, 0};
    uint32_t channel       = sm_clk->channel;
    uint32_t clockId       = sm_clk->clk_id;
    uint32_t flags         = sm_clk->flags;
    int32_t status = -1;

    rate.lower = sm_clk->ratel;
    rate.upper = sm_clk->rateu;

    status = SCMI_ClockRateSet(channel, clockId, flags, rate);
    if (status != 0)
    {
        return;
    }
    return;
}

/*!
 * @brief return the rate of clk
 *
 * @param sm_clk
 * The api is deprecated.It's replaced by SM_ClockGetRate.
 */
uint64_t SM_CLOCK_GetSourceFreq(sm_clock_t *sm_clk)
{
    scmi_clock_rate_t rate = {0, 0};
    uint32_t channel       = sm_clk->channel;
    uint32_t clockId       = sm_clk->clk_id;
    int32_t status = SCMI_ERR_SUCCESS;

    status = SCMI_ClockRateGet(channel, clockId, &rate);
    if (status != SCMI_ERR_SUCCESS)
    {
        return 0ULL;
    }
    return rate.lower | ((uint64_t)(rate.upper) << 32U);
}

/*!
 * @brief specify a new rate for sm_clk
 *
 * @param sm_clk
 */
int32_t SM_ClockSetRate(sm_clock_t *sm_clk)
{
    scmi_clock_rate_t rate = {0, 0};
    uint32_t channel       = sm_clk->channel;
    uint32_t clockId       = sm_clk->clk_id;
    uint32_t flags         = sm_clk->flags;

    rate.lower = sm_clk->ratel;
    rate.upper = sm_clk->rateu;

    return SCMI_ClockRateSet(channel, clockId, flags, rate);
}

/*!
 * @brief return the rate of sm_clk
 *
 * @param sm_clk
 */
uint64_t SM_ClockGetRate(sm_clock_t *sm_clk)
{
    scmi_clock_rate_t rate = {0, 0};
    uint32_t channel       = sm_clk->channel;
    uint32_t clockId       = sm_clk->clk_id;
    int32_t status = SCMI_ERR_SUCCESS;

    status = SCMI_ClockRateGet(channel, clockId, &rate);
    if (status != SCMI_ERR_SUCCESS)
    {
        return 0ULL;
    }
    return rate.lower | ((uint64_t)(rate.upper) << 32U);
}

/*!
 * @brief Set clock configuration
 *
 * @param sm_clk
 */
int32_t SM_ClockSetConfig(sm_clock_t *sm_clk)
{
    uint32_t channel       = sm_clk->channel;
    uint32_t clockId       = sm_clk->clk_id;
    uint32_t attributes    = sm_clk->attributes;
    uint32_t oemConfigVal  = sm_clk->oem_config_val;

    return SCMI_ClockConfigSet(channel, clockId, attributes, oemConfigVal);
}

/*!
 * @brief Set clock parent
 *
 * @param sm_clk
 */
int32_t SM_ClockSetParent(sm_clock_t *sm_clk)
{
    uint32_t channel       = sm_clk->channel;
    uint32_t clockId       = sm_clk->clk_id;
    uint32_t parentId       = sm_clk->pclk_id;

    return SCMI_ClockParentSet(channel, clockId, parentId);
}

/*!
 * @brief Get clock parent
 *
 * @param sm_clk
 */
int32_t SM_ClockGetParent(sm_clock_t *sm_clk, uint32_t *parentId)
{
    uint32_t channel       = sm_clk->channel;
    uint32_t clockId       = sm_clk->clk_id;

    return SCMI_ClockParentGet(channel, clockId, parentId);
}
