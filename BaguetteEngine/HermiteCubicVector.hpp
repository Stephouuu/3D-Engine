#pragma once

#include "ACubicCurveVector.hpp"

class HermiteCubicVector : public ACubicCurveVector
{
public:
	HermiteCubicVector(void);
	virtual ~HermiteCubicVector(void);

	virtual void setParam(const std::vector<ofVec2f> & v);
};

