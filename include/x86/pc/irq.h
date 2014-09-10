
static const unsigned char IRQ_MASTER_BASE=0x20;
static const unsigned char IRQ_SLAVE_BASE=0x28; 

extern int irq_master_base, irq_slave_base;

void irq_init(void);

extern struct gate_init_entry irq_inittab[];
