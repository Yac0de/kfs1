#include "terminal.h"
#include "screen.h"

#define MAX_ROWS 25
#define MAX_COLS 80
#define DEFAULT_COLOR 0x0F

static int cursor_row = 0;
static int cursor_col = 0;

static void update_cursor() {
    set_cursor(cursor_row, cursor_col);
}

static void scroll_if_needed(char attribute) {
    if (cursor_row < MAX_ROWS)
        return;

    for (int row = 1; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            char* video_memory = (char*)0xB8000;
            int from = (row * MAX_COLS + col) * 2;
            int to = ((row - 1) * MAX_COLS + col) * 2;
            video_memory[to] = video_memory[from];
            video_memory[to + 1] = video_memory[from + 1];
        }
    }

    for (int col = 0; col < MAX_COLS; col++) {
        put_char_at(' ', MAX_ROWS - 1, col, attribute);
    }

    cursor_row = MAX_ROWS - 1;
}

void terminal_init(void) {
    clear_screen();
    cursor_row = 0;
    cursor_col = 0;
    update_cursor();
}

void terminal_print_color(const char* str, char attribute) {
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];

        if (c == '\n') {
            cursor_row++;
            cursor_col = 0;
        } else {
            put_char_at(c, cursor_row, cursor_col, attribute);
            cursor_col++;
            if (cursor_col >= MAX_COLS) {
                cursor_col = 0;
                cursor_row++;
            }
        }

        scroll_if_needed(attribute);
        update_cursor();
    }
}

// Default version (white on black)
void terminal_print(const char* str) {
    terminal_print_color(str, DEFAULT_COLOR);
}

