#ifndef SHA256
# define SHA256

// rotate c bits from x to the right, the outside ones are moved to the left
#define RIGHT_ROTATE(x, n)   ((x >> n) | (x << (32 - n)))
// move bits to right
#define SHR(x, n)    (x >> n)

// return y if x is 1 else z
#define CH(x, y, z)      ((x & y) ^ (~x & z))
// return 1 if 2 or 3 bits are 1
#define MAJ(x, y, z)     ((x & y) ^ (x & z) ^ (y & z))

#define SIG0(x)  (RIGHT_ROTATE(x, 2) ^ RIGHT_ROTATE(x, 13) ^ RIGHT_ROTATE(x, 22))
#define SIG1(x)  (RIGHT_ROTATE(x, 6) ^ RIGHT_ROTATE(x, 11) ^ RIGHT_ROTATE(x, 25))

#define Theta0(x)  (RIGHT_ROTATE(x, 7) ^ RIGHT_ROTATE(x, 18) ^ SHR(x, 3))
#define Theta1(x)  (RIGHT_ROTATE(x, 17) ^ RIGHT_ROTATE(x, 19) ^ SHR(x, 10))


int sha256_hash();

#endif