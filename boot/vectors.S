.text

.global vector_table

.align 11
vector_table:
	.org(vector_table + 0x000)
	b .
	.org(vector_table + 0x080)
	b .
	.org(vector_table + 0x100)
	b .
	.org(vector_table + 0x180)
	b .

	/* Current EL with SP_ELx, x>0 */
	.org(vector_table + 0x200)
	b .
	.org(vector_table + 0x280) // IRQ/FIQ
	b irq_handler
	.org(vector_table + 0x300)
	b .
	.org(vector_table + 0x380)
	b .

	.org(vector_table + 0x400)
	b .
	.org(vector_table + 0x480)
	b .
	.org(vector_table + 0x500)
	b .
	.org(vector_table + 0x580)
	b .

	.org(vector_table + 0x600)
	b .
	.org(vector_table + 0x680)
	b .
	.org(vector_table + 0x700)
	b .
	.org(vector_table + 0x780)
	b .

