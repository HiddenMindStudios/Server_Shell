#pragma once
#include "DBCon.h"
#include "Common.h"
#include "base64.h"
#include "Log.h"
#include "InstanceManager.h"

enum SockMsgType{
	sockMsgFirstConnect = 0,
	sockMsgLogin,
	sockMsgPing,
	sockMsgRequestGame,
	sockMsgGame
};

struct AccountConn{
	int serverID;
	string user;
	time_t lastConn;
	bool timeout;
	AccountConn(int sID, string u = "") : serverID(sID), user(u),  timeout(false){};
	AccountConn(){ timeout = false; };
	void setLastConn(){ this->lastConn = GetTickCount64(); };
	void setUser(string s) { user = s; };
	time_t getLastConn(){ return this->lastConn; };
};

struct PassAuth{
	bool accountExist;
	bool passGood;
	PassAuth(){};
};

struct SockInterface{
	static const int MAX_CONN = 100;
	AccountConn* accounts;
	int connCount = 0;
	Log logger;
	
	bool setAccountUser(int cID, string u){
		for (int i = 0; i < connCount; i++){
			if (accounts[i].serverID == cID){
				accounts[i].setUser(u);
				return true;
			}
		}
		return false;
	}

	void clearAccount(int sID){
		
	}
	
	vstring splitMessage(std::string msg)
	{
		vstring elems;
		std::stringstream ss(msg);
		std::string item;
		while (std::getline(ss, item, ':')){
			elems.push_back(item);
		}
		return elems;
	};

	PassAuth checkLogin(std::string user, std::string pass){
		PassAuth p = PassAuth();
		db.connect();
		vstring data = db.getUserData(user);
		if (data.size() == 0){
			p.accountExist = 0;
			p.passGood = 0;
		}
		else if (pass == data[User_Password]){
			p.accountExist = 1;
			p.passGood = 1;
		}
		else{
			p.accountExist = 1;
			p.passGood = 0;
		}
		return p;
	}

	bool userLoggedIn(std::string user){
		for (int i = 0; i < connCount; i++){
			if (accounts[i].user == user){
				return true;
			}
		}
		return false;
	}

	char* readMessage(char* buf){
		//Decode input
		std::string msg = base64_decode(buf);
		//Generic initializers
		std::string user = "";
		std::string pass = "";
		std::string sMsg;
		char* charMsg;
		PassAuth ok = PassAuth();
		//Pull params
		vstring params = splitMessage(msg);
		//Param switch (check sockMsgs enum)
		switch (stoi(params[0])){
		case sockMsgFirstConnect:
			if (params.size() < 2){
				logger.send(LOGMINIMAL, NETLOG, "Bad params received. Skipping...");
				return "";
			}
			if (params[1] == CLIENT_VERSION){
				std::string id = std::to_string(rand() * rand());
				std::string empty = "";
				if (std::find(clientID.begin(), clientID.end(), id) == clientID.end()){
					sMsg = "0:" + params[2] + ":" + id;
					accounts[connCount] = AccountConn(stoi(id), empty);
					connCount++;
					sMsg = base64_encode(sMsg);
					charMsg = new char[sMsg.length() + 1];
					std::strcpy(charMsg, sMsg.c_str());
					return charMsg;
				}
				else{
					logger.send(LOGDEBUG, NETLOG, "No Client Version... ");
				}
			}
			else{
				logger.send(LOGDETAIL, NETLOG, "Client bad version");
				sMsg = base64_encode("0:BAD_CLIENT");
				break;
			}
		case sockMsgLogin:
			if (params.size() < 4){
				logger.send(LOGDEBUG, NETLOG, "Bad parameter count. Got " + to_string(params.size()) + " expected 4");
				return "";
			}
			ok = checkLogin(params[2], params[3]);
			if (ok.accountExist && ok.passGood){
				logger.send(LOGDEBUG, NETLOG, "Login Okay...");
				bool accountSync = setAccountUser(stoi(params[1]), params[2]);
				if (accountSync){
					sMsg = base64_encode("1:OK");
					logger.send(LOGDEBUG, NETLOG, "User " + params[2] + " logged in.");
				}
				else{
					if (userLoggedIn(params[2])){
						sMsg = base64_encode("1:USERLOGGEDIN");
						logger.send(LOGERROR, NETLOG, "User " + params[2] + " already logged in...");
					}
					else{
						sMsg = base64_encode("1:BADCLIENT");
						logger.send(LOGERROR, NETLOG, "Client " + params[1] + " not authenticated.");
					}
				}
			}
			else if (ok.accountExist && !ok.passGood)
			{
				sMsg = base64_encode("1:BADPASS");
			}
			else{
				sMsg = base64_encode("1:NOUSER");
			}
			charMsg = new char[sMsg.length() + 1];
			std::strcpy(charMsg, sMsg.c_str());
			logger.send(LOGDEBUG, NETLOG, "Returning " + sMsg);
			return charMsg;
			break;
		case sockMsgPing:
			if (params.size() < 2){
				logger.send(LOGERROR, NETLOG, "Bad Parameter count for sockMsgPing. Got " + to_string(params.size()) + " expected 2");
				return "";
			}
			if (params[1] == "Ping"){
				sMsg = base64_encode("2:Pong");
				charMsg = new char[sMsg.length() + 1];
				std::strcpy(charMsg, sMsg.c_str());
				return charMsg;
			}
			break;
		//Player hit "Play" button on the client
		case sockMsgRequestGame:
			//sockMsgRequestGame:clientID:CHARACTER_START
			//sockMsgRequestGame:clientID:CHARACTER_PICK:x
			//sockMsgRequestGame:clientID:CHARACTER_NEW
			if (params.size() < 3 || params.size() > 4){
				logger.send(LOGERROR, NETLOG, "Bad Parameter count for sockMsgRequestGame. Got " + to_string(params.size()) + ".");
				break;
			}
			if (params[2] == "CHARACTER_START"){
				string uName = "";
				int cID = stoi(params[1]);
				for (int i = 0; i < connCount; ++i){
					if (accounts[i].serverID == cID)
						uName = accounts[i].user;
				}
				if (uName == ""){
					logger.send(LOGERROR, NETLOG, "Client ID mismatch with system. Character load cancelled");
					break;
				}
				iMgr.pushNewPlayer(uName, cID);
			}
		default:
			std::cout << "Bad info" << std::endl;
			break;
		}
		return "";
	};
	SockInterface(string logPath){
		Log logger = Log(logPath);
		accounts = new AccountConn[MAX_CONN];
		iMgr = InstanceManager(logger);
		db.Initialize();
	}
	SockInterface(){};
private:
	DBCon db = DBCon();
	vstring clientID;
	InstanceManager iMgr;
};