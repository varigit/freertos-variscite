include_guard(GLOBAL)
message("middleware_multicore_rpmsg_lite component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/rpmsg_lite/lib/common/llist.c
    ${CMAKE_CURRENT_LIST_DIR}/rpmsg_lite/lib/rpmsg_lite/rpmsg_lite.c
    ${CMAKE_CURRENT_LIST_DIR}/rpmsg_lite/lib/rpmsg_lite/rpmsg_ns.c
    ${CMAKE_CURRENT_LIST_DIR}/rpmsg_lite/lib/virtio/virtqueue.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/rpmsg_lite/lib/include
)


#OR Logic component
if(CONFIG_USE_middleware_multicore_rpmsg_lite_freertos_MIMX8ML8)
     include(middleware_multicore_rpmsg_lite_freertos_MIMX8ML8)
endif()
if(CONFIG_USE_middleware_multicore_rpmsg_lite_bm_MIMX8ML8)
     include(middleware_multicore_rpmsg_lite_bm_MIMX8ML8)
endif()
if(NOT (CONFIG_USE_middleware_multicore_rpmsg_lite_freertos_MIMX8ML8 OR CONFIG_USE_middleware_multicore_rpmsg_lite_bm_MIMX8ML8))
    message(WARNING "Since middleware_multicore_rpmsg_lite_freertos_MIMX8ML8/middleware_multicore_rpmsg_lite_bm_MIMX8ML8 is not included at first or config in config.cmake file, use middleware_multicore_rpmsg_lite_bm_MIMX8ML8 by default.")
    include(middleware_multicore_rpmsg_lite_bm_MIMX8ML8)
endif()

