# Add set(CONFIG_USE_middleware_multicore_remoteproc_empty_rsc_table true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

      target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
          ${CMAKE_CURRENT_LIST_DIR}/remoteproc/empty_rsc_table.c
        )

  

