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


project(cmsis_lpi2c_int_b2b_transfer_slave)

set(MCUX_BUILD_TYPES debug release)

set(MCUX_SDK_PROJECT_NAME cmsis_lpi2c_int_b2b_transfer_slave.elf)

if (NOT DEFINED SdkRootDirPath)
    SET(SdkRootDirPath ${ProjDirPath}/../../../../../../..)
endif()

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../cmsis_lpi2c_int_b2b_transfer_slave.c"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
"${ProjDirPath}/../RTE_Device.h"
"${ProjDirPath}/../board.c"
"${ProjDirPath}/../board.h"
"${ProjDirPath}/../clock_config.c"
"${ProjDirPath}/../clock_config.h"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${ProjDirPath}/..
)

set(CMAKE_MODULE_PATH
    ${SdkRootDirPath}/devices/MIMX9352/utilities
    ${SdkRootDirPath}/devices/MIMX9352/utilities/debug_console_lite
    ${SdkRootDirPath}/devices/MIMX9352/drivers
    ${SdkRootDirPath}/devices/MIMX9352/cmsis_drivers
    ${SdkRootDirPath}/devices/MIMX9352
    ${SdkRootDirPath}/components/uart
    ${SdkRootDirPath}/components/lists
    ${SdkRootDirPath}/CMSIS/Core/Include
    ${SdkRootDirPath}/devices/MIMX9352/drivers/dma3
    ${SdkRootDirPath}/CMSIS/Driver/Include
)

# include modules
include(utility_debug_console_lite_MIMX9352)

include(utility_assert_lite_MIMX9352)

include(driver_clock_MIMX9352)

include(driver_lpi2c_MIMX9352)

include(driver_lpi2c_edma_MIMX9352)

include(driver_cmsis_lpi2c_MIMX9352)

include(driver_common_MIMX9352)

include(device_MIMX9352_CMSIS_MIMX9352)

include(component_lpuart_adapter_MIMX9352)

include(component_lists_MIMX9352)

include(driver_lpuart_MIMX9352)

include(device_MIMX9352_startup_MIMX9352)

include(driver_iomuxc_MIMX9352)

include(driver_rgpio_MIMX9352)

include(driver_cache_xcache_MIMX9352)

include(driver_sentinel_MIMX9352)

include(CMSIS_Include_core_cm_MIMX9352)

include(driver_dma3_MIMX9352)

include(driver_memory_MIMX9352)

include(CMSIS_Driver_Include_I2C_MIMX9352)

include(CMSIS_Driver_Include_Common_MIMX9352)

include(utilities_misc_utilities_MIMX9352)


IF(NOT DEFINED TARGET_LINK_SYSTEM_LIBRARIES)  
    SET(TARGET_LINK_SYSTEM_LIBRARIES "-lm -lc -lgcc -lnosys")  
ENDIF()  

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${TARGET_LINK_SYSTEM_LIBRARIES})

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)

ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY}
-Obinary ${EXECUTABLE_OUTPUT_PATH}/${MCUX_SDK_PROJECT_NAME} ${EXECUTABLE_OUTPUT_PATH}/sdk20-app.bin)

