#pragma once

#include "ofMain.h"

class IShader
{
public:
	virtual ~IShader() {}
	virtual void begin() = 0;
	virtual void end() = 0;
	virtual bool load(std::string vertName, std::string fragName) = 0;
	virtual void setUniform1i(const std::string & name, int v1) = 0;
	virtual void setUniformTexture(const string &name, const ofTexture &img, int textureLocation) = 0;
	virtual void setUniformMatrix4f(const string &name, const ofMatrix4x4 &m, int count = 1) = 0;
};