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
	virtual ~MainMenu();
	virtual void draw();
	virtual void setup();
	virtual void refresh(int newEditorDimension);

private:
	void refresh2D(void);
	void refresh3D(void);

	void buttonPressedFile(const void * sender);
	void buttonPressed2D(const void * sender);
	void buttonPressed3D(const void * sender);

private:
	ofxPanel			gui_;
	ofxGuiGroup			insertGroup_;
	ofxGuiGroup			primitiveGroup_;
	ofxGuiGroup			fileGroup_;

	ofxButton			insertSphere_;
	ofxButton			insertPlan_;
	ofxButton			insertBox_;
	ofxButton			insertCone_;

	ofxButton			insertTriangle_;
	ofxButton			insertEllipse_;
	ofxButton			insertPoint_;
	ofxButton			insertCircle_;
	ofxButton			insertRectangle_;

	ofxButton			exportScene_;
	ofMouseEventArgs	mouseEvents_;

	SceneController		&scene_;
	EditMenu			&editMenu_;
	SceneViewer			&sceneViewer_;

	Image				exportImg_;
};