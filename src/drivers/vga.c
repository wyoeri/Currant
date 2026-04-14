#include "vga.h"

static uint8_t* const vga_buffer = (uint8_t*)0xB8000;

void put_vga(const char c, uint8_t color, int x, int y){
    uint32_t offset = (y * 80 + x) * 2;
    vga_buffer[offset] = c;
    vga_buffer[offset + 1] = color;
}