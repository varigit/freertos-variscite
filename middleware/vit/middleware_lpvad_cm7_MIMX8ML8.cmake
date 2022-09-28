include_guard()
message("middleware_lpvad_cm7 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/i.MX8MPlus_CM7/ExApp/VIT_helper.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/i.MX8MPlus_CM7/Lib
    ${CMAKE_CURRENT_LIST_DIR}/i.MX8MPlus_CM7/Lib/Inc
    ${CMAKE_CURRENT_LIST_DIR}/i.MX8MPlus_CM7/ExApp
)


