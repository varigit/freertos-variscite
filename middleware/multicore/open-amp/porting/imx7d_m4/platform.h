/*
 * Copyright (c) 2015 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of Freescale Semiconductor nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/**************************************************************************
 * FILE NAME
 *
 *       platform.h
 *
 * COMPONENT
 *
 *       OpenAMP
 *
 * DESCRIPTION
 *
 * This file provides function prototypes of platform.c.
 *
 **************************************************************************/

#ifndef PLATFORM_H_
#define PLATFORM_H_

/*
 * 32 MSG (16 rx, 16 tx), 512 bytes each, it is only used when RPMSG driver is working in master mode, otherwise
 * the share memory is managed by the other side.
 * When working with Linux, SHM_ADDR and SHM_SIZE is not used
 */
#define SHM_ADDR                    (0)
#define SHM_SIZE                    (0)

void platform_time_delay(int num_msec);
int  platform_in_isr(void);
int  platform_interrupt_enable(unsigned int vector_id, unsigned int trigger_type, unsigned int priority);
int  platform_interrupt_disable(unsigned int vector_id);
void platform_interrupt_enable_all(void);
void platform_interrupt_disable_all(void);
void platform_map_mem_region(unsigned int va,unsigned int pa, unsigned int size, unsigned int flags);
void platform_cache_all_flush_invalidate(void);
void platform_cache_disable(void);
unsigned long platform_vatopa(void *addr);
void *platform_patova(unsigned long addr);
void platform_isr(int vect_id, void *data);
int  platform_init(void);
int  platform_deinit(void);

#endif /* PLATFORM_H_ */
