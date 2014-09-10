
#include <x86/eflags.h>
#include <x86/cpuid.h>
#include <x86/proc_reg.h>
#include <c/string.h>

static void get_cache_config(struct cpu_info *id)
{
    unsigned ci[4];
    unsigned cicount = 0;
    unsigned ccidx = 0;

    do
    {
        unsigned i;
       
        cicount++;
        asm volatile(
        "       cpuid\n"
        : "=a" (ci[0]),
          "=b" (ci[1]),
          "=c" (ci[2]),
          "=d" (ci[3])
        : "a" (2));
        
        for(i = 0; i < 4; i++)
        {
            unsigned reg = ci[i];
            if ((reg & (1 << 31)) == 0)
            {
                if (i == 0)
                    reg >>= 8;
                while(reg != 0)
                {
                    if ((reg & 0xff) &&
                        (ccidx < sizeof(id->cache_config)))
                    {
                        id->cache_config[ccidx++] = 
                            reg & 0xff;
                    }
                    reg >>= 8;
                } 
            }
        }
    } 
    while(cicount < (ci[0] & 0xff));
}

void cpuid(struct cpu_info *out_id)
{
    int orig_eflags;

    orig_eflags = get_eflags();

    memset(out_id, 0, sizeof(*out_id));

    set_eflags(orig_eflags ^ EFL_AC);
    if ((get_eflags() ^ orig_eflags) & EFL_AC)
    {
        set_eflags(orig_eflags ^ EFL_ID);
        if ((get_eflags() ^ orig_eflags) & EFL_ID)
        {
             int highest_val;
             asm volatile(
             "        cpuid\n"
             : "=a" (highest_val),
               "=b" (*((int*)(out_id->vendor_id+0))),
               "=d" (*((int*)(out_id->vendor_id+4))),
               "=c" (*((int*)(out_id->vendor_id+8)))
             : "a" (0));
             if (highest_val >= 1)
             {
                  asm volatile(
                  "       cpuid\n"
                  : "=a" (*((int*)out_id)),
                    "=d" (out_id->feature_flags)
                  : "a" (1)
                  : "ebx", "ecx");
             }
             if (highest_val >= 2)
                 get_cache_config(out_id); 
        }
        else
        {
            out_id->family = cpu_family_486;
        } 
    }
    else
    {
        out_id->family = cpu_family_386;
    }

    set_eflags(orig_eflags); 
}
