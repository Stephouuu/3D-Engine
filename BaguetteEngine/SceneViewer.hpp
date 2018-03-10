#pragma once

#include <vector>

#include "ofMain.h"
#include "ofxGui.h"

#include "IGuiView.hpp"
#include "SceneController.hpp"

class SceneViewer : public IGuiView
{
public:
	SceneViewer(SceneController & scene);
	virtual ~SceneViewer(void);

	virtual void draw(void);
	virtual void setup(void);
	virtual void refresh(int newEditorDimension);
	virtual void focus(const Identifiable & id);
	virtual void windowsResized(const ofPoint & size);

	void update(void);

private:
	void buttonPressed(const void * sender);

private:
	ofxPanel gui_;
	ofxGuiGroup	layout_;

	std::vector<ofxButton> buttons_;

	SceneController	& scene_;
};