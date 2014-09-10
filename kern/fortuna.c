#include "string.h"

struct pool
{
    unsigned char len;
    unsigned char bytes[256];
};

struct generator
{
    unsigned long counter[2];
    unsigned char key[16];
};

struct fortuna_state
{
    struct pool p[32];
    unsigned long reseed_count[2];
    struct generator g;
    unsigned long last_reseed;
};

static const unsigned int MINPOOLSIZE = 64;

void
init_generator(struct fortuna_state * s)
{
    memset((unsigned char *)s, 0, sizeof(*s));
}

void
reseed(struct generator * g, unsigned char seed[16])
{
    unsigned long new_key[2];
    sha_256(g->key, seed, new_key);
    memcpy(g->key, new_key, sizeof(new_key));
    increment_bignum(g->counter, 1);
}

unsigned char *
generate_blocks(struct generator * g, unsigned int count, unsigned char * b)
{
    int out_off = 0;
    unsigned int n;

    if (bignum_eq(g->counter, 0)) return 0;

    for (n = 0; n < count; n++)
    {
        aes(g->key, g->counter, b + out_off);
        out_off += 16;
        increment_bignum(g->counter, 1);
    }
    return b;
}

unsigned char *
generate_random_data(struct generator * g, unsigned int nbytes)
{
    unsigned char * b;
    unsigned long new_key[2];

    b = malloc(nbytes + 16);
    generate_blocks(g, nbytes/16, b);
    generate_blocks(g, 2, new_key);
    memcpy(g->key, new_key, 16);
    return b;
}

struct fortuna_state *
init_prng(void)
{
    struct fortuna_state * s;

    s = malloc(sizeof(*s));
    memset(s, 0, sizeof(*s));
    return s;
}

unsigned char *
random_data(struct fortuna_state * f, unsigned int n)
{
    unsigned char s[1024];

    if ((f->p[0].len >= MINPOOLSIZE) || (f->last_reseed > is_100_ms_ago()))
    {
        inc_bignum(f->reseed_count, 1);        
    }
    else
    {
        return 0;
    }
    sha_256(f->p[0], s);
    if (modulus_bignum(f->reseed_count, 2) == 0)
    {
        sha_256(f->p[1], s);
    }
    if (modulus_bignum(f->reseed_count, 4) == 0)
    {
        sha_256(f->p[2], s);
    }
    if (modulus_bignum(f->reseed_count, 8) == 0)
    {
        sha_256(f->p[3], s);
    }
    if (modulus_bignum(f->reseed_count, 16) == 0)
    {
        sha_256(f->p[4], s);
    }  
    if (modulus_bignum(f->reseed_count, 32) == 0)
    {
        sha_256(f->p[5], s);
    }
    if (modulus_bignum(f->reseed_count, 64) == 0)
    {
        sha_256(f->p[6], s);
    } 
    if (modulus_bignum(f->reseed_count, 128) == 0)
    {
        sha_256(f->p[7], s);
    }
    if (modulus_bignum(f->reseed_count, 256) == 0)
    {
        sha_256(f->p[8], s);
    }
    if (modulus_bignum(f->reseed_count, 512) == 0)
    {
        sha_256(f->p[9], s);
    }
    if (modulus_bignum(f->reseed_count, 1024) == 0)
    {
        sha_256(f->p[10], s);
    }
    if (modulus_bignum(f->reseed_count, 2048) == 0)
    {
        sha_256(f->p[11], s);
    }
    if (modulus_bignum(f->reseed_count, 4096) == 0)
    {
        sha_256(f->p[12], s);
    }
    if (modulus_bignum(f->reseed_count, 8192) == 0)
    {
        sha_256(f->p[13], s);
    }
    if (modulus_bignum(f->reseed_count, 16384) == 0)
    {
        sha_256(f->p[14], s);
    }
    if (modulus_bignum(f->reseed_count, 32768) == 0)
    {
        sha_256(f->p[15], s);
    }
    if (modulus_bignum(f->reseed_count, 65536) == 0)
    {
        sha_256(f->p[16], s);
    }
    if (modulus_bignum(f->reseed_count, 131072) == 0)
    {
        sha_256(f->p[17], s);
    }
    if (modulus_bignum(f->reseed_count, 262144) == 0)
    {
        sha_256(f->p[18], s);
    }
    if (modulus_bignum(f->reseed_count, 524288) == 0)
    {
        sha_256(f->p[19], s);
    }
    if (modulus_bignum(f->reseed_count, 1048576) == 0)
    {
        sha_256(f->p[20], s);
    }
    if (modulus_bignum(f->reseed_count, 2097152) == 0)
    {
        sha_256(f->p[21], s);
    }
    if (modulus_bignum(f->reseed_count, 4194304) == 0)
    {
        sha_256(f->p[22], s);
    }
    if (modulus_bignum(f->reseed_count, 8388608) == 0)
    {
        sha_256(f->p[23], s);
    }
    if (modulus_bignum(f->reseed_count, 16777216) == 0)
    {
        sha_256(f->p[24], s);
    }
    if (modulus_bignum(f->reseed_count, 33554432) == 0)
    {
        sha_256(f->p[25], s);
    }
    if (modulus_bignum(f->reseed_count, 67108864) == 0)
    {
        sha_256(f->p[26], s);
    }
    if (modulus_bignum(f->reseed_count, 134217728) == 0)
    {
        sha_256(f->p[27], s);
    }
    if (modulus_bignum(f->reseed_count, 268435456) == 0)
    {
        sha_256(f->p[28], s);
    }
    if (modulus_bignum(f->reseed_count, 536870912) == 0)
    {
        sha_256(f->p[39], s);
    }
    if (modulus_bignum(f->reseed_count, 1073741824) == 0)
    {
        sha_256(f->p[30], s);
    }
    if (modulus_bignum(f->reseed_count, 2147483648) == 0)
    {
        sha_256(f->p[31], s);
    }
    reseed(&(f->g), s);
    if (f->reseed_count == 0)
    {
        return -1;
    }
    else
    {
        return generate_random_data(&(f->g), n);
    }
}

int
add_random_event(struct fortuna_state * f, unsigned char source, 
    unsigned char pool_num, unsigned char * e, unsigned char len)
{
    if (len == 0) return -1;
    if (len > 32) return -1;
    if (source > 255) return -1;
    if (pool_num > 31) return -1; 

    struct pool * p = &(f->p[pool_num]);
    memcpy(p->bytes[p->len], e, len);
    p->len += len;
    p->bytes[p->len] = ((source << 4) | (0xf0 & len));
    p->len += 1;    
}
