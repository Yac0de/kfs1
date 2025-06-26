#include "terminal.h"
#include "screen.h"
#include "printf.h"

void main() {
    terminal_init();

    // === Mandatory part ===
    terminal_print("42");

    // === Bonus 1: Scroll and cursor demo ===
    // for (int i = 0; i < 30; i++) {
    //     printf("Line %d: Hello from KFS1!\n", i);
    // }

    // === Bonus 2: Colors support (foreground and background) ===
    // printf("\nColor preview:\n");

    // // Foreground only (text color on black background)
    // for (int fg = 1; fg <= 15; fg++) {
    //     terminal_print_color("Text color\n", COLOR(fg, BLACK));
    // }

    // // Background only (white text on various backgrounds)
    // for (int bg = 1; bg <= 7; bg++) {
    //     terminal_print_color("Background color\n", COLOR(WHITE, bg));
    // }

    // === Bonus 3: Printf helper ===
    // printf("Signed int: %d\n", -1234);
    // printf("Unsigned hex: %x\n", 0xBADC0DE);
    // printf("Char: %c\n", '@');
    // printf("String: %s\n", "Kernel loaded.");
}
