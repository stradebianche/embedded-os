INCLUDES += -I../../source/arch/arm64
INCLUDES += -I../../source/drivers/include
INCLUDES += -I../../source/drivers

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
LINKER_PATH = ../../source/boards/linker-ultrazed.ld
OUT = build

$(shell   mkdir -p $(OUT))

build/%.o: ./%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

build/%.o: ../../source/boards/%.S
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

build/%.o: ../../source/arch/arm64/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

build/%.o: ../../source/arch/arm64/%.S
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

build/%.o: ../../source/drivers/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

build/%.o: ../../source/drivers/%.S
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

image.elf:${OBJS}
	@echo 'Building target: $@'
	${CC} ${CFLAGS} -Wl,-T$(LINKER_PATH) ${INCLUDES} -o $@ ${OBJS} ${LIBS} -Wl,--print-memory-usage
	@echo  'Done.'

clean:
	-rm -rf *.o image.elf ${OUT}
