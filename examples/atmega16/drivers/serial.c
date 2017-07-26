 #include <avr/io.h>
 #include "serial.h"

void uart_init(uint32_t	baud) {

	 uint16_t _ubr = ( (F_CPU) / (baud * 16UL) - 1 );

	 UBRRH = (uint8_t) (_ubr >> 8);
	 UBRRL = (uint8_t) _ubr;

	 UCSRB = (1 << RXEN) | (1 << TXEN);

	 /* Frame format: 8n1 */
	 UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
 }

 void sendchar(char c) {
	 
	 while( !(UCSRA & (1<<UDRE)) );
	 UDR = c;
 }

 void putstr(const char *s ) {

	 while (*s)
	 sendchar(*s++);
 }

 uint8_t get_char(void) {

	 while( (UCSRA & (1<<RXC)) == 0 );
	 return UDR;
 }