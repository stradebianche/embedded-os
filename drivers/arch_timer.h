#ifndef ARM_ARCH_TIMER_H_
#define ARM_ARCH_TIMER_H_

void 
arch_timer_enable();

unsigned long long 
arch_timer_get_count();

void 
arch_timer_set_comp_value(unsigned long long value);

#endif
