#ifndef VGA_H
#define VGA_H

#include "lib/other/types.h"

#define BLACK_COLOR 0x00
#define WHITE_COLOR 0x0F
#define RED_COLOR 0x04
#define GREEN_COLOR 0x02
#define BLUE_COLOR 0x01
#define BROWN_COLOR 0x06
#define YELLOW_COLOR 0x0E
#define ORANGE_COLOR 0x06
#define VIOLET_COLOR 0x05

void put_vga(const char c, uint8_t color, int x, int y);

#endif