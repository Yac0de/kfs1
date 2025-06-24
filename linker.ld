ENTRY(_start)  /* Define the kernel entry point */

SECTIONS {
    . = 1M;     /* Kernel will be loaded at 0x00100000 (1MB) */

    .text : {
        *(.multiboot)    /* Multiboot header must be in the .text section */
        *(.text*)        /* All code sections */
    }

    .rodata : { *(.rodata*) }  /* Read-only data */
    .data   : { *(.data*) }    /* Initialized data */
    .bss    : { *(.bss*) }     /* Uninitialized data (zeroed) */
}

