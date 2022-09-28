#include "exceptions.h"
#include <stdio.h>

static void (*exceptions_table[MAX_EXCEPTIONS + 1])(void *arg);

int exc_execute(unsigned int int_id, void *arg)
{
    if (exceptions_table[int_id] == NULL) {
        return -1;
    }

    (exceptions_table[int_id])(arg);
    return 0;
}

int exc_register_handler(unsigned int int_id, void (*fp)(void *arg))
{
    if (fp == NULL || int_id > MAX_EXCEPTIONS) {
        return -1;
    }

    exceptions_table[int_id] = fp;
    return 0;
}

void exc_enable(void)
{
    asm volatile ("msr daifclr, #0x0f");
}

void exc_disable(void)
{
    asm volatile ("msr daifset, #0x0f");
}
