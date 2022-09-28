#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#define MAX_EXCEPTIONS 195U

int exc_execute(unsigned int int_id, void *arg);
int exc_register_handler(unsigned int int_id, void(*fp)(void *arg));
void exc_enable(void);
void exc_disable(void);

#endif
