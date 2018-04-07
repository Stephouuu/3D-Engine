#define _USE_MATH_DEFINES
#include "MathUtils.hpp"
#include <cmath>

ofPoint MathUtils::Rotate2D(const ofPoint &p, float degrees, const ofPoint & origin)
{
	float r = DegreesToRadians(degrees);
	
	return {
		(p.x - origin.x) * std::cos(r) - (p.y - origin.y) * std::sin(r) + origin.x,
		(p.x - origin.x) * std::sin(r) + (p.y - origin.y) * std::cos(r) + origin.y
	};
}

float MathUtils::DegreesToRadians(float degrees)
{
	return (degrees * (M_PI / 180.f));
}

float MathUtils::RadiansToDegrees(float radians)
{
	return (radians * (180.f / M_PI));
}

float MathUtils::easeInSine(float t)
{
	return std::sin(1.5707936f * t);
}

double  MathUtils::clamp(double x)
{
	return x < 0 ? 0 : x > 1 ? 1 : x;
}