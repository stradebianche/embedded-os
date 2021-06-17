#ifndef XILINX_UART_PS_H_
#define XILINX_UART_PS_H_

#include <stdbool.h>

void uartps_putc(char data);
void uartps_puts(const char *s);
bool uartps_getc(char *data);

#endif
