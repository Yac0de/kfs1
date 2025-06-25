// kernel/main.c

#include "terminal.h"

void main() {
    terminal_init();

    char buffer[32];

    for (int i = 0; i < 60; i++) {
        // Convert int to string manually (no sprintf yet)
        int num = i;
        int idx = 0;

        if (num == 0) {
            buffer[idx++] = '0';
        } else {
            while (num > 0 && idx < 30) {
                buffer[idx++] = '0' + (num % 10);
                num /= 10;
            }

            // Reverse the string
            for (int j = 0; j < idx / 2; j++) {
                char tmp = buffer[j];
                buffer[j] = buffer[idx - 1 - j];
                buffer[idx - 1 - j] = tmp;
            }
        }

        buffer[idx++] = '\n';
        buffer[idx] = '\0';

        terminal_print(buffer);
    }
}

