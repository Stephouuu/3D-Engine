#pragma once

#include "ofxGui.h"
#include "ofMain.h"

class ColorSlider : public ofxColorSlider
{
public:
	ColorSlider();
	~ColorSlider();
	void setValue(ofColor & color);
};

