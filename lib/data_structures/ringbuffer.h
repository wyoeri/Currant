#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include "lib/other/types.h"

typedef struct{
    uint8_t* buffer;
    volatile int head;
    volatile int tail;
    volatile int count;
    int size;
} ring_buffer_t;

void init_buffer(ring_buffer_t* rb, uint8_t* memory, size_t size);
bool pushrb(ring_buffer_t* rb, uint8_t data);
int poprb(ring_buffer_t* rb);

#endif