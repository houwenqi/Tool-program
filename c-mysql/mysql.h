#ifndef __CMYSQL_H__
#define __CMYSQL_H__

#include <string>
#include <map>
#include <vector>

#ifdef __cplusplus
extern "C"{
#endif

#include "mysql.h"

#ifdef __cplusplus
}
#endif

using namespace std;

typedef map<string,int> STRING2INT;

class CMysql
{
public:
	CMysql();
	CMysql(const char* szHost,const char* szUser,const char* szPass,const char* szDB);
	~CMysql();
	//
	int Close();
	int Connect(const char* szHost,const char* szUser,const char* szPass,const char* szDB);
	int Connect();
	//
	int DisConnect();

	int Query(char* szSqlString);
	int Query(char* szSqlString,string &blob);
	int QueryBlob(char* szSqlString,string &blob);
	int GetBlob(char* szSqlString,string &blob);
	int StoreResult();
	int FreeResult();

	char** FetchRow();
	char* GetField(unsigned int iField);
	char* GetField(char* szFieldName);
	unsigned int GetAffectedRows();
	unsigned int GetFieldLength(unsigned int iField);

	MYSQL* GetConnectHandle()
	{
		return &m_connection;
	}
	char* GetLastError()
	{
		return m_ErrMsg;
	}
	int StartTransaction()
	{
		return mysql_autocommit(&m_connection,0);
	}
	int RollBack()
	{
		mysql_rollback(&m_connection);
	}
	int EndTransaction()
	{
		return mysql_autocommit(&m_connection,1);
	}

private:
	char m_ErrMsg[1024];
	char m_szHost[64];
	char m_szUser[64];
	char m_szPass[64];
	char m_szDB[64];

	unsigned int m_iField;
	MYSQL m_connection;
	MYSQL_RES* m_result;
	MYSQL_ROW m_row;
	STRING2INT m_FieldIndex;
	bool m_bFieldIndexInitialized;
	bool m_bConnected;

	int InitFieldName(); 
};

#endif