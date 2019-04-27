/*
 * Copyright 2018 NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_ak4497.h"
#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
static void Delay(void)
{
    uint32_t i;
    for (i = 0; i < 1000; i++)
    {
        __NOP();
    }
}

void AK4497_DefaultConfig(ak4497_config_t *config)
{
    config->ak4497Mode = kAK4497_PcmMode;
    config->dataChannelMode = kAK4497_NormalMode;
    /* PCM mode setting. */
    config->pcmConfig.pcmSampleFreqMode = kAK4497_AutoSettingMode;
    config->pcmConfig.pcmSdataFormat = kAK4497_32BitI2S;
    config->pcmConfig.pcmTdmMode = kAK4497_Normal;
    config->pcmConfig.pcmSdsSlot = kAK4497_L1R1;
    /* DSD mode setting. */
    config->dsdConfig.dsdMclk = kAK4497_mclk512fs;
    config->dsdConfig.dsdPath = kAK4497_Path1;
    config->dsdConfig.dsdPlaybackPath = kAK4497_NormalPath;
    config->dsdConfig.dsdDataMute = kAK4497_DsdMuteDisable;
    config->dsdConfig.dsdDclkPolarity = kAK4497_FallingEdge;
}

status_t AK4497_Init(codec_handle_t *handle, void *ak4497_config)
{
    ak4497_config_t *config = (ak4497_config_t *)ak4497_config;
    handle->codecPriv = config;
    handle->slaveAddress = AK4497_I2C_ADDR;

    AK4497_ModifyReg(handle, AK4497_CONTROL2, AK4497_CONTROL2_SMUTE_MASK,
                     1U << AK4497_CONTROL2_SMUTE_SHIFT); /* Soft ware mute */

    AK4497_ModifyReg(handle, AK4497_CONTROL1,
                     AK4497_CONTROL1_DIF0_MASK | AK4497_CONTROL1_DIF1_MASK | AK4497_CONTROL1_DIF2_MASK,
                     config->pcmConfig.pcmSdataFormat << AK4497_CONTROL1_DIF0_SHIFT);
    AK4497_ModifyReg(handle, AK4497_CONTROL3, AK4497_CONTROL3_SELLR_MASK, config->dataChannelMode
                                                                              << AK4497_CONTROL3_SELLR_SHIFT);
    if (config->ak4497Mode == kAK4497_PcmMode) /* PCM mode*/
    {
        if (config->pcmConfig.pcmSampleFreqMode != kAK4497_ManualSettingMode)
        {
            if (config->pcmConfig.pcmSampleFreqMode == kAK4497_AutoSettingMode)
            {
                AK4497_ModifyReg(handle, AK4497_CONTROL1, AK4497_CONTROL1_AFSD_MASK,
                                 0U << AK4497_CONTROL1_AFSD_SHIFT); /*Auto setting mode*/
                AK4497_ModifyReg(handle, AK4497_CONTROL1, AK4497_CONTROL1_ACKS_MASK, 1U << AK4497_CONTROL1_ACKS_SHIFT);
            }
            else
            {
                AK4497_ModifyReg(handle, AK4497_CONTROL1, AK4497_CONTROL1_AFSD_MASK,
                                 1U << AK4497_CONTROL1_AFSD_SHIFT); /* Auto Detect mode*/
                AK4497_ModifyReg(handle, AK4497_CONTROL1, AK4497_CONTROL1_ACKS_MASK, 0U << AK4497_CONTROL1_ACKS_SHIFT);
            }
        }
        AK4497_ModifyReg(handle, AK4497_CONTROL7, AK4497_CONTROL7_TDM0_MASK | AK4497_CONTROL7_TDM1_MASK,
                         config->pcmConfig.pcmTdmMode << AK4497_CONTROL7_TDM0_SHIFT);
        AK4497_ModifyReg(handle, AK4497_CONTROL8, AK4497_CONTROL8_SDS0_MASK, (config->pcmConfig.pcmSdsSlot & 0x1)
                                                                                 << AK4497_CONTROL8_SDS0_SHIFT);
        AK4497_ModifyReg(handle, AK4497_CONTROL7, AK4497_CONTROL7_SDS1_MASK,
                         ((config->pcmConfig.pcmSdsSlot & 0x2) >> 1U) << AK4497_CONTROL7_SDS1_SHIFT);
        AK4497_ModifyReg(handle, AK4497_CONTROL7, AK4497_CONTROL7_SDS2_MASK,
                         ((config->pcmConfig.pcmSdsSlot & 0x4) >> 2U) << AK4497_CONTROL7_SDS2_SHIFT);
    }

    else if (config->ak4497Mode == kAK4497_DsdMode) /*DSD mode*/
    {
        AK4497_ModifyReg(handle, AK4497_CONTROL1, AK4497_CONTROL1_EXDF_MASK, 0U << AK4497_CONTROL1_EXDF_SHIFT);
        AK4497_ModifyReg(handle, AK4497_CONTROL3, AK4497_CONTROL3_DP_MASK, 1U << AK4497_CONTROL3_DP_SHIFT);
        AK4497_ModifyReg(handle, AK4497_CONTROL3, AK4497_CONTROL3_DCKS_MASK, config->dsdConfig.dsdMclk
                                                                                 << AK4497_CONTROL3_DCKS_SHIFT);
        AK4497_ModifyReg(handle, AK4497_DSD2, AK4497_DSD2_DSDPATH_MASK, config->dsdConfig.dsdPath
                                                                            << AK4497_DSD2_DSDPATH_SHIFT);
        AK4497_ModifyReg(handle, AK4497_DSD1, AK4497_DSD1_DSDD_MASK, config->dsdConfig.dsdPlaybackPath
                                                                         << AK4497_DSD1_DSDD_SHIFT);
        AK4497_ModifyReg(handle, AK4497_DSD1, AK4497_DSD1_DDM_MASK, config->dsdConfig.dsdDataMute
                                                                        << AK4497_DSD1_DDM_SHIFT);
        AK4497_ModifyReg(handle, AK4497_CONTROL3, AK4497_CONTROL3_DCKB_MASK, config->dsdConfig.dsdDclkPolarity
                                                                                 << AK4497_CONTROL3_DCKB_SHIFT);
    }
    else /* EXDF mode*/
    {
        AK4497_ModifyReg(handle, AK4497_CONTROL1, AK4497_CONTROL1_EXDF_MASK, 1U << AK4497_CONTROL1_EXDF_SHIFT);
        AK4497_ModifyReg(handle, AK4497_CONTROL3, AK4497_CONTROL3_DP_MASK, 0U << AK4497_CONTROL3_DP_SHIFT);
    }

    AK4497_ModifyReg(handle, AK4497_CONTROL2, AK4497_CONTROL2_SMUTE_MASK,
                     0U << AK4497_CONTROL2_SMUTE_SHIFT); /* Normal Operation */

    AK4497_ModifyReg(handle, AK4497_CONTROL1, AK4497_CONTROL1_RSTN_MASK,
                     0U << AK4497_CONTROL1_RSTN_SHIFT); /* Rest the ak4497 */
    Delay(); /* Need to wait to ensure the ak4497 has updated the above registers. */
    AK4497_ModifyReg(handle, AK4497_CONTROL1, AK4497_CONTROL1_RSTN_MASK,
                     1U << AK4497_CONTROL1_RSTN_SHIFT); /* Normal Operation */
    Delay();

    return kStatus_Success;
}

