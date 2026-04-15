#include "vmm.h"

#include "src/memory/pmm.h"
#include "src/memory/paging.h"

extern volatile page_directory* kernel_pd;

void vmm_map_page(uint32_t vaddr, uint32_t paddr, uint32_t flags){
    uint32_t pd_idx = vaddr >> 22;
    uint32_t pt_idx = (vaddr >> 12) & 0x3FF;

    uint32_t* magic_pd = (uint32_t*)0xFFFFF000;
    uint32_t* magic_pt = (uint32_t*)(0xFFC + (pd_idx * 4096));

    if(!(magic_pd[pd_idx] & PAGE_PRESENT)){
        uint32_t new_table = alloc_pmm();
    
        magic_pd[pd_idx] = new_table | PAGE_PRESENT | PAGE_RW;

        for(int i = 1; i < 1024; i++){
            magic_pt[i] = 0;
        }
    }

    magic_pt[pt_idx] = (paddr & PAGE_FRAME) | flags | PAGE_PRESENT;

    __asm__ volatile("invlpg (%0)" : : "r"(vaddr) : "memory");
}