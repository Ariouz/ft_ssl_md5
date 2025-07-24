# include "ft_ssl.h"
# include "sha256.h"

static const uint32_t K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};


uint8_t *sha256_pad(const uint8_t *msg, size_t len, size_t *new_len) {
    size_t bit_len = len * 8;
    size_t pad_len;

    pad_len = len + 1;
    while ((pad_len % 64) != 56)
        pad_len++;

    *new_len = pad_len + 8;

    uint8_t *padded = ft_calloc(*new_len, sizeof(uint8_t));
    if (!padded)
        return NULL;

    ft_memcpy(padded, msg, len);

    padded[len] = 0x80;

    padded[*new_len - 8] = (bit_len >> 56) & 0xff;
    padded[*new_len - 7] = (bit_len >> 48) & 0xff;
    padded[*new_len - 6] = (bit_len >> 40) & 0xff;
    padded[*new_len - 5] = (bit_len >> 32) & 0xff;
    padded[*new_len - 4] = (bit_len >> 24) & 0xff;
    padded[*new_len - 3] = (bit_len >> 16) & 0xff;
    padded[*new_len - 2] = (bit_len >> 8) & 0xff;
    padded[*new_len - 1] = (bit_len) & 0xff;

    return padded;
}

void sha256_transform(uint32_t state[8], const uint8_t block[64]) {
    uint32_t W[64];
    uint32_t a, b, c, d, e, f, g, h;

    // create 16 blocks of 32 bits
    for (int i = 0; i < 16; i++) {
       W[i] =   ((uint32_t)block[i * 4] << 24) |
                ((uint32_t)block[i * 4 + 1] << 16) |
                ((uint32_t)block[i * 4 + 2] << 8) |
                ((uint32_t)block[i * 4 + 3]);
    }

    // extends blocks to 64 bits
    for (int i = 16; i < 64; i++) {
        uint32_t s0 = Theta0(W[i - 15]);
        uint32_t s1 = Theta1(W[i - 2]);
        W[i] = W[i - 16] + s0 + W[i - 7] + s1;
    }

    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];
    f = state[5];
    g = state[6];
    h = state[7];

    for (int i = 0; i < 64; i++) {
        uint32_t T1 = h + SIG1(e) + CH(e, f, g) + K[i] + W[i];
        uint32_t T2 = SIG0(a) + MAJ(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    state[5] += f;
    state[6] += g;
    state[7] += h;
}

void print_sha256_digest(void *void_state) {
    uint32_t *state = (uint32_t *)void_state;
    uint8_t digest[32];

    for (int i = 0; i < 8; i++) {
        digest[i * 4]     = (state[i] >> 24) & 0xff;
        digest[i * 4 + 1] = (state[i] >> 16) & 0xff;
        digest[i * 4 + 2] = (state[i] >> 8) & 0xff;
        digest[i * 4 + 3] = state[i] & 0xff;
    }

    for (int i = 0; i < 32; i++) {
        ft_printf("%02x", digest[i]);
    }
}

static int hash(t_input *input) {
    uint32_t state[8] = {
        0x6a09e667,
        0xbb67ae85,
        0x3c6ef372,
        0xa54ff53a,
        0x510e527f,
        0x9b05688c,
        0x1f83d9ab,
        0x5be0cd19
    };

    size_t  padded_len = 0;
    uint8_t *padded_msg = sha256_pad((unsigned char*) input->value, ft_strlen(input->value), &padded_len);
    if (!padded_msg)
        return fatal_error("Failed to pad sha256 message");

    // process all blocks
    for (size_t i = 0; i < padded_len; i += 64) {
        sha256_transform(state, padded_msg + i);
    }

    free(padded_msg);
    if (input->type == SRC_STDIN)
        print_stdin_digest(&state, input, print_sha256_digest);
    
    if (input->type == SRC_SFLAG)
        print_sflag_digest(&state, input, print_sha256_digest, "SHA256");

    if (input->type == SRC_FILE)
        print_file_digest(&state, input, print_sha256_digest, "SHA256");

    return 0;
}

int sha256_hash() {
    t_list *inputs = ssl->inputs;

    t_list *curr = inputs->next;

    while (curr) {
        t_input *input = (t_input *) curr->content;
        if (input->type == SRC_FILE) {
            if (read_file_to(input->value, &input->value) != ERROR_FATAL)
                hash(input);
        }
        else hash(input);

        curr = curr->next;
    }

    return 0;
}