#include "GMAC.h"
using namespace std;

uint8_t test_iv[] = {
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x01};
    

int main()
{
    GMAC_maker gmac;
    gmac.IV_to_Y(test_iv);
    gmac.encrypt("qiandichen2013011402");
    //gmac.encrypt_null().print_data();
    
    /*uint128_t a;
    a.set_len(18);
    a.rightshift();*/
    return 0;
}