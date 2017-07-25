#ifndef PORT_MACRO_H_
#define PORT_MACRO_H_

/*
 *  Port types definitions.
 */
#define port_stack_type		uint8_t
typedef port_stack_type		stack_type_t;

/*
 *	Function specific attributes
 */
#define NAKED_FUNCTION		__attribute__ ( ( naked ) )
#define INLINE_FUNCTION		__attribute__ ( ( always_inline ) )

/*
 *  System timer definitions.
 */
#define SysTick_Handler	ISR
#define TIMER_VECT		TIMER1_COMPA_vect
#define TIMER_NAKED		ISR_NAKED


#endif /* PORT_MACRO_H_ */
