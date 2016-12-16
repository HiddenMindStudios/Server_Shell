#include "stdafx.h"
#include "Resource.h"

using namespace std;

class Player
{
	string name;
	int clientId;
	string addr;
public:
	inline string getName(){ return name; };
	inline int getClientID(){ return clientId; };
	inline void setPlayerAddress(string ip){ addr = ip; };
	Player(string n, int cID);
};