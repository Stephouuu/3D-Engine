#pragma once

#include "ofxGui.h"
#include "ofMain.h"

#include "IGuiView.hpp"
#include "Identifiable.hpp"
#include "SceneController.hpp"
#include "Vec3Slider.hpp"
#include "Vec2Slider.hpp"
#include "ColorSlider.hpp"

class EditMenu : public IGuiView
{
public:
	EditMenu(SceneController &scene);
	virtual ~EditMenu();

	virtual void draw();
	virtual void setup();
	virtual void refresh(int newEditorDimension);
	virtual void focus(const Identifiable & id);

	void vecSliderPositionChange(ofVec3f & vec);
	void vecSliderSizeChange(ofVec3f & vec);
	void vecSliderColorChange(ofColor & color);
	void vecSliderRotationChange(ofColor & color);

	void vec2SliderPositionChange(ofVec2f & vec);
	void vec2SliderSizeChange(ofVec2f & vec);

private:
	void baseSetup();
	void updateValues(SceneNode *node);

private:
	ofxPanel					gui_;
	ofMouseEventArgs			mouseEvents_;

	SceneController				&scene_;

	Vec3Slider					position_;
	Vec3Slider					size_;
	Vec3Slider					rotation_;

	Vec2Slider					position2d_;
	Vec2Slider					size2d_;
	Vec2Slider					rotation2d_;

	ColorSlider					colorFill_;
	int							currentDimension_;
};

