INCLUDES += -I./drivers/include
INCLUDES += -I./drivers

OBJS += boards/translation_tables.o

OBJS += boot/main.o \
boot/startup.o \
boot/boot.o \
boot/vectors.o \

OBJS += \
./drivers/xilinx_uart_ps.o

CFLAG = -Wall -g -O0
CC = aarch64-none-elf-gcc
LIBS =
LINKER_PATH = ./boards/linker-ultrazed.ld

boards/%.o: boards/%.S
	$(CC) $(CFLAGS) -c $(INCLUDES) -o $@ $<

boot/%.o: boot/%.c
	$(CC) $(INCLUDES) -c -o $@ $<

boot/%.o: boot/%.S
	$(CC) $(INCLUDES) -c -o $@ $<

image.elf:${OBJS}
	@echo 'Building target: $@'
	${CC} ${CFLAGS} -Wl,-T$(LINKER_PATH) ${INCLUDES} -o $@ ${OBJS} ${LIBS}

clean:
	-rm -rf *.o image.elf ${OBJS}

