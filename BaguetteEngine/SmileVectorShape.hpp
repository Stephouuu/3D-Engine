#pragma once

#include "AVectorShape.hpp"

#include "PointVector.hpp"
#include "EllipseVector.hpp"

class SmileVectorShape : public AVectorShape
{
public:
	SmileVectorShape(void);
	virtual ~SmileVectorShape(void);

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
	PointVector circle_;
	EllipseVector eye1_;
	EllipseVector eye2_;
	EllipseVector eye3_;
	EllipseVector eye4_;
};

