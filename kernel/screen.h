#ifndef SCREEN_H
#define SCREEN_H

// VGA color codes (foreground & background)
#define BLACK       0x0
#define BLUE        0x1
#define GREEN       0x2
#define CYAN        0x3
#define RED         0x4
#define MAGENTA     0x5
#define BROWN       0x6
#define LIGHT_GRAY  0x7
#define DARK_GRAY   0x8
#define LIGHT_BLUE  0x9
#define LIGHT_GREEN 0xA
#define LIGHT_CYAN  0xB
#define LIGHT_RED   0xC
#define PINK        0xD
#define YELLOW      0xE
#define WHITE       0xF

// Combine foreground and background into a VGA attribute byte
#define COLOR(fg, bg) ((bg << 4) | (fg))

/**
 * @brief Write a character at a specific screen location with color.
 * @param c Character to display
 * @param row Row number (0 to MAX_ROWS-1)
 * @param col Column number (0 to MAX_COLS-1)
 * @param attribute VGA attribute byte (foreground + background color)
 */
void put_char_at(char c, int row, int col, char attribute);

/**
 * @brief Clears the entire screen using default color and spaces.
 */
void clear_screen(void);

/**
 * @brief Move the hardware VGA cursor to a specific location.
 * @param row Target row (0 to MAX_ROWS-1)
 * @param col Target column (0 to MAX_COLS-1)
 */
void set_cursor(int row, int col);

#endif
