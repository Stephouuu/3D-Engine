#include "Sphere.hpp"

Sphere::Sphere(double r, const ofVec3f & p, const ofVec3f & e, const ofVec3f & c)
	: radius(r), position(p), emission(e), color(c)
{
}

Sphere::~Sphere(void)
{
}

double Sphere::intersect(const Ray & ray) const
{
	double distance = 0;
	double epsilon = 1e-4;
	double t;

	ofVec3f delta = position - ray.origin;
	double a = delta.dot(delta);
	double b = delta.dot(ray.direction);
	double c = radius * radius;
	double discriminant = b * b - a + c;

	if (discriminant < 0)
	{
		// pas d'intersection
		distance = 0;
	}
	else
	{
		discriminant = std::sqrt(discriminant);
		t = b - discriminant;
		if (t > epsilon) {
			distance = t;
		}
		else {
			t = b + discriminant;
			distance = (t > epsilon) ? t : 0;
		}
	}
	return distance;
}