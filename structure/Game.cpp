#include "stdafx.h"
#include "Game.h"

//Use username to query the db for the db user id. Then, query the server for all character sets with that id.

Game::Game(){
	mapData[0] = new MapData(0, "Developer Test");
}

std::string Game::getMapName(int id){
	for (int i = 0; i < MAPID_COUNT; ++i){
		if (mapData[i]->id == id){
			return mapData[i]->name;
		}
	}
	return NULL;
}