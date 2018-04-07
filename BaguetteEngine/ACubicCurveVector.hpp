#pragma once

#include "AVectorPrimitive.hpp"
#include <vector>

#include "ofVec2f.h"

class ACubicCurveVector : public AVectorPrimitive
{
public:
	ACubicCurveVector(void);
	virtual ~ACubicCurveVector(void);

	virtual void setParam(const std::vector<ofVec2f> & v) = 0;

	virtual void invalidate(void);

protected:
	ofPolyline line_;
	float resolution_;
};

