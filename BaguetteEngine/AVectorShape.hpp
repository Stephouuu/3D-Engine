#pragma once

#include "IDrawable.hpp"

class AVectorShape : public IDrawable
{
public:
	AVectorShape(void);
	virtual ~AVectorShape(void);

	virtual void destroy(void) {}

 	virtual void update(float dt) = 0;
	virtual void draw(ARenderer & renderer) = 0;

	virtual void setFillColor(const ofColor & color) = 0;
	virtual const ofColor & getFillColor(void) const = 0;

	virtual void setOutlineColor(const ofColor & color) = 0;
	virtual const ofColor &getOutlineColor(void) const = 0;

	virtual void setOutlineThickness(int thickness) = 0;
	virtual int getOutlineThickness(void) const = 0;

	virtual void setTexture(Texture * texture) = 0;

	virtual void invalidate(void) = 0;
};