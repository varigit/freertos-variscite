/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
* Copyright 2020-2021 NXP
*
* NXP Confidential. This software is owned or controlled by NXP and may only
* be used strictly in accordance with the applicable license terms found in
* file LICENSE.txt
*/

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_pdm.h"

#include "PL_platformTypes_CortexM.h"
#include "VIT.h"
#include "VIT_helper.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_PDM PDM
#define DEMO_PDM_CLK_FREQ \
    (24000000U) / (CLOCK_GetRootPreDivider(kCLOCK_RootPdm)) / (CLOCK_GetRootPostDivider(kCLOCK_RootPdm))
#define DEMO_PDM_FIFO_WATERMARK       (FSL_FEATURE_PDM_FIFO_DEPTH / 2U - 1U)
#define DEMO_PDM_QUALITY_MODE         kPDM_QualityModeHigh
#define DEMO_PDM_CIC_OVERSAMPLE_RATE  (0U)
#define DEMO_PDM_ENABLE_CHANNEL_LEFT  (0U)

#define DEMO_AUDIO_SAMPLE_RATE  (VIT_SAMPLE_RATE)
#define SAMPLE_COUNT (VIT_SAMPLES_PER_FRAME)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
SDK_ALIGN(static int16_t txBuff_a[SAMPLE_COUNT], 4);
SDK_ALIGN(static int16_t txBuff_b[SAMPLE_COUNT], 4);

static volatile int16_t *write_txBuff = txBuff_a;
static volatile int16_t *read_txBuff = txBuff_a;

static volatile bool s_lowFreqFlag          = false;
static volatile bool s_fifoErrorFlag        = false;
static volatile bool data_available = false;
static volatile uint32_t s_readIndex        = 0U;
static const pdm_config_t pdmConfig         = {
    .enableDoze        = false,
    .fifoWatermark     = DEMO_PDM_FIFO_WATERMARK,
    .qualityMode       = DEMO_PDM_QUALITY_MODE,
    .cicOverSampleRate = DEMO_PDM_CIC_OVERSAMPLE_RATE,
};
static pdm_channel_config_t channelConfig = {
    .cutOffFreq = kPDM_DcRemoverCutOff152Hz,
    .gain       = kPDM_DfOutputGain7,
};
/*******************************************************************************
 * Code
 ******************************************************************************/
static void pdm_error_irqHandler(void)
{
    uint32_t status = 0U;
    if (PDM_GetStatus(DEMO_PDM) & PDM_STAT_LOWFREQF_MASK)
    {
        PDM_ClearStatus(DEMO_PDM, PDM_STAT_LOWFREQF_MASK);
        s_lowFreqFlag = true;
    }

    status = PDM_GetFifoStatus(DEMO_PDM);
    if (status != 0U)
    {
        PDM_ClearFIFOStatus(DEMO_PDM, status);
        s_fifoErrorFlag = true;
    }
#if defined(FSL_FEATURE_PDM_HAS_RANGE_CTRL) && FSL_FEATURE_PDM_HAS_RANGE_CTRL
    status = PDM_GetRangeStatus(DEMO_PDM);
    if (status != 0U)
    {
        PDM_ClearRangeStatus(DEMO_PDM, status);
    }
#else
    status = PDM_GetOutputStatus(DEMO_PDM);
    if (status != 0U)
    {
        PDM_ClearOutputStatus(DEMO_PDM, status);
    }
#endif
}

#if !(defined FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ && FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ)
void PDM_ERROR_IRQHandler(void)
{
    pdm_error_irqHandler();
    __DSB();
}
#endif

void PDM_EVENT_IRQHandler(void)
{
    uint32_t i = 0U, status = PDM_GetStatus(DEMO_PDM);
    /* recieve data */
    if ((1U << DEMO_PDM_ENABLE_CHANNEL_LEFT) & status)
    {
        for (i = 0U; i < DEMO_PDM_FIFO_WATERMARK; i++)
        {
            if (s_readIndex < SAMPLE_COUNT)
            {
                write_txBuff[s_readIndex] =
                    PDM_ReadData(DEMO_PDM, DEMO_PDM_ENABLE_CHANNEL_LEFT);
                s_readIndex++;
            }
        }
    }

    /* handle PDM error status */
#if (defined FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ && FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ)
    pdm_error_irqHandler();
#endif

    PDM_ClearStatus(DEMO_PDM, status);
    if (s_readIndex >= SAMPLE_COUNT)
    {
        s_readIndex = 0;
        if (write_txBuff == txBuff_a) {
            write_txBuff = txBuff_b;
            read_txBuff = txBuff_a;
        } else {
            write_txBuff = txBuff_a;
            read_txBuff = txBuff_b;
        }
        data_available = true;
      //  PDM_Enable(DEMO_PDM, false);
    }
    __DSB();
}


