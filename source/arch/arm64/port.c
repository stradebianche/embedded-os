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
stack_type_t * port_init_task_stack(stack_type_t *stack_top, task_func_t func_handler) {

	/* Initialize registers */
	stack_top = (stack_type_t *)((uintptr_t)stack_top & (uintptr_t)0xfffffff0);

	stack_top--;
	*stack_top = 0x01;
	stack_top--;
	*stack_top = 0x00;

	stack_top--;
	*stack_top = 0x03;
	stack_top--;
	*stack_top = 0x02;

	stack_top--;
	*stack_top = 0x05;
	stack_top--;
	*stack_top = 0x04;

	stack_top--;
	*stack_top = 0x07;
	stack_top--;
	*stack_top = 0x06;

	stack_top--;
	*stack_top = 0x09;
	stack_top--;
	*stack_top = 0x08;

	stack_top--;
	*stack_top = 0x11;
	stack_top--;
	*stack_top = 0x10;

	stack_top--;
	*stack_top = 0x13;
	stack_top--;
	*stack_top = 0x12;

	stack_top--;
	*stack_top = 0x15;
	stack_top--;
	*stack_top = 0x14;

	stack_top--;
	*stack_top = 0x17;
	stack_top--;
	*stack_top = 0x16;

	stack_top--;
	*stack_top = 0x19;
	stack_top--;
	*stack_top = 0x18;

	stack_top--;
	*stack_top = 0x21;
	stack_top--;
	*stack_top = 0x20;

	stack_top--;
	*stack_top = 0x23;
	stack_top--;
	*stack_top = 0x22;

	stack_top--;
	*stack_top = 0x25;
	stack_top--;
	*stack_top = 0x24;

	stack_top--;
	*stack_top = 0x27;
	stack_top--;
	*stack_top = 0x26;

	stack_top--;
	*stack_top = 0x29;
	stack_top--;
	*stack_top = 0x28;

	/* elr_el3 */
	stack_top--;
	*stack_top = (uintptr_t)func_handler;

	/* link register */
	stack_top--;
	*stack_top = (uintptr_t)func_handler;

	/* cptr_el3 */
	stack_top--;
	*stack_top = 0x0;

	/* spsr_el3 */
	stack_top--;
	*stack_top = 0x0;

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
 *  pointer registers values on stack.
 */
#define port_SAVE_CONTEXT()										  \
			asm volatile (  "stp x0, x1, [sp, #-16]!		\n\t" \
							"stp x2, x3, [sp, #-16]!		\n\t" \
							"stp x4, x5, [sp, #-16]!		\n\t" \
							"stp x6, x7, [sp, #-16]!		\n\t" \
							"stp x8, x9, [sp, #-16]!		\n\t" \
							"stp x10, x11, [sp, #-16]!		\n\t" \
							"stp x12, x13, [sp, #-16]!		\n\t" \
							"stp x14, x15, [sp, #-16]!		\n\t" \
							"stp x16, x17, [sp, #-16]!		\n\t" \
							"stp x18, x19, [sp, #-16]!		\n\t" \
							"stp x20, x21, [sp, #-16]!		\n\t" \
							"stp x22, x23, [sp, #-16]!		\n\t" \
							"stp x24, x25, [sp, #-16]!		\n\t" \
							"stp x26, x27, [sp, #-16]!		\n\t" \
							"stp x28, x29, [sp, #-16]!		\n\t" \
																  \
							"mrs x0, elr_el3				\n\t" \
						    "stp x30, x0, [sp, #-16]!		\n\t" \
																  \
						    "mrs x0, spsr_el3				\n\t" \
						    "mrs x1, cptr_el3				\n\t" \
						    "stp x0, x1, [sp, #-16]!		\n\t" \
																  \
							"ldr x0, =current_task			\n\t" \
							"mov x1, sp						\n\t" \
							"str x1, [x0]  					\n\t" \
							);

/*
 *  Perform restoring task context.
 *
 *  In order to restore task context, we have to bring back all
 *  previously saved register values from stack.
 */
#define port_RESTORE_CONTEXT()									  \
			asm volatile (	"ldr x0, =current_task			\n\t" \
							"ldr x1, [x0]  					\n\t" \
							"mov sp, x1						\n\t" \
							"ldp x0, x1, [sp], #16 			\n\t" \
							"ldp x30, x2, [sp], #16 		\n\t" \
							"msr cptr_el3, x1 				\n\t" \
							"msr spsr_el3, x0  				\n\t" \
							"msr elr_el3, x2 				\n\t" \
							"ldp x28, x29, [sp], #16 		\n\t" \
							"ldp x26, x27, [sp], #16 		\n\t" \
							"ldp x24, x25, [sp], #16 		\n\t" \
							"ldp x22, x23, [sp], #16 		\n\t" \
							"ldp x20, x21, [sp], #16 		\n\t" \
							"ldp x18, x19, [sp], #16 		\n\t" \
							"ldp x16, x17, [sp], #16 		\n\t" \
							"ldp x14, x15, [sp], #16 		\n\t" \
							"ldp x12, x13, [sp], #16 		\n\t" \
							"ldp x10, x11, [sp], #16 		\n\t" \
							"ldp x8, x9, [sp], #16			\n\t" \
							"ldp x6, x7, [sp], #16 			\n\t" \
							"ldp x4, x5, [sp], #16 			\n\t" \
							"ldp x2, x3, [sp], #16 			\n\t" \
							"ldp x0, x1, [sp], #16 			\n\t" \
							);

/*
 *  Macro switching stack pointer to RAMEND location.
 *
 *	This is done to kernel performs its task on a brand new
 *  stack region, not interfering with tasks private stack space.
 *  Since we don't have MSP/PSP, this routine was implemented.
 */					
#define port_SWITCH_TO_OS_STACK()							\
			asm volatile ("nop");


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
