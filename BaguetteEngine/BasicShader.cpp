#include "BasicShader.hpp"

BasicShader::BasicShader()
{
}

BasicShader::~BasicShader()
{
}

void BasicShader::begin()
{
	shader_.begin();
}

void BasicShader::end()
{
	shader_.end();
}

bool BasicShader::load(std::string vertName, std::string fragName)
{
	return shader_.load(vertName, fragName);
}

void BasicShader::setUniform1i(const std::string & name, int v1)
{
	shader_.setUniform1i(name, v1);
}

void BasicShader::setUniformTexture(const string & name, const ofTexture & img, int textureLocation)
{
	shader_.setUniformTexture(name, img, textureLocation);
}

void BasicShader::setUniformMatrix4f(const string & name, const ofMatrix4x4 & m, int count)
{
	shader_.setUniformMatrix4f(name, m, count);
}
