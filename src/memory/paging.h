#ifndef PAGING_H
#define PAGING_H

#include "lib/other/types.h"

typedef struct{
    uint32_t present : 1;
    uint32_t rw : 1;
    uint32_t memory_access : 1;
    uint32_t pwt : 1;
    uint32_t pcd : 1;
    uint32_t accessed : 1;
    uint32_t dirty : 1;
    uint32_t pat : 1;
    uint32_t global : 1;
    uint32_t available : 3;
    uint32_t frame : 20;
} __attribute__((packed)) page_entry;

void init_paging(void);
void load_page_directory(volatile uint32_t* directory);
void enable_paging(void);

#endif