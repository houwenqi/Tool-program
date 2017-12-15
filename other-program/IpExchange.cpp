#include<sys/socket.h>
#include<sys/types.h>
#include "stdio.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "string.h"
int main()
{
	long long i;
	char szip[256];

	time_t t = 1457686004;

    unsigned short port = 63146;
    char * szLocalIP = "47.90.8.159";
    printf("%s:%u,%d,%u\r\n",szLocalIP,inet_addr(szLocalIP),inet_network(szLocalIP),htonl(inet_network(szLocalIP)));
    printf("%u,%u,%u\r\n",port,ntohs(port),htons(port));
	//printf("%s",
    port = 53768;
    printf("%u,%u,%u\r\n",port,ntohs(port),htons(port));
    port = 58242;
    printf("%u,%u,%u\r\n",port,ntohs(port),htons(port));
	
    int ip = -1626842577;
    unsigned int uip = ip;
    printf("%u,%u\r\n",ip,uip);
    while(scanf("%s",szip))
	{
		long ip;
		long port = 0;
		
		if(strlen(szip)>10)
		{
			sscanf(szip,"%llu",&i);
			ip = ((i>>32)&0xffffffff);
			port = ((i>>16)&0xffff);
		}
		else
		{
			sscanf(szip,"%u",&ip);
		}
        printf("szip:%s\r\n");
		//ip = 3508535263;
		struct in_addr addr;
		struct in_addr addr1;  
		struct in_addr addr2;

		addr.s_addr = (unsigned int)ip;
		printf("ip:%u,%s,port:%d\r\n",ip,inet_ntoa(addr),port);
		//addr1.s_addr = ntohl(ip);
		//addr2.s_addr = htonl(ip);
		//printf("ip:%s,%s,%s,port:%d,%d,%d\r\n",inet_ntoa(addr),inet_ntoa(addr1),inet_ntoa(addr2),ntohs(port),htons(port),port);
	}
	return 0;
}
