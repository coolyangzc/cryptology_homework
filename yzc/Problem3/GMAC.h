#ifndef GMAC
#define GMAC

#include "AES.h"
#include "uint128_t.h"

#include <cstdio>
#include <cstring>

namespace GMAC
{
    #define rep(i,n) for(int i=0; i<n; i++)
    #define For(i,n) for(int i=1; i<=n; i++)
    using namespace std;

    uint128_t GHASH(uint128_t H, const bool * A, uint64_t lenA)
    {
        uint128_t X;
        uint8_t size = 0;
        uint64_t p = 0;
        while (p < lenA)
        {
            if (lenA - p > 128)
                size = 128;
            else
                size = lenA - p;
            uint128_t block(A + p, size);
            p += size;
            X = X ^ block;
            X = X * H;
        }
        uint128_t block(lenA);
        X = X ^ block;
        X = X * H;
        return X;
    }

    uint128_t encrypt(const bool * A, uint64_t lenA, const uint8_t IV[12], const uint8_t key[16], bool print = false)
    {
        uint128_t zero;
        uint128_t H(AES::cipher(zero.to_uint8_t(), key));

        uint8_t Y0[16];
        rep(i, 12)
            Y0[i] = IV[i];
        Y0[12] = Y0[13] = Y0[14] = 0x00;
        Y0[15] = 0x01;

        uint128_t right(AES::cipher(Y0, key));
        uint128_t left = GHASH(H, A, lenA);

        if (print)
        {
            H.print("\nH:\n");
            right.print("\nE(K, Y0):\n");
            left.print("\nGHASH(H, A, C):\n");
        }

        return left ^ right;
    }

    uint128_t encrypt(const char * A, const uint8_t IV[12], const uint8_t key[16], bool print = false)
    {
        uint32_t len = strlen(A);
        uint32_t lenA = len * 8;
        bool * msg_bool = new bool[lenA];
        uint64_t p = 0;
        for(uint64_t i = 0; i < len; i++)
            for(uint32_t j = 0; j < 8; j++)
                msg_bool[p++] = (A[i] >> (7-j)) & 1;
        if (print) printf("\nA:\n%s\n", A);
        uint128_t res = encrypt(msg_bool, lenA, IV, key, print);
        delete[] msg_bool;
        return res;
    }
}

#endif //GMAC

