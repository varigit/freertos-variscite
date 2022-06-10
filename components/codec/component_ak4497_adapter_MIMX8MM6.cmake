include_guard(GLOBAL)
message("component_ak4497_adapter component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/port/ak4497/fsl_codec_ak4497_adapter.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/port/ak4497
    ${CMAKE_CURRENT_LIST_DIR}/port
)


include(driver_ak4497_MIMX8MM6)

include(driver_codec_MIMX8MM6)

