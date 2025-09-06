/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "fsl_device_registers.h"
#include "fsl_mu.h"
#include "sm_platform.h"
#if SCMI_LMM_POWER_CHANGE_PROCESSED
#include "app_srtm.h"
#endif

static MU_Type *const s_muBases[] = MU_BASE_PTRS;
static IRQn_Type const s_muIrqs[] = MU_IRQS;

#if SCMI_LM_REQUEST_M7_SUSPEND_ENABLE
extern bool scmiRequestM7IntoSuspend;
bool scmiRequestM7IntoSuspend = false; /* power app case should deal with flag. */
#endif

/*******************************************************************************
 * Definition
 ******************************************************************************/
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Initialize channel and MU interface for communication with SM.
 */
void SM_Platform_Init(void)
{
    MU_Type *base = s_muBases[SM_PLATFORM_MU_INST];
    IRQn_Type irq = s_muIrqs[SM_PLATFORM_MU_INST];

    /* Configure SMT */
    SMT_ChannelConfig(SM_PLATFORM_A2P, SM_PLATFORM_MU_INST, SM_PLATFORM_DBIR_A2P, SM_PLATFORM_SMA_ADDR);
    SMT_ChannelConfig(SM_PLATFORM_NOTIFY, SM_PLATFORM_MU_INST, SM_PLATFORM_DBIR_NOTIFY, SM_PLATFORM_SMA_ADDR);
    SMT_ChannelConfig(SM_PLATFORM_PRIORITY, SM_PLATFORM_MU_INST, SM_PLATFORM_DBIR_PRIORITY, SM_PLATFORM_SMA_ADDR);

    /* Configure MU */
    MU_Init(base);
    EnableIRQ(irq);
    NVIC_SetPriority(irq, SCMI_MU_IRQ_PRIORITY);
    MU_EnableInterrupts(base, (uint32_t)kMU_GenInt1InterruptEnable);
    MU_EnableInterrupts(base, (uint32_t)kMU_GenInt2InterruptEnable);

    /* Enable system notifications */
    SCMI_SystemPowerStateNotify(SM_PLATFORM_A2P, SCMI_SYS_NOTIFY_ENABLE(1U));

    /* Enable LMM notifications from AP(cortex-A55) */
    SCMI_LmmNotify(SM_PLATFORM_A2P, SM_PLATFORM_LMID_A55,
                   SCMI_LMM_NOTIFY_BOOT(1U) | SCMI_LMM_NOTIFY_SHUTDOWN(1U) | SCMI_LMM_NOTIFY_SUSPEND(1U) |
                       SCMI_LMM_NOTIFY_WAKE(1U));

#if defined(SCMI_BBSM_RTC_NOTIFICATIONS_ENABLE)
    /* Enable BBM notifications */
    SCMI_BbmRtcNotify(
        SM_PLATFORM_A2P, SM_PLATFORM_RTC_ID,
        SCMI_BBM_NOTIFY_RTC_UPDATED(1U) | SCMI_BBM_NOTIFY_RTC_ROLLOVER(1U) | SCMI_BBM_NOTIFY_RTC_ALARM(1U));
#endif

    SCMI_BbmButtonNotify(SM_PLATFORM_A2P, SCMI_BBM_NOTIFY_BUTTON_DETECT(1U));

    /* Enable FuSa notifications */
    if (SCMI_ERR_SUCCESS != SCMI_FusaFaultGroupNotify(SM_PLATFORM_A2P,
			    SM_PLATFORM_FAULT_ID_FIRST, SM_PLATFORM_FAULT_MASK,
                            SM_PLATFORM_NOTIFY_ENABLE, NULL, NULL))
    {
	PRINTF("Failed to enable/disable fault notifications\r\n");
    }
}

/*!
 * @brief Deinitialize MU interface.
 */
void SM_Platform_Deinit(void)
{
}

/*!
 * @brief SM Platform Handler.
 */
