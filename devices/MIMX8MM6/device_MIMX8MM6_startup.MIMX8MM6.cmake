# Add set(CONFIG_USE_device_MIMX8MM6_startup true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_device_MIMX8MM6_system)

if(CONFIG_TOOLCHAIN STREQUAL iar)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/iar/startup_MIMX8MM6_cm4.s "" device_MIMX8MM6_startup.MIMX8MM6)
endif()

if(CONFIG_TOOLCHAIN STREQUAL armgcc)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/gcc/startup_MIMX8MM6_cm4.S "" device_MIMX8MM6_startup.MIMX8MM6)
endif()

if(CONFIG_TOOLCHAIN STREQUAL mdk)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/arm/startup_MIMX8MM6_cm4.S "" device_MIMX8MM6_startup.MIMX8MM6)
endif()

if(CONFIG_TOOLCHAIN STREQUAL mcux)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/mcuxpresso/startup_MIMX8MM6_cm4.c "" device_MIMX8MM6_startup.MIMX8MM6)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/mcuxpresso/startup_MIMX8MM6_cm4.cpp "" device_MIMX8MM6_startup.MIMX8MM6)
endif()

else()

message(SEND_ERROR "device_MIMX8MM6_startup.MIMX8MM6 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
