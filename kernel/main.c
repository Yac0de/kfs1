#include "terminal.h"

void main() {
    terminal_init();

    terminal_print("Booting...\n");

    terminal_print_color("SUCCESS\n", 0x2F); // Green on white
    terminal_print_color("WARNING\n", 0x6F); // Yellow on white
    terminal_print_color("ERROR\n", 0x4F);   // Red on white
}

