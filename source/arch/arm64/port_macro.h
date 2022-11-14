#ifndef PORT_MACRO_H_
#define PORT_MACRO_H_

/*
 *  Port types definitions.
 */
#define port_stack_type		uint64_t
typedef port_stack_type		stack_type_t;

/*
 *	Function specific attributes
 */
#define NAKED_FUNCTION		// __attribute__ ( ( naked ) )
#define INLINE_FUNCTION		__attribute__ ( ( always_inline ) )

/*
 *  System timer definitions.
 */
#define SysTick_Handler	SysTick_Handler
#define TIMER_VECT		
#define TIMER_NAKED		


#endif /* PORT_MACRO_H_ */
