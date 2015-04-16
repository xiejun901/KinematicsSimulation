#include"Vector2d.h"

Vector2D::Vector2D()
{

}
Vector2D::~Vector2D()
{

}
Vector2D operator+(const Vector2D &v1, const Vector2D &v2)
{
	return Vector2D(v1.x + v2.x, v1.y + v2.y);
}
Vector2D operator-(const Vector2D &v1, const Vector2D &v2)
{
	return Vector2D(v1.x - v2.x, v1.y - v2.y);
}
Vector2D operator*(const Vector2D &v1, const Vector2D &v2)
{
	return Vector2D(v1.x * v2.x, v1.y * v2.y);
}
Vector2D operator*(const double &d1, const Vector2D &v2)
{
	return Vector2D(d1 * v2.x, d1* v2.y);
}
Vector2D operator/(const Vector2D &v2, const double &d1)
{
	return Vector2D(v2.x / d1, v2.y / d1);
}