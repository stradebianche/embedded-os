#ifndef OS_CONFIG_H_
#define OS_CONFIG_H_

/*
 *	Software version
 */
#define _OS_VERSION_	1.0	


/* Max number of running tasks */
#define MAX_TASK	5


/* Stack size definitions. */
#define STACK_MIN_SIZE	64 * 8
#define STACK_MID_SIZE	128 * 8
#define STACK_MAX_SIZE	256 * 8


/* Switching frequency */
//TODO
#define SWITCHING_PERIOD_MS	20


#endif /* OS_CONFIG_H_ */
