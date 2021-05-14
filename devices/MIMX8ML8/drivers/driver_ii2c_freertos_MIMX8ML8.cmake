if(NOT DRIVER_II2C_FREERTOS_MIMX8ML8_INCLUDED)
    
    set(DRIVER_II2C_FREERTOS_MIMX8ML8_INCLUDED true CACHE BOOL "driver_ii2c_freertos component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_i2c_freertos.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_ii2c_MIMX8ML8)

    include(middleware_freertos-kernel_MIMX8ML8)

endif()
