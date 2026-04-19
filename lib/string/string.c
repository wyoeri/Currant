#include "string.h"

int strcom(const char* s1, const char* s2){
    while(*s1 && (*s1 == *s2)){
        s1++;
        s2++;
    }
    return (uint8_t)(*s1) - (uint8_t)(*s2);
}

int strlen(const char* s){
    size_t i = 0;
    while(*s++){
        i++;
    }
    return i;
}

void* memset(void* dest, int c, size_t n){
    volatile uint8_t* p = (uint8_t*)dest;
    while(n--){
        *p++ = (uint8_t)c;
    }
    return dest;
}

void* memcpy(void* dest, const void* src, size_t n){
    uint8_t* d = dest;
    const uint8_t* s = src;
    while(n--){
        *d++ = *s++;
    }
    return dest;
}