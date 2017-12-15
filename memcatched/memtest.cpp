#include <iostream>
#include "memcatched.h"
using std::cout;
using std::endl;

int main()
{
    MemCachedClient mc;
    mc.Insert("kingcat11","value123");     
    cout << mc.Get("kingcat") << endl;
    return 1;
};