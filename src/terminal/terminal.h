#ifndef TERMINAL_H
#define TERMINAL_H

#include "lib/other/types.h"

#define TERMINAL_BUFFER_SIZE 128
#define DEFAULT_THEME 0x0F

void init_terminal(void);

// linear printing
void print_char(const char c);
void print_str(const char* s);

// printing by coordinates
void print_coord_char(const char c, const int x, const int y);
void print_coord_str(const char* s, const int x, const int y);

// processing user input
void input_processing_terminal(void);
void char_handler(const char c);

// working whith colors
uint8_t get_theme_terminal(void);
void set_theme_terminal(const uint8_t fg, const uint8_t bg);
uint8_t make_color_terminal(const uint8_t fg, const uint8_t bg);

// other
void output_invitation(void);
void clear_screen(void);

#endif