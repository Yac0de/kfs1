#ifndef PRINTF_H
#define PRINTF_H

/**
 * Prints a formatted string to the terminal.
 * Supports a minimal subset of C's printf:
 *   - %s: string
 *   - %d: signed decimal integer
 *   - %x: hexadecimal (with 0x prefix)
 *   - %c: character
 *   - %%: literal '%'
 *
 * @param format Format string
 * @param ... Variadic arguments matching the format specifiers
 */
void printf(const char* format, ...);

#endif
