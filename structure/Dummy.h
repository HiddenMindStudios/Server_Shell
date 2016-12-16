#pragma once
#include "Entity.h"
#include "Define.h"
class STRUCTURE_API Dummy : public Entity
{
private:

public:
	Dummy(void);
	~Dummy(void);
	void update(double dt);
};

