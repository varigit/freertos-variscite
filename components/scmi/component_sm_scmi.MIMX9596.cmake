# Add set(CONFIG_USE_component_sm_scmi true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

      target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
          ${CMAKE_CURRENT_LIST_DIR}/scmi.c
          ${CMAKE_CURRENT_LIST_DIR}/scmi_clock.c
          ${CMAKE_CURRENT_LIST_DIR}/scmi_base.c
          ${CMAKE_CURRENT_LIST_DIR}/scmi_bbm.c
          ${CMAKE_CURRENT_LIST_DIR}/scmi_cpu.c
          ${CMAKE_CURRENT_LIST_DIR}/scmi_fusa.c
          ${CMAKE_CURRENT_LIST_DIR}/scmi_lmm.c
          ${CMAKE_CURRENT_LIST_DIR}/scmi_misc.c
          ${CMAKE_CURRENT_LIST_DIR}/scmi_perf.c
          ${CMAKE_CURRENT_LIST_DIR}/scmi_pinctrl.c
          ${CMAKE_CURRENT_LIST_DIR}/scmi_power.c
          ${CMAKE_CURRENT_LIST_DIR}/scmi_reset.c
          ${CMAKE_CURRENT_LIST_DIR}/scmi_sensor.c
          ${CMAKE_CURRENT_LIST_DIR}/scmi_sys.c
          ${CMAKE_CURRENT_LIST_DIR}/scmi_voltage.c
        )

  
      target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
          ${CMAKE_CURRENT_LIST_DIR}/.
        )

  
