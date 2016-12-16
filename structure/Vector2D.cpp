#include "stdafx.h"
#include "Vector2d.h"
using namespace std;

Vector2D::Vector2D()
{
	x = 0.;
	y = 0.;
}

Vector2D::Vector2D(double sx, double sy)
{
	x = sx;
	y = sy;
}

Vector2D::Vector2D(const Vector2D& v)
{
	this->x = v.getX();
	this->y = v.getY();
}

Vector2D::~Vector2D()
{

}

double Vector2D::getLength()
{
	return sqrt(x * x + y * y);
}

double Vector2D::getLength2()
{
	return x * x + y * y;
}

double Vector2D::getDist(Vector2D v)
{
	return sqrt(this->getDist2(v));
}

double Vector2D::getDist2(Vector2D v)
{
	double dx = x - v.getX();
	double dy = y - v.getY();
	return dx * dx + dy * dy;
}

double Vector2D::getAngleTo(Vector2D v)
{
	return atan2(y, x) - atan2(v.getY(), v.getX());
}

double Vector2D::getAngleTo()
{
	return atan2(y, x);
}

void Vector2D::normalize()
{
	double l = this->getLength();
	if( l > 0)
	{
		x /= l;
		y /= l;
	}
}

Vector2D Vector2D::getPerp()
{
	return Vector2D(-y, x);
}

void Vector2D::transRotate(double phi)
{
	double c = cos(phi);
	double s = sin(phi);
	x = c * x - s * y;
	y = s * x + c * y;
}

void Vector2D::transProject(Vector2D v)
{
	double s = this->getLength2() / v.getLength2();
	x *= s;
	y *= s;
}

void Vector2D::transMirror(Vector2D v)
{
	double s = 2 * this->getLength2() / v.getLength2();
	x = s * v.getX() - x;
	y = s * v.getY() - y;
}

