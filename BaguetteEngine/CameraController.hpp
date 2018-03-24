#pragma once

#include "EasyCamera.hpp"

class CameraController
{
public:
	CameraController(void);
	~CameraController(void);

	void update(float dt);
	void setTarget(const ofVec3f & position);

	void begin(ofRectangle viewport = ofRectangle());
	void end(void);

	void switchOrbit(void);

	void zoom(int factor);

	void right(void);
	void left(void);

private:
	EasyCamera cam_;
};

