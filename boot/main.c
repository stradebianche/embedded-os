#include <stdlib.h>
#include <unistd.h>
#include "pseudo_asm.h"

#include "xilinx_uart_ps.h"

volatile unsigned int * const UART0DR = (unsigned int *)0x09000000;

static void puts_uart(const char *s)
{
	while (*s != '\0') {
		*UART0DR = (unsigned int)(*s);
		s++;
	}
}

void _exit (int status);
void _exit (int status)
{
	(void)status;
	for (;;);
}

caddr_t _sbrk (int incr);
caddr_t _sbrk (int incr)
{
	(void) incr;
	return 0;
}


int main(void) {

	char inbuf[28];
	char *pinbuf = inbuf;
	char inbyte = 0;

	uartps_puts("Hello scheduler\n");

	for (;;) {
		bool status = uartps_getc(&inbyte);
		if (status) {
			if (inbyte != 10 && inbyte != 13) {
				*pinbuf++ = inbyte;
			} else {
				*pinbuf++ = '\0';
				break;
			}
		}
	}

	uartps_puts("received: ");
	uartps_puts(inbuf);

	return 0;
}

