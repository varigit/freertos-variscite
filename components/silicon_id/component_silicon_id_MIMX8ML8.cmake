include_guard()
message("component_silicon_id component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_silicon_id.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


#OR Logic component
if(CONFIG_USE_driver_common_MIMX8ML8)
     include(driver_common_MIMX8ML8)
endif()
if(CONFIG_USE_component_silicon_id_rt10xx_MIMX8ML8)
     include(component_silicon_id_rt10xx_MIMX8ML8)
endif()
if(CONFIG_USE_driver_common_MIMX8ML8)
     include(driver_common_MIMX8ML8)
endif()
if(CONFIG_USE_component_silicon_id_imx8_MIMX8ML8)
     include(component_silicon_id_imx8_MIMX8ML8)
endif()
if(CONFIG_USE_driver_common_MIMX8ML8)
     include(driver_common_MIMX8ML8)
endif()
if(CONFIG_USE_component_silicon_id_rt1170_MIMX8ML8)
     include(component_silicon_id_rt1170_MIMX8ML8)
endif()
if(CONFIG_USE_driver_common_MIMX8ML8)
     include(driver_common_MIMX8ML8)
endif()
if(CONFIG_USE_component_silicon_id_rt1180_MIMX8ML8)
     include(component_silicon_id_rt1180_MIMX8ML8)
endif()
if(CONFIG_USE_driver_common_MIMX8ML8)
     include(driver_common_MIMX8ML8)
endif()
if(CONFIG_USE_component_silicon_id_scfw_MIMX8ML8)
     include(component_silicon_id_scfw_MIMX8ML8)
endif()
if(CONFIG_USE_driver_common_MIMX8ML8)
     include(driver_common_MIMX8ML8)
endif()
if(CONFIG_USE_component_silicon_id_rw610_MIMX8ML8)
     include(component_silicon_id_rw610_MIMX8ML8)
endif()
if(NOT (CONFIG_USE_driver_common_MIMX8ML8 OR CONFIG_USE_component_silicon_id_rt10xx_MIMX8ML8 OR CONFIG_USE_driver_common_MIMX8ML8 OR CONFIG_USE_component_silicon_id_imx8_MIMX8ML8 OR CONFIG_USE_driver_common_MIMX8ML8 OR CONFIG_USE_component_silicon_id_rt1170_MIMX8ML8 OR CONFIG_USE_driver_common_MIMX8ML8 OR CONFIG_USE_component_silicon_id_rt1180_MIMX8ML8 OR CONFIG_USE_driver_common_MIMX8ML8 OR CONFIG_USE_component_silicon_id_scfw_MIMX8ML8 OR CONFIG_USE_driver_common_MIMX8ML8 OR CONFIG_USE_component_silicon_id_rw610_MIMX8ML8))
    message(WARNING "Since driver_common_MIMX8ML8/component_silicon_id_rt10xx_MIMX8ML8/component_silicon_id_imx8_MIMX8ML8/component_silicon_id_rt1170_MIMX8ML8/component_silicon_id_rt1180_MIMX8ML8/component_silicon_id_scfw_MIMX8ML8/component_silicon_id_rw610_MIMX8ML8 is not included at first or config in config.cmake file, use driver_sim_MIMX8ML8/component_silicon_id_kinetis_device_support_MIMX8ML8 by default.")
    include(driver_sim_MIMX8ML8)
    include(component_silicon_id_kinetis_device_support_MIMX8ML8)
endif()

