#pragma once
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <WinSock2.h>
#include <stdio.h>
#include "SockInterface.h"
#include "Log.h"
#include "base64.h"
#pragma comment(lib, "ws2_32.lib")

#define BUFLEN 2048
#define PORT 3524

class Socket{
	SOCKET s;
	SockInterface socki;
	struct sockaddr_in server, si_other;
	int slen, recv_len;
	Log logger;
	char buf[BUFLEN];
	WSADATA wsa;
public:
	void Initialize(string logPath, int tId);
	void Update(double dt);
	Socket();
	void Send(char* buf);
};
