#include "EasyCamera.hpp"

EasyCamera::EasyCamera(void)
	: dt_(0), currentLookAt_(0, 0, 0), target_(nullptr)
{
	setDistance(10);
	setNearClip(0.01);
	setFarClip(1000);

	setTranslationKey('t');
}

EasyCamera::~EasyCamera(void)
{
}

void EasyCamera::update(float dt)
{
	if (target_) {
		if (dt_ > 0.000000f) {
			dt_ -= dt;
			if (dt_ < 0.000000f)
				dt_ = 0.000000f;
			transition(1.f - dt_);
		}
	}
}

void EasyCamera::targetPositionChanged(void)
{
	dt_ = 1;
}

void EasyCamera::begin(ofRectangle viewport)
{
	ofEasyCam::begin(viewport);
}

void EasyCamera::end(void)
{
	ofEasyCam::end();
}

void EasyCamera::setTargetSceneNode(SceneNode *node)
{
	if (node) {
		target_ = node;
		targetPositionChanged();
	}
	else {
		reset();
	}
}

void EasyCamera::reset(void)
{
	setPosition(ofVec3f(0, 10, 5));
	rotate(0, 0, 0, 0);
	lookAt(ofVec3f(0, 0, 0));
}

void EasyCamera::transition(float dt)
{
	const ofVec3f & p = target_->getDrawable()->getGlobalPosition();

	currentLookAt_ = {
		currentLookAt_.x + ((p.x - currentLookAt_.x) * std::sin(1.5707936f * dt)),
		currentLookAt_.y + ((p.y - currentLookAt_.y) * std::sin(1.5707936f * dt)),
		currentLookAt_.z + ((p.z - currentLookAt_.z) * std::sin(1.5707936f * dt))
	};
	lookAt(currentLookAt_);
}