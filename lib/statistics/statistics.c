#include "statistics.h"

#include "src/terminal/terminal.h"
#include "lib/print/print.h"

void print_info(const char* name, uint32_t val){
    print_str(name);
    print_str(": ");
    print_hex(val);
    print_char('\n');
}

void output_registers_info(const registers* rg){
    print_info("EAX", rg->eax);
    print_info("ECX", rg->ecx);
    print_info("EDX", rg->edx);
    print_info("EBX", rg->ebx);
    print_info("EBP", rg->ebp);
    print_info("ESI", rg->esi);
    print_info("EDI", rg->edi);
    print_info("EIP", rg->eip);
}

void output_error(const registers* rg, const char* msg){
    print_str(msg);
    print_str(error_messages_isr[rg->int_no]);
    print_char('\n');
    print_info("ERROR CODE", rg->err_code);
}

void output_context(const registers* rg){
    print_info("USERESP", rg->useresp);
    print_info("DS", rg->ds);
    print_info("CS", rg->cs);
    print_info("SS", rg->ss);
}

void output_flags(const registers* rg){
    print_info("EFLAGS", rg->eflags);
}