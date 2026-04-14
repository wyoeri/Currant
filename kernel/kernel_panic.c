#include "kernel_panic.h"

#include "lib/statistics/statistics.h"
#include "src/terminal/terminal.h"

static int in_handler = 0;

void kernel_panic(registers* rg){
    asm volatile("cli");

    if(in_handler){__asm__ volatile("hlt");}
    in_handler = 1;

    set_theme_terminal(0x00, 0x04);

    clear_screen();
    print_str("KERNEL PANIC!\n");
    print_str("A fatal exception has occurred\n");
    print_str("System halted to prevent damage\n");
    print_str("Please reboot!\n\n");
    print_str("Information:\n");

    if(rg->int_no < 34){
        output_error(rg, "EXCEPTION: ");
    }
    else{
        output_error(rg, "UNKNOWN EXCEPTION!");
    }

    output_registers_info(rg);
    output_flags(rg);
    output_context(rg);
}