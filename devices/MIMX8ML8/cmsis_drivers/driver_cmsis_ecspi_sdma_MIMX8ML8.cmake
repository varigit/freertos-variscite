if(NOT DRIVER_CMSIS_ECSPI_SDMA_MIMX8ML8_INCLUDED)
    
    set(DRIVER_CMSIS_ECSPI_SDMA_MIMX8ML8_INCLUDED true CACHE BOOL "driver_cmsis_ecspi_sdma component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_ecspi_cmsis.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_ecspi_sdma_MIMX8ML8)

    include(CMSIS_Driver_Include_SPI_MIMX8ML8)

endif()
