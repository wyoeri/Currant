#include "commands.h"

#include "src/drivers/vga.h"
#include "arch/i386/io.h"
#include "src/terminal/terminal.h"

void reboot(void){
    outb(0x64, 0xFE);
    while(1){__asm__ volatile("hlt");}
}

void help(void){
    print_str_vga("Creator: wyoeri\n");
    print_str_vga("Version: v0.0.1\n");
    print_str_vga("More information: https://github.com/wyoeri/Currant/tree/main \n");
}

void cat(void){
    print_str_vga("  /\\_/\\\n ( o.o )\n  > ^ <\n");
}

void panic(void){
    __asm__ volatile("ud2");
}

// installing the theme
void black_theme(void){
    set_theme_terminal(WHITE_COLOR, BLACK_COLOR);
    clear_screen_vga();
}

void white_theme(void){
    set_theme_terminal(BLACK_COLOR, WHITE_COLOR);
    clear_screen_vga();
}

void red_theme(void){
    set_theme_terminal(BLACK_COLOR, RED_COLOR);
    clear_screen_vga();
}

void green_theme(void){
    set_theme_terminal(BLACK_COLOR, GREEN_COLOR);
    clear_screen_vga();
}