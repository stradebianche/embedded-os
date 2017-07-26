/*
 *  Quick configure and run example.
 *		Uart drivers required.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>

/* Drivers include */
#include "serial.h"

/* System includes */
#include "scheduler.h"


/* First thread handler function */
int thread1(void) {
	for(;;) {
		/* This for ensure atomic operation */
		cli();
		putstr("task 1   . \r\n");
		sei();
		_delay_ms(500);
	}
	return 0;
}

/* Second thread handler function */
int thread2(void) {
	while(1) {
		cli();
		putstr("task 2 . \r\n");
		sei();
		_delay_ms(1000);
	}
	return 0;
}


int main(void) {

	/* Init serial port with 230400 baud rate */
	uart_init( 230400 );
	/* Put some welcome string */
	putstr("\r\nOS Initializing...\r\n");

	/* Initialize system components */
	os_init_system();

	/* Add some tasks with minimal stack size */
	os_create_task(thread1, STACK_MIN_SIZE);
	os_create_task(thread2, STACK_MIN_SIZE);

	/* Start executing tasks */
	os_start_task_scheduler();

	/* This should never execute */
    while (1) {
		/* Handle error here */
    }
}
