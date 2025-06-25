// Clear the screen by writing spaces to the entire video memory
void clear_screen() {
    char* video_memory = (char*)0xb8000;
    
    // There are 80 columns * 25 rows = 2000 character cells
    for (int i = 0; i < 80 * 25; i++) {
        video_memory[i * 2] = ' ';      // Character to display
        video_memory[i * 2 + 1] = 0x0F; // Attribute: white on black
    }
}

// Kernel entry point (called from boot.asm)
void main() {
    clear_screen();  // Wipe previous content from screen (e.g. GRUB message)

    char* video_memory = (char*)0xb8000;

    // Write '4'
    video_memory[0] = '4';
    video_memory[1] = 0x0F;

    // Write '2'
    video_memory[2] = '2';
    video_memory[3] = 0x0F;
}

