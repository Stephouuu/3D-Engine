#include "ADrawable.hpp"

ADrawable::ADrawable(void)
	: rotation_(0), focused_(false), texture_(nullptr)
{
}

ADrawable::~ADrawable(void)
{
}

void ADrawable::setTexture(Texture * texture)
{
	texture_ = texture;
}

Texture * ADrawable::texture(void)
{
	return texture_;
}

void ADrawable::setRotation(float degrees)
{
	rotation_ = degrees;
	invalidate();
}

float ADrawable::getRotation(void) const
{
	return rotation_;
}

void ADrawable::setFocused(bool v)
{
	focused_ = v;
}

bool ADrawable::isFocused(void) const
{
	return focused_;
}

void ADrawable::onPositionChanged(void)
{
	invalidate();
}

void ADrawable::onOrientationChanged(void)
{
	invalidate();
}

void ADrawable::onScaleChanged(void)
{
	invalidate();
}