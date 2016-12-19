#pragma once
#include "Vector2D.h"
#include <math.h>
using namespace std;

typedef long long GUID_t;

class STRUCTURE_API MapObject
{
protected:
	Vector2D* pos;
	Vector2D* move;
	char* name;
	GUID_t id;
	int bounding[2];
	bool destructable;
	bool clipping;
	bool absolute; //Potentially useless and dangerous

public:
	MapObject();
	MapObject(MapObject& m);
	~MapObject();
	
	inline void MapObject::setAbsolute(bool b) { this->absolute = b; };
	inline bool MapObject::isAbsolute() const { return this->absolute; };

	inline bool MapObject::hasClipping() const { return this->clipping; };
	inline void MapObject::setClipping(bool b) { this->clipping = b; };

	inline bool MapObject::isDestructable() const { return this->destructable; };
	inline void MapObject::isDestructable(bool b) { this->destructable = b; };

	inline int MapObject::getBoundingX() const { return this->bounding[0]; };
	inline int MapObject::getBoundingY() const { return this->bounding[1]; };

	inline void MapObject::setBoundingX(int i) { this->bounding[0] = i; };
	inline void MapObject::setBoundingY(int i) { this->bounding[1] = i; };

	inline void MapObject::setPosX(double d) { this->pos->setX(d); };
	inline void MapObject::setPosY(double d) { this->pos->setY(d); };
	inline void MapObject::setPosVect(Vector2D& v) { delete this->pos; this->pos = new Vector2D(v); };

	inline void MapObject::setMoveX(double d) { this->move->setX(d); };
	inline void MapObject::setMoveY(double d) { this->move->setY(d); };
	inline void MapObject::setMoveVect(Vector2D& v) { delete this->move; this->move = new Vector2D(v); };

	inline double MapObject::getPosX() const { return this->pos->getX(); };
	inline double MapObject::getPosY() const { return this->pos->getY(); };

	inline Vector2D MapObject::getMoveVect() const { return *this->move; }
	inline Vector2D MapObject::getPosVect() { return *this->pos; };

	inline char* MapObject::getName() const { return this->name; };
	inline void MapObject::setName(char* s) { this->name = s; };

	inline GUID_t MapObject::getGUID() const { return this->id; };
	inline void MapObject::generateGUID() { this->id = rand() * rand() / 2; };
};