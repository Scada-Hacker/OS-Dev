#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>

void memory_init(uint32_t memory_size);  // pass total physical memory in bytes
void* alloc_page(void);
void free_page(void* addr);

#endif