status_t AK4497_SetEncoding(codec_handle_t *handle, uint8_t format)
{
    ak4497_config_t *config = handle->codecPriv;
    if (format > kAUDIO_Stereo32Bits)
    {
        /* Only set codec when playback mode changed. */
        if (config->ak4497Mode != kAK4497_DsdMode)
        {
            AK4497_ModifyReg(handle, AK4497_CONTROL1, AK4497_CONTROL1_EXDF_MASK, 0U << AK4497_CONTROL1_EXDF_SHIFT);
            AK4497_ModifyReg(handle, AK4497_CONTROL3, AK4497_CONTROL3_DP_MASK, 1U << AK4497_CONTROL3_DP_SHIFT);
            AK4497_ModifyReg(handle, AK4497_CONTROL3, AK4497_CONTROL3_DCKS_MASK, config->dsdConfig.dsdMclk
                                                                                     << AK4497_CONTROL3_DCKS_SHIFT);
            AK4497_ModifyReg(handle, AK4497_DSD2, AK4497_DSD2_DSDPATH_MASK, config->dsdConfig.dsdPath
                                                                                << AK4497_DSD2_DSDPATH_SHIFT);
            AK4497_ModifyReg(handle, AK4497_DSD1, AK4497_DSD1_DSDD_MASK, config->dsdConfig.dsdPlaybackPath
                                                                             << AK4497_DSD1_DSDD_SHIFT);
            AK4497_ModifyReg(handle, AK4497_DSD1, AK4497_DSD1_DDM_MASK, config->dsdConfig.dsdDataMute
                                                                            << AK4497_DSD1_DDM_SHIFT);
            AK4497_ModifyReg(handle, AK4497_CONTROL3, AK4497_CONTROL3_DCKB_MASK, config->dsdConfig.dsdDclkPolarity
                                                                                     << AK4497_CONTROL3_DCKB_SHIFT);
        }
        config->ak4497Mode = kAK4497_DsdMode;
    }
    else
    {
        /* Only set codec when playback mode changed. */
        if (config->ak4497Mode != kAK4497_PcmMode)
        {
            AK4497_ModifyReg(handle, AK4497_CONTROL7, AK4497_CONTROL7_TDM0_MASK | AK4497_CONTROL7_TDM1_MASK,
                             config->pcmConfig.pcmTdmMode << AK4497_CONTROL7_TDM0_SHIFT);
            AK4497_ModifyReg(handle, AK4497_CONTROL8, AK4497_CONTROL8_SDS0_MASK, (config->pcmConfig.pcmSdsSlot & 0x1)
                                                                                     << AK4497_CONTROL8_SDS0_SHIFT);
            AK4497_ModifyReg(handle, AK4497_CONTROL7, AK4497_CONTROL7_SDS1_MASK,
                             ((config->pcmConfig.pcmSdsSlot & 0x2) >> 1U) << AK4497_CONTROL7_SDS1_SHIFT);
            AK4497_ModifyReg(handle, AK4497_CONTROL7, AK4497_CONTROL7_SDS2_MASK,
                             ((config->pcmConfig.pcmSdsSlot & 0x4) >> 2U) << AK4497_CONTROL7_SDS2_SHIFT);
            AK4497_ModifyReg(handle, AK4497_CONTROL1, AK4497_CONTROL1_EXDF_MASK, 0U << AK4497_CONTROL1_EXDF_SHIFT);
            AK4497_ModifyReg(handle, AK4497_CONTROL3, AK4497_CONTROL3_DP_MASK, 0U << AK4497_CONTROL3_DP_SHIFT);
        }
        config->ak4497Mode = kAK4497_PcmMode;
    }
    return kStatus_Success;
}

