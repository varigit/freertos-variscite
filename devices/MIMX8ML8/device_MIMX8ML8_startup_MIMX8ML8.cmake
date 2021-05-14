if(NOT DEVICE_MIMX8ML8_STARTUP_MIMX8ML8_INCLUDED)
    
    set(DEVICE_MIMX8ML8_STARTUP_MIMX8ML8_INCLUDED true CACHE BOOL "device_MIMX8ML8_startup component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/gcc/startup_MIMX8ML8_cm7.S
    )


    include(device_MIMX8ML8_system_MIMX8ML8)

endif()
