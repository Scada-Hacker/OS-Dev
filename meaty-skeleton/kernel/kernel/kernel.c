#include <stdio.h>
#include <stddef.h>
#include <kernel/tty.h>
#include <kernel/gdt.h>
#include "memory.h"
#include <stdio.h>

void kernel_main(void) {
    terminal_initialize();
    gdt_install(); 
    memory_init(16 * 1024 * 1024); // Pretend we have 16MB RAM

    void* page1 = alloc_page();
    void* page2 = alloc_page();
    printf("Allocated page1 at %p\n", page1);
    printf("Allocated page2 at %p\n", page2);

    free_page(page1);
    printf("Freed page1\n");

    void* page3 = alloc_page();
    printf("Re-allocated page1 as page3: %p\n", page3);
}


