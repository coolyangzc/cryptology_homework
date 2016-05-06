#ifndef SHA_1
#define SHA_1

#include <cstring>
#include <iostream>

namespace SHA_1
{
    typedef unsigned int uint32_t;
    typedef unsigned long long uint64_t;

    const uint32_t K[4] = {0x5a827999, 0x6ed9eba1, 0x8f1bbcdc, 0xca62c1d6};
    const uint32_t H0[5] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0xc3d2e1f0};

    uint32_t ROTL(uint32_t x, uint32_t n)
    {
        return (x << n) | (x >> (32 - n));
    }

    uint32_t Ch(uint32_t x, uint32_t y, uint32_t z)
    {
        return (x&y) ^ (~x&z);
    }

    uint32_t Parity(uint32_t x, uint32_t y, uint32_t z)
    {
        return x ^ y ^ z;
    }

    uint32_t Maj(uint32_t x, uint32_t y, uint32_t z)
    {
        return (x&y) ^ (x&z) ^ (y&z);
    }

    uint32_t f(uint32_t t, uint32_t x, uint32_t y, uint32_t z)
    {
        if (t < 20)
            return Ch(x, y, z);
        else if (40 <= t && t < 60)
            return Maj(x, y, z);
        else
            return Parity(x, y, z);
    }

    uint32_t* SHA1(const bool * msg, uint64_t size)
    {

        uint64_t N = (size / 512) + 1;
        uint32_t mod = size % 512;
        if (mod > 447)
            N++;
        uint32_t W[80];
        uint32_t a, b, c, d, e;
        uint64_t p = 0;
        uint32_t * H = new uint32_t[5];
        for(uint32_t i = 0; i < 5; i++)
            H[i] = H0[i];

        for(uint64_t i = 0; i < N; i++)
        {
            //Prepare the message schedule
            for(uint32_t t = 0; t < 16; t++)
            {
                W[t] = 0;
                for (uint32_t j = 0; j < 32; j++ ,p++)
                    if (p < size)
                        W[t] = W[t] << 1 | msg[p];
                    else if (p == size)
                        W[t] = W[t] << 1 | 1;
                    else
                        W[t] = W[t] << 1;
            }
            if (i == N-1)
            {
                W[14] = size >> 32;
                W[15] = size & (1ULL << 32) -1;
            }

            for(uint32_t t = 16; t < 80; t++)
                W[t] = ROTL(W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16], 1);

            //Initialize the five working variables, a, b, c, d, and e, with the (i-1)-st hash value
            a = H[0];
            b = H[1];
            c = H[2];
            d = H[3];
            e = H[4];

            for(uint32_t t = 0; t < 80; t++)
            {
                uint32_t T = ROTL(a, 5) + f(t, b, c, d) + e + K[t/20] + W[t];
                e = d;
                d = c;
                c = ROTL(b, 30);
                b = a;
                a = T;
            }

            //Compute the i-th intermediate hash value H(i)
            H[0] = a + H[0];
            H[1] = b + H[1];
            H[2] = c + H[2];
            H[3] = d + H[3];
            H[4] = e + H[4];
        }
        return H;
    }

    uint32_t* SHA1(const char * msg)
    {
        uint32_t len = strlen(msg);
        uint32_t size = len * 8;
        bool * msg_bool = new bool[size];
        uint64_t p = 0;
        for(uint64_t i = 0; i < len; i++)
            for(uint32_t j = 0; j < 8; j++)
                msg_bool[p++] = (msg[i] >> (7-j)) & 1;
        uint32_t* res = SHA1(msg_bool, size);
        delete[] msg_bool;
        return res;
    }


}

#endif // SHA_1
