include_guard()
message("utility_debug_console_lite component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/str/fsl_str.c
    ${CMAKE_CURRENT_LIST_DIR}/debug_console_lite/fsl_debug_console.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/str
    ${CMAKE_CURRENT_LIST_DIR}/debug_console_lite
)


include(component_iuart_adapter_MIMX8ML8)

include(driver_common_MIMX8ML8)

