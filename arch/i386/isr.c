#include "isr.h"

#include "arch/i386/io.h"
#include "kernel/kernel_panic.h"
#include "src/drivers/keyboard.h"
#include "src/drivers/timer.h"

void isr_handler(registers_t* rg){
    if(rg->int_no >= 32 && rg->int_no < 47){
        if(33 == rg->int_no){
            handler_keyboard();
        }

        if(32 == rg->int_no){
            handler_timer();
        }
        
        if(rg->int_no >= 40) {outb(0xA0, 0x20);}

        outb(0x20, 0x20);
        return;
    }

    kernel_panic(rg);

    for(;;);
}