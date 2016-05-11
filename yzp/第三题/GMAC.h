#include "AES.h"
#include <bitset>
using namespace std;

uint8_t zero_plaintext[] = {
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00};
    
uint8_t for_getBit[8] = {
    0x80,0x40,0x20,0x10,
    0x08,0x04,0x02,0x01
};

bool getBit(uint8_t* data,int n)
{
    int q,r;
    q = n/8;
    r = n - 8*q;
    bool temp = data[q]&for_getBit[r];
    return temp;
}
    
    
class uint128_t
{
public:
    bitset<128> data;
    //create
    uint128_t(){}
    uint128_t(uint8_t* x)
    {
        for(int i=0;i<128;i++)
            data[i] = getBit(x,i);
    }
    //method
    bool operator [](int n)
    {
        return data[n];
    }
    uint128_t rightshift()
    {
        uint128_t res;
        res.data = data>>1;
        return res;
    }
    uint128_t operator ^(uint128_t &x)
    {
        uint128_t res;
        res.data = data^x.data;
        return res;
    }
    uint128_t operator *(uint128_t &y)//this * y
    {
        uint128_t z, v(*this);
        for(int i=0;i<128;i++)
        {
            if(y[i])
                z = z^v;
            if(v[127] == 0)
            {
                v = v.rightshift();
            }
            else
            {
                v = v.rightshift()^(*this);
            }
        }
        return z;
    }
    //print
    void print_data()
    {
        cout<<data<<endl;
        printf("\n");
    }
};
    
class GMAC_maker
{
public:
    AES_maker aes;
    uint128_t H;
};