if(NOT DRIVER_TMU_2_MIMX8ML8_INCLUDED)
    
    set(DRIVER_TMU_2_MIMX8ML8_INCLUDED true CACHE BOOL "driver_tmu_2 component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_tmu.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common_MIMX8ML8)

endif()
