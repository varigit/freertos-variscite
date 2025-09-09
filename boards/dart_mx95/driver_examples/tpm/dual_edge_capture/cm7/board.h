/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "hal_clock.h"
#include "clock_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief The board name */
#define BOARD_NAME "IMX95LPD5-EVK"
/* for System Manager */

/* sync with 'devices/MIMX95/drivers/fsl_clock.h' of imx-sm-sandbox */
#define CLOCK_NUM_SRC 41UL

/*! Number of device pins */
#define DEV_SM_NUM_PIN    108U
/*! Number of device daisy */
#define DEV_SM_NUM_DAISY  68U
#define SCMI_IOMUXC_BASE AON__IOMUXC0__IOMUXC_BASE
#define SCMI_IOMUXC_CFGREG_OFF (SCMI_IOMUXC_BASE + (DEV_SM_NUM_PIN * 4U))
#define SCMI_IOMUXC_DAISYREG_OFF (SCMI_IOMUXC_BASE + (DEV_SM_NUM_PIN * 8U))

#define SCMI_LMID_M7 1
#define SCMI_LMID_A55 2
#define SCMI_MU_SEL     8

#define SCMI_A2P    0
#define SCMI_NOTIFY 1
#define SCMI_P2A    2
/* Doorbell interrupt request number */
#define SCMI_DBIR_A2P    0    /* 0: A2P channel */
#define SCMI_DBIR_NOTIFY 1    /* 1: P2A notification channel */
#define SCMI_DBIR_P2A    3    /* 2: FuSa reverse channel 3: P2A channel */
#define SCMI_SMA_ADDR    0    /* share memory address. 0: Use of internal MU SRAM */

#if (SCMI_DBIR_NOTIFY == 1)
#define MU_NOTIFY_GENINT_EN(base)  \
    MU_EnableInterrupts(base, kMU_GenInt1InterruptEnable)
#define MU_NOTIFY_GENINT_FLAG kMU_GenInt1Flag
#endif

#if (SCMI_DBIR_P2A == 3)
#define MU_P2A_GENINT_EN(base)  \
    MU_EnableInterrupts(base, kMU_GenInt3InterruptEnable)
#define MU_P2A_GENINT_FLAG kMU_GenInt1Flag
#endif

/*
 * The UART instance to be used for debugging.
 * On iMX95 Emulator
 * +---------------------------------+
 * |   CM33    |  CM7        | CA55  |
 * -----------------------------------
 * |   1      |   2          | 3     |
 * +---------------------------------+
 *
 * On iMX95 LPDDR5 19x19 EVK
 * +---------------------------------+
 * |   CM33    |  CM7        | CA55  |
 * -----------------------------------
 * |   2      |   3          | 1     |
 * +---------------------------------+
 */

/* boad type: imx95 emulator or imx95 lpddr5 19x19 evk */
#define BOARD_DEBUG_UART_INSTANCE 3

#define BOARD_DEBUG_UART_INSTANCE_FOR_CM7_WITH_SM 3U
#define BOARD_DEBUG_UART_CLOCK_ROOT_FOR_CM7_WITH_SM hal_clock_lpuart3
#define BOARD_DEBUG_UART_CLK_FREQ_FOR_CM7_WITH_SM   HAL_ClockGetRate(BOARD_DEBUG_UART_CLOCK_ROOT_FOR_CM7_WITH_SM)

#define BOARD_DEBUG_UART_INSTANCE_FOR_CM7_WITHOUT_SM 3U
#define BOARD_DEBUG_UART_CLOCK_ROOT_FOR_CM7_WITHOUT_SM hal_clock_lpuart3
#define BOARD_DEBUG_UART_CLK_FREQ_FOR_CM7_WITHOUT_SM   HAL_ClockGetRate(BOARD_DEBUG_UART_CLOCK_ROOT_FOR_CM7_WITHOUT_SM)

#define BOARD_DEBUG_UART_INSTANCE_FOR_CM33_WITHOUT_SM 2U
#define BOARD_DEBUG_UART_CLOCK_ROOT_FOR_CM33_WITHOUT_SM hal_clock_lpuart2
#define BOARD_DEBUG_UART_CLK_FREQ_FOR_CM33_WITHOUT_SM   HAL_ClockGetRate(BOARD_DEBUG_UART_CLOCK_ROOT_FOR_CM33_WITHOUT_SM)

#define BOARD_DEBUG_UART_CLOCK_ROOT hal_clock_lpuart3

#define BOARD_DEBUG_UART_CLK_FREQ HAL_ClockGetRate(BOARD_DEBUG_UART_CLOCK_ROOT)
#define BOARD_DEBUG_UART_BAUDRATE   115200U
#define BOARD_DEBUG_UART_TYPE       kSerialPort_Uart

#define VDEV0_VRING_BASE (0x88000000U)
#define VDEV1_VRING_BASE (0x88010000U)

#define LED_INIT()
#define LED_TOGGLE()


















#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/
void BOARD_InitDebugConsoleForCM7WithSM(void);
void BOARD_InitDebugConsoleForCM7WithoutSM(void);
void BOARD_InitDebugConsole(void);
#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
void BOARD_LPI2C_Init(LPI2C_Type *base, uint32_t clkSrc_Hz);
status_t BOARD_LPI2C_Send(LPI2C_Type *base,
                          uint8_t deviceAddress,
                          uint32_t subAddress,
                          uint8_t subaddressSize,
                          uint8_t *txBuff,
                          uint8_t txBuffSize,
                          uint32_t flags);
status_t BOARD_LPI2C_Receive(LPI2C_Type *base,
                             uint8_t deviceAddress,
                             uint32_t subAddress,
                             uint8_t subaddressSize,
                             uint8_t *rxBuff,
                             uint8_t rxBuffSize,
                             uint32_t flags);
status_t BOARD_Display_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_Display_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);




#endif

/* Mcore suspend setting */
#define OSCPLL_LPM_START 3U
#define OSCPLL_LPM_END   12U
/* SysTick Control and Status Register(SYST_CSR) of cortex-M33 */
#define SYSTICK_CTRL_REG (*((volatile uint32_t *)0xe000e010))
/*
 * SYST_CSR[0] ENABLE(Enable counter):
 * 0: Counter Disabled
 * 1: Counter Enabled
 * SYST_CSR[1] TICKINT(Enables SysTick exception request):
 * 0: Counting down to zero does not assert the SysTick exception request.
 * 1: Counting down to zero asserts the SysTick exception request.
 * More info from
 * https://developer.arm.com/documentation/100235/0004/the-cortex-m33-peripherals/system-timer--systick/systick-control-and-status-register
 */
#define SYSTICK_CLOSE 0U
void BOARD_McoreSUSPEND(void);

void BOARD_ConfigMPU(void);
#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* _BOARD_H_ */
