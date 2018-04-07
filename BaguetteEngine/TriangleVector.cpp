#include "TriangleVector.hpp"

TriangleVector::TriangleVector(void)
{
}

TriangleVector::~TriangleVector(void)
{
}

void TriangleVector::invalidate(void)
{
	float size = getScale().x;
	int ot = getOutlineThickness();
	float altitude = std::sqrt(3) / 2.f * size;
	ofPoint fboSize = { (size * 1.5f) + (ot * 4), (size * 1.5f) + (ot * 4) };
	ofPoint fboMiddle = { fboSize.x / 2.f, fboSize.y / 2.f };

	setOrigin(fboMiddle);

	ofPoint p1 = { fboMiddle.x - size / 2.f, fboMiddle.y - size / 2.f };
	ofPoint p2 = { fboMiddle.x + size / 2.f, fboMiddle.y - size / 2.f };
	ofPoint p3 = { fboMiddle.x,	fboMiddle.y + altitude / 2.f };

	ofPoint p1Out = { p1.x - ot * 2.f, p1.y - ot };
	ofPoint p2Out = { p2.x + ot * 2.f, p2.y - ot };
	ofPoint p3Out = { p3.x, p3.y + ot * 2 };

	reallocate(fboSize.x, fboSize.y);
	drawFboBegin();
		ofSetColor(getFillColor());
		ofDrawTriangle(p1, p2, p3);

		ofSetColor(getOutlineColor());
		ofDrawTriangle(p1Out, p2Out, p3Out);
	drawFboEnd();
}