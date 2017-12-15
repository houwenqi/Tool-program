#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  //sleep函数
#include "mysql.h"

//数据结构定义
MYSQL mysql;
MYSQL_RES *res;
MYSQL_ROW row;

int ConnectDB(char *ip, char *DBname, char *pwd, char *table )
{
	//如果连接成功，返回MYSQL*连接句柄。如果连接失败，返回NULL。
	if( !mysql_real_connect(&mysql, ip, DBname, pwd, table, 0, NULL, 0))
    {
        return -1;
    }
    return 0;
}
int DoSQL(char* sql)
{
    int retcode = 0;
    retcode = mysql_real_query(&mysql,sql,(unsigned int)strlen(sql));//如果查询成功，函数返回零。如果发生一个错误，函数返回非零。
    if( retcode != 0 )
    {
        return -1;
    }
    return 0;
}

int main()
{
	int ret;
	int rest;
	char sql[1024] = "";
	char db[50] = "";
	//初始化
	mysql_init(&mysql);

	for( int sum = 0; sum < 10; sum++)
	{
		rest = snprintf(db,sizeof(db),"db_ptt_gps_%d",sum);
		db[rest] = 0;
		printf("db is %s\n",db );
		//连接IP总数据库
		ret = ConnectDB( "52.37.163.27", "root", "Wkl@cyhd0810", db);
		if( ret != 0 )
		{
			printf("ConnectDB failed\n");
			return -2;
		}

		for( int num = 0; num < 100 ; num++ )
		{
			//需要执行的语句
		    ret = snprintf(sql,sizeof(sql),"ALTER TABLE t_ptt_gps_%d ADD location int(11);",num);
		    sql[ret] = 0;

		    //执行创建语句
		    printf("DB %s sql is [%s]\n", db, sql );

		    ret = DoSQL(sql);
		    if( ret != 0 )
		    {
		    	printf("DoSQL failed\n");
		    	return -2;
		    }
		}
		mysql_close(&mysql);
	}
	return 0;
}