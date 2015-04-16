#ifndef _PARTICLE_H_
#define _PARTICLE_H_
#pragma once
#include"Vector2d.h"
class Particle
{
public:
	Vector2D<float> position;
	Vector2D<float> velocity;
	Vector2D<float> acceleration;
	float radius;
public:
	Particle(Vector2D<float> p, Vector2D<float> v, Vector2D<float> a, float r) :position(p), velocity(v), acceleration(a), radius(r){}
	Particle(){}
	~Particle(){}
};
#endif