#ifndef SERIAL_H_
#define SERIAL_H_

void uart_init(uint32_t baud);

uint8_t get_char(void);

void sendchar(char c);

void putstr(const char *str);

#endif /* SERIAL_H_ */