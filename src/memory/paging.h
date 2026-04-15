#ifndef PAGING_H
#define PAGING_H

#include "lib/other/types.h"

#define PAGE_PRESENT (1 << 0)
#define PAGE_RW (1 << 1)
#define PAGE_US (1 << 2)
#define PAGE_PWT (1 << 3)
#define PAGE_PCD (1 << 4)
#define PAGE_A (1 << 5)
#define PAGE_D (1 << 6)
#define PAGE_PS (1 << 7)
#define PAGE_G (1 << 8)
#define PAGE_AVL_1 (1 << 9)
#define PAGE_AVL_2 (1 << 10)
#define PAGE_AVL_3 (1 << 11)
#define PAGE_FRAME 0xFFFFF000

typedef struct{
    uint32_t pe[1024];
} page_table __attribute__((aligned(4096)));

typedef struct{
    uint32_t pe[1024];
} page_directory __attribute__((aligned(4096)));

void init_paging(void);
void load_page_directory(volatile uint32_t* directory);
void enable_paging(void);

#endif