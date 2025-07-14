# include "ft_ssl.h"

// md5 inverversal constants
static const uint32_t s[64] = {
    7, 12, 17, 22,   7, 12, 17, 22,   7, 12, 17, 22,   7, 12, 17, 22,
    5,  9, 14, 20,   5,  9, 14, 20,   5,  9, 14, 20,   5,  9, 14, 20,
    4, 11, 16, 23,   4, 11, 16, 23,   4, 11, 16, 23,   4, 11, 16, 23,
    6, 10, 15, 21,   6, 10, 15, 21,   6, 10, 15, 21,   6, 10, 15, 21
};

static const uint32_t K[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

uint32_t F(uint32_t b, uint32_t c, uint32_t d) {
    return (b & c) | ((~b) & d);
}

uint32_t G(uint32_t b, uint32_t c, uint32_t d) {
    return (d & b) | ((~d) & c);
}

uint32_t H(uint32_t b, uint32_t c, uint32_t d) {
    return b ^ c ^ d;
}

uint32_t I(uint32_t b, uint32_t c, uint32_t d) {
    return c ^ (b | ~d);
}

uint8_t *md5_pad(uint8_t *msg, size_t len, size_t *new_len) {
    // Add 0x80 then 0s so len can be modulo 512
    size_t padding_len = (56 - (len + 1) % 64) % 64;
    *new_len = len + 1 + padding_len + 8;

    uint8_t *padded_msg = ft_calloc(*new_len, 1);

    ft_memcpy(padded_msg, msg, len);
    padded_msg[len] = 0x80;

    uint64_t bit_len = (uint64_t) len * 8;
    ft_memcpy(padded_msg + *new_len - 8, &bit_len, 8);

    return padded_msg;
}

void    process_block(uint8_t *block, t_md5_state *state) {
    uint32_t M[16];
    size_t  index = 0;
    // Split the 512 bits block in 16 32bits blocks
    while (index < 16) {
        M[index] = (uint32_t)block[index * 4]
        | ((uint32_t)block[index * 4 + 1] << 8)
        | ((uint32_t)block[index * 4 + 2] << 16)
        | ((uint32_t)block[index * 4 + 3] << 24);
        index++;
    }

    // get registers
    uint32_t a = state->A;
    uint32_t b = state->B;
    uint32_t c = state->C;
    uint32_t d = state->D;

    index = 0;
    // 64 operations per block
    while (index < 64) {
        uint32_t f, g;

        // Apply function depending on block operation
        if (index < 16) {
            f = F(b, c, d);
            g = index;
        } else if(index < 32) {
            f = G(b, c, d);
            g = (5 * index + 1) % 16;
        } else if (index < 48) {
            f = H(b, c, d);
            g = (3 * index + 5) % 16;
        } else {
            f = I(b, c, d);
            g = (7 * index) % 16;
        }

        uint32_t tmp = d;
        d = c;
        c = b;
        // Add some "randomness" by rotating bits
        b = b + LEFTROTATE((a + f + K[index] + M[g]), s[index]);
        a = tmp;

        index++;
    }

    state->A += a;
    state->B += b;
    state->C += c;
    state->D += d;
}


int md5_hash(char *args) {
    (void) args;
    printf("%s\n", args);

    // init md5 registers
    t_md5_state state = {
        .A = 0x67452301,
        .B = 0xefcdab89,
        .C = 0x98badcfe,
        .D = 0x10325476
    };

    size_t  padded_len = 0;
    uint8_t *padded_msg = md5_pad((unsigned char*) args, ft_strlen(args), &padded_len);
    
    size_t  offset = 0;
    while (offset < padded_len) {
        uint8_t *block = padded_msg + offset;
        process_block(block, &state);
        offset += 64;
    }

    uint8_t digest[16];
    ft_memcpy(digest, &state.A, 4);
    ft_memcpy(digest + 4, &state.B, 4);
    ft_memcpy(digest + 8, &state.C, 4);
    ft_memcpy(digest + 12, &state.D, 4);

    for (int i = 0; i < 16; i++)
        ft_printf("%02x", digest[i]);
    ft_printf("\n");

    free(padded_msg);

    return 0;
}