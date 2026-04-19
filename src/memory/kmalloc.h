#ifndef KMALLOC_H
#define KMALLOC_H

#include "lib/other/types.h"

typedef struct kmallfree{
    uint32_t size;
    struct kmallfree* next;
    uint8_t is_free;
} kmallfree;

void* kmalloc(size_t size);
void* kcalloc(size_t num, size_t size);
void kfree(void* ptr);
size_t aligment(size_t size, size_t alig);

#endif