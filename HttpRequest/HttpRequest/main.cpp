
#include "HttpRequest.h"

//appid,pass,mobile,text,extCode,timer,orderId

int main()
{
	HttpRequest* Http = new HttpRequest;
	
	char* str = (char*)malloc(BUFSIZE);
	
	memset(str, 0, BUFSIZE);

	char* str1 = (char*)malloc(100);
	memset(str1, 0, 100);
    strcat(str1, "http://sms.combmobile.com/api.do?act=ms");

    char* str2 = (char*)malloc(2048);
    memset(str2, 0, 2048);
    strcat(str2, "appid=1004&pass=EA8A706C4C34A168&mobile=18576646727&text=111111");


	if(Http->HttpPost(str1, str2, str)) {
		printf("%s\n", str);
	} else {
		printf("HttpPost请求失败!\n");
	}	
	
	
	free(str);
	free(str1);
	free(str2);

	return 0;
}