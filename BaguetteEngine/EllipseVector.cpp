#include "EllipseVector.hpp"

EllipseVector::EllipseVector(void)
{
}

EllipseVector::~EllipseVector(void)
{
}

void EllipseVector::invalidate(void)
{
	float ot = getOutlineThickness();

	reallocate(w_ + ot * 2, h_ + ot * 2);
	drawFboBegin();
		ofSetColor(getFillColor());
		ofDrawEllipse(ofPoint((w_ / 2.f) + ot, (h_ / 2.f) + ot), w_ + ot, h_ + ot);

		ofSetColor(getOutlineColor());
		ofDrawEllipse(ofPoint(w_ / 2.f + ot, h_ / 2.f + ot), w_ + 2 * ot, h_ + 2 * ot);
	drawFboEnd();
}

void EllipseVector::setDimension(int w, int h)
{
	setWidth(w);
	setHeight(h);
}

void EllipseVector::setWidth(int w)
{
	w_ = w;
}

void EllipseVector::setHeight(int h)
{
	h_ = h;
}
