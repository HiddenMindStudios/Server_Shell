#pragma once
#include "Define.h"

class STRUCTURE_API Resource
{
private:
	int curr;
	int max;
	int natRec;

public:
	inline int getCurrent()
	{
		return curr;
	};

	inline int getMax()
	{
		return max;
	};

	inline int getRecover()
	{
		return natRec;
	};
};