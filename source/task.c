#include "task.h"
#include "port.h"

/*
 *  This function creates task defined by user.
 */
 eTaskControlBlock * osTaskCreate(task_func_t func_handler, size_t stack_size) {

	/* Allocate memory for storing new Task Control Block - malloc style */
	eTaskControlBlock *new_task = ( eTaskControlBlock * ) malloc ( sizeof( eTaskControlBlock ) );

 	/* Allocate memory block for local stack - malloc style */
	port_allocate_stack_memory( &new_task->stack_top, stack_size );
	
	/* Initialize task stack with default values 
	Update task stack pointer to new value */
	new_task->stack_ptr = port_init_task_stack( new_task->stack_top, func_handler );
	
	/* Assign function address to TCB's task handler */
	new_task->func_handler = func_handler;

	/* Return pointer to new Task Control Block */
	return new_task;
 }


/* 
 *  This function deletes task from system memory.
 */
int osTaskDelete( eTaskControlBlock *deletedTaskControlBlock ) {


	return 0;
}
