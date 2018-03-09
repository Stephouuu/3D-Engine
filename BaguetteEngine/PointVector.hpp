#pragma once

#include "ofMain.h"

#include "AVectorPrimitive.hpp"

class PointVector : public AVectorPrimitive
{
public:
	PointVector(void);
	virtual ~PointVector(void);

	void setRadius(float radius);
	virtual void invalidate(void);

private:
	float radius_;
};

