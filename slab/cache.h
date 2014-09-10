struct cache
{
    unsigned int size;
    unsigned int count;
    struct slab * empty;
    struct slab * partial;
    struct slab * full;
};
