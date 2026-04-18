#include "pmm.h"

#define SYSTEM_INFO_SIZE 0x100000

static volatile pmm_control pmm;

void init_pmm(multiboot_info* mbi){
    uint32_t max_addr = get_max_address(mbi);
    pmm.bitmap = (uint32_t*)&ebss;
    pmm.total_frames = max_addr / 4096;
    pmm.bitmap_size = pmm.total_frames / 8;
    pmm.used_frames = pmm.total_frames;

    for(uint32_t i = 0; i < pmm.bitmap_size / 4; i++){
        pmm.bitmap[i] = 0xFFFFFFFF;
    }
    
    mmap_multiboot_info* mmap_mbi = (mmap_multiboot_info*)mbi->mmap_addr;
    while((uint32_t)mmap_mbi < mbi->mmap_addr + mbi->mmap_len){
        if(1 == mmap_mbi->type){
            init_pmm_region((uint32_t)mmap_mbi->addr, (uint32_t)mmap_mbi->len);
        }
        mmap_mbi = (mmap_multiboot_info*)((uint32_t)mmap_mbi + mmap_mbi->size + 4);
    }
    
    uint32_t end_kernel = (uint32_t)&ebss + pmm.bitmap_size;
    lock_pmm_region(0, end_kernel);
    set_frame_pmm(0);
}

void set_frame_pmm(uint32_t addr){
    uint32_t frame = addr / 4096;
    pmm.bitmap[frame / 32] |= (1 << (frame % 32));
}

void unset_frame_pmm(uint32_t addr){
    uint32_t frame = addr / 4096;
    pmm.bitmap[frame / 32] &= ~(1 << (frame % 32));
}

void init_pmm_region(uint32_t addr, uint32_t len){
    for(uint64_t a = addr; a < addr + len; a += 4096){
        unset_frame_pmm(a);
        if(pmm.used_frames > 0){pmm.used_frames--;}
    }
}

void lock_pmm_region(uint32_t addr, uint32_t len){
    for(uint32_t a = addr; a < addr + len; a += 4096){
        set_frame_pmm(a);
        pmm.used_frames++;
    }
}

uint32_t get_end_kernel_area(void){
    return (uint32_t)((uint32_t)&ebss + pmm.bitmap_size);
}

uint32_t alloc_pmm(void){
    for(uint32_t i = 0; i < pmm.bitmap_size / 4; i++){
        if(pmm.bitmap[i] != 0xFFFFFFFF){
            for(uint32_t j = 0; j < 32; j++){
                if(!(pmm.bitmap[i] & (1 << j))){
                    uint64_t addr = (i * 32 + j) * 4096;
                    set_frame_pmm(addr);
                    pmm.used_frames++;
                    return addr;
                }
            }
        }
    }
    return 0;
}