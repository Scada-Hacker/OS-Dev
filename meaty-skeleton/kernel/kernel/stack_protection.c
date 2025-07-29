// src/stack_protection.c
#include <kernel/tty.h>
#include <stdio.h>
__attribute__((noreturn))
void __stack_chk_fail(void) {
    terminal_initialize(); // Optional
    printf("Stack smashing detected!\n");

    // Halt the CPU
    while (1) {
        __asm__ volatile("cli; hlt");
    }
}

