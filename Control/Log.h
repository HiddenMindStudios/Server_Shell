#pragma once
#include "stdafx.h"
#include "Define.h"
#include <fstream>
using namespace std;
enum CONTROL_API LogLevel
{
	LOGMINIMAL,
	LOGERROR,
	LOGDETAIL,
	LOGDEBUG
};

enum CONTROL_API LogType
{
	NETLOG,
	DBLOG,
	PLRLOG,
	SERVLOG,
	GAMELOG
};

class CONTROL_API Log
{
	static string netLog;
	static string dbLog;
	static string playerLog;
	static string serverLog;
	static string gameLog;
	static string logPath;

	string formatTime();
public:

	LogLevel level;
	Log(string fp);
	Log();
	virtual ~Log(void);

	LogLevel ReportingLevel();

	void initialize();
	void setFullPath(string fp);
	void send(LogLevel l, LogType t, std::string s);
};

