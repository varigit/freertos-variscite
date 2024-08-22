# Copy variable into project config.cmake to use software component
#set.board.evkmimx8mm
#  # description: Board_project_template evkmimx8mm
#  set(CONFIG_USE_BOARD_Project_Template_evkmimx8mm true)

#set.device.MIMX8MM6
#  # description: Middleware baremetal
#  set(CONFIG_USE_middleware_baremetal true)

#  # description: Utilities which is needed for particular toolchain like the SBRK function required to address limitation between HEAP and STACK in GCC toolchain library.
#  set(CONFIG_USE_utilities_misc_utilities true)

#  # description: Driver phy-common
#  set(CONFIG_USE_driver_phy-common true)

#  # description: Driver srtm
#  set(CONFIG_USE_driver_srtm true)

#  # description: Devices_project_template MIMX8MM6
#  set(CONFIG_USE_DEVICES_Project_Template_MIMX8MM6 true)

#  # description: Device MIMX8MM6_cmsis
#  set(CONFIG_USE_device_MIMX8MM6_CMSIS true)

#  # description: Rte_device
#  set(CONFIG_USE_RTE_Device true)

#  # description: Clock Driver
#  set(CONFIG_USE_driver_clock true)

#  # description: ENET Driver
#  set(CONFIG_USE_driver_enet true)

#  # description: SDMA Driver
#  set(CONFIG_USE_driver_sdma true)

#  # description: Component serial_manager_uart
#  set(CONFIG_USE_component_serial_manager_uart true)

#  # description: Utility debug_console_lite
#  set(CONFIG_USE_utility_debug_console_lite true)

#  # description: ECSPI SDMA Driver
#  set(CONFIG_USE_driver_ecspi_sdma true)

#  # description: IUART SDMA Driver
#  set(CONFIG_USE_driver_iuart_sdma true)

#  # description: SAI SDMA Driver
#  set(CONFIG_USE_driver_sai_sdma true)

#  # description: IOMUXC Driver
#  set(CONFIG_USE_driver_iomuxc true)

#  # description: MEMORY Driver
#  set(CONFIG_USE_driver_memory true)

#  # description: Device MIMX8MM6_system
#  set(CONFIG_USE_device_MIMX8MM6_system true)

#  # description: Device MIMX8MM6_startup
#  set(CONFIG_USE_device_MIMX8MM6_startup true)

#  # description: Utility assert
#  set(CONFIG_USE_utility_assert true)

#  # description: Utility assert_lite
#  set(CONFIG_USE_utility_assert_lite true)

#  # description: Utility str
#  set(CONFIG_USE_utility_str true)

#  # description: Utility debug_console
#  set(CONFIG_USE_utility_debug_console true)

#  # description: ECSPI CMSIS Driver
#  set(CONFIG_USE_driver_cmsis_ecspi true)

#  # description: ENET CMSIS Driver
#  set(CONFIG_USE_driver_cmsis_enet true)

#  # description: I2C CMSIS Driver
#  set(CONFIG_USE_driver_cmsis_ii2c true)

#  # description: UART CMSIS Driver
#  set(CONFIG_USE_driver_cmsis_iuart true)

#  # description: Driver ak4497
#  set(CONFIG_USE_driver_ak4497 true)

#  # description: Driver codec
#  set(CONFIG_USE_driver_codec true)

#  # description: Component codec adapters for multi codec
#  set(CONFIG_USE_component_codec_adapters true)

#  # description: Component wm8524 adapter for single codec
#  set(CONFIG_USE_component_wm8524_adapter true)

#  # description: Component ak4497 adapter for single codec
#  set(CONFIG_USE_component_ak4497_adapter true)

#  # description: Component codec_i2c
#  set(CONFIG_USE_component_codec_i2c true)

#  # description: Component ii2c_adapter
#  set(CONFIG_USE_component_ii2c_adapter true)

