# config to select component, the format is CONFIG_USE_${component}
# Please refer to cmake files below to get available components:
#  ${SdkRootDirPath}/devices/MIMX9352/all_lib_device.cmake

set(CONFIG_COMPILER gcc)
set(CONFIG_TOOLCHAIN armgcc)
set(CONFIG_USE_COMPONENT_CONFIGURATION false)
set(CONFIG_USE_driver_phy-device-rtl8211f true)
set(CONFIG_USE_middleware_freertos-kernel_cm33_non_trustzone true)
set(CONFIG_USE_driver_lpi2c true)
set(CONFIG_USE_driver_enet true)
set(CONFIG_USE_middleware_lwip_kinetis_ethernetif true)
set(CONFIG_USE_middleware_lwip true)
set(CONFIG_USE_component_silicon_id_imx93 true)
set(CONFIG_USE_component_silicon_id true)
set(CONFIG_USE_driver_clock true)
set(CONFIG_USE_middleware_freertos-kernel_heap_3 true)
set(CONFIG_USE_driver_common true)
set(CONFIG_USE_device_MIMX9352_CMSIS true)
set(CONFIG_USE_utility_debug_console true)
set(CONFIG_USE_utility_assert true)
set(CONFIG_USE_component_lpuart_adapter true)
set(CONFIG_USE_component_serial_manager_uart true)
set(CONFIG_USE_component_serial_manager true)
set(CONFIG_USE_driver_lpuart true)
set(CONFIG_USE_component_lists true)
set(CONFIG_USE_device_MIMX9352_startup true)
set(CONFIG_USE_driver_iomuxc true)
set(CONFIG_USE_driver_rgpio true)
set(CONFIG_USE_driver_cache_xcache true)
set(CONFIG_USE_driver_sentinel true)
set(CONFIG_USE_driver_adp5585 true)
set(CONFIG_USE_driver_pcal6524 true)
set(CONFIG_USE_utilities_misc_utilities true)
set(CONFIG_USE_driver_phy-common true)
set(CONFIG_USE_middleware_freertos-kernel true)
set(CONFIG_USE_middleware_freertos-kernel_template true)
set(CONFIG_USE_middleware_freertos-kernel_extension true)
set(CONFIG_USE_driver_memory true)
set(CONFIG_USE_middleware_lwip_template true)
set(CONFIG_USE_component_rgpio_adapter true)
set(CONFIG_USE_CMSIS_Include_core_cm true)
set(CONFIG_CORE cm33)
set(CONFIG_DEVICE MIMX9352)
set(CONFIG_BOARD mcimx93evk)
set(CONFIG_KIT mcimx93evk)
set(CONFIG_DEVICE_ID MIMX9352xxxxM)
set(CONFIG_FPU SP_FPU)
set(CONFIG_DSP DSP)
