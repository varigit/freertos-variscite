# Add set(CONFIG_USE_BOARD_Project_Template_evkmimx8mm true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_BOARD STREQUAL evkmimx8mm))

add_config_file(${CMAKE_CURRENT_LIST_DIR}/board.h "" BOARD_Project_Template_evkmimx8mm)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/board.c "" BOARD_Project_Template_evkmimx8mm)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/clock_config.h ${CMAKE_CURRENT_LIST_DIR}/. BOARD_Project_Template_evkmimx8mm)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/clock_config.c "" BOARD_Project_Template_evkmimx8mm)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/pin_mux.h ${CMAKE_CURRENT_LIST_DIR}/. BOARD_Project_Template_evkmimx8mm)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/pin_mux.c "" BOARD_Project_Template_evkmimx8mm)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/peripherals.h ${CMAKE_CURRENT_LIST_DIR}/. BOARD_Project_Template_evkmimx8mm)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/peripherals.c "" BOARD_Project_Template_evkmimx8mm)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
)

else()

message(SEND_ERROR "BOARD_Project_Template_evkmimx8mm dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
