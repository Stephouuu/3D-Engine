#pragma once

#include "ofMain.h"
#include "SceneNode.hpp"

#include "Identifiable.hpp"
#include "MathUtils.hpp"

class EasyCamera : public ofCamera
{
public:
	const ofVec3f BasePosition = { 0, 10, 5 };
	enum class Direction : int {
		East =  1,
		West =  -1
	};

public:
	EasyCamera(void);
	~EasyCamera(void);

	void update(float dt);
	void setTarget(const ofVec3f & position);

	void begin(ofRectangle viewport = ofRectangle()) override;
	void end(void) override;

	void switchOrbit(void);
	void zoom(float f);

	void setDirection(Direction dir);

private:
	void targetTransition(float dt);
	void zoomTransition(float dt);
	void orbit(float dt);

	void setDistance(float distance);
	float getDistance(void) const;

private:
	ofVec3f currentLookAt_;
	ofVec3f target_;
	float targetTransitionDt_;
	float azimuth_;
	float orbiting_;

	float distance_;
	float savedDistance_;
	float zoomDt_;
	float zoomFactor_;
	Direction direction_;
};