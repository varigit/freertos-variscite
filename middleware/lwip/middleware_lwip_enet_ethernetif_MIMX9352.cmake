include_guard()
message("middleware_lwip_enet_ethernetif component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/port/enet_ethernetif.c
    ${CMAKE_CURRENT_LIST_DIR}/port/ethernetif.c
    ${CMAKE_CURRENT_LIST_DIR}/port/ethernetif_mmac.c
)

if(CONFIG_USE_driver_enet_MIMX9352)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/port/enet_ethernetif_kinetis.c
)
elseif(CONFIG_USE_driver_lpc_enet_MIMX9352)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/port/enet_ethernetif_lpc.c
)
elseif(CONFIG_USE_driver_enet_qos_MIMX9352)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/port/enet_ethernetif_qos.c
)
endif()


target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/port
)


#OR Logic component
if(CONFIG_USE_driver_enet_MIMX9352)
     include(driver_enet_MIMX9352)
endif()
if(CONFIG_USE_middleware_lwip_enet_ethernetif_mcx_port_MIMX9352)
     include(middleware_lwip_enet_ethernetif_mcx_port_MIMX9352)
endif()
if(CONFIG_USE_driver_enet_qos_MIMX9352)
     include(driver_enet_qos_MIMX9352)
endif()
if(NOT (CONFIG_USE_driver_enet_MIMX9352 OR CONFIG_USE_middleware_lwip_enet_ethernetif_mcx_port_MIMX9352 OR CONFIG_USE_driver_enet_qos_MIMX9352))
    message(WARNING "Since driver_enet_MIMX9352/middleware_lwip_enet_ethernetif_mcx_port_MIMX9352/driver_enet_qos_MIMX9352 is not included at first or config in config.cmake file, use driver_enet_MIMX9352 by default.")
    include(driver_enet_MIMX9352)
endif()

include(middleware_lwip_MIMX9352)

include(driver_phy-common_MIMX9352)

