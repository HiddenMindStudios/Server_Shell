#pragma once
#include "stdafx.h"
#include <string>
#include "Define.h"
#include "..\mysqlcon\include\mysql.h"
enum TABLE_FIELD_COUNT
{
	tbl_users = 6,
	tbl_test = 6

};

enum USER_DATA_POS
{
	User_ID = 0,
	User_UserName = 1,
	User_Password = 2,
	User_GMLevel = 3,
	User_Email = 4,
	User_Creation = 5,
	User_LastLogin = 6
};
class DBCon{
	MYSQL* conn;
	MYSQL_RES* res;
	MYSQL_ROW row;
	char* server;
	char* db;
	int port;
	char* user;
	char* pass;
public:
	int Initialize();
	bool connect();
	vstring getUserData(std::string user);
	int insertData(std::string table, vstring fields, vstring values);
};

