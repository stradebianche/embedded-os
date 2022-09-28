#ifndef ARM_ARCH_TIMER_H_
#define ARM_ARCH_TIMER_H_

#define IRQ_TIMER_CNTNCT_EL0 27

void 
arch_timer_enable();

void 
arch_timer_disable();

unsigned long long 
arch_timer_get_count();

void 
arch_timer_set_comp_value(unsigned long long value);

#endif
