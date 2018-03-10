#include "AVectorPrimitive.hpp"

AVectorPrimitive::AVectorPrimitive(void)
	: fillColor_(ofColor::white),
	  outlineColor_(ofColor::white),
	  outlineThickness_(0),
	  position_(0, 0),
	  rotation_(0.f),
	  origin_(0, 0)
{
}

AVectorPrimitive::~AVectorPrimitive(void)
{
}

void AVectorPrimitive::update(float dt)
{
	(void)dt;
}

void AVectorPrimitive::draw(ARenderer & renderer)
{
	ofDisableDepthTest();

	ofPushMatrix();
		ofTranslate(getPosition());
		ofRotateZ(getRotation());
		fbo_.draw(-getOrigin());
	ofPopMatrix();

	ofEnableDepthTest();
}

void AVectorPrimitive::setFillColor(const ofColor & color)
{
	fillColor_ = color;
	invalidate();
}

const ofColor & AVectorPrimitive::getFillColor(void) const
{
	return fillColor_;
}

void AVectorPrimitive::setOutlineColor(const ofColor & color)
{
	outlineColor_ = color;
	invalidate();
}

const ofColor & AVectorPrimitive::getOutlineColor(void) const
{
	return outlineColor_;
}

void AVectorPrimitive::setOutlineThickness(int thickness)
{
	outlineThickness_ = thickness;
	invalidate();
}

int AVectorPrimitive::getOutlineThickness(void) const
{
	return outlineThickness_;
}

const ofPoint & AVectorPrimitive::getOrigin(void) const
{
	return origin_;
}

void AVectorPrimitive::setAlignment(Alignment alignment)
{
	alignment_ = alignment;
}

AVectorPrimitive::Alignment AVectorPrimitive::getAlignment(void) const
{
	return alignment_;
}

void AVectorPrimitive::setOrigin(const ofPoint & origin)
{
	origin_ = origin;
}

void AVectorPrimitive::reallocate(int w, int h)
{
	if (fbo_.isAllocated()) {
		fbo_.destroy();
	}
	fbo_.allocate(w, h, GL_RGBA);
}

void AVectorPrimitive::drawFboBegin(void)
{
	fbo_.begin();
	ofClear(255, 255, 255, 0);
}

void AVectorPrimitive::drawFboEnd(void)
{
	fbo_.end();
}