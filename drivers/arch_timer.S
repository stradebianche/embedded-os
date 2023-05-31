.text

.global arch_timer_get_count
arch_timer_get_count:
	mrs x0, cntvct_el0
	isb
	ret

.global arch_timer_set_comp_value
arch_timer_set_comp_value:
	msr cntv_cval_el0, x0
	isb
	ret

.global arch_timer_enable
arch_timer_enable:
	mov x0, #1
	msr cntv_ctl_el0, x0
	isb
	ret

.global arch_timer_disable
arch_timer_disable:
	mov x0, #0
	mrs x0, cntv_ctl_el0
	isb
	ret