#  # description: Component lists
#  set(CONFIG_USE_component_lists true)

#  # description: Driver phy-device-rtl8211f
#  set(CONFIG_USE_driver_phy-device-rtl8211f true)

#  # description: Driver phy-device-ar8031
#  set(CONFIG_USE_driver_phy-device-ar8031 true)

#  # description: Component serial_manager
#  set(CONFIG_USE_component_serial_manager true)

#  # description: Component serial_manager_virtual
#  set(CONFIG_USE_component_serial_manager_virtual true)

#  # description: Component serial_manager_swo
#  set(CONFIG_USE_component_serial_manager_swo true)

#  # description: Driver silicon_id imx8
#  set(CONFIG_USE_component_silicon_id_imx8 true)

#  # description: Driver silicon_id
#  set(CONFIG_USE_component_silicon_id true)

#  # description: Driver srtm freertos
#  set(CONFIG_USE_driver_srtm_freertos true)

#  # description: Component iuart_adapter
#  set(CONFIG_USE_component_iuart_adapter true)

#  # description: Driver wm8524
#  set(CONFIG_USE_driver_wm8524 true)

#  # description: COMMON Driver
#  set(CONFIG_USE_driver_common true)

#  # description: CACHE LMEM Driver
#  set(CONFIG_USE_driver_cache_lmem true)

#  # description: ECSPI Driver
#  set(CONFIG_USE_driver_ecspi true)

#  # description: ECSPI Freertos Driver
#  set(CONFIG_USE_driver_ecspi_freertos true)

#  # description: GPC Driver
#  set(CONFIG_USE_driver_gpc_2 true)

#  # description: GPT Driver
#  set(CONFIG_USE_driver_gpt true)

#  # description: GPIO Driver
#  set(CONFIG_USE_driver_igpio true)

#  # description: I2C Driver
#  set(CONFIG_USE_driver_ii2c true)

#  # description: I2C Freertos Driver
#  set(CONFIG_USE_driver_ii2c_freertos true)

#  # description: PWM Driver
#  set(CONFIG_USE_driver_ipwm true)

#  # description: IUART Driver
#  set(CONFIG_USE_driver_iuart true)

#  # description: IUART Freertos Driver
#  set(CONFIG_USE_driver_iuart_freertos true)

#  # description: MU Driver
#  set(CONFIG_USE_driver_mu true)

#  # description: PDM Driver
#  set(CONFIG_USE_driver_pdm true)

#  # description: PDM SDMA Driver
#  set(CONFIG_USE_driver_pdm_sdma true)

#  # description: RDC Driver
#  set(CONFIG_USE_driver_rdc true)

#  # description: RDC SEMA42 Driver
#  set(CONFIG_USE_driver_rdc_sema42 true)

#  # description: SAI Driver
#  set(CONFIG_USE_driver_sai true)

#  # description: SEMA4 Driver
#  set(CONFIG_USE_driver_sema4 true)

#  # description: TMU Driver
#  set(CONFIG_USE_driver_tmu_1 true)

#  # description: wdog01 Driver
#  set(CONFIG_USE_driver_wdog01 true)

#set.CMSIS
#  # description: CMSIS-CORE for Cortex-M, ARMv8-M, ARMv8.1-M
#  set(CONFIG_USE_CMSIS_Include_core_cm true)

#  # description: Access to #include Driver_USART.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_USART true)

#  # description: Access to #include Driver_CAN.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_CAN true)

#  # description: Access to #include Driver_ETH.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_Ethernet true)

#  # description: Access to #include Driver_ETH_MAC.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_Ethernet_MAC true)

#  # description: Access to #include Driver_ETH_PHY.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_Ethernet_PHY true)

#  # description: Access to #include Driver_Flash.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_Flash true)

#  # description: Access to #include Driver_I2C.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_I2C true)

#  # description: Access to #include Driver_MCI.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_MCI true)

#  # description: Access to #include Driver_NAND.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_NAND true)

