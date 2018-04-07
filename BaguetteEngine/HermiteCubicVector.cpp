#include "HermiteCubicVector.hpp"

HermiteCubicVector::HermiteCubicVector(void)
{
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

HermiteCubicVector::~HermiteCubicVector(void)
{
}

void HermiteCubicVector::setParam(const std::vector<ofVec2f> & v)
{
	if (v.size() < 4)
		return;

	for (int i = 0; i <= resolution_; ++i)
	{
		ofVec2f tan1 = v[1] - v[0];
		ofVec2f tan2 = v[2] - v[3];

		float t = i / resolution_;
		float u = 1 - t;
		float uu = u * u;
		float uuu = uu * u;
		float tt = t * t;
		float ttt = tt * t;

		ofVec2f p = {
			(2 * ttt - 3 * tt + 1) * v[0].x + (ttt - 2 * tt + t) * tan1.x + (ttt - tt) * tan2.x + (-2 * ttt + 3 * tt) * v[3].x,
			(2 * ttt - 3 * tt + 1) * v[0].y + (ttt - 2 * tt + t) * tan1.y + (ttt - tt) * tan2.y + (-2 * ttt + 3 * tt) * v[3].y
		};

		line_[i] = p;
	}

	invalidate();
}