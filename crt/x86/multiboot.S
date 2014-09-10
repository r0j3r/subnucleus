//multiboot header
.text
    .p2align 2
boot_hdr:
    .long 0x1BADB002
    .long 0x00000000
    .long 0-0x1BADB002-0x00000000
boot_entry:
    movl $stack_end, %esp
    pushl $0
    popf

    lea edata, %edi
    lea end, %ecx
    subl %edi,%ecx
    xorl %eax,%eax
    rep
    stosb

    pushl %ebx

    call multiboot_main

    .data
    .p2align 12
    .globl start_of_data
start_of_data:
    .long 0
.L69:
    .long version_string    
