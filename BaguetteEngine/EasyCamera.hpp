#pragma once

#include "ofMain.h"

#include "Identifiable.hpp"
#include "SceneNode.hpp"

class EasyCamera : public ofEasyCam
{
public:
	EasyCamera(void);
	~EasyCamera(void);

	void update(float dt);
	void targetPositionChanged(void);

	void begin(ofRectangle viewport = ofRectangle()) override;
	void end(void) override;

	void setTargetSceneNode(SceneNode *node);

private:
	void reset(void);
	void transition(float dt);

private:
	ofVec3f currentLookAt_;
	SceneNode *target_;
	float dt_;
};

