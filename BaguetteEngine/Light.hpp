#pragma once

#include "ofMain.h"
#include "ADrawable.hpp"

class Light : public ADrawable
{
public:
	enum class LightModel { lambert, gouraud, phong, blinn_phong };

public:
	Light();
	~Light();
	void	enable(void);
	void	disable(void);
	void	setLightShader(Light::LightModel model);
	void	setPosition(const ofVec3f pos);
	void	setBrightness(const float brightness);
	void	setAmbientColor(const float ambiant);
	void	setDiffuseColor(const float diffuse);
	void	setSpecularColor(const float specular);

	virtual void destroy(void);
	virtual void update(float dt);
	virtual void draw(ARenderer & renderer);
	virtual void setFillColor(const ofColor & color);
	virtual const ofColor & getFillColor(void) const;
	virtual void setOutlineColor(const ofColor & color);
	virtual const ofColor &getOutlineColor(void) const;
	virtual void setOutlineThickness(int thickness);
	virtual int getOutlineThickness(void) const;
	virtual void invalidate(void);


private:
	ofLight		light_;
	ofShader	shader_;
};

