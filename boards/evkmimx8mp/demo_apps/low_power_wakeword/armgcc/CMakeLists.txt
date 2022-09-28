# CROSS COMPILER SETTING
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED (VERSION 3.10.0)

# THE VERSION NUMBER
SET (Tutorial_VERSION_MAJOR 1)
SET (Tutorial_VERSION_MINOR 0)

# ENABLE ASM
ENABLE_LANGUAGE(ASM)

SET(CMAKE_STATIC_LIBRARY_PREFIX)
SET(CMAKE_STATIC_LIBRARY_SUFFIX)

SET(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
SET(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

# CURRENT DIRECTORY
SET(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})

SET(EXECUTABLE_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})
SET(LIBRARY_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})


project(low_power_wakeword)

set(MCUX_SDK_PROJECT_NAME low_power_wakeword.elf)

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../app_srtm.c"
"${ProjDirPath}/../app_srtm.h"
"${ProjDirPath}/../low_power_voice_common.c"
"${ProjDirPath}/../low_power_voice_common.h"
"${ProjDirPath}/../voice_engine_common.c"
"${ProjDirPath}/../voice_engine_common.h"
"${ProjDirPath}/../voice_engine_voiceseeker_voicespot.c"
"${ProjDirPath}/../lpm.c"
"${ProjDirPath}/../lpm.h"
"${ProjDirPath}/../FreeRTOSConfig.h"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
"${ProjDirPath}/../rpmsg_config.h"
"${ProjDirPath}/../rsc_table.c"
"${ProjDirPath}/../rsc_table.h"
"${ProjDirPath}/../remoteproc.h"
"${ProjDirPath}/../board.c"
"${ProjDirPath}/../board.h"
"${ProjDirPath}/../clock_config.c"
"${ProjDirPath}/../clock_config.h"
"${ProjDirPath}/../fsl_iomuxc.h"
"${ProjDirPath}/../empty_rsc_table.c"
"${ProjDirPath}/../../../../../components/srtm/channels/srtm_rpmsg_endpoint.h"
"${ProjDirPath}/../../../../../components/srtm/channels/srtm_rpmsg_endpoint.c"
"${ProjDirPath}/../../../../../components/srtm/services/srtm_audio_service.h"
"${ProjDirPath}/../../../../../components/srtm/services/srtm_audio_service.c"
"${ProjDirPath}/../../../../../components/srtm/services/srtm_sai_sdma_adapter.h"
"${ProjDirPath}/../../../../../components/srtm/services/srtm_sai_sdma_adapter.c"
"${ProjDirPath}/../../../../../components/srtm/services/srtm_pdm_sdma_adapter.h"
"${ProjDirPath}/../../../../../components/srtm/services/srtm_pdm_sdma_adapter.c"
"${ProjDirPath}/../../../../../components/srtm/services/srtm_i2c_service.h"
"${ProjDirPath}/../../../../../components/srtm/services/srtm_i2c_service.c"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${ProjDirPath}/..
    ${ProjDirPath}/../../../../../components/srtm/channels
    ${ProjDirPath}/../../../../../components/srtm/services
)

set(CMAKE_MODULE_PATH
    ${ProjDirPath}/../../../../../devices/MIMX8ML8/utilities/debug_console_lite
    ${ProjDirPath}/../../../../../middleware/voice_spot
    ${ProjDirPath}/../../../../../middleware/voice_seeker
    ${ProjDirPath}/../../../../../CMSIS/DSP
    ${ProjDirPath}/../../../../../devices/MIMX8ML8/drivers
    ${ProjDirPath}/../../../../../components/codec
    ${ProjDirPath}/../../../../../components/codec/i2c
    ${ProjDirPath}/../../../../../components/i2c
    ${ProjDirPath}/../../../../../middleware/multicore
    ${ProjDirPath}/../../../../../rtos/freertos/freertos_kernel
    ${ProjDirPath}/../../../../../devices/MIMX8ML8
    ${ProjDirPath}/../../../../../components/uart
    ${ProjDirPath}/../../../../../components/serial_manager
    ${ProjDirPath}/../../../../../components/lists
    ${ProjDirPath}/../../../../../CMSIS/Core/Include
    ${ProjDirPath}/../../../../../components/srtm/port
    ${ProjDirPath}/../../../../../components/srtm
    ${ProjDirPath}/../../../../../components/codec/wm8960
    ${ProjDirPath}/../../../../../devices/MIMX8ML8/utilities
)

