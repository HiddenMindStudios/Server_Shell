#pragma once
#include "Define.h"

class STRUCTURE_API Vector2D
{
private:
	double x;
	double y;

public:
	Vector2D();
	Vector2D(double x, double y);
	Vector2D(const Vector2D& v);
	~Vector2D();

	inline double getX() const { return x; };
	inline double getY() const { return y; };

	inline void setX(double d) { this->x = d; };
	inline void setY(double d) { this->y = d; };

	inline Vector2D& operator+(const Vector2D& other) 
	{
		x += other.getX();
		y += other.getY();
		return *this;
	};

	inline Vector2D& operator-(const Vector2D& other)
	{
		x -= other.getX();
		y -= other.getY();
		return *this;
	};

	inline Vector2D& operator+=(const Vector2D& other)
	{
		return *this + other;
	}

	inline Vector2D& operator*(const Vector2D& other)
	{
		x *= other.getX();
		y *= other.getY();
		return *this;
	};

	inline Vector2D& operator*(double f)
	{
		x *= f;
		y *= f;
		return *this;
	};

	inline Vector2D& operator/(double f)
	{
		x /= f;
		y /= f;
		return *this;
	};

	inline bool operator==(Vector2D& v)
	{
		return (x == v.getX() && y == v.getY());
	};

	double getLength();
	double getLength2();
	double getDist(Vector2D v);
	double getDist2(Vector2D v);
	double getAngleTo(Vector2D v);
	double getAngleTo();
	void normalize();
	Vector2D getPerp();
	void transRotate(double phi);
	void transProject(Vector2D v);
	void transMirror(Vector2D v);
	
};