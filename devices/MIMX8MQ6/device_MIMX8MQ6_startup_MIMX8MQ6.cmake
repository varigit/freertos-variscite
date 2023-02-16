include_guard()
message("device_MIMX8MQ6_startup component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/gcc/startup_MIMX8MQ6_cm4.S
)


include(device_MIMX8MQ6_system_MIMX8MQ6)

