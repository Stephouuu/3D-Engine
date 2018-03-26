#include "Light.hpp"

Light::Light()
{
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

void Light::setLightShader(ofShader shader)
{
	shader = std::move(shader);
}

void Light::setPosition(const ofVec3f pos)
{
	light_.setGlobalPosition(pos);
}

void Light::setBrightness(const float brightness)
{
	shader_.begin();
	shader_.setUniform1f("brightness", brightness);
	shader_.end();
}

void Light::draw_(void)
{
//	shader_.setUniform3f("lightPosition", light_.getGlobalPosition() * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
}
