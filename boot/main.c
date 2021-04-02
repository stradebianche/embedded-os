#include <stdlib.h>
#include <unistd.h>
#include "pseudo_asm.h"

//#include "xilinx_uart_ps.h"

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

	unsigned int current_el;

	GET_CURRENT_EL(current_el);
	current_el = (current_el >> 2);

	switch(current_el) {
	case 3:
		puts_uart("current el: 3\n");
		break;
	case 2:
		puts_uart("current el: 2\n");
		break;
	case 1:
		puts_uart("current el: 1\n");
		break;
	case 0:
		puts_uart("current el: 0\n");
		break;		
	default:
		puts_uart("current el: error\n");
		break;
	}

	return 0;
}

