#include <stdlib.h>
#include <unistd.h>
#include "gicv2.h"
#include "xilinx_uart_ps.h"
#include "arch_timer.h"
#include "exceptions.h"

#include "scheduler.h"

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

volatile unsigned int __systick = 0;

void systick_handler(void *arg) {
	unsigned long long counter = arch_timer_get_count();
	/* writing value bigger than current CNTVCT_EL0 will clear irq bit in CNTV_CTL_EL0 */
	arch_timer_set_comp_value(counter + (unsigned long long)0x10000000);
	__systick++;
}

/* First thread handler function */
int thread1(void) {
	for(;;) {

		static unsigned int systick;
		if (systick != __systick) {
			uartps_puts("systick changed!\r\n");
			systick = __systick;
		}

		for (unsigned long long i = 0; i < 64000000; i++) {
			asm volatile ("nop");
			asm volatile ("nop");
			asm volatile ("nop");
			asm volatile ("nop");
			asm volatile ("nop");
		}
	}
	return 0;
}


int main(void) {

	uartps_puts("Embedded OS - 16/11/2022 - 00\r\n");

	/* EL3(S) --> By default IRQ/FIQ belongs to Group0 (Secure) */
	gicv2_dist_init();
	gicv2_cpu_init();
	gicv2_set_irq_unmask(IRQ_TIMER_CNTNCT_EL0);

	/* setup arm arch timer */
	unsigned long long counter = arch_timer_get_count();
	arch_timer_set_comp_value(counter + (unsigned long long)0x1000);

	/* register handler for arch timer interrupt */
	exc_register_handler(IRQ_TIMER_CNTNCT_EL0, systick_handler);

	/* Initialize system components */
	os_init_system();

	/* enable exceptions */
	exc_enable();

	/* enable timer */
	arch_timer_enable();

	/* Add some tasks with minimal stack size */
	os_create_task(thread1, STACK_MIN_SIZE);
//	os_create_task(thread2, STACK_MIN_SIZE);

	/* Start executing tasks */
	os_start_task_scheduler();
}
