#ifndef SCREEN_H
#define SCREEN_H

// Write character at specific position with color
void put_char_at(char c, int row, int col, char attribute);

// Clear screen (default color)
void clear_screen(void);

// Move hardware cursor
void set_cursor(int row, int col);
int get_cursor(void);

#endif

