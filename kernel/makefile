TARGET := kernel.elf

LDFLAGS := -ffreestanding -T ./arch/i386/linker.ld -nostdlib -mcmodel=kernel -lgcc

DEFINES := KERNEL KERNEL_DEBUG QEMU_DEBUGGING

SRC_DIRS = . ./arch/i386 ../lib/libcore ../lib/libc

include ../common.mk

$(TARGET): $(OBJECTS)
	@echo "LD $@"; $(LD) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

all: $(TARGET)
