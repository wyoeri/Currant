ENTRY(_start)

SECTIONS
{
    . = 0x100000;

    .multiboot ALIGN(4K) :
    {
        *(.multiboot)
    }

    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.text)
    }

    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

     .stack BLOCK(4K) : ALIGN(4K)
    {
        *(.stack) 
    }

    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
        ebss = .;
    }

    /DISCARD/ :
    {
        *(.comment)
        *(.note.*)
    }
}