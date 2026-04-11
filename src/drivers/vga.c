#include "vga.h"

static uint8_t* const vga_buffer = (uint8_t*)0xB8000;
static struct terminalcurpos tcp;

void init_vga(void){
    tcp.x = 0;
    tcp.y = 0;
}

// linear output
void print_char_vga(const char c){
    if(tcp.y >= 80 || tcp.x >= 25){tcp.y = 0; tcp.x++;}
    if(tcp.x >= 25){clear_screen_vga(); tcp.x = 0;}

    if('\n' == c){
        tcp.y = 0; 
        tcp.x++;
    }
    else if('\t' == c){
        tcp.y += 4;
    }
    else if('\b' == c){
        tcp.y--;
        uint32_t offset = calc_offset_vga();
        vga_buffer[offset] = '\0';
        vga_buffer[offset + 1] = WHITE_COLOR;
    }
    else{
        uint32_t offset = calc_offset_vga();
        vga_buffer[offset] = c;
        vga_buffer[offset + 1] = WHITE_COLOR;
        tcp.y++;
    }
}

void print_str_vga(const char* s){
    while('\0' != *s){
        print_char_vga(*s);
        s++;
    }
}

// output by coordinates
void print_by_coord_char_vga(const char c, int y, int x){
    tcp.y = y;
    tcp.x = x;
    print_char_vga(c);
}

void print_by_coord_str_vga(const char* s, int y, int x){
    tcp.y = y;
    tcp.x = x;
    while('\0' != *s){
        print_char_vga(*s);
        s++;
    }
}

// output in hex format
void print_hex_vga(uint32_t n){
    static const char table_hex[] = "0123456789ABCDEF";
    
    print_str_vga("0x");
    
    for(int i = 28; i >= 0; i -= 4){
        int x = (n >> i) & 0x0F;
        print_char_vga(table_hex[x]);
    }
}

// other
void clear_screen_vga(void){
    for(int i = 0; i < 80 * 25; i++){
        vga_buffer[i * 2] = ' ';
        vga_buffer[i * 2 + 1] = WHITE_COLOR;
    }
    tcp.x = 0;
    tcp.y = 0;
}

uint32_t calc_offset_vga(void){
    return (tcp.x * 80 + tcp.y) * 2;
}