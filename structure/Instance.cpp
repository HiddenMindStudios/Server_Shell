#pragma once
#include "stdafx.h"
#include "Instance.h"

Instance::Instance(){
	mapId = -1;
	mapName = "UNDEFINED";
	logger = nullptr;
	mergeCount = -1;
}

Instance::Instance(Log* l){
	mapId = -1;
	mapName = "IN_LOADING";
	logger = l;
	mergeCount = -1;
}

Instance::Instance(int mID, string mN, Log* l){
	mapId = mID;
	mapName = mN;
	logger = l;
	mergeCount = 0;
	//Do Data load (future stuffs)
}

int Instance::removePlayer(int cID){
	for (int i = 0; i < mapCount; ++i){
		for (int j = 0; j < pCount[i]; ++i){
			if (pData[i][j]->player->getClientID() == cID){
				pData[i][j] = nullptr;
				pCount[i]--;
				return 0;
			}
		}
	}
	return 1;
}

int Instance::getPlayerMapID(int cID){
	for (int i = 0; i < mapCount; ++i){
		for (int j = 0; j < pCount[i]; ++j){
			if (pData[i][j]->player->getClientID() == cID){
				return i;
			}
		}
	}
	return -1;
}

Player* Instance::getPlayerByClientID(int cID){
	for (int i = 0; i < mapCount; ++i){
		for (int j = 0; j < pCount[i]; j++){
			if (pData[i][j]->player->getClientID() == cID)
				return pData[i][j]->player;
		}
	}
	return nullptr;
}

int Instance::addPlayerToMap(Player* p){	
	//Max maps and playercount in map is max
	if (mapCount == MAP_MAX && pCount[MAP_MAX-1] == PLAYER_MAX){
		if (logger)
			logger->send(LOGDETAIL, GAMELOG, "Instance for mapid " + to_string(mapId) + " full. Spawning new Instance...");
		return -1;
	}
	//Check for empty spot in maps
	for (int i = 0; i < mapCount; ++i){
		int playerCount = pCount[i];
		if (playerCount < PLAYER_MAX){
			pData[i][playerCount] = new PlayerData(mapId);
			pData[i][playerCount]->player = p;
			pCount[i]++;
			if (logger)
				logger->send(LOGDETAIL, GAMELOG, "Added player " + to_string(p->getClientID()) + " to map_instance " + to_string(i) + ".");
			return 0;
		}
	}
	//No Empty spots, try making a new map
	if (mapCount < MAP_MAX){
		maps[mapCount] = new Map();
		pCount[mapCount] = 0;
		//Map init here
		pData[mapCount][pCount[mapCount]] = new PlayerData(mapId);
		pCount[mapCount]++;
		mapCount++;
		if (logger)
			logger->send(LOGDETAIL, GAMELOG, "Created new map " + to_string(mapCount) + " and added player " + to_string(p->getClientID()) + ".");
	}
}

int Instance::checkForMerge(){
	//Create array of map ids and empty spaces
	MapMergeData mapMerge[MAP_MAX/2];
	int mCount = 0;
	for (int i = 0; i < mapCount; ++i){
		int playerCount = pCount[i];
		int space = PLAYER_MAX - playerCount;
		if (pCount[i] < PLAYER_MAX){
			mapMerge[mCount] = MapMergeData(i, space, playerCount);
			mCount++;
		}
	}
	//Loop array and check for pCount < map space
	for (int i = 0; i < mCount; ++i){
		//Store mergeTo data
		int mergeTo = mapMerge[i].mapId;
		int mergeToSpace = mapMerge[i].space;
		//Inner array loop
		for (int j = 0; j < mCount; ++i){
			//If the mapid is already being merged or we're doubled up, skip.
			if (mapMerge[j].merging || mergeTo == mapMerge[j].mapId)
				continue;
			//Store mergeFrom info
			int mergeFrom = mapMerge[j].mapId;
			int mergeFromPlyrs = mapMerge[j].pCount;
			//mergeTo space >= mergeFrom Player count
			if (mergeToSpace >= mergeFromPlyrs){
				//Create a new Merge
				merging[mergeCount] = MergeInfo(mergeFrom, mergeTo, mergeFromPlyrs);
				mergeCount++;
				mapMerge[i].space -= mergeFromPlyrs;
				mapMerge[j].merging = true;
			}
		}
	}
	return mCount;
}

void Instance::pushPlayerToMap(PlayerData& p, int mapID){
	for (int i = 0; i < PLAYER_MAX; ++i){
		if (!pData[mapID][i]){
			pData[mapID][i]->mapID = mapID;
			pData[mapID][i] = &p;
		}
	}
}

void Instance::mergeMaps(){
	for (int i = 0; i < mergeCount; ++i){
		if (merging[i].mapFrom == -1)
			continue;
		int mTo = merging[i].mapTo;
		int mFr = merging[i].mapFrom;
		int pCount = merging[i].pCount;
		for (int j = 0; j < pCount; ++j){
			PlayerData* movePlayer = pData[mFr][j];
			pushPlayerToMap(*movePlayer, mTo);
			pData[mFr][j] = NULL;
		}
		merging[i] = MergeInfo();
	}
	mergeCount = 0;
}