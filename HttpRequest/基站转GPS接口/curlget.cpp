#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <curl/curl.h>  
#include <string>
//json
#include "json.h"

using namespace std;
  
Json::Reader jreader;  
Json::Value jroot; 
  
size_t handle_data(void* buffer,size_t size,size_t nmemb,string &content)  
{  
    string temp;
    long sizes = size * nmemb;
    temp = string((char*)buffer,sizes);
    content += temp;

    printf("content is %s\n",content.c_str() );
/*
    errcode,纬度,经度,精度半径,地址
    errcode
    0: 成功
    10000: 参数错误
    10001: 无查询结果
*/
    const char* str = content.c_str(); 
    int code;
    string slat;
    string slon;
    string sradius;
    string address;
    if (jreader.parse(str, jroot))  // reader将Json字符串解析到root，root将包含Json里所有子元素  
    {  
        code = jroot["errcode"].asInt();  
        slat = jroot["lat"].asString();
        slon = jroot["lon"].asString();
        sradius = jroot["radius"].asString();
        address = jroot["address"].asString();
    }  
    printf("code is %d, slat is %s, slon is %s, srad is %s, address is %s\n",code,slat.c_str(),slon.c_str(),sradius.c_str(),address.c_str() );

    int lat,lon,radius;
    lat = atof(slat.c_str()) * 1000000;
    lon = atof(slon.c_str()) * 1000000;
    radius = atoi(sradius.c_str());
    printf("lat is %d, lon is %d, radius is %d\n",lat,lon,radius );
    
    return sizes;  
}  

int main(int argc,char *argv[])  
{
    char GETURL[1024] = "";
    int mcc = 460;        //国家代码：中国代码 460
    int mnc = 1;          //网络类型：0移动，1联通(电信对应sid)，十进制
    int lac = 9536;       //(电信对应nid)，十进制
    int ci = 31352;       //(电信对应bid)，十进制
    string coord = "";    //坐标类型(wgs84/gcj02/bd09)，默认wgs84
    string output = "json";   //返回格式(csv/json/xml)，默认csv

    sprintf(GETURL,"http://api.cellocation.com/cell/?mcc=%d&mnc=%d&lac=%d&ci=%d&output=%s",mcc,mnc,lac,ci,output.c_str());
    printf("GETURL is %s\n",GETURL );

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
  
    curl_easy_setopt(curl,CURLOPT_URL,GETURL); //url地址   
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&handle_data); //对返回的数据进行操作的函数地址  
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,&content); //这是write_data的第四个参数值  


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