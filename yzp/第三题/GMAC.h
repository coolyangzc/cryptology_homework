#include "AES.h"
#include <bitset>
#include <vector>
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

bool getBit(string data,int n)
{
    int q,r;
    q = n/8;
    r = n - 8*q;
    if(q >= data.size()) return 0;
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
    
    uint128_t(string s)
    {
        for(int i=0;i<128;i++)
            data[i] = getBit(s,i);
    }
    
    //method
    bool operator [](int n)
    {
        return data[n];
    }
    
    uint128_t rightshift()
    {
        uint128_t res;
        res.data = data<<1;
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
        uint128_t R;
        R.data[0] = 1;R.data[1] = 1;R.data[2] = 1;R.data[7] = 1;
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
                v = v.rightshift()^R;
            }
        }
        return z;
    }
    
    //print
    void print_data()
    {
        int temp = 0;
        for(int i=0;i<128;i++)
        {
            temp = temp*2 + int(data[i]);
            if(i%4 == 3) 
            {
                cout<<hex<<temp;
                temp = 0;
            }
            if(i%8 == 7) 
            {
                cout<<" ";
            }
        }
        cout<<endl;
    }
    
    //for GHASH
    bitset<128> int_to_bit(int len)
    {
        bitset<128> inverse = len;
        bitset<128> res;
        for(int i=0;i<128;i++)
            res[i] = inverse[127-i];
        return res;
    }
    void set_len(int len1,int len2)
    {
        data = (int_to_bit(len1)>>64)^int_to_bit(len2);
        cout<<"len A|len C :"<<endl;
        print_data();
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
    uint128_t H;
    uint8_t Y[16];
    
    int A_len;
    int C_len;
    vector<uint128_t > workspace;
    
    void IV_to_Y(uint8_t* IV)
    {
        for(int i=0;i<16;i++) 
            Y[i] = IV[i];
    }
    
    uint128_t GHASH()
    {
        cout<<"string to 128 :"<<endl;
        for(int i=0;i<workspace.size();i++)
        {
            workspace[i].print_data();
        }
        uint128_t res;
        if(workspace.size() == 0)
        {
            res = res*H;
        }
        else
        {
            for(int i=0;i<workspace.size();i++)
            {
                res = (res^workspace[i])*H;
                cout<<"middle"<<i<<" :"<<endl;
                res.print_data();
            }
            uint128_t len_link;
            len_link.set_len(A_len,C_len);
            res = (res^len_link)*H;
        }
        cout<<"GHASH :"<<endl;
        res.print_data();
        return res;
    }
    //main
    uint128_t encrypt()
    {
        aes.expand();
        uint128_t HH(aes.cipher(zero_plaintext));//ab a3 1e 4e cb 74 1b f0 ce 52 1d bf 7e 2d 77 f7
        H = HH;
        uint128_t E(aes.cipher(Y));
        cout<<"H=\n";
        H.print_data();
        cout<<"E=\n";
        E.print_data();
        uint128_t T = GHASH()^E;
        cout<<"T=\n";
        return T;
    }
    
    uint128_t encrypt(string s)
    {
        int len = s.size();
        A_len = 8*len;
        C_len = 0;
        workspace.clear();
        for(int i=0;i<len;i+=16)
        {
            string sub = s.substr(i,16);
            uint128_t temp128(sub);
            workspace.push_back(temp128);
        }
        return encrypt();
    }
    
    uint128_t encrypt_null()
    {
        workspace.clear();
        A_len = 0;
        C_len = 0;
        return encrypt();
    }
    //a test in paper
    uint128_t encrypt_test()
    {
        workspace.clear();
        A_len = 0;
        C_len = 128;
        aes.expand();
        uint128_t HH(aes.cipher(zero_plaintext));//ab a3 1e 4e cb 74 1b f0 ce 52 1d bf 7e 2d 77 f7
        H = HH;
        uint128_t E(aes.cipher(Y));
        cout<<"H=\n";
        H.print_data();
        cout<<"E=\n";
        E.print_data();
        //GHASH
        uint128_t G;
        Y[15]++;
        uint128_t C(aes.cipher(Y));
        cout<<"C=\n";
        C.print_data();
        
        G = (G^C)*H;
        
        cout<<"middle :"<<endl;
        G.print_data();
        
        uint128_t len_link;
        len_link.set_len(A_len,C_len);
        G = (G^len_link)*H;
        cout<<"GHASH :"<<endl;
        G.print_data();
        return G^E;
    }
};