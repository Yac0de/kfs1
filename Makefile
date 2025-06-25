# Output binary names
TARGET = kernel.bin
ISO = kernel.iso
BUILD = build

# Compilers and flags
CC = gcc
CFLAGS = -m32 -ffreestanding -fno-pic -fno-builtin -fno-stack-protector -nostdlib
NASM = nasm
NASMFLAGS = -f elf32

# GRUB configuration path
GRUB_CFG = iso/boot/grub/grub.cfg

# Source files (explicit, no wildcard)
SRC_C = kernel/main.c kernel/screen.c kernel/terminal.c
SRC_ASM = boot/boot.asm

# Object files (mapped manually)
OBJ_C = $(BUILD)/kernel/main.o $(BUILD)/kernel/screen.o $(BUILD)/kernel/terminal.o
OBJ_ASM = $(BUILD)/boot/boot.o

# Default target
all: $(ISO)

# Compile C files
$(BUILD)/kernel/%.o: kernel/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile ASM files
$(BUILD)/boot/%.o: boot/%.asm
	@mkdir -p $(dir $@)
	$(NASM) $(NASMFLAGS) $< -o $@

# Link the final kernel binary
$(TARGET): $(OBJ_C) $(OBJ_ASM)
	$(CC) -m32 -nostdlib -T linker.ld -o $@ $^

# Create ISO image with GRUB
$(ISO): $(TARGET) $(GRUB_CFG)
	mkdir -p iso/boot
	cp $< iso/boot/kernel.bin
	grub-mkrescue -o $@ iso

# Clean build artifacts
clean:
	rm -rf $(BUILD) $(TARGET) $(ISO)

# Full clean including copied kernel
fclean: clean
	rm -f iso/boot/kernel.bin

# Rebuild everything from scratch
re: fclean all

.PHONY: all clean fclean re

