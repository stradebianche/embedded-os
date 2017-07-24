#ifndef TASK_H_
#define TASK_H_

/* Includes */
#include <inttypes.h>
#include <stdlib.h>
#include "port_macro.h"

/* Definition of user thread function:
	 -function pointer
	 -no params
	 -must return int value
 */
typedef int (* task_func_t)(void);


/* Task tcb type definition */
//typedef eTaskControlBlock * task_t;


/*
 *  Structure describing tasks properties. 
 *
 *  Contains all necessary parameters like stack pointers values,
 *  descriptors or task function handler.
 */
typedef struct eTaskControlBlock_s {

	/* Pointer to current value of task Stack Pointer */
	stack_type_t *stack_ptr;

	/* Pointer to a highest stack address 
	of a local task - top of stack */
	stack_type_t *stack_top;

	/* Task function handler */
	task_func_t func_handler;

} eTaskControlBlock;


/*
 *  User function for creating new task. 
 *
 *  Function creates task with @func_handler code and stack of size @stack_size.
 *  Task is automatically added to task queue.
 */
eTaskControlBlock * osTaskCreate(task_func_t func_handler, size_t stack_size);


/*
 *  Delete task and free memory. 
 *
 *  This is not implemented yet.
 */
int osTaskDelete(eTaskControlBlock *deletedTaskControlBlock);


#endif /* TASK_H_ */