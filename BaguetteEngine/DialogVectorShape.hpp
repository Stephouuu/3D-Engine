#pragma once

#include "AVectorShape.hpp"

#include "RectangleVector.hpp"

class DialogVectorShape : public AVectorShape
{
public:
	DialogVectorShape(void);
	virtual ~DialogVectorShape(void);

	virtual void update(float dt);
	virtual void draw(ARenderer & renderer);

	virtual void setFillColor(const ofColor & color);
	virtual const ofColor & getFillColor(void) const;

	virtual void setOutlineColor(const ofColor & color);
	virtual const ofColor &getOutlineColor(void) const;

	virtual void setOutlineThickness(int thickness);
	virtual int getOutlineThickness(void) const;

	virtual void setTexture(Texture * texture);

	virtual void invalidate(void);

private:
	RectangleVector shape_;
	RectangleVector underscore_;
	RectangleVector maximize_;
	RectangleVector bar_;
	RectangleVector croix1_;
	RectangleVector croix2_;
};

