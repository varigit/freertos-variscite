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

///////////////////////////////////////////////////////////////////////////////
//  Includes
///////////////////////////////////////////////////////////////////////////////
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "board.h"
#include "rdc_semaphore.h"
#include "debug_console_imx.h"
#include "gpio_pins.h"
#include "gpio_imx.h"
#include "i2c_xfer.h"
#include "fxas21002.h"
#include "fxos8700.h"
#include "mpl3115.h"

////////////////////////////////////////////////////////////////////////////////
// Definition
////////////////////////////////////////////////////////////////////////////////
#define HEIGHT_UPDATE_THRESHOLD     (0.5f)
#define TEMP_UPDATE_THRESHOLD       (0.3f)
#define GYRO_UPDATE_THRESHOLD       (5.0f)
#define GYRO_OVERSAMPLE_RATIO       (10)

#define MPL3115_MPERCOUNT           (0.0000152587890625f) // 1/65536 fixed range for MPL3115
#define MPL3115_CPERCPOUNT          (0.00390625f)         // 1/256 fixed range for MPL3115
#define FXAS21002_DEGPERSECPERCOUNT (0.0625F)             // must be reciprocal of FCOUNTSPERDEGPERSEC

////////////////////////////////////////////////////////////////////////////////
// Type definition
////////////////////////////////////////////////////////////////////////////////
typedef struct _gyro_sensor
{
    int32_t iSumYpFast[3];         // sum of fast measurements
    float   fYp[3];                // raw gyro sensor output (deg/s)
    float   fDegPerSecPerCount;    // initialized to FDEGPERSECPERCOUNT
    int16_t iYpFast[3];            // fast (typically 200Hz) readings
    int16_t iYp[3];                // averaged gyro sensor output (counts)
} gyro_sensor_t;

typedef struct _pressure_sensor
{
    float fHp;                     // float point type height (m)
    float fTp;                     // float point type temperature (C)
    float fmPerCount;              // initialized to FMPERCOUNT
    float fCPerCount;              // initialized to FCPERCPOUNT
} pressure_sensor_t;

////////////////////////////////////////////////////////////////////////////////
// Static Variable
////////////////////////////////////////////////////////////////////////////////
static i2c_handle_t      I2C_handle;
static SemaphoreHandle_t xSemaphore;
static fxas_handle_t     fxasHandle = {.device  = &I2C_handle, 
                                       .address = BOARD_I2C_FXAS21002_ADDR};
static fxos_handle_t     fxosHandle = {.device  = &I2C_handle,
                                       .address = BOARD_I2C_FXOS8700_ADDR};
static mpl_handle_t      mplHandle  = {.device  = &I2C_handle};

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////
int32_t getOneDecimalPlace(float num)
{
    if (num < 0)
        return -(((int32_t)(num * 10)) % 10);
    else
        return (((int32_t)(num * 10)) % 10);
}

void printGyro(float Gxf, float Gyf, float Gzf)
{
    PRINTF("[FXAS21002] Rotate detected: X:%5d.%1ddps, Y:%5d.%1ddps, Z:%5d.%1ddps\n\r",
           (int32_t)Gxf,
           getOneDecimalPlace(Gxf),
           (int32_t)Gyf,
           getOneDecimalPlace(Gyf),
           (int32_t)Gzf,
           getOneDecimalPlace(Gzf));
}

void printAccMag(float Axf, float Ayf, float Azf, float Mxf, float Myf, float Mzf)
{
    PRINTF("[FXOS8700]Current Acc:X=%7d.%1dg Y=%7d.%1dg Z=%7d.%1dg\n\r",
           (int32_t)Axf,
           getOneDecimalPlace(Axf),
           (int32_t)Ayf,
           getOneDecimalPlace(Ayf),
           (int32_t)Azf,
           getOneDecimalPlace(Azf));
    PRINTF("[FXOS8700]Current Mag:X=%6d.%1duT Y=%6d.%1duT Z=%6d.%1duT\n\r",
           (int32_t)Mxf,
           getOneDecimalPlace(Mxf),
           (int32_t)Myf,
           getOneDecimalPlace(Myf),
           (int32_t)Mzf,
           getOneDecimalPlace(Mzf));
}

void printHeightTmp(float height, float tmp)
{
    PRINTF("[MPL3115]Current Height = %6d.%1dMeter, Current Temp = %6d.%1dCelsius\n\r",
           (int32_t)height,
           getOneDecimalPlace(height),
           (int32_t)tmp,
           getOneDecimalPlace(tmp));
}

