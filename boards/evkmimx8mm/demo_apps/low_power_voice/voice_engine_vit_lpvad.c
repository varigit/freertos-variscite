/*
 * Copyright 2021-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"

#include "PL_platformTypes_CortexM.h"
#include "VIT.h"
#include "VIT_helper.h"

#include "fsl_debug_console.h"
#include "srtm_pdm_sdma_adapter.h"
#include "task.h"
#include "voice_engine_common.h"

#define RX_BUFFER_LEN (50 * 1024) /* 200ms * 8channels * 16KHz * 16bits*/
int8_t g_rx_buffer[RX_BUFFER_LEN];

#define SAMPLES_PER_FRAME_IN (160)

srtm_pdm_sdma_local_buf_t g_local_rx_buf = {
    .buf              = (uint8_t *)&g_rx_buffer,
    .bufSize          = RX_BUFFER_LEN,
    .periods          = 0,                    // Ignored because samples per period below.
    .samplesPerPeriod = SAMPLES_PER_FRAME_IN, // for VIT
};

static VIT_Handle_t handle = PL_NULL;
static uint16_t input_buf[SAMPLES_PER_FRAME_IN]; // VIT works on 16bits

extern uint32_t next_buf_size;
extern srtm_audio_format_type_t audio_format;
extern srtm_sai_adapter_t pdmAdapter;

/*
 * VIT specific functions.
 */

void voice_engine_algo_init(void)
{
    VIT_LibInfo_st Lib_Info;
    PL_MemoryTable_st memorytable;
    VIT_ControlParams_st controlparams;
    VIT_ReturnStatus_en status;
    VIT_InstanceParams_st instparams = {.SampleRate_Hz   = VIT_SAMPLE_RATE,
                                        .SamplesPerFrame = VIT_SAMPLES_PER_FRAME,
                                        .NumberOfChannel = _1CHAN,
                                        .DeviceId        = VIT_DEVICE_ID};
    // Get Lib Info
    status = VIT_GetLibInfo(&Lib_Info);
    CHECK(status, "VIT_GetLibInfo");

    PRINTF("VIT release: 0x%x\r\n", Lib_Info.VIT_LIB_Release);

    // VIT get memory table
    status = VIT_GetMemoryTable(PL_NULL, &memorytable, &instparams);
    CHECK(status, "VIT_GetMemoryTable");

    // Set up memory
    VIT_SetupMemoryRegion(&memorytable);

    // Get handle
    status = VIT_GetInstanceHandle(&handle, &memorytable, &instparams);
    CHECK(status, "VIT_GetInstanceHandle");

    // Reset Instance
    status = VIT_ResetInstance(handle);
    CHECK(status, "VIT_ResetInstance");

    // Set VIT control parameters
    controlparams.OperatingMode = VIT_LPVAD_ENABLE;

    // Apply VIT Control Parameters
    status = VIT_SetControlParameters(handle, &controlparams);
    CHECK(status, "VIT_SetControlParameters");

    SRTM_PdmSdmaAdapter_SetRxLocalBuf(pdmAdapter, &g_local_rx_buf);

error:
    // TODO: uninit everything...
    return;
}

uint8_t voice_engine_algo_process(void *data)
{
    VIT_DataIn_st inputbuffers = {PL_NULL, PL_NULL, PL_NULL};

    VIT_StatusParams_st statusparams_buffer;
    VIT_DetectionStatus_en detectionresults = VIT_NO_DETECTION;
    VIT_ReturnStatus_en status;
    uint32_t i;
    uint32_t input_nb_bytes_per_sample =
        next_buf_size / SAMPLES_PER_FRAME_IN; // delta in bytes between first byte of each sample
                                              // depends on the number of mics configured by the host and audio format

    /* Extract one channel and convert audio samples to float. */
    switch (audio_format)
    {
        case SRTM_Audio_Stereo16Bits:
            for (i = 0; i < SAMPLES_PER_FRAME_IN; i++)
            {
                input_buf[i] = ((int16_t *)data)[i * input_nb_bytes_per_sample / sizeof(int16_t)];
            }
            break;
        case SRTM_Audio_Stereo32Bits:
            for (i = 0; i < SAMPLES_PER_FRAME_IN; i++)
            {
                input_buf[i] =
                    (uint16_t)((((int32_t *)data)[i * input_nb_bytes_per_sample / sizeof(int32_t)] & 0xFFFF0000) >> 16);
            }
            break;
        default:
            PRINTF("ERROR: unsupported audio format: %d\r\n", audio_format);
            return 0;
            break;
    }

    inputbuffers.pBuffer_Chan1 = (PL_INT16 *)input_buf;
    status                     = VIT_Process(handle, &inputbuffers, &detectionresults);
    CHECK(status, "VIT_Process");

    VIT_StatusParams_st *statusparam_buffer = (VIT_StatusParams_st *)&statusparams_buffer;

    VIT_GetStatusParameters(handle, statusparam_buffer, sizeof(statusparams_buffer));

    if (statusparam_buffer->LPVAD_EventDetected)
    {
        PRINTF("VAD : START OF THE DETECTION\r\n");
    }

    return (statusparam_buffer->LPVAD_EventDetected ? 1 : 0);

error:
    return 0;
}

void voice_engine_algo_reset(void)
{
    VIT_ControlParams_st controlparams;

    PRINTF("reset VIT\r\n");

    // Reset Instance
    VIT_ResetInstance(handle);

    // Set VIT control parameters
    controlparams.OperatingMode = VIT_LPVAD_ENABLE;

    // Apply VIT Control Parameters
    VIT_SetControlParameters(handle, &controlparams);
}
