#include "redis.h"

int main()
{
    Redis *r = new Redis();

    if( r->connect("127.0.0.1", 6969) == 0)
    {
        printf("connect error!\n");
        return 0;
    }
 
    r->set("name", "Andy");
    
    string name = r->get("name");
    printf("Get the name is %s\n", name.c_str());


    r->set("key","value");
    r->expire("key","2");
    sleep(3);
    string value = r->get("key");
    if( value != "ERROR")
    {
        printf("Get the key is %s\n",value.c_str() );
    }
    else
    {
        printf("key time out \n");
    }

    r->set("id","msg");
    r->expire("id","5");
    sleep(3);
    string msg = r->get("id");
    if( msg != "ERROR")
    {
        printf("Get the id is %s\n",msg.c_str() );
    }
    else
    {
        printf("id time out \n");
    }
    delete r;
    return 0;
}