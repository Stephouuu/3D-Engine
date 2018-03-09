#pragma once

#include "AVectorPrimitive.hpp"

class EllipseVector : public AVectorPrimitive
{
public:
	EllipseVector(void);
	virtual ~EllipseVector(void);

	virtual void invalidate(void);

	void setDimension(int w, int h);
	void setWidth(int w);
	void setHeight(int h);

private:
	int w_;
	int h_;
};

