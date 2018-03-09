#include "TriangleVector.hpp"

TriangleVector::TriangleVector(void)
	: size_(1)
{
}

TriangleVector::~TriangleVector(void)
{
}

void TriangleVector::invalidate(void)
{
	int ot = getOutlineThickness();
	float altitude = std::sqrt(3) / 2.f * size_;
	ofPoint fboSize = { (size_ * 1.5f) + (ot * 4), (size_ * 1.5f) + (ot * 4) };
	ofPoint fboMiddle = { fboSize.x / 2.f, fboSize.y / 2.f };

	if (getAlignment() == Alignment::Middle) {
		setOrigin(fboMiddle);
	}

	ofPoint p1 = { fboMiddle.x - size_ / 2.f, fboMiddle.y - size_ / 2.f };
	ofPoint p2 = { fboMiddle.x + size_ / 2.f, fboMiddle.y - size_ / 2.f };
	ofPoint p3 = { fboMiddle.x,	fboMiddle.y + altitude / 2.f };

	ofPoint p1InRot = MathUtils::Rotate2D(p1, getRotation(), fboMiddle);
	ofPoint p2InRot = MathUtils::Rotate2D(p2, getRotation(), fboMiddle);
	ofPoint p3InRot = MathUtils::Rotate2D(p3, getRotation(), fboMiddle);

	ofPoint p1Out = { p1.x - ot * 2.f, p1.y - ot };
	ofPoint p2Out = { p2.x + ot * 2.f, p2.y - ot };
	ofPoint p3Out = { p3.x, p3.y + ot * 2 };

	ofPoint p1OutRot = MathUtils::Rotate2D(p1Out, getRotation(), fboMiddle);
	ofPoint p2OutRot = MathUtils::Rotate2D(p2Out, getRotation(), fboMiddle);
	ofPoint p3OutRot = MathUtils::Rotate2D(p3Out, getRotation(), fboMiddle);

	reallocate(fboSize.x, fboSize.y);
	drawFboBegin();
		ofSetColor(getFillColor());
		ofDrawTriangle(p1InRot, p2InRot, p3InRot);

		ofSetColor(getOutlineColor());
		ofDrawTriangle(p1OutRot, p2OutRot, p3OutRot);
	drawFboEnd();
}

void TriangleVector::setSize(float size)
{
	size_ = size;
}