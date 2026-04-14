#include "ringbuffer.h"

void init_buffer(ring_buffer* rb, uint8_t* memory, size_t size){
    rb->buffer = memory;
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
    rb->size = size;
}

int pushrb(ring_buffer* rb, uint8_t data){
    if(rb->count == rb->size){return 0;}

    rb->buffer[rb->head] = data;

    rb->head = (rb->head + 1) % rb->size;

    rb->count++;

    return 1;
}

int poprb(ring_buffer* rb){
    if(rb->count == 0){return -1;}

    uint8_t val = rb->buffer[rb->tail];

    rb->tail = (rb->tail + 1) % rb->size;

    rb->count--;

    return (int)val;
}