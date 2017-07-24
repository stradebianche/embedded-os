 #include "task_queue.h"


int task_queue_init(Queue *tQueue, eTaskControlBlock **queue_buffer, size_t queue_size) {

	tQueue->head = 0;
	tQueue->tail = 0;
	tQueue->size = queue_size;
	tQueue->buffer = queue_buffer;
	tQueue->number_of_elements = 0;

	return 0;
}


int task_queue_insert(eTaskControlBlock *new_task, Queue *tQueue) {

	if(tQueue->number_of_elements >= tQueue->size) {
		return 1;
	}

	tQueue->buffer[tQueue->tail] = new_task;
	tQueue->number_of_elements++;

	if(tQueue->tail >= tQueue->size - 1)
	tQueue->tail = 0;
	else
	tQueue->tail++;

	return 0;
}


eTaskControlBlock* task_queue_take(Queue *tQueue) {

	if( tQueue->number_of_elements < 1 ) {
		return 0;
	}

	eTaskControlBlock * t_tcb = tQueue->buffer[tQueue->head];

	if(tQueue->head >= tQueue->size - 1)
		tQueue->head = 0;
	else
		tQueue->head++;

	tQueue->number_of_elements--;

	return t_tcb;
}