#include <x86/pc/pic.h>

const unsigned int MASTER_PIC_BASE = 0x20;
const unsigned int SLAVES_PIC_BASE = 0xa0;
const unsigned int OFF_ICW         = 0x00;
const unsigned int OFF_OCW         = 0x01;

const unsigned int ICW_TEMPLATE = 0x10;
const unsigned int LEVL_TRIGGER = 0x08;
const unsigned int EDGE_TRIGGER = 0x00;
const unsigned int ADDR_INTRVL4 = 0x04;
const unsigned int ADDR_INTRVL8 = 0x08;
const unsigned int SINGLE__MODE = 0x02;
const unsigned int CASCADE_MODE = 0x00;
const unsigned int ICW4__NEEDED = 0x01;
const unsigned int NO_ICW4_NEED = 0x00;

const unsigned int SLAVE_ON_IR0 = 0x01;
const unsigned int SLAVE_ON_IR1 = 0x02;
const unsigned int SLAVE_ON_IR2 = 0x04;
const unsigned int SLAVE_ON_IR3 = 0x08;
const unsigned int SLAVE_ON_IR4 = 0x10;
const unsigned int SLAVE_ON_IR5 = 0x20;
const unsigned int SLAVE_ON_IR6 = 0x40;
const unsigned int SLAVE_ON_IR7 = 0x80;

const unsigned int I_AM_SLAVE_0 = 0x00;
const unsigned int I_AM_SLAVE_1 = 0x01;
const unsigned int I_AM_SLAVE_2 = 0x02;
const unsigned int I_AM_SLAVE_3 = 0x03;
const unsigned int I_AM_SLAVE_4 = 0x04;
const unsigned int I_AM_SLAVE_5 = 0x05;
const unsigned int I_AM_SLAVE_6 = 0x06;
const unsigned int I_AM_SLAVE_7 = 0x07;

const unsigned int SNF_MODE_ENA = 0x10;
const unsigned int SNF_MODE_DIS = 0x00;
const unsigned int BUFFERD_MODE = 0x08;
const unsigned int NONBUFD_MODE = 0x00;
const unsigned int AUTO_EOI_MOD = 0x02;
const unsigned int NRML_EOI_MOD = 0x00;
const unsigned int I8086_EMM_MOD = 0x01;
const unsigned int SET_MCS_MODE = 0x00;

const unsigned int NON_SPEC_EOI = 0x20;
const unsigned int SPECIFIC_EOI = 0x60;
const unsigned int ROT_NON_SPEC = 0xa0;
const unsigned int SET_ROT_AEOI = 0x80;
const unsigned int RSET_ROTAEOI = 0x00;
const unsigned int ROT_SPEC_EOI = 0xe0;
const unsigned int SET_PRIORITY = 0xc0;
const unsigned int NO_OPERATION = 0x40;

void
pic_init(unsigned char master_base, unsigned char slave_base)	
{
    unsigned int MASTER_ICW;
    unsigned int MASTER_OCW;
    unsigned int SLAVES_ICW;
    unsigned int SLAVES_OCW;

    unsigned int PICM_ICW1;
    unsigned int PICM_ICW3;
    unsigned int PICM_ICW4;

    unsigned int PICS_ICW1;
    unsigned int PICS_ICW3;
    unsigned int PICS_ICW4;

    MASTER_ICW = MASTER_PIC_BASE + OFF_ICW;
    MASTER_OCW = MASTER_PIC_BASE + OFF_OCW;
    SLAVES_ICW = SLAVES_PIC_BASE + OFF_ICW;
    SLAVES_OCW = SLAVES_PIC_BASE + OFF_OCW;    

    PICM_ICW1 = ICW_TEMPLATE | EDGE_TRIGGER | ADDR_INTRVL8 | CASCADE_MODE 
        | ICW4__NEEDED;
    PICM_ICW3 = SLAVE_ON_IR2;
    PICM_ICW4 = SNF_MODE_DIS | NONBUFD_MODE | NRML_EOI_MOD | I8086_EMM_MOD;

    PICS_ICW1 = ICW_TEMPLATE | EDGE_TRIGGER | ADDR_INTRVL8 | CASCADE_MODE 
        | ICW4__NEEDED;
    PICS_ICW3 = I_AM_SLAVE_2;
    PICS_ICW4 = SNF_MODE_DIS | NONBUFD_MODE | NRML_EOI_MOD | I8086_EMM_MOD;

    asm volatile("outb %0, %%dx" : : "a" ((unsigned char)(PICM_ICW1)), 
        "d" ((unsigned short)(MASTER_ICW)));
    asm volatile("outb %0, %%dx" : : "a" ((unsigned char)(master_base)),
        "d" ((unsigned short)(MASTER_OCW)));
    asm volatile("outb %0, %%dx" : : "a" ((unsigned char)(PICM_ICW3)),
        "d" ((unsigned short)(MASTER_OCW)));
    asm volatile("outb %0, %%dx" : : "a" ((unsigned char)(PICM_ICW4)),
        "d" ((unsigned short)(MASTER_OCW)));

    asm volatile("outb %0, %%dx" : : "a" ((unsigned char)(PICS_ICW1)),
        "d" ((unsigned short)(SLAVES_ICW)));
    asm volatile("outb %0, %%dx" : : "a" ((unsigned char)(slave_base)),
        "d" ((unsigned short)(SLAVES_OCW)));
    asm volatile("outb %0, %%dx" : : "a" ((unsigned char)(PICS_ICW3)),
        "d" ((unsigned short)(SLAVES_OCW)));
    asm volatile("outb %0, %%dx" : : "a" ((unsigned char)(PICS_ICW4)),
        "d" ((unsigned short)(SLAVES_OCW)));    

    asm volatile("outb %0, %%dx" : : "a" ((unsigned char)(NON_SPEC_EOI)),
        "d" ((unsigned short)(MASTER_ICW)));
    asm volatile("outb %0, %%dx" : : "a" ((unsigned char)(NON_SPEC_EOI)),
        "d" ((unsigned short)(SLAVES_ICW)));
}

void pic_disable_all(void)
{
    unsigned int MASTER_OCW;
    unsigned int SLAVES_OCW;

    MASTER_OCW = MASTER_PIC_BASE + OFF_OCW;
    SLAVES_OCW = SLAVES_PIC_BASE + OFF_OCW;

    asm volatile("outb %0, %%dx" : : "a" ((unsigned char)(PICM_MASK)),
        "d" ((unsigned short)(MASTER_OCW)));
    asm volatile("outb %0, %%dx" : : "a" ((unsigned char)(PICS_MASK)),
        "d" ((unsigned short)(SLAVES_OCW)));    
}