void fxas21002OutputUpdate(gyro_sensor_t *gyroSensorPtr)
{
    static uint32_t count = 0, printCount = 0;

    count++;
    if (count == GYRO_OVERSAMPLE_RATIO)
    {
        count = 0;
        gyroSensorPtr->iYp[0] = gyroSensorPtr->iSumYpFast[0] / GYRO_OVERSAMPLE_RATIO;
        gyroSensorPtr->iYp[1] = gyroSensorPtr->iSumYpFast[1] / GYRO_OVERSAMPLE_RATIO;
        gyroSensorPtr->iYp[2] = gyroSensorPtr->iSumYpFast[2] / GYRO_OVERSAMPLE_RATIO;
        gyroSensorPtr->fYp[0] = gyroSensorPtr->iYp[0] * gyroSensorPtr->fDegPerSecPerCount;
        gyroSensorPtr->fYp[1] = gyroSensorPtr->iYp[1] * gyroSensorPtr->fDegPerSecPerCount;
        gyroSensorPtr->fYp[2] = gyroSensorPtr->iYp[2] * gyroSensorPtr->fDegPerSecPerCount;
        gyroSensorPtr->iSumYpFast[0] = 0;
        gyroSensorPtr->iSumYpFast[1] = 0;
        gyroSensorPtr->iSumYpFast[2] = 0;
    }

    if ((gyroSensorPtr->fYp[0] > GYRO_UPDATE_THRESHOLD)  ||
        (gyroSensorPtr->fYp[0] < -GYRO_UPDATE_THRESHOLD) ||
        (gyroSensorPtr->fYp[1] > GYRO_UPDATE_THRESHOLD)  ||
        (gyroSensorPtr->fYp[1] < -GYRO_UPDATE_THRESHOLD) ||
        (gyroSensorPtr->fYp[2] > GYRO_UPDATE_THRESHOLD)  ||
        (gyroSensorPtr->fYp[2] < -GYRO_UPDATE_THRESHOLD))
    {
        printCount++;
        if (5 == printCount)
        {
            printCount = 0;
            printGyro(gyroSensorPtr->fYp[0], gyroSensorPtr->fYp[1], gyroSensorPtr->fYp[2]);
        }
    }
}

void mpl3115OutputUpdate(pressure_sensor_t *pressureSensorPtr)
{
    static float lastHight = 0, lastTemp = 0;

    /* Print the data to terminal, if the delta exceed threshold. */
    if (((pressureSensorPtr->fHp - lastHight) > HEIGHT_UPDATE_THRESHOLD)  ||
        ((pressureSensorPtr->fHp - lastHight) < -HEIGHT_UPDATE_THRESHOLD) ||
        ((pressureSensorPtr->fTp - lastTemp) > TEMP_UPDATE_THRESHOLD)     ||
        ((pressureSensorPtr->fTp - lastTemp) < -TEMP_UPDATE_THRESHOLD))
    {
        lastHight = pressureSensorPtr->fHp;
        lastTemp = pressureSensorPtr->fTp;
        printHeightTmp(pressureSensorPtr->fHp, pressureSensorPtr->fTp);
    }
}

void fxas21002Demo_Pol(void)
{
    const fxas_init_t initConfig = {
        .dataRate = fxasDataRate100HZ,
        .range    = fxasRange2000Dps
    };

    fxas_data_t fxasData;
    gyro_sensor_t thisGyroSensor;

    memset(&thisGyroSensor, 0, sizeof(thisGyroSensor));
    thisGyroSensor.fDegPerSecPerCount = FXAS21002_DEGPERSECPERCOUNT;

    PRINTF("\n\r-------------- FXAS21002 Gyro data acquisition --------------\n\r\n\r");

    PRINTF("FXAS21002 initialization ... ");
    if (FXAS_Init(&fxasHandle, &initConfig))
        PRINTF("OK\n\r");
    else
        PRINTF("ERROR\n\r");

    /* Active FXAS21002. */
    FXAS_Enable(&fxasHandle);

    /* Delay 100ms to wait sensor init finish */
    vTaskDelay(100);

    PRINTF("Please rotate the board to acquire current angular velocity\n\r");

    while(1)
    {
        vTaskDelay(10);

        FXAS_ReadData(&fxasHandle, &fxasData);
        thisGyroSensor.iSumYpFast[0] += fxasData.gyroX;
        thisGyroSensor.iSumYpFast[1] += fxasData.gyroY;
        thisGyroSensor.iSumYpFast[2] += fxasData.gyroZ;

        fxas21002OutputUpdate(&thisGyroSensor);
    }
}

