#pragma once

#include "EasyCamera.hpp"

class CameraController
{
public:
	CameraController(void);
	~CameraController(void);

	void reset(void);

	void update(float dt);
	void setTarget(const ofVec3f & position);

	void begin(ofRectangle viewport = ofRectangle());
	void end(void);

	void zoom(int factor);

	void stop(void);
	void right(void);
	void left(void);

	void swapPerspectiveOrtho(bool value);

private:
	EasyCamera cam_;
};

