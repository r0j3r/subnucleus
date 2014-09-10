#include <x86/seg.h>
#include <x86/gdt.h>
#include <x86/tss.h>
#include <x86/vm.h>

void gdt_init(void)
{
    fill_descriptor(&gdt[QUARQ_TSS / 8],
        kvtolin((unsigned int)&tss), sizeof(tss) - 1,
        ACC_PL_K | ACC_TSS | ACC_P, 0);

    fill_descriptor(&gdt[KERNEL_CS / 8],
        kvtolin(0), 0xffffffff,
        ACC_PL_K | ACC_CODE_R, SZ_32);
    fill_descriptor(&gdt[KERNEL_DS/ 8],
        kvtolin(0), 0xffffffff,
        ACC_PL_K | ACC_DATA_W, SZ_32);

    fill_descriptor(&gdt[LINEAR_CS / 8],
        0x00000000, 0xffffffff,
        ACC_PL_K | ACC_CODE_R, SZ_32);
    fill_descriptor(&gdt[LINEAR_DS / 8],
        0x00000000, 0xffffffff,
        ACC_PL_K | ACC_DATA_W, SZ_32); 
}
