#include "terminal.h"
#include "screen.h"

#define MAX_ROWS 25
#define MAX_COLS 80

static int cursor_row = 0;
static int cursor_col = 0;

// Internal helper to move cursor to current position
static void update_cursor() {
    set_cursor(cursor_row, cursor_col);
}

// Clear terminal and reset cursor
void terminal_init(void) {
    clear_screen();
    cursor_row = 0;
    cursor_col = 0;
    update_cursor();
}

// Print string, support for '\n'
void terminal_print(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];

        if (c == '\n') {
            cursor_row++;
            cursor_col = 0;
        } else {
            put_char_at(c, cursor_row, cursor_col);
            cursor_col++;
            if (cursor_col >= MAX_COLS) {
                cursor_col = 0;
                cursor_row++;
            }
        }

        if (cursor_row >= MAX_ROWS) {
            // No scroll yet — stop here
            break;
        }

        update_cursor();
    }
}

