#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Convert a signed integer to a decimal string.
 * @param value The integer to convert.
 * @param str Output buffer (must be large enough).
 */
void itoa(int value, char* str);

/**
 * @brief Convert an unsigned integer to a decimal string.
 * @param value The unsigned integer to convert.
 * @param str Output buffer (must be large enough).
 */
void utoa(unsigned int value, char* str);

/**
 * @brief Convert an unsigned integer to a hexadecimal string.
 * @param value The value to convert.
 * @param str Output buffer (must be large enough).
 * @param prefix Whether to add '0x' prefix (non-zero = yes).
 */
void xtoa(unsigned int value, char* str, int prefix);

/**
 * @brief Calculate the length of a null-terminated string.
 * @param str Input string.
 * @return Number of characters before null terminator.
 */
int strlen(const char* str);

#endif
