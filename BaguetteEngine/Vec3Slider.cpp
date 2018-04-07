#include "Vec3Slider.hpp"

Vec3Slider::Vec3Slider(void)
{
}

Vec3Slider::~Vec3Slider(void)
{
}

void Vec3Slider::setValue(ofVec3f &vec)
{
	changeValue(vec);
}

const ofVec3f & Vec3Slider::getValue(void) const
{
	return value.cast<ofVec3f>();
}