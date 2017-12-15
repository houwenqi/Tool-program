#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <curl/curl.h>  
#include <string>
//生成随机数
#include <cstdlib>
#include <ctime>
//json
#include "json.h"

using namespace std;
  
#define POSTURL "http://sms.combmobile.com/api.do?act=ms" 

Json::Reader jreader;  
Json::Value jroot; 
  
size_t handle_data(void* buffer,size_t size,size_t nmemb,string &content)  
{  
    string temp;
    long sizes = size * nmemb;
    temp = string((char*)buffer,sizes);
    content += temp;

    printf("content is %s\n",content.c_str() );

    const char* str = content.c_str(); 
    int code;
    if (jreader.parse(str, jroot))  // reader将Json字符串解析到root，root将包含Json里所有子元素  
    {  
        code = jroot["code"].asInt();    // 访问节点，code = 100 
    }  
    printf("code is %d\n",code );
    return sizes;  
}  

int main(int argc,char *argv[])  
{
    char POSTFIELDS[1024] = "";
    int appid = 1005;
    char pass[100] = "e10adc3949ba59a";
    long mobile = 18576646;
     
    char num[6];
    int i,mark;
    srand( (unsigned)time( NULL ) );//初始化时间种子
    for(i=0;i<6;i++)//循环6次，生成6个字符密码
    {
        mark=rand()%10;//产生从0到9共个随机数
        num[i]=mark+48;//如果随机数在0到9之间，则密码转化为字符型的0到9
    }

    sprintf(POSTFIELDS,"appid=%d&pass=%s&mobile=%ld&text=[蜂巢互联]您的验证码是：%s",appid,pass,mobile,num);
    printf("data is %s\n",POSTFIELDS );

    CURL *curl;  
    CURLcode res;  
    struct curl_slist *http_header = NULL;  
    string content;
  
    curl = curl_easy_init();  
    if (!curl)  
    {  
        fprintf(stderr,"curl init failed\n");  
        return -1;  
    }  
  
    curl_easy_setopt(curl,CURLOPT_URL,POSTURL); //url地址  
    curl_easy_setopt(curl,CURLOPT_POSTFIELDS,POSTFIELDS); //post参数  
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&handle_data); //对返回的数据进行操作的函数地址  
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,&content); //这是write_data的第四个参数值  
    curl_easy_setopt(curl,CURLOPT_POST,1); //设置问非0表示本次操作为post  
    curl_easy_setopt(curl,CURLOPT_VERBOSE,0); //打印调试信息  
    curl_easy_setopt(curl,CURLOPT_HEADER,0); //将响应头信息和相应体一起传给write_data  
    curl_easy_setopt(curl,CURLOPT_FOLLOWLOCATION,0); //设置为非0,响应头信息location  
    curl_easy_setopt(curl,CURLOPT_COOKIEFILE,"/Users/zhu/CProjects/curlposttest.cookie"); 

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)  
    {  
        switch(res)  
        {  
            case CURLE_UNSUPPORTED_PROTOCOL:  
                fprintf(stderr,"不支持的协议,由URL的头部指定\n");  
            case CURLE_COULDNT_CONNECT:  
                fprintf(stderr,"不能连接到remote主机或者代理\n");  
            case CURLE_HTTP_RETURNED_ERROR:  
                fprintf(stderr,"http返回错误\n");  
            case CURLE_READ_ERROR:  
                fprintf(stderr,"读本地文件错误\n");  
            default:  
                fprintf(stderr,"返回值:%d\n",res);  
        }  
        return -1;  
    }

    curl_easy_cleanup(curl);  
}  