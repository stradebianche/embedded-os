OBJS += boards/translation_tables.o

boards/%.o: ./boards/%.S
	aarch64-none-elf-gcc -c -o $@ $<

