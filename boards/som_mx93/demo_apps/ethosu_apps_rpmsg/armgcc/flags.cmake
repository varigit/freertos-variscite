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
    -D__STARTUP_INITIALIZE_NONCACHEDATA \
    -mcpu=cortex-m33 \
    -Wall \
    -mthumb \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -ffreestanding \
    -fno-builtin \
    -mapcs \
    -std=gnu99 \
    ${FPU} \
")
SET(CMAKE_ASM_FLAGS_DEBUG " \
    ${CMAKE_ASM_FLAGS_DEBUG} \
    -DDEBUG \
    -D__STARTUP_CLEAR_BSS \
    -D__STARTUP_INITIALIZE_NONCACHEDATA \
    -mcpu=cortex-m33 \
    -Wall \
    -mthumb \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -ffreestanding \
    -fno-builtin \
    -mapcs \
    -std=gnu99 \
    ${FPU} \
")
SET(CMAKE_C_FLAGS_RELEASE " \
    ${CMAKE_C_FLAGS_RELEASE} \
    -DNDEBUG \
    -DCPU_MIMX9352DVVXM_cm33 \
    -DARM_MATH_CM33 \
    -D__FPU_PRESENT=1 \
    -DPRINTF_ADVANCED_ENABLE=1 \
    -DETHOSU_ARCH=u65 \
    -DETHOSU65=1 \
    -DTF_LITE_STATIC_MEMORY \
    -DMCUXPRESSO_SDK \
    -DCMSIS_NN \
    -DSDK_OS_FREE_RTOS \
    -DSERIAL_PORT_TYPE_UART=1 \
    -Os \
    -fno-strict-aliasing \
    -Wno-unused-function \
    -Wall \
    -Wno-maybe-uninitialized \
    -Wno-strict-aliasing \
    -mcpu=cortex-m33 \
    -mthumb \
    -MMD \
    -MP \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -mapcs \
    -std=gnu99 \
    ${FPU} \
    ${DEBUG_CONSOLE_CONFIG} \
")
SET(CMAKE_C_FLAGS_DEBUG " \
    ${CMAKE_C_FLAGS_DEBUG} \
    -DDEBUG \
    -DCPU_MIMX9352DVVXM_cm33 \
    -DARM_MATH_CM33 \
    -D__FPU_PRESENT=1 \
    -DPRINTF_ADVANCED_ENABLE=1 \
    -DETHOSU_ARCH=u65 \
    -DETHOSU65=1 \
    -DTF_LITE_STATIC_MEMORY \
    -DMCUXPRESSO_SDK \
    -DCMSIS_NN \
    -DSDK_OS_FREE_RTOS \
    -DSERIAL_PORT_TYPE_UART=1 \
    -O1 \
    -g \
    -fno-strict-aliasing \
    -Wno-unused-function \
    -Wall \
    -Wno-maybe-uninitialized \
    -Wno-strict-aliasing \
    -mcpu=cortex-m33 \
    -mthumb \
    -MMD \
    -MP \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -mapcs \
    -std=gnu99 \
    ${FPU} \
    ${DEBUG_CONSOLE_CONFIG} \
")
SET(CMAKE_CXX_FLAGS_RELEASE " \
    ${CMAKE_CXX_FLAGS_RELEASE} \
    -DNDEBUG \
    -DARM_MATH_CM33 \
    -D__FPU_PRESENT=1 \
    -DPRINTF_ADVANCED_ENABLE=1 \
    -DCPU_MIMX9352DVVXM_cm33 \
    -DETHOSU_ARCH=u65 \
    -DETHOSU65=1 \
    -DTF_LITE_STATIC_MEMORY \
    -DMCUXPRESSO_SDK \
    -DCMSIS_NN \
    -DSERIAL_PORT_TYPE_UART=1 \
    -Os \
    -Wall \
    -fno-rtti \
    -fno-exceptions \
    -Wno-maybe-uninitialized \
    -Wno-sign-compare \
    -Wno-strict-aliasing \
    -Wno-deprecated-declarations \
    -mcpu=cortex-m33 \
    -mthumb \
    -MMD \
    -MP \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -mapcs \
    ${FPU} \
    ${DEBUG_CONSOLE_CONFIG} \
")
SET(CMAKE_CXX_FLAGS_DEBUG " \
    ${CMAKE_CXX_FLAGS_DEBUG} \
    -DDEBUG \
    -DARM_MATH_CM33 \
    -D__FPU_PRESENT=1 \
    -DPRINTF_ADVANCED_ENABLE=1 \
    -DCPU_MIMX9352DVVXM_cm33 \
    -DETHOSU_ARCH=u65 \
    -DETHOSU65=1 \
    -DTF_LITE_STATIC_MEMORY \
    -DMCUXPRESSO_SDK \
    -DCMSIS_NN \
    -DSERIAL_PORT_TYPE_UART=1 \
    -O1 \
    -g \
    -Wall \
    -fno-rtti \
    -fno-exceptions \
    -Wno-maybe-uninitialized \
    -Wno-sign-compare \
    -Wno-strict-aliasing \
    -Wno-deprecated-declarations \
    -mcpu=cortex-m33 \
    -mthumb \
    -MMD \
    -MP \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -mapcs \
    ${FPU} \
    ${DEBUG_CONSOLE_CONFIG} \
")
SET(CMAKE_EXE_LINKER_FLAGS_RELEASE " \
    ${CMAKE_EXE_LINKER_FLAGS_RELEASE} \
    -Xlinker \
    --no-wchar-size-warning \
    -mcpu=cortex-m33 \
    -Wall \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
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
    -Wl,--print-memory-usage \
    -Xlinker \
    --defsym=__stack_size__=0x1000 \
    -Xlinker \
    --defsym=__heap_size__=0x2000 \
    ${FPU} \
    ${SPECS} \
    -T\"${ProjDirPath}/MIMX9352_cm33_ram.ld\" -static \
")
SET(CMAKE_EXE_LINKER_FLAGS_DEBUG " \
    ${CMAKE_EXE_LINKER_FLAGS_DEBUG} \
    -g \
    -Xlinker \
    --no-wchar-size-warning \
    -mcpu=cortex-m33 \
    -Wall \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
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
    -Wl,--print-memory-usage \
    -Xlinker \
    --defsym=__stack_size__=0x1000 \
    -Xlinker \
    --defsym=__heap_size__=0x2000 \
    ${FPU} \
    ${SPECS} \
    -T\"${ProjDirPath}/MIMX9352_cm33_ram.ld\" -static \
")
