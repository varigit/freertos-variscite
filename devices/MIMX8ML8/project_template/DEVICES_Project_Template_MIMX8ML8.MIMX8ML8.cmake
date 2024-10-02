# Add set(CONFIG_USE_DEVICES_Project_Template_MIMX8ML8 true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_DEVICE_ID STREQUAL MIMX8ML8xxxLZ OR CONFIG_DEVICE_ID STREQUAL MIMX8ML8xxxKZ) AND CONFIG_USE_device_MIMX8ML8_CMSIS AND CONFIG_USE_device_MIMX8ML8_startup AND CONFIG_USE_driver_audiomix AND CONFIG_USE_driver_clock AND CONFIG_USE_driver_common AND CONFIG_USE_driver_iuart AND CONFIG_USE_driver_rdc AND ((CONFIG_USE_utility_assert AND CONFIG_USE_utility_debug_console) OR (CONFIG_USE_utility_assert_lite AND CONFIG_USE_utility_debug_console_lite)))

add_config_file(${CMAKE_CURRENT_LIST_DIR}/board.h "" DEVICES_Project_Template_MIMX8ML8.MIMX8ML8)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/board.c "" DEVICES_Project_Template_MIMX8ML8.MIMX8ML8)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/clock_config.h "" DEVICES_Project_Template_MIMX8ML8.MIMX8ML8)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/clock_config.c "" DEVICES_Project_Template_MIMX8ML8.MIMX8ML8)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/pin_mux.h "" DEVICES_Project_Template_MIMX8ML8.MIMX8ML8)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/pin_mux.c "" DEVICES_Project_Template_MIMX8ML8.MIMX8ML8)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/peripherals.h "" DEVICES_Project_Template_MIMX8ML8.MIMX8ML8)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/peripherals.c "" DEVICES_Project_Template_MIMX8ML8.MIMX8ML8)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
)

else()

message(SEND_ERROR "DEVICES_Project_Template_MIMX8ML8.MIMX8ML8 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
