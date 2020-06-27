/*
 * v8bsp
 *
 * Linker template for ARMv8
 */
 
 #include "config.h"
 
 SECTIONS 
 {
    . = CONFIG_MEMORY_BASE;
	
	/* Let's put the boot code and handlers in here */
	.boot	:
	{
		*(.boot)
	}
	
	. = CONFIG_MEMORY_BASE + 0x1000;
	
	/* Code section */
	. = ALIGN(4);				// may not be needed
	.text	:
	{
		*(.text)
	}
	
	.rodata	:
	{
		*(.rodata)
	}
	
	.data	:
	{
		*(.data)
	}
	
	. = ALIGN(4);				// I want to have nice aligment
	bss_start = .;
	.bss	:
	{
		*(.bss)
	}
	
	. = ALIGN(4096);
	. = . + 0x1000;
	stack_top = .; 
 }
  
 ENTRY(boot_entry)
 