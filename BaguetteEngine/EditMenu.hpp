#pragma once

#include "ofxGui.h"
#include "ofMain.h"

#include "IGuiView.hpp"
#include "Identifiable.hpp"
#include "SceneController.hpp"
#include "Vec3Slider.hpp"
#include "Vec2Slider.hpp"
#include "Vec4Slider.hpp"
#include "ColorSlider.hpp"
#include "toggle.hpp"
#include "Texture.hpp"

class EditMenu : public IGuiView
{
public:
	EditMenu(SceneController &scene);
	virtual ~EditMenu();

	virtual void draw();
	virtual void setup();
	virtual void refresh(int newEditorDimension);
	virtual void displayListImage();
	void displayListSecondary();
	virtual void focus(const Identifiable & id);
	virtual void windowsResized(const ofPoint & size);

	virtual void update(float dt);

	bool getIsImported();
	void setIsImported(bool value);
	void vecSliderPositionChange(ofVec3f & vec);
	void vec3SliderPerlinChange(ofVec3f & vec);
	void vecSliderSizeChange(ofVec3f & vec);
	void vecSliderColorChange(ofColor & color);
	void vecSliderRotationChange(ofVec3f & color);
	void vecSliderColorSpecularChange(ofColor & color);
	void vecSliderColorDiffuseChange(ofColor & color);
	void vec2SliderBezierChange(ofVec2f & p);
	void vec2SliderBezierSplineChange(ofVec2f & p);

	void vec2SliderPositionChange(ofVec2f & vec);
	void vec2SliderSizeChange(ofVec2f & vec);
	void vec2SliderRotationChange(ofVec3f & v);

	void buttonPressedAnimations(const void * sender);

	void onColorOutChange(ofColor & color);
	void onThicknessChange(ofVec2f & vec);
	void onColorSceneChange(ofColor & color);

	void toggleSelectedFilter(const void * sender, bool & value);
	void toggleSelectedMode(const void * sender, bool & value);
	void toggleSelectedPrimary(const void * sender, bool & value);
	void toggleSelectedSecondary(const void * sender, bool & value);

private:
	void baseSetup();
	void updateValues(SceneNode *node);
	void onTransformationChange(void);

	void initFilters(void);
	void initListeners(void);
	void initModeComposition(void);
	void removeListeners(void);

	void setupGuiFromDrawableType(const ADrawable * drawable);
	void updateGuiFromDrawableType(const ADrawable * drawable);

private:
	ofxPanel					gui_;
	ofxGuiGroup					selectPrimaryTextures_;
	ofxGuiGroup					selectSecondaryTextures_;
	ofxGuiGroup					composition_;
	ofxGuiGroup					mode_;
	ofxGuiGroup					filter_;
	ofMouseEventArgs			mouseEvents_;

	SceneController				&scene_;

	Vec3Slider					position_;
	Vec3Slider					size_;
	Vec3Slider					rotation_;

	Vec2Slider					position2d_;
	Vec2Slider					size2d_;
	Vec3Slider					rotation2d_;

	Vec2Slider					thickness_;
	Vec2Slider					curveParam1_;
	Vec2Slider					curveParam2_;
	Vec2Slider					curveParam3_;
	Vec2Slider					curveParam4_;
	Vec2Slider					curveParam5_;
	Vec2Slider					curveParam6_;
	Vec2Slider					curveParam7_;

	ColorSlider					colorFill_;
	ColorSlider					colorOut_;
	ColorSlider					colorScene_;
	int							currentDimension_;
	bool						resetting_;
	float						yolo_;
	ofVec3f						yoloArg_;
	Texture::CompositionType	compositionMode_;

	Vec3Slider					perlinNoiseSize_;
	Vec3Slider					PerlinNoise_;

	Vec2Slider					brightness_;
	ColorSlider					colorDiffuse_;
	ColorSlider					colorSpecular_;

	vector<ofxToggle *>			primaryTextureList_;
	vector<ofxToggle *>			secondaryTextureList_;
	vector<ofxToggle *>			filterList_;
	vector<ofxToggle *>			modeCompositionList_;

	map <std::string, Texture::FilterType>		filterLabel_;
	map <std::string, Texture::CompositionType>	compositionLabel_;

	vector<ofxButton*>			images_;
	ofxButton					animationButton_;

public:
	bool				isImported;
};

