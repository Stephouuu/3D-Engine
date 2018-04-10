#include "Light.hpp"

Light::Light()
{
	setPosition(ofVec3f(0, 0, 0));
	setLightModel(LightModel::color_fill);
	color_.r = 255;
	color_.g = 0;
	color_.b = 0;
	brightness_ = 0.f;
	ambient_ = 0.f;
	diffuse_ = 0.f;
	specular_ = 0.f;
}

Light::~Light()
{
}

void Light::enable(void)
{
	//light_.enable();
}

void Light::disable(void)
{
	//light_.disable();
}

void Light::setPosition(const ofVec3f pos)
{
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

void Light::setAmbientColor(const float ambient)
{
	ambient_ = ambient;
}

void Light::setDiffuseColor(const float diffuse)
{
	diffuse_ = diffuse;
}

void Light::setSpecularColor(const float specular)
{
	specular_ = specular;
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
