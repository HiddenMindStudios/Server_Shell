#include "stdafx.h"
#include "Path.h"
#include "Vector2d.h"

Path::Path()
{
	pointCount = 0;
	nextPos    = 0;
	point[0] = Vector2D(0, 0);
}

void Path::addPoint(Vector2D v)
{
	point[pointCount] = v;
	pointCount++;
}

Vector2D Path::getNVectorToNext(Vector2D const &v)
{
	Vector2D nvect = Vector2D(point[nextPos]);

	nvect += v;
	nvect.normalize();
	return nvect;
}