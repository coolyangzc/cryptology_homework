#include "AES.h"
using namespace std;

uint8_t zero_plaintext[] = {
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00};
    
    
class uint128_t
{
public:
    uint8_t data[16];
    uint128_t(){}
    uint128_t(uint8_t* x)
    {
        for(int i=0;i<16;i++) 
            data[i] = x[i];
    }
    uint128_t operator ^(uint128_t &x)
    {
        uint128_t res;
        for(int i=0;i<16;i++) 
            res[i] = x[i]^data[i];
        return res;
    }
    uint128_t operator *(uint128_t &x)
    {
        uint128_t res;
        //
        return res;
    }
}
    
class GMAC_maker
{
public:
    AES_maker aes;
    uint128_t H;
};