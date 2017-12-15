#include <stdio.h>
#include <string.h>
#include "cmysql.h"


CMysql::CMysql()
{
	mysql_init (&m_connection);
	mysql_options (&m_connection,MYSQL_SET_CHARSET_NAME,"utf8");

	m_bConnected = false;
	m_iField = 0;
	m_result = NULL;
	bzero (m_szHost,sizeof(m_szHost));
	bzero (m_szUser,sizeof(m_szUser);
	bzero (m_szPass, sizeof(m_szPass));
	bzero (m_ErrMsg, sizeof(m_ErrMsg));
	m_bFieldIndexInitialized = false;
}

CMysql::CMysql(const char* szHost,const char* szUser,const char* szPass,const char* szDB)
{
	mysql_init(&m_connection);
	mysql_options (&m_connection,MYSQL_SET_CHARSET_NAME,"utf8");

	m_bConnected = false;
	m_iField = 0;
	m_result = NULL;
	strcpy (m_szHost,szHost);
	strcpy (m_szUser,szUser);
	strcpy (m_szPass,szPass);
	strcpy (m_szDB,szDB);
	bzero (m_ErrMsg,sizeof(m_ErrMsg));
	m_bFieldIndexInitialized = false;
}

CMysql::~CMysql()
{
	Close();
}

int CMysql::Close()
{
	if(m_bConnected)
	{
		mysql_close(&m_connection);
		m_bConnected = false;
	}
	FreeResult();
	return 0;
}

int CMysql::Connect(const char* szHost, const char* szUser, const char* szPass,const char* szDB)
{
	if( !strcmp(szHost,m_szHost))
	{
		return Connect();
	}
	strcpy (m_szHost, szHost);
	strcpy (m_szUser, szUser);
	strcpy (m_szPass, szPass);
	strcpy (m_szDB, szDB);
	Close();
	return Connect();
}

int CMysql::Connect()
{
	if( !m_bConnected)
	{
		if(mysql_real_connect(&m_connection,m_szHost,m_szUser,m_szPass,m_szDB,0,NULL,0) == NULL)
		{
			return -1;
		}
		m_bConnected = true;
	}
	return 0;
}

//如果连接断开，但是不清除转储存的结果
int CMysql::DisConnec()
{
	if(m_bConnected)
	{
		mysql_close(&m_connection);
		m_bConnected = false;
	}
	return 0;
}

int CMysql::Query(char* szSqlString)
{
	Connect();
	if(mysql_query(&m_connection,szSqlString) != 0)
	{
		DisConnect();
		if( 0 != Connect())
		{
			sprintf(m_ErrMsg,"Connect Database failed:%s",mysql_error(&m_connection));
			return -1;
		}
		mysql_real_query(&m_connection,"SET NAMES UTF8;",(unsigned long)strlen("SET NAMES UTF8;"));
		if( 0 != mysql_query(&m_connection,szSqlString))
		{
			sprintf(m_ErrMsg,"Query Database failed:%s",mysql_error(&m_connection));
			return -1;
		}
	}
	return 0;
}

int CMysql::Query(char* szSqlString,string &blob)
{
	Connect();
	MYSQL_BIND bind[1];
	unsigned long length;

	MYSQL_STMT *stmt = mysql_stmt_init(&m_connection);
	if( !stmt )
	{
		sprintf(m_ErrMsg,"mysql_stmt_init(),out of memory");
		return -1;
	}
	if(mysql_stmt_prepare(stmt,szSqlString,strlen(szSqlString)))
	{
		sprintf(m_ErrMsg,"mysql_stmt_prepare(),INSERT failed %s",mysql_stmt_error(stmt));
		mysql_stmt_close(stmt);
		return -1;
	}

	memset(bind,0,sizeof(bind));
	bind[0].buffer_type = MYSQL_TYPE_STRING;
	bind[0].length = &length;
	bind[0].is_null = 0;

	if(mysql_stmt_bind_param(stmt,bind))
	{
		sprintf (m_ErrMsg,"param bind failed %s", mysql_stmt_error(stmt));
	 	mysql_stmt_close(stmt);
	 	return -1;
	}

	if(mysql_stmt_send_long_data(stmt,0,blob.c_str(),blob.size()))
	{
		sprintf (m_ErrMsg,"send_long_data failed %s", mysql_stmt_error(stmt));
	 	mysql_stmt_close(stmt);
	 	return -1;
	}

	if(mysql_stmt_execute(stmt))
	{
		sprintf (m_ErrMsg,"mysql_stmt_execute failed %s", mysql_stmt_error(stmt));
	 	mysql_stmt_close(stmt);
	 	return -1;
	}
	mysql_stmt_close(stmt);
	return 0;
}

int CMysql:: QueryBlob(char* szSqlString, string &blob)
{
	Connect();
	MYSQL_BIND bind[1];
	unsigned long length;

	MYSQL_STMT *stmt = mysql_stmt_init(&m_connection);
	if (!stmt)
	{
	  sprintf (m_ErrMsg, " mysql_stmt_init(), out of memory");
	  return -1;
	}
	if (mysql_stmt_prepare(stmt, szSqlString, strlen(szSqlString)))
	{
	  sprintf (m_ErrMsg,  "mysql_stmt_prepare(), INSERT failed %s", mysql_stmt_error(stmt));
	  mysql_stmt_close(stmt);
	  return -1;
	}
	
	memset(bind, 0, sizeof(bind));
	bind[0].buffer_type= MYSQL_TYPE_BLOB;
	bind[0].length= &length;
	bind[0].buffer_length = blob.size();
	bind[0].buffer = const_cast<char*>(blob.data());
	bind[0].is_null= 0;

	if (mysql_stmt_bind_param(stmt, bind))
	{
	  sprintf (m_ErrMsg,"param bind failed %s", mysql_stmt_error(stmt));
	  mysql_stmt_close(stmt);
	  return -1;
	}
	if ( mysql_stmt_send_long_data(stmt,0, blob.data(), blob.size()  ) )
	{
	  sprintf (m_ErrMsg, "send_long_data failed %s", mysql_stmt_error(stmt));
	  mysql_stmt_close(stmt);
	  return -1;
	}
	if (mysql_stmt_execute(stmt))
	{
	  sprintf (m_ErrMsg, "mysql_stmt_execute failed %s", mysql_stmt_error(stmt));
	  mysql_stmt_close(stmt);
	  return -1;
	}
	mysql_stmt_close(stmt);
	return 0;
}

int CMysql:: GetBlob(char* szSqlString, string &blob)
{
	MYSQL_STMT* stmt = mysql_stmt_init(&m_connection);
	if(NULL==stmt)
		return -1;
   int sql_len = strlen(szSqlString);
   int ret = mysql_stmt_prepare(stmt, szSqlString, sql_len);
   if(0!=ret)
   		return -1;
   MYSQL_BIND result = {0};
   unsigned long total_length = 0;
   result.buffer_type = MYSQL_TYPE_BLOB;
   result.length = &total_length;

   ret = mysql_stmt_bind_result(stmt, &result);
   if(0!=ret)
	{
		mysql_stmt_close(stmt);
		return -1;
	}
   ret = mysql_stmt_execute(stmt);
   if(0!=ret)
	{
		mysql_stmt_close(stmt);
		return -1;
	}
   ret = mysql_stmt_store_result(stmt);
   if(0!=ret)
   	{
   		mysql_stmt_close(stmt);
   		return -1;
   	}
   //while (mysql_stmt_fetch(stmt)!=0)
	ret = mysql_stmt_fetch(stmt);
	if (ret!=0 && ret!=MYSQL_DATA_TRUNCATED) 
	{
		mysql_stmt_close(stmt);
		return 0;//no data
	}
   if ( total_length> 0 )
   {
		char *buf=new char[total_length];
		memset(buf,0, total_length);

	   result.buffer = (buf);
	   result.buffer_length = total_length;  //每次读这么长
	   ret = mysql_stmt_fetch_column(stmt, &result, 0, 0);
	   if (ret!=0)
	   {
	   		mysql_stmt_close(stmt);
			delete []buf;
			return -7;
	   }
	   blob.assign(buf,total_length);
  	   delete []buf;
	}
  mysql_stmt_close(stmt);
  return 0;
}

int CMysql::FreeResult()
{
	if(m_result != NULL)
	{
		mysql_free_result(m_result);
	}
	m_iField = 0;
	m_result = NULL;
	if( m_bFieldIndexInitialized)
	{
		m_FieldIndex.erase(m_FieldIndex.begin(),m_FieldIndex.end());
		m_bFieldIndexInitialized = false;
	}
	return 0;
}

int CMysql::StoreResult()
{
	FreeResult();
	m_result = mysql_store_result(&m_connection);
	if(m_result == NULL)
	{
		sprintf(m_ErrMsg,"StoreResult Error:%s!",mysql_error(&m_connection));
		return -1;
	}
	m_iField = mysql_num_fields(m_result);
	return 0;
}

char** CMysql::FetchRow()
{
	if (m_result == NULL)
		StoreResult();
	m_row = mysql_fetch_row (m_result);
	return m_row;
}

int CMysql::InitFieldName()
{
	if ((!m_bFieldIndexInitialized) && (m_result!=NULL))
	{
		unsigned int i;
		MYSQL_FIELD *fields;

		fields = mysql_fetch_fields(m_result);
		for(i = 0; i < m_iField; i++)
		{
			m_FieldIndex[fields[i].name] = i;
		}
		m_bFieldIndexInitialized = true;
	}
	return 0;
}

unsigned int CMysql::GetFieldLength(unsigned int iField)
{
	unsigned long *lengths = mysql_fetch_lengths(m_result);
	if(iField<m_iField)
		return lengths[iField];
	else 
		return -1;
}
/*	返回结果的行数
*/
unsigned int CMysql::GetAffectedRows()
{
	my_ulonglong iNumRows;

	if (!m_bConnected) return 0;
	iNumRows = mysql_affected_rows(&m_connection);

	return (unsigned int)iNumRows;
}
/*	按照字段名取回当前行的结果
*/
char* CMysql::GetField(char* szFieldName)
{
	InitFieldName();
	return GetField(m_FieldIndex[szFieldName]);
}
/*	按照字段索引取回当前行的结果
*/
char* CMysql::GetField(unsigned int iField)
{
	if (iField > m_iField)
		return NULL;
	return m_row[iField];
}
