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
            i++;
            char spec = format[i];

            switch (spec) {
                case 's': {
                    char* s = va_arg(args, char*);
                    terminal_print(s);
                    break;
                }
                case 'd': {
                    int n = va_arg(args, int);
                    itoa(n, buffer);
                    terminal_print(buffer);
                    break;
                }
                case 'x': {
                    unsigned int n = va_arg(args, unsigned int);
                    xtoa(n, buffer, 1); // with "0x"
                    terminal_print(buffer);
                    break;
                }
                case 'c': {
                    char c = (char) va_arg(args, int);
                    terminal_putchar(c);
                    break;
                }
                case '%': {
                    terminal_putchar('%');
                    break;
                }
                default: {
                    terminal_putchar('%');
                    terminal_putchar(spec);
                    break;
                }
            }
        } else {
            terminal_putchar(format[i]);
        }
    }

    va_end(args);
}