/*!
 * @brief Main function
 */
int main(void)
{
    PL_MemoryTable_st       memorytable;
    VIT_DataIn_st           inputbuffers = { PL_NULL, PL_NULL, PL_NULL };
    VIT_Handle_t            handle = PL_NULL;
    VIT_ControlParams_st    controlparams;
    VIT_StatusParams_st     statusparams_buffer;
    VIT_DetectionStatus_en  detectionresults = VIT_NO_DETECTION;
    VIT_ReturnStatus_en     status;

    VIT_InstanceParams_st   instparams = {
        .SampleRate_Hz   = VIT_SAMPLE_RATE,
        .SamplesPerFrame = VIT_SAMPLES_PER_FRAME,
        .NumberOfChannel = _1CHAN,
        .DeviceId        = VIT_IMX8MINIM4
    };

    /* Init board hardware. */
    /* Board specific RDC settings */
    BOARD_RdcInit();
    BOARD_InitBootPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    BOARD_InitMemory();

    /* Set PDM source from OSC 25MHZ */
    CLOCK_SetRootMux(kCLOCK_RootPdm, kCLOCK_PdmRootmuxOsc24M);

    /* Set root clock to 25MHZ */
    CLOCK_SetRootDivider(kCLOCK_RootPdm, 1U, 1U);
    PRINTF("Vit test app!\r\n");

    // Get Lib Info
    VIT_LibInfo_st Lib_Info;
    status = VIT_GetLibInfo(&Lib_Info);
    CHECK(status, "VIT_GetLibInfo");

    // VIT get memory table
    status = VIT_GetMemoryTable(PL_NULL, &memorytable, &instparams);
    CHECK(status, "VIT_GetMemoryTable");

    // Set up memory
    VIT_SetupMemoryRegion(&memorytable);

    // Get handle
    status = VIT_GetInstanceHandle(&handle,
                                   &memorytable,
                                   &instparams);
    CHECK(status, "VIT_GetInstanceHandle");

    // Reset Instance
    status = VIT_ResetInstance(handle);
    CHECK(status, "VIT_ResetInstance");

    // Set VIT control parameters
    controlparams.OperatingMode = VIT_LPVAD_ENABLE;

    // Apply VIT Control Parameters
    status = VIT_SetControlParameters(handle, &controlparams);
    CHECK(status, "VIT_SetControlParameters");

    PL_INT32 frame_cnt = 0;

    PRINTF("PDM VIT example started!\n\r");

    memset(txBuff_a, 0U, sizeof(txBuff_a));
    memset(txBuff_b, 0U, sizeof(txBuff_b));

    /* Set up pdm */
    PDM_Init(DEMO_PDM, &pdmConfig);

    PDM_SetChannelConfig(DEMO_PDM,
            DEMO_PDM_ENABLE_CHANNEL_LEFT,
            &channelConfig);
    if (PDM_SetSampleRateConfig(DEMO_PDM,
                DEMO_PDM_CLK_FREQ,
                DEMO_AUDIO_SAMPLE_RATE) != kStatus_Success)
    {
        PRINTF("PDM configure sample rate failed.\r\n");
        return -1;
    }
    PDM_EnableInterrupts(DEMO_PDM,
            kPDM_ErrorInterruptEnable | kPDM_FIFOInterruptEnable);

    EnableIRQ(PDM_EVENT_IRQn);
#if !(defined FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ && FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ)
    EnableIRQ(PDM_ERROR_IRQn);
#endif
    PDM_Enable(DEMO_PDM, true);

    while (true)
    {
        while (!data_available) ;

        data_available = false;
        inputbuffers.pBuffer_Chan1 = (PL_INT16 *)read_txBuff;
        status = VIT_Process(handle, &inputbuffers, &detectionresults);
        CHECK(status, "VIT_Process");

        VIT_StatusParams_st* statusparam_buffer =
            (VIT_StatusParams_st*)&statusparams_buffer;

        VIT_GetStatusParameters(handle, statusparam_buffer,
                sizeof(statusparams_buffer));

        static PL_BOOL vad_detection_on = PL_FALSE;
        if (statusparam_buffer->LPVAD_EventDetected)
        {
            if (!vad_detection_on)
            {
                PRINTF("VAD : START OF THE DETECTION %d\r\n", frame_cnt+1);
            }
            vad_detection_on = PL_TRUE;
        }
        else
        {
            if (vad_detection_on)
            {
                PRINTF("VAD : END OF THE DETECTION %d\r\n",  frame_cnt+1);
            }
            vad_detection_on = PL_FALSE;
        }
        frame_cnt++;
    }

    PRINTF("\r\nPDM VIT example finished!\n\r ");
error:
    PDM_Deinit(DEMO_PDM);
    return 0;
}
