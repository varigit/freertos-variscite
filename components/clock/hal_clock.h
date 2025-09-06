/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef HAL_CLOCK_H_
#define HAL_CLOCK_H_

#include "hal_clock_platform.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

extern volatile uint64_t g_halClkFreq[HAL_CLOCK_PLATFORM_MAX_ID];

/* clock round options(Currently the enum is only used by System Manager Agent) */
typedef enum
{
    hal_clk_round_down = 0,
    hal_clk_round_up   = 1,
    hal_clk_round_auto = 2
} hal_clk_rnd_opt_e;

typedef struct
{
    hal_clk_id_e clk_id;             /* clock device id */
    hal_clk_id_e pclk_id;            /* parent clock device id */
    uint32_t div;                    /* clock divider(Don't need it yet) */
    bool enable_clk;                 /* true: enable clock; false: disable clock(Don't need it) */
    hal_clk_rnd_opt_e clk_round_opt; /* clock round options */
    uint32_t rateu;                  /* clock Rate upper(It is replaced by rate) */
    uint32_t ratel;                  /* clock Rate lower(It is replaced by rate) */
    uint64_t rate;                   /* rate */
} hal_clk_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /*__cplusplus */

void HAL_ClockSetRootClk(hal_clk_t *hal_clk);
/* The api is deprecated.It's replaced by HAL_ClockSetRate. */
void HAL_ClockSetPllClk(hal_clk_t *hal_clk);
/* The api is deprecated.It's replaced by HAL_ClockEnable. */
void HAL_ClockEnableRootClk(hal_clk_t *hal_clk);

/* The api is deprecated.It's replaced by HAL_ClockGetRate. */
uint64_t HAL_ClockGetIpFreq(hal_clk_id_e clk_id);

/* The api is deprecated.It's replaced by HAL_ClockGetRate. */
uint64_t HAL_ClockGetFreq(hal_clk_id_e clk_id);

/*!
 * @brief specify a new rate for hal_clk
 *
 * @param hal_clk
 */
int32_t HAL_ClockSetRate(hal_clk_t *hal_clk);

/*!
 * @brief return rate of hal_clk
 *
 * @param hal_clk
 */
uint64_t HAL_ClockGetRate(hal_clk_id_e clk_id);
/*!
 * @brief ungate a clock
 *
 * @param hal_clk
 */
int32_t HAL_ClockEnable(hal_clk_t *hal_clk);

/*!
 * @brief gate a clock
 *
 * @param hal_clk
 */
int32_t HAL_ClockDisable(hal_clk_t *hal_clk);

/*!
 * @brief Set clock parent
 *
 * @param hal_clk
 */
int32_t HAL_ClockSetParent(hal_clk_t *hal_clk);

/*!
 * @brief Get clock parent
 *
 * @param hal_clk
 * @param pclk_id: parent clock id
 */
int32_t HAL_ClockGetParent(hal_clk_t *hal_clk, hal_clk_id_e *pclk_id);

#if defined(__cplusplus)
}
#endif /*__cplusplus */

/*! @} */

#endif /* HAL_CLOCK_H_ */
