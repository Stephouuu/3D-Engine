#pragma once

#include "AVectorPrimitive.hpp"
#include <vector>

#include "ofVec2f.h"

class ACubicCurveVector : public AVectorPrimitive
{
public:
	ACubicCurveVector(void);
	virtual ~ACubicCurveVector(void);

	virtual void invalidate(void);

	virtual void setParam(const std::vector<ofVec2f> & v);
	const std::vector<ofVec2f> & getParam(void) const;

protected:
	ofPolyline line_;
	float resolution_;
	std::vector<ofVec2f> v_;
};

