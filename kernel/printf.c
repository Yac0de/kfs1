#include "printf.h"
#include "terminal.h"
#include "utils.h"
#include <stdarg.h>

void printf(const char* format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[32];

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            // Next character determines format specifier
            i++;
            char spec = format[i];

            switch (spec) {
                case 's': {
                    // String
                    char* s = va_arg(args, char*);
                    terminal_print(s);
                    break;
                }
                case 'd': {
                    // Signed decimal
                    int n = va_arg(args, int);
                    itoa(n, buffer);
                    terminal_print(buffer);
                    break;
                }
                case 'x': {
                    // Hexadecimal (with "0x" prefix)
                    unsigned int n = va_arg(args, unsigned int);
                    xtoa(n, buffer, 1);
                    terminal_print(buffer);
                    break;
                }
                case 'c': {
                    // Single character
                    char c = (char) va_arg(args, int);  // promoted
                    terminal_putchar(c);
                    break;
                }
                case '%': {
                    // Literal '%'
                    terminal_putchar('%');
                    break;
                }
                default: {
                    // Unknown specifier: print as-is
                    terminal_putchar('%');
                    terminal_putchar(spec);
                    break;
                }
            }
        } else {
            // Regular character
            terminal_putchar(format[i]);
        }
    }

    va_end(args);
}
