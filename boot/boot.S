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
	ldr x0, =vector_table
	msr vbar_el3, x0

	msr sctlr_el3, xzr
	msr sctlr_el2, xzr
	msr hcr_el2, xzr

	mrs x0, scr_el3
	orr x0, x0, #(1<<10)	/* The next lower level is AArch64 */
	orr x0, x0, #(1 << 3)	/* SError routed to EL3 */
	orr x0, x0, #(1 << 2)	/* FIQs routed to EL3 */
	orr x0, x0, #(1 << 1)	/* IRQs routed to EL3 */
	orr x0, x0, #(1<<0)		/* Exception levels lower than EL3 are in */
							/* non-secure state                       */

	msr scr_el3, x0
	isb

	msr cptr_el3, xzr	/* Do not trap FP access */

	/* set initial el3 stack pointer value */
	ldr x1, =stack_top
	and x0, x1, #0xfffffffffffffff0
	mov sp, x0

	/* setup MMU */
	ldr x0, =0x000000BB0400FF44
	msr mair_el3, x0

	/* TCR_EL3, PS=010, TG0=00, T0SZ=24 */
	ldr x0, =0x80823518
	msr tcr_el3, x0
	isb

	/* set translation table base address */
	ldr x0, =mmu_table_l0
	msr ttbr0_el3, x0

	/* enable SError */
	mrs x0, daif
	bic x0, x0, #(1 << 8)
	msr daif, x0

	/* enable mmu, caches, sp aligment */
	// https://developer.arm.com/documentation/ddi0601/2021-03/AArch64-Registers/SCTLR-EL1--System-Control-Register--EL1-?lang=en
	mov x1, xzr
	orr x1, x1, #(1 << 5)
	orr x1, x1, #(1 << 12)		// I caches
	orr x1, x1, #(1 << 3)		// SP aligment check
	orr x1, x1, #(1 << 2)		// D caches
	orr x1, x1, #(1 << 0)		// MMU
	msr sctlr_el3, x1

	dsb	 sy
	isb

	mov x0, xzr
	mov x1, xzr

	/* currently, not dropping to EL1(NS) */
	b _startup

	mov x0, #0b01001	/* EL=EL2, SP=SPx, DAIF=0000 */
	msr spsr_el3, x0

	adr x0, init_el2
	msr elr_el3, x0

	eret

init_el2:
	/* drops to el1 */	
	msr sctlr_el1, xzr
	
	mrs x0, hcr_el2
	orr x0, x0, #(1<<31)    /* The Execution state for EL1 is AArch64 */
	msr hcr_el2, x0

	mov x0, #0b00101        /* EL=EL1, SP=SPx, DAIF=0000 */
	msr spsr_el2, x0

	adr x0, init_el1
	msr elr_el2, x0

	eret

init_el1:
	/* set initial stack pointer value */
	ldr x1, =stack_top
	and x0, x1, #0xfffffffffffffff0
	mov sp, x0

	/* set vector table base address */
	ldr x0, =vector_table
	msr vbar_el1, x0

	/* enable SError */
	mrs x0, daif
	bic x0, x0, #(1 << 8)
	msr daif, x0

	/* invalidate caches */
	// TODO: operation required after reset

	/* setting up the mmu */
	// TODO:
	// MAIR_EL1
	ldr x0, =0x000000BB0400FF44
	msr mair_el1, x0
	// TCR_EL1, PS=010, TG0=00, T0SZ=24
	ldr x0, =0x285800518
	msr tcr_el1, x0
	isb

	/* set translation table base address */
	ldr x0, =mmu_table_l0
	msr ttbr0_el1, x0

	/* enable mmu, caches, sp aligment */
	// https://developer.arm.com/documentation/ddi0601/2021-03/AArch64-Registers/SCTLR-EL1--System-Control-Register--EL1-?lang=en
	mov x1, xzr
	orr     x1, x1, #(1 << 5)
	//orr x1, x1, #(1 << 12)	// I caches
	orr x1, x1, #(1 << 3)		// SP aligment check
	//orr x1, x1, #(1 << 2)		// D caches
	orr x1, x1, #(1 << 0)		// MMU
	msr sctlr_el1, x1

	dsb sy
	isb

	mov x0, xzr
	mov x1, xzr

	b _startup

error:
	b .
