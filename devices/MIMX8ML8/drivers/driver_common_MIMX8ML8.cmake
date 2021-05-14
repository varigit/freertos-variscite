if(NOT DRIVER_COMMON_MIMX8ML8_INCLUDED)
    
    set(DRIVER_COMMON_MIMX8ML8_INCLUDED true CACHE BOOL "driver_common component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_common.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_clock_MIMX8ML8)

    include(device_MIMX8ML8_CMSIS_MIMX8ML8)

endif()