void fxas21002Demo_Int(void)
{
    const fxas_init_t initConfig = {
        .dataRate = fxasDataRate100HZ,
        .range    = fxasRange2000Dps
    };

    fxas_data_t fxasData;
    gyro_sensor_t thisGyroSensor;

    memset(&thisGyroSensor, 0, sizeof(thisGyroSensor));
    thisGyroSensor.fDegPerSecPerCount = FXAS21002_DEGPERSECPERCOUNT;

    PRINTF("\n\r-------------- FXAS21002 Gyro data acquisition --------------\n\r\n\r");

    PRINTF("FXAS21002 initialization ... ");
    if (FXAS_Init(&fxasHandle, &initConfig))
        PRINTF("OK\n\r");
    else
        PRINTF("ERROR\n\r");

    /* Delay 100ms to wait sensor init finish */
    vTaskDelay(100);

    /* Enable Data Ready Interrupt. */
    // 1.Route Data Ready Interrupt to INT1 Pin;
    // 2.Set INT1 Pin logic polarity to Active Low;
    // 3.Set INT1 Pin output driver configuration to Open-drain;
    // 4.Enable Data Ready Interrupt.
    FXAS_WriteReg(&fxasHandle, FXAS21002_CTRL_REG2, 0x0C);

    /* Active FXAS21002 Sensor. */
    FXAS_Enable(&fxasHandle);

    PRINTF("Please rotate the board to acquire current angular velocity\n\r");

    while(1)
    {
        /* Wait until sensor data ready. */
        if (pdTRUE == xSemaphoreTake(xSemaphore, 100))
        {
            /* Read data from sensor */
            FXAS_ReadData(&fxasHandle, &fxasData);
            thisGyroSensor.iSumYpFast[0] += fxasData.gyroX;
            thisGyroSensor.iSumYpFast[1] += fxasData.gyroY;
            thisGyroSensor.iSumYpFast[2] += fxasData.gyroZ;
            fxas21002OutputUpdate(&thisGyroSensor);
        }
        else
        {
            /* Because the GPIO interrutp of Sensor Int pin will be masked when Linux
             * boot on Cortex-A7 Core, so we provide this walkaround to enable the GPIO
             * interrupt of Sensor Int pin here, if we did not get the sensor data ready
             * interrupt for a long time.
             */
            NVIC_DisableIRQ(BOARD_GPIO_SENSOR_IRQ_NUM);
            RDC_SEMAPHORE_Lock(BOARD_GPIO_SENSOR_RDC_PDAP);
            GPIO_SetPinIntMode(BOARD_GPIO_SENSOR_CONFIG->base, BOARD_GPIO_SENSOR_CONFIG->pin, true);
            RDC_SEMAPHORE_Unlock(BOARD_GPIO_SENSOR_RDC_PDAP);
            NVIC_EnableIRQ(BOARD_GPIO_SENSOR_IRQ_NUM);
        }
    }
}

void fxos8700Demo_Pol(void)
{
    const fxos_init_t initConfig = {
        .dataRate = fxosDataRate400HZ,
        .osr      = fxosOSR7,
        .hms      = fxosBoth,
        .range    = fxosRange4gMode
    };

    fxos_data_t fxos8700Data;
    float Axf, Ayf, Azf, Mxf, Myf, Mzf;

    PRINTF("\n\r-------------- FXOS8700 Acc+Mag data acquisition --------------\n\r\n\r");

    PRINTF("FXOS8700 initialization  ... ");
    if (FXOS_Init(&fxosHandle, &initConfig))
        PRINTF("OK\n\r");
    else
        PRINTF("ERROR\n\r");

    /* Active FXOS8700 Sensor. */
    FXOS_Enable(&fxosHandle);

    while(1)
    {
        vTaskDelay(500);
        FXOS_ReadData(&fxosHandle, &fxos8700Data);
        Axf = fxos8700Data.accX / 8192.0;
        Ayf = fxos8700Data.accY / 8192.0;
        Azf = fxos8700Data.accZ / 8192.0;
        Mxf = fxos8700Data.magX * 0.1;
        Myf = fxos8700Data.magY * 0.1;
        Mzf = fxos8700Data.magZ * 0.1;
        printAccMag(Axf, Ayf, Azf, Mxf, Myf, Mzf);
    }
}

