#include "screen.h"
#include <stdint.h>

#define VIDEO_ADDRESS 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define DEFAULT_COLOR 0x0F

#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

// Low-level function to send a byte to an I/O port
void outb(uint16_t port, uint8_t val);

// Low-level function to read a byte from an I/O port
uint8_t inb(uint16_t port);

void put_char_at(char c, int row, int col, char attribute) {
    // Get pointer to VGA memory
    char* video_memory = (char*) VIDEO_ADDRESS;

    // Calculate offset: each cell is 2 bytes (char + attribute)
    int offset = (row * MAX_COLS + col) * 2;

    // Write character and its color
    video_memory[offset] = c;
    video_memory[offset + 1] = attribute;
}

void clear_screen(void) {
    // Fill all cells with space character and default color
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            put_char_at(' ', row, col, DEFAULT_COLOR);
        }
    }
}

void set_cursor(int row, int col) {
    int offset = row * MAX_COLS + col;

    // High byte of offset → register 14
    outb(REG_SCREEN_CTRL, 14);
    outb(REG_SCREEN_DATA, (offset >> 8) & 0xFF);

    // Low byte of offset → register 15
    outb(REG_SCREEN_CTRL, 15);
    outb(REG_SCREEN_DATA, offset & 0xFF);
}

/**
 * @brief Retrieve the current cursor position in VGA memory offset (in bytes).
 * @return Offset from VIDEO_ADDRESS (in bytes)
 */
static int get_cursor(void) {
    outb(REG_SCREEN_CTRL, 14);
    int offset = inb(REG_SCREEN_DATA) << 8;

    outb(REG_SCREEN_CTRL, 15);
    offset += inb(REG_SCREEN_DATA);

    // Multiply by 2 to get actual memory offset in bytes
    return offset * 2;
}

void outb(uint16_t port, uint8_t val) {
    // Sends the byte 'val' to the I/O port 'port' using inline assembly.
    // 'a' specifies that 'val' is placed in the AL register.
    // 'Nd' allows using an immediate value or DX register for the port.
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

uint8_t inb(uint16_t port) {
    uint8_t ret;
    // Reads a byte from the I/O port 'port' into variable 'ret'.
    // '=a'(ret): output operand, value goes into AL then stored in 'ret'
    // 'Nd'(port): input operand, port number to read from
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}
