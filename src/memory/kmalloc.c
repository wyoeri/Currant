#include "kmalloc.h"

#include "src/memory/paging.h" 
#include "src/memory/vmm.h"
#include "src/memory/pmm.h"
#include "lib/string/string.h"

static kmallfree* head = NULL;
static uint32_t head_top = 0xD0000000; 

void* kmalloc(size_t size){
    if(0 == size){return NULL;}
    size = aligment(size, 4);
    kmallfree* current = head;
    while(NULL != current){
        if(current->is_free && current->size >= size){
            if(current->size >= size + sizeof(kmallfree) + 4){
                kmallfree* next_block = (kmallfree*)((uint8_t*)current + sizeof(kmallfree) + size);
                next_block->size = current->size - size - sizeof(kmallfree);
                next_block->is_free = 1;
                next_block->next = current->next;
 
                current->size = size;
                current->next = next_block;
            }
            current->is_free = 0;
            return (void*)((uint8_t*)current + sizeof(kmallfree));
        }

        if(NULL == current->next){break;}

        current = current->next;
    }

    uint32_t phys = alloc_pmm();
    if(0 == phys){return NULL;}

    vmm_map_page(head_top, phys, PAGE_PRESENT | PAGE_RW);

    kmallfree* new = (kmallfree*)head_top;
    new->size = 4096 - sizeof(kmallfree);
    new->is_free = 1;
    new->next = NULL;

    if(NULL == head){
        head = new;
    }
    else{
        current->next = new;
    }

    head_top += 4096;

    return kmalloc(size);
}

void* kcalloc(size_t num, size_t size){
    if(0 == num || 0 == size){return NULL;}
    if(0 != num && size > SIZE_MAX / num){return NULL;}

    size_t total = num * size;
    void* ptr = kmalloc(total);

    if(NULL == ptr){return NULL;}
    memset(ptr, 0, total);
    return ptr;
}

void kfree(void* ptr){
    if(NULL == ptr){return;}
    kmallfree* delete_block = (kmallfree*)((uint8_t*)ptr - sizeof(kmallfree));
    delete_block->is_free = 1;

    if(NULL != delete_block->next && delete_block->next->is_free){
        delete_block->size += sizeof(kmallfree) + delete_block->next->size;
        delete_block->next = delete_block->next->next;
    }
    
    if(delete_block == head){return;}

    kmallfree* current = head;
    
    while(NULL != current && current->next != delete_block){
        current = current->next;
    }

    if(NULL != current && current->is_free){
        current->size += sizeof(kmallfree) + delete_block->size;
        current->next = delete_block->next;
    }
}

size_t aligment(size_t size, size_t alig){
    return (size + alig - 1) & ~(alig - 1);
}