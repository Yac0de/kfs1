void main() {
    char* video_memory = (char*)0xb8000;

    // Each character cell on screen is 2 bytes: [char][attribute]
    // Attribute 0x0F = white on black
    video_memory[0] = '4';  // First character
    video_memory[1] = 0x0F; // Color attribute
    video_memory[2] = '2';  // Second character
    video_memory[3] = 0x0F; // Color attribute
}

