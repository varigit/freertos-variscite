if(NOT DEVICE_MIMX8ML8_SYSTEM_MIMX8ML8_INCLUDED)
    
    set(DEVICE_MIMX8ML8_SYSTEM_MIMX8ML8_INCLUDED true CACHE BOOL "device_MIMX8ML8_system component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/system_MIMX8ML8_cm7.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(device_MIMX8ML8_CMSIS_MIMX8ML8)

endif()
