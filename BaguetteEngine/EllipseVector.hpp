#pragma once

#include "AVectorPrimitive.hpp"

class EllipseVector : public AVectorPrimitive
{
public:
	EllipseVector(void);
	virtual ~EllipseVector(void);

	virtual void invalidate(void);
};

