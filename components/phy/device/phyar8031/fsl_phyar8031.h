/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_PHYAR8031_H_
#define _FSL_PHYAR8031_H_

#include "fsl_phy.h"

/*!
 * @addtogroup phy_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief PHY driver version */
/*
    -2.0.1
      - Default configure RMII I/O to 1.8v in PHY_AR8031_Init
      - Enable RMII rx delay.
*/
#define FSL_PHY_DRIVER_VERSION (MAKE_VERSION(2, 0, 1)) /*!< Version 2.0.1. */

/*! @brief Defines the PHY registers. */
#define PHY_SPECIFIC_STATUS_REG    0x11U /*!< The PHY specific status register. */
#define PHY_COPPERFIBER_STATUS_REG 0x1BU /*!< The PHY copper/fiber status register. */
#define PHY_DEBUGPORT_ADDR_REG     0x1DU /*!< The PHY Debug port address register.*/
#define PHY_DEBUGPORT_DATA_REG     0x1EU /*!< The PHY Debug port data register.*/
#define PHY_CHIP_CFG_REG           0x1FU /*!< The PHY chip configure register. */

/*! @brief Defines the Debug register offset. */
#define PHY_DEBUG_HIBECTL_REG_OFFSET 0x0BU /*!< The PHY Debug register offset 0xB.*/
#define PHY_DEBUG_EXTLOOP_REG_OFFSET 0x11U /*!< The PHY Debug register offset 0x11.*/

#define PHY_CONTROL_ID1 0x004DU /*!< The PHY ID1 is 0x004D. */

/*!@brief Defines the mask flag of operation mode in control two register*/
#define PHY_CTL2_REMOTELOOP_MASK    0x0004U /*!< The PHY remote loopback mask. */
#define PHY_CTL2_REFCLK_SELECT_MASK 0x0080U /*!< The PHY RMII reference clock select. */
#define PHY_CTL1_10HALFDUPLEX_MASK  0x0001U /*!< The PHY 10M half duplex mask. */
#define PHY_CTL1_100HALFDUPLEX_MASK 0x0002U /*!< The PHY 100M half duplex mask. */
#define PHY_CTL1_10FULLDUPLEX_MASK  0x0005U /*!< The PHY 10M full duplex mask. */
#define PHY_CTL1_100FULLDUPLEX_MASK 0x0006U /*!< The PHY 100M full duplex mask. */

/*! @brief Defines the mask flag in specific status register. */
#define PHY_SSTATUS_LINKSTATUS_MASK 0x0400U /*!< The PHY link status mask. */
#define PHY_SSTATUS_LINKSPEED_MASK  0xC000U /*!< The PHY link speed mask. */
#define PHY_SSTATUS_LINKDUPLEX_MASK 0x2000U /*!< The PHY link duplex mask. */
#define PHY_SSTATUS_LINKSPEED_SHIFT 14      /*!< The link speed shift */

/*! @brief Defines the mask flag in PHY debug register- hibernate control register. */
#define PHY_DEBUG_HIBERNATECTL_REG 0x8000U /*!< The power hibernate control mask. */

/*! @brief Defines the PHY MMD access. */
#define PHY_MMD_DEVICEID3             3U     /*!< The PHY device id 3. */
#define PHY_MMD_REMOTEPHY_LOOP_OFFSET 0x805A /*!< The PHY MMD phy register */
#define PHY_MMD_SMARTEEE_CTL_OFFSET   0x805D /*!< The PHY MMD smartEEE register */
#define PHY_MMD_SMARTEEE_LPI_EN_SHIFT 8      /*!< The SmartEEE enable/disable bit shift */
/*! @brief Defines the chip configure register. */
#define PHY_MODE_CFG_MASK 0xFU /*!< The PHY mode configure mask. */

/*! @brief ENET MDIO operations structure. */
extern const phy_operations_t phyar8031_ops;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name PHY Driver
 * @{
 */

/*!
 * @brief Initializes PHY.
 *
 *  This function initialize PHY.
 *
 * @param handle       PHY device handle.
 * @param config       Pointer to structure of phy_config_t.
 * @retval kStatus_Success  PHY initializes success
 * @retval kStatus_PHY_SMIVisitTimeout  PHY SMI visit time out
 * @retval kStatus_PHY_AutoNegotiateFail  PHY auto negotiate fail
 */
status_t PHY_AR8031_Init(phy_handle_t *handle, const phy_config_t *config);

/*!
 * @brief PHY Write function. This function write data over the SMI to
 * the specified PHY register. This function is called by all PHY interfaces.
 *
 * @param handle  PHY device handle.
 * @param phyReg  The PHY register.
 * @param data    The data written to the PHY register.
 * @retval kStatus_Success     PHY write success
 * @retval kStatus_PHY_SMIVisitTimeout  PHY SMI visit time out
 */
status_t PHY_AR8031_Write(phy_handle_t *handle, uint32_t phyReg, uint32_t data);

/*!
 * @brief PHY Read function. This interface read data over the SMI from the
 * specified PHY register. This function is called by all PHY interfaces.
 *
 * @param handle   PHY device handle.
 * @param phyReg   The PHY register.
 * @param dataPtr  The address to store the data read from the PHY register.
 * @retval kStatus_Success  PHY read success
 * @retval kStatus_PHY_SMIVisitTimeout  PHY SMI visit time out
 */
status_t PHY_AR8031_Read(phy_handle_t *handle, uint32_t phyReg, uint32_t *dataPtr);

/*!
 * @brief Enables/disables PHY loopback.
 *
 * @param handle   PHY device handle.
 * @param mode     The loopback mode to be enabled, please see "phy_loop_t".
 * All loopback modes should not be set together, when one loopback mode is set
 * another should be disabled.
 * @param speed    PHY speed for loopback mode.
 * @param enable   True to enable, false to disable.
 * @retval kStatus_Success  PHY loopback success
 * @retval kStatus_PHY_SMIVisitTimeout  PHY SMI visit time out
 */
status_t PHY_AR8031_EnableLoopback(phy_handle_t *handle, phy_loop_t mode, phy_speed_t speed, bool enable);

/*!
 * @brief Gets the PHY link status.
 *
 * @param handle   PHY device handle.
 * @param status   The link up or down status of the PHY.
 *         - true the link is up.
 *         - false the link is down.
 * @retval kStatus_Success   PHY gets link status success
 * @retval kStatus_PHY_SMIVisitTimeout  PHY SMI visit time out
 */
status_t PHY_AR8031_GetLinkStatus(phy_handle_t *handle, bool *status);

/*!
 * @brief Gets the PHY link speed and duplex.
 *
 * @param handle   PHY device handle.
 * @param speed    The address of PHY link speed.
 * @param duplex   The link duplex of PHY.
 * @retval kStatus_Success   PHY gets link speed and duplex success
 * @retval kStatus_PHY_SMIVisitTimeout  PHY SMI visit time out
 */
status_t PHY_AR8031_GetLinkSpeedDuplex(phy_handle_t *handle, phy_speed_t *speed, phy_duplex_t *duplex);

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_PHYAR8031_H_ */
