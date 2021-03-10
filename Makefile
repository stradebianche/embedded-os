# Makefile

all: main

clean:
	-rm main.elf
	-rm *.o

main:
	aarch64-none-elf-gcc -ggdb boot.S startup.c main.c -o main.elf -T ./linker.ld
