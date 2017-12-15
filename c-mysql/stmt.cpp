#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mysql.h"

int main()
{
	MYSQL *conn = mysql_init(NULL); //初始化服务器句柄
	/*登陆服务器*/
	if( !mysql_real_connect(conn,"172.16.1.23","Cserver","wkl1409624367","test",0,NULL,0))
	{
		fprintf(stderr, "mysql_real_connect: %s\n",mysql_error(conn) );
		return -1;
	}
	MYSQL_STMT *stmt = mysql_stmt_init(conn); //创建MYSQL_STMT句柄

	char *query = "select * from testtable;";

	if(mysql_stmt_prepare(stmt,query,strlen(query)))
	{
		fprintf(stderr, "mysql_stmt_prepare: %s\n",mysql_error(conn) );
		return -1;
	}

	int id;
	char name[20];
	int sex;
	//printf("id name sex:\n");
	//scanf("%d %s %d",&id,name,&sex);
	printf("strlen name is %d\n",strlen(name) );
	MYSQL_BIND params[3];
	memset(params,0,sizeof(params));
	params[0].buffer_type = MYSQL_TYPE_LONG;
	params[0].buffer = &id;
	params[1].buffer_type = MYSQL_TYPE_STRING;
	params[1].buffer = name;
	params[1].buffer_length = 20;
	params[2].buffer_type = MYSQL_TYPE_LONG;
	params[2].buffer = &sex;

	printf("params  is ok\n");


	//mysql_stmt_bind_param(stmt,params);
	//printf("bind is ok\n");


	mysql_stmt_bind_result(stmt,params);////用于将结果集中的列与数据缓冲和长度缓冲关联（绑定）起来


	mysql_stmt_execute(stmt);   //执行与语句句柄相关的预处理
	printf("execute is ok\n");


	mysql_stmt_store_result(stmt);//以便后续的mysql_stmt_fetch()调用能返回缓冲数据
	printf("store is ok\n");

	while( mysql_stmt_fetch(stmt) == 0 )//返回结果集中下一行
	{
		printf("aaaaaaaaaa\n");
		printf("%d\t%s\t%d\n",id,name,sex);
	}
	printf("fetch is ok\n");

	mysql_stmt_close(stmt);
	mysql_close(conn);

	return 0;
}