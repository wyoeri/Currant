#include "paging.h"

static volatile uint32_t page_directory[1024] __attribute__((aligned(4096))) = {0};
static volatile uint32_t page_table[1024] __attribute__((aligned(4096))) = {0};

void init_paging(void){
    for(int i = 0; i < 1024; i++){
        page_table[i] = (i * 4096) | 3;
    }

    page_directory[0] = ((uint32_t)page_table) | 3;

    for(int i = 1; i < 1024; i++){
        page_directory[i] = 0 | 2;
    }

    load_page_directory(page_directory);
    enable_paging();
}

void load_page_directory(volatile uint32_t* directory){
    __asm__ volatile("mov %0, %%cr3" : : "r"(directory));
}

void enable_paging(void){
    uint32_t cr0;
    __asm__ volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000;
    __asm__ volatile("mov %0, %%cr0" : : "r"(cr0));
}