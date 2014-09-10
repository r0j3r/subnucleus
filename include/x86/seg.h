extern const unsigned int SZ_32;
extern const unsigned int SZ_16;
extern const unsigned int SZ_G;

extern const unsigned int ACC_A;
extern const unsigned int ACC_TYPE;
extern const unsigned int ACC_TYPE_SYSTEM;
extern const unsigned int ACC_LDT;
extern const unsigned int ACC_CALL_GATE_16;
extern const unsigned int ACC_TASK_GATE;
extern const unsigned int ACC_TSS;
extern const unsigned int ACC_CALL_GATE;
extern const unsigned int ACC_INTR_GATE;
extern const unsigned int ACC_TRAP_GATE;
extern const unsigned int ACC_TSS_BUSY;
extern const unsigned int ACC_TYPE_USER;
extern const unsigned int ACC_DATA;
extern const unsigned int ACC_DATA_W;
extern const unsigned int ACC_DATA_E;
extern const unsigned int ACC_DATA_EW;
extern const unsigned int ACC_CODE;
extern const unsigned int ACC_CODE_R;
extern const unsigned int ACC_CODE_C;
extern const unsigned int ACC_CODE_CR;

extern const unsigned int ACC_PL;
extern const unsigned int ACC_PL_K;
extern const unsigned int ACC_PL_U;
extern const unsigned int ACC_P;

struct x86_desc
{
    unsigned int limit_low  :16,
                 base_low   :16,
                 base_med   :8,
                 access     :8,
                 limit_high :4,
                 granularity:4,
                 base_high  :8;    
};

struct x86_gate
{
    unsigned int offset_low:16,
                 selector:16,
                 word_count:8,
                 access:8,
                 offset_high:16;
};

void fill_descriptor(struct x86_desc *, unsigned int, unsigned int,
    unsigned char, unsigned char);
