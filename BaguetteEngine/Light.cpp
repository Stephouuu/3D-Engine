#include "Light.hpp"

Light::Light()
{
	setPosition(ofVec3f(0, 0, 0));
	setLightModel(LightModel::color_fill);
	setLightType(LightType::ambiant);
	color_.r = 255;
	color_.g = 0;
	color_.b = 0;
	brightness_ = 20.f;
	light_.setDiffuseColor(ofColor(255.f, 140.f, 0.f));
	light_.setSpecularColor(ofColor(255.f, 255.f, 255.f));
}

Light::~Light()
{
}

void Light::enable(void)
{
	light_.enable();
}

void Light::disable(void)
{
	light_.disable();
}

void Light::setPosition(const ofVec3f pos)
{
	light_.setGlobalPosition(pos);
	pos_ = pos;
}

void Light::onPositionChanged(void)
{
	setPosition(getGlobalPosition());
	invalidate();
}

ofVec3f Light::getPosition(void) const
{
	return pos_;
}

void Light::setBrightness(const float brightness)
{
	brightness_ = brightness;
}

float Light::getBrightness(void) const
{
	return brightness_;
}

void Light::setLightModel(const LightModel lightModel)
{
	lightModel_ = lightModel;
}

Light::LightModel Light::getLightModel(void) const
{
	return lightModel_;
}

void Light::destroy(void)
{
}

void Light::update(float dt)
{
}

void Light::draw(ARenderer & renderer)
{
}

void Light::setFillColor(const ofColor & color)
{
	color_ = color;
}

const ofColor & Light::getFillColor(void) const
{
	return color_;
}

void Light::setOutlineColor(const ofColor & color)
{
}

const ofColor & Light::getOutlineColor(void) const
{
	return ofColor(255, 255, 255);
}

void Light::setOutlineThickness(int thickness)
{
}

int Light::getOutlineThickness(void) const
{
	return 0;
}

void Light::invalidate(void)
{
}

void	Light::setDrawableId(int id)
{
	drawableId_ = id;
}

int		Light::getDrawableId(void) const
{
	return drawableId_;
}

Light::LightType	Light::getLightType(void) const
{
	return lightType_;
}

void	Light::setLightType(const LightType lightType)
{
	if (lightType == Light::LightType::directional)
	{
		light_.setDirectional();
		light_.setOrientation(ofVec3f(0, 90, 0));
	}
	else if (lightType == Light::LightType::ponctual)
		light_.setPointLight();
	else if (lightType == Light::LightType::spotlight)
		light_.setSpotlight();
	lightType_ = lightType;
}