#  # description: Access to #include Driver_SAI.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_SAI true)

#  # description: Access to #include Driver_SPI.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_SPI true)

#  # description: Access to #include Driver_USBD.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_USB_Device true)

#  # description: Access to #include Driver_USBH.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_USB_Host true)

#  # description: Access to #include Driver_WiFi.h file
#  set(CONFIG_USE_CMSIS_Driver_Include_WiFi true)

#  # description: Device interrupt controller interface
#  set(CONFIG_USE_CMSIS_Device_API_OSTick true)

#  # description: CMSIS-RTOS API for Cortex-M, SC000, and SC300
#  set(CONFIG_USE_CMSIS_Device_API_RTOS2 true)

#  # description: CMSIS-RTOS2 RTX5 for Cortex-M, SC000, C300 and Armv8-M (Library)
#  set(CONFIG_USE_CMSIS_RTOS2_Secure true)

#  # description: CMSIS-RTOS2 RTX5 for Armv8-M Non-Secure Domain (Library)
#  set(CONFIG_USE_CMSIS_RTOS2_NonSecure true)

#set.CMSIS_DSP_Lib
#  # description: CMSIS-DSP Library Header
#  set(CONFIG_USE_CMSIS_DSP_Include true)

#  # description: CMSIS-DSP Library
#  set(CONFIG_USE_CMSIS_DSP_Source true)

#  # description: CMSIS-NN Library
#  set(CONFIG_USE_CMSIS_NN_Source true)

#set.middleware.freertos-kernel
#  # description: FreeRTOS NXP extension
#  set(CONFIG_USE_middleware_freertos-kernel_extension true)

#  # description: Template configuration file to be edited by user. Provides also memory allocator (heap_x), change variant if needed.
#  set(CONFIG_USE_middleware_freertos-kernel_template true)

#  # description: FreeRTOS kernel
#  set(CONFIG_USE_middleware_freertos-kernel true)

#  # description: FreeRTOS heap 1
#  set(CONFIG_USE_middleware_freertos-kernel_heap_1 true)

#  # description: FreeRTOS heap 2
#  set(CONFIG_USE_middleware_freertos-kernel_heap_2 true)

#  # description: FreeRTOS heap 3
#  set(CONFIG_USE_middleware_freertos-kernel_heap_3 true)

#  # description: FreeRTOS heap 4
#  set(CONFIG_USE_middleware_freertos-kernel_heap_4 true)

#  # description: FreeRTOS heap 5
#  set(CONFIG_USE_middleware_freertos-kernel_heap_5 true)

#  # description: FreeRTOS MPU wrappers
#  set(CONFIG_USE_middleware_freertos-kernel_mpu_wrappers true)

#set.middleware.multicore
#  # description: Multicore SDK
#  set(CONFIG_USE_middleware_multicore true)

#  # description: remoteproc-load script
#  set(CONFIG_USE_middleware_multicore_remoteproc_loadscript true)

#  # description: RPMsg-Lite BM environment sources
#  set(CONFIG_USE_middleware_multicore_rpmsg_lite_bm true)

#  # description: RPMsg-Lite FreeRTOS environment sources
#  set(CONFIG_USE_middleware_multicore_rpmsg_lite_freertos true)

#  # description: RPMsg-Lite XOS environment layer sources
#  set(CONFIG_USE_middleware_multicore_rpmsg_lite_xos true)

#  # description: RPMsg-Lite Azure RTOS environment sources
#  set(CONFIG_USE_middleware_multicore_rpmsg_lite_azurertos true)

#  # description: RPMsg-Lite for evkmimx8mm baremetal application
#  set(CONFIG_USE_middleware_multicore_rpmsg_lite_imx8mm_m4_bm true)

#  # description: RPMsg-Lite for evkmimx8mm FreeRTOS application
#  set(CONFIG_USE_middleware_multicore_rpmsg_lite_imx8mm_m4_freertos true)

