/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "fsl_pdm.h"
#include "fsl_sai.h"
#include "fsl_wm8524.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_PDM PDM
#define DEMO_PDM_CLK_FREQ (24576000U)
#define DEMO_PDM_FIFO_WATERMARK (7U)
#define DEMO_PDM_QUALITY_MODE kPDM_QualityModeHigh
#define DEMO_PDM_CIC_OVERSAMPLE_RATE (0U)
#define DEMO_PDM_ENABLE_CHANNEL_LEFT (0U)
#define DEMO_PDM_ENABLE_CHANNEL_RIGHT (1U)
#define DEMO_PDM_SAMPLE_CLOCK_RATE (1536000U * 4) /* 6.144MHZ */

#define DEMO_SAI (I2S3)
#define DEMO_SAI_CLK_FREQ (24576000U)
#define DEMO_SAI_FIFO_WATER_MARK (FSL_FEATURE_SAI_FIFO_COUNT / 2U)
#define DEMO_SAI_CLOCK_SOURCE (1U)

#define DEMO_CODEC_WM8524
#define DEMO_CODEC_BUS_PIN (NULL)
#define DEMO_CODEC_BUS_PIN_NUM (0)
#define DEMO_CODEC_MUTE_PIN (GPIO5)
#define DEMO_CODEC_MUTE_PIN_NUM (21)
#define BUFFER_SIZE (DEMO_PDM_FIFO_WATERMARK * 2U)
#define BUFFER_NUMBER (256U)
#define EXAMPLE_LED_GPIO GPIO1
#define EXAMPLE_LED_GPIO_PIN 15U
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void saiCallback(I2S_Type *base, sai_handle_t *handle, status_t status, void *userData);
/*******************************************************************************
 * Variables
 ******************************************************************************/
sai_handle_t txHandle = {0};
static volatile bool isSaiFinished = false;
SDK_ALIGN(static int16_t txBuff[BUFFER_SIZE * BUFFER_NUMBER], 4);
static volatile bool s_dataReadFinishedFlag = false;
static volatile uint32_t s_readIndex = 0U;
static volatile uint32_t s_writeIndex = 0U;

static const pdm_config_t pdmConfig = {
    .enableDoze = false,
    .fifoWatermark = DEMO_PDM_FIFO_WATERMARK,
    .qualityMode = DEMO_PDM_QUALITY_MODE,
    .cicOverSampleRate = DEMO_PDM_CIC_OVERSAMPLE_RATE,
};
static pdm_channel_config_t channelConfig = {
    .cutOffFreq = kPDM_DcRemoverCutOff152Hz, .gain = kPDM_DfOutputGain4,
};
/*******************************************************************************
 * Code
 ******************************************************************************/
static void saiCallback(I2S_Type *base, sai_handle_t *handle, status_t status, void *userData)
{
    isSaiFinished = true;
}

void PDM_ERROR_IRQHandler(void)
{
    uint32_t fifoStatus = 0U;
    if (PDM_GetStatus(DEMO_PDM) & PDM_STAT_LOWFREQF_MASK)
    {
        PDM_ClearStatus(DEMO_PDM, PDM_STAT_LOWFREQF_MASK);
    }

    fifoStatus = PDM_GetFifoStatus(DEMO_PDM);
    if (fifoStatus)
    {
        PDM_ClearFIFOStatus(DEMO_PDM, fifoStatus);
    }
}

void PDM_EVENT_IRQHandler(void)
{
    uint32_t status = PDM_GetStatus(DEMO_PDM);

    /* recieve data */
    if ((1U << DEMO_PDM_ENABLE_CHANNEL_LEFT) & status)
    {
        if ((s_readIndex >= s_writeIndex) || (s_readIndex <= (s_writeIndex - 1U)))
        {
            PDM_ReadNonBlocking(DEMO_PDM, 0, 2, &txBuff[s_readIndex * BUFFER_SIZE], DEMO_PDM_FIFO_WATERMARK);
            s_readIndex += 1U;
            if (s_readIndex == BUFFER_NUMBER)
            {
                s_readIndex = 0U;
            }
            s_dataReadFinishedFlag = true;
        }
    }

    PDM_ClearStatus(DEMO_PDM, status);
}

