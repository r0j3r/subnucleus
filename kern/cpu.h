
struct cpu
{
    unsigned int q_env_id[1 << 7];
    unsigned int q_ticks[1 << 7];
    unsigned short q_no[1 << 7];
    unsigned long regs[32]; 
};
