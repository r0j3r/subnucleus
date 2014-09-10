#include <c/assert.h>
#include <x86/eflags.h>
#include <x86/seg.h>
#include <x86/idt.h>
#include <x86/gdt.h>
#include <x86/gate_init.h>
#include <x86/pc/irq.h>
#include <x86/proc_reg.h>
#include <x86/pc/pic.h> 

void 
irq_init()
{
    assert((get_eflags() & EFL_IF) == 0);

    gate_init(idt, irq_inittab, KERNEL_CS);

    pic_init(IRQ_MASTER_BASE, IRQ_SLAVE_BASE);
    irq_master_base = IRQ_MASTER_BASE;
    irq_slave_base = IRQ_SLAVE_BASE;

    pic_disable_all();
}
