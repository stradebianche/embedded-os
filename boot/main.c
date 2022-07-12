#include <stdlib.h>
#include <unistd.h>
#include "pseudo_asm.h"

#include "gicv2.h"
#include "xilinx_uart_ps.h"

#define IRQ_TIMER_CNTNCT_EL0 27

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

	uartps_puts("12/07/2022\r\n");

	/* test interrupt */
	/* EL3(S) --> By default IRQ/FIQ belongs to Group0 (Secure) */
	gicv2_dist_init();
	gicv2_cpu_init();
	gicv2_set_irq_unmask(IRQ_TIMER_CNTNCT_EL0);

	asm volatile ("msr daifclr, #0x0f");

	/* setup arm arch timer */
	asm volatile ("mrs x0, CNTVCT_EL0");
	asm volatile ("isb");
	asm volatile ("add x0, x0, #1000");
	asm volatile ("msr CNTV_CVAL_EL0, x0");

	/* enable timer */
	asm volatile ("mov x0, #1");
	asm volatile ("msr CNTV_CTL_EL0, x0");

    for(;;);
}
