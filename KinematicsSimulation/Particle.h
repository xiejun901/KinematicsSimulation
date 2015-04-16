#ifndef _PARTICLE_H_
#define _PARTICLE_H_
#pragma once
#include"Vector2d.h"
class Particle
{
public:
	Vector2D<double> position;
	Vector2D<double> velocity;
	Vector2D<double> acceleration;
	double radius;
public:
	Particle(Vector2D<double> p, Vector2D<double> v, Vector2D<double> a, double r) :position(p), velocity(v), acceleration(a), radius(r){}
	Particle(){}
	~Particle(){}
};
#endif