#pragma once
#include "stdafx.h"
#include "Define.h"
#include "Map.h"
#include "MapObject.h"
#include "Player.h"
#include "Log.h"
#define MAP_MAX 50
#define PLAYER_MAX 50

struct PlayerData{
	Player* player;
	int mapID;
	PlayerData(int id) : mapID(id){};
};

struct MergeInfo{
	int mapFrom;
	int mapTo;
	int pCount;
	MergeInfo(int mF, int mT, int pC) :mapFrom(mF), mapTo(mT), pCount(pC){};
	MergeInfo(){ mapFrom = -1; };
};

struct MapMergeData{
	int mapId;
	int space;
	int pCount;
	bool merging = false;
	MapMergeData(int mId, int sp, int pC) :mapId(mId), space(sp), pCount(pC){};
	MapMergeData(){};
};

class Instance{
	Map* maps[MAP_MAX];
	int mapCount;
	PlayerData* pData[MAP_MAX][PLAYER_MAX];
	int pCount[MAP_MAX];
	string mapName;
	MergeInfo merging[MAP_MAX/2];
	int mergeCount;
	int mapId;
	Log* logger;
	void pushPlayerToMap(PlayerData& p, int mapID); //Done
public:
	void update(double dt);
	int addPlayerToMap(Player* p); //Done
	int checkForMerge(); //Done
	int getPlayerMapID(int cID); // Done
	void mergeMaps();//Done
	inline int getMapID(){ return mapId; };
	inline int getMapCount(){ return this->mapCount; };	//Done
	Player* getPlayerByClientID(int cID); //Done
	int removePlayer(int cID); //Done
	Instance(int mID, string mN, Log* l); //Done
	Instance(Log* l);
	Instance();
};