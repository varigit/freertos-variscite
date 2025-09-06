IF(NOT DEFINED FPU)  
    SET(FPU "-mfloat-abi=hard -mfpu=fpv5-d16")  
ENDIF()  

IF(NOT DEFINED SPECS)  
    SET(SPECS "--specs=nano.specs --specs=nosys.specs")  
ENDIF()  

IF(NOT DEFINED DEBUG_CONSOLE_CONFIG)  
    SET(DEBUG_CONSOLE_CONFIG "-DSDK_DEBUGCONSOLE=1")  
ENDIF()  

SET(CMAKE_ASM_FLAGS_RELEASE " \
    ${CMAKE_ASM_FLAGS_RELEASE} \
    -D__STARTUP_INITIALIZE_NONCACHEDATA \
    -D__STARTUP_CLEAR_BSS \
    -DNO_CRP \
    -DMCUXPRESSO_SDK \
    -DCPU_MIMX9596AVZXN_cm7 \
    -DMIMX9596_cm7_SERIES \
    -mthumb \
    -mcpu=cortex-m7 \
    ${FPU} \
")
SET(CMAKE_C_FLAGS_RELEASE " \
    ${CMAKE_C_FLAGS_RELEASE} \
    -include ${ProjDirPath}/../mcux_config.h \
    -DNDEBUG \
    -D__STARTUP_CLEAR_BSS \
    -DSRTM_DEBUG_MESSAGE_FUNC=DbgConsole_Printf \
    -DSRTM_DEBUG_VERBOSE_LEVEL=SRTM_DEBUG_VERBOSE_WARN \
    -DNOT_CONFIG_CLK_ROOT=1 \
    -DVOICE_ENGINE_CONFIG_VOICESEEKER_2MIC=1 \
    -DSRTM_PDM_EDMA_DATA_INJECTION=1 \
    -DSRTM_SAI_EDMA_CONFIG_RX_ENABLE=0 \
    -DSRTM_PDM_EDMA_ADAPTER_USE_HWVAD=0 \
    -DBOARD_USE_PCAL6408=1 \
    -DBOARD_USE_PCA6416A \
    -DUSE_SRTM_PDM_EDMA \
    -DFSL_EDMA_DRIVER_EDMA4 \
    -DSDK_I2C_BASED_COMPONENT_USED=1 \
    -DSRTM_AUDIO_SERVICE_USED=1 \
    -DSRTM_SAI_EDMA_PLAY_HALT_WORKAROUND=1 \
    -DSRTM_SAI_EDMA_CLOCK_SWITCH_ENABLE=1 \
    -DDEMO_SAI_TX_CONFIG_StopOnSuspend=1 \
    -DDEMO_SAI_TX_CONFIG_UseLocalBuf=0 \
    -DSRTM_SAI_CONFIG_Rx_Enabled=0 \
    -DSRTM_SAI_CONFIG_SupportLocalBuf=0 \
    -DMCUX_META_BUILD \
    -DMCUXPRESSO_SDK \
    -DFSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL=1 \
    -DCPU_MIMX9596AVZXN_cm7 \
    -DMIMX9596_cm7_SERIES \
    -DDISABLEFLOAT16 \
    -DCODEC_MULTI_ADAPTERS=1 \
    -DCODEC_WM8962_ENABLE \
    -DSDK_OS_FREE_RTOS \
    -Os \
    -Wall \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -fno-builtin \
    -mthumb \
    -mapcs \
    -std=gnu99 \
    -mcpu=cortex-m7 \
    ${FPU} \
    ${DEBUG_CONSOLE_CONFIG} \
")
SET(CMAKE_CXX_FLAGS_RELEASE " \
    ${CMAKE_CXX_FLAGS_RELEASE} \
    -DNDEBUG \
    -DMCUX_META_BUILD \
    -DMCUXPRESSO_SDK \
    -DCPU_MIMX9596AVZXN_cm7 \
    -DMIMX9596_cm7_SERIES \
    -DSDK_OS_FREE_RTOS \
    -Os \
    -Wall \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -fno-builtin \
    -mthumb \
    -mapcs \
    -fno-rtti \
    -fno-exceptions \
    -mcpu=cortex-m7 \
    ${FPU} \
    ${DEBUG_CONSOLE_CONFIG} \
")
SET(CMAKE_EXE_LINKER_FLAGS_RELEASE " \
    ${CMAKE_EXE_LINKER_FLAGS_RELEASE} \
    -Xlinker \
    --defsym=__stack_size__=0x0080 \
    -Xlinker \
    --defsym=__heap_size__=0x12C00 \
    -Xlinker \
    -Map=output.map \
    -Wall \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -fno-builtin \
    -mthumb \
    -mapcs \
    -Wl,--gc-sections \
    -Wl,-static \
    -Wl,--print-memory-usage \
    -mcpu=cortex-m7 \
    ${FPU} \
    ${SPECS} \
    -T\"${ProjDirPath}/MIMX9596_cm7_lpv_ram.ld\" -static \
")
