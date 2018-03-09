#pragma once

#include "AVectorPrimitive.hpp"

class RectangleVector : public AVectorPrimitive
{
public:
	RectangleVector(void);
	virtual ~RectangleVector(void);

	virtual void invalidate(void);

	void setDimension(int w, int h);
	void setWidth(int w);
	void setHeight(int h);

private:
	int w_;
	int h_;
};

