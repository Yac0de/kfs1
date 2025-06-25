#include "screen.h"
#include <stdint.h>

#define VIDEO_ADDRESS 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0F

#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

// Function prototypes for low-level port I/O
void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);

// Write character at (row, col)
void put_char_at(char c, int row, int col) {
    char* video_memory = (char*) VIDEO_ADDRESS;
    int offset = (row * MAX_COLS + col) * 2;

    video_memory[offset] = c;
    video_memory[offset + 1] = WHITE_ON_BLACK;
}

// Read current cursor position from VGA ports
int get_cursor(void) {
    outb(REG_SCREEN_CTRL, 14);
    int offset = inb(REG_SCREEN_DATA) << 8;

    outb(REG_SCREEN_CTRL, 15);
    offset += inb(REG_SCREEN_DATA);

    return offset * 2; // Each character cell is 2 bytes
}

// Set cursor position to (row, col)
void set_cursor(int row, int col) {
    int offset = row * MAX_COLS + col;

    outb(REG_SCREEN_CTRL, 14);
    outb(REG_SCREEN_DATA, (offset >> 8) & 0xFF);
    outb(REG_SCREEN_CTRL, 15);
    outb(REG_SCREEN_DATA, offset & 0xFF);
}

// Write char at cursor and advance cursor
void put_char(char c) {
    int offset = get_cursor();

    char* video_memory = (char*) VIDEO_ADDRESS;
    video_memory[offset] = c;
    video_memory[offset + 1] = WHITE_ON_BLACK;

    offset += 2;

    int row = (offset / 2) / MAX_COLS;
    int col = (offset / 2) % MAX_COLS;
    set_cursor(row, col);
}

// Clear the screen and reset cursor
void clear_screen(void) {
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            put_char_at(' ', row, col);
        }
    }
    set_cursor(0, 0);
}

// Print string from current cursor
void print(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        put_char(str[i]);
    }
}

// Low-level port output
void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

// Low-level port input
uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

