# Add set(CONFIG_USE_middleware_voice_seeker_rdsp_utilities_public_cm33 true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_CORE STREQUAL cm33) AND (CONFIG_BOARD STREQUAL mcimx93autoevk OR CONFIG_BOARD STREQUAL mcimx93evk OR CONFIG_BOARD STREQUAL mcimx93qsb))

if((CONFIG_TOOLCHAIN STREQUAL armgcc OR CONFIG_TOOLCHAIN STREQUAL mcux))
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/rdsp_memory_utils_public/RdspMemoryUtilsPublic.c
      ${CMAKE_CURRENT_LIST_DIR}/rdsp_memory_utils_public/memcheck.c
  )
endif()

if((CONFIG_TOOLCHAIN STREQUAL armgcc OR CONFIG_TOOLCHAIN STREQUAL mcux))
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include
  ${CMAKE_CURRENT_LIST_DIR}/rdsp_memory_utils_public
)
endif()

else()

message(SEND_ERROR "middleware_voice_seeker_rdsp_utilities_public_cm33 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
