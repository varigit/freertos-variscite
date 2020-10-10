/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_phyar8031.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Defines the timeout macro. */
#define PHY_TIMEOUT_COUNT 100000U

/*! @brief Defines the delay macro. */
#define PHY_DELAY_COUNT 50000000U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
const phy_operations_t phyar8031_ops = {.phyInit            = PHY_AR8031_Init,
                                        .phyWrite           = PHY_AR8031_Write,
                                        .phyRead            = PHY_AR8031_Read,
                                        .getLinkStatus      = PHY_AR8031_GetLinkStatus,
                                        .getLinkSpeedDuplex = PHY_AR8031_GetLinkSpeedDuplex,
                                        .enableLoopback     = PHY_AR8031_EnableLoopback};

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t PHY_AR8031_Init(phy_handle_t *handle, const phy_config_t *config)
{
    uint32_t bssReg  = 0;
    uint32_t counter = PHY_TIMEOUT_COUNT;
    uint32_t idReg   = 0;
    status_t result  = kStatus_Success;
    uint32_t timeDelay;

    /* Init MDIO interface. */
    MDIO_Init(handle->mdioHandle);

    /* assign phy address. */
    handle->phyAddr = config->phyAddr;

    /* Initialization after PHY stars to work. */
    while ((idReg != PHY_CONTROL_ID1) && (counter != 0))
    {
        MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_ID1_REG, &idReg);
        counter--;
    }

    if (!counter)
    {
        return kStatus_Fail;
    }

    /* Configure RMII voltage 1.8V */
    result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_ADDR_REG, 0x1F);
    if (result != kStatus_Success)
    {
        return result;
    }
    result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_DATA_REG, 0x8);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Reset PHY. */
    counter = PHY_TIMEOUT_COUNT;
    result  = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, PHY_BCTL_RESET_MASK);
    if (result == kStatus_Success)
    {
        /* Close smartEEE. */
        result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_MMD_ACCESS_CONTROL_REG, PHY_MMD_DEVICEID3);
        if (result == kStatus_Success)
        {
            result =
                MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_MMD_ACCESS_DATA_REG, PHY_MMD_SMARTEEE_CTL_OFFSET);
            if (result == kStatus_Success)
            {
                result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_MMD_ACCESS_CONTROL_REG,
                                    PHY_MMD_DEVICEID3 | 0x4000);
                if (result == kStatus_Success)
                {
                    MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_MMD_ACCESS_DATA_REG, &bssReg);
                    MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_MMD_ACCESS_DATA_REG,
                               (bssReg & ~((uint32_t)1 << PHY_MMD_SMARTEEE_LPI_EN_SHIFT)));
                }
            }
        }
        /* Enable Tx clock delay */
        result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_ADDR_REG, 0x5);
        if (result != kStatus_Success)
        {
            return result;
        }
        result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_DATA_REG, &bssReg);
        if (result != kStatus_Success)
        {
            return result;
        }
        result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_DATA_REG, (bssReg | 0x0100));
        if (result != kStatus_Success)
        {
            return result;
        }

        /* Enable Rx clock delay */
        result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_ADDR_REG, 0x0);
        if (result != kStatus_Success)
        {
            return result;
        }
        result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_DATA_REG, &bssReg);
        if (result != kStatus_Success)
        {
            return result;
        }
        result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_DATA_REG, (bssReg | 0x8000));
        if (result != kStatus_Success)
        {
            return result;
        }

        /* Set the negotiation. */
        result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_AUTONEG_ADVERTISE_REG,
                            (PHY_100BASETX_FULLDUPLEX_MASK | PHY_100BASETX_HALFDUPLEX_MASK |
                             PHY_10BASETX_FULLDUPLEX_MASK | PHY_10BASETX_HALFDUPLEX_MASK | 0x1U));
        if (result == kStatus_Success)
        {
            result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_1000BASET_CONTROL_REG,
                                PHY_1000BASET_FULLDUPLEX_MASK | PHY_1000BASET_HALFDUPLEX_MASK);
            if (result == kStatus_Success)
            {
                result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, &bssReg);

                result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG,
                                    (bssReg | PHY_BCTL_AUTONEG_MASK | PHY_BCTL_RESTART_AUTONEG_MASK));
                if (result == kStatus_Success)
                {
                    /* Check auto negotiation complete. */
                    while (counter--)
                    {
                        result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_BASICSTATUS_REG, &bssReg);
                        if (result == kStatus_Success)
                        {
                            if ((bssReg & PHY_BSTATUS_AUTONEGCOMP_MASK) != 0)
                            {
                                /* Wait a moment for Phy status stable due to Auto complete takes about 3s ~ 4s. */
                                for (timeDelay = 0; timeDelay < PHY_DELAY_COUNT; timeDelay++)
                                {
                                    __ASM("nop");
                                }
                                break;
                            }
                        }

                        if (!counter)
                        {
                            return kStatus_PHY_AutoNegotiateFail;
                        }
                    }
                }
            }
        }
    }

    return result;
}

