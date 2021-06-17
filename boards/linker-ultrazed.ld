/*
 * v8bsp
 * Linker template for ARMv8
 */

ENTRY(_boot)
 
SECTIONS 
{
	. = 0x0;

	/* Let's put the boot code and handlers in here */
	.boot	:
	{
		*(.boot)
	}
	
	/*. = CONFIG_MEMORY_BASE + 0x1000;*/
	
	/* Code section */
	. = ALIGN(8);
	.text	:
	{
		*(.text)
	}
	
	/* Data sections */
	.rodata	:
	{
		*(.rodata)
	}
	
	.data	:
	{
		*(.data)
	}
	
	. = ALIGN(8);
	bss_start = .;
	.bss	:
	{
		__bss_start__ = .;
		*(.bss)
		__bss_end__ = .;
	}
	
	/* Stack section */
	. = ALIGN(16);			/* SP has to be 16-byte aligned */
	. = . + 0x1000;
	stack_top = .; 

	/* Translation tables */
	. = ALIGN(4096);		/* Tables has to be properly aligned */
	.mmu_tbl_0 : {
   		*(.mmu_tbl_0)
	}
	. = ALIGN(4096);
	.mmu_tbl_1 : {
   		*(.mmu_tbl_1)
	}
	. = ALIGN(4096);
	.mmu_tbl_2 : {
   		*(.mmu_tbl_2)
	}
}
