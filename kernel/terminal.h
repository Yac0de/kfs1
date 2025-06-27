#ifndef TERMINAL_H
#define TERMINAL_H

/**
 * @brief Initialize the terminal: clears screen and resets cursor to (0,0).
 */
void terminal_init(void);

/**
 * @brief Print a null-terminated string with default color.
 * @param str The string to display.
 */
void terminal_print(const char* str);

/**
 * @brief Print a null-terminated string with custom color.
 * @param str The string to display.
 * @param attribute VGA attribute byte (foreground + background).
 */
void terminal_print_color(const char* str, char attribute);

/**
 * @brief Print a single character with default color.
 * @param c Character to display.
 */
void terminal_putchar(char c);

/**
 * @brief Print a single character with custom color.
 * @param c Character to display.
 * @param attribute VGA attribute byte (foreground + background).
 */
void terminal_putchar_color(char c, char attribute);

#endif
