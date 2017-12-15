#include <signal.h>  
#include <stdio.h> 
#include <unistd.h>   

//通过调用alarm来设置计时器，然后继续做别的事情。当计时器计时到0时，信号发送，处理函数被调用。  
static void timer(int sig) 
{  
    static int count = 0;  
    count++;  
    printf("\ncount = %d\n", count);  
  
    if (sig == SIGALRM)  
    {  
        printf("timer\n");  
    }   
    signal(SIGALRM, timer); //重新注册定时器  
    alarm(3);//定时3s  
   
    return;  
}  
  
//linux定时器的实现  
int main() 
{  
      
    signal(SIGALRM, timer);//执行定时器函数  

    alarm(3); //定时5s   

    getchar(); 

    return 0;  
  
}  