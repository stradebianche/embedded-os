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
