#include "ADrawable.hpp"

ADrawable::ADrawable(void)
	: rotation_(0), focused_(false), shader_(nullptr), otherShader_(false)
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
	otherShader_ = true;
	basicShader_.load(v, f);
}

void ADrawable::setShader(IShader *shader)
{
	otherShader_ = false;
	shader_ = shader;
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

bool ADrawable::haveOtherShader() const
{
	return otherShader_;
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

void ADrawable::setSpecularColor(const ofColor & color)
{
	specularColor_ = color;
}

ofColor ADrawable::getSpecularColor() const
{
	return specularColor_;
}

void ADrawable::setDiffuseColor(const ofColor & color)
{
	diffuseColor_ = color;
}

ofColor ADrawable::getDiffuseColor() const
{
	return diffuseColor_;
}
