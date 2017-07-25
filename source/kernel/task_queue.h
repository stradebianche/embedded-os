#ifndef QUEUE_H_
#define QUEUE_H_

#include "task.h"


/*
 *  Structure describing task queue. 
 *
 */
typedef struct Queue_s {
	
	eTaskControlBlock **buffer;

	uint8_t head;

	uint8_t tail;

	size_t size;

	/* Current quantity of elements in queue */
	uint8_t number_of_elements;

} Queue;


/*
 *  Initializes task queue. 
 */
int task_queue_init(Queue *tQueue, eTaskControlBlock **queue_buffer, size_t queue_size);


/*
 *  Insert task at end of queue. 
 */
int task_queue_insert(eTaskControlBlock *new_task, Queue *tQueue);


/*
 *  Take first task from queue.
 */
eTaskControlBlock* task_queue_take(Queue *tQueue);


#endif /* QUEUE_H_ */
