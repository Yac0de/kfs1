[bits 32]
[extern main]                ; Reference to the kernel main function (in C)

section .multiboot
    align 4
    dd 0x1BADB002            ; Magic number required by Multiboot
    dd 0x00                  ; Flags
    dd -(0x1BADB002)         ; Checksum: -(magic + flags)

section .text
global _start
_start:
    call main                ; Call the C kernel entry point

.hang:
    cli                     ; Clear interrupts
    hlt                     ; Halt CPU
    jmp .hang               ; Infinite loop to prevent exiting

