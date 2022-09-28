include_guard()
message("middleware_voice_seeker_cm7_iMX8MP component is included.")


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/iMX8M_CortexM7/include
)