#  # description: RPMsg-Lite baremetal for evkmimx8mm board
#  set(CONFIG_USE_middleware_multicore_rpmsg_lite_bm_config true)

#  # description: RPMsg-Lite FreeRTOS for evkmimx8mm board
#  set(CONFIG_USE_middleware_multicore_rpmsg_lite_freertos_config true)

#  # description: RPMsg-Lite
#  set(CONFIG_USE_middleware_multicore_rpmsg_lite true)

#set.middleware.pkcs11
#  # description: Public Key Cryptography Standard #11 defines generic cryptographic token interface.
#  set(CONFIG_USE_middleware_pkcs11 true)

#set.middleware.tinycbor
#  # description: Concise Binary Object Representation (CBOR) Library
#  set(CONFIG_USE_middleware_tinycbor true)

#set.middleware.voice_spot
#  # description: Voice Spot Hey NXP model
#  set(CONFIG_USE_middleware_voice_spot_model true)

#  # description: Voice Spot library for Cortex M4
#  set(CONFIG_USE_middleware_voice_spot_cm4_iMX8MM true)

#set.middleware.corehttp
#  # description: Client implementation of the HTTP/1.1 specification for embedded devices.
#  set(CONFIG_USE_middleware_freertos_corehttp true)

#set.middleware.llhttp
#  # description: HTTP parser in LLVM IR
#  set(CONFIG_USE_middleware_llhttp true)

#set.middleware.voice_seeker
#  # description: Voice seeker library for Cortex M4
#  set(CONFIG_USE_middleware_voice_seeker_cm4 true)

#  # description: Voice seeker memory utilities for Cortex M4
#  set(CONFIG_USE_middleware_voice_seeker_rdsp_utilities_public_cm4 true)

#set.middleware.rtcesl
#  # description: Real Time Control Embedded Software Library for CM4F core
#  set(CONFIG_USE_middleware_rtcesl_cm4fAllLibs true)

list(APPEND CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
  ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
  ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver
  ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/NN
  ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/RTOS2
  ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/RTOS2/Include
  ${CMAKE_CURRENT_LIST_DIR}/../../boards/evkmimx8mm/project_template
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/ak4497
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8524
  ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
  ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
  ${CMAKE_CURRENT_LIST_DIR}/../../components/phy
  ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phyar8031
  ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phyrtl8211f
  ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
  ${CMAKE_CURRENT_LIST_DIR}/../../components/silicon_id
  ${CMAKE_CURRENT_LIST_DIR}/../../components/silicon_id/socs/imx8
  ${CMAKE_CURRENT_LIST_DIR}/../../components/srtm
  ${CMAKE_CURRENT_LIST_DIR}/../../components/srtm/port
  ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
  ${CMAKE_CURRENT_LIST_DIR}/../../middleware/bm
  ${CMAKE_CURRENT_LIST_DIR}/../../middleware/llhttp
  ${CMAKE_CURRENT_LIST_DIR}/../../middleware/multicore
  ${CMAKE_CURRENT_LIST_DIR}/../../middleware/pkcs11
  ${CMAKE_CURRENT_LIST_DIR}/../../middleware/rtcesl
  ${CMAKE_CURRENT_LIST_DIR}/../../middleware/tinycbor
  ${CMAKE_CURRENT_LIST_DIR}/../../middleware/voice_seeker/ARM_CortexM4
  ${CMAKE_CURRENT_LIST_DIR}/../../middleware/voice_seeker/ARM_CortexM4/rdsp_utilities_public
  ${CMAKE_CURRENT_LIST_DIR}/../../middleware/voice_spot
  ${CMAKE_CURRENT_LIST_DIR}/../../rtos/freertos/corehttp
  ${CMAKE_CURRENT_LIST_DIR}/../../rtos/freertos/freertos-kernel
  ${CMAKE_CURRENT_LIST_DIR}/cmsis_drivers
  ${CMAKE_CURRENT_LIST_DIR}/drivers
  ${CMAKE_CURRENT_LIST_DIR}/project_template
  ${CMAKE_CURRENT_LIST_DIR}/template
  ${CMAKE_CURRENT_LIST_DIR}/utilities
  ${CMAKE_CURRENT_LIST_DIR}/utilities/debug_console_lite
)

