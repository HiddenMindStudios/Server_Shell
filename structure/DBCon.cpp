#include "stdafx.h"
#include "DBCon.h"

int DBCon::Initialize(){
	server = "localhost";
	db = "colosseumchampions";
	port = 3306;
	user = "CCServer";
	pass = "serverConnect";
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, server, user, pass, db, port, NULL, 0)){
		fprintf(stderr, "%s\n", mysql_error(conn));
		return(1);
	}
	mysql_close(conn);
}

bool DBCon::connect(){
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, server, user, pass, db, port, NULL, 0)){
		fprintf(stderr, "%s\n", mysql_error(conn));
		return(false);
	}
	return true;
}

int DBCon::insertData(std::string table, vstring fields, vstring values){
	if (!connect())
		return -1;
	std::string header = "INSERT INTO " + table + "(";
	for (vstring::iterator it = fields.begin(); it != fields.end(); ++it){
		std::string s = *it;
		header += s + ", ";
	}
	header += ") VALUES(";
	for (vstring::iterator it = values.begin(); it != values.end(); ++it){
		std::string s = *it;
		header += s + ", ";
	}
	header += ");";
	if (mysql_query(conn, header.c_str())){
		printf("%s\n", mysql_error(conn));
		return -1;
	}
	mysql_close(conn);
	return 0;
}

vstring DBCon::getUserData(std::string user){
	vstring empty = vstring();
	if (!connect())
		return empty;
	std::string header = "SELECT * FROM users WHERE Username IN('" + user + "');";
	if (mysql_query(conn, header.c_str()))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		return(empty);
	}
	res = mysql_use_result(conn);
	vstring ret;
	while ((row = mysql_fetch_row(res)) != NULL)
	{
		for (int i = 0; i < tbl_users; i++)
			ret.push_back(row[i]);
	}
	mysql_free_result(res);
	mysql_close(conn);
	return ret;
}