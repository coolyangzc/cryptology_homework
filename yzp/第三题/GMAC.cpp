#include "GMAC.h"
using namespace std;

uint8_t test_plaintext[] = {
    0xA7,0xB3,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00};
    

int main()
{
    uint128_t test128(test_plaintext);
    uint128_t zero128(zero_plaintext);
    cout<<(test128*zero128).data<<endl;
    cout<<(zero128*test128).data<<endl;
    cout<<(test128*test128).data<<endl;
    return 0;
}