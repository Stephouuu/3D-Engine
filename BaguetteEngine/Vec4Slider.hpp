#pragma once

#include "ofxGui.h"

class Vec4Slider : public ofxVec4Slider
{
public:
	Vec4Slider(void);
	virtual ~Vec4Slider(void);

	void setValue(ofVec4f & vec);
};

