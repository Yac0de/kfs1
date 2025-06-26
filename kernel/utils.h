#ifndef UTILS_H
#define UTILS_H

// Integer to ASCII (signed)
void itoa(int value, char* str);

// Unsigned int to ASCII (decimal)
void utoa(unsigned int value, char* str);

// Unsigned int to HEX string (prefixed or not)
void xtoa(unsigned int value, char* str, int prefix);

// String length
int strlen(const char* str);

#endif

