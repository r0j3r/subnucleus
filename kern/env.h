struct env_state
{
    unsigned long rax;
    unsigned long rbx;
    unsigned long rcx;
    unsigned long rdx;
    unsigned long rex;
    unsigned long rfx;
    unsigned long rgx;
    unsigned long rx;
};

struct capability
{
    unsigned int privs;
    unsigned char obj_id[16];
};

enum state 
{
    RUNNING,
    BLOCKED,
    TERMINATED
};

struct page_table 
{
    unsigned char e[16];
};

struct env
{
    struct env * link;
    enum state env_state;
    unsigned char * stack_base;
    unsigned char * stack_top;
    struct capability caps[32];
    int (entry*)(long);
    int (ipc*)(long);
    struct env_state s;
    struct env * next;
    struct page_tables pt[512];
    struct mem_map * mm; 
};

struct env_tab {
    struct env_tab * n;
    struct env * e;
}
