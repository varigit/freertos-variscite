# Add set(CONFIG_USE_middleware_voice_seeker_cm33 true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_BOARD STREQUAL mcimx93autoevk OR CONFIG_BOARD STREQUAL mcimx93evk OR CONFIG_BOARD STREQUAL mcimx93qsb) AND CONFIG_USE_middleware_voice_seeker_rdsp_utilities_public_cm33)

if((CONFIG_TOOLCHAIN STREQUAL armgcc OR CONFIG_TOOLCHAIN STREQUAL mcux))
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include
)
endif()

if((CONFIG_TOOLCHAIN STREQUAL armgcc OR CONFIG_TOOLCHAIN STREQUAL mcux))
  target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE
    -Wl,--start-group
      ${CMAKE_CURRENT_LIST_DIR}/lib/libvoiceseeker_no_aec.a
      -Wl,--end-group
  )
endif()

else()

message(SEND_ERROR "middleware_voice_seeker_cm33 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
