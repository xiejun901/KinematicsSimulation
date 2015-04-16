#ifndef _PARTICLE_H_
#define _PARTICLE_H_
#pragma once
#include"Vector2d.h"
class Particle
{
public:
	Vector2D position;
	Vector2D velocity;
	Vector2D acceleration;
	double radius;
public:
	Particle(Vector2D p, Vector2D v, Vector2D a, double r):position(p), velocity(v), acceleration(a), radius(r){}
	Particle(){}
	~Particle(){}
};
#endif