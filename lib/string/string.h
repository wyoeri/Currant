#ifndef STRING_H
#define STRING_H

#include "lib/other/types.h"

int strcom(const char* s1, const char* s2);
int strlen(const char* s);
void* memset(void* dest, int c, size_t n);
void* memcpy(void* dest, const void* src, size_t n);

#endif