#pragma once

#include "ofMain.h"
#include "ADrawable.hpp"

class Light : public ADrawable
{
public:
	enum class LightModel { color_fill, lambert, gouraud, phong, blinn_phong, none };
	enum class LightType { ambiant, spotlight, directional, ponctual };
	typedef Light* Ptr;

public:
	Light();
	~Light();
	void	enable(void);
	void	disable(void);
	void	setPosition(const ofVec3f pos);
	ofVec3f	getPosition(void) const;
	void	setBrightness(const float brightness);
	void	setLightModel(const LightModel lightModel);
	void	setLightType(const LightType lightType);
	Light::LightModel	getLightModel(void) const;
	Light::LightType	getLightType(void) const;
	float	getBrightness(void) const;
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
	ofVec3f		pos_;
	ofColor		color_;
	LightModel	lightModel_;
	LightType	lightType_;
	float		brightness_;
	unsigned int drawableId_;
	ofLight		light_;
};

