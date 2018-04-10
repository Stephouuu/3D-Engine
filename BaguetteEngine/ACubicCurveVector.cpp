#include "ACubicCurveVector.hpp"

ACubicCurveVector::ACubicCurveVector(void)
	: resolution_(40)
{
	for (int i = 0; i <= resolution_; ++i)
		line_.addVertex(ofPoint());
}

ACubicCurveVector::~ACubicCurveVector(void)
{
}

void ACubicCurveVector::setParam(const std::vector<ofVec2f> & v)
{
	v_ = v;
}

const std::vector<ofVec2f> & ACubicCurveVector::getParam(void) const
{
	return v_;
}

void ACubicCurveVector::invalidate(void)
{
	reallocate(ofGetWidth(), ofGetHeight());

	setOrigin(line_[resolution_ / 2]);

	drawFboBegin();
	ofSetColor(getFillColor());
	line_.draw();
	drawFboEnd();
}