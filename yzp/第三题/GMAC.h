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
        for(int i=0;i<128;i++)
        {
            cout << data[i];
            if(i%4 == 3) cout<<" ";
        }
        cout<<endl;
    }
};

void print_state(uint8_t* state)
{
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
        {
            printf("%x ", state[4*i+j]);
        }
    printf("\n");
}
    
class GMAC_maker
{
public:
    AES_maker aes;
    string str;
    uint128_t H;
    uint8_t Y[16];
    
    //main
    bitset<128> getA()
    {
        bitset<128> A;
        return A;
    }
    void IV_to_Y(uint8_t* IV)
    {
        for(int i=0;i<16;i++) 
            Y[i] = IV[i];
    }
    void encrypt()
    {
        aes.expand();
        uint128_t HH(aes.cipher(zero_plaintext));//ab a3 1e 4e cb 74 1b f0 ce 52 1d bf 7e 2d 77 f7
        H = HH;
    }
};