#ifndef _SYSIO_H_
#define _SYSIO_H_

#include <stdio.h>

/*
 * Based on Zephyr implementation, direct assembly operations
 */

#define INLINE inline __attribute__((always_inline))

static INLINE void sys_write8(uint8_t data, uintptr_t addr)
{
	__asm__ volatile ("dmb sy" : : : "memory");
	__asm__ volatile ("strb %w0, [%1]" : : "r" (data), "r" (addr));
}

static INLINE uint8_t sys_read8(uintptr_t addr)
{
	uint8_t val;

	__asm__ volatile ("ldrb %w0, [%1]" : "=r" (val) : "r" (addr));
	__asm__ volatile ("dmb sy" : : : "memory");

	return val;
}

static INLINE void sys_write32(uint32_t data, uintptr_t addr)
{
	__asm__ volatile ("dmb sy" : : : "memory");
	__asm__ volatile ("str %w0, [%1]" : : "r" (data), "r" (addr));
}

static INLINE uint32_t sys_read32(uintptr_t addr)
{
	uint32_t val;

	__asm__ volatile ("ldr %w0, [%1]" : "=r" (val) : "r" (addr));
	__asm__ volatile ("dmb sy" : : : "memory");

	return val;
}

#endif
