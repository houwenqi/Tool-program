
#include <stdio.h>
#include <string.h>
#include <string>
#include "json/json.h"

using namespace std;
int main()
{
	string content = "{\"uploadid\": \"UP000000\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}";
	printf("content is %s\n",content.c_str() );
	const char* str = content.c_str();

    Json::Reader reader;  
    Json::Value root;  
    string upload_id;
    int code;
    if (reader.parse(str, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素  
    {  
        upload_id = root["uploadid"].asString();  // 访问节点，upload_id = "UP000000"  
        code = root["code"].asInt();    // 访问节点，code = 100 
    }  
    printf("upid is %s\n",upload_id.c_str() );
    printf("code is %d\n",code );

    return 0;
}