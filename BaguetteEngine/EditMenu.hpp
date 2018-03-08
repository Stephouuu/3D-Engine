#pragma once

#include "ofxGui.h"
#include "ofMain.h"

#include "IGuiView.hpp"
#include "Identifiable.hpp"
#include "SceneController.hpp"
#include "Vec3Slider.hpp"
#include "ColorSlider.hpp"

class EditMenu : public IGuiView
{
public:
	EditMenu(SceneController &scene);
	~EditMenu();
	virtual void draw();
	virtual void setup();
	void setFocus(const Identifiable & obj);
	void vecSliderPositionChange(ofVec3f & vec);
	void vecSliderSizeChange(ofVec3f & vec);
	void vecSliderColorChange(ofColor & color);
	void vecSliderRotationChange(ofColor & color);

private:
	void setValues();
	void baseSetup();

private:
	ofxPanel					gui_;
	ofMouseEventArgs			mouseEvents_;

	SceneNode					*currentObj_;
	SceneController				&scene_;


	Vec3Slider					position_;
	Vec3Slider					size_;
	Vec3Slider					rotation_;
	ColorSlider					colorFill_;
};

