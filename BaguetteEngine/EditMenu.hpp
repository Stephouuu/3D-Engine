#pragma once

#include "ofxGui.h"
#include "ofMain.h"

#include "IGuiView.hpp"
#include "Identifiable.hpp"
#include "SceneController.hpp"
#include "Vec3Slider.hpp"
#include "Vec2Slider.hpp"
#include "Vec1Slider.hpp"
#include "ColorSlider.hpp"

class EditMenu : public IGuiView
{
public:
	EditMenu(SceneController &scene);
	virtual ~EditMenu();

	virtual void draw();
	virtual void setup();
	virtual void refresh(int newEditorDimension);
	virtual void refreshImages();
	virtual void focus(const Identifiable & id);
	virtual void windowsResized(const ofPoint & size);

	bool getIsImported();
	void setIsImported(bool value);
	void vecSliderPositionChange(ofVec3f & vec);
	void vecSliderSizeChange(ofVec3f & vec);
	void vecSliderColorChange(ofColor & color);
	void vecSliderRotationChange(ofVec3f & color);

	void vec2SliderPositionChange(ofVec2f & vec);
	void vec2SliderSizeChange(ofVec2f & vec);
	void vec2SliderRotationChange(ofVec3f & v);

	void onColorOutChange(ofColor & color);
	void onThicknessChange(ofVec2f & vec);
	void onColorSceneChange(ofColor & color);

private:
	void baseSetup();
	void updateValues(SceneNode *node);

	void initListeners(void);
	void removeListeners(void);

private:
	ofxPanel					gui_;
	ofxGuiGroup					selectTextures_;
	ofMouseEventArgs			mouseEvents_;

	SceneController				&scene_;

	Vec3Slider					position_;
	Vec3Slider					size_;
	Vec3Slider					rotation_;

	Vec2Slider					position2d_;
	Vec2Slider					size2d_;
	Vec3Slider					rotation2d_;

	Vec2Slider					thickness_;

	ColorSlider					colorFill_;
	ColorSlider					colorOut_;
	ColorSlider					colorScene_;
	int							currentDimension_;

	vector<ofxButton*>			images_;
public:
	bool				isImported;
};

