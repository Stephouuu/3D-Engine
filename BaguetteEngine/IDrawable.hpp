#pragma once

#include "ofNode.h"
#include "ofPoint.h"

class ARenderer;

struct IDrawable : public ofNode
{
public:
	virtual ~IDrawable(void) {};

	virtual void update(float dt) = 0;
	virtual void draw(ARenderer & renderer) = 0;

	virtual void setFillColor(const ofColor & color) = 0;
	virtual const ofColor & getFillColor(void) const = 0;

	virtual void setOutlineColor(const ofColor & color) = 0;
	virtual const ofColor &getOutlineColor(void) const = 0;

	virtual void setOutlineThickness(int thickness) = 0;
	virtual int getOutlineThickness(void) const = 0;

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

};