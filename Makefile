INCLUDES += -I./drivers/include
INCLUDES += -I./drivers

OBJS += boards/translation_tables.o

OBJS += boot/main.o \
boot/startup.o \
boot/boot.o \
boot/vectors.o \
boot/irq_fiq_handler.o \
boot/os_interrupt_handler.o \

OBJS += \
./drivers/xilinx_uart_ps.o \
./drivers/gicv2.o

CFLAG = -Wall -g -O0
CC = aarch64-none-elf-gcc
LIBS =
LINKER_PATH = ./boards/linker-ultrazed.ld

boards/%.o: boards/%.S
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

boot/%.o: boot/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

boot/%.o: boot/%.S
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

drivers/%.o: drivers/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

image.elf:${OBJS}
	@echo 'Building target: $@'
	${CC} ${CFLAGS} -Wl,-T$(LINKER_PATH) ${INCLUDES} -o $@ ${OBJS} ${LIBS}

clean:
	-rm -rf *.o image.elf ${OBJS}

