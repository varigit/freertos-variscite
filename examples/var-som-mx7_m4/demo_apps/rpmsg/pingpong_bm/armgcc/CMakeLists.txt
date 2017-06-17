INCLUDE(CMakeForceCompiler)

# CROSS COMPILER SETTING
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

# THE VERSION NUMBER
SET (Tutorial_VERSION_MAJOR 1)
SET (Tutorial_VERSION_MINOR 0)

# ENABLE ASM
ENABLE_LANGUAGE(ASM)

SET(CMAKE_STATIC_LIBRARY_PREFIX)
SET(CMAKE_STATIC_LIBRARY_SUFFIX)

SET(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
SET(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

 
# CURRENT DIRECTORY
SET(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})

# DEBUG LINK FILE
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -T${ProjDirPath}/../../../../../../platform/devices/MCIMX7D/linker/gcc/MCIMX7D_M4_tcm.ld  -static")

# RELEASE LINK FILE
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -T${ProjDirPath}/../../../../../../platform/devices/MCIMX7D/linker/gcc/MCIMX7D_M4_tcm.ld  -static")

# DEBUG ASM FLAGS
SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -g  -mcpu=cortex-m4  -mfloat-abi=hard  -mfpu=fpv4-sp-d16  -mthumb  -Wall  -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -mapcs  -std=gnu99")

# DEBUG C FLAGS
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g  -O0  -fno-strict-aliasing  -mcpu=cortex-m4  -mfloat-abi=hard  -mfpu=fpv4-sp-d16  -mthumb  -MMD  -MP  -Wall  -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -mapcs  -std=gnu99")

# DEBUG LD FLAGS
SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -g  -mcpu=cortex-m4  -mfloat-abi=hard  -mfpu=fpv4-sp-d16  --specs=nano.specs  -lm  -Wall  -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -Os  -mthumb  -mapcs  -Xlinker --gc-sections  -Xlinker -static  -Xlinker -z  -Xlinker muldefs  -Xlinker --defsym=__stack_size__=0x400  -Xlinker --defsym=__heap_size__=0x4000")

# RELEASE ASM FLAGS
SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -mcpu=cortex-m4  -mfloat-abi=hard  -mfpu=fpv4-sp-d16  -mthumb  -Wall  -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -mapcs  -std=gnu99")

# RELEASE C FLAGS
SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Os  -fno-strict-aliasing  -mcpu=cortex-m4  -mfloat-abi=hard  -mfpu=fpv4-sp-d16  -mthumb  -MMD  -MP  -Wall  -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -mapcs  -std=gnu99")

# RELEASE LD FLAGS
SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -mcpu=cortex-m4  -mfloat-abi=hard  -mfpu=fpv4-sp-d16  --specs=nano.specs  -lm  -Wall  -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -Os  -mthumb  -mapcs  -Xlinker --gc-sections  -Xlinker -static  -Xlinker -z  -Xlinker muldefs  -Xlinker --defsym=__stack_size__=0x400  -Xlinker --defsym=__heap_size__=0x4000")

# ASM MACRO
SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG}  -D__DEBUG")

# C MACRO
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}  -D__DEBUG")
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}  -DCPU_MCIMX7D_M4")
SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}  -D__NDEBUG")
SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}  -DCPU_MCIMX7D_M4")

# CXX MACRO

