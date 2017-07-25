/* Define to prevent recursive inclusion --------------------------------------*/
#ifndef PORT_H_
#define PORT_H_


/* Includes ------------------------------------------------------------------ */
#include <inttypes.h>
#include "port_macro.h"
#include "task.h"


/* Macro definitions --------------------------------------------------------- */

/* Stack definitions. */
#define STACK_MIN_SIZE	64
#define STACK_MID_SIZE	128
#define STACK_MAX_SIZE	256


/* Function prototypes ------------------------------------------------------- */

/*
 *	Get current task stack pointer from port layer.
 *
 *  This is something like a "middleman" between port layer and
 *  kernel code, as we store current task stack pointer in a
 *  local variable.
 */
stack_type_t * port_get_current_stack_pointer( void );


/*
 *  Set new value for task stack pointer. 
 *
 *  This need to be done before performing restore_context procedure.
 */
void port_set_new_stack_pointer( stack_type_t *new_task_sp );		


/*
 *  Start executing first task from queue. 
 *
 *	If task queue is empty program goes to idle_task as default. This 
 *  to be called in os_start_scheduler procedure, after initialising 
 *  all components.
 */
void port_start_first_task( void ) NAKED_FUNCTION ;


/*
 *  Initializes hardware timer as sys_tick timer.
 *
 *	Timer that needs to be initialized in order to perform periodic
 *  switches between os tasks. An yield_from_isr procedure is called
 *  inside of given timer.
 */
void port_init_system_timer( uint8_t period_ms );


/*
 *  Allocates memory block in RAM for tasks stack.
 *
 *	Currently this is done by using malloc functions. Further, more 
 *  distinguish implementations are still ahead.
 */
void port_allocate_stack_memory( stack_type_t **return_stack_address, size_t stack_size );


/*
 *  Initializes task stack, as it was just after context_save procedure.
 *
 *	Port specific task stack initialization. 
 */
stack_type_t *port_init_task_stack( stack_type_t *stack_top, task_func_t func_handler );


/*
 *  Resets sys_tick timer.
 */
void port_reset_timer( void );


/* Port critical section  management */
// 
//			TO BE DONE
//
/* - - - - - - - - - - - - - - - - - */

#endif /* PORT_H_ */
