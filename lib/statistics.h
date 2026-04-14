#ifndef STATISTICS_H
#define STATISTICS_H

#include "arch/i386/isr.h"
#include "kernel/error_msg_isr.h"

void print_info(const char* name, uint32_t val, int x, int y);
void output_registers_info(const registers* rg);
void output_error(const registers* rg, const char* msg);
void output_context(const registers* rg);
void output_flags(const registers* rg);

#endif