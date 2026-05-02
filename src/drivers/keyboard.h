#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "arch/i386/isr.h"
#include "lib/other/types.h"

#define KEYBOARD_BUFFER_SIZE 256

extern unsigned char kbd_us[128];
extern unsigned char kbd_us_upper[128]; 

void init_keyboard(void);
void handler_keyboard(void);
int read_keyboard(void);
char get_char_keyboard(void);
int get_scancode_keyboard(void);

#endif