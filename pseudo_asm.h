/*
 *
 */
#ifndef PSEUDO_ASM_H_
#define PSEUDO_ASM_H_

#define GET_CURRENT_EL(value)	\
	__asm__ __volatile__( \
			"mrs %[result], CurrentEL" : \
			[result] "=r" (value) ::)

#endif

