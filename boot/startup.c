extern unsigned int __bss_start__;
extern unsigned int __bss_end__;

extern int main(void);

static void _clear_section(unsigned int *__start, unsigned int *__end)
{
	unsigned int *next = (unsigned int *)__start;

	while (next < __end) {
		*next++ = 0x0;
	}
}

void _startup(void);
void _startup(void)
{
	_clear_section(&__bss_start__, &__bss_end__);

	main();

	for(;;);
}
