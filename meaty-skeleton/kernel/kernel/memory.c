#include "memory.h"
#include <kernel/tty.h>

#define PAGE_SIZE 4096
#define MAX_PAGES 32768  // 128MB max (32768 * 4K = 128MB)

static uint8_t bitmap[MAX_PAGES / 8];
static uint32_t total_pages;

static inline void set_bit(uint32_t bit) {
    bitmap[bit / 8] |= (1 << (bit % 8));
}

static inline void clear_bit(uint32_t bit) {
    bitmap[bit / 8] &= ~(1 << (bit % 8));
}

static inline int test_bit(uint32_t bit) {
    return bitmap[bit / 8] & (1 << (bit % 8));
}

void memory_init(uint32_t memory_size) {
    total_pages = memory_size / PAGE_SIZE;
    for (uint32_t i = 0; i < total_pages / 8; i++)
        bitmap[i] = 0; // mark all as free

    printf("Memory manager initialized: %u pages (%u KB)\n", total_pages, memory_size / 1024);
}

void* alloc_page(void) {
    for (uint32_t i = 0; i < total_pages; i++) {
        if (!test_bit(i)) {
            set_bit(i);
            return (void*)(i * PAGE_SIZE);
        }
    }
    return NULL; // Out of memory
}

void free_page(void* addr) {
    uint32_t index = ((uintptr_t)addr) / PAGE_SIZE;
    clear_bit(index);
}