static void SM_Platform_Handler(void)
{
    MU_Type *base = s_muBases[SM_PLATFORM_MU_INST];
    uint32_t flags;

    /* Get interrupt status flags */
    flags = MU_GetStatusFlags(base);

    /* Clear interrupts */
    MU_ClearStatusFlags(base, flags);

    /* Notification pending? */
    if ((flags & (uint32_t)kMU_GenInt1Flag) != 0U)
    {
        uint32_t protocolId, messageId;

        /* Get pending info */
        if (SCMI_P2aPending(SM_PLATFORM_NOTIFY, &protocolId, &messageId) == SCMI_ERR_SUCCESS)
        {
            /* System event? */
            if (protocolId == SCMI_PROTOCOL_SYS)
            {
                uint32_t notifyFlags, systemState;

                if (SCMI_SystemPowerStateNotifier(SM_PLATFORM_NOTIFY, NULL, &notifyFlags, &systemState, NULL) ==
                    SCMI_ERR_SUCCESS)
                {
                    bool graceful = (SCMI_SYS_NOTIFIER_GRACEFUL(notifyFlags) != 0U);

                    PRINTF("\nSCMI system notification: graceful=%u, state=0x%08X\r\n", graceful, systemState);

                    if (graceful)
                    {
                        switch (systemState)
                        {
                            case SCMI_SYS_STATE_FULL_SHUTDOWN:
                            case SCMI_SYS_STATE_SHUTDOWN:
                                PRINTF("sm request M7 into shutdown\r\n");
                                break;
                            case SCMI_SYS_STATE_FULL_RESET:
                            case SCMI_SYS_STATE_COLD_RESET:
                            case SCMI_SYS_STATE_WARM_RESET:
                                PRINTF("sm request M7 into reset\r\n");
                                break;
                            case SCMI_SYS_STATE_FULL_SUSPEND:
                            case SCMI_SYS_STATE_SUSPEND:
#if SCMI_LM_REQUEST_M7_SUSPEND_ENABLE
                                /* SCMI send lm 1 suspend -> M7 sm platform interrupt -> app power rtos case to deal with this request. */
                                scmiRequestM7IntoSuspend = true;
#endif
                                PRINTF("sm request M7 into suspend\r\n");
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
            else if (protocolId == SCMI_PROTOCOL_LMM)
            {
                uint32_t notifyFlags, eventLm;

                if (SCMI_LmmEvent(SM_PLATFORM_NOTIFY, NULL, &eventLm, &notifyFlags) == SCMI_ERR_SUCCESS)
                {
#if SCMI_LMM_POWER_CHANGE_PROCESSED
                   /* Handle peer acore power changes notification to assure right communication. */
                   APP_SRTM_HandleLmmPowerChange(eventLm, notifyFlags);
#endif
                }
            }
            else if (protocolId == SCMI_PROTOCOL_BBM)
            {
                if (messageId == SCMI_MSG_BBM_RTC_EVENT)
                {
                    uint32_t notifyFlags;

                    if (SCMI_BbmRtcEvent(SM_PLATFORM_NOTIFY, &notifyFlags) == SCMI_ERR_SUCCESS)
                    {
                        PRINTF("\nSCMI BBM RTC notification: flags=0x%08X\r\n", flags);
                    }
                }
                else
                {
                    uint32_t notifyFlags;

                    if (SCMI_BbmButtonEvent(SM_PLATFORM_NOTIFY, &notifyFlags) == SCMI_ERR_SUCCESS)
                    {
                        PRINTF("\nSCMI BBM button notification: flags=0x%08X\r\n", flags);
                    }
                }
            }
            else if (protocolId == SCMI_PROTOCOL_SENSOR)
            {
                uint32_t sensorId, desc;

                if (SCMI_SensorTripPointEvent(SM_PLATFORM_NOTIFY, NULL, &sensorId, &desc) == SCMI_ERR_SUCCESS)
                {
                    PRINTF("\nSCMI sensor notification: sensor=%u, desc=0x%08X\r\n", sensorId, desc);
                }
            }
            else
            {
                PRINTF("\nSCMI unknown notification: 0x%X, 0x%X\r\n", protocolId, messageId);
            }
        }
    }

    /* Priority notification pending? */
    if ((flags & (uint32_t)kMU_GenInt2Flag) != 0U)
    {
        uint32_t protocolId, messageId;

        /* Get pending info */
        if (SCMI_P2aPending(SM_PLATFORM_PRIORITY, &protocolId, &messageId) == SCMI_ERR_SUCCESS)
        {
            if (messageId == SCMI_MSG_FUSA_FEENV_STATE_EVENT)
            {
                uint32_t state, mSel;

                if (SCMI_FusaFeenvStateEvent(SM_PLATFORM_PRIORITY, &state, &mSel) == SCMI_ERR_SUCCESS)
                {
                    PRINTF("\nSCMI FuSa F-EENV notification: state=%u, mSel=%u\r\n", state, mSel);
                }
            }
            else if (messageId == SCMI_MSG_FUSA_SEENV_STATE_REQ_EVENT)
            {
                uint32_t cookie;

                if (SCMI_FusaSeenvStateReqEvent(SM_PLATFORM_PRIORITY, &cookie) == SCMI_ERR_SUCCESS)
                {
                    PRINTF("\nSCMI FuSa S-EENV notification: cookie=%u\r\n", cookie);
                }
            }
            else
            {
                uint32_t faultId, flag;

                if (SCMI_FusaFaultEvent(SM_PLATFORM_PRIORITY, &faultId, &flag) == SCMI_ERR_SUCCESS)
                {
                    PRINTF("\nSCMI FuSa fault notification: faultId=%u, flags=%u\r\n", faultId, flag);

                    if (SCMI_FUSA_FAULT_FLAG_STATE(flag) != 0U)
                    {
                        SCMI_FusaFaultSet(SM_PLATFORM_A2P, faultId, SCMI_FUSA_FAULT_SET_STATE(0U));
                    }
                }
            }
        }
    }
}

/*!
 * @brief MU5_A IRQ Handler
 */
void MU5_A_IRQHandler(void)
{
    SM_Platform_Handler();
}
