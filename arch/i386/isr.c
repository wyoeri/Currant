#include "isr.h"

#include "arch/i386/io.h"
#include "kernel/kernel_panic.h"
#include "src/drivers/keyboard.h"

void isr_handler(registers* rg){
    if(rg->int_no >= 32 && rg->int_no < 47){
        if(rg->int_no == 33){
            handler_keyboard();
        }

        if(rg->int_no == 32) {
            outb(0x20, 0x20);
            return;
        }

        if(rg->int_no >= 40) {outb(0xA0, 0x20);}

        outb(0x20, 0x20);
        return;
    }

    kernel_panic(rg);

    for(;;);
}