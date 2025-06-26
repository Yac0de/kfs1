#ifndef TERMINAL_H
#define TERMINAL_H

// Initialize the terminal (clear + reset cursor)
void terminal_init(void);

// Print a string with default color
void terminal_print(const char* str);

// Print a string with custom color
void terminal_print_color(const char* str, char attribute);

// Print a single character (default color)
void terminal_putchar(char c);

// Print a single character (custom color)
void terminal_putchar_color(char c, char attribute);

#endif

