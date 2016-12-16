#pragma once
#include "Define.h"
#include "Vector2d.h"
#include "MapObject.h"
#include "Resource.h"
using namespace std;

class STRUCTURE_API Entity : public MapObject
{
protected:
	double speed;
	int HP;
	int HPMax;
	Resource resc;

public:
	Entity();
	~Entity();
	Entity(Entity& e);
	//Make this virtual, class objs must declare their own update fxn
	virtual void update(double dt) = 0;
	void setMoveVector(Vector2D v);
};