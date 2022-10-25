include_guard()
message("middleware_lpvad_cm4 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/i.MX8MMini_CM4/ExApp/VIT_helper.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/i.MX8MMini_CM4/Lib
    ${CMAKE_CURRENT_LIST_DIR}/i.MX8MMini_CM4/Lib/Inc
    ${CMAKE_CURRENT_LIST_DIR}/i.MX8MMini_CM4/ExApp
)


