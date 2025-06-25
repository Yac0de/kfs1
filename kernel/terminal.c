// kernel/terminal.c

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

// Scroll the screen up by one line if needed
static void scroll_if_needed() {
    if (cursor_row < MAX_ROWS)
        return;

    // Move all lines up
    for (int row = 1; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            // Read char from below
            int from_offset = (row * MAX_COLS + col) * 2;
            int to_offset = ((row - 1) * MAX_COLS + col) * 2;

            char* video_memory = (char*)0xB8000;
            video_memory[to_offset] = video_memory[from_offset];
            video_memory[to_offset + 1] = video_memory[from_offset + 1];
        }
    }

    // Clear last line
    for (int col = 0; col < MAX_COLS; col++) {
        put_char_at(' ', MAX_ROWS - 1, col);
    }

    // Adjust cursor
    cursor_row = MAX_ROWS - 1;
}

// Clear terminal and reset cursor
void terminal_init(void) {
    clear_screen();
    cursor_row = 0;
    cursor_col = 0;
    update_cursor();
}

// Print string with \n and scrolling
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

        scroll_if_needed();
        update_cursor();
    }
}

