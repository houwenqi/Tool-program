����Redis��srcĿ¼
��������
./redis-server

redis-cli





��дMakefile�ļ�
redis: redis.cpp redis.h
    g++ redis.cpp -o redis -L/usr/local/lib/ -lhiredis

clean:
    rm redis.o redis
���б���
make
����������ִ��
g++ redis.cpp -o redis -L/usr/local/lib/ -lhiredis
������������Ҳ�����̬���ӿ�
��/etc/ld.so.conf.d/Ŀ¼���½��ļ�usr-libs.conf�������ǣ�/usr/local/lib