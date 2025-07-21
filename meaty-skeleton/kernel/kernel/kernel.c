#include <stdio.h>
#include <stdint.h>
#include <kernel/tty.h>

uintptr_t __stack_chk_guard = 0xBADC0FFEE0DDF00D;

void __attribute__((noreturn)) __stack_chk_fail(void) {
    for (;;) {
        asm volatile ("cli; hlt");
    }
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
  for(constructor* i = &start_ctors; i != &end_ctors; i++)
     (*i)();
}

void kernel_main(void) {
	terminal_initialize();
	printf("Hello, kernel World!\n");
}
