#include <x86/seg.h>
#include <x86/idt.h>
#include <x86/gdt.h>
#include <x86/gate_init.h>
#include <x86/trap.h>

void
trap_init(void)
{
    gate_init(idt, trap_inittab, KERNEL_CS);
}
