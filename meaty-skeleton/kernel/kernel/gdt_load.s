.global gdt_flush

gdt_flush:
    movl 4(%esp), %eax       # Load pointer to GDT descriptor
    lgdt (%eax)              # Load GDT

    movw $0x10, %ax          # 0x10 = offset of data segment
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss

    ljmp $0x08, $flush_cs    # 0x08 = offset of code segment
flush_cs:
    ret

