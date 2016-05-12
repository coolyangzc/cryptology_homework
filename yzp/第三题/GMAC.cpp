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
    gmac.encrypt("yezipeng2013011404").print_data();
    //gmac.encrypt("yangzhican2013011377").print_data();
    //gmac.encrypt_null().print_data();
    //gmac.encrypt_test().print_data();
    
    /*uint128_t a;
    a.set_len(18);
    a.rightshift();*/
    return 0;
}