void fxos8700Demo_Int(void)
{
    const fxos_init_t initConfig = {
        .dataRate = fxosDataRate1_56HZ,
        .osr      = fxosOSR7,
        .hms      = fxosBoth,
        .range    = fxosRange4gMode
    };

    fxos_data_t fxos8700Data;
    float Axf, Ayf, Azf, Mxf, Myf, Mzf;

    PRINTF("\n\r-------------- FXOS8700 Acc+Mag data acquisition --------------\n\r\n\r");

    PRINTF("FXOS8700 initialization  ... ");
    if (FXOS_Init(&fxosHandle, &initConfig))
        PRINTF("OK\n\r");
    else
        PRINTF("ERROR\n\r");

    /* Enable Data Ready Interrupt. */
    // Set Interrupt pin to Active Low & Open-Drain.
    FXOS_WriteReg(&fxosHandle, FXOS8700_CTRL_REG3, 0x01);

    // Route Data Ready Interrupt to Int1 Pin.
    FXOS_WriteReg(&fxosHandle, FXOS8700_CTRL_REG5, 0x01);

    // Enable Data Ready Interrupt.
    FXOS_WriteReg(&fxosHandle, FXOS8700_CTRL_REG4, 0x01);

    /* Active FXOS8700. */
    FXOS_Enable(&fxosHandle);

    while(1)
    {
        /* Wait until sensor data ready. */
        if (pdTRUE == xSemaphoreTake(xSemaphore, 1500))
        {
            /* Read data from sensor */
            FXOS_ReadData(&fxosHandle, &fxos8700Data);
            Axf = fxos8700Data.accX / 8192.0;
            Ayf = fxos8700Data.accY / 8192.0;
            Azf = fxos8700Data.accZ / 8192.0;
            Mxf = fxos8700Data.magX * 0.1;
            Myf = fxos8700Data.magY * 0.1;
            Mzf = fxos8700Data.magZ * 0.1;

            /* Print to terminal */
            printAccMag(Axf, Ayf, Azf, Mxf, Myf, Mzf);
        }
        else
        {
            /* Because the GPIO interrutp of Sensor Int pin will be masked when Linux
             * boot on Cortex-A7 Core, so we provide this walkaround to enable the GPIO
             * interrupt of Sensor Int pin here, if we did not get the sensor data ready
             * interrupt for a long time.
             */
            NVIC_DisableIRQ(BOARD_GPIO_SENSOR_IRQ_NUM);
            RDC_SEMAPHORE_Lock(BOARD_GPIO_SENSOR_RDC_PDAP);
            GPIO_SetPinIntMode(BOARD_GPIO_SENSOR_CONFIG->base, BOARD_GPIO_SENSOR_CONFIG->pin, true);
            RDC_SEMAPHORE_Unlock(BOARD_GPIO_SENSOR_RDC_PDAP);
            NVIC_EnableIRQ(BOARD_GPIO_SENSOR_IRQ_NUM);
        }
    }
}

void mpl3115Demo_Pol(void)
{
    const mpl3115_init_t initConfig = {
        .outputFormat = mpl3115OutputFormatAltimeter,
        .outputMode   = mpl3115OutputModeNormal,
        .oversampleRatio = mpl3115OverSampleX128
    };

    mpl3115_data_t mpl3115Data;
    pressure_sensor_t thisPressureSensor;

    memset(&thisPressureSensor, 0, sizeof(thisPressureSensor));
    thisPressureSensor.fmPerCount = MPL3115_MPERCOUNT;
    thisPressureSensor.fCPerCount = MPL3115_CPERCPOUNT;

    PRINTF("\n\r-------------- MPL3115 Pressure data acquisition --------------\n\r\n\r");

    PRINTF("MPL3115 initialization   ... ");
    if (MPL3115_Init(&mplHandle, &initConfig))
        PRINTF("OK\n\r");
    else
        PRINTF("ERROR\n\r");

    /* Active MPL3115 Sensor. */
    MPL3115_Enable(&mplHandle);

    while(1)
    {
        vTaskDelay(500);
        MPL3115_ReadData(&mplHandle, &mpl3115Data);

        thisPressureSensor.fHp = (float) mpl3115Data.presData *
                  thisPressureSensor.fmPerCount;
        thisPressureSensor.fTp = (float) mpl3115Data.tempData *
                  thisPressureSensor.fCPerCount;

        mpl3115OutputUpdate(&thisPressureSensor);
    }
}

