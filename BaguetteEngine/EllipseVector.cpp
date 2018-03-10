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
	float w = getScale().x;
	float h = getScale().y;

	ofPoint fboSize = { w + ot * 2, h + ot * 2 };
	ofPoint fboMiddle = fboSize / 2.f;

	setOrigin(fboMiddle);

	reallocate(fboSize.x, fboSize.y);
	drawFboBegin();
		ofSetColor(getFillColor());
		ofDrawEllipse(ofPoint((w / 2.f) + ot, (h / 2.f) + ot), w + ot, h + ot);

		ofSetColor(getOutlineColor());
		ofDrawEllipse(ofPoint(w / 2.f + ot, h / 2.f + ot), w + 2 * ot, h + 2 * ot);
	drawFboEnd();
}