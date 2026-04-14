#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "arch/i386/isr.h"
#include "lib/other/types.h"

#define KEYBOARD_BUFFER_SIZE 256

extern char kbd_us[128];

void init_keyboard(void);
void handler_keyboard(void);
int read_keyboard(void);
int get_scancode_keyboard(void);

#endif