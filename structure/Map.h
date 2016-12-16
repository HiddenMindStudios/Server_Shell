#pragma once
#include "Define.h"
#include "Vector2d.h"
#include <vector>
#include "MapObject.h"
#include "Unit.h"
#define MAX_UNITS 500
#define MAX_OBJ 500

class STRUCTURE_API Map
{
private:
	MapObject* obj[MAX_OBJ];
	Unit* units[MAX_UNITS];
	char* name;
	bool bFlagForMerge;
public:
	Map(Map& m);
	Map();
	~Map();

	inline MapObject* Map::getObj(int i) const { return this->obj[i]; };

	MapObject* Map::addObj(MapObject& m);
	void Map::delObj(int index);

	void Map::update(double dt);

	inline char* Map::getName() const { return this->name; };
	inline void Map::setName(char* s) { this->name = s; };
};