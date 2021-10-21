include_guard(GLOBAL)
message("device_MIMX8MN6_startup component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/gcc/startup_MIMX8MN6_cm7.S
)


include(device_MIMX8MN6_system_MIMX8MN6)

