include_guard(GLOBAL)
message("driver_cmsis_ecspi component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_ecspi_cmsis.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_ecspi_MIMX8ML8)

include(CMSIS_Driver_Include_SPI_MIMX8ML8)

include(driver_ecspi_sdma_MIMX8ML8)