status_t PHY_AR8031_Write(phy_handle_t *handle, uint32_t phyReg, uint32_t data)
{
    return MDIO_Write(handle->mdioHandle, handle->phyAddr, phyReg, data);
}

status_t PHY_AR8031_Read(phy_handle_t *handle, uint32_t phyReg, uint32_t *dataPtr)
{
    return MDIO_Read(handle->mdioHandle, handle->phyAddr, phyReg, dataPtr);
}

status_t PHY_AR8031_EnableLoopback(phy_handle_t *handle, phy_loop_t mode, phy_speed_t speed, bool enable)
{
    status_t result;
    uint32_t data = 0;

    /* Set the loop mode. */
    if (enable)
    {
        if (mode == kPHY_LocalLoop)
        {
            if (speed == kPHY_Speed1000M)
            {
                data = PHY_BCTL_SPEED1_MASK | PHY_BCTL_DUPLEX_MASK | PHY_BCTL_LOOP_MASK;
            }
            else if (speed == kPHY_Speed100M)
            {
                data = PHY_BCTL_SPEED_100M_MASK | PHY_BCTL_DUPLEX_MASK | PHY_BCTL_LOOP_MASK;
            }
            else
            {
                data = PHY_BCTL_DUPLEX_MASK | PHY_BCTL_LOOP_MASK;
            }
            return MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, data);
        }
        else if (mode == kPHY_RemoteLoop)
        {
            /* First read the current status in control register. */
            result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_MMD_ACCESS_CONTROL_REG, PHY_MMD_DEVICEID3);
            if (result == kStatus_Success)
            {
                result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_MMD_ACCESS_DATA_REG,
                                    PHY_MMD_REMOTEPHY_LOOP_OFFSET);
                if (result == kStatus_Success)
                {
                    result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_MMD_ACCESS_CONTROL_REG,
                                        PHY_MMD_DEVICEID3 | 0x4000);
                    if (result == kStatus_Success)
                    {
                        return MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_MMD_ACCESS_DATA_REG, 1U);
                    }
                }
            }
        }
        else
        {
            /* First read the current status in control register. */
            result =
                MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_ADDR_REG, PHY_DEBUG_HIBECTL_REG_OFFSET);
            if (result == kStatus_Success)
            {
                result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_DATA_REG, 0);
                if (result == kStatus_Success)
                {
                    result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_ADDR_REG,
                                        PHY_DEBUG_EXTLOOP_REG_OFFSET);
                    if (result == kStatus_Success)
                    {
                        result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_DATA_REG, 1);
                        if (result == kStatus_Success)
                        {
                            if (speed == kPHY_Speed1000M)
                            {
                                data = PHY_BCTL_SPEED1_MASK | PHY_BCTL_DUPLEX_MASK | PHY_BCTL_RESET_MASK;
                            }
                            else if (speed == kPHY_Speed100M)
                            {
                                data = PHY_BCTL_SPEED_100M_MASK | PHY_BCTL_DUPLEX_MASK | PHY_BCTL_RESET_MASK;
                            }
                            else
                            {
                                data = PHY_BCTL_DUPLEX_MASK | PHY_BCTL_RESET_MASK;
                            }
                            return MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, data);
                        }
                    }
                }
            }
        }
    }
    else
    {
        /* Disable the loop mode. */
        if (mode == kPHY_LocalLoop)
        {
            /* First read the current status in control register. */
            result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, &data);
            if (result == kStatus_Success)
            {
                data &= ~PHY_BCTL_LOOP_MASK;
                return MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG,
                                  (data | PHY_BCTL_RESTART_AUTONEG_MASK));
            }
        }
        else if (mode == kPHY_RemoteLoop)
        {
            /* First read the current status in control register. */
            result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_MMD_ACCESS_CONTROL_REG, PHY_MMD_DEVICEID3);
            if (result == kStatus_Success)
            {
                result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_MMD_ACCESS_DATA_REG,
                                    PHY_MMD_REMOTEPHY_LOOP_OFFSET);
                if (result == kStatus_Success)
                {
                    result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_MMD_ACCESS_CONTROL_REG,
                                        PHY_MMD_DEVICEID3 | 0x4000);
                    if (result == kStatus_Success)
                    {
                        return MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_MMD_ACCESS_DATA_REG, 0x0U);
                    }
                }
            }
        }
        else
        {
            /* First read the current status in control register. */
            result =
                MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_ADDR_REG, PHY_DEBUG_HIBECTL_REG_OFFSET);
            if (result == kStatus_Success)
            {
                result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_DATA_REG, 0);
                if (result == kStatus_Success)
                {
                    result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_ADDR_REG,
                                        PHY_DEBUG_EXTLOOP_REG_OFFSET);
                    if (result == kStatus_Success)
                    {
                        result = MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_DEBUGPORT_DATA_REG, 0);
                        if (result == kStatus_Success)
                        {
                            data = PHY_BCTL_AUTONEG_MASK | PHY_BCTL_RESET_MASK;
                            return MDIO_Write(handle->mdioHandle, handle->phyAddr, PHY_BASICCONTROL_REG, data);
                        }
                    }
                }
            }
        }
    }
    return result;
}

