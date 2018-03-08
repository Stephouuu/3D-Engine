#pragma once

#include "ofxGui.h"
#include "ofMain.h"

class Vec3Slider : public ofxVec3Slider
{
public:
	Vec3Slider();
	~Vec3Slider();
	void setValue(ofVec3f & vec);
};

