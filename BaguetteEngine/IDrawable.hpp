#pragma once

#include "ofNode.h"
#include "ofPoint.h"
#include "Texture.hpp"

class ARenderer;

struct IDrawable : public ofNode
{
public:
	IDrawable(void) : rotation_(0), focused_(false), texture_(nullptr) {};
	virtual ~IDrawable(void) {};

	virtual void update(float dt) = 0;
	virtual void draw(ARenderer & renderer) = 0;

	virtual void setFillColor(const ofColor & color) = 0;
	virtual const ofColor & getFillColor(void) const = 0;

	virtual void setOutlineColor(const ofColor & color) = 0;
	virtual const ofColor &getOutlineColor(void) const = 0;

	virtual void setOutlineThickness(int thickness) = 0;
	virtual int getOutlineThickness(void) const = 0;

	virtual void setTexture(Texture * texture) = 0;

	Texture * texture(void)
	{
		return texture_;
	}

	void setRotation(float degrees)
	{
		rotation_ = degrees;
		invalidate();
	}

	float getRotation(void) const
	{
		return rotation_;
	}

	void setFocused(bool v)
	{
		focused_ = v;
	}

	bool isFocused(void) const
	{
		return focused_;
	}

	virtual void invalidate(void) = 0;

	virtual void onPositionChanged(void) override
	{
		invalidate();
	}

	virtual void onOrientationChanged(void) override
	{
		invalidate();
	}

	virtual void onScaleChanged(void) override
	{
		invalidate();
	}

protected:
	Texture * texture_;

private:
	float rotation_;
	bool focused_;
};