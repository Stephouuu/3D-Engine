#pragma once

#include "ofxGui.h"

#include "IGuiView.hpp"
#include "Identifiable.hpp"
#include "SceneController.hpp"

class EditMenu : public IGuiView
{
public:
	EditMenu(SceneController &scene);
	~EditMenu();
	virtual void draw();
	virtual void setup();
	void setFocus(Identifiable & obj);
	void vecSliderChange(const void * sender);


private:
	ofxPanel					gui_;
	ofMouseEventArgs			mouseEvents_;

	SceneNode					*currentObj_;
	SceneController				&scene_;

	ofParameter<ofVec3f>		position_;
	ofParameter<ofColor>		colorFill_;
	ofParameter<float>			radius_;
	ofParameter<ofVec2f>		size_;
};

