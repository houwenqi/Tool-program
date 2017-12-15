//测试MYSQL C API编程小程
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //sleep函数
#include <string.h>
#include "mysql.h"

using namespace std;

int main()
{
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *query;
	int t,r;
	//初始化数据库
	mysql_init(&mysql);

	//连接数据库
	if( !mysql_real_connect(&mysql,"172.16.1.23","Cserver","wkl1409624367","test",0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(&mysql));
	}else{
		printf("connect database success\n");
	}	

	//查询语句
	query = "select * from testtable";

	t = mysql_real_query(&mysql,query,(unsigned int)strlen(query));
	if( t )
	{
		printf("Error making query:%s\n",mysql_error(&mysql));
	}else{
		printf("query %s  is ok\n",query);
	}

	//处理查询结果集
	res = mysql_store_result(&mysql);
	while( row = mysql_fetch_row(res) )
	{
		for( t=0;t<mysql_num_fields(res);t++)
		{
			printf("%s\n",row[t]);
		}
		printf("\n");
	}

	printf("mysql free result \n");
	mysql_free_result(res);

	sleep(1);

	 // execute the insert query 

 	query = "insert into testtable(id, name,sex) values(13, 'xiaohong',2)"; 
 	t = mysql_real_query(&mysql,query,(unsigned int) strlen(query)); 
 	if (t) 
 	{ 
   		printf("Error making query: %s\n", 
     	mysql_error(&mysql)); 
 	}else{
 		printf("[%s] made...\n", query);  
 	}
    mysql_close(&mysql); 

    return 0;
}