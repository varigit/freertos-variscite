include_guard(GLOBAL)
message("driver_ecspi_sdma component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_ecspi_sdma.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_ecspi_MIMX8ML8)

include(driver_sdma_MIMX8ML8)

