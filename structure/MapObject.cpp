#include "stdafx.h"
#include "MapObject.h"

MapObject::MapObject(MapObject& m)
{
	move = new Vector2D(*m.move);
	pos = new Vector2D(*m.move);
	//We want to create a new GUID for the new object
	generateGUID();
}

MapObject::MapObject()
{
	move = new Vector2D();
	pos = new Vector2D();
	generateGUID();
}

MapObject::~MapObject()
{
	delete move;
	delete pos;
}