void mpl3115Demo_Int(void)
{
    const mpl3115_init_t initConfig = {
        .outputFormat = mpl3115OutputFormatAltimeter,
        .outputMode   = mpl3115OutputModeNormal,
        .oversampleRatio = mpl3115OverSampleX128
    };

    mpl3115_data_t mpl3115Data;
    pressure_sensor_t thisPressureSensor;

    memset(&thisPressureSensor, 0, sizeof(thisPressureSensor));
    thisPressureSensor.fmPerCount = MPL3115_MPERCOUNT;
    thisPressureSensor.fCPerCount = MPL3115_CPERCPOUNT;

    PRINTF("\n\r-------------- MPL3115 Pressure data acquisition --------------\n\r\n\r");

    PRINTF("MPL3115 initialization   ... ");
    if (MPL3115_Init(&mplHandle, &initConfig))
        PRINTF("OK\n\r");
    else
        PRINTF("ERROR\n\r");

    /* Enable Data Ready Interrupt. */
    // MPL3115 Interrupt source to generate data ready event
    // flag on new Pressure/Altitude or Temperature data.
    MPL3115_WriteReg(&mplHandle, MPL3115_PT_DATA_CFG, 0x07);

    // Set interrupt pad INT1 & INT2 to Active Low & Open Drain.
    MPL3115_WriteReg(&mplHandle, MPL3115_CTRL_REG3, 0x11);

    // Route Data Ready Interrupt to interrupt pad INT1.
    MPL3115_WriteReg(&mplHandle, MPL3115_CTRL_REG5, 0x80);

    // Enable Data Ready Interrupt.
    MPL3115_WriteReg(&mplHandle, MPL3115_CTRL_REG4, 0x80);

    /* Active MPL3115 Sensor. */
    MPL3115_Enable(&mplHandle);

    while(1)
    {
        /* Wait until sensor data ready. */
        if (pdTRUE == xSemaphoreTake(xSemaphore, 1000))
        {
            /* Get the latest data from sensor */
            MPL3115_ReadData(&mplHandle, &mpl3115Data);

            /* Convert sensor data to standard unit. */
            thisPressureSensor.fHp = (float) mpl3115Data.presData *
                      thisPressureSensor.fmPerCount;
            thisPressureSensor.fTp = (float) mpl3115Data.tempData *
                      thisPressureSensor.fCPerCount;

            mpl3115OutputUpdate(&thisPressureSensor);
        }
        else
        {
            /* Because the GPIO interrutp of Sensor Int pin will be masked when Linux
             * boot on Cortex-A7 Core, so we provide this walkaround to enable the GPIO
             * interrupt of Sensor Int pin here, if we did not get the sensor data ready
             * interrupt for a long time.
             */
            NVIC_DisableIRQ(BOARD_GPIO_SENSOR_IRQ_NUM);
            RDC_SEMAPHORE_Lock(BOARD_GPIO_SENSOR_RDC_PDAP);
            GPIO_SetPinIntMode(BOARD_GPIO_SENSOR_CONFIG->base, BOARD_GPIO_SENSOR_CONFIG->pin, true);
            RDC_SEMAPHORE_Unlock(BOARD_GPIO_SENSOR_RDC_PDAP);
            NVIC_EnableIRQ(BOARD_GPIO_SENSOR_IRQ_NUM);
        }
    }
}

