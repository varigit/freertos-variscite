/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __MPL3115_H__
#define __MPL3115_H__

#include <stdint.h>
#include <stdbool.h>

/*!
 * @addtogroup mpl3115
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief MPL3115 I2C address. */
#define MPL3115_ADDRESS            (0x60)

/*! @brief MPL3115 device ID number. */
#define MPL3115_DEVICE_ID          (0xC4)

/*! @briefRegister address Definitions. */
#define MPL3115_STATUS             (0x00)
#define MPL3115_OUT_P_MSB          (0x01)
#define MPL3115_OUT_P_CSB          (0x02)
#define MPL3115_OUT_P_LSB          (0x03)
#define MPL3115_OUT_T_MSB          (0x04)
#define MPL3115_OUT_T_LSB          (0x05)
#define MPL3115_DR_STATUS          (0x06)
#define MPL3115_OUT_P_DELTA_MSB    (0x07)
#define MPL3115_OUT_P_DELTA_CSB    (0x08)
#define MPL3115_OUT_P_DELTA_LSB    (0x09)
#define MPL3115_OUT_T_DELTA_MSB    (0x0A)
#define MPL3115_OUT_T_DELTA_LSB    (0x0B)
#define MPL3115_WHO_AM_I           (0x0C)
#define MPL3115_F_STATUS           (0x0D)
#define MPL3115_F_DATA             (0x0E)
#define MPL3115_F_SETUP            (0x0F)
#define MPL3115_TIME_DLY           (0x10)
#define MPL3115_SYSMOD             (0x11)
#define MPL3115_INT_SOURCE         (0x12)
#define MPL3115_PT_DATA_CFG        (0x13)
#define MPL3115_BAR_IN_MSB         (0x14)
#define MPL3115_BAR_IN_LSB         (0x15)
#define MPL3115_P_TGT_MSB          (0x16)
#define MPL3115_P_TGT_LSB          (0x17)
#define MPL3115_T_TGT              (0x18)
#define MPL3115_P_WND_MSB          (0x19)
#define MPL3115_P_WND_LSB          (0x1A)
#define MPL3115_T_WND              (0x1B)
#define MPL3115_P_MIN_MSB          (0x1C)
#define MPL3115_P_MIN_CSB          (0x1D)
#define MPL3115_P_MIN_LSB          (0x1E)
#define MPL3115_T_MIN_MSB          (0x1F)
#define MPL3115_T_MIN_LSB          (0x20)
#define MPL3115_P_MAX_MSB          (0x21)
#define MPL3115_P_MAX_CSB          (0x22)
#define MPL3115_P_MAX_LSB          (0x23)
#define MPL3115_T_MAX_MSB          (0x24)
#define MPL3115_T_MAX_LSB          (0x25)
#define MPL3115_CTRL_REG1          (0x26)
#define MPL3115_CTRL_REG2          (0x27)
#define MPL3115_CTRL_REG3          (0x28)
#define MPL3115_CTRL_REG4          (0x29)
#define MPL3115_CTRL_REG5          (0x2A)
#define MPL3115_OFF_P              (0x2B)
#define MPL3115_OFF_T              (0x2C)
#define MPL3115_OFF_H              (0x2D)

/*
 * Field Definitions.
 */

/*! @brief mpl3115 Altimeter/Barometer selection. */
typedef enum _mpl3115_output_format_cfg
{
    mpl3115OutputFormatAltimeter = 0x80,
    mpl3115OutputFormatBarometer = 0x0
} mpl3115_output_format_cfg_t;

/*! @brief mpl3115 raw data output without digital data processing selection. */
typedef enum _mpl3115_output_mode_cfg
{
    mpl3115OutputModeRaw         = 0x40,
    mpl3115OutputModeNormal      = 0x0
} mpl3115_output_mode_cfg_t;

/*! @brief mpl3115 oversample ratio selection. */
typedef enum _mpl3115_oversample_cfg
{
    mpl3115OverSampleX1          = 0x0 << 3,
    mpl3115OverSampleX2          = 0x1 << 3,
    mpl3115OverSampleX4          = 0x2 << 3,
    mpl3115OverSampleX8          = 0x3 << 3,
    mpl3115OverSampleX16         = 0x4 << 3,
    mpl3115OverSampleX32         = 0x5 << 3,
    mpl3115OverSampleX64         = 0x6 << 3,
    mpl3115OverSampleX128        = 0x7 << 3
} mpl3115_oversample_cfg_t;

/*! @brief fxos configure definition. */
typedef struct _mpl_handle
{
    /* I2C relevant definition. */
    i2c_handle_t *device;  /*!< I2C handle. */
} mpl_handle_t;

/*! @brief Initialize structure of mpl3115 */
typedef struct _mpl3115_init
{
    mpl3115_output_format_cfg_t outputFormat;
    mpl3115_output_mode_cfg_t   outputMode;
    mpl3115_oversample_cfg_t    oversampleRatio;
} mpl3115_init_t;

/*! @brief mpl3115 Pressure/Altitude and Temperature data structure */
typedef struct _mpl3115_data
{
    int32_t presData;
    int16_t tempData;
} mpl3115_data_t;

/*******************************************************************************
 * API
 ******************************************************************************/
/* Function prototypes */
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief MPL3115 initialize function.
 *
 * This function should be called after I2C transfer driver is initialized, and
 * in this function, some configurations are fixed.
 * If users want to change the settings, they have to use fxos_write_reg() to set
 * the register value of MPL3115.
 * @param handle MPL3115 handle structure.
 * @param mpl3115_config mpl3115 configuration structure.
 */
bool MPL3115_Init(mpl_handle_t *handle, const mpl3115_init_t *mpl3115_config);

/*!
 * @brief Deinit the MPL3115 sensor.
 * @param handle MPL3115 handler structure.
 */
bool MPL3115_Deinit(mpl_handle_t *handle);

/*!
 * @brief Enable the MPL3115 sensor.
 * @param handle MPL3115 handler structure.
 */
bool MPL3115_Enable(mpl_handle_t *handle);

/*!
 * @brief Disable the MPL3115 sensor.
 * @param handle MPL3115 handler structure.
 */
bool MPL3115_Disable(mpl_handle_t *handle);

/*!
 * @brief Write register to MPL3115 using I2C.
 * @param handle MPL3115 handle structure.
 * @param regAddr The register address in mpl3115.
 * @param regVal Value needs to write into the register.
 */
bool MPL3115_WriteReg(mpl_handle_t *handle, uint8_t regAddr, uint8_t regVal);

/*!
 * @brief Read register from MPL3115 using I2C.
 * @param handle MPL3115 handle structure.
 * @param regAddr The register address in mpl3115.
 * @param regValPtr Value pointer to written into.
 */
bool MPL3115_ReadReg(mpl_handle_t *handle, uint8_t regAddr, uint8_t *regValPtr);

/*!
 * @brief Read sensor data from MPL3115 using I2C
 * @param handle MPL3115 handler structure.
 * @param val Sensor data pointer read from mpl3115.
 */
bool MPL3115_ReadData(mpl_handle_t *handle, mpl3115_data_t *val);

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* __MPL3115_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
