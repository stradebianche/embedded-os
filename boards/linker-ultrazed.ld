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
	. = ALIGN(4);
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
	
	. = ALIGN(4);
	bss_start = .;
	.bss	:
	{
		__bss_start__ = .;
		*(.bss)
		__bss_end__ = .;
	}
	
	/* Stack section */
	. = ALIGN(16);
	. = . + 0x1000;
	stack_top = .; 

	/* Translation tables */
	. = ALIGN(16);
	.mmu_tbl_0 : {
   		*(.mmu_tbl_0)
	}

	. = ALIGN(16);
	.mmu_tbl_1 : {
   		*(.mmu_tbl_1)
	}

	. = ALIGN(16);
	.mmu_tbl_2 : {
   		*(.mmu_tbl_2)
	}
}

