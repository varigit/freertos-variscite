IF(NOT DEFINED FPU)  
    SET(FPU "-mfloat-abi=hard -mfpu=fpv5-sp-d16")  
ENDIF()  

IF(NOT DEFINED SPECS)  
    SET(SPECS "--specs=nano.specs --specs=nosys.specs")  
ENDIF()  

IF(NOT DEFINED DEBUG_CONSOLE_CONFIG)  
    SET(DEBUG_CONSOLE_CONFIG "-DSDK_DEBUGCONSOLE=1")  
ENDIF()  

SET(CMAKE_ASM_FLAGS_RELEASE " \
    ${CMAKE_ASM_FLAGS_RELEASE} \
    -DNDEBUG \
    -D__STARTUP_CLEAR_BSS \
    -DNO_CRP \
    -D__PERFORMANCE_IMPLEMENTATION \
    -D__STARTUP_INITIALIZE_NONCACHEDATA \
    -mcpu=cortex-m7 \
    -mthumb \
    ${FPU} \
")
SET(CMAKE_C_FLAGS_RELEASE " \
    ${CMAKE_C_FLAGS_RELEASE} \
    -DNDEBUG \
    -DSRTM_PDM_SDMA_ADAPTER_USE_HWVAD=0 \
    -DSRTM_PDM_SDMA_ADAPTER_FORCE_LOCAL_AND_EXTRA_BUFFERS=1 \
    -DDEMO_SAI_TX_CONFIG_StopOnSuspend=1 \
    -DDEMO_SAI_TX_CONFIG_UseLocalBuf=0 \
    -DSRTM_SINGLE_SDMA_MULTI_FIFO_SCRIPT=1 \
    -DSRTM_SAI_CONFIG_Rx_Enabled=0 \
    -DSRTM_SAI_CONFIG_SupportLocalBuf=0 \
    -DCPU_MIMX8ML8DVNLZ \
    -DCPU_MIMX8ML8DVNLZ_cm7 \
    -DSRTM_DEBUG_MESSAGE_FUNC=DbgConsole_Printf \
    -DSRTM_DEBUG_VERBOSE_LEVEL=SRTM_DEBUG_VERBOSE_WARN \
    -DNOT_CONFIG_CLK_ROOT=1 \
    -DDISABLEFLOAT16 \
    -DSDK_I2C_BASED_COMPONENT_USED=1 \
    -DCODEC_MULTI_ADAPTERS=1 \
    -DSERIAL_PORT_TYPE_UART=1 \
    -DSDK_OS_FREE_RTOS \
    -DBOARD_USE_CODEC=1 \
    -DCODEC_WM8960_ENABLE \
    -DMCUXPRESSO_SDK \
    -Os \
    -mcpu=cortex-m7 \
    -Wall \
    -Wno-address-of-packed-member \
    -mthumb \
    -MMD \
    -MP \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -ffreestanding \
    -fno-builtin \
    -mapcs \
    -std=gnu99 \
    ${FPU} \
    ${DEBUG_CONSOLE_CONFIG} \
")
SET(CMAKE_CXX_FLAGS_RELEASE " \
    ${CMAKE_CXX_FLAGS_RELEASE} \
    -DNDEBUG \
    -DCPU_MIMX8ML8DVNLZ \
    -DCPU_MIMX8ML8DVNLZ_cm7 \
    -DSERIAL_PORT_TYPE_UART=1 \
    -DMCUXPRESSO_SDK \
    -Os \
    -mcpu=cortex-m7 \
    -Wall \
    -Wno-address-of-packed-member \
    -mthumb \
    -MMD \
    -MP \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -ffreestanding \
    -fno-builtin \
    -mapcs \
    -fno-rtti \
    -fno-exceptions \
    ${FPU} \
    ${DEBUG_CONSOLE_CONFIG} \
")
SET(CMAKE_EXE_LINKER_FLAGS_RELEASE " \
    ${CMAKE_EXE_LINKER_FLAGS_RELEASE} \
    -mcpu=cortex-m7 \
    -Wall \
    -Wl,--print-memory-usage \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -ffreestanding \
    -fno-builtin \
    -mthumb \
    -mapcs \
    -Xlinker \
    --gc-sections \
    -Xlinker \
    -static \
    -Xlinker \
    -z \
    -Xlinker \
    muldefs \
    -Xlinker \
    -Map=output.map \
    -Xlinker \
    --defsym=__stack_size__=0x0080 \
    -Xlinker \
    --defsym=__heap_size__=0x13000 \
    ${FPU} \
    ${SPECS} \
    -T${ProjDirPath}/MIMX8ML8xxxxx_cm7_lpv_ram.ld -static \
")
