#pragma once

#include "ofxGui.h"

#include "IGuiView.hpp"

class EditMenu : public IGuiView
{
public:
	EditMenu();
	~EditMenu();
	virtual void draw();
	virtual void setup();
	void setFocus(const int id);

private:
	ofxPanel				gui_;
	ofMouseEventArgs		mouseEvents_;
	ofParameter<ofVec3f>	position_;
	ofParameter<ofColor>	colorFill_;
	ofParameter<float>		radius_;
	ofParameter<ofVec2f>	size_;
};