status_t AK4497_ConfigDataFormat(codec_handle_t *handle, uint32_t mclk, uint32_t sampleRate, uint32_t bitWidth)
{
    ak4497_pcm_samplefreqselect_t samplefreq;
    ak4497_dsd_dclk_t dsdsel;
    ak4497_pcm_sdata_format_t sdataFormat;
    ak4497_config_t *config = handle->codecPriv;
    if (config->ak4497Mode == kAK4497_DsdMode)
    {
        switch (sampleRate * bitWidth)
        {
            case 2048000U:
            case 2822400U:
            case 3072000U:
                dsdsel = kAK4497_dclk64fs;
                break;
            case 4096000U:
            case 5644800U:
            case 6144000U:
                dsdsel = kAK4497_dclk128fs;
                break;
            case 8192000U:
            case 11289600U:
            case 12288000U:
                dsdsel = kAK4497_dclk256fs;
                break;
            case 16284000U:
            case 22579200U:
            case 24576000U:
                dsdsel = kAK4497_dclk512fs;
                break;
            default:
                return kStatus_Fail;
        }
        AK4497_ModifyReg(handle, AK4497_DSD1, AK4497_DSD1_DSDSEL0_MASK,
                         (dsdsel & 0x1) << AK4497_DSD1_DSDSEL0_SHIFT); /* Set DSDSEL0 */
        AK4497_ModifyReg(handle, AK4497_DSD2, AK4497_DSD2_DSDSEL1_MASK,
                         ((dsdsel & 0x2) >> 1U) << AK4497_DSD2_DSDSEL1_SHIFT); /* Set DSDSEL1 */
    }
    else /* PCM mode */
    {
        switch (sampleRate)
        {
            case 8000U:
            case 11025U:
            case 16000U:
            case 22050U:
            case 32000U:
            case 44100U:
            case 48000U:
                samplefreq = kAK4497_NormalSpeed;
                break;
            case 88200U:
            case 96000U:
                samplefreq = kAK4497_DoubleSpeed;
                break;
            case 176400U:
            case 192000U:
                samplefreq = kAK4497_QuadSpeed;
                break;
            case 352800U:
            case 384000U:
                samplefreq = kAK4497_OctSpeed;
                break;
            case 705600U:
            case 768000U:
                samplefreq = kAK4497_HexSpeed;
                break;
            default:
                return kStatus_Fail;
        }
        switch (bitWidth)
        {
            /* For PCM, only strero mode supported. */
            case 16U:
            case 24U:
                sdataFormat = kAK4497_16_24BitI2S;
                break;
            case 32U:
                sdataFormat = kAK4497_32BitI2S;
                break;
            default:
                return kStatus_Fail;
        }
        AK4497_ModifyReg(handle, AK4497_CONTROL2, AK4497_CONTROL2_DFS0_MASK | AK4497_CONTROL2_DFS1_MASK,
                         (samplefreq & 0x3) << AK4497_CONTROL2_DFS0_SHIFT); /* Set DFS[1:0] */
        AK4497_ModifyReg(handle, AK4497_CONTROL4, AK4497_CONTROL4_DFS2_MASK | AK4497_CONTROL4_DFS2_MASK,
                         ((samplefreq & 0x4) >> 2U) << AK4497_CONTROL4_DFS2_SHIFT); /* Set DFS[2] */
        AK4497_ModifyReg(handle, AK4497_CONTROL1,
                         AK4497_CONTROL1_DIF0_MASK | AK4497_CONTROL1_DIF1_MASK | AK4497_CONTROL1_DIF2_MASK,
                         sdataFormat << AK4497_CONTROL1_DIF0_SHIFT);
    }

    AK4497_ModifyReg(handle, AK4497_CONTROL1, AK4497_CONTROL1_RSTN_MASK,
                     0U << AK4497_CONTROL1_RSTN_SHIFT); /* Rest the ak4497 */

    Delay();

    AK4497_ModifyReg(handle, AK4497_CONTROL1, AK4497_CONTROL1_RSTN_MASK,
                     1U << AK4497_CONTROL1_RSTN_SHIFT); /* Normal Operation */
    Delay();

    return kStatus_Success;
}

