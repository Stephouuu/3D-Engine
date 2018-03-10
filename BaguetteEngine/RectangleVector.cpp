#include "RectangleVector.hpp"

RectangleVector::RectangleVector(void)
{
}

RectangleVector::~RectangleVector(void)
{
}

void RectangleVector::invalidate(void)
{
	float ot = getOutlineThickness();
	float w = getScale().x;
	float h = getScale().y;

	ofPoint fboSize = { w + ot * 3, h + ot * 3};
	ofPoint fboMiddle = fboSize / 2.f;

	setOrigin(fboMiddle);

	reallocate(fboSize.x, fboSize.y);
	drawFboBegin();
		ofSetColor(getFillColor());
		ofDrawRectangle(ot, ot, w + ot, h + ot);

		ofSetColor(getOutlineColor());
		ofDrawRectangle(0, 0, w + (3 * ot), h + (3 * ot));
	drawFboEnd();
}