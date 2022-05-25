include_guard(GLOBAL)
message("driver_easrc_sdma component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_asrc_sdma.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_easrc_MIMX8MN6)

include(driver_sdma_MIMX8MN6)

include(driver_common_MIMX8MN6)

