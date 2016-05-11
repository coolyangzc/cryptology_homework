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
    //gmac.encrypt("yezipeng2013011404");
    gmac.encrypt_null().print_data();
    return 0;
}