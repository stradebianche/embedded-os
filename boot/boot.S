/*
 * Boot code before application handoff.
 */
.section .boot,"ax"

.global _boot

_boot:
	mrs x0, currentEL
	cmp x0, #0xc
	beq init_el3

	cmp x0, #0x8
	beq init_el2

	cmp x0, #0x4
	beq init_el1

	b error

init_el3:
	/* drops to el2 */
	msr sctlr_el2, xzr
	msr hcr_el2, xzr

	mrs x0, scr_el3
	orr x0, x0, #(1<<10)	/* The next lower level is AArch64 */
	orr x0, x0, #(1<<0)	/* Exception levels lower than EL3 are in */
				/* Non-secure state                       */
	msr scr_el3, x0

	mov x0, #0b01001	/* EL=EL2, SP=SPx, DAIF=0000 */
	msr spsr_el3, x0

	adr x0, init_el2
	msr elr_el3, x0

	eret

init_el2:
	/* drops to el1 */	
	msr sctlr_el1, xzr
	
	mrs x0, hcr_el2
	orr x0, x0, #(1<<31)	/* The Execution state for EL1 is AArch64 */
	msr hcr_el2, x0

	mov x0, #0b00101	/* EL=EL1, SP=SPx, DAIF=0000 */
	msr spsr_el2, x0

	adr x0, init_el1
	msr elr_el2, x0

	eret

init_el1:
	/* set initial stack pointer value */
	ldr x1, =stack_top
	and x0, x1, #0xfffffffffffffff0
	mov sp, x0

	mov x0, xzr
	mov x1, xzr

	b _startup

error:
	b .

