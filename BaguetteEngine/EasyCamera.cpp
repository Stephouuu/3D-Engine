#include "EasyCamera.hpp"

EasyCamera::EasyCamera(void)
	: targetTransitionDt_(0),
	  azimuth_(0),
	  orbiting_(false),
	  zoomDt_(0),
	  direction_(Direction::East)
{
	setNearClip(0.01);
	setFarClip(1000);

	setPosition(BasePosition);
	rotate(0, 0, 0, 0);
	lookAt(ofVec3f(0, 0, 0));

	setTarget(ofVec3f());
	setDistance(10);
}

EasyCamera::~EasyCamera(void)
{
}

void EasyCamera::update(float dt)
{
	if (targetTransitionDt_ > 0.000000f) {
		targetTransitionDt_ -= dt;
		if (targetTransitionDt_ < 0.000000f)
			targetTransitionDt_ = 0.000000f;
		targetTransition(1.f - targetTransitionDt_);
	}
	if (zoomDt_ > 0.000000f) {
		zoomDt_ -= (dt * 3.f);
		if (zoomDt_ < 0.000000f)
			zoomDt_ = 0.000000f;
		zoomTransition(1.f - zoomDt_);
	}
	if (orbiting_) {
		orbit(dt);
	}
}

void EasyCamera::setTarget(const ofVec3f & position)
{
	targetTransitionDt_ = 1.f;
	target_ = position;
	lookAt(position);
}

void EasyCamera::begin(ofRectangle viewport)
{
	ofCamera::begin(viewport);
}

void EasyCamera::end(void)
{
	ofCamera::end();
}
void EasyCamera::switchOrbit(void)
{
	orbiting_ = !orbiting_;
}

void EasyCamera::zoom(float f)
{
	savedDistance_ = distance_;
	zoomAxes_ = f;
	zoomDt_ = 1.f;
}

void EasyCamera::orbit(float dt)
{
	azimuth_ += dt * 20 * -(int)direction_;
	
	ofCamera::orbit(-azimuth_ , -45, getDistance(), target_);
	lookAt(target_);
}

void EasyCamera::setDirection(Direction dir)
{
	direction_ = dir;
}

void EasyCamera::targetTransition(float dt)
{
	currentLookAt_ += (target_ - currentLookAt_) * MathUtils::easeInSine(dt);
	lookAt(currentLookAt_);
}

void EasyCamera::zoomTransition(float dt)
{
	setDistance(savedDistance_ + (savedDistance_ / ZoomFactor) * zoomAxes_ * MathUtils::easeInSine(dt));
}

void EasyCamera::setDistance(float distance)
{
	if (distance > 0.00000f) {
		setPosition(target_ + (distance * getZAxis()));
		distance_ = distance;
	}
}

float EasyCamera::getDistance(void) const
{
	return distance_;
}