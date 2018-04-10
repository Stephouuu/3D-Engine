#include "LightShader.hpp"

LightShader::LightShader() : lights_(nullptr)
{
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
	for (it = lights_->begin(); it != lights_->end(); it++)
	{
		if (i == 0)
		{
			activeShader_ = &shaders_[(*it)->getLightModel()];
			activeShader_->begin();
		}
		ofColor		color = (*it)->getFillColor();
		if ((*it)->getLightModel() == Light::LightModel::color_fill)
		{
			stringstream ss;

			ss << i;
			//std::cout << "i = " << "lightColors[" + ss.str() + "]" << std::endl;
			//std::cout << "Color = " << color << std::endl;
			activeShader_->setUniform4f("lightColors[" + ss.str() + "]", color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
		}
		else if ((*it)->getLightModel() == Light::LightModel::lambert)
		{
			activeShader_->setUniform4f("colorAmbient", color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
			activeShader_->setUniform3f("colorDiffuse", 0.6f, 0.6f, 0.6f);
		}
		else if ((*it)->getLightModel() == Light::LightModel::gouraud)
		{
			activeShader_->setUniform3f("color", 1.f, 0.f, 0.f);
			activeShader_->setUniform4f("colorAmbient", color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
			activeShader_->setUniform3f("colorDiffuse", 0.6f, 0.6f, 0.0f);
			activeShader_->setUniform3f("colorSpecular", 1.0f, 1.0f, 0.0f);
			activeShader_->setUniform1f("brightness", 20);
		}
		else if ((*it)->getLightModel() == Light::LightModel::phong)
		{
			activeShader_->setUniform4f("colorAmbient", color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);

			activeShader_->setUniform3f("colorDiffuse", 0.6f, 0.6f, 0.0f);
			
			activeShader_->setUniform3f("colorSpecular", 1.0f, 1.0f, 0.0f);

			activeShader_->setUniform3f("spotDir", 0.0f, 0.0f, 0.0f);
			activeShader_->setUniform1f("spotSize", 0.0f);

			activeShader_->setUniform1f("brightness", 20);
		}
		else if ((*it)->getLightModel() == Light::LightModel::blinn_phong)
		{
			activeShader_->setUniform3f("color", 1.f, 0.f, 0.f);
			activeShader_->setUniform4f("colorAmbient", color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
			activeShader_->setUniform3f("colorDiffuse", 0.6f, 0.6f, 0.0f);
			activeShader_->setUniform3f("colorSpecular", 1.0f, 1.0f, 0.0f);
			activeShader_->setUniform1f("brightness", 20);
		}
		activeShader_->setUniform3f("lightPosition", (*it)->getPosition() * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
		i++;
	}
	if (activeShader_ != nullptr)
	{
		activeShader_->setUniform1i("lightNb", i);
		//activeShader_->setAttribute4fv("lightColors", (float*)&colors, colors.size());
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