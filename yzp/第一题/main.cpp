#include "SHA-1.h"

#include <iostream>

using namespace std;

const char msg[4][100] = {"yangzhican2013011377", "yezipeng2013011404", "D2/;q<IVQq", "e,N>rF 5es"};
int main()
{
    unsigned int * res = NULL;

    for(int t=0; t<4; t++)
    {
        cout << msg[t] << ":" << endl;
        res = SHA_1::SHA1(msg[t], true);
        cout << "SHA-1 : ";
        for(int i = 0; i < 5; i++)
            cout << hex << res[i];
        cout << endl << endl;
        delete[] res;
    }

    return 0;
}
