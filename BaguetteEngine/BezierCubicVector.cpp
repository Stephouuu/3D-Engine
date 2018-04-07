#include "BezierCubicVector.hpp"

BezierCubicVector::BezierCubicVector(void)
	: resolution_(40)
{
	for (int i = 0; i <= resolution_; ++i)
		line_.addVertex(ofPoint());

	int framebuffer_width = ofGetWidth();
	int framebuffer_height = ofGetHeight();

	float w_1_8 = framebuffer_width / 8.0f;
	float w_3_4 = framebuffer_width * 3.0f / 4.0f;
	float h_1_5 = framebuffer_height / 5.0f;
	float h_4_5 = framebuffer_height * 4.0f / 5.0f;

	setParam({
		{ w_1_8, h_4_5 },
		{ w_1_8, h_4_5 },
		{ w_3_4, h_1_5 },
		{ w_3_4, h_1_5 }
	});
}

BezierCubicVector::~BezierCubicVector(void)
{
}

void BezierCubicVector::invalidate(void)
{
	reallocate(ofGetWidth(), ofGetHeight());

	setOrigin(line_[resolution_ / 2]);

	drawFboBegin();
		ofSetColor(getFillColor());
		line_.draw();
	drawFboEnd();
}

void BezierCubicVector::setParam(const std::vector<ofVec2f> & v)
{
	if (v.size() < 4)
		return;
	
	for (int i = 0; i <= resolution_; ++i)
	{
		float t = i / resolution_;
		float u = 1 - t;
		float uu = u * u;
		float uuu = uu * u;
		float tt = t * t;
		float ttt = tt * t;

		ofVec2f p = {
			uuu * v[0].x + 3 * uu * t * v[1].x + 3 * u * tt * v[2].x + ttt * v[3].x,
			uuu * v[0].y + 3 * uu * t * v[1].y + 3 * u * tt * v[2].y + ttt * v[3].y
		};

		line_[i] = p;
	}

	invalidate();
}