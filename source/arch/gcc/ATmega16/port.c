#include <avr/interrupt.h>
#include <avr/io.h>

#include "port.h"
#include "scheduler.h"

/* Private variables ---------------------------------------------------------*/

/* Store current task _SP_ address */
static stack_type_t *current_task;

/* This to help solving RAMEND forbidden access from ISR routine - dunno why not workin */
volatile static const unsigned int ram_end = RAMEND;


/* Returns saved context stack pointer */
stack_type_t * port_get_current_stack_pointer( void ) {
	return current_task;
}


/* Set stack pointer of context to restore */
void port_set_new_stack_pointer( stack_type_t *new_task_sp ) {
	current_task = new_task_sp;
}


/* Allocate stack memory for task */
void port_allocate_stack_memory( stack_type_t **return_stack_top, size_t stack_size ) {

	/* Use malloc to allocate memory, set highest address as stack initial value */
	*return_stack_top = ( malloc( stack_size ) + stack_size - 1 );
}


/* Prepare tasks tack for first use */
stack_type_t * port_init_task_stack( stack_type_t *stack_top, task_func_t func_handler) {
	
	/* Debug info */
	*stack_top = 0x77;
	stack_top--;
	*stack_top = 0x77;
	stack_top--;

	/* Init stack with task function address */
	/* Get address of task handler function */
	/* Works only for 2-byte PC */
	uint16_t taskThreadAddress = (uint16_t)func_handler;

	/* Insert task handler function for ret(i) */
	*stack_top = (taskThreadAddress & 0xff);
	stack_top--;
	*stack_top = (taskThreadAddress >> 8) & 0xff;
	stack_top--;

	/* Initialize register R0 */
	*stack_top = 0x00;
	stack_top--;

	/* Put interrupt enable on SREG */
	*stack_top = 0x80;
	//*stack_top = 0x00;
	stack_top--;

	/* R1 must be set to 0 */
	*stack_top = 0x00;
	stack_top--;

	/* Initialize rest of regs R2..R31 */
	*stack_top = 0x02;
	stack_top--;
	*stack_top = 0x03;
	stack_top--;
	*stack_top = 0x04;
	stack_top--;
	*stack_top = 0x05;
	stack_top--;
	*stack_top = 0x06;
	stack_top--;
	*stack_top = 0x07;
	stack_top--;
	*stack_top = 0x08;
	stack_top--;
	*stack_top = 0x09;
	stack_top--;
	*stack_top = 0x10;
	stack_top--;
	*stack_top = 0x11;
	stack_top--;
	*stack_top = 0x12;
	stack_top--;
	*stack_top = 0x13;
	stack_top--;
	*stack_top = 0x14;
	stack_top--;
	*stack_top = 0x15;
	stack_top--;
	*stack_top = 0x16;
	stack_top--;
	*stack_top = 0x17;
	stack_top--;
	*stack_top = 0x18;
	stack_top--;
	*stack_top = 0x19;
	stack_top--;
	*stack_top = 0x20;
	stack_top--;
	*stack_top = 0x21;
	stack_top--;
	*stack_top = 0x22;
	stack_top--;
	*stack_top = 0x23;
	stack_top--;

	/* Thread attributes here - TO BE DONE*/
	*stack_top = 0x24;
	stack_top--;
	*stack_top = 0x25;
	stack_top--;
	/* ------- */

	*stack_top = 0x26;
	stack_top--;
	*stack_top = 0x27;
	stack_top--;
	*stack_top = 0x28;
	stack_top--;
	*stack_top = 0x29;
	stack_top--;
	*stack_top = 0x30;
	stack_top--;
	*stack_top = 0x31;
	stack_top--;

	return stack_top;
}


/* Resets system timer */
void port_reset_timer( void ) {
	TCNT1 = 0;
}


/* Init system timer */
void port_init_system_timer( uint8_t period_ms ) {

	/* Given period formula:	period * F_CPU / preskaler = timer_cnt + 1 */
	/* freq = 50 Hz, thus period = 20 ms, then if prescaler = 8, then timer_cnt = 39 999 */

	/* Calculating give tick count */
 	uint32_t CTC_MATCH_OVERFLOW = ( (F_CPU * period_ms) / 8000) - 1 ;

	/* Store ticks count into specific registers */
	OCR1AH = (uint8_t)(CTC_MATCH_OVERFLOW >> 8);
	OCR1AL = (uint8_t)(CTC_MATCH_OVERFLOW);

 	/* Set CTC mode, set clock/8 */
 	TCCR1B |= (1 << WGM12) | (1 << CS11);

 	/* Clear counter */
 	TCNT1 = 0;

 	/* Enable compare match interrupt */
 	TIMSK |= (1 << OCIE1A);
}


/*
 *  Perform saving task context on stack.
 *
 *  This routine saves all general purpose, special and stack 
 *  pointer registers values on stack, so we actually can suspend 
 *  task for a while. I use sts for reading _SP_ directly, because
 *  _SP_ is loaded with private variable - curren_task, so
 *  this value needs to be assigned to task control block in
 *  scheduler routine: port_SAVE_CONTEXT doesn't update stack_ptr in
 *  task control block automatically!
 */
#define port_SAVE_CONTEXT()									\
		asm volatile(	"push r0					\n\t"	\
						"in r0, __SREG__			\n\t"	\
						"cli						\n\t"	\
						"push r0					\n\t"	\
						"push r1					\n\t"	\
						"clr r1						\n\t"	\
						"push r2					\n\t"	\
						"push r3					\n\t"	\
						"push r4					\n\t"	\
						"push r5					\n\t"	\
						"push r6					\n\t"	\
						"push r7					\n\t"	\
						"push r8					\n\t"	\
						"push r9					\n\t"	\
						"push r10					\n\t"	\
						"push r11					\n\t"	\
						"push r12					\n\t"	\
						"push r13					\n\t"	\
						"push r14					\n\t"	\
						"push r15					\n\t"	\
						"push r16					\n\t"	\
						"push r17					\n\t"	\
						"push r18					\n\t"	\
						"push r19					\n\t"	\
						"push r20					\n\t"	\
						"push r21					\n\t"	\
						"push r22					\n\t"	\
						"push r23					\n\t"	\
						"push r24					\n\t"	\
						"push r25					\n\t"	\
						"push r26					\n\t"	\
						"push r27					\n\t"	\
						"push r28					\n\t"	\
						"push r29					\n\t"	\
						"push r30					\n\t"	\
						"push r31					\n\t"	\
						"in r0, __SP_L__			\n\t"	\
						"sts current_task, r0		\n\t"	\
						"in r0, __SP_H__			\n\t"	\
						"sts current_task + 1, r0	\n\t"	\
					);


/*
 *  Perform restoring task context.
 *
 *  In order to restore task context, we have to bring back all
 *  previously saved register values from stack.
 */
#define port_RESTORE_CONTEXT()								\
		asm volatile(	"lds r26, current_task		\n\t"	\
						"lds r27, current_task + 1	\n\t"	\
						"out __SP_L__, r26			\n\t"	\
						"out __SP_H__, r27			\n\t"	\
						"pop r31					\n\t"	\
						"pop r30					\n\t"	\
						"pop r29					\n\t"	\
						"pop r28					\n\t"	\
						"pop r27					\n\t"	\
						"pop r26					\n\t"	\
						"pop r25					\n\t"	\
						"pop r24					\n\t"	\
						"pop r23					\n\t"	\
						"pop r22					\n\t"	\
						"pop r21					\n\t"	\
						"pop r20					\n\t"	\
						"pop r19					\n\t"	\
						"pop r18					\n\t"	\
						"pop r17					\n\t"	\
						"pop r16					\n\t"	\
						"pop r15					\n\t"	\
						"pop r14					\n\t"	\
						"pop r13					\n\t"	\
						"pop r12					\n\t"	\
						"pop r11					\n\t"	\
						"pop r10					\n\t"	\
						"pop r9						\n\t"	\
						"pop r8						\n\t"	\
						"pop r7						\n\t"	\
						"pop r6						\n\t"	\
						"pop r5						\n\t"	\
						"pop r4						\n\t"	\
						"pop r3						\n\t"	\
						"pop r2						\n\t"	\
						"pop r1						\n\t"	\
						"pop r0						\n\t"	\
						"out __SREG__, r0			\n\t"	\
						"pop r0						\n\t"	\
					);


/*
 *  Macro switching stack pointer to RAMEND location.
 *
 *	This is done to kernel performs its task on a brand new
 *  stack region, not interfering with tasks private stack space.
 *  Since we don't have MSP/PSP, this routine was implemented.
 */					
#define port_SWITCH_TO_OS_STACK()							\
		asm volatile(	"lds r16,  ram_end			\n\t"	\
						"out __SP_L__, r16			\n\t"	\
						"lds r16, ram_end + 1		\n\t"	\
						"out __SP_H__, r16			\n\t"	\
					);


/* Run first task - var current_task must be set! */
void port_start_first_task( void ) NAKED_FUNCTION ;
void port_start_first_task( void ) {

	/* Restore context of first task */
	port_RESTORE_CONTEXT();

	/* Return to first task */
	asm volatile("ret");
}


/*
 *	Function called from ISR sys_tick routine.
 */
inline void yield_from_isr( void ) INLINE_FUNCTION ;
void yield_from_isr( void ) {

	/* Save context of current executed task */
	port_SAVE_CONTEXT();

	/* Switch stack pointer to RAMEND */
	port_SWITCH_TO_OS_STACK();

	/* Execute schedulers switching routine */
	os_proc_task_scheduler();
	
	/* Restore task context */
	port_RESTORE_CONTEXT();

	/* Return to new task */
	asm volatile("reti");
}


 /*
  *	 Sys_Tick timer routine.
  */
//ISR(TIMER1_COMPA_vect, ISR_NAKED) {
SysTick_Handler(TIMER_VECT, TIMER_NAKED) {
	  
	/* Switch Tasks In ISR */
	yield_from_isr();

}
