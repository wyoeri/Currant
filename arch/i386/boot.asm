section .multiboot
    align 4
    dd 0x1BADB002
    dd 0x03
    dd -(0x1BADB002 + 0x03)
section .stack  ;.bss
    align 4096
stack_bottom:
    resb 65536
stack_top:
section .text
    global _start
    extern kmain
_start:
    cli
    mov esp, stack_top
    push eax 
    push ebx 
    call kmain
.loop:
    hlt
    jmp .loop