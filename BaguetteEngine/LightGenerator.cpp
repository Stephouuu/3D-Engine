#include "LightGenerator.hh"



LightGenerator::LightGenerator()
{
}


LightGenerator::~LightGenerator()
{
}

void * LightGenerator::generate() const
{

	return nullptr;
}

void LightGenerator::setPosition(const ofVec3f pos)
{
	light_.setPosition(pos);
}

void LightGenerator::setLightModel(Light::LightModel model)
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
	case Light::LightModel::color_fill:
		shaderName += "color_fill";
		break;
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
	light_.setLightShader(shader);
}
