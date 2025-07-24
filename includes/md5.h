#ifndef MD5
# define MD5

// rotate c bits from x to the left, the outside ones are moved to the right
#define LEFTROTATE(x, c)    (((x) << (c)) | ((x) >> (32 - (c))))

typedef struct {
    uint32_t A;
    uint32_t B;
    uint32_t C;
    uint32_t D;
}   t_md5_state;

int md5_hash();


#endif