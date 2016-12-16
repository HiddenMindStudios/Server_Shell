#pragma once
#include "stdafx.h"
#include "Define.h"
#include "GameDef.h"
class Game{
	MapData* mapData[MAPID_COUNT];

public:
	std::string getMapName(int id);
	int getMapId(std::string n);
	Game();
};