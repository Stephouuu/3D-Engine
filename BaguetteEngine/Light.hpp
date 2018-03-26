#pragma once

#include "ofMain.h"
#include "ADrawable.hpp"

class Light
{
public:
	enum class LightModel { color_fill, lambert, gouraud, phong, blinn_phong };

public:
	Light();
	~Light();
	void	enable(void);
	void	disable(void);
	void	setLightShader(ofShader shader);
	void	setPosition(const ofVec3f pos);
	void	setBrightness(const float brightness);
	void	draw_(void);

private:
	ofLight		light_;
	ofShader	shader_;
};

