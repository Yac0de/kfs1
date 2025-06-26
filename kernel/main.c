#include "terminal.h"
#include "screen.h"

void main() {
    terminal_init();

    terminal_print_color("INFO\n", COLOR(LIGHT_GREEN, BLACK));
    terminal_print_color("DEBUG\n", COLOR(CYAN, BLACK));
    terminal_print_color("ERROR\n", COLOR(WHITE, RED));
}

