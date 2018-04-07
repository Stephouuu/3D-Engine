#pragma once

#include "ACubicCurveVector.hpp"

class BezierCubicVector : public ACubicCurveVector
{
public:
	BezierCubicVector(void);
	virtual ~BezierCubicVector(void);

	virtual void setParam(const std::vector<ofVec2f> & v);
};

