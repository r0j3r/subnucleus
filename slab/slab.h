struct cache;
struct slab
{
    struct cache * cache;
    void * start;       //start of buffers
    unsigned int ref;   //count of in use buffers
    unsigned int alloc_size;
    struct slab * prev;
    struct slab * next;
    unsigned char bmap[];
};
