include_guard(GLOBAL)
message("driver_cmsis_iuart component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_uart_cmsis.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_iuart_MIMX8MM6)

include(CMSIS_Driver_Include_USART_MIMX8MM6)

include(driver_iuart_sdma_MIMX8MM6)

