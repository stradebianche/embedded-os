INCLUDES += -I./drivers/include
INCLUDES += -I./drivers

OBJS += build/translation_tables.o

OBJS += build/main.o \
build/startup.o \
build/boot.o \
build/vectors.o \
build/irq_fiq_handler.o \
build/os_interrupt_handler.o \
build/exceptions.o \

OBJS += \
build/xilinx_uart_ps.o \
build/gicv2.o \
build/arch_timer.o \

CFLAG = -Wall -g -O0
CC = aarch64-none-elf-gcc
LIBS =
LINKER_PATH = ./boards/linker-ultrazed.ld
OUT = build

$(shell   mkdir -p $(OUT))

build/%.o: boards/%.S
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

build/%.o: boot/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

build/%.o: boot/%.S
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

build/%.o: drivers/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

build/%.o: drivers/%.S
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

image.elf:${OBJS}
	@echo 'Building target: $@'
	${CC} ${CFLAGS} -Wl,-T$(LINKER_PATH) ${INCLUDES} -o $@ ${OBJS} ${LIBS} -Wl,--print-memory-usage
	@echo  'Done.'

clean:
	-rm -rf *.o image.elf ${OUT}
