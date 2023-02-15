include_guard()
message("middleware_voice_seeker_cm4 component is included.")


target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/ARM_CortexM4/include
)

include(middleware_voice_seeker_rdsp_utilities_public_MIMX8MM6)

