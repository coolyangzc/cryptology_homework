#ifndef UINT128_T
#define UINT128_T

#include <bitset>
#include <cstdio>

struct uint128_t
{
    std::bitset<128> bit;

    uint128_t(uint32_t x = 0)
    {
        bit = x;
    }

    uint128_t(const uint8_t x[16])
    {
        bit = 0;
        uint8_t p = 0;
        rep(i, 16)
            rep(j, 8)
                if (x[i] & (1 << (7-j)))
                    bit[p++] = 1;
                else
                    bit[p++] = 0;
    }

    uint128_t(const bool * x, uint8_t size = 128)
    {
        rep(i, size)
            bit[i] = x[i];
        for(int i=size; i<128; i++)
            bit[i] = 0;
    }

    bool operator [](int k) {return bit[k];}
    const bool operator [](int k) const {return bit[k];}

    uint8_t* to_uint8_t()
    {
        uint8_t * res =new uint8_t[16];
        uint8_t p = 0;
        rep(i, 16)
        {
            res[i] = 0;
            rep(j, 8)
                if (bit[p++])
                    res[i] |= 1 << (7-j);
        }
        return res;
    }

    void rightshift()
    {
        bit <<= 1;
    }

    uint128_t operator * (uint128_t &b)
    {
        uint128_t z, v(*this);
        uint128_t R(135);//11100001
        rep(i, 128)
        {
            if (b[i])
                z = z^v;
            if (v[127] == 0)
                v.rightshift();
            else
            {
                v.rightshift();
                v = v ^ R;
            }
        }

    }

    uint128_t operator ^ (uint128_t &b)
    {
        uint128_t c;
        c.bit = bit ^ b.bit;
        return c;
    }

    void print(const char* s)
    {
        printf("%s", s);
        uint8_t p = 0;
        rep(i, 16)
        {
            uint8_t tmp = 0;
            rep(j, 8)
                tmp = (tmp << 1) | bit[p++];
            printf("%02x", tmp);
        }
        puts("");
    }

    void print()
    {
        print("");
    }
};

#endif //UINT128_T
