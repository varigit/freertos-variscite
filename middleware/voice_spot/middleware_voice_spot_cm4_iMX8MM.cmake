# Add set(CONFIG_USE_middleware_voice_spot_cm4_iMX8MM true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_BOARD STREQUAL evkmimx8mm) AND CONFIG_USE_middleware_voice_spot_model)

if(CONFIG_TOOLCHAIN STREQUAL armgcc)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/ARM_CortexM4/lib/include
)
endif()

if(CONFIG_TOOLCHAIN STREQUAL armgcc)
  target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE
    -Wl,--start-group
      ${CMAKE_CURRENT_LIST_DIR}/ARM_CortexM4/lib/libvoicespot.a
      -Wl,--end-group
  )
endif()

else()

message(SEND_ERROR "middleware_voice_spot_cm4_iMX8MM dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
