include_guard(GLOBAL)
message("device_MIMX8MN6_system component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/system_MIMX8MN6_cm7.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(device_MIMX8MN6_CMSIS_MIMX8MN6)

