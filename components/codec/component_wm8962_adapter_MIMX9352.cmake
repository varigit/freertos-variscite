include_guard()
message("component_wm8962_adapter component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/port/wm8962/fsl_codec_wm8962_adapter.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/port/wm8962
    ${CMAKE_CURRENT_LIST_DIR}/port
)


include(driver_wm8962_MIMX9352)

include(driver_codec_MIMX9352)

