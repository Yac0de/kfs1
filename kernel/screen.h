#ifndef SCREEN_H
#define SCREEN_H

// Write character at specific position
void put_char_at(char c, int row, int col);

// Write character at current cursor position and advance cursor
void put_char(char c);

// Print a null-terminated string
void print(const char* str);

// Clear screen
void clear_screen(void);

// Move hardware cursor to given row and column
void set_cursor(int row, int col);

// Get current hardware cursor position (offset in video memory)
int get_cursor(void);

#endif

