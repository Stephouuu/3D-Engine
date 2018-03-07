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

private:
	ofxPanel			gui_;
	ofxGuiGroup			positiontGroup_;
	ofxGuiGroup			colorGroup_;
	ofMouseEventArgs	mouseEvents_;
};

