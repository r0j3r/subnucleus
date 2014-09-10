extern const unsigned int MASTER_PIC_BASE;
extern const unsigned int SLAVES_PIC_BASE;
extern const unsigned int OFF_ICW;
extern const unsigned int OFF_OCW;  

extern const unsigned int ICW_TEMPLATE; 
extern const unsigned int LEVL_TRIGGER;
extern const unsigned int EDGE_TRIGGER;
extern const unsigned int ADDR_INTRVL4;
extern const unsigned int ADDR_INTRVL8;
extern const unsigned int SINGLE__MODE;
extern const unsigned int CASCADE_MODE;
extern const unsigned int ICW4__NEEDED;
extern const unsigned int NO_ICW4_NEED;

extern const unsigned int SLAVE_ON_IR0;
extern const unsigned int SLAVE_ON_IR1;
extern const unsigned int SLAVE_ON_IR2;
extern const unsigned int SLAVE_ON_IR3;
extern const unsigned int SLAVE_ON_IR4;
extern const unsigned int SLAVE_ON_IR5;
extern const unsigned int SLAVE_ON_IR6;
extern const unsigned int SLAVE_ON_IR7;

extern const unsigned int I_AM_SLAVE_0;
extern const unsigned int I_AM_SLAVE_1;
extern const unsigned int I_AM_SLAVE_2;
extern const unsigned int I_AM_SLAVE_3;
extern const unsigned int I_AM_SLAVE_4;
extern const unsigned int I_AM_SLAVE_5;
extern const unsigned int I_AM_SLAVE_6;
extern const unsigned int I_AM_SLAVE_7;

extern const unsigned int SNF_MODE_ENA;
extern const unsigned int SNF_MODE_DIS;
extern const unsigned int BUFFERD_MODE;
extern const unsigned int NONBUFD_MODE;
extern const unsigned int AUTO_EOI_MOD;
extern const unsigned int NRML_EOI_MOD;
extern const unsigned int I8086_EMM_MOD;
extern const unsigned int SET_MCS_MODE;

extern const unsigned int PICM_MASK;
extern const unsigned int PICS_MASK;

extern const unsigned int NON_SPEC_EOI;
extern const unsigned int SPECIFIC_EOI;
extern const unsigned int ROT_NON_SPEC;
extern const unsigned int SET_ROT_AEOI;
extern const unsigned int RSET_ROTAEOI;
extern const unsigned int ROT_SPEC_EOI;
extern const unsigned int SET_PRIORITY;
extern const unsigned int NO_OPERATION;

extern void pic_init(unsigned char, unsigned char);
extern void pic_disable_all(void);
