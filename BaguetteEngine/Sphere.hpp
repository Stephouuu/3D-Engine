#pragma once

#include "Ray.hpp"

struct Sphere
{
	Sphere(double r, const ofVec3f & p, const ofVec3f & e, const ofVec3f & c);
	~Sphere(void);

	double intersect(const Ray & ray) const;

	double radius;
	ofVec3f position;
	ofVec3f emission;
	ofVec3f color;
};

