# Kernel From Scratch - KFS1 Project

## Table of Contents

1. [Project Overview](#1-project-overview)
2. [Project Structure](#2-project-structure)
3. [Build & Run Instructions](#3-build--run-instructions)
4. [Expectations and Constraints](#4-expectations-and-constraints)
5. [Toolchain & Compilation Flags](#5-toolchain--compilation-flags)
6. [Kernel Features](#6-kernel-features)
7. [Pedagogical Notes](#7-pedagogical-notes)
8. [Conclusion](#8-conclusion)

---

## 1. Project Overview

The **KFS1 (Kernel From Scratch)** project aims to create a minimal 32-bit kernel from scratch that can boot using **GRUB** and comply with the **Multiboot Specification**.

The kernel must:

* Boot with GRUB using a proper Multiboot header.
* Display **"42"** on the screen (mandatory).
* Remain under **10 MB** in size.
* Provide a minimal runtime environment (screen driver, terminal abstraction, basic utils).

This project introduces key low-level concepts:

* Bootloaders and Multiboot headers.
* Linker scripts and memory layout.
* VGA text mode programming.
* Writing a freestanding kernel in **C + Assembly**.

---

## 2. Project Structure

```
kfs1
├── boot
│   └── boot.asm          # Multiboot header + kernel entry (_start)
├── iso
│   └── boot
│       └── grub
│           └── grub.cfg  # GRUB configuration
├── kernel
│   ├── main.c            # Kernel entry point (C)
│   ├── printf.c/.h       # Minimal printf implementation
│   ├── screen.c/.h       # VGA driver (low-level screen control)
│   ├── terminal.c/.h     # Terminal abstraction (cursor, scroll, colors)
│   ├── utils.c/.h        # Helper functions (itoa, utoa, xtoa, strlen)
├── linker.ld             # Linker script for memory layout
└── Makefile              # Build system (GCC, NASM, GRUB ISO, QEMU)
```

---

## 3. Build & Run Instructions

### Environment Setup

Make sure you have the following installed:

```bash
sudo apt update
sudo apt install gcc nasm grub-pc-bin xorriso qemu-system-x86 make
```

### Build Kernel and ISO

```bash
make
```

This produces:

* `kernel.bin` → the compiled kernel
* `kernel.iso` → a bootable ISO image with GRUB

### Run in QEMU

```bash
make run
```

This launches QEMU and boots the kernel ISO.

### Clean Builds

```bash
make clean   # Remove build artifacts
make fclean  # Full clean (also removes ISO + kernel)
make re      # Full rebuild
```

---

## 4. Expectations and Constraints

* The kernel must be **Multiboot compliant** (verified by GRUB).
* The binary size must stay under **10 MB**.
* Code must be **freestanding** (compiled without libc/stdlib).
* Assembly (`boot.asm`) sets up Multiboot and jumps into C `main()`.
* Displaying `"42"` is the mandatory deliverable.

---

## 5. Toolchain & Compilation Flags

### Compiler: `gcc`

* `-m32` → Force 32-bit mode.
* `-ffreestanding` → No assumptions about standard library.
* `-fno-pic -fno-builtin -fno-stack-protector` → Disable unwanted optimizations.
* `-nostdlib -nodefaultlibs` → Do not link system libraries.

### Assembler: `nasm`

* `-f elf32` → Output 32-bit ELF objects.

### Linker: `ld`

* Controlled via `linker.ld`.
* Kernel is loaded at `0x00100000` (1MB).

---

## 6. Kernel Features

### Mandatory:

* ✅ Multiboot-compliant boot sector.
* ✅ GRUB boots kernel.
* ✅ Kernel prints **"42"** to the screen.

### Bonus (implemented):

* Scroll and cursor management.
* VGA color support (foreground/background).
* Minimal `printf` implementation supporting:

  * `%s` (string)
  * `%d` (signed integer)
  * `%x` (hexadecimal with 0x prefix)
  * `%c` (character)
  * `%%` (literal percent sign)

---

## 7. Pedagogical Notes

This project also serves as a learning ground for core systems programming concepts:

* **What is a Kernel?** A kernel is the central part of an operating system. It manages communication between hardware and software, handling resources such as CPU, memory, and devices. In this project, the kernel is minimal and only focuses on text output, but the principle remains the same: it is the core controller.
* **What is GRUB?** GRUB (GRand Unified Bootloader) is a widely used bootloader. It is responsible for loading operating systems into memory and transferring control to them. By supporting the Multiboot standard, GRUB can load different kernels in a uniform way.
* **Multiboot Header:** Ensures compatibility with bootloaders like GRUB. It defines how the kernel image should be loaded into memory.
* **Linker Script (`linker.ld`):** Controls memory layout and guarantees the kernel starts at the expected physical address (1MB).
* **I/O Ports:** Low-level operations (e.g., moving the cursor) require direct port access with `inb` and `outb` instructions.

These elements together illustrate the basics of kernel development: how to bootstrap a CPU into protected mode, manage memory, and communicate with hardware.

---

## 8. Conclusion

The **KFS1 kernel** demonstrates the foundations of operating system development: from a simple bootloader handoff to text rendering in VGA mode. While minimal, it highlights how low-level programming builds the bridge between hardware and software. This project can be extended towards more advanced topics like interrupts, memory management, and device drivers, making it a strong stepping stone into OS development.
