#pragma once
#include "Server.h"


using namespace std;

struct ThreadArgs{
	int id;
	string path;
	Log& log;
	ThreadArgs(int i, string s, Log& log) : id(i), path(s), log(log){};
};

DWORD WINAPI thread_cmd(LPVOID lpParameter){
	ThreadArgs* tArgs = (ThreadArgs*)lpParameter;
	tArgs->log.send(LOGMINIMAL, SERVLOG, "Thread " + to_string(tArgs->id) + " entered");
	for (;;){
		string temp;
		getline(cin, temp);
		if (temp == "exit")
			break;
	}
	tArgs->log.send(LOGDEBUG, SERVLOG, "Thread " + to_string(tArgs->id) + " closed.");
	return 0;
}

DWORD WINAPI thread_sock(LPVOID lpParameter){
	ThreadArgs* tArgs = (ThreadArgs*)lpParameter;
	tArgs->log.send(LOGMINIMAL, SERVLOG, "Thread " + to_string(tArgs->id) + " entered");
	string basePath = tArgs->path;
	Socket s;
	s.Initialize(basePath, tArgs->id);
	for (;;){
		s.Update(1 / 60);
	}
	tArgs->log.send(LOGMINIMAL, SERVLOG, "Thread " + to_string(tArgs->id) + " closed.");
	return 0;
}


bool serverRunning = true;
string fullPath;

string initPath(char* argv[])
{
	//Pull the basepath from argv and convert it to string
	char t[255] = "";
	_fullpath(t, argv[0], sizeof(t));
	string basePath = t;

	//Strip the .exe from the filename
	int last = 0;
	for(int i = 0; i < basePath.length(); i++)
	{
		if( basePath.at(i) == '\\')
			last = i;
	}
	return basePath.substr(0, last+1);
}

void print(string s) 
{
	cout << s << endl;
	cin.clear();
}

int main(int argc, char* argv[])
{
	const double rate = 1 / 60;
	double dt = 0;
	bool login = false;
	string basePath = initPath(argv);
	cout << basePath << endl;
	Log logger = Log(basePath);
	srand(time(NULL));
	const int threadCount = 3;
	HANDLE hArray[threadCount];
	for (int i = 0; i < threadCount; i++){
		hArray[i] = CreateThread(NULL, 0, thread_sock, new ThreadArgs(i, basePath, logger), 0, 0);
		logger.send(LOGMINIMAL, SERVLOG, "Created Thread id " + to_string(i) + " as sockthread");
	}
	hArray[threadCount-1] = CreateThread(NULL, 0, thread_cmd, new ThreadArgs(threadCount-1, basePath, logger), 0, 0);
	WaitForMultipleObjects(threadCount, hArray, true, INFINITE);
	logger.send(LOGMINIMAL, SERVLOG, "Proccess Termination");
	cin.get();
	return 0;
}