#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

long getmictime()
{
    struct timeval tv;
    gettimeofday(&tv,NULL); 

    return tv.tv_sec*1000 + tv.tv_usec/1000;
}

int main()
{
    long int t_flg = 0;

    for( int i = 0; i<5; i++ )
    {
        sleep(1);

        long int t_now = getmictime();
        printf("i[%d],time is [%lu]\n",i,t_now - t_flg);
        if( t_now - t_flg < 3000)
        {
            printf("i[%d], NO NO NO !!! \n",i);

        }
        else
        {
            printf("i[%d], GO GO GO !!! \n",i);
            t_flg = t_now;
            continue;
        }
    }

    return 0;
}