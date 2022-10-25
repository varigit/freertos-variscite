include_guard()
message("middleware_multicore_rpmsg_lite_imx8mm_m4_freertos component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/rpmsg_lite/lib/rpmsg_lite/porting/platform/imx8mm_m4/rpmsg_platform.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/rpmsg_lite/lib/include/platform/imx8mm_m4
)


include(middleware_freertos-kernel_MIMX8MM6)

include(middleware_freertos-kernel_heap_4_MIMX8MM6)

