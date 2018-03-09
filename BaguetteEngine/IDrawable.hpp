#pragma once

#include "ofNode.h"
#include "ofPoint.h"

class ARenderer;

struct IDrawable : public ofNode
{
	virtual ~IDrawable(void) {};

	virtual void update(float dt) = 0;
	virtual void draw(ARenderer & renderer) = 0;

	virtual void setColor(const ofColor & color) = 0;
	virtual const ofColor & getColor(void) const = 0;
};