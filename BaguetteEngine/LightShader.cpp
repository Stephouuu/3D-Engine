#include "LightShader.hpp"

LightShader::LightShader() : lights_(nullptr)
{
	material.setShininess(120);
	material.setSpecularColor(ofColor(255, 255, 255, 255));

}

LightShader::~LightShader()
{
}

void LightShader::load()
{
	ofShader shaderColorFill;
	ofShader shaderLambert;
	ofShader shaderGouraud;
	ofShader shaderPhong;
	ofShader shaderBlinnPhong;
	ofShader shaderNone;

	shaderColorFill.load("./shaders/color_fill_330_vs.glsl", "./shaders/color_fill_330_fs.glsl");
	shaders_.insert(std::make_pair(Light::LightModel::color_fill, std::move(shaderColorFill)));
	shaderLambert.load("./shaders/lambert_330_vs.glsl", "./shaders/lambert_330_fs.glsl");
	shaders_.insert(std::make_pair(Light::LightModel::lambert, std::move(shaderLambert)));
	shaderGouraud.load("./shaders/gouraud_330_vs.glsl", "./shaders/gouraud_330_fs.glsl");
	shaders_.insert(std::make_pair(Light::LightModel::gouraud, std::move(shaderGouraud)));
	shaderPhong.load("./shaders/phong_330_vs.glsl", "./shaders/phong_330_fs.glsl");
	shaders_.insert(std::make_pair(Light::LightModel::phong, std::move(shaderPhong)));
	shaderBlinnPhong.load("./shaders/blinn_phong_330_vs.glsl", "./shaders/blinn_phong_330_fs.glsl");
	shaders_.insert(std::make_pair(Light::LightModel::blinn_phong, std::move(shaderBlinnPhong)));
	shaderNone.load("./shaders/vertex_shader.vert", "./shaders/fragment_shader.frag");
	shaders_.insert(std::make_pair(Light::LightModel::none, std::move(shaderNone)));
	activeShader_ = &shaders_[Light::LightModel::none];
}

void LightShader::begin()
{
	std::vector<Light*>::const_iterator it;
	unsigned int						i;

	i = 0;
	if (lights_ == nullptr)
	{
		activeShader_->begin();
		return;
	}

	for (it = lights_->cbegin(); it != lights_->cend() && i < 4; it++)
	{
		if (i == 0)
		{
			activeShader_ = &shaders_[(*it)->getLightModel()];
			activeShader_->begin();
		}
		ofColor		color = (*it)->getFillColor();
		//ofColor		diffuseColor = (*it)->getDiffuseColor() + diffuseMaterial_;
		//ofColor		specularColor = (*it)->getSpecularColor() + specularMaterial_;
		ofColor		diffuseColor = (*it)->getDiffuseColor();
		ofColor		specularColor = (*it)->getSpecularColor();
		if ((*it)->getLightModel() == Light::LightModel::color_fill)
		{
			std::cout << "i == " << "colorAmbient" + std::to_string(i) << std::endl;
			activeShader_->setUniform4f("colorAmbient" + std::to_string(i), color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
		}
		else if ((*it)->getLightModel() == Light::LightModel::lambert)
		{
			activeShader_->setUniform4f("colorAmbient", color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
			activeShader_->setUniform3f("colorDiffuse", diffuseColor.r / 255.f, diffuseColor.g / 255.f, diffuseColor.b / 255.f);
			if ((*it)->getLightType() == Light::LightType::spotlight)
				activeShader_->setUniform1f("coneAngle", 15.f);
			else
				activeShader_->setUniform1f("coneAngle", -1.f);
			activeShader_->setUniform1f("brightness", (*it)->getBrightness());
		}
		else if ((*it)->getLightModel() == Light::LightModel::gouraud)
		{
			activeShader_->setUniform4f("colorAmbient", color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
			activeShader_->setUniform3f("colorDiffuse", diffuseColor.r / 255.f, diffuseColor.g / 255.f, diffuseColor.b / 255.f);
			activeShader_->setUniform3f("colorSpecular", specularColor.r / 255.f, specularColor.g / 255.f, specularColor.b / 255.f);
			if ((*it)->getLightType() == Light::LightType::spotlight)
				activeShader_->setUniform1f("coneAngle", 15.f);
			else
				activeShader_->setUniform1f("coneAngle", -1.f);
			activeShader_->setUniform1f("brightness", (*it)->getBrightness());
		}
		else if ((*it)->getLightModel() == Light::LightModel::phong)
		{
			activeShader_->setUniform4f("colorAmbient", color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
			activeShader_->setUniform3f("colorDiffuse", diffuseColor.r / 255.f, diffuseColor.g / 255.f, diffuseColor.b / 255.f);
			activeShader_->setUniform3f("colorSpecular", specularColor.r / 255.f, specularColor.g / 255.f, specularColor.b / 255.f);
			if ((*it)->getLightType() == Light::LightType::spotlight)
				activeShader_->setUniform1f("coneAngle", 15.f);
			else
				activeShader_->setUniform1f("coneAngle", -1.f);
			activeShader_->setUniform1f("brightness", (*it)->getBrightness());
		}
		else if ((*it)->getLightModel() == Light::LightModel::blinn_phong)
		{
			activeShader_->setUniform4f("colorAmbient", color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
			activeShader_->setUniform3f("colorDiffuse", diffuseColor.r / 255.f, diffuseColor.g / 255.f, diffuseColor.b / 255.f);
			activeShader_->setUniform3f("materialSpecularColor", specularColor.r / 255.f, specularColor.g / 255.f, specularColor.b / 255.f);
			if ((*it)->getLightType() == Light::LightType::spotlight)
				activeShader_->setUniform1f("coneAngle", 15.f);
			else
				activeShader_->setUniform1f("coneAngle", -1.f);
			activeShader_->setUniform1f("materialShininess", (*it)->getBrightness());
		}
		activeShader_->setUniform3f("lightPosition", (*it)->getGlobalPosition() * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
		i++;
	}
	if (activeShader_ != nullptr)
	{
		activeShader_->setUniform1i("lightNb", i);
	}
	if (i == 0)
		activeShader_->begin();
}

void LightShader::end()
{
	activeShader_->end();
}

bool LightShader::load(std::string vertName, std::string fragName)
{
	//Not necessary for now
	return false;
}

void LightShader::setUniform1i(const std::string & name, int v1)
{
	activeShader_->setUniform1i(name, v1);
}

void LightShader::setUniformTexture(const string &name, const ofTexture &img, int textureLocation)
{
	activeShader_->setUniformTexture(name, img, textureLocation);
}

void LightShader::setLights(std::vector<Light*> * lights)
{
	lights_ = lights;
}

void LightShader::setUniformMatrix4f(const string &name, const ofMatrix4x4 &m, int count)
{
	activeShader_->setUniformMatrix4f(name, m, count);
}

size_t LightShader::countLights() const
{
	if (lights_ == nullptr)
		return (0);
	return lights_->size();
}

void LightShader::setSpecularMaterial(const ofColor &color)
{
	specularMaterial_ = color;
}


void LightShader::setDiffuseMaterial(const ofColor &color)
{
	diffuseMaterial_ = color;
}