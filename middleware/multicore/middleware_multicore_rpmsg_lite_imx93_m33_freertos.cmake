# Add set(CONFIG_USE_middleware_multicore_rpmsg_lite_imx93_m33_freertos true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_BOARD STREQUAL mcimx93evk OR CONFIG_BOARD STREQUAL mcimx93qsb OR CONFIG_BOARD STREQUAL mcimx93autoevk) AND CONFIG_USE_middleware_freertos-kernel AND CONFIG_USE_middleware_freertos-kernel_heap_4)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/rpmsg_lite/lib/rpmsg_lite/porting/platform/imx93_m33/rpmsg_platform.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/rpmsg_lite/lib/include/platform/imx93_m33
)

else()

message(SEND_ERROR "middleware_multicore_rpmsg_lite_imx93_m33_freertos dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
