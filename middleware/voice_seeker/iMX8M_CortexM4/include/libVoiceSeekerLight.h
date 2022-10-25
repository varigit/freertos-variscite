/*
Copyright 2021 by Retune DSP
Copyright 2022 NXP

NXP Confidential. This software is owned or controlled by NXP and may only be used strictly in accordance with the applicable license terms.  By expressly accepting such terms or by downloading, installing, activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef RDSP_VOICESEEKER_LIGHT_PLUGIN_H_
#define RDSP_VOICESEEKER_LIGHT_PLUGIN_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "RdspPublicUtilities.h"
#include "RdspPluginTypes.h"
#include "RdspStatusCodes.h"

typedef struct rdsp_voiceseekerlight_ver_struct_s {
	int32_t major;
	int32_t minor;
	int32_t patch;
} rdsp_voiceseekerlight_ver_struct_t;

typedef struct rdsp_voiceseekerlight_config_s {
	uint32_t num_mics;
	uint32_t max_num_mics; // (ro)
	uint32_t num_spks;
	uint32_t max_num_spks; // (ro)
	rdsp_coordinate_xyz_t* mic_xyz_mm;
	uint32_t samplerate;
	uint32_t framesize_in; // (ro)
	uint32_t framesize_out;
	int32_t create_aec;
	rfloat buffer_length_sec;
	uint32_t aec_filter_length_ms;
} rdsp_voiceseekerlight_config_t;

typedef struct RETUNE_VOICESEEKER_plugin_s {
	rdsp_voiceseekerlight_ver_struct_t version; // (ro)
	rdsp_voiceseekerlight_config_t config;
	rdsp_mem_t mem;
	uint32_t sysdefs_checksum; // (ro) CRC checksum of xml sysdefs entries: name, id, length, used by app/tool to find matching rdsp2 file 
} RETUNE_VOICESEEKERLIGHT_plugin_t;

/*
 * VoiceSeeker Light
 */

extern RdspStatus VoiceSeekerLight_Create(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit, rdsp_voiceseekerlight_config_t* Aconfig);
extern void VoiceSeekerLight_Init(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit);
extern int32_t VoiceSeekerLight_SetParameterID(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit, uint32_t Aid, uint32_t Alength, uint32_t* Avalues);
extern int32_t VoiceSeekerLight_SetParameterBin(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit, const char* Aparameter_bin);
extern int32_t VoiceSeekerLight_SetParameterXml(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit, const char* Aparameter_xml);
extern RdspStatus VoiceSeekerLight_Process(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit, float** Amic_in, float** Aref_in, float** Aout);
extern void VoiceSeekerLight_TriggerFound(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit, uint32_t Atrigger_start_offset_samples);
extern void VoiceSeekerLight_Destroy(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit);

extern uint32_t VoiceSeekerLightGetPersistantMemUsage(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit);
extern uint32_t VoiceSeekerLightGetScratchMemUsage(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit);
extern uint32_t VoiceSeekerLightGetCycleUsage(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit);
extern void VoiceSeekerLight_GetConfig(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit, rdsp_voiceseekerlight_config_t* Acfg);
extern void VoiceSeekerLight_PrintConfig(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit);
extern void VoiceSeekerLight_PrintMemOverview(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit);

/*
 * Additional DSP Blocks
 */

/*
 * Resampling Utility
 */

extern RdspStatus VoiceSeekerLight_MicResample_Create(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit, int32_t AresampleFactor);
extern void VoiceSeekerLight_MicResample_Init(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit_s);
extern void VoiceSeekerLight_MicResample_Downsample_Process(rfloat** Amic_in, int32_t Anum_channels);
extern void VoiceSeekerLight_MicResample_Upsample_Process(rfloat** Amic_in, int32_t Anum_channels);
extern void VoiceSeekerLight_MicResample_Destroy(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit);

extern RdspStatus VoiceSeekerLight_SpkResample_Create(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit, int32_t AresampleFactor);
extern void VoiceSeekerLight_SpkResample_Init(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit_s);
extern void VoiceSeekerLight_SpkResample_Downsample_Process(rfloat** Aspkc_in, int32_t Anum_channels);
extern void VoiceSeekerLight_SpkResample_Upsample_Process(rfloat** Aspk_in, int32_t Anum_channels);
extern void VoiceSeekerLight_SpkResample_Destroy(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit);

 /*
  * Voice Activity Detector
  */

extern RdspStatus VoiceSeekerLight_Vad_Create(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit);
extern void VoiceSeekerLight_Vad_Init(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit);
extern int32_t VoiceSeekerLight_Vad_Process(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit, rfloat* Avad_in);
extern void VoiceSeekerLight_Vad_Destroy(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit);

/*
 * Automatic Gain Control
 */

extern RdspStatus VoiceSeekerLight_Agc_Create(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit);
extern void VoiceSeekerLight_Agc_Init(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit);
extern void VoiceSeekerLight_Agc_ComputeMaxAbs(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit, rfloat* Aagc_in, int32_t Anum_samples);
extern void VoiceSeekerLight_Agc_ComputeGain(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit);
extern void VoiceSeekerLight_Agc_ApplyGain(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit, rfloat* Aagc_in, int32_t Anum_samples);
extern void VoiceSeekerLight_Agc_Destroy(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit);

/*
 * Windback Buffer
 */

extern RdspStatus VoiceSeekerLight_WindbackBuffer_Create(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit);
extern void VoiceSeekerLight_WindbackBuffer_Init(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit);
extern void VoiceSeekerLight_WindbackBuffer_GetCircularBufReg(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit, rfloat** AStartPtr, rfloat** AEndPtr);
extern void VoiceSeekerLight_WindbackBuffer_WriteToBuffer(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit, rfloat* Ax, int32_t Anum_samples);
extern rfloat* VoiceSeekerLight_WindbackBuffer_GetReadPointer(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit, uint32_t Asample);
extern void VoiceSeekerLight_WindbackBuffer_Destroy(RETUNE_VOICESEEKERLIGHT_plugin_t* APluginInit);

#ifdef __cplusplus
}
#endif

#endif // RDSP_VOICESEEKER_LIGHT_PLUGIN_H_
