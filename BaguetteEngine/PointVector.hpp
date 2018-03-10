#pragma once

#include "ofMain.h"

#include "AVectorPrimitive.hpp"

class PointVector : public AVectorPrimitive
{
public:
	PointVector(void);
	virtual ~PointVector(void);

	virtual void invalidate(void);
};

