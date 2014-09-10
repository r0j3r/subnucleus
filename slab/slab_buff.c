#include "slab.h"
#include "cache.h"

//this is an unrolled list boundary tag memory allocator
//this is the slab header cache

struct slab_buffer_page
{
    struct slab_buffer_page * next;
    struct slab_buffer_page * prev;
    unsigned int bytes_available;
};

struct chunk 
{
    unsigned short tag;
    unsigned short next;
    unsigned short prev;
};

struct tag
{
    unsigned short tag;
};

struct slab_buffer_page slab_dir_empty;
struct slab_buffer_page slab_dir_partial;
struct slab_buffer_page slab_dir_full;

const int PAGE_SIZE = 4096;
const void * NULL = 0;

void * get_page(unsigned int);

//we initialize the sentinel nodes in this circular lists 

int
init_slab_buffer_list()
{
    struct slab_buffer_page * slab_buffer = get_page(1);
    struct chunk * first_chunk;
    unsigned long t;
    unsigned long base;  
 
    slab_dir_partial.next = &slab_dir_partial;
    slab_dir_partial.prev = &slab_dir_partial;
    slab_dir_partial.bytes_available = 0;

    slab_dir_full.next = &slab_dir_full;
    slab_dir_full.prev = &slab_dir_full;
    slab_dir_full.bytes_available = 0;

    slab_dir_empty.next = slab_buffer;
    slab_dir_empty.prev = slab_buffer;
    slab_dir_empty.bytes_available = 0;    

    slab_buffer->next = &slab_dir_empty;
    slab_buffer->prev = &slab_dir_empty;
    slab_buffer->bytes_available = PAGE_SIZE - sizeof(struct slab_buffer_page);

    t = (unsigned long)slab_buffer;
    base = t;
    first_chunk = (struct chunk *)(t + sizeof(struct slab_buffer_page));
    first_chunk->tag = sizeof(struct chunk);

    t = (unsigned long)first_chunk;
    trailer = (struct tag *)(t + sizeof(struct chunk)); 
    trailer->tag = first_chunk->tag | 0x0001;
   
    t = trailer;
    t += sizeof(trailer); 
    first_chunk->next = t - base;
    first_chunk->prev = t - base;
    
    first_chunk = t;
    first_chunk->tag = PAGE_SIZE - t - sizeof(struct tag);
    trailer = base + t + first_chunk-tag;
    trailer->tag = first_chunk->tag;
    first_chunk->next = sizeof(struct buffer_slab) + sizeof(struct chunk)
        + sizeof(struct trailer);
    first_chunk->prev = first_chunk->next; 
}

void *
find_node_big_enough(struct slab_buffer_page * page, 
    unsigned int size)
{
    void * guard;
    struct chunk * chunk, * prev_chunk, * new_chunk;
    unsigned long a;

    base = page;
    sentinel = base + sizeof(struct slab_buffer_page);
    sentinel->tag = size + sizeof(struct tag); 
 
    for(node = base + sentinel->next;
        node->tag < size + sizeof(struct tag);
        node = base + node->next)

    if (node == sentinel)
        return 0;
    else
        return node;
}

void *
get_chunk_from_buffer_page(struct slab_buffer_page * page, 
    struct chunk * node, unsigned int * size)
{
    base = page;
    if (*size + sizeof(struct tag)) < sizeof(struct chunk)
    {
        *size = sizeof(struct chunk) - sizeof(struct tag);
    }

    if (node->tag - (*size + sizeof(struct tag))) >= (sizeof(struct chunk) 
        + sizeof(struct tag))
    {
        t = node;
        node->tag = node->tag - (size + sizeof(struct tag) 
            + sizeof(struct tag));
        trailer = t + node->tag;
        trailer->tag = node->tag;

        header = t + node->tag + sizeof(struct tag);
        header->tag = size + sizeof(struct tag);
        t = header;
        trailer = t + header->tag;
        trailer->tag = trailer->tag | 0x0001;
        header->tag = header->tag | 0x0001;
        return t + sizeof(struct tag);  
    }
    else
    {
        *size = node->tag; 
        prev = base + node->prev;
        next = base + node->next;
        prev->next = node->next;
        next->prev = node->prev; 
        return node + sizeof(struct tag);
    }
}

int
return_chunk_to_buffer_page(struct slab_buffer_page * page, void * chunk, 
    unsigned int size)
{
    void * guard;
    struct chunk * prev_chunk, * next_chunk, * new_chunk;
    unsigned long a;

    base = page;

    node = chunk - sizeof(struct tag);
    trailer = chunk - sizeof(struct tag) - sizeof(struct tag);

    if ((trailer->tag & 0x0001) == 0)
    {
        //we try to coalesce with preceding chunk
        header = trailer - trailer->tag;
        node->tag &= 0xFFFE;
        header->tag += node->tag;
        trailer = header + header->tag;
        trailer->tag = header->tag;
        node = trailer + sizeof(struct tag);
        if ((node->tag & 0x0001) == 0)
        {
            //coalecse with next trailing chunk
            header->tag += node->tag;
            trailer = header + header->tag;
            trailer->tag = header->tag;
            prev = base + node->next;
            next = base + node->prev;
            prev->next = node->next;
            next->prev = node->prev;  
        }
    }
    else
    {
        header = node + node->tag + sizeof(struct tag);
        if ((header->tag & 0x0001) == 0)
        {
            //coalesce with next chunk
            node->tag += header->tag;
            trailer = header + header->tag;
            trailer->tag = header->tag;
            prev = base + header->prev;
            next = base + header->next;
            node->next = header->next;
            node->prev = header->prev;
            prev->next = node - base;
            next->prev = node - base; 
        }
        else
        {
            //create new free node and push on freelist
            header = chunk - sizeof(struct tag);
            header->tag != 0xFFFE;
            trailer = header + header->tag;
            trailer->tag = header->tag;
            header->next = sentinel->next;
            header->prev = sentinel;
            sentinel->next = header - base; 
        }        
    }
} 

int 
get_chunk(unsigned long size)
{
    if (slab_dir_partial->next != &slab_dir_partial)
    {
        chunk = 0;
        for (buff_page = slab_dir_partial.next;
             buff_page != &slab_dir_partial;
             buff_page = buff_page->next;);
        {
            chunk = find_node_big_enough(buff_page, size);
        }
        if (chunk)
        {
            if (buff_page_full(buff_page))
            {
                remove_buff_page(buff_page);
                insert_buff_page(buff_page, slab_dir_full);
            }
            return get_chunk_from_buffer_page(buff_page, chunk);
        } 
    }
    if (slab_dir_empty->next != &slab_dir_empty)
    {
        buff_page = slab_dir_empty->next;
        find_node_big_enough(buff_page, size);
        get_chunk_from_buffer_page(buff_page, chunk);
        remove_buff_page(buff_page);
        insert_buff_page(buff_page, &slab_dir_partial);
    }
    else
    {
        buff_page = get_page();
        find_buff_page_with_node_big_enough();
        get_chunk_from_buffer_page();
        insert_buffer_page(buff_page, &slab_dir_partial);
    }
    return chunk;
}

int
return_chunk()
{

}
