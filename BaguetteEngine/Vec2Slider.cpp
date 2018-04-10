#include "Vec2Slider.hpp"

Vec2Slider::Vec2Slider(void)
{
}

Vec2Slider::~Vec2Slider(void)
{
}

void Vec2Slider::setValue(ofVec2f & vec)
{
	changeValue(vec);
}

const ofVec2f & Vec2Slider::getValue(void) const
{
	return value.cast<ofVec2f>();
}