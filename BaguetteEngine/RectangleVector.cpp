#include "RectangleVector.hpp"

RectangleVector::RectangleVector(void)
	: w_(10), h_(10)
{
}

RectangleVector::~RectangleVector(void)
{
}

void RectangleVector::invalidate(void)
{
	float ot = getOutlineThickness();

	reallocate(w_ + ot * 3, h_ + ot * 3);
	drawFboBegin();
		ofSetColor(getFillColor());
		ofDrawRectangle(ot, ot, w_ + ot, h_ + ot);

		ofSetColor(getOutlineColor());
		ofDrawRectangle(0, 0, w_ + (3 * ot), h_ + (3 * ot));
	drawFboEnd();
}

void RectangleVector::setDimension(int w, int h)
{
	setWidth(w);
	setHeight(h);
}

void RectangleVector::setWidth(int w)
{
	w_ = w;
}

void RectangleVector::setHeight(int h)
{
	h_ = h;
}