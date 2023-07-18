#include "Connection.h"
#include <iostream>
using namespace std;

Connection::Connection()
{
	// 初始化数据库连接
	_conn = mysql_init(nullptr);
}

Connection::~Connection()
{
	// 释放数据库连接
	if (_conn != nullptr)
		mysql_close(_conn);
}

bool Connection::connect(string ip, unsigned short port, 
	string username, string password, string dbname)
{
	// 连接数据库
	MYSQL *p = mysql_real_connect(_conn, ip.c_str(), username.c_str(),
		password.c_str(), dbname.c_str(), 3306, nullptr, 0);

	return p != nullptr;
}

bool Connection::update(string sql)
{
	// 更新操作
	if (mysql_query(_conn, sql.c_str()))
	{
		LOG("Update fail:" + sql);
		return false;
	}
	return true;
}

MYSQL_RES* Connection::query(string sql)
{
	// 查询操作 select
	if (mysql_query(_conn, sql.c_str()))
	{
		LOG("Query fail:" + sql);
		return nullptr;
	}
	return mysql_use_result(_conn);
}