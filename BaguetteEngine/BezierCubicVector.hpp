#pragma once

#include <vector>

#include "AVectorPrimitive.hpp"

// todo: superclass CubicCurves
class BezierCubicVector : public AVectorPrimitive
{
public:
	BezierCubicVector(void);
	virtual ~BezierCubicVector(void);

	virtual void invalidate(void);

	void setParam(const std::vector<ofVec2f> & v);

private:
	ofPolyline line_;
	float resolution_;
};

