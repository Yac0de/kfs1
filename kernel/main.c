#include "terminal.h"

void main() {
    terminal_init();

    terminal_print("Char-by-char:\n");

    const char* msg = "KFS1 is fun\n";
    for (int i = 0; msg[i] != '\0'; i++) {
        terminal_putchar(msg[i]);
    }
}

