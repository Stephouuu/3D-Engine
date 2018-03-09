#include "PointVector.hpp"

PointVector::PointVector(void)
	: radius_(1)
{
}

PointVector::~PointVector(void)
{
}

void PointVector::invalidate(void)
{
	int ot = getOutlineThickness();

	reallocate((radius_ * 2.f) + (ot * 2), (radius_ * 2.f) + (ot * 2));
	drawFboBegin();
		ofSetColor(getFillColor());
		ofDrawCircle(ofPoint(radius_ + ot, radius_ + ot), radius_);

		ofSetColor(getOutlineColor());
		ofDrawCircle(ofPoint(radius_ + ot, radius_ + ot), radius_ + ot);
	drawFboEnd();
}

void PointVector::setRadius(float radius)
{
	radius_ = radius;
}