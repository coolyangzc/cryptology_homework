#include "AES.h"

#include <cstdio>
#include <iostream>

using namespace std;

const uint8_t key[16] = {0x3A,0xE1,0x15,0x62,0xA8,0xF3,0xC7,0x1A,0x2B,0xF6,0xDF,0xA1,0x50,0x9B,0xCA,0xF1};
const uint8_t plaintext[16] = {0x32,0x43,0xF6,0xA8,0x88,0x5A,0x30,0x8D,0x31,0x31,0x98,0xA2,0xE0,0x37,0x07,0x34};
int main()
{
    puts("Plaintext:");
    rep(i, 16)
        printf("%02x", plaintext[i]);
    puts("");puts("");
    puts("Key:");
    rep(i, 16)
        printf("%02x", key[i]);
    puts("");puts("");

    uint8_t w[11][4][4];
    AES::keyExpansion(key, w);
    puts("Round Keys:");
    rep(i, 11)
    {
        printf("Round %2d: ", i);
        rep(j, 4)
            rep(k, 4)
                printf("%02x", w[i][j][k]);
        puts("");
    }
    puts("");
    puts("Cryptotext:");
    uint8_t* cryptotext = AES::cipher(plaintext, key);
    rep(i, 16)
        printf("%02x", cryptotext[i]);
    puts("");
    delete[] cryptotext;
    return 0;
}
