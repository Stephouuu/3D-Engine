#pragma once

#include "ofxGui.h"

class Vec2Slider : public ofxVec2Slider
{
public:
	Vec2Slider(void);
	virtual ~Vec2Slider(void);

	void setValue(ofVec2f & vec);
};

