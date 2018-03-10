#pragma once

#include "AVectorPrimitive.hpp"

class RectangleVector : public AVectorPrimitive
{
public:
	RectangleVector(void);
	virtual ~RectangleVector(void);

	virtual void invalidate(void);
};

