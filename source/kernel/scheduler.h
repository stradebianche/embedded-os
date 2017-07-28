#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "task.h"
#include "os_config.h"

/* Types definitions ------------------------------------------------------- */

/* Task states */
typedef enum {
	TASK_STATE_RUNNING = 0,
	TASK_STATE_READY,
	TASK_STATE_WAIT
} task_state_t;


/* Function prototypes ------------------------------------------------------- */

/*
 *  Initializes system.
 */
void os_init_system( void );

/*
 *  Creates task defined by user.
 */
int os_create_task( task_func_t task_handler, size_t stack_size );

/*
 *  Starts executing first task from queue.
 */
void os_start_task_scheduler( void );

/*
 *  Performs task switch in ISR routine.
 */
void os_proc_task_scheduler( void );


#endif /* SCHEDULER_H_ */
