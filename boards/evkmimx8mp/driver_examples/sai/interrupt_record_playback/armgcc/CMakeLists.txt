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


project(sai_interrupt_record_playback)

set(MCUX_SDK_PROJECT_NAME sai_interrupt_record_playback.elf)

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../sai_interrupt_record_playback.c"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
"${ProjDirPath}/../board.c"
"${ProjDirPath}/../board.h"
"${ProjDirPath}/../clock_config.c"
"${ProjDirPath}/../clock_config.h"
"${ProjDirPath}/../fsl_iomuxc.h"
"${ProjDirPath}/../empty_rsc_table.c"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${ProjDirPath}/..
)

set(CMAKE_MODULE_PATH
    ${ProjDirPath}/../../../../../../components/codec/wm8960
    ${ProjDirPath}/../../../../../../devices/MIMX8ML8/drivers
    ${ProjDirPath}/../../../../../../components/codec
    ${ProjDirPath}/../../../../../../components/codec/i2c
    ${ProjDirPath}/../../../../../../components/i2c
    ${ProjDirPath}/../../../../../../devices/MIMX8ML8/utilities/debug_console_lite
    ${ProjDirPath}/../../../../../../devices/MIMX8ML8
    ${ProjDirPath}/../../../../../../components/uart
    ${ProjDirPath}/../../../../../../components/lists
    ${ProjDirPath}/../../../../../../CMSIS/Core/Include
    ${ProjDirPath}/../../../../../../devices/MIMX8ML8/utilities
)

# include modules
include(driver_wm8960_MIMX8ML8)

include(driver_igpio_MIMX8ML8)

include(driver_codec_MIMX8ML8)

include(driver_common_MIMX8ML8)

include(component_wm8960_adapter_MIMX8ML8)

include(driver_ii2c_MIMX8ML8)

include(component_codec_i2c_MIMX8ML8)

include(component_ii2c_adapter_MIMX8ML8)

include(utility_debug_console_lite_MIMX8ML8)

include(utility_assert_lite_MIMX8ML8)

include(driver_clock_MIMX8ML8)

include(driver_sai_MIMX8ML8)

include(driver_rdc_MIMX8ML8)

include(driver_audiomix_MIMX8ML8)

include(device_MIMX8ML8_CMSIS_MIMX8ML8)

include(component_iuart_adapter_MIMX8ML8)

include(component_lists_MIMX8ML8)

include(driver_iuart_MIMX8ML8)

include(device_MIMX8ML8_startup_MIMX8ML8)

include(CMSIS_Include_core_cm_MIMX8ML8)

include(utilities_misc_utilities_MIMX8ML8)

include(device_MIMX8ML8_system_MIMX8ML8)


TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE m)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE c)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE gcc)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE nosys)

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)

ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY}
-Obinary ${EXECUTABLE_OUTPUT_PATH}/${MCUX_SDK_PROJECT_NAME} ${EXECUTABLE_OUTPUT_PATH}/sai_interrupt_record_playback.bin)

