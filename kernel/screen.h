#ifndef SCREEN_H
#define SCREEN_H

// Write a character at (row, col) with a fixed attribute
void put_char_at(char c, int row, int col);

// Clear the entire screen
void clear_screen(void);

// Print a null-terminated string starting from the top-left corner
void print(const char* str);

#endif

