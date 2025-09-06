/*
 * Copyright 2023-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "hal_config.h"
#include "hal_power.h"
#if SM_POWER
#include "sm_power.h"
#elif CCMSRCGPC_POWER
#include "fsl_power.h"
#endif

#if SM_POWER && CCMSRCGPC_POWER
#error "Pls not define them as 1 at the same time in hal_config.h!!!"
#endif

#if SM_POWER
int32_t HAL_PowerSetState(hal_pwr_s_t *pwr_st)
{
    sm_power_t sm_power = {0};

    sm_power.channel   = SM_PLATFORM_A2P;
    sm_power.domain_id = pwr_st->did;

    if (pwr_st->st == hal_power_state_on)
    {
        sm_power.power_st = SCMI_POWER_DOMAIN_STATE_ON;
    }
    else if (pwr_st->st == hal_power_state_off)
    {
        sm_power.power_st = SCMI_POWER_DOMAIN_STATE_OFF;
    }
    else
    {
        return SCMI_ERR_OUT_OF_RANGE;
    }

    return SM_POWER_SetState(&sm_power);
}

hal_pwr_st_e HAL_PowerGetState(hal_pwr_s_t *pwr_st)
{
    int32_t status;
    uint32_t power_state = SCMI_POWER_DOMAIN_STATE_OFF;
    sm_power_t sm_power = {0};

    sm_power.channel   = SM_PLATFORM_A2P;
    sm_power.domain_id = pwr_st->did;

    status = SM_POWER_GetState(&sm_power, &power_state);
    if (status != SCMI_ERR_SUCCESS)
    {
        return hal_power_state_err;
    }

    if (power_state == SCMI_POWER_DOMAIN_STATE_ON)
    {
        return hal_power_state_on;
    }
    else
    {
        return hal_power_state_off;
    }
}

#elif CCMSRCGPC_POWER
int32_t HAL_PowerSetState(hal_pwr_s_t *pwr_st)
{
    bool power_on = false;

    if (pwr_st->st == hal_power_state_on)
    {
        power_on = true;
    }
    else if (pwr_st->st == hal_power_state_off)
    {
        power_on = false;
    }
    else
    {
        return -1;
    }

    PWR_MixPowerSet(pwr_st->did, power_on);

    return 0;
}

hal_pwr_st_e HAL_PowerGetState(hal_pwr_s_t *pwr_st)
{
    hal_pwr_st_e state = hal_power_state_off;

    if (PWR_IsParentPowered(pwr_st->did) == true)
    {
        state = hal_power_state_on;
    }

    return state;
}
#else
#error "Pls define macro SM_POWER or CCMSRCGPC_POWER in hal_config.h.!!!"
#endif
