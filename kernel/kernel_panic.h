#ifndef KERNEL_PANIC
#define KERNEL_PANIC

#include "arch/i386/isr.h"

void kernel_panic(registers_t* rg);

#endif