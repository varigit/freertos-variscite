include_guard()
message("middleware_voice_seeker_cm4_iMX8MM component is included.")


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/iMX8M_CortexM4/include
)

