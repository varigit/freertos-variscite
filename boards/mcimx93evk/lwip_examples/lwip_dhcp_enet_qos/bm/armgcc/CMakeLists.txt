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


project(lwip_dhcp_enet_qos_bm)

set(MCUX_BUILD_TYPES debug release)

set(MCUX_SDK_PROJECT_NAME lwip_dhcp_enet_qos_bm.elf)

if (NOT DEFINED SdkRootDirPath)
    SET(SdkRootDirPath ${ProjDirPath}/../../../../../..)
endif()

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../lwip_dhcp_bm.c"
"${ProjDirPath}/../lwipopts.h"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
"${ProjDirPath}/../board.c"
"${ProjDirPath}/../board.h"
"${ProjDirPath}/../clock_config.c"
"${ProjDirPath}/../clock_config.h"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${ProjDirPath}/..
)

set(CMAKE_MODULE_PATH
    ${SdkRootDirPath}/components/phy/device/phyrtl8211f
    ${SdkRootDirPath}/devices/MIMX9352/drivers
    ${SdkRootDirPath}/components/pcal6524
    ${SdkRootDirPath}/components/silicon_id
    ${SdkRootDirPath}/components/silicon_id/socs/imx93
    ${SdkRootDirPath}/middleware/lwip
    ${SdkRootDirPath}/components/phy
    ${SdkRootDirPath}/devices/MIMX9352
    ${SdkRootDirPath}/devices/MIMX9352/utilities
    ${SdkRootDirPath}/components/uart
    ${SdkRootDirPath}/components/serial_manager
    ${SdkRootDirPath}/components/lists
    ${SdkRootDirPath}/CMSIS/Core/Include
)

# include modules
include(driver_phy-device-rtl8211f_MIMX9352)

include(driver_lpi2c_MIMX9352)

include(driver_pcal6524_MIMX9352)

include(component_silicon_id_MIMX9352)

include(driver_common_MIMX9352)

include(component_silicon_id_imx93_MIMX9352)

include(driver_clock_MIMX9352)

include(middleware_lwip_enet_ethernetif_MIMX9352)

include(middleware_lwip_MIMX9352)

include(driver_phy-common_MIMX9352)

include(driver_enet_qos_MIMX9352)

include(device_MIMX9352_CMSIS_MIMX9352)

include(utility_debug_console_MIMX9352)

include(utility_assert_MIMX9352)

include(component_lpuart_adapter_MIMX9352)

include(component_serial_manager_MIMX9352)

include(component_lists_MIMX9352)

include(component_serial_manager_uart_MIMX9352)

include(driver_lpuart_MIMX9352)

include(device_MIMX9352_startup_MIMX9352)

include(driver_iomuxc_MIMX9352)

include(driver_rgpio_MIMX9352)

include(driver_cache_xcache_MIMX9352)

include(driver_sentinel_MIMX9352)

include(CMSIS_Include_core_cm_MIMX9352)

include(driver_memory_MIMX9352)

include(utilities_misc_utilities_MIMX9352)


IF(NOT DEFINED TARGET_LINK_SYSTEM_LIBRARIES)  
    SET(TARGET_LINK_SYSTEM_LIBRARIES "-lm -lc -lgcc -lnosys")  
ENDIF()  

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${TARGET_LINK_SYSTEM_LIBRARIES})

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)

ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY}
-Obinary ${EXECUTABLE_OUTPUT_PATH}/${MCUX_SDK_PROJECT_NAME} ${EXECUTABLE_OUTPUT_PATH}/sdk20-app.bin)

