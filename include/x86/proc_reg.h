static inline unsigned get_eflags(void)
{
    unsigned eflags;
    asm volatile(
    "       pushfl\n"
    "       popl %0" : "=r" (eflags));
    return eflags;
}

static inline void set_eflags(unsigned eflags) 
{
    asm volatile(
    "        pushl %0\n"
    "        popfl" : : "r" (eflags));
}

static inline int get_esp(void)
{
    register unsigned int esp;
    asm("movl %%esp, %0" : "=r" (esp));
    return esp;
}
