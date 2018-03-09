#pragma once

#include "ofPoint.h"

class MathUtils
{
public:
	static ofPoint Rotate2D(const ofPoint &p, float degrees, const ofPoint & origin = ofPoint());
	static float DegreesToRadians(float degrees);
	static float RadiansToDegrees(float radians);
};

