#include "utils.h"

int strlen(const char* str) {
    int len = 0;
    while (str[len] != '\0') len++;
    return len;
}

void itoa(int value, char* str) {
    if (value < 0) {
        *str++ = '-';
        utoa(-value, str);
    } else {
        utoa(value, str);
    }
}

void utoa(unsigned int value, char* str) {
    char buffer[16];
    int i = 0;

    if (value == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    while (value > 0) {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    }

    // Reverse
    for (int j = 0; j < i; j++) {
        str[j] = buffer[i - j - 1];
    }
    str[i] = '\0';
}

void xtoa(unsigned int value, char* str, int prefix) {
    char buffer[16];
    int i = 0;

    if (value == 0) {
        if (prefix) {
            str[0] = '0';
            str[1] = 'x';
            str[2] = '0';
            str[3] = '\0';
        } else {
            str[0] = '0';
            str[1] = '\0';
        }
        return;
    }

    while (value > 0) {
        int digit = value % 16;
        buffer[i++] = digit < 10 ? '0' + digit : 'A' + (digit - 10);
        value /= 16;
    }

    int offset = 0;
    if (prefix) {
        str[0] = '0';
        str[1] = 'x';
        offset = 2;
    }

    for (int j = 0; j < i; j++) {
        str[offset + j] = buffer[i - j - 1];
    }
    str[offset + i] = '\0';
}

