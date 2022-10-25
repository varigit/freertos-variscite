/*
Copyright 2021 by Retune DSP
Copyright 2022 NXP

NXP Confidential. This software is owned or controlled by NXP and may only be used strictly in accordance with the applicable license terms.  By expressly accepting such terms or by downloading, installing, activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef RDSP_PUBLIC_UTILITY_H
#define RDSP_PUBLIC_UTILITY_H

#include "RdspPluginTypes.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Library options
 */

#define RDSP_ENABLE_PRINTF 0
#define RDSP_ENABLE_FILEIO 0

/*
 * Memory management
 */

typedef enum {
	MEM_ALIGN_1 = 1, /*!< Align 1 byte */
	MEM_ALIGN_2 = 2, /*!< Align 2 byte */
	MEM_ALIGN_4 = 4, /*!< Align 4 byte */
	MEM_ALIGN_8 = 8, /*!< Align 8 byte */
	MEM_ALIGN_16 = 16, /*!< Align 16 byte */
} MemAlign_t;

typedef struct rdsp_mem_s {
	void *pPrivateDataBase;
	void *pPrivateDataNext;
	uint32_t FreePrivateDataSize;
	uint32_t count_malloc_bytes;

	void *pScratchDataBase;
	void *pScratchDataNext;
	uint32_t FreeScratchDataSize;
	uint32_t count_scratch_malloc_bytes;
} rdsp_mem_t;

/*
 * Scratch memory allocation
 */

extern void rdsp_plugin_scratch_init(void* Aext_scratch_mem_baseptr, void* Aext_scratch_mem_nextptr, uint32_t Aext_scratch_memSize);
extern uint32_t rdsp_plugin_scratch_GetAllocatedBytes();
extern void rdsp_plugin_scratch_reset();
extern void* rdsp_plugin_scratch_malloc(uint32_t Asize, int32_t Aalign);

/*
 * Persistent memory allocation
 */

extern void* rdsp_plugin_malloc_init(void* Aextmem_baseptr, void* Aextmem_nextptr, uint32_t AextmemSize);
extern uint32_t rdsp_plugin_malloc_GetAllocatedBytes();
extern void* rdsp_plugin_malloc(uint32_t Asize, int32_t Aalign);
extern void* rdsp_plugin_free(void* Amem);
extern void* rdsp_plugin_memset(void* Aptr, uint8_t Aval, uint32_t Asize);
extern void* rdsp_plugin_memset_float(rfloat* Aptr, rfloat Aval, uint32_t Alength);
extern void rdsp_plugin_memcpy(void* Adest, void* Asrc, uint32_t Asize);
extern void rdsp_plugin_memmove(void* Adest, void* Asrc, uint32_t Asize);

/*
 * File I/O
 */
#if RDSP_ENABLE_FILEIO==1
typedef struct rdsp_file_s {
	FILE* rdspFile; // USB file for fopen/fwrite
} rdsp_file_t;

extern rdsp_file_t* rdsp_fopen(char* filename, const char* mode);
extern int32_t rdsp_fclose(rdsp_file_t* stream);
extern size_t rdsp_fread(void* ptr, int32_t size, int32_t count, rdsp_file_t* stream);
extern size_t rdsp_fwrite(void* ptr, int32_t size, int32_t count, rdsp_file_t* stream);
extern void rdsp_fwrite_rfloat(rfloat* x, int32_t length, rdsp_file_t* fid);
extern int rdsp_fseek(rdsp_file_t* stream, long int offset, int origin);
extern long int rdsp_ftell(rdsp_file_t* stream);
extern void rdsp_rewind(rdsp_file_t* stream);
#endif // RDSP_ENABLE_FILEIO==1

/*
 * Printing
 */

#if RDSP_ENABLE_PRINTF==1
#ifdef SDK_DEBUGCONSOLE
extern int DbgConsole_Printf(const char *formatString, ...);
#define RDSP_PRINTF(...) DbgConsole_Printf(__VA_ARGS__)
#else
#define RDSP_PRINTF(...) printf(__VA_ARGS__)
#endif
#else
#define RDSP_PRINTF
#endif // RDSP_ENABLE_PRINTF==1

#ifdef __cplusplus
}
#endif

#endif // RDSP_PUBLIC_UTILITY_H

