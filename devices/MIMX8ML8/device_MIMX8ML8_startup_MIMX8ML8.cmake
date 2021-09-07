include_guard(GLOBAL)
message("device_MIMX8ML8_startup component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/gcc/startup_MIMX8ML8_cm7.S
)


include(device_MIMX8ML8_system_MIMX8ML8)

