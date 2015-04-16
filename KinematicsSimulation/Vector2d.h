#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_
#pragma once
#include<math.h>
class Vector2D
{
	friend Vector2D operator+(const Vector2D &v1, const Vector2D &v2);
	friend Vector2D operator-(const Vector2D &v1, const Vector2D &v2);
	friend Vector2D operator*(const Vector2D &v1, const Vector2D &v2);
	friend Vector2D operator*(const double &d1, const Vector2D &v2);
	friend Vector2D operator/(const Vector2D &v2, const double &d1);
public:
	Vector2D();
	Vector2D(const double &x, const double &y) :x(x), y(y){}
	~Vector2D();
	double getx()
	{
		return x;
	}
	double gety()
	{
		return y;
	}
	void addx(double var)
	{
		x = x + var;
	}
	void addy(double var)
	{
		y = y + var;
	}
	double length()
	{
		return sqrt(x*x + y*y);
	}
	double sqrLength()
	{
		return x*x + y*y;
	}
	Vector2D nomorlize()
	{
		double var = 1 / length();
		return Vector2D(x*var, y*var);
	}
	void negtive()
	{
		x = -x;
		y = -y;
	}
	void negtivex()
	{
		x = -x;
	}
	void negtivey()
	{
		y = -y;
	}
	void add(Vector2D v)
	{
		x = x + v.x;
		y = y + v.y;
	}
	void sub(Vector2D v)
	{
		x = x - v.x;
		y = y - v.y;
	}
	void multiply(double var)
	{
		x = x*var;
		y = y*var;
	}
	void devide(double var)
	{
		x = x / var;
		y = y / var;
	}
	void dotMultiply(Vector2D v)
	{
		x = x*v.x;
		y = y*v.y;
	}
private:
	double x;
	double y;
};
#endif