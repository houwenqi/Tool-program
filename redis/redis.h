#ifndef _REDIS_H_
#define _REDIS_H_

#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <unistd.h>

#include <hiredis/hiredis.h>

using namespace std;

class Redis
{
public:

    Redis(){}

    ~Redis()
    {
        this->_connect = NULL;
        this->_reply = NULL;                
    }

    int connect(string host, int port)
    {
        this->_connect = redisConnect(host.c_str(), port);
        if(this->_connect != NULL && this->_connect->err)
        {
            printf("connect error: %s\n", this->_connect->errstr);
            return 0;
        }
        return 1;
    }

    string get(string key)
    {
        string rest;
        this->_reply = (redisReply*)redisCommand(this->_connect, "GET %s", key.c_str());
        if( (this->_reply->type != REDIS_REPLY_STRING) && (this->_reply != REDIS_OK))
        {
            rest = "ERROR";
        }
        else
        {
            rest = this->_reply->str;
        }
        freeReplyObject(this->_reply);
        return rest;
    }

    void set(string key, string value)
    {
        this->_reply = (redisReply*)redisCommand(this->_connect, "SET %s %s", key.c_str(), value.c_str());
        freeReplyObject(this->_reply);
    }

    void expire(string key,string time)
    {
        this->_reply = (redisReply*)redisCommand(this->_connect, "EXPIRE  %s %s", key.c_str(), time.c_str());
        freeReplyObject(this->_reply);
    }

private:

    redisContext* _connect;
    redisReply* _reply;

};

#endif  