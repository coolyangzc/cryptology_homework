#include "SHA-1.h"

#include <cstdio>
#include <iostream>

using namespace std;
int main()
{
    unsigned int * res = NULL;

    res = SHA_1::SHA1("yangzhican2013011377");
    for(int i = 0; i < 5; i++)
        cout << hex << res[i];
    cout << endl;
    delete[] res;

    res = SHA_1::SHA1("yezipeng2013011404");
    for(int i = 0; i < 5; i++)
        cout << hex << res[i];
    delete[] res;

    return 0;
}