void MainTask(void *pvParameters)
{
    uint8_t demoSel;

    /* GPIO module initialize, configure button as interrupt mode. */
    gpio_init_config_t sensorIntInitConfig = {
        .pin = BOARD_GPIO_SENSOR_CONFIG->pin,
        .direction = gpioDigitalInput,
        .interruptMode = gpioIntFallingEdge
    };

    /* Setup I2C init structure. */
    i2c_xfer_init_config_t i2cInitConfig = {
        .base   = BOARD_I2C_BASEADDR,
        .config = {
            .clockRate    = get_i2c_clock_freq(BOARD_I2C_BASEADDR),
            .baudRate     = 400000u,
            .slaveAddress = 0x00
        },
        .irqNum  = BOARD_I2C_IRQ_NUM,
        .irqPrio = 3
    };

    PRINTF("\n\r-------------- iMX7D SDB on board sensor example --------------\n\r\n\r");

    /* Data acquire sync semi4 init. */
    xSemaphore = xSemaphoreCreateBinary();

    /* Initialize I2C module with I2C init structure. */
    I2C_XFER_Init(&I2C_handle, &i2cInitConfig);

    /* Deinit on-board sensors to avoid unexpected interrupt. */
    FXAS_Deinit(&fxasHandle);
    FXOS_Deinit(&fxosHandle);
    MPL3115_Deinit(&mplHandle);
    vTaskDelay(50);

    /* Acquire RDC semaphore before access GPIO to avoid conflict, it's
     * necessary when GPIO RDC is configured as Semaphore Required */
    RDC_SEMAPHORE_Lock(BOARD_GPIO_SENSOR_RDC_PDAP);

    GPIO_Init(BOARD_GPIO_SENSOR_CONFIG->base, &sensorIntInitConfig);

    /* Clear the interrupt state, this operation is necessary, because the GPIO module maybe confuse
       the first rising edge as interrupt*/
    GPIO_ClearStatusFlag(BOARD_GPIO_SENSOR_CONFIG->base, BOARD_GPIO_SENSOR_CONFIG->pin);
    /* Enable GPIO pin interrupt */
    GPIO_SetPinIntMode(BOARD_GPIO_SENSOR_CONFIG->base, BOARD_GPIO_SENSOR_CONFIG->pin, true);

    RDC_SEMAPHORE_Unlock(BOARD_GPIO_SENSOR_RDC_PDAP);

    /* Set I2C Interrupt priority */
    NVIC_SetPriority(BOARD_GPIO_SENSOR_IRQ_NUM, 3);
    NVIC_EnableIRQ(BOARD_GPIO_SENSOR_IRQ_NUM);

    /* Print the initial banner. */
    PRINTF("\n\rPlease select the sensor demo you want to run:\n\r");
    PRINTF("[1].FXAS21002 3-axes Gyro sensor Polling Demo\n\r");
    PRINTF("[2].FXAS21002 3-axes Gyro sensor Interrupt Demo\n\r");
    PRINTF("[3].FXOS8700 6-axes Acc+Mag sensor Polling Demo\n\r");
    PRINTF("[4].FXOS8700 6-axes Acc+Mag sensor Interrupt Demo\n\r");
    PRINTF("[5].MPL3115 Pressure sensor Polling Demo\n\r");
    PRINTF("[6].MPL3115 Pressure sensor Interrupt Demo\n\r");

    while(1)
    {
        demoSel = GETCHAR();
        if ((demoSel >= '1') && (demoSel <= '6'))
            break;
    }

    switch(demoSel)
    {
        case '1':
            fxas21002Demo_Pol();
            break;
        case '2':
            fxas21002Demo_Int();
            break;
        case '3':
            fxos8700Demo_Pol();
            break;
        case '4':
            fxos8700Demo_Int();
            break;
        case '5':
            mpl3115Demo_Pol();
            break;
        case '6':
            mpl3115Demo_Int();
            break;
    }
}

int main(void)
{
    /* Initialize board specified hardware. */
    hardware_init();

    /* Create a the APP main task. */
    xTaskCreate(MainTask, "Main Task", configMINIMAL_STACK_SIZE + 100,
                NULL, tskIDLE_PRIORITY+1, NULL);

    /* Start FreeRTOS scheduler. */
    vTaskStartScheduler();

    /* should never reach this point. */
    while (true);
}

void BOARD_I2C_HANDLER(void)
{
    I2C_XFER_Handler(&I2C_handle);
}

void BOARD_GPIO_SENSOR_HANDLER(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    RDC_SEMAPHORE_Lock(BOARD_GPIO_SENSOR_RDC_PDAP);

    /* clear the interrupt status. */
    GPIO_ClearStatusFlag(BOARD_GPIO_SENSOR_CONFIG->base, BOARD_GPIO_SENSOR_CONFIG->pin);

    RDC_SEMAPHORE_Unlock(BOARD_GPIO_SENSOR_RDC_PDAP);

    /* Unlock the task to process the event. */
    xSemaphoreGiveFromISR(xSemaphore, &xHigherPriorityTaskWoken);

    /* Perform a context switch to wake the higher priority task. */
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
