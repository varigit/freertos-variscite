include_guard(GLOBAL)
message("driver_codec component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_codec_common.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


#OR Logic component
if(CONFIG_USE_component_wm8904_adapter_MIMX8MM6)
     include(component_wm8904_adapter_MIMX8MM6)
endif()
if(CONFIG_USE_component_wm8960_adapter_MIMX8MM6)
     include(component_wm8960_adapter_MIMX8MM6)
endif()
if(CONFIG_USE_component_wm8524_adapter_MIMX8MM6)
     include(component_wm8524_adapter_MIMX8MM6)
endif()
if(CONFIG_USE_component_sgtl_adapter_MIMX8MM6)
     include(component_sgtl_adapter_MIMX8MM6)
endif()
if(CONFIG_USE_component_da7212_adapter_MIMX8MM6)
     include(component_da7212_adapter_MIMX8MM6)
endif()
if(CONFIG_USE_component_ak4497_adapter_MIMX8MM6)
     include(component_ak4497_adapter_MIMX8MM6)
endif()
if(CONFIG_USE_component_tfa9xxx_adapter_MIMX8MM6)
     include(component_tfa9xxx_adapter_MIMX8MM6)
endif()
if(CONFIG_USE_component_tfa9896_adapter_MIMX8MM6)
     include(component_tfa9896_adapter_MIMX8MM6)
endif()
if(CONFIG_USE_component_cs42888_adapter_MIMX8MM6)
     include(component_cs42888_adapter_MIMX8MM6)
endif()
if(CONFIG_USE_component_cs42448_adapter_MIMX8MM6)
     include(component_cs42448_adapter_MIMX8MM6)
endif()
if(CONFIG_USE_component_codec_adapters_MIMX8MM6)
     include(component_codec_adapters_MIMX8MM6)
endif()
if(NOT (CONFIG_USE_component_wm8904_adapter_MIMX8MM6 OR CONFIG_USE_component_wm8960_adapter_MIMX8MM6 OR CONFIG_USE_component_wm8524_adapter_MIMX8MM6 OR CONFIG_USE_component_sgtl_adapter_MIMX8MM6 OR CONFIG_USE_component_da7212_adapter_MIMX8MM6 OR CONFIG_USE_component_ak4497_adapter_MIMX8MM6 OR CONFIG_USE_component_tfa9xxx_adapter_MIMX8MM6 OR CONFIG_USE_component_tfa9896_adapter_MIMX8MM6 OR CONFIG_USE_component_cs42888_adapter_MIMX8MM6 OR CONFIG_USE_component_cs42448_adapter_MIMX8MM6 OR CONFIG_USE_component_codec_adapters_MIMX8MM6))
    message(WARNING "Since component_wm8904_adapter_MIMX8MM6/component_wm8960_adapter_MIMX8MM6/component_wm8524_adapter_MIMX8MM6/component_sgtl_adapter_MIMX8MM6/component_da7212_adapter_MIMX8MM6/component_ak4497_adapter_MIMX8MM6/component_tfa9xxx_adapter_MIMX8MM6/component_tfa9896_adapter_MIMX8MM6/component_cs42888_adapter_MIMX8MM6/component_cs42448_adapter_MIMX8MM6/component_codec_adapters_MIMX8MM6 is not included at first or config in config.cmake file, use component_wm8904_adapter_MIMX8MM6 by default.")
    include(component_wm8904_adapter_MIMX8MM6)
endif()

include(driver_common_MIMX8MM6)

