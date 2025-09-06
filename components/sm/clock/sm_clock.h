/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SM_CLOCK_H_
#define SM_CLOCK_H_

#include "fsl_common.h"
#include "scmi_clock.h"
#include "sm_platform.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SM_CLOCK_RATE_MASK 0xFFFFFFFFU

typedef struct
{
    uint32_t channel;    /* channel id: SCMI_A2P, SCMI_NOTIRY, SCMI_P2A, */
    uint32_t rateu;
    uint32_t ratel;
    uint32_t clk_id;     /* clock device id */
    uint32_t pclk_id;    /* parent clock device id */
    uint32_t div;        /* clock divider */
    uint32_t attributes; /* clock attributes */
    uint32_t oem_config_val;
    uint32_t flags;
} sm_clock_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /*__cplusplus */

/* The api is deprecated.It's replaced by SM_ClockGetParent, SM_ClockSetParent, SM_ClockGetRate, SM_ClockSetRate and SM_ClockEnable. */
void SM_CLOCK_SetRootClock(sm_clock_t *sm_clk);
/* The api is deprecated.It's replaced by SM_ClockSetRate. */
void SM_CLOCK_SetPllClock(sm_clock_t *sm_clk);
/* The api is deprecated.It's replaced by SM_ClockSetConfig. */
void SM_CLOCK_EnableRootClock(sm_clock_t *sm_clk);

/* The api is deprecated.It's replaced by SM_ClockGetRate. */
uint64_t SM_CLOCK_GetIpFreq(sm_clock_t *sm_clk);
/* The api is deprecated.It's replaced by SM_ClockGetRate. */
uint64_t SM_CLOCK_GetSourceFreq(sm_clock_t *sm_clk);

int32_t SM_ClockSetRate(sm_clock_t *sm_clk);
uint64_t SM_ClockGetRate(sm_clock_t *sm_clk);

/*!
 * @brief Set clock configuration
 *
 * @param sm_clk
 */
int32_t SM_ClockSetConfig(sm_clock_t *sm_clk);

/*!
 * @brief Set clock parent
 *
 * @param sm_clk
 */
int32_t SM_ClockSetParent(sm_clock_t *sm_clk);

/*!
 * @brief Get clock parent
 *
 * @param sm_clk
 */
int32_t SM_ClockGetParent(sm_clock_t *sm_clk, uint32_t *parentId);
#if defined(__cplusplus)
}
#endif /*__cplusplus */

/*! @} */

#endif /* SM_CLOCK_H_ */
