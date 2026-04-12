#ifndef VGA_H
#define VGA_H

#include "lib/types.h"

#define BLACK_COLOR 0x00
#define WHITE_COLOR 0x0F
#define RED_COLOR 0x04
#define GREEN_COLOR 0x02
#define BLUE_COLOR 0x01
#define BROWN_COLOR 0x06
#define YELLOW_COLOR 0x0E
#define ORANGE_COLOR 0x06
#define VIOLET_COLOR 0x05

typedef struct{
    int x;
    int y;
} terminalcursor;

void init_vga(void);

// linear output
void print_char_vga(const char c, uint8_t color_vga);
void print_str_vga(const char* s, uint8_t color_vg);

// output by coordinates
void print_by_coord_char_vga(const char c, uint8_t color_vga, int y, int x);
void print_by_coord_str_vga(const char* s, uint8_t color_vga, int y, int x);

// other
void clear_screen_vga(uint8_t color_vga);
uint32_t calc_offset_vga(void);

#endif