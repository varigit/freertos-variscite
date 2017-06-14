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

#ifndef __FXAS21002_H__
#define __FXAS21002_H__

/*!
 * @addtogroup fxas21002
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief FXAS21002 I2C address. */
#define FXAS21002_ADDRESS_0             (0x20)
#define FXAS21002_ADDRESS_1             (0x21)
#define FXAS21002_ADDRESS_DEFAULT       (FXAS21002_ADDRESS_0)

/*! @brief FXAS21002 device ID number. */
#define FXAS21002_DEVICE_ID             (0xD7)

/*! @brief FXAS21002 Registers address definition. */
#define FXAS21002_STATUS                (0x00)
#define FXAS21002_OUT_X_MSB             (0x01)
#define FXAS21002_OUT_X_LSB             (0x02)
#define FXAS21002_OUT_Y_MSB             (0x03)
#define FXAS21002_OUT_Y_LSB             (0x04)
#define FXAS21002_OUT_Z_MSB             (0x05)
#define FXAS21002_OUT_Z_LSB             (0x06)
#define FXAS21002_DR_STATUS             (0x07)
#define FXAS21002_F_STATUS              (0x08)
#define FXAS21002_F_SETUP               (0x09)
#define FXAS21002_F_EVENT               (0x0A)
#define FXAS21002_INT_SRC_FLAG          (0x0B)
#define FXAS21002_WHO_AM_I              (0x0C)
#define FXAS21002_CTRL_REG0             (0x0D)
#define FXAS21002_RT_CFG                (0x0E)
#define FXAS21002_RT_SRC                (0x0F)
#define FXAS21002_RT_THS                (0x10)
#define FXAS21002_RT_COUNT              (0x11)
#define FXAS21002_TEMP                  (0x12)
#define FXAS21002_CTRL_REG1             (0x13)
#define FXAS21002_CTRL_REG2             (0x14)
#define FXAS21002_CTRL_REG3             (0x15)

/*
 * Field Definitions.
 */

/*! @brief fxas21002 output data rate configuration. */
typedef enum _fxas_data_rate_cfg
{
    fxasDataRate800Hz  = 0x0 << 2,
    fxasDataRate400HZ  = 0x1 << 2,
    fxasDataRate200HZ  = 0x2 << 2,
    fxasDataRate100HZ  = 0x3 << 2,
    fxasDataRate50HZ   = 0x4 << 2,
    fxasDataRate25HZ   = 0x5 << 2,
    fxasDataRate12_5HZ = 0x6 << 2,
} fxas_data_rate_cfg_t;

/*! @brief fxas21002 gyroscope full-scale range */
typedef enum _fxas_range_cfg
{
    fxasRange2000Dps = 0x0, /*!< +-2000 dps mode */
    fxasRange1000Dps = 0x1, /*!< +-1000 dps mode */
    fxasRange500Dps  = 0x2, /*!< +-500 dps mode */
    fxasRange250Dps  = 0x3  /*!< +-250 dps mode */
} fxas_range_cfg_t;

/*! @brief fxas21002 configure definition. */
typedef struct _fxas_handle
{
    /* I2C relevant definition. */
    i2c_handle_t *device;  /*!< I2C handle. */
    uint8_t       address; /*!< fxas21002 I2C bus address. */
} fxas_handle_t;

/*! @brief Initialize structure of fxas21002 */
typedef struct _fxas_init
{
    fxas_data_rate_cfg_t dataRate; /*!< Output data rate selection */
    fxas_range_cfg_t     range;    /*!< Accelerometer full scale range selection */
} fxas_init_t;

/*! @brief fxas gyroscope data struct */
typedef struct _fxas_data
{
    int16_t gyroX;
    int16_t gyroY;
    int16_t gyroZ;
} fxas_data_t;

/* Function prototypes */
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief fxas21002 initialize function.
 *
 * This function should be called after i2c module initialize, and in this function,
 * some configurations are fixed. The second parameter is the initialize structure to fxas21002.
 * If users want to change the settings after initialization, they have to use FXAS_writeReg()
 * to set the register value of fxas21002.
 * @param handle fxas21002 handle structure.
 * @param fxos_config fxas21002 configuration structure.
 */
bool FXAS_Init(fxas_handle_t *handle, const fxas_init_t *fxas_config);

/*!
 * @brief Deinit the fxas21002 sensor.
 *
 * Mainly used to set fxas21002 to standby mode and reset its registers content.
 * @param handle fxas21002 handle structure pointer.
 */
bool FXAS_Deinit(fxas_handle_t *handle);

/*!
 * @brief Enable the FXAS21002 sensor.
 * @param handle FXAS21002 handler structure.
 */
bool FXAS_Enable(fxas_handle_t *handle);

/*!
 * @brief Disable the FXAS21002 sensor.
 * @param handle FXAS21002 handler structure.
 */
bool FXAS_Disable(fxas_handle_t *handle);

/*!
 * @brief Write register to fxas21002 using I2C.
 * @param handle fxas21002 handle structure.
 * @param regAddr The register address in fxas21002.
 * @param regVal Value needs to write into the register.
 */
bool FXAS_WriteReg(fxas_handle_t *handle, uint8_t regAddr, uint8_t regVal);

/*!
 * @brief Read register from fxas21002 using I2C.
 * @param handle fxas21002 handle structure.
 * @param regAddr The register address in fxas21002.
 * @param regValPtr The read value buffer pointer.
 */
bool FXAS_ReadReg(fxas_handle_t *handle, uint8_t regAddr, uint8_t *regValPtr);

/*!
 * @brief Read sensor data from fxas21002 using I2C
 * @param handler fxas21002 handler structure.
 * @param val Sensor data read from fxas21002.
 */
bool FXAS_ReadData(fxas_handle_t *handle, fxas_data_t *val);

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* __FXAS21002_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
