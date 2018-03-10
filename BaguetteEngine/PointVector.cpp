#include "PointVector.hpp"

PointVector::PointVector(void)
{
}

PointVector::~PointVector(void)
{
}

void PointVector::invalidate(void)
{
	int ot = getOutlineThickness();
	float r = std::max({ getScale().x, getScale().y, getScale().z });

	ofPoint fboSize = { (r * 2.f) + (ot * 2), (r * 2.f) + (ot * 2) };
	ofPoint fboMiddle = fboSize / 2.f;

	setOrigin(fboMiddle);

	reallocate(fboSize.x, fboSize.y);
	drawFboBegin();
		ofSetColor(getFillColor());
		ofDrawCircle(ofPoint(r + ot, r + ot), r);

		ofSetColor(getOutlineColor());
		ofDrawCircle(ofPoint(r + ot, r + ot), r + ot);
	drawFboEnd();
}