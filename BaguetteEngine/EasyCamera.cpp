#include "EasyCamera.hpp"

EasyCamera::EasyCamera(void)
{
	setNearClip(0.01);
	setFarClip(1000);

	reset();
}

EasyCamera::~EasyCamera(void)
{
}

void EasyCamera::reset(void)
{
	rotate(0, 0, 0, 0);
	setPosition(BasePosition);

	/* Par défault, la caméra regarde devant elle */
	lookAt({ BasePosition.x, BasePosition.y, BasePosition.z - 1});

	targetTransitionDt_ = 0;
	latitude_ = 0;
	longitude_ = 0;
	zoomDt_ = 0;
	longitudeDirection_ = OrbitDirection::None;
	latitudeDirection_ = OrbitDirection::None;
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
		if (zoomDt_ < 0.000000f) {
			zoomDt_ = 0.000000f;
		}
		zoomTransition(1.f - zoomDt_);
	}
	
	orbit(dt);
}

void EasyCamera::setTarget(const ofVec3f & position)
{
	targetTransitionDt_ = 1.f;
	target_ = position;
	latitudeDirection_ = OrbitDirection::None;
	longitudeDirection_ = OrbitDirection::None;
	latitude_ = -45;
	longitude_ = 0;

	elevation_ = position.distance(getPosition());
	savedElevation_ = elevation_;

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

void EasyCamera::zoom(float f)
{
	savedElevation_ = elevation_;
	zoomAxes_ = f;
	zoomDt_ = 1.f;
}

void EasyCamera::orbit(float dt)
{
	if (longitudeDirection_ != OrbitDirection::None /*|| latitudeDirection_ != OrbitDirection::None*/) {

		longitude_ += dt * 40 * -(int)longitudeDirection_;
		// latitude_ += dt * 30 * -(int)latitudeDirection_;
		ofCamera::orbit(-longitude_, -45, getDistanceFromTarget(), target_);
		setElevation(getElevation());
		lookAt(target_);
	}
}

void EasyCamera::setLongitudeDirection(OrbitDirection dir)
{
	longitudeDirection_ = dir;
}

void EasyCamera::setLatitudeDirection(OrbitDirection dir)
{
	latitudeDirection_ = dir;
}

void EasyCamera::targetTransition(float dt)
{
	currentLookAt_ += (target_ - currentLookAt_) * MathUtils::easeInSine(dt);
	lookAt(currentLookAt_);
}

void EasyCamera::zoomTransition(float dt)
{
	setElevation(savedElevation_ + (savedElevation_ / ZoomFactor) * zoomAxes_ * MathUtils::easeInSine(dt));
}

void EasyCamera::setElevation(float distance)
{
	if (distance > 0.00000f) {
		setPosition(target_ + (distance * getZAxis()));
		elevation_ = distance;
	}
}

float EasyCamera::getElevation(void) const
{
	return elevation_;
}

float EasyCamera::getDistanceFromTarget(void) const
{
	return target_.distance(getPosition());
}