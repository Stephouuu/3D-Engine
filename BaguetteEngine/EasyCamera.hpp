#pragma once

#include "ofMain.h"
#include "SceneNode.hpp"

#include "Identifiable.hpp"
#include "MathUtils.hpp"

class EasyCamera : public ofCamera
{
public:
	const ofVec3f BasePosition = { 0, 10, 5 };
	const float ZoomFactor = 5.f;

public:
	enum class OrbitDirection : int {
		Backward = -1,
		None = 0,
		Forward = 1
	};

public:
	EasyCamera(void);
	~EasyCamera(void);

	void reset(void);

	void update(float dt);
	void setTarget(const ofVec3f & position);

	void begin(ofRectangle viewport = ofRectangle()) override;
	void end(void) override;

	void zoom(float f);

	void setLongitudeDirection(OrbitDirection dir);
	void setLatitudeDirection(OrbitDirection dir);

	void setElevation(float distance);
	float getElevation(void) const;

private:
	void targetTransition(float dt);
	void zoomTransition(float dt);
	void orbit(float dt);

	float getDistanceFromTarget(void) const;

private:
	ofVec3f currentLookAt_;
	ofVec3f target_;
	float targetTransitionDt_;
	float latitude_;
	float longitude_;

	float elevation_;
	float savedElevation_;
	float zoomDt_;
	float zoomAxes_;
	OrbitDirection longitudeDirection_;
	OrbitDirection latitudeDirection_;
};