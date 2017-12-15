进入Redis的src目录
启动服务
./redis-server

redis-cli





编写Makefile文件
redis: redis.cpp redis.h
    g++ redis.cpp -o redis -L/usr/local/lib/ -lhiredis

clean:
    rm redis.o redis
进行编译
make
或者命令行执行
g++ redis.cpp -o redis -L/usr/local/lib/ -lhiredis
运行如果出现找不到动态链接库
在/etc/ld.so.conf.d/目录下新建文件usr-libs.conf，内容是：/usr/local/lib