# include modules
include(utility_debug_console_lite_MIMX8ML8)

include(utility_assert_lite_MIMX8ML8)

include(middleware_voice_spot_cm7_iMX8MP_MIMX8ML8)

include(middleware_voice_seeker_cm7_iMX8MP_MIMX8ML8)

include(CMSIS_DSP_Source_MIMX8ML8)

include(driver_igpio_MIMX8ML8)

include(driver_iuart_MIMX8ML8)

include(driver_gpc_2_MIMX8ML8)

include(driver_gpt_MIMX8ML8)

include(driver_codec_MIMX8ML8)

include(driver_common_MIMX8ML8)

include(component_codec_adapters_MIMX8ML8)

include(driver_pdm_sdma_MIMX8ML8)

include(component_codec_i2c_MIMX8ML8)

include(component_ii2c_adapter_MIMX8ML8)

include(component_wm8960_adapter_MIMX8ML8)

include(middleware_multicore_rpmsg_lite_imx8mp_m7_freertos_MIMX8ML8)

include(middleware_multicore_rpmsg_lite_MIMX8ML8)

include(middleware_multicore_rpmsg_lite_freertos_MIMX8ML8)

include(middleware_freertos-kernel_heap_4_MIMX8ML8)

include(driver_pdm_MIMX8ML8)

include(driver_clock_MIMX8ML8)

include(driver_rdc_MIMX8ML8)

include(driver_audiomix_MIMX8ML8)

include(device_MIMX8ML8_CMSIS_MIMX8ML8)

include(component_iuart_adapter_MIMX8ML8)

include(component_serial_manager_MIMX8ML8)

include(component_lists_MIMX8ML8)

include(component_serial_manager_uart_MIMX8ML8)

include(device_MIMX8ML8_startup_MIMX8ML8)

include(CMSIS_Include_core_cm_MIMX8ML8)

include(middleware_voice_spot_model_MIMX8ML8)

include(driver_sdma_MIMX8ML8)

include(driver_memory_MIMX8ML8)

include(driver_mu_MIMX8ML8)

include(driver_sai_MIMX8ML8)

include(driver_sai_sdma_MIMX8ML8)

include(driver_srtm_freertos_MIMX8ML8)

include(driver_srtm_MIMX8ML8)

include(middleware_freertos-kernel_MIMX8ML8)

include(middleware_freertos-kernel_extension_MIMX8ML8)

include(driver_ii2c_MIMX8ML8)

include(driver_wm8960_MIMX8ML8)

include(utilities_misc_utilities_MIMX8ML8)

include(device_MIMX8ML8_system_MIMX8ML8)


TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE m)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE c)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE gcc)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE nosys)

if(CMAKE_BUILD_TYPE STREQUAL release)
    target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${ProjDirPath}/../../../../../middleware/voice_spot/iMX8M_CortexM7/Lib/librdsp_libvoicespot.a)
endif(CMAKE_BUILD_TYPE STREQUAL release)

if(CMAKE_BUILD_TYPE STREQUAL release)
    target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${ProjDirPath}/../../../../../middleware/voice_seeker/iMX8M_CortexM7/lib/libVoiceSeekerLight_noAEC.a)
endif(CMAKE_BUILD_TYPE STREQUAL release)

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)

ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY}
-Obinary ${EXECUTABLE_OUTPUT_PATH}/${MCUX_SDK_PROJECT_NAME} ${EXECUTABLE_OUTPUT_PATH}/low_power_wakeword.bin)

