#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


char* cmd_system(const char* command)
{
    char* result = "";
    FILE *fpRead;
    fpRead = popen(command, "r");
    char buf[1024];
    memset(buf,'\0',sizeof(buf));
    while(fgets(buf,1024-1,fpRead)!=NULL)
    { 
    	result = buf;
    }
    if(fpRead!=NULL)
        pclose(fpRead);
    return result;
}

int main(int argc,char* argv[])
 {
 	char opt ;
 	printf("The mode you do is [%s] \n",argv[1]);

	printf("**** a : close                    ****\n");
	printf("**** b : delete                   ****\n");
	printf("**** c : delshell                 ****\n");
	printf("**** d : delself                  ****\n");
	printf("**** q : Quit                     ****\n");

	while(1)
	{
		printf("**** input one char to test :(a,b,c,d,q) ****\n"); 
		scanf("%c",&opt);
		switch(opt)
		{
			case 'a':
				printf("close mode....\n");
				char cmd0[100];
				sprintf(cmd0, "chmod 777 /home/msgbin/%s/stop.sh",argv[1]); 
				system(cmd0);
				//char* ret0 = cmd_system(cmd0);
				//printf("chmod result:%s\n",ret0);

				char cmd[100];
				sprintf(cmd, "sh /home/msgbin/%s/stop.sh",argv[1]); 
				system(cmd);
				//char* ret = cmd_system(cmd);
				//printf("stop result:%s\n",ret);

				break;

			case 'b':
				printf("delete mode.... \n");
				char cmd1[100];
				sprintf(cmd1,"rm -rf /home/msgbin/%s/test",argv[1]);
				system(cmd1);
			    //char* ret1 = cmd_system(cmd1);
				//printf("delete result:%s\n",ret1);
				break;
			
			case 'c':
				printf("delshell...\n");
				break;
			
			case 'd':
				printf("delself..\n");
				break;

			case 'q':
				exit(0);
				
			default:
			break;
		}
	}
	return 0;
}