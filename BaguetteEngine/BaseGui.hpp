#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class BaseGui
{
public:
	BaseGui();
	~BaseGui();
	void draw();
	void setup();

private:
	ofxPanel			gui_;
	ofxGuiGroup			insertGroup_;
	ofxGuiGroup			fileGroup_;

	ofxButton			insertSphere_;
	ofxButton			exportScene_;

};
