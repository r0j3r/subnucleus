
#include <x86/proc_reg.h>
#include <x86/seg.h>
#include <x86/gdt.h>
#include <x86/tss.h>

void tss_init(void)
{
    if (!tss.ss0)
    {
        tss.ss0 = KERNEL_DS;
        tss.esp0 = get_esp();
        tss.io_bit_map_offset = sizeof(tss);
    }
}
