/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __SPI_MEMORY_H__
#define __SPI_MEMORY_H__

/* Number of bytes used for addressing within memory */
#define SPI_MEMORY_ADDRESS_BYTES       3

/* Memory page size - maximum bytes per write */
#define SPI_MEMORY_PAGE_SIZE           0x0100   

/* The SPI serial memory test addresses */
#define SPI_MEMORY_ADDR1               0x000020  /* test address 1 */
#define SPI_MEMORY_ADDR2               0x000120  /* test address 2 */
#define SPI_MEMORY_ADDR3               0x000220  /* test address 3 */

/* The SPI serial memory instructions */
#define SPI_MEMORY_WRITE_ENABLE        0x06
#define SPI_MEMORY_WRITE_DISABLE       0x04
#define SPI_MEMORY_READ_STATUS         0x05
#define SPI_MEMORY_WRITE_STATUS        0x01
#define SPI_MEMORY_READ_DATA           0x03
#define SPI_MEMORY_PAGE_PROGRAM        0x02
#define SPI_MEMORY_BULK_ERASE          0xC7

#ifdef __cplusplus
extern "C" {
#endif

/* Funtion prototypes */
uint8_t M25P32_ReadStatus(void);
void M25P32_SetWriteEnable(bool enable);
void M25P32_SetProtection(bool protect);
void M25P32_EraseChip(void);
uint32_t M25P32_WriteData(uint32_t addr, uint32_t size, uint8_t* data);
uint32_t M25P32_ReadData(uint32_t addr, uint32_t size, uint8_t* data);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* __SPI_MEMORY_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
