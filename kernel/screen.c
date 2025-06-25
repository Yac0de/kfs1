#include "screen.h"

#define VIDEO_ADDRESS 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0F

// Write character at position (row, col)
void put_char_at(char c, int row, int col) {
    char* video_memory = (char*) VIDEO_ADDRESS;
    int offset = (row * MAX_COLS + col) * 2;

    video_memory[offset] = c;
    video_memory[offset + 1] = WHITE_ON_BLACK;
}

// Fill the screen with spaces
void clear_screen(void) {
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            put_char_at(' ', row, col);
        }
    }
}

// Print string starting from top-left, no cursor or newline management yet
void print(const char* str) {
    int row = 0;
    int col = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (col >= MAX_COLS) {
            row++;
            col = 0;
        }
        if (row >= MAX_ROWS)
            break;

        put_char_at(str[i], row, col);
        col++;
    }
}

