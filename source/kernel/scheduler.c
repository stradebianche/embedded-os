#include "scheduler.h"
#include "task_queue.h"
#include "port.h"
#include "os_config.h"

/* Private variables ---------------------------------------------------------*/

/* Buffer for storing tasks in queue. */
static eTaskControlBlock * queue_buffer[ MAX_TASK ];

/* Instance of task queue. */
static Queue task_queue;

/* Pointer to given task control block. */
static eTaskControlBlock *tcb;

/* Declaration of idle task handler function. */
static void idle_task( void );


/*
 *  This functions initialize all kernel components.
 */
void os_init_system( void ) {

	port_init_system_timer( SWITCHING_PERIOD_MS );

	task_queue_init( &task_queue, queue_buffer, MAX_TASK );
}


/*
 *  This is a function called by user in order to create new task.
 */
int os_create_task( task_func_t func_handler, size_t stack_size ) {

	task_queue_insert( osTaskCreate( func_handler, stack_size ), &task_queue );

	return 0;
}


/*
 *  This function is called by user when tasks have been created,
 *	system is initialized and now is time to start party.
 */
void os_start_task_scheduler( void ) {

	/* No tasks to execute so simply run idle task */
	if( task_queue.number_of_elements < 1 ) {

		//TODO	- only blocking now	
		for(;;);
		
	} else {
		/* Get first task in queue */
		tcb = task_queue_take( &task_queue );
		/* Send tasks stack pointer to port layer */
		port_set_new_stack_pointer( tcb->stack_ptr );
	}

	/* Call port layer to perform scheduler running */
	port_start_first_task();

	/* This should never execute */
	for(;;);
}


/*
 *  This function is called periodically in ISR routine to get new task from queue.
 */
void os_proc_task_scheduler( void ) {

	/* Get stack pointer value from currently saved task */
	tcb->stack_ptr = port_get_current_stack_pointer();
	/* Put that value at the end of queue */
	task_queue_insert( tcb, &task_queue );

	/* Take next task from queue - round robin algorithm */
	tcb = task_queue_take( &task_queue );
	/* Set stack pointer value to port layer */
	port_set_new_stack_pointer( tcb->stack_ptr );
}


/*
 *	TODO:
 */
void os_task_yield( void ) {

}


/*
 *  Implementation of idle task.
 */
 void idle_task(void) {
	for(;;) {
		asm volatile ("nop");
	}
 }
