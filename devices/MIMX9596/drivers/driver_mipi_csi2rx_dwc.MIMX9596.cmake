# Add set(CONFIG_USE_driver_mipi_csi2rx_dwc true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

      target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
          ${CMAKE_CURRENT_LIST_DIR}/fsl_dwc_mipi_csi2rx.c
          ${CMAKE_CURRENT_LIST_DIR}/fsl_dwc_mipi_dphy.c
        )

  
      target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
          ${CMAKE_CURRENT_LIST_DIR}/.
        )

  
