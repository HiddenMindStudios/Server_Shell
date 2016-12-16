#include "stdafx.h"
#include "Log.h"
using namespace std;
//Doesn't log if logs folder doesn't exist. fix pls.
string Log::netLog = "net.log";
string Log::dbLog = "db.log";
string Log::playerLog = "player.log";
string Log::serverLog = "server.log";
string Log::gameLog = "game.log";
string Log::logPath = "\\logs\\";

Log::Log(string fp)
{
	level = LOGDEBUG;
	logPath = fp + logPath;
	initialize();
}

Log::Log(){
	initialize();
}

Log::~Log(void)
{

}

void Log::initialize()
{
	
}

string Log::formatTime(){
	time_t t = time(0);
	struct tm* now = localtime(&t);
	string ret;
	ret.append(to_string(now->tm_hour) + ":" + to_string(now->tm_min) + ":" + to_string(now->tm_sec) + "|" + to_string(now->tm_mon + 1) + "/" +
		to_string(now->tm_mday) + "/" + to_string(now->tm_year + 1900));
	return ret;
}

LogLevel Log::ReportingLevel(){
	return level;
}

void Log::send(LogLevel l, LogType t, std::string s)
{
	if (l > ReportingLevel())
		return;
	ofstream fs;
	switch(t)
	{
	case NETLOG:
		fs.open(logPath + netLog, ios::app);
		break;
	case DBLOG:
		fs.open(logPath + dbLog, ios::app);
		break;
	case PLRLOG:
		fs.open(logPath + playerLog, ios::app);
		break;
	case SERVLOG:
		fs.open(logPath + serverLog, ios::app);
		break;
	case GAMELOG:
		fs.open(logPath + gameLog, ios::app);
		break;
	default:
		fs.open(logPath + serverLog, ios::app);
		break;
	}
	string tm = formatTime();
	string out = "[" + tm + "] " + to_string(LogLevel(l)) + ": " + s + "\n";
	fs << out;
	fs.close();
	cout << out;
}