# INCLUDE_DIRECTORIES
IF(CMAKE_BUILD_TYPE MATCHES Debug)
    INCLUDE_DIRECTORIES(${ProjDirPath}/../../../..)
    INCLUDE_DIRECTORIES(${ProjDirPath}/..)
    INCLUDE_DIRECTORIES(${ProjDirPath}/../../../../../../platform/CMSIS/Include)
    INCLUDE_DIRECTORIES(${ProjDirPath}/../../../../../../platform/devices)
    INCLUDE_DIRECTORIES(${ProjDirPath}/../../../../../../platform/devices/MCIMX7D/include)
    INCLUDE_DIRECTORIES(${ProjDirPath}/../../../../../../platform/devices/MCIMX7D/startup)
    INCLUDE_DIRECTORIES(${ProjDirPath}/../../../../../../platform/drivers/inc)
    INCLUDE_DIRECTORIES(${ProjDirPath}/../../../../../../platform/utilities/inc)
    INCLUDE_DIRECTORIES(${ProjDirPath}/../../../..)
    INCLUDE_DIRECTORIES(${ProjDirPath}/../../../../../../middleware/multicore/open-amp)
    INCLUDE_DIRECTORIES(${ProjDirPath}/..)
    INCLUDE_DIRECTORIES(${ProjDirPath}/../../../../../../middleware/multicore/open-amp/porting/imx7d_m4)
    INCLUDE_DIRECTORIES(${ProjDirPath}/../../../../../../middleware/multicore/open-amp/porting/env/bm)
ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
    INCLUDE_DIRECTORIES(${ProjDirPath}/../../../..)
    INCLUDE_DIRECTORIES(${ProjDirPath}/..)
    INCLUDE_DIRECTORIES(${ProjDirPath}/../../../../../../platform/CMSIS/Include)
    INCLUDE_DIRECTORIES(${ProjDirPath}/../../../../../../platform/devices)
    INCLUDE_DIRECTORIES(${ProjDirPath}/../../../../../../platform/devices/MCIMX7D/include)
    INCLUDE_DIRECTORIES(${ProjDirPath}/../../../../../../platform/devices/MCIMX7D/startup)
    INCLUDE_DIRECTORIES(${ProjDirPath}/../../../../../../platform/drivers/inc)
    INCLUDE_DIRECTORIES(${ProjDirPath}/../../../../../../platform/utilities/inc)
    INCLUDE_DIRECTORIES(${ProjDirPath}/../../../..)
    INCLUDE_DIRECTORIES(${ProjDirPath}/../../../../../../middleware/multicore/open-amp)
    INCLUDE_DIRECTORIES(${ProjDirPath}/..)
    INCLUDE_DIRECTORIES(${ProjDirPath}/../../../../../../middleware/multicore/open-amp/porting/imx7d_m4)
    INCLUDE_DIRECTORIES(${ProjDirPath}/../../../../../../middleware/multicore/open-amp/porting/env/bm)
ENDIF()

