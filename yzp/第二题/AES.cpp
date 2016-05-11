#include "AES.h"
using namespace std;

int main()
{
    aes.expand();
    aes.cipher();
    printf("\n");
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
