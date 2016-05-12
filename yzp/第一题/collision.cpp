#include "SHA-1.h"

#include <map>
#include <cstdlib>
#include <iostream>

const int RAND_SEED = 0;


using namespace std;

void print_msg(unsigned int id, int len = 10)
{
    srand(RAND_SEED);
    char s[len+1];
    s[len] = '\0';
    for(int t=0; t<=id; t++)
        for (int i=0; i<len; i++)
            s[i] = rand() % 95 + 32;
    cout << s << endl;
}

void find_collision(int len = 10)
{
    srand(RAND_SEED);
    char s[len+1];
    s[len] = '\0';
    map<unsigned long long, unsigned int> collision_map;
    unsigned int * res = NULL;
    unsigned int id = 0;
    for(;;)
    {
        for (int i=0; i<len; i++)
            s[i] = rand() % 95 + 32;
        res = SHA_1::SHA1(s);
        unsigned long long digest = res[0];
        digest = (digest << 18) | (res[1] >> 14);
        delete[] res;

        map<unsigned long long, unsigned int>::iterator got = collision_map.find(digest);
        if (got != collision_map.end())
        {
            cout << "Find Collision: " << id << " " << got->second << endl;
            print_msg(id);
            print_msg(got->second);
            return;
        }

        collision_map[digest] = id++;
        if (id % 100000 == 0)
            cout << "Generating "<< id << endl;
    }
}

int main()
{
    find_collision();
    //print_msg(43657, 5);
    //print_msg(389516, 6);
    //print_msg(4346771);
    return 0;
}

