struct vma
{
    unsigned char * base;
    unsigned long len;
    struct vma * next;
};

struct mem_map
{
    struct vma * vm_areas;
};

struct page
{
    unsigned int ref_count; 
};
