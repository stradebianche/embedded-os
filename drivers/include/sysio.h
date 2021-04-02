#ifndef _SYSIO_H_
#define _SYSIO_H_

#define INLINE inline


static INLINE void sys_write32(uint32_t data, uintptr_t addr)
{
	/* DMB() */
	*(volatile uint32_t *)addr = data;
}

static INLINE uint32_t sys_read32(uintptr_t addr)
{
	uint32_t val = *(volatile uint32_t *)addr;
	// __DMB();
	return val;
}


#endif

