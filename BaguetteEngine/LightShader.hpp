#pragma once

#include <map>
#include <sstream>
#include "IShader.hpp"
#include "Light.hpp"

class LightShader : public IShader
{
public:
	LightShader();
	virtual ~LightShader();
	virtual void load();
	virtual void begin();
	virtual void end();
	virtual bool load(std::string vertName, std::string fragName);
	virtual void setUniform1i(const std::string & name, int v1);
	virtual void setUniformTexture(const string &name, const ofTexture &img, int textureLocation);
	virtual void setLights(std::vector<Light *> * lights);
	virtual void setUniformMatrix4f(const string &name, const ofMatrix4x4 &m, int count = 1);
	size_t countLights() const;
	void setSpecularMaterial(const ofColor &color);
	void setDiffuseMaterial(const ofColor &color);

private:
	std::map<Light::LightModel, ofShader> shaders_;
	ofShader						*activeShader_;
	std::vector<Light *>			*lights_;
	ofMaterial						material;
	ofColor							specularMaterial_;
	ofColor							diffuseMaterial_;
};