status_t PHY_AR8031_GetLinkStatus(phy_handle_t *handle, bool *status)
{
    assert(status);

    status_t result = kStatus_Success;
    uint32_t data;

    /* Read the basic status register. */
    result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_SPECIFIC_STATUS_REG, &data);
    if (result == kStatus_Success)
    {
        if (!(PHY_SSTATUS_LINKSTATUS_MASK & data))
        {
            /* link down. */
            *status = false;
        }
        else
        {
            /* link up. */
            *status = true;
        }
    }
    return result;
}

status_t PHY_AR8031_GetLinkSpeedDuplex(phy_handle_t *handle, phy_speed_t *speed, phy_duplex_t *duplex)
{
    assert(duplex);

    status_t result = kStatus_Success;
    uint32_t statReg;

    /* Read the control two register. */
    result = MDIO_Read(handle->mdioHandle, handle->phyAddr, PHY_SPECIFIC_STATUS_REG, &statReg);
    if (result == kStatus_Success)
    {
        if ((statReg & PHY_SSTATUS_LINKDUPLEX_MASK))
        {
            /* Full duplex. */
            *duplex = kPHY_FullDuplex;
        }
        else
        {
            /* Half duplex. */
            *duplex = kPHY_HalfDuplex;
        }

        switch ((statReg & PHY_SSTATUS_LINKSPEED_MASK) >> PHY_SSTATUS_LINKSPEED_SHIFT)
        {
            case kPHY_Speed10M:
                *speed = kPHY_Speed10M;
                break;
            case kPHY_Speed100M:
                *speed = kPHY_Speed100M;
                break;
            case kPHY_Speed1000M:
                *speed = kPHY_Speed1000M;
                break;
            default:
                *speed = kPHY_Speed10M;
                break;
        }
    }

    return result;
}
