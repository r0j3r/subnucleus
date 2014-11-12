
struct cpu
{
    unsigned int q_env_id[1 << 7];
    unsigned int * q_active;
    unsigned int * q_expired; 
    unsigned short q_no[1 << 7];
    unsigned long regs[32]; 
};
