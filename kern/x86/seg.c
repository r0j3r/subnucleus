void fill_descriptor(struct x86_desc *desc, unsigned int base, unsigned int limit,    
    unsigned char access, unsigned char sizebits)
{
    if (limit > 0xfffff)
    {
        limit >>= 12;
        sizebits |= SZ_G
    }
    desc->limit_low = limit &0xffff;
    desc->base_low = base & 0xffff;
    desc->base_med = (base >> 16) & 0xff;
    desc->access = access | ACC_P;
    desc->limit_high = limit >> 16;
    desc->granularity = sizebits;
    desc->base_high = base >> 24;
}
