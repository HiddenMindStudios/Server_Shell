#pragma once
#include "Define.h"
#include "Entity.h"
#include "Ability.h"
#include <vector>

class STRUCTURE_API Unit : public Entity
{
private:
	int resourceID;
public:
	Unit();
	Unit(Unit& u);
	~Unit(void);
	void update(double dt);
};

