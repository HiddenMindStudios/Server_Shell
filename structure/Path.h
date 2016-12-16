#pragma once
#include "Define.h"
#include "Vector2d.h"

class STRUCTURE_API Path
{

private:
	static const int MAX_POINTS = 100;
	Vector2D point[MAX_POINTS];
	int nextPos;
	int pointCount;
public:
	Path();
	~Path();
	
	inline Vector2D getFirstPos(){ return point[0];}
	inline int getPointCount(){ return pointCount;}
	inline Vector2D getNextPos(){ return point[nextPos];}
	inline void nextPoint(){ nextPos++;}
	inline void prevPoint(){ nextPos--;}

	void addPoint(Vector2D v );
	Vector2D getNVectorToNext(Vector2D const& v);


};