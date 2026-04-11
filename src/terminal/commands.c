#include "commands.h"

#include "src/drivers/vga.h"
#include "arch/i386/io.h"

void reboot(void){
    outb(0x64, 0xFE);
    while(1){__asm__ volatile("hlt");}
}

void help(void){
    print_str_vga("Creator: wyoeri\n");
    print_str_vga("Version: v0.0.1\n");
}

void cat(void){
    print_str_vga("  /\\_/\\\n ( o.o )\n  > ^ <\n");
}

void panic(void){
    __asm__ volatile("ud2");
}