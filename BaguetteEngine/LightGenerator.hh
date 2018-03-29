#pragma once

#include "Light.hpp"

class LightGenerator
{
public:
	LightGenerator();
	~LightGenerator();
	//ADrawable * operator()(void) const;
	//virtual ADrawable * generate() const;
	void setPosition(const ofVec3f pos);
	void setLightModel(Light::LightModel model);

private:
	Light	light_;
};
