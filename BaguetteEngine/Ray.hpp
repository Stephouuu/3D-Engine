#pragma once

#include "ofVec3f.h"

struct Ray
{
	Ray(void) = default;
	Ray(const ofVec3f & o, const ofVec3f & d)
		: origin(o), direction(d)
	{
	}

	ofVec3f origin;
	ofVec3f direction;
};