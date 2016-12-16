#include "Sock.h"
#define SOCK_TIMEOUT 600.0
void Socket::Initialize(string logPath, int tId){
	logger = Log(logPath);
	socki = SockInterface(logPath);
	slen = sizeof(si_other);
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0){
		logger.send(LOGMINIMAL, NETLOG, "Failed to initialize Winsock2. Error Code: " + to_string(WSAGetLastError()));
		exit(EXIT_FAILURE);
	}
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET){
		logger.send(LOGMINIMAL, NETLOG, "Could not create socket: " + to_string(WSAGetLastError()));
		exit(EXIT_FAILURE);
	}
	int enable = 1;
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char*)&enable, sizeof(enable));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(PORT);
	if (bind(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR){
		logger.send(LOGMINIMAL, NETLOG, "Bind failure. Error code: " + to_string(WSAGetLastError()) + " for sockthread " + to_string(tId));
		exit(EXIT_FAILURE);
	}
	logger.send(logger.ReportingLevel(), NETLOG, "Socket Thread" + to_string(tId) + " created successfully");
}

void Socket::Send(char* buf){
	string ping = base64_encode("2:Pong");
	if (sendto(s, buf, strlen(buf), 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR){
		printf("Failed to send %s to &s", buf, si_other.sin_addr);
		exit(EXIT_FAILURE);
	}
	if (ping == buf)
		return;
	logger.send(LOGDEBUG, NETLOG, buf);
}

void Socket::Update(double dt){
	fflush(stdout);
	memset(buf, '\0', BUFLEN);
	for (int i = 0; i < socki.connCount; i++){
		if (socki.accounts[i].getLastConn() + SOCK_TIMEOUT <= GetTickCount64()){
			socki.clearAccount(socki.accounts[i].serverID);
		}
	}
	if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr*)&si_other, &slen)) == SOCKET_ERROR){
		logger.send(LOGMINIMAL, NETLOG, "recvfrom() failed. Error code: " + to_string(WSAGetLastError()));
		exit(EXIT_FAILURE);
	}
	else{
		char* newSend = socki.readMessage(buf);
		if (newSend != "")
			Send(newSend);
	}
}

Socket::Socket(){
}
