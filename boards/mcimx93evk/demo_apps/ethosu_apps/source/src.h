/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SRC_ML_H
#define SRC_ML_H

#define REG32(addr)             ((volatile uint32_t *)(addr))
#define R32(addr, value)	((value) = *((volatile uint32_t *)(addr)))
#define W32(addr, value)        ((*((volatile uint32_t *)(addr))) = (value))

#define SRC_IPS_BASE_ADDR               (0x44460000)
#define SRC_GLOBAL_RBASE                (SRC_IPS_BASE_ADDR + 0x0000)
#define REG_SRC_GLOBAL_SCR              (REG32(SRC_GLOBAL_RBASE + 0x10))

#define SRC_NIC_RBASE                   (SRC_IPS_BASE_ADDR + 0x1C00)
#define REG_SRC_NIC_FUNC_STAT           (REG32(SRC_NIC_RBASE + 0xB4))

#define SRC_ML_MEM_RBASE                (SRC_IPS_BASE_ADDR + 0x4800)
#define REG_SRC_ML_MEM_MEM_CTRL         (REG32(SRC_ML_MEM_RBASE + 0x4))

#define SRC_ML_RBASE                    (SRC_IPS_BASE_ADDR + 0x1800)
#define REG_SRC_ML_AUTHEN_CTRL		(REG32(SRC_ML_RBASE + 0x4))
#define REG_SRC_ML_MEM_MEM_STAT         (REG32(SRC_ML_MEM_RBASE + 0x18))
#define REG_SRC_ML_SW_CTRL              (REG32(SRC_ML_RBASE + 0x20))
#define REG_SRC_ML_PSW_ACK_CTRL_0       (REG32(SRC_ML_RBASE + 0x80))
#define REG_SRC_ML_FUNC_STAT            (REG32(SRC_ML_RBASE + 0xB4))

#define SRC_MIX_SLICE_FUNC_STAT_RST_STAT        (BIT(2))
#define SRC_MEM_MEM_STAT_PGEN_STAT              (BIT(6))
#define SRC_MIX_SLICE_FUNC_STAT_PSW_STAT        (BIT(0))
#define SRC_MIX_SLICE_FUNC_STAT_ISO_STAT        (BIT(4))

#define BIT(nr)                                 (1UL << (nr))

#endif
