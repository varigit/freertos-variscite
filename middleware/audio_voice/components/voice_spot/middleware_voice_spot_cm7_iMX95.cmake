# Add set(CONFIG_USE_middleware_voice_spot_cm7_iMX95 true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

      if(CONFIG_TOOLCHAIN STREQUAL armgcc)
    target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
          ${CMAKE_CURRENT_LIST_DIR}/i.MX95_CortexM7/lib/include
        )
    endif()

  
      if(CONFIG_TOOLCHAIN STREQUAL armgcc)
    target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE
    -Wl,--start-group
          ${CMAKE_CURRENT_LIST_DIR}/i.MX95_CortexM7/lib/libvoicespot.a
        -Wl,--end-group
    )
    endif()

  