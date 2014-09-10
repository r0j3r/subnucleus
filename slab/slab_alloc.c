struct slab
{
    struct cache * cache; //uplink to cache head node
    void * start;       //start of buffers
    unsigned int ref;   //count of in use buffers
    struct slab * prev;
    struct slab * next;
    unsigned char bmap[];
};

struct cache
{
    unsigned int size;
    unsigned int count;
    struct slab * empty;
    struct slab * partial;
    struct slab * full;
};

struct slab_buffer_page * slab_dir;

int
init_cache(struct cache * theCache, unsigned int size)
{
    number_pages = compute_buff_pages(size);
    slab = get_chunk(compute_slab_head_size(number_pages));
    slab->buffers = get_page(number_pages);
    theCache->empty = slab;
}

void *
cache_alloc(struct cache * cache)
{
    void * buff;

    buff = get_buff(cache->partial);
    if (!buff) buff = get_buff(chache->empty); 
    else if (slab_full(cache->partial))
    {
        list_add(cache->partial, cache->full);
        list_remove(cache->partial, cache);
    }
    if (!buff) 
    {
        list_add(create_slab(cache), cache->partial;
        buff = get_buff(cache->partial);
    }   
    return buff;
}
