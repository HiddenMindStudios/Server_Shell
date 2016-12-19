#include "stdafx.h"
#include "Define.h"
#include "InstanceManager.h"

Player* InstanceManager::getPlayerByClientID(int id){
	for (vInstance::iterator it = instance.begin(); it != instance.end(); ++it){
		Player* player = it->getPlayerByClientID(id);
		if (player != nullptr)
			return player;
	}
	return nullptr;
};

vstring InstanceManager::getUserData(std::string uName){
	db.connect();
	return db.getUserData(uName);
}

InstanceManager::InstanceManager(){

};

InstanceManager::InstanceManager(Log& l){
	logger = l;
	loadList = vPlayer();
	instance = vInstance();
	gameInstance = Game();
	db = DBCon();
	db.Initialize();
}

bool InstanceManager::pushNewPlayer(std::string uName, int clientID){
	Player p = Player(uName, clientID);
	loadList.push_back(p);
	return true;
}

bool InstanceManager::playerDoneLoad(int clientID, int mapID){
	Player* p = nullptr;
	for (vPlayer::iterator it = loadList.begin(); it != loadList.end(); ++it){
		if (it->getClientID() == clientID){
			p = &(*it); 
			loadList.erase(it);
			for (vInstance::iterator t = instance.begin(); t != instance.end(); ++t){
				if (t->getMapID() == mapID){
					t->addPlayerToMap(&(*it));
					return true;
				}
			}
		}
	}
	//Fell through, no map with that mapID!
	if (p == nullptr)
		return false;
	Instance i = Instance(mapID, gameInstance.getMapName(mapID), &logger);
	i.addPlayerToMap(p);
	instance.push_back(i);
	return true;
}