#include "terminal.h"
#include "printf.h"

void main() {
    terminal_init();

    printf("Booting KFS1...\n");
    printf("Integer: %d\n", -42);
    printf("Hex: %x\n", 3735928559); // 0xDEADBEEF
    printf("Char: %c\n", '!');
    printf("String: %s\n", "done");
}

