#include "vga.h"

static uint8_t* const vga_buffer = (uint8_t*)0xB8000;
static terminalcursor tcs;

void init_vga(void){
    tcs.x = 0;
    tcs.y = 0;
}

// linear output
void print_char_vga(const char c, uint8_t color_vga){
    if('\n' == c){
        tcs.x = 0; 
        tcs.y++;
    }
    else if('\t' == c){
        tcs.x += 4;
    }
    else if('\b' == c && tcs.x > 0){
        tcs.x--;
        uint32_t offset = calc_offset_vga();
        vga_buffer[offset] = '\0';
        vga_buffer[offset + 1] = color_vga;
    }
    else{
        uint32_t offset = calc_offset_vga();
        vga_buffer[offset] = c;
        vga_buffer[offset + 1] = color_vga;
        tcs.x++;
    }

    if (tcs.x >= 80) {
        tcs.x = 0;
        tcs.y++;
    }

    if (tcs.y >= 25) {
        clear_screen_vga();
        tcs.x = 0;
        tcs.y = 0;
    }
}

void print_str_vga(const char* s, uint8_t color_vga){
    while('\0' != *s){
        print_char_vga(*s, color_vga);
        s++;
    }
}

// output by coordinates
void print_by_coord_char_vga(const char c, uint8_t color_vga, int y, int x){
    tcs.y = y;
    tcs.x = x;
    print_char_vga(c, color_vga);
}

void print_by_coord_str_vga(const char* s, uint8_t color_vga, int y, int x){
    tcs.y = y;
    tcs.x = x;
    while('\0' != *s){
        print_char_vga(*s, color_vga);
        s++;
    }
}

// other
void clear_screen_vga(uint8_t color_vga){
    for(int i = 0; i < 80 * 25; i++){
        vga_buffer[i * 2] = ' ';
        vga_buffer[i * 2 + 1] = color_vga;
    }
    tcs.x = 0;
    tcs.y = 0;
}

uint32_t calc_offset_vga(void){
    return (tcs.y * 80 + tcs.x) * 2;
}