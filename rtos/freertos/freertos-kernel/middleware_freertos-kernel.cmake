# Add set(CONFIG_USE_middleware_freertos-kernel true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_middleware_freertos-kernel_template AND CONFIG_USE_middleware_freertos-kernel_extension)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/croutine.c
  ${CMAKE_CURRENT_LIST_DIR}/event_groups.c
  ${CMAKE_CURRENT_LIST_DIR}/list.c
  ${CMAKE_CURRENT_LIST_DIR}/queue.c
  ${CMAKE_CURRENT_LIST_DIR}/stream_buffer.c
  ${CMAKE_CURRENT_LIST_DIR}/tasks.c
  ${CMAKE_CURRENT_LIST_DIR}/timers.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DSDK_OS_FREE_RTOS
  )

endif()

else()

message(SEND_ERROR "middleware_freertos-kernel dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
