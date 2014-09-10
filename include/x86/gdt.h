
extern const unsigned int QUARQ_TSS;
extern const unsigned int KERNEL_CS;
extern const unsigned int KERNEL_DS;
extern const unsigned int LINEAR_CS;
extern const unsigned int LINEAR_DS;
extern const unsigned int USER_CS;
extern const unsigned int USER_DS;
extern const unsigned int KERNEL_TRAP_TSS; 

static const int GDTSZ = 0x80/8; 

extern struct x86_desc gdt[];

void gdt_init(void);
