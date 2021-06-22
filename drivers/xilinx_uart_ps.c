#include <stdint.h>
#include "sysio.h"
#include "xilinx_uart_ps.h"

#define UARTPS_ADDRESS_BASE	0xFF000000
#define UARTPS_SR_OFFSET	0x2C
#define UARTPS_FIFO_OFFSET	0x30

void uartps_putc(char data)
{
	// TODO: check is buffer empty
	sys_write32(data, (uintptr_t)(UARTPS_ADDRESS_BASE + UARTPS_FIFO_OFFSET));
}

void uartps_puts(const char *s)
{
	while(*s)
		uartps_putc(*s++);
}

bool uartps_getc(char *data)
{
	volatile uint32_t uartps_sr_reg = sys_read32(UARTPS_ADDRESS_BASE + UARTPS_SR_OFFSET);

	if (((uartps_sr_reg & (uint32_t)0x2) == (uint32_t)0x2)) {
		return false;
	} else {
		*data = sys_read8(UARTPS_ADDRESS_BASE + UARTPS_FIFO_OFFSET);
	}

	return true;
}
