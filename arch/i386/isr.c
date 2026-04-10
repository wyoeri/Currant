#include "isr.h"

#include "src/drivers/vga.h"

static int in_handler = 0;

static const char* error_message[] = {
    "Divide by zero", // 0
    "Debug Exception", // 1
    "Non Maskable Interrupt", // 2
    "Breakpoint", // 3
    "Into Detected Overflow", // 4
    "BOUND Range Exceeded", // 5
    "Invalid Opcode (Undefined Opcode)", // 6
    "Device Not Available (No Math Coprocessor)", // 7
    "Double Fault", // 8
    "Coprocessor Segment Overrun", // 9
    "Invalid TSS", // 10
    "Segment Not Present", // 11
    "Stack-Segment Fault", // 12
    "General Protection", // 13
    "Page Fault", // 14
    "Unknown Interrupt", // 15
    "Coprocessor Fault", // 16
    "Alignment Check", // 17
    "Machine Check", // 18
    "SIMD Floating-Point Exception", // 19
    "Virtualization Exception", // 20
    "Control Protection Exception", // 21
    "Reserved", // 22
    "Reserved", // 23
    "Reserved", // 24
    "Reserved", // 25
    "Reserved", // 26
    "Reserved", // 27
    "Reserved", // 28
    "Reserved", // 29
    "Reserved", // 30
    "Reserved", // 31
    "System timer", // 32
    "Keyboard Controller", // 33
};

void isr_handler(struct registers* regs){
    if(regs->int_no > 32 && regs->int_no < 47){
        if(regs->int_no >= 40) {outb(0xA0, 0x20);}
        outb(0x20, 0x20);
        return;
    }

    if(regs->int_no == 32) {
        outb(0x20, 0x20);
        return;
    }
    
    asm volatile("cli");

    if(in_handler){__asm__ volatile("hlt");}
    in_handler = 1;

    clear_screen_vga();
    print_str_vga("KERNEL PANIC!\n");
    if(regs->int_no < 32){
        print_str_vga("EXCEPTION: ");
        print_str_vga(error_message[regs->int_no]);
        print_hex_vga(regs->int_no);
    }
    else{
        print_str_vga("UNKNOWN EXCEPTION!\n");
    }

    for(;;);
}