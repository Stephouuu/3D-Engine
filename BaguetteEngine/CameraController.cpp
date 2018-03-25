#include "CameraController.hpp"

CameraController::CameraController(void)
{
}

CameraController::~CameraController(void)
{
}

void CameraController::reset(void)
{
	cam_.reset();
}

void CameraController::update(float dt)
{
	cam_.update(dt);
}

void CameraController::setTarget(const ofVec3f & position)
{
	cam_.setTarget(position);
}

void CameraController::begin(ofRectangle viewport)
{
	cam_.begin(viewport);
}

void CameraController::end(void)
{
	cam_.end();
}

void CameraController::zoom(int factor)
{
	cam_.zoom(factor);
}

void CameraController::stop(void)
{
	cam_.setLongitudeDirection(EasyCamera::OrbitDirection::None);
}

void CameraController::right(void)
{
	cam_.setLongitudeDirection(EasyCamera::OrbitDirection::Forward);
}

void CameraController::left(void)
{
	cam_.setLongitudeDirection(EasyCamera::OrbitDirection::Backward);
}


void CameraController::swapPerspectiveOrtho(bool value)
{
	if (value == true)
	{
		if (cam_.getOrtho() == false)
			cam_.enableOrtho();
	}
	else
	{
		if (cam_.getOrtho() == true)
			cam_.disableOrtho();
	}
}