# ADD_EXECUTABLE
ADD_EXECUTABLE(rpmsg_pingpong_bm_example 
    "${ProjDirPath}/../../../../../../platform/devices/MCIMX7D/startup/gcc/startup_MCIMX7D_M4.S"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/porting/imx7d_m4/platform.h"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/porting/imx7d_m4/rpmsg_platform_porting.h"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/rpmsg/rpmsg.h"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/rpmsg/rpmsg_ext.h"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/common/hil/hil.h"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/common/llist/llist.h"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/common/shm/sh_mem.h"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/porting/config/config.h"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/porting/env/env.h"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/rpmsg/rpmsg_core.h"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/virtio/virtio.h"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/virtio/virtio_ring.h"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/virtio/virtqueue.h"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/rpmsg/rpmsg_rtos.h"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/porting/env/bm/rpmsg_porting.h"
    "${ProjDirPath}/../../../../../../platform/drivers/inc/ccm_analog_imx7d.h"
    "${ProjDirPath}/../../../../../../platform/drivers/inc/ccm_imx7d.h"
    "${ProjDirPath}/../../../../../../platform/drivers/inc/lmem.h"
    "${ProjDirPath}/../../../../../../platform/drivers/inc/rdc.h"
    "${ProjDirPath}/../../../../../../platform/drivers/inc/rdc_defs_imx7d.h"
    "${ProjDirPath}/../../../../../../platform/drivers/inc/wdog_imx.h"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/porting/imx7d_m4/platform.c"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/porting/imx7d_m4/platform_info.c"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/common/hil/hil.c"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/common/llist/llist.c"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/common/shm/sh_mem.c"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/porting/config/config.c"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/rpmsg/remote_device.c"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/rpmsg/rpmsg.c"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/rpmsg/rpmsg_ext.c"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/rpmsg/rpmsg_core.c"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/virtio/virtio.c"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/virtio/virtqueue.c"
    "${ProjDirPath}/../../../../../../middleware/multicore/open-amp/porting/env/bm/rpmsg_porting.c"
    "${ProjDirPath}/../../../../../../platform/drivers/src/ccm_analog_imx7d.c"
    "${ProjDirPath}/../../../../../../platform/drivers/src/ccm_imx7d.c"
    "${ProjDirPath}/../../../../../../platform/drivers/src/lmem.c"
    "${ProjDirPath}/../../../../../../platform/drivers/src/rdc.c"
    "${ProjDirPath}/../../../../../../platform/drivers/src/wdog_imx.c"
    "${ProjDirPath}/../../../../../../platform/utilities/src/debug_console_imx.c"
    "${ProjDirPath}/../../../../../../platform/utilities/inc/debug_console_imx.h"
    "${ProjDirPath}/../../../../../../platform/utilities/src/print_scan.c"
    "${ProjDirPath}/../../../../../../platform/utilities/src/print_scan.h"
    "${ProjDirPath}/../../../../../../platform/devices/MCIMX7D/startup/system_MCIMX7D_M4.c"
    "${ProjDirPath}/../../../../../../platform/devices/MCIMX7D/startup/system_MCIMX7D_M4.h"
    "${ProjDirPath}/../../../../pin_mux.c"
    "${ProjDirPath}/../../../../pin_mux.h"
    "${ProjDirPath}/../../../../board.c"
    "${ProjDirPath}/../../../../board.h"
    "${ProjDirPath}/../../../../clock_freq.c"
    "${ProjDirPath}/../../../../clock_freq.h"
    "${ProjDirPath}/../hardware_init.c"
    "${ProjDirPath}/../pingpong_bm.c"
    "${ProjDirPath}/../../../../../../platform/drivers/src/uart_imx.c"
    "${ProjDirPath}/../../../../../../platform/drivers/inc/uart_imx.h"
    "${ProjDirPath}/../../../../../../platform/drivers/src/mu_imx.c"
    "${ProjDirPath}/../../../../../../platform/drivers/inc/mu_imx.h"
)
SET_TARGET_PROPERTIES(rpmsg_pingpong_bm_example PROPERTIES OUTPUT_NAME "rpmsg_pingpong_bm_example.elf")

TARGET_LINK_LIBRARIES(rpmsg_pingpong_bm_example -Wl,--start-group)
# LIBRARIES
IF(CMAKE_BUILD_TYPE MATCHES Debug)
ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
ENDIF()

# SYSTEM LIBRARIES
TARGET_LINK_LIBRARIES(rpmsg_pingpong_bm_example m)
TARGET_LINK_LIBRARIES(rpmsg_pingpong_bm_example c)
TARGET_LINK_LIBRARIES(rpmsg_pingpong_bm_example gcc)
TARGET_LINK_LIBRARIES(rpmsg_pingpong_bm_example nosys)
TARGET_LINK_LIBRARIES(rpmsg_pingpong_bm_example -Wl,--end-group)

# MAP FILE
SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG}  -Xlinker -Map=debug/rpmsg_pingpong_bm_example.map")
SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE}  -Xlinker -Map=release/rpmsg_pingpong_bm_example.map")

# BIN AND HEX
ADD_CUSTOM_COMMAND(TARGET rpmsg_pingpong_bm_example POST_BUILD COMMAND ${CMAKE_OBJCOPY} -Oihex ${EXECUTABLE_OUTPUT_PATH}/rpmsg_pingpong_bm_example.elf ${EXECUTABLE_OUTPUT_PATH}/rpmsg_pingpong_bm_example.hex)
ADD_CUSTOM_COMMAND(TARGET rpmsg_pingpong_bm_example POST_BUILD COMMAND ${CMAKE_OBJCOPY} -Obinary ${EXECUTABLE_OUTPUT_PATH}/rpmsg_pingpong_bm_example.elf ${EXECUTABLE_OUTPUT_PATH}/rpmsg_pingpong_bm_example.bin)
