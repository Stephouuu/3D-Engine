#pragma once

#include "ofNode.h"
#include "ofPoint.h"

class ARenderer;

struct IDrawable : public ofNode
{
public:
	IDrawable(void) : rotation_(0), focused_(false) {};
	virtual ~IDrawable(void) {};

	virtual void update(float dt) = 0;
	virtual void draw(ARenderer & renderer) = 0;

	virtual void setFillColor(const ofColor & color) = 0;
	virtual const ofColor & getFillColor(void) const = 0;

	virtual void setOutlineColor(const ofColor & color) = 0;
	virtual const ofColor &getOutlineColor(void) const = 0;

	virtual void setOutlineThickness(int thickness) = 0;
	virtual int getOutlineThickness(void) const = 0;

	void setRotation(float degrees)
	{
		rotation_ = degrees;
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

private:
	float rotation_;
	bool focused_;
};