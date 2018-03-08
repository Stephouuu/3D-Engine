#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "IGuiView.hpp"
#include "SceneController.hpp"
#include "EditMenu.hpp"
#include "SceneViewer.hpp"
#include "Image.h"

class MainMenu : public IGuiView
{
public:
	MainMenu(SceneController & scene, EditMenu & editMenu, SceneViewer & sceneViewer);
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
	ofxButton			insertPlan_;
	ofxButton			insertBox_;
	ofxButton			insertCone_;
	ofxButton			exportScene_;
	ofMouseEventArgs	mouseEvents_;

	SceneController		&scene_;
	EditMenu			&editMenu_;
	SceneViewer			&sceneViewer_;

	Image				exportImg_;
};