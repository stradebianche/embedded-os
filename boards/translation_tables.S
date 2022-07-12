/*
 * Translation Tables for UltraZed Board
 *
 * Coverage:
 *    - DDR RAM:   0x0 - 0x8000000 (128 MB)
 */
.globl  mmu_table_l0
.globl  mmu_table_l1
.globl  mmu_table_l2

.set reserved,	0x0 					
.set memory,	0x405 | (2 << 8) | (0x0)
.set device,	0x409 | (1 << 53)| (1 << 54) |(0x0)

/*
 * TTBR0_El1 -> mmu_table_l0 -> mmu_table_l1 -> mmu_table_l2:
 * 							mmu_table_l2:
 * 							- 2 MB region 1st
 * 							...
 * 							- 2 MB region Nth
 */

.section .mmu_tbl_0,"a"
mmu_table_l0:
	.set    SECT, mmu_table_l1 
	.8byte	SECT + 0x3


.section .mmu_tbl_1,"a"
mmu_table_l1:
	.set    SECT, mmu_table_l2			/* points to 1st GiB */
	.8byte	SECT + 0x3

	.set    SECT, SECT + 0x1000			/* points to 2nd GiB */
	.8byte  SECT + 0x3

	.set    SECT, SECT + 0x1000			/* points to 3rd GiB */
	.8byte  SECT + 0x3

	.set    SECT, SECT + 0x1000			/* points to 4th GiB */
	.8byte  SECT + 0x3

	/* remaining (512-4) entries keep reserved */
	//TODO


.section .mmu_tbl_2,"a"
mmu_table_l2:
	.set SECT, 0

	/* 1st GiB */
	.rept	0x40						/* first 128 MB of DDR are valid */
	.8byte	SECT + memory
	.set	SECT, SECT + 0x200000
	.endr
	.rept   0x1C0						/* remaining 896 MB reserved */
	.8byte  SECT + reserved
	.set    SECT, SECT + 0x200000
	.endr

	/* 2nd GiB */
	.rept   0x200
	.8byte  SECT + reserved
	.set    SECT, SECT + 0x200000
	.endr

	/* 3rd GiB */
	.rept   0x200
	.8byte  SECT + reserved
	.set    SECT, SECT + 0x200000
	.endr

	/* 4th GiB */
	.rept   0x1C8						/* 0xC000_0000 to 0xF8FF_FFFF */
	.8byte  SECT + reserved					/* reserved */
	.set    SECT, SECT + 0x200000
	.endr
	.rept	0x1						/* 0xF900_0000 to 0xF91F_FFFF */
	.8byte	SECT + device					/* GIC v2 */
	.set	SECT, SECT + 0x200000
	.endr
	.rept	0x2F						/* 0xF9200_0000 to 0xFEFF_FFFF */
	.8byte	SECT + reserved					/* reserved */
	.set	SECT, SECT + 0x200000
	.endr	
	.rept	0x6						/* 0xFF00_0000 to 0xFFBF_FFFF */
	.8byte	SECT + device					/* LPD Slaves: PS UART, etc. */
	.set	SECT, SECT + 0x200000
	.endr
	.rept   0x2						/* 0xFFC0_0000 to 0xFFFF_FFFF */
	.8byte  SECT + reserved					/* reserved */
	.set    SECT, SECT + 0x200000
	.endr
