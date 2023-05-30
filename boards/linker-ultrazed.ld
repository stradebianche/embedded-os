/*
 * v8bsp
 * Linker template for ARMv8
 */

MEMORY
{
	DDR_RAM_0 : ORIGIN = 0x0, LENGTH = 0x1000000
}

ENTRY(_boot)

SECTIONS 
{
	. = 0x0;

	/* 
	 * Let's put the boot code and handlers in here 
	 */
	.boot	:
	{
		*(.boot)
	} > DDR_RAM_0
	
	/*
	 * Code section
	 */
	.text ALIGN(8) :
	{
		*(.text)
	} > DDR_RAM_0
	
	/* 
	 * Data sections
	 */
	.rodata	:
	{
		. = ALIGN(64);
		*(.rodata)
	} > DDR_RAM_0
	
	.data	:
	{
		. = ALIGN(64);
		*(.data)
	} > DDR_RAM_0
	
	.bss (NOLOAD) :
	{
		. = ALIGN(64);
		__bss_start__ = .;
		*(.bss)
		. = ALIGN(64);
		__bss_end__ = .;
	} > DDR_RAM_0
	
	/* 
	 * Stack sections
	 *   - SP has to be 16-byte aligned!
	 */
	. = ALIGN(16);					
	. = . + 0x8000;
	stack_top = .; 

	/* 
	 * Translation tables 
	 *   - tables has to be properly aligned!
	 */
	.mmu_tbl_0 (ALIGN(4096)) : {	
   		*(.mmu_tbl_0)
	} > DDR_RAM_0

	.mmu_tbl_1 (ALIGN(4096)) : {
   		*(.mmu_tbl_1)
	} > DDR_RAM_0
	
	.mmu_tbl_2 (ALIGN(4096)) : {
   		*(.mmu_tbl_2)
	} > DDR_RAM_0
}
