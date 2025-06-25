#ifndef TERMINAL_H
#define TERMINAL_H

// Initialize the terminal (clear + reset cursor)
void terminal_init(void);

// Print a string with basic formatting (handles \n)
void terminal_print(const char* str);

#endif

