#include "lib/types.h"
#include "arch/i386/gdt.h"
#include "arch/i386/idt.h"
#include "src/drivers/vga.h"
#include "src/drivers/keyboard.h"
#include "src/terminal/terminal.h"

void kmain(void){
    gdt_init();
    remap_pic();
    idt_init();
    init_vga();
    init_keyboard();
    __asm__ volatile("sti");
    clear_screen_vga();

    output_invitation();

    while(1) {
        terminal();
        __asm__ volatile("hlt"); 
    }
}