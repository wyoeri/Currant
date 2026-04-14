#include "arch/i386/multiboot.h"
#include "arch/i386/gdt.h"
#include "arch/i386/idt.h"
#include "lib/other/types.h"
#include "src/memory/paging.h"
#include "src/memory/pmm.h"
#include "src/drivers/keyboard.h"
#include "src/terminal/terminal.h"

void kmain(multiboot_info* mbi, uint32_t signature_grub){
    if(0x2BADB002 != signature_grub){__asm__ volatile("hlt"); return;}
    init_gdt();
    remap_pic();
    init_idt();
    init_terminal();
    init_pmm(mbi);
    init_paging();
    init_keyboard();
    __asm__ volatile("sti");

    clear_screen();
    output_invitation();

    while(1) {
        input_processing_terminal();
        __asm__ volatile("hlt"); 
    }
}