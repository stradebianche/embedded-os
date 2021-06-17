#include <stdint.h>
// #include "sysio.h"
#include "xilinx_uart_ps.h"

void uartps_putc(char data)
{
	volatile char *ptr = (volatile char *)0xFF000030;
	*ptr = data;
}

void uartps_puts(const char *s)
{
	while(*s) {
		uartps_putc(*s++);
	}
}

bool uartps_getc(char *data)
{
	volatile uint32_t *ptr = (volatile uint32_t *)0xFF00002C;
	volatile uint32_t uartps_sr_reg = *ptr;

	if (((uartps_sr_reg & (uint32_t)0x2) == (uint32_t)0x2)) {
		return false;
	} else {
		volatile char *fifo = (volatile char *)0xFF000030;
		*data = *fifo;
	}

	return true;
}