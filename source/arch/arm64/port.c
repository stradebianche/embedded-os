#include "port.h"
#include "scheduler.h"

/* Private variables ---------------------------------------------------------*/

/* Store current task _SP_ address */
static stack_type_t *current_task;

/* This to help solving RAMEND forbidden access from ISR routine - dunno why not workin */
//volatile static const unsigned int ram_end = RAMEND;


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
	// *return_stack_top = ( malloc( stack_size ) + stack_size - 1 );
	static uint64_t stack_pool[10][256];
	static uint8_t it = 0;

	*return_stack_top = &stack_pool[it++][128];
}


/* Prepare tasks tack for first use */
stack_type_t * port_init_task_stack( stack_type_t *stack_top, task_func_t func_handler) {

	/* Initialize register R0 */
	*stack_top = 0x00;
	stack_top--;

	*stack_top = 0x01;
	stack_top--;

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

	*stack_top = 0x24;
	stack_top--;
	*stack_top = 0x25;
	stack_top--;

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

	/* spsr */
	*stack_top = 0x00;
	stack_top--;

	/* elr_el1 */
	*stack_top = 0x00;
	stack_top--;	

	return stack_top;
}


/* Resets system timer */
void port_reset_timer( void ) {

}


/* Init system timer */
void port_init_system_timer( uint8_t period_ms ) {

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
			asm volatile ("nop");

/*
 *  Perform restoring task context.
 *
 *  In order to restore task context, we have to bring back all
 *  previously saved register values from stack.
 */
#define port_RESTORE_CONTEXT()								\
			asm volatile ("nop");

/*
 *  Macro switching stack pointer to RAMEND location.
 *
 *	This is done to kernel performs its task on a brand new
 *  stack region, not interfering with tasks private stack space.
 *  Since we don't have MSP/PSP, this routine was implemented.
 */					
#define port_SWITCH_TO_OS_STACK()							\
			asm volatile ("nop");
		// asm volatile(	"lds r16,  ram_end			\n\t"	\
		// 				"out __SP_L__, r16			\n\t"	\
		// 				"lds r16, ram_end + 1		\n\t"	\
		// 				"out __SP_H__, r16			\n\t"	\
		// 			);


/* Run first task - var current_task must be set! */
void port_start_first_task( void ) NAKED_FUNCTION ;
void port_start_first_task( void ) {

	/* Restore context of first task */
	port_RESTORE_CONTEXT();

	/* Return to first task */
//	asm volatile("ret");
}


/*
 *	Function called from ISR sys_tick routine.
 */
inline void yield_from_isr( void ) INLINE_FUNCTION ;
void yield_from_isr( void ) {

	/* Save context of current executed task */
	// port_SAVE_CONTEXT();

	// /* Switch stack pointer to RAMEND */
	// port_SWITCH_TO_OS_STACK();

	// /* Execute schedulers switching routine */
	// os_proc_task_scheduler();
	
	// /* Restore task context */
	// port_RESTORE_CONTEXT();

	/* Return to new task */
//	asm volatile("reti");
}


 /*
  *	 Sys_Tick timer routine.
  */
void SysTick_Handler(void) {

	/* Switch Tasks In ISR */
	yield_from_isr();

}
