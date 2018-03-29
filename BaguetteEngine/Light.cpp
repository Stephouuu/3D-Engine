#include "Light.hpp"

Light::Light()
{
	setLightShader(LightModel::blinn_phong);
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

void Light::setLightShader(Light::LightModel model)
{
	std::string		shaderVersion;
	std::string		shaderName;
	ofShader		shader;

	if (ofIsGLProgrammableRenderer())
		shaderVersion = "330";
	else
		shaderVersion = "120";

	shaderName = "shaders/";
	switch (model)
	{
	case Light::LightModel::lambert:
		shaderName += "lambert";
		break;
	case Light::LightModel::gouraud:
		shaderName += "gouraud";
		break;
	case Light::LightModel::phong:
		shaderName += "phong";
		break;
	case Light::LightModel::blinn_phong:
		shaderName += "blinn_phong";
		break;
	}
	shader.load(shaderName + "_" + shaderVersion + "_vs.glsl", shaderName + "_" + shaderVersion + "_fs.glsl");
}

void Light::setPosition(const ofVec3f pos)
{
	light_.setGlobalPosition(pos);
	shader_.begin();
	//shader_.setUniform3f("lightPosition", light_.getGlobalPosition() * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
	shader_.end();
}

void Light::setBrightness(const float brightness)
{
	shader_.begin();
	shader_.setUniform1f("brightness", brightness);
	shader_.end();
}

void Light::setAmbientColor(const float ambient)
{
	shader_.begin();
	shader_.setUniform1f("colorAmbient", ambient);
	shader_.end();
}

void Light::setDiffuseColor(const float diffuse)
{
	shader_.begin();
	shader_.setUniform1f("colorDiffuse", diffuse);
	shader_.end();
}

void Light::setSpecularColor(const float specular)
{
	shader_.begin();
	shader_.setUniform1f("colorSpecular", specular);
	shader_.end();
}

void Light::destroy(void)
{
}

void Light::update(float dt)
{
}

void Light::draw(ARenderer & renderer)
{
	ofEnableLighting();
	shader_.begin();
	shader_.setUniform3f("lightPosition", light_.getGlobalPosition() * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
	shader_.setUniform3f("colorAmbient", 0.1f, 0.1f, 0.1f);
	shader_.setUniform3f("colorDiffuse", 0.0f, 0.6f, 0.6f);
	shader_.setUniform3f("colorSpecular", 1.0f, 1.0f, 0.0f);
	shader_.setUniform1f("brightness", 20);
	shader_.end();
}

void Light::setFillColor(const ofColor & color)
{
}

const ofColor & Light::getFillColor(void) const
{
	return ofColor(255, 255, 255);
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
