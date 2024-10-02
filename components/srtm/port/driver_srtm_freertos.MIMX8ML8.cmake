# Add set(CONFIG_USE_driver_srtm_freertos true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_driver_srtm)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/srtm_heap_freertos.c
  ${CMAKE_CURRENT_LIST_DIR}/srtm_mutex_freertos.c
  ${CMAKE_CURRENT_LIST_DIR}/srtm_sem_freertos.c
)

else()

message(SEND_ERROR "driver_srtm_freertos.MIMX8ML8 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
