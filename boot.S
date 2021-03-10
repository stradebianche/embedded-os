.section .boot,"ax"

.global _boot

_boot:
	/* set initial stack pointer value */
	ldr x1, =stack_top
	and x0, x1, #0xfffffffffffffff0
	mov sp, x0

	mov x0, xzr
	mov x1, xzr

	b _startup
