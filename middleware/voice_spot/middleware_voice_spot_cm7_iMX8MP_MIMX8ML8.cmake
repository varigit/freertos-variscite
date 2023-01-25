include_guard()
message("middleware_voice_spot_cm7_iMX8MP component is included.")


target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/iMX8M_CortexM7/Lib/include
)

include(middleware_voice_spot_model_MIMX8ML8)

