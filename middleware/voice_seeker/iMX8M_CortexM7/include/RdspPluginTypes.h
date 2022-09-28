/*
Copyright 2021 by Retune DSP
Copyright 2022 NXP

NXP Confidential. This software is owned or controlled by NXP and may only be used strictly in accordance with the applicable license terms.  By expressly accepting such terms or by downloading, installing, activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef RDSP_VOICESEEKERLIGHT_PLUGIN_TYPES_H_
#define RDSP_VOICESEEKERLIGHT_PLUGIN_TYPES_H_

#include <stdint.h>

#ifdef HIFI4
#include <xtensa/tie/xt_hifi4.h>
#include <xtensa/tie/xt_FP.h>
#include "NatureDSP_Signal.h"
#include "NatureDSP_types.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HIFI4
	typedef xtfloat rfloat;
	typedef xtfloatx2 rfloat2;
	typedef xtfloatx2 rdsp_complex;
#else
	typedef float rfloat;
	typedef float rfloat2[2];
	typedef float rdsp_complex[2];
#endif

	typedef rfloat rdsp_coordinate_xyz_t[3];

#ifdef __cplusplus
}
#endif

#endif // RDSP_VOICESEEKERLIGHT_PLUGIN_TYPES_H_
