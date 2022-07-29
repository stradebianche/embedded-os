#include <stdlib.h>
#include <unistd.h>
#include "pseudo_asm.h"
#include "gicv2.h"
#include "xilinx_uart_ps.h"
#include "arch_timer.h"

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

volatile int systick = false;

int main(void) {

	uartps_puts("29/07/2022\r\n");

	/* test interrupt */
	/* EL3(S) --> By default IRQ/FIQ belongs to Group0 (Secure) */
	gicv2_dist_init();
	gicv2_cpu_init();
	gicv2_set_irq_unmask(IRQ_TIMER_CNTNCT_EL0);

	/* enable exceptions */
	asm volatile ("msr daifclr, #0x0f");

	/* setup arm arch timer */
    unsigned long long counter = arch_timer_get_count();
    arch_timer_set_comp_value(counter + (unsigned long long)0x1000);

	/* enable timer */
	arch_timer_enable();

    for(;;) {
		if (systick) {
			uartps_puts("systick\r\n");
			systick = 0;
		}
	}
}
