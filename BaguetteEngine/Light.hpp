#pragma once

#include "ofMain.h"
#include "ADrawable.hpp"

class Light : public ADrawable
{
public:
	enum class LightModel { color_fill, lambert, gouraud, phong, blinn_phong, none };
	typedef Light* Ptr;

public:
	Light();
	~Light();
	void	enable(void);
	void	disable(void);
	void	setPosition(const ofVec3f pos);
	ofVec3f	getPosition(void) const;
	void	setBrightness(const float brightness);
	void	setAmbientColor(const float ambiant);
	void	setDiffuseColor(const float diffuse);
	void	setSpecularColor(const float specular);
	void	setLightModel(const LightModel lightModel);
	Light::LightModel	getLightModel(void) const;
	void	setDrawableId(int id);
	int		getDrawableId(void) const;

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
	virtual void onPositionChanged(void);

private:
	ofLight		light_;
	ofVec3f		pos_;
	ofColor		color_;
	LightModel	lightModel_;
	float		brightness_;
	float		ambient_;
	float		diffuse_;
	float		specular_;
	unsigned int drawableId_;
};

