#pragma once

#include "Light.hpp"

class LightGenerator
{
public:
	LightGenerator();
	~LightGenerator();
	//AMesh * operator()(void) const;
	void * generate() const; //Need to change that
	void setPosition(const ofVec3f pos);
	void setLightModel(Light::LightModel model);

private:
	Light	light_;
};
