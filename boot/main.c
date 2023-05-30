#include <stdlib.h>
#include <unistd.h>
#include "pseudo_asm.h"
#include "gicv2.h"
#include "xilinx_uart_ps.h"
#include "arch_timer.h"
#include "exceptions.h"

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

void systick_handler(void *arg) {
	unsigned long long counter = arch_timer_get_count();
	/* writing value bigger than current CNTVCT_EL0 will clear irq bit in CNTV_CTL_EL0 */
	arch_timer_set_comp_value(counter + (unsigned long long)0x10000000);
	systick = 1;
}

int main(void) {

	uartps_puts("28/09/2022 - 01\r\n");

	/* EL3(S) --> By default IRQ/FIQ belongs to Group0 (Secure) */
	gicv2_dist_init();
	gicv2_cpu_init();
	gicv2_set_irq_unmask(IRQ_TIMER_CNTNCT_EL0);

	/* setup arm arch timer */
	unsigned long long counter = arch_timer_get_count();
	arch_timer_set_comp_value(counter + (unsigned long long)0x1000);

	/* register handler for arch timer interrupt */
	exc_register_handler(IRQ_TIMER_CNTNCT_EL0, systick_handler);

	/* enable exceptions */
	exc_enable();

	/* enable timer */
	arch_timer_enable();

	for(;;) {
		if (systick) {
			uartps_puts("[systick]: \r\n");
			systick = 0;
		}
	}
}
