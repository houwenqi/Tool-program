#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  //sleep函数
#include "mysql.h"

//数据结构定义
MYSQL mysql;
MYSQL_RES *res;
MYSQL_ROW row;

void DoSQL(char* sql)
{
	int retcode = 0;
	retcode = mysql_real_query(&mysql,sql,(unsigned int)strlen(sql));//如果查询成功，函数返回零。如果发生一个错误，函数返回非零。
	if( retcode != 0 )
	{
		printf("mysql_real_query is failed:%s\n",mysql_error(&mysql));
	}
}

int CMYSQL()
{
	//需要执行的语句
	char* insert1 = "insert into testtable values(1,'xiaohong','girl')";
	char* insert2 = "insert into testtable values(2,'xiaogang','boy')";
	char* create = "create table testtable(id int,name varchar(20),sex varchar(10))";
	char* query = "select * from testtable";
	//执行创建语句
	DoSQL(create);
	sleep(1);

	//执行插入语句
	DoSQL(insert1);
	sleep(1);
	DoSQL(insert2);
	sleep(1);

	//执行查询语句
	DoSQL(query);
	//处理查询结果
	res = mysql_store_result(&mysql);//如果成功，返回具有多个结果的MYSQL_RES结果集合。如果出现错误，返回NULL
	while( row = mysql_fetch_row(res) )
	{
		for(int i=0;i<mysql_num_fields(res);i++)
		{
			printf("%s\n",row[i] );
		}
		printf("\n");
	}
	mysql_free_result(res);
	return 0;
}


int STMT()
{
	//创建MYSQL_STMT句柄
	MYSQL_STMT* stmt = mysql_stmt_init(&mysql);

	//sql语句
	char* select = "select * from testtable where id = ? ;";

	//语句准备
	if( mysql_stmt_prepare(stmt,select,strlen(select)))//如果成功处理了语句，返回0。如果出现错误，返回非0值。
	{
		printf("mysql_stmt_prepare is failed:%s\n",mysql_error(&mysql));
		return -5;
	}

	//输入参数
	int id; 
	char name[20]="";
	char sex[10]="";
    printf("id: ");
    scanf("%d",&id);

    //参数准备
    MYSQL_BIND params[3];
    memset(params,0,sizeof(params));
    params[0].buffer_type = MYSQL_TYPE_LONG;
    params[0].buffer = &id;
    params[1].buffer_type = MYSQL_TYPE_STRING;
    params[1].buffer = name;
    params[1].buffer_length = 50;
    params[2].buffer_type = MYSQL_TYPE_STRING;
    params[2].buffer = sex;
    params[2].buffer_length = 20;

    //绑定参数
    mysql_stmt_bind_param(stmt,params);

    //将结果集中的列与数据缓冲和长度缓冲关联（绑定）起来
    mysql_stmt_bind_result(stmt,params);

    //执行与句柄相关的预处理语句
    mysql_stmt_execute(stmt);

    //对结果的缓冲处理
    mysql_stmt_store_result(stmt);

    //具体数据读取
    while( mysql_stmt_fetch(stmt) == 0 )
    {
    	printf("%d %s %s\n",id,name,sex );
    }

    mysql_stmt_close(stmt);
	return 0;
}

int main()
{
	//初始化
	mysql_init(&mysql);

	//连接数据库
	if( !mysql_real_connect(&mysql,"172.16.1.23","Cserver","wkl1409624367","test",0,NULL,0))//如果连接成功，返回MYSQL*连接句柄。如果连接失败，返回NULL。
	{
		printf("mysql_real_connect is failed:%s\n",mysql_error(&mysql));
		return -3;
	}

	//第一步，调用普通CMYSQL函数，向数据库插入三条数据，并查询查询结果；
	int ret = 0;
	ret = CMYSQL();
	if( ret != 0 )
	{
		printf("Do CMYSQL failed\n");
		return -1;
	}
	
	//第二步，调用CMYSQL预处理函数，查询数据库信息并展示，增加一条数据；
	ret = STMT();
	if( ret != 0 )
	{
		printf("Do STMT failed\n");
		return -2;
	}

	mysql_close(&mysql);
	return 0;
}