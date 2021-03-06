#pragma once

#include <vector>

#include "ofMain.h"
#include "ofxGui.h"

#include "IGuiView.hpp"
#include "SceneController.hpp"
#include "EditMenu.hpp"
#include "SceneViewer.hpp"
#include "Image.hpp"
#include "Model3D.hpp"

class MainMenu : public IGuiView
{
public:
	MainMenu(SceneController & scene, EditMenu & editMenu, SceneViewer & sceneViewer);
	virtual ~MainMenu();
	virtual void draw();
	virtual void setup();
	virtual void refresh(int newEditorDimension);
	virtual void focus(const Identifiable & id);
	virtual void windowsResized(const ofPoint & size);
	void vec2SliderFromXYChange(ofVec2f & vec);
	void vec2SliderFromWHChange(ofVec2f & vec);
	bool wantScreenshot(void);

	virtual void update(float dt);

private:
	void refresh2D(void);
	void refresh3D(void);
	void refreshRaytracer(void);

	void buttonPressedFile(const void * sender);
	void buttonPressedMode(const void * sender);
	void buttonPressed2D(const void * sender);
	void buttonPressed3D(const void * sender);
	void buttonPressed3DModel(const void * sender);
	void buttonPressedShapeVector(const void * sender);
	void toggleSwapMode(const void * sender, bool & value);
	void vecSliderModel3DBoxChange(ofVec3f & vec);
	void addPortails(const void * sender);
	void addCamera(const void * sender);
	void removeCamera(const void * sender);

	void setup_(void);

private:
	ofxPanel			gui_;
	ofxGuiGroup			insertGroup_;
	ofxGuiGroup			primitiveGroup_;
	ofxGuiGroup			model3DGroup_;
	ofxGuiGroup			lightGroup_;
	ofxGuiGroup			modelLightGroup_;
	ofxGuiGroup			fileGroup_;
	ofxGuiGroup			vectorShapeGroup_;
	ofxGuiGroup			cropImage_;
	ofxGuiGroup			camera_;

	ofxButton			insertSphere_;
	ofxButton			insertPlan_;
	ofxButton			insertBox_;
	ofxButton			insertCone_;
	ofxButton			insert3DModel_;

	ofxButton			insertTriangle_;
	ofxButton			insertEllipse_;
	ofxButton			insertPoint_;
	ofxButton			insertCircle_;
	ofxButton			insertRectangle_;

	ofxButton			insertBezier_;
	ofxButton			insertBezierSpline_;
	ofxButton			insertHermite_;

	ofxButton			insertAmbiantLight_;
	ofxButton			insertDirectionalLight_;
	ofxButton			insertPonctualLight_;
	ofxButton			insertSpotLight_;
	ofxButton			lambertLight_;
	ofxButton			gouraudLight_;
	ofxButton			phongLight_;
	ofxButton			blinnPhongLight_;
	ofxButton			colorFillLight_;
	ofxButton			noneLight_;

	ofxButton			insertDialogVector_;
	ofxButton			insertSmileVector_;

	ofxGuiGroup			modeGroup_;
	ofxButton			scene2D_;
	ofxButton			scene3D_;
	ofxButton			sceneRaytracer_;

	ofxButton			portails_;

	ofxButton			addCamera_;
	ofxButton			removeCamera_;

	ofxButton			exportScene_;
	ofxButton			importImage_;
	ofxButton			importCroppedImage_;
	ofMouseEventArgs	mouseEvents_;

	Vec3Slider			model3DBoxSlider_;
	Vec2Slider			fromXY_;
	Vec2Slider			cropWH_;
	ofVec2f				fromXYValues_;
	ofVec2f				cropWHValues_;

	SceneController		&scene_;
	EditMenu			&editMenu_;
	SceneViewer			&sceneViewer_;

	Image				exportImg_;
	ofVec3f				model3DBox_;
	bool				wantScreenshot_;

	ofxToggle			swapCameraMode_;
};