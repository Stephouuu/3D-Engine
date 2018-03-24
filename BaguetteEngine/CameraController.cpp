#include "CameraController.hpp"

CameraController::CameraController(void)
{
}

CameraController::~CameraController(void)
{
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

void CameraController::switchOrbit(void)
{
	cam_.switchOrbit();
}

void CameraController::zoom(int factor)
{
	cam_.zoom(factor);
}

void CameraController::right(void)
{
	cam_.setDirection(EasyCamera::Direction::East);
}

void CameraController::left(void)
{
	cam_.setDirection(EasyCamera::Direction::West);
}