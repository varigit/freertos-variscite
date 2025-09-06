# Add set(CONFIG_USE_device_startup true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

      if(CONFIG_TOOLCHAIN STREQUAL iar)
          add_config_file(${CMAKE_CURRENT_LIST_DIR}/iar/startup_MIMX9596_cm7.s "" device_startup.MIMX9596)
        endif()

        if(CONFIG_TOOLCHAIN STREQUAL armgcc)
          add_config_file(${CMAKE_CURRENT_LIST_DIR}/gcc/startup_MIMX9596_cm7.S "" device_startup.MIMX9596)
        endif()

  

