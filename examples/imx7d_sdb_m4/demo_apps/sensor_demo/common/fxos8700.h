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

#ifndef __FXOS_8700_H__
#define __FXOS_8700_H__

#include <stdint.h>
#include <stdbool.h>

/*!
 * @addtogroup fxos8700
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief FXOS8700 I2C address. */
#define FXOS8700_ADDRESS_0          (0x1C)
#define FXOS8700_ADDRESS_1          (0x1D)
#define FXOS8700_ADDRESS_2          (0x1E)
#define FXOS8700_ADDRESS_3          (0x1F)
#define FXOS8700_ADDRESS_DEFAULT    (FXOS8700_ADDRESS_0)

/*! @brief FXOS8700 device ID number. */
#define FXOS8700_DEVICE_ID          (0xC7)

/*! @brief FXOS8700 Registers address definition. */
#define FXOS8700_OUT_X_MSB          (0x01)
#define FXOS8700_WHO_AM_I           (0x0D)
#define FXOS8700_XYZ_DATA_CFG       (0x0E)
#define FXOS8700_CTRL_REG1          (0x2A)
#define FXOS8700_CTRL_REG2          (0x2B)
#define FXOS8700_CTRL_REG3          (0x2C)
#define FXOS8700_CTRL_REG4          (0x2D)
#define FXOS8700_CTRL_REG5          (0x2E)
#define FXOS8700_M_CTRL_REG1        (0x5B)
#define FXOS8700_M_CTRL_REG2        (0x5C)

/*
 * Field Definitions.
 */

/*! @brief fxos8700 output data rate configuration. */
typedef enum _fxos_data_rate_cfg
{
    fxosDataRate800Hz  = 0x0 << 3,
    fxosDataRate400HZ  = 0x1 << 3,
    fxosDataRate200HZ  = 0x2 << 3,
    fxosDataRate100HZ  = 0x3 << 3,
    fxosDataRate50HZ   = 0x4 << 3,
    fxosDataRate12_5HZ = 0x5 << 3,
    fxosDataRate6_25HZ = 0x6 << 3,
    fxosDataRate1_56HZ = 0x7 << 3
} fxos_data_rate_cfg_t;

/*! @brief fxos8700 oversample ratio configuration. */
typedef enum _fxos_oversample_cfg
{
    fxosOSR0 = 0x0 << 2,
    fxosOSR1 = 0x1 << 2,
    fxosOSR2 = 0x2 << 2,
    fxosOSR3 = 0x3 << 2,
    fxosOSR4 = 0x4 << 2,
    fxosOSR5 = 0x5 << 2,
    fxosOSR6 = 0x6 << 2,
    fxosOSR7 = 0x7 << 2
} fxos_oversample_cfg_t;

/*! @brief fxos8700 accelerometer/magnetometer selection. */
typedef enum _fxos_hms_cfg
{
    fxosAccelerometerOnly = 0x0,  /*!< accelerometer only */
    fxosMagnetometerOnly  = 0x1,  /*!< magnetometer only */
    fxosBoth              = 0x3   /*!< select both accelerometer and magnetometer */
} fxos_hms_cfg_t;

/*! @brief fxos accelerometer full-scale range */
typedef enum _fxos_range_cfg
{
    fxosRange2gMode = 0x0, /*!< 2g mode */
    fxosRange4gMode = 0x1, /*!< 4g mode */
    fxosRange8gMode = 0x2  /*!< 8g mode */
} fxos_range_cfg_t;

/*! @brief fxos configure definition. */
typedef struct _fxos_handle
{
    /* I2C relevant definition. */
    i2c_handle_t *device;  /*!< I2C handle. */
    uint8_t       address; /*!< fxos I2C bus address. */
} fxos_handle_t;

/*! @brief Initialize structure of fxos8700 */
typedef struct _fxos_init
{
    fxos_data_rate_cfg_t  dataRate; /*!< Output data rate selection */
    fxos_oversample_cfg_t osr;      /*!< Over sample ratio selection */
    fxos_hms_cfg_t        hms;      /*!< Accelerometer/Magnetometer selection */
    fxos_range_cfg_t      range;    /*!< Accelerometer full scale range selection */
} fxos_init_t;

/*! @brief fxos accelerometer and magnetometer data structure */
typedef struct _fxos_data
{
    int16_t accX;
    int16_t accY;
    int16_t accZ;
    int16_t magX;
    int16_t magY;
    int16_t magZ;
} fxos_data_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief fxos8700 initialize function.
 *
 * This function should be called after i2c module initialize, and in this function,
 * some configurations are fixed. The second parameter is the initialize structure to fxos8700.
 * If users want to change the settings after initialization, they have to use FXOS_writeReg()
 * to set the register value of fxos8700.
 * @param handle fxos8700 handle structure.
 * @param fxos_config fxos8700 configuration structure.
 */
bool FXOS_Init(fxos_handle_t *handle, const fxos_init_t *fxos_config);

/*!
 * @brief Deinit the fxos8700 sensor.
 *
 * Mainly used to set fxos8700 to standby mode and reset its registers content.
 * @param handle fxos8700 handle structure pointer.
 */
bool FXOS_Deinit(fxos_handle_t *handle);

/*!
 * @brief Enable the FXOS8700 sensor.
 * @param handle FXOS8700 handler structure.
 */
bool FXOS_Enable(fxos_handle_t *handle);

/*!
 * @brief Disable the FXOS8700 sensor.
 * @param handle FXOS8700 handler structure.
 */
bool FXOS_Disable(fxos_handle_t *handle);

/*!
 * @brief Write register to fxos8700 using I2C.
 * @param handle fxos8700 handle structure.
 * @param regAddr The register address in fxos8700.
 * @param regVal Value needs to write into the register.
 */
bool FXOS_WriteReg(fxos_handle_t *handle, uint8_t regAddr, uint8_t regVal);

/*!
 * @brief Read register from fxos8700 using I2C.
 * @param handle fxos8700 handle structure.
 * @param regAddr The register address in fxos8700.
 * @param regValPtr The read value buffer pointer.
 */
bool FXOS_ReadReg(fxos_handle_t *handle, uint8_t regAddr, uint8_t *regValPtr);

/*!
 * @brief Read sensor data from fxos8700 using I2C
 * @param handle fxos8700 handle structure.
 * @param val Sensor data read from fxos8700.
 */
bool FXOS_ReadData(fxos_handle_t *handle, fxos_data_t *val);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif/* __FXOS_8700_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
