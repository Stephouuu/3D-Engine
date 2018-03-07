#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "IGuiView.hpp"

class MainMenu : public IGuiView
{
public:
	MainMenu();
	~MainMenu();
	void draw();
	void setup();
	void buttonPressed(const void * sender);

private:
	ofxPanel			gui_;
	ofxGuiGroup			insertGroup_;
	ofxGuiGroup			primitiveGroup_;
	ofxGuiGroup			fileGroup_;

	ofxButton			insertSphere_;
	ofxButton			exportScene_;

};

