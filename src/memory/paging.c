#include "paging.h"

#include "src/memory/pmm.h"

volatile page_directory* kernel_pd = NULL;

void init_paging(void){
    kernel_pd = (page_directory*)alloc_pmm();
    page_table* first_pt = (page_table*)alloc_pmm(); 

    for(int i = 0; i < 1024; i++){
        kernel_pd->pe[i] = 0;
        first_pt->pe[i] = 0;
    }
    
    for(int i = 1; i < 1024; i++){
        first_pt->pe[i] = (i * 4096) | PAGE_PRESENT | PAGE_RW;
    }
    
    kernel_pd->pe[0] = ((uint32_t)first_pt) | PAGE_PRESENT | PAGE_RW;
    kernel_pd->pe[1023] = ((uint32_t)kernel_pd) | PAGE_PRESENT | PAGE_RW;

    load_page_directory((uint32_t*)kernel_pd);
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