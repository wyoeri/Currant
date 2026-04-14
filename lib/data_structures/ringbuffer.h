#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include "other/types.h"

typedef struct{
    uint8_t* buffer;
    volatile int head;
    volatile int tail;
    volatile int count;
    int size;
} ring_buffer;

void init_buffer(ring_buffer* rb, uint8_t* memory, size_t size);
int pushrb(ring_buffer* rb, uint8_t data);
int poprb(ring_buffer* rb);

#endif