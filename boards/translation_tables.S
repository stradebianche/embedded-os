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
 *     mmu_table_l2:
 *         - 2 MB region 1st 
 * 		...
 *         - 2 MB region Nth
 */

.section .mmu_tbl_0,"a"
mmu_table_l0:
	.set SECT, mmu_table_l1 
	.8byte	SECT + 0x3

.section .mmu_tbl_1,"a"
mmu_table_l1:
	.set SECT, mmu_table_l2
	.8byte	SECT + 0x3

.section .mmu_tbl_2,"a"
mmu_table_l2:
	.set SECT, 0
	.set DDR_REGIONS, 0x8000000/0x200000	/* 128 MB */

	.rept	DDR_REGIONS
	.8byte	SECT + memory
	.set	SECT, SECT + 0x200000
	.endr

