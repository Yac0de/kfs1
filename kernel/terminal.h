#ifndef TERMINAL_H
#define TERMINAL_H

void terminal_init(void);

// Print string using default color
void terminal_print(const char* str);

// Print string using custom color attribute
void terminal_print_color(const char* str, char attribute);

#endif

