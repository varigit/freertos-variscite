# Add set(CONFIG_USE_middleware_freertos-kernel_template true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_CORE STREQUAL cm33 AND CONFIG_FPU STREQUAL SP_FPU AND (CONFIG_DEVICE_ID STREQUAL MIMX9311xxxxM OR CONFIG_DEVICE_ID STREQUAL MIMX9312xxxxM OR CONFIG_DEVICE_ID STREQUAL MIMX9321xxxxM OR CONFIG_DEVICE_ID STREQUAL MIMX9322xxxxM OR CONFIG_DEVICE_ID STREQUAL MIMX9331xxxxM OR CONFIG_DEVICE_ID STREQUAL MIMX9332xxxxM OR CONFIG_DEVICE_ID STREQUAL MIMX9351xxxxM OR CONFIG_DEVICE_ID STREQUAL MIMX9352xxxxM))
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/template/ARM_CM33_3_priority_bits/FreeRTOSConfig.h ${CMAKE_CURRENT_LIST_DIR}/template/ARM_CM33_3_priority_bits middleware_freertos-kernel_template)
endif()
