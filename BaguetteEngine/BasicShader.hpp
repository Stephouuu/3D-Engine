#pragma once

#include "IShader.hpp"

class BasicShader : public IShader
{
public:
	BasicShader();
	virtual ~BasicShader();
	virtual void begin();
	virtual void end();
	virtual bool load(std::string vertName, std::string fragName);
	virtual void setUniform1i(const std::string & name, int v1);
	virtual void setUniformTexture(const string &name, const ofTexture &img, int textureLocation);
	virtual void setUniformMatrix4f(const string &name, const ofMatrix4x4 &m, int count = 1);

private:
	ofShader	shader_;
};