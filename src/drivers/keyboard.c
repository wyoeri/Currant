#include "keyboard.h"

#include "lib/data_structures/ringbuffer.h"
#include "arch/i386/io.h"

static uint8_t kbd_mem[KEYBOARD_BUFFER_SIZE];
static ring_buffer kbd_rb;

void init_keyboard(void){
    init_buffer(&kbd_rb, kbd_mem, KEYBOARD_BUFFER_SIZE);
    while(inb(0x64) & 0x01){inb(0x60);}
}

void handler_keyboard(void){
    int scancode = read_keyboard();

    if(scancode != -1){
        pushrb(&kbd_rb, (uint8_t)scancode);
    }
    
    outb(0x20, 0x20);
}

int read_keyboard(void){
    uint8_t status = inb(0x64);

    if(!(status & 0x01)){return -1;}

    uint8_t scancode = inb(0x60);

    return (int)scancode;
}

int get_scancode_keyboard(void){
    return poprb(&kbd_rb);
}

char kbd_us[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t', 
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0
};