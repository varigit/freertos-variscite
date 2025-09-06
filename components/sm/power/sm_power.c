/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "sm_power.h"
#include "scmi_power.h"

int32_t SM_POWER_SetState(sm_power_t *sm_power)
{
    uint32_t channel       = sm_power->channel;
    uint32_t domain_id      = sm_power->domain_id;
    uint32_t flag          = sm_power->flag;
    uint32_t power_st       = sm_power->power_st;
    return SCMI_PowerStateSet(channel, domain_id, flag, power_st);
}

int32_t SM_POWER_GetState(sm_power_t *sm_power, uint32_t *power_state)
{
    uint32_t channel       = sm_power->channel;
    uint32_t domain_id      = sm_power->domain_id;

    return SCMI_PowerStateGet(channel, domain_id, power_state);
}
