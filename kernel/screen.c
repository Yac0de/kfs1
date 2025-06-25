#include "screen.h"

#define VIDEO_ADDRESS 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0F

// Put a character on screen at given row and column
void put_char_at(char c, int row, int col) {
    char* video_memory = (char*) VIDEO_ADDRESS;
    int offset = (row * MAX_COLS + col) * 2;

    video_memory[offset] = c;
    video_memory[offset + 1] = WHITE_ON_BLACK;
}

// Clear the screen by filling it with spaces
void clear_screen(void) {
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            put_char_at(' ', row, col);
        }
    }
}

