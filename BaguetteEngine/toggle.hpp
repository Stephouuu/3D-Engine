#pragma once

#include "ofxGui.h"

class toggle : public ofxToggle
{
public:
	bool getValue();
	void setValue(bool);
};

