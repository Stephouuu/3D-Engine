#pragma once

#include "AMesh.hpp"

class SpherePrimitive : public AMesh
{
public:
	SpherePrimitive();
	virtual ~SpherePrimitive();
	void setRadius(const float radius);

private:
	ofSpherePrimitive	sphere_;
};

