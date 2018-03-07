#pragma once

#include "AMesh.hpp"

class PlanePrimitive :
	public AMesh
{
public:
	PlanePrimitive();
	virtual ~PlanePrimitive();
	void setSize(const float width, const float height);

private:
	ofPlanePrimitive	plane_;
};

