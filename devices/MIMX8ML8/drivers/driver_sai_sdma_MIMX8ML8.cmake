if(NOT DRIVER_SAI_SDMA_MIMX8ML8_INCLUDED)
    
    set(DRIVER_SAI_SDMA_MIMX8ML8_INCLUDED true CACHE BOOL "driver_sai_sdma component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_sai_sdma.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_sai_MIMX8ML8)

    include(driver_sdma_MIMX8ML8)

endif()
