struct kmem_cache;

struct slab {
    struct slab * next;
    struct kmem_cache * c;
    unsigned int inuse;
    unsigned char * buffers;
    unsigned int buf_cnt;
    unsigned char bmap[];
}; 

struct unrolled_list {
    struct unrolled_list * next;
    int num;
    int elem_size;
    int maxnum;
    unsigned char elem[];
};

struct kmem_cache {
    unsigned int size;
    unsigned int aligned size;
    struct slab * empty;
    struct slab * partial;
    struct slab * full;
};

struct unrolled_list * cache_list;
 

struct page {
    struct slab * s;
};

int
init_cache() {
    int size = sizeof(struct kmem_cache);
    if (size < (4096/8)) {
        pages = 1;
        cache_list = get_page(pages);
    } else {
        pages = (((size * 8) + 4095) & ~4095) / 4096;
        cache_list = get_page(pages);
    }
    memset(cache_list, 0, 4096 * pages);
    cache_list.max
    struct kmem_cache * c = &cache_list.elem[cache_list.num++];
       
}

int
get_pages()
{

}

int
free_pages()
{

}