void Codec_Init(void)
{
    uint32_t delayCycle = 500000;

    wm8524_config_t codecConfig = {0};
    wm8524_handle_t codecHandle = {0};
    codecConfig.busPinNum = DEMO_CODEC_BUS_PIN_NUM;
    codecConfig.busPin = DEMO_CODEC_BUS_PIN;
    codecConfig.mutePin = DEMO_CODEC_MUTE_PIN;
    codecConfig.mutePinNum = DEMO_CODEC_MUTE_PIN_NUM;
    codecConfig.protocol = kWM8524_ProtocolI2S;
    WM8524_Init(&codecHandle, &codecConfig);

    while (delayCycle)
    {
        __ASM("nop");
        delayCycle--;
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    sai_config_t config;
    uint32_t mclkSourceClockHz = 0U;
    sai_transfer_format_t format;
    sai_transfer_t xfer;

    /* Board specific RDC settings */
    BOARD_RdcInit();

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    BOARD_InitMemory();

    CLOCK_SetRootMux(kCLOCK_RootPdm, kCLOCK_PdmRootmuxAudioPll1); /* Set PDM source from OSC 25MHZ */
    CLOCK_SetRootDivider(kCLOCK_RootPdm, 1U, 32U);                /* Set root clock to 25MHZ */

    CLOCK_SetRootMux(kCLOCK_RootSai3, kCLOCK_SaiRootmuxAudioPll1); /* Set SAI source to Audio PLL1 Div6 786432000HZ */
    CLOCK_SetRootDivider(kCLOCK_RootSai3, 1U, 32U);                /* Set root clock to 786432000HZ / 32 = 24576000HZ */

    PRINTF("PDM sai interrupt example started!\n\r");

    memset(txBuff, 0U, sizeof(txBuff));
    memset(&format, 0U, sizeof(sai_transfer_format_t));

    /*
     * config.masterSlave = kSAI_Master;
     * config.mclkSource = kSAI_MclkSourceSysclk;
     * config.protocol = kSAI_BusLeftJustified;
     * config.syncMode = kSAI_ModeAsync;
     * config.mclkOutputEnable = true;
     */
    SAI_TxGetDefaultConfig(&config);
    config.bclkSource = (sai_bclk_source_t)DEMO_SAI_CLOCK_SOURCE;
    config.protocol = kSAI_BusI2S;
    SAI_TxInit(DEMO_SAI, &config);

    /* Configure the audio format */
    format.bitWidth = kSAI_WordWidth16bits;
    format.channel = 0U;
    format.sampleRate_Hz = kSAI_SampleRate48KHz;
#if (defined FSL_FEATURE_SAI_HAS_MCLKDIV_REGISTER && FSL_FEATURE_SAI_HAS_MCLKDIV_REGISTER) || \
    (defined FSL_FEATURE_PCC_HAS_SAI_DIVIDER && FSL_FEATURE_PCC_HAS_SAI_DIVIDER)
    format.masterClockHz = OVER_SAMPLE_RATE * format.sampleRate_Hz;
#else
    format.masterClockHz = DEMO_SAI_CLK_FREQ;
#endif
    format.protocol = config.protocol;
    format.stereo = kSAI_Stereo;
    format.isFrameSyncCompact = true;
#if defined(FSL_FEATURE_SAI_FIFO_COUNT) && (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    format.watermark = FSL_FEATURE_SAI_FIFO_COUNT / 2U;
#endif

    Codec_Init();

    SAI_TransferTxCreateHandle(DEMO_SAI, &txHandle, saiCallback, NULL);
    mclkSourceClockHz = DEMO_SAI_CLK_FREQ;
    SAI_TransferTxSetFormat(DEMO_SAI, &txHandle, &format, mclkSourceClockHz, format.masterClockHz);

    /* Set up pdm */
    PDM_Init(DEMO_PDM, &pdmConfig);
    PDM_SetChannelConfig(DEMO_PDM, DEMO_PDM_ENABLE_CHANNEL_LEFT, &channelConfig);
    PDM_SetChannelConfig(DEMO_PDM, DEMO_PDM_ENABLE_CHANNEL_RIGHT, &channelConfig);
    PDM_SetSampleRate(DEMO_PDM, (1U << DEMO_PDM_ENABLE_CHANNEL_LEFT) | (1U << DEMO_PDM_ENABLE_CHANNEL_RIGHT),
                      pdmConfig.qualityMode, pdmConfig.cicOverSampleRate,
                      DEMO_PDM_CLK_FREQ / DEMO_PDM_SAMPLE_CLOCK_RATE);
    PDM_Reset(DEMO_PDM);
    PDM_EnableInterrupts(DEMO_PDM, kPDM_ErrorInterruptEnable | kPDM_FIFOInterruptEnable);
    EnableIRQ(PDM_EVENT_IRQn);
    PDM_Enable(DEMO_PDM, true);

    /* wait data read finish */
    while (1)
    {
        if (s_readIndex != s_writeIndex)
        {
            /*  xfer structure */
            xfer.data = (uint8_t *)(&txBuff[s_writeIndex * BUFFER_SIZE]);
            xfer.dataSize = BUFFER_SIZE * 2U; /* int16_t convert to byte length */
            if (SAI_TransferSendNonBlocking(DEMO_SAI, &txHandle, &xfer) != kStatus_SAI_QueueFull)
            {
                if ((s_writeIndex += 1U) >= BUFFER_NUMBER)
                {
                    s_writeIndex = 0U;
                }
            }
        }
    }
}
