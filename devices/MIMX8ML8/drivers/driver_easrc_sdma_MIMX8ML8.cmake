include_guard()
message("driver_easrc_sdma component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_asrc_sdma.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_easrc_MIMX8ML8)

include(driver_sdma_MIMX8ML8)

include(driver_common_MIMX8ML8)

