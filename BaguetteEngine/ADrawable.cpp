#include "ADrawable.hpp"

ADrawable::ADrawable(void)
	: rotation_(0), focused_(false)
{
}

ADrawable::~ADrawable(void)
{
}

void ADrawable::setTexture(Texture * texture, int i)
{
	if (i >= textures_.size()) textures_.push_back(texture);
	else {
		delete textures_[i];
		if (!texture) {
			textures_.erase(std::cbegin(textures_) + i);
		}
		else {
			textures_[i] = texture;
		}
	}
}

Texture *ADrawable::getTexture(int i)
{
	if (i >= textures_.size())
		return nullptr;
	return textures_[i];
}

void ADrawable::setShader(const std::string & v, const std::string & f)
{
	shader_.load(v, f);
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