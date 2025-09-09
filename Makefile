# ========= Colors ===========
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[1;33m
NC      = \033[0m

# ========= Output ===========
TARGET     = kernel.bin
ISO        = kernel.iso
BUILD      = build
GRUB_CFG   = iso/boot/grub/grub.cfg

# ========= Sources ==========
SRC_C_FILES  = main screen terminal utils printf
SRC_C        = $(addprefix kernel/, $(addsuffix .c, $(SRC_C_FILES)))
OBJ_C        = $(SRC_C:kernel/%.c=$(BUILD)/kernel/%.o)

SRC_ASM      = boot/boot.asm
OBJ_ASM      = $(SRC_ASM:boot/%.asm=$(BUILD)/boot/%.o)

# ========= Tools ============
CC        = gcc
CFLAGS    = -m32 -ffreestanding -fno-pic -fno-builtin -fno-stack-protector -nostdlib -nodefaultlibs
NASM      = nasm
NASMFLAGS = -f elf32

GRUB_MODULES = iso9660 multiboot \
			   normal part_acorn part_amiga part_apple \
			   part_bsd part_dfly part_dvh part_gpt part_msdos \
			   part_plan part_sun part_sunpc
GRUB_EXCLUDED_FILES = boot/grub/x86_64-efi \
					  boot/grub/locale \
					  System mach_kernel \
					  efi efi.img

# ========= Default ==========
all: $(ISO)

# ========= Compilation Rules ==========
$(BUILD)/kernel/%.o: kernel/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/boot/%.o: boot/%.asm
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Assembling $<$(NC)"
	@$(NASM) $(NASMFLAGS) $< -o $@

# ========= Linking ==========
$(TARGET): $(OBJ_C) $(OBJ_ASM)
	@echo "$(GREEN)Linking kernel -> $@$(NC)"
	@$(CC) -m32 -nostdlib -T linker.ld -o $@ $^

# ========= ISO Creation ==========
$(ISO): $(TARGET) $(GRUB_CFG)
	@mkdir -p iso/boot
	@cp $< iso/boot/kernel.bin
	@echo "$(GREEN)Creating bootable ISO -> $@$(NC)"
	grub-mkrescue \
		--themes="" \
		--install-modules "$(GRUB_MODULES)" \
		-o $@ iso -- \
		-rm_r $(GRUB_EXCLUDED_FILES)

# ========= Run ==========
run: $(ISO)
	@echo "$(GREEN)Launching QEMU with $<$(NC)"
	qemu-system-i386 -cdrom $<

# ========= Cleaning Rules ==========
clean:
	@echo "$(RED)Cleaning build files$(NC)"
	@rm -rf $(BUILD) $(TARGET) $(ISO)

fclean: clean
	@echo "$(RED)Cleaning ISO kernel copy$(NC)"
	@rm -f iso/boot/kernel.bin

re: fclean all

.PHONY: all clean fclean re run