include_if_use(BOARD_Project_Template_evkmimx8mm)
include_if_use(CMSIS_DSP_Include)
include_if_use(CMSIS_DSP_Source)
include_if_use(CMSIS_Device_API_OSTick)
include_if_use(CMSIS_Device_API_RTOS2)
include_if_use(CMSIS_Driver_Include_CAN)
include_if_use(CMSIS_Driver_Include_Ethernet)
include_if_use(CMSIS_Driver_Include_Ethernet_MAC)
include_if_use(CMSIS_Driver_Include_Ethernet_PHY)
include_if_use(CMSIS_Driver_Include_Flash)
include_if_use(CMSIS_Driver_Include_I2C)
include_if_use(CMSIS_Driver_Include_MCI)
include_if_use(CMSIS_Driver_Include_NAND)
include_if_use(CMSIS_Driver_Include_SAI)
include_if_use(CMSIS_Driver_Include_SPI)
include_if_use(CMSIS_Driver_Include_USART)
include_if_use(CMSIS_Driver_Include_USB_Device)
include_if_use(CMSIS_Driver_Include_USB_Host)
include_if_use(CMSIS_Driver_Include_WiFi)
include_if_use(CMSIS_Include_core_cm)
include_if_use(CMSIS_NN_Source)
include_if_use(CMSIS_RTOS2_NonSecure)
include_if_use(CMSIS_RTOS2_Secure)
include_if_use(DEVICES_Project_Template_MIMX8MM6.MIMX8MM6)
include_if_use(RTE_Device.MIMX8MM6)
include_if_use(component_ak4497_adapter.MIMX8MM6)
include_if_use(component_codec_adapters.MIMX8MM6)
include_if_use(component_codec_i2c.MIMX8MM6)
include_if_use(component_ii2c_adapter.MIMX8MM6)
include_if_use(component_iuart_adapter.MIMX8MM6)
include_if_use(component_lists.MIMX8MM6)
include_if_use(component_serial_manager.MIMX8MM6)
include_if_use(component_serial_manager_swo.MIMX8MM6)
include_if_use(component_serial_manager_uart.MIMX8MM6)
include_if_use(component_serial_manager_virtual.MIMX8MM6)
include_if_use(component_silicon_id.MIMX8MM6)
include_if_use(component_silicon_id_imx8.MIMX8MM6)
include_if_use(component_wm8524_adapter.MIMX8MM6)
include_if_use(device_MIMX8MM6_CMSIS.MIMX8MM6)
include_if_use(device_MIMX8MM6_startup.MIMX8MM6)
include_if_use(device_MIMX8MM6_system.MIMX8MM6)
include_if_use(driver_ak4497.MIMX8MM6)
include_if_use(driver_cache_lmem.MIMX8MM6)
include_if_use(driver_clock.MIMX8MM6)
include_if_use(driver_cmsis_ecspi.MIMX8MM6)
include_if_use(driver_cmsis_enet.MIMX8MM6)
include_if_use(driver_cmsis_ii2c.MIMX8MM6)
include_if_use(driver_cmsis_iuart.MIMX8MM6)
include_if_use(driver_codec.MIMX8MM6)
include_if_use(driver_common.MIMX8MM6)
include_if_use(driver_ecspi.MIMX8MM6)
include_if_use(driver_ecspi_freertos.MIMX8MM6)
include_if_use(driver_ecspi_sdma.MIMX8MM6)
include_if_use(driver_enet.MIMX8MM6)
include_if_use(driver_gpc_2.MIMX8MM6)
include_if_use(driver_gpt.MIMX8MM6)
include_if_use(driver_igpio.MIMX8MM6)
include_if_use(driver_ii2c.MIMX8MM6)
include_if_use(driver_ii2c_freertos.MIMX8MM6)
include_if_use(driver_iomuxc.MIMX8MM6)
include_if_use(driver_ipwm.MIMX8MM6)
include_if_use(driver_iuart.MIMX8MM6)
include_if_use(driver_iuart_freertos.MIMX8MM6)
include_if_use(driver_iuart_sdma.MIMX8MM6)
include_if_use(driver_memory.MIMX8MM6)
include_if_use(driver_mu.MIMX8MM6)
include_if_use(driver_pdm.MIMX8MM6)
include_if_use(driver_pdm_sdma.MIMX8MM6)
include_if_use(driver_phy-common.MIMX8MM6)
include_if_use(driver_phy-device-ar8031.MIMX8MM6)
include_if_use(driver_phy-device-rtl8211f.MIMX8MM6)
include_if_use(driver_rdc.MIMX8MM6)
include_if_use(driver_rdc_sema42.MIMX8MM6)
include_if_use(driver_sai.MIMX8MM6)
include_if_use(driver_sai_sdma.MIMX8MM6)
include_if_use(driver_sdma.MIMX8MM6)
include_if_use(driver_sema4.MIMX8MM6)
include_if_use(driver_srtm.MIMX8MM6)
include_if_use(driver_srtm_freertos.MIMX8MM6)
include_if_use(driver_tmu_1.MIMX8MM6)
include_if_use(driver_wdog01.MIMX8MM6)
include_if_use(driver_wm8524.MIMX8MM6)
include_if_use(middleware_baremetal.MIMX8MM6)
include_if_use(middleware_freertos-kernel)
include_if_use(middleware_freertos-kernel_extension)
include_if_use(middleware_freertos-kernel_heap_1)
include_if_use(middleware_freertos-kernel_heap_2)
include_if_use(middleware_freertos-kernel_heap_3)
include_if_use(middleware_freertos-kernel_heap_4)
include_if_use(middleware_freertos-kernel_heap_5)
include_if_use(middleware_freertos-kernel_mpu_wrappers)
include_if_use(middleware_freertos-kernel_template)
include_if_use(middleware_freertos_corehttp)
include_if_use(middleware_llhttp)
include_if_use(middleware_multicore)
include_if_use(middleware_multicore_remoteproc_loadscript)
include_if_use(middleware_multicore_rpmsg_lite)
include_if_use(middleware_multicore_rpmsg_lite_azurertos)
include_if_use(middleware_multicore_rpmsg_lite_bm)
include_if_use(middleware_multicore_rpmsg_lite_bm_config)
include_if_use(middleware_multicore_rpmsg_lite_freertos)
include_if_use(middleware_multicore_rpmsg_lite_freertos_config)
include_if_use(middleware_multicore_rpmsg_lite_imx8mm_m4_bm)
include_if_use(middleware_multicore_rpmsg_lite_imx8mm_m4_freertos)
include_if_use(middleware_multicore_rpmsg_lite_xos)
include_if_use(middleware_pkcs11)
include_if_use(middleware_rtcesl_cm4fAllLibs)
include_if_use(middleware_tinycbor)
include_if_use(middleware_voice_seeker_cm4)
include_if_use(middleware_voice_seeker_rdsp_utilities_public_cm4)
include_if_use(middleware_voice_spot_cm4_iMX8MM)
include_if_use(middleware_voice_spot_model)
include_if_use(utilities_misc_utilities.MIMX8MM6)
include_if_use(utility_assert.MIMX8MM6)
include_if_use(utility_assert_lite.MIMX8MM6)
include_if_use(utility_debug_console.MIMX8MM6)
include_if_use(utility_debug_console_lite.MIMX8MM6)
include_if_use(utility_str.MIMX8MM6)
