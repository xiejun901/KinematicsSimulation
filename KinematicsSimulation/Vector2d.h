#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_
#pragma once
#include<math.h>
template<class T>
class Vector2D
{
public:
	template<class T>
	friend Vector2D<T> operator+(const Vector2D< T> &v1, const Vector2D< T> &v2);
	template<class T>
	friend Vector2D<T> operator-(const Vector2D< T> &v1, const Vector2D< T> &v2);
	template<class T>
	friend Vector2D<T> operator*(const Vector2D<T> &v1, const Vector2D<T> &v2);
	template<class T>
	friend Vector2D<T> operator*(const T &d1, const Vector2D<T> &v2);
	template<class T>
	friend Vector2D<T> operator/(const Vector2D< T> &v2, const T &d1);
public:
	Vector2D();
	Vector2D(const T &x, const T &y) :x(x), y(y){}
	~Vector2D();
	T getx()
	{
		return x;
	}
	T gety()
	{
		return y;
	}
	void addx(T var)
	{
		x = x + var;
	}
	void addy(T var)
	{
		y = y + var;
	}
	T length()
	{
		return sqrt(x*x + y*y);
	}
	T sqrLength()
	{
		return x*x + y*y;
	}
	Vector2D nomorlize()
	{
		T var = 1 / length();
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
	void multiply(T var)
	{
		x = x*var;
		y = y*var;
	}
	void devide(T var)
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

template<class T>
Vector2D<T>::Vector2D()
{

}
template<class T>
Vector2D< T>::~Vector2D()
{

}

template<class T>
Vector2D< T> operator+(const Vector2D<T> &v1, const Vector2D<T> &v2)
{
	return Vector2D< T>(v1.x + v2.x, v1.y + v2.y);
}

template<class T>
Vector2D<T> operator-(const Vector2D<T> &v1, const Vector2D<T> &v2)
{
	return Vector2D<T>(v1.x - v2.x, v1.y - v2.y);
}

template<class T>
Vector2D<T> operator*(const Vector2D<T> &v1, const Vector2D<T> &v2)
{
	return Vector2D< T>(v1.x * v2.x, v1.y * v2.y);
}

template<class T>
Vector2D< T> operator*(const T &d1, const Vector2D< T> &v2)
{
	return Vector2D< T>(d1 * v2.x, d1* v2.y);
}

template<class T>
Vector2D<T> operator/(const Vector2D<T> &v2, const T &d1)
{
	return Vector2D<T>(v2.x / d1, v2.y / d1);
}

#endif