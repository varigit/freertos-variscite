# Add set(CONFIG_USE_middleware_voice_spot_cm33 true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_BOARD STREQUAL mcimx93autoevk OR CONFIG_BOARD STREQUAL mcimx93evk OR CONFIG_BOARD STREQUAL mcimx93qsb) AND CONFIG_USE_middleware_voice_spot_model)

if(CONFIG_TOOLCHAIN STREQUAL armgcc)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/ARM_CortexM33/lib/include
  ${CMAKE_CURRENT_LIST_DIR}/ARM_CortexM33/rdsp_utilities_public/include
)
endif()

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  if(CONFIG_TOOLCHAIN STREQUAL armgcc)
    target_compile_options(${MCUX_SDK_PROJECT_NAME} PUBLIC
    )
  endif()

endif()

if(CONFIG_TOOLCHAIN STREQUAL armgcc)
  target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE
    -Wl,--start-group
      ${CMAKE_CURRENT_LIST_DIR}/ARM_CortexM33/lib/libvoicespot.a
      -Wl,--end-group
  )
endif()

else()

message(SEND_ERROR "middleware_voice_spot_cm33 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
