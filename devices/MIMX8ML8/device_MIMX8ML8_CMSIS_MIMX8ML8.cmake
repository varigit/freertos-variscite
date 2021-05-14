if(NOT DEVICE_MIMX8ML8_CMSIS_MIMX8ML8_INCLUDED)
    
    set(DEVICE_MIMX8ML8_CMSIS_MIMX8ML8_INCLUDED true CACHE BOOL "device_MIMX8ML8_CMSIS component is included.")


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    include(CMSIS_Include_core_cm7_MIMX8ML8)

endif()