status_t AK4497_SetVolume(codec_handle_t *handle, uint8_t value)
{
    status_t retval = kStatus_Success;
    /*
     * 255 levels, 0.5dB setp + mute (value = 0)
     */
    retval = AK4497_WriteReg(handle, AK4497_LCHATT, value);
    retval = AK4497_WriteReg(handle, AK4497_RCHATT, value);

    return retval;
}

status_t AK4497_GetVolume(codec_handle_t *handle, uint8_t *value)
{
    status_t retval = kStatus_Success;
    /*
     * 255 levels, 0.5dB setp + mute (value = 0);
     * R-channel volume regarded the same as the L-channel, here just read the L-channel value.
     */
    retval = AK4497_ReadReg(handle, AK4497_LCHATT, value);

    return retval;
}

status_t AK4497_Deinit(codec_handle_t *handle)
{
    AK4497_ModifyReg(handle, AK4497_CONTROL2, AK4497_CONTROL2_SMUTE_MASK,
                     1U << AK4497_CONTROL2_SMUTE_SHIFT); /* Soft ware mute */
    return kStatus_Success;
}
status_t AK4497_WriteReg(codec_handle_t *handle, uint8_t reg, uint8_t val)
{
    status_t retval = kStatus_Success;
    Delay(); /* Ensure the Codec I2C bus free before writing the slave. */
    retval = CODEC_I2C_WriteReg(handle->slaveAddress, kCODEC_RegAddr8Bit, reg, kCODEC_RegWidth8Bit, val,
                                handle->I2C_SendFunc);
    return retval;
}

status_t AK4497_ReadReg(codec_handle_t *handle, uint8_t reg, uint8_t *val)
{
    status_t retval = kStatus_Success;
    Delay(); /* Ensure the Codec I2C bus free before reading the slave. */
    retval = CODEC_I2C_ReadReg(handle->slaveAddress, kCODEC_RegAddr8Bit, reg, kCODEC_RegWidth8Bit, val,
                               handle->I2C_ReceiveFunc);
    return retval;
}

status_t AK4497_ModifyReg(codec_handle_t *handle, uint8_t reg, uint8_t mask, uint8_t val)
{
    status_t retval = kStatus_Success;
    uint8_t reg_val = 0;
    retval = AK4497_ReadReg(handle, reg, &reg_val);
    if (retval != kStatus_Success)
    {
        return kStatus_Fail;
    }
    reg_val &= (uint8_t)~mask;
    reg_val |= val;
    retval = AK4497_WriteReg(handle, reg, reg_val);
    if (retval != kStatus_Success)
    {
        return kStatus_Fail;
    }
    return kStatus_Success;
}
