#include <compiler.h>
#include <x86/cpuid.h>
#include <x86/cpu.h>
#include <x86/seg.h>
#include <x86/gate_init.h>
#include <x86/trap.h>
#include <x86/gdt.h>
#include <x86/tss.h>
#include <x86/pc/irq.h>

struct cpu_info b_cpuid;

void cpu_init(void)
{
    cpuid(&b_cpuid);

    trap_init();
    irq_init();
    gdt_init();
    tss_init();
}
