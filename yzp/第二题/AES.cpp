#include "AES.h"
using namespace std;

uint8_t zero_plaintext[] = {
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00};

uint8_t test_plaintext[] = {
    0x32,0x43,0xF6,0xA8,
    0x88,0x5A,0x30,0x8D,
    0x31,0x31,0x98,0xA2,
    0xE0,0x37,0x07,0x34};
    
    
void print_state(uint8_t* state)
{
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
        {
            printf("%x ", state[4*i+j]);
        }
    printf("\n");
}

int main()
{
    AES_maker aes;
    aes.expand();
    printf("crypto is:\n");
    print_state(aes.cipher(test_plaintext));
    printf("\n");
    printf("expand_key is:\n");
    for(int i=0;i<ROUNDS_PLUS;i++)
    {
        for(int j=0;j<4;j++)
        {
            for(int k=0;k<4;k++)
            {
                printf("%x ", aes.expand_key[i][j][k]);
            }
        }
        printf("\n");
    }
    return 0;
}
