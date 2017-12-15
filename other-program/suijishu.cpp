/*
srand((unsigned)time(null));
(a,b) (rand()%(b-a+1))+a-1
[a,b) (rand()%(b-a))+a
(a,b] (rand()%(b-a))+a+1
[a,b] (rand()%(b-a+1))+a
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int i, m, n;
    srand((int)time(NULL));
    m = 1000;
    n = 9999;
    for(i=0; i<10; i++)
    {
        printf("%d\n", rand()%(n-m+1)+m);
    }
    return 0;
}