#include "stdafx.h"
#include "Define.h"
#include "Map.h"
Map::Map()
{
	*this->obj = nullptr;
}

MapObject* Map::addObj(MapObject& m)
{
	int index = -1;
	for(int i = 0; i < MAX_OBJ; i++)
	{
		if (this->getObj(i) == nullptr)
		{
			index = i;
			break;
		}
	}
	if (index < 0)
		throw(index);

	this->obj[index] = new MapObject(m);
	return this->obj[index];
}

void Map::delObj(int index)
{
	if (this->obj[index] == nullptr)
		throw(1);
	delete this->obj[index];
}
