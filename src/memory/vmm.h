#ifndef VMM_H
#define VMM_H

#include "lib/other/types.h"

void vmm_map_page(uint32_t vaddr, uint32_t paddr, uint32_t flags);

#endif