#ifndef PMM_H
#define PMM_H

#include "lib/other/types.h"
#include "arch/i386/multiboot.h"

extern uint32_t ebss;

typedef struct{
    uint32_t* bitmap;
    uint32_t total_frames;
    uint32_t used_frames;
    uint32_t bitmap_size;
    uint32_t last_index;
} pmm_control_t;

void init_pmm(multiboot_info_t* mbi);
void set_frame_pmm(uint32_t addr);
void unset_frame_pmm(uint32_t addr);
void init_pmm_region(uint32_t addr, uint32_t len);
void lock_pmm_region(uint32_t addr, uint32_t len);
uint32_t get_end_kernel_area(void);
uint32_t alloc_pmm(void);

#endif