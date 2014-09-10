struct cpu_info
{
    unsigned stepping : 4;
    unsigned model    : 4;
    unsigned family   : 4;
    unsigned type     : 2;
    unsigned reserved : 18;
    unsigned feature_flags;
    char vendor_id[12];
    unsigned char cache_config[16];
};

//values for cpu_info.family field
static const unsigned char cpu_family_386         = 3;
static const unsigned char cpu_family_486         = 4;
static const unsigned char cpu_family_pentium     = 5;
static const unsigned char cpu_family_pentium_pro = 6; 

//values for cpu_info.type field
static const unsigned char cpu_type_original      = 0;
static const unsigned char cpu_type_overdrive     = 1;
static const unsigned char type_dual              = 2; 

//cpu feature bits
static const int cpuf_on_chip_FPU = 0x00000001;

void cpuid(struct cpu_